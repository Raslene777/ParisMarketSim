#include "engine/MatchingEngine.hpp"
#include "core/Transaction.hpp"
#include "user/Portefeuille.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>

MatchingEngine::MatchingEngine() {}

void MatchingEngine::ajouterOrdre(const Ordre& ordre) {

    if (!ordre.valider())
        return;

    if (ordre.getType() == TypeOrdre::ACHAT)
        buyOrders.push_back(ordre);
    else
        sellOrders.push_back(ordre);

    executerMatch();
}

void MatchingEngine::executerMatch() {

    std::sort(buyOrders.begin(), buyOrders.end(),
              [](const Ordre& a, const Ordre& b) {
                  return a.getPrix() > b.getPrix();
              });

    std::sort(sellOrders.begin(), sellOrders.end(),
              [](const Ordre& a, const Ordre& b) {
                  return a.getPrix() < b.getPrix();
              });

    for (size_t i = 0; i < buyOrders.size(); ++i) {

        for (size_t j = 0; j < sellOrders.size(); ++j) {

            if (buyOrders[i].getActionId() != sellOrders[j].getActionId())
                continue;

            if (buyOrders[i].getPrix() < sellOrders[j].getPrix())
                continue;

            int quantiteExec = std::min(
                buyOrders[i].getQuantite(),
                sellOrders[j].getQuantite()
            );

            double prixExec = sellOrders[j].getPrix();
            double montantTotal = prixExec * quantiteExec;

            Portefeuille acheteur(buyOrders[i].getCompteId());
            Portefeuille vendeur(sellOrders[j].getCompteId());

            // VALIDATE BOTH SIDES FIRST
            if (!vendeur.aAssez(
                    sellOrders[j].getActionId(),
                    quantiteExec))
                continue;

            if (!acheteur.peutDebiter(montantTotal))
                continue;

            // EXECUTE AFTER VALIDATION
            vendeur.retirerAction(
                sellOrders[j].getActionId(),
                quantiteExec
            );

            acheteur.ajouterAction(
                buyOrders[i].getActionId(),
                quantiteExec
            );

            updateCompteSolde(
                buyOrders[i].getCompteId(),
                montantTotal,
                true
            );

            updateCompteSolde(
                sellOrders[j].getCompteId(),
                montantTotal,
                false
            );

            long long transaction_id = std::time(nullptr);

            Transaction transaction(
                transaction_id,
                buyOrders[i].getOrdreId(),
                sellOrders[j].getOrdreId(),
                buyOrders[i].getActionId(),
                prixExec,
                quantiteExec,
                "2026-01-01"
            );

            transaction.enregistrerCSV("data/transactions.csv");

            std::ofstream cours("data/cours_actions.csv", std::ios::app);
            cours << transaction_id << ","
                  << buyOrders[i].getActionId() << ","
                  << prixExec << ","
                  << "2026-01-01\n";

            buyOrders[i].mettreAJourStatut(
                "data/ordres.csv", "EXECUTE"
            );

            sellOrders[j].mettreAJourStatut(
                "data/ordres.csv", "EXECUTE"
            );

            std::ofstream log(
                "data/historique_evenements.csv",
                std::ios::app
            );

            log << std::time(nullptr)
                << ",TRANSACTION,"
                << transaction_id
                << ",Execution ordre,"
                << "2026-01-01\n";

            buyOrders.erase(buyOrders.begin() + i);
            sellOrders.erase(sellOrders.begin() + j);

            return;
        }
    }
}

void MatchingEngine::updateCompteSolde(
        long long compte_id,
        double montant,
        bool debit)
{
    std::ifstream in("data/comptes.csv");
    std::vector<std::string> lignes;
    std::string ligne;

    while (std::getline(in, ligne)) {

        std::stringstream ss(ligne);
        std::string token;
        std::getline(ss, token, ',');
        long long id = std::stoll(token);

        std::vector<std::string> fields;
        std::stringstream ss2(ligne);
        std::string field;

        while (std::getline(ss2, field, ','))
            fields.push_back(field);

        if (id == compte_id) {

            double solde = std::stod(fields[3]);

            if (debit)
                solde -= montant;
            else
                solde += montant;

            fields[3] = std::to_string(solde);

            ligne = fields[0];
            for (size_t i = 1; i < fields.size(); ++i)
                ligne += "," + fields[i];
        }

        lignes.push_back(ligne);
    }

    in.close();

    std::ofstream out("data/comptes.csv", std::ios::trunc);
    for (const auto& l : lignes)
        out << l << "\n";
}