#include "../../include/core/Transaction.hpp"
#include <fstream>

Transaction::Transaction(long long id,
                         long long ordreAchat,
                         long long ordreVente,
                         long long action,
                         double prix,
                         int qte,
                         const std::string& date)
    : transaction_id(id),
      ordre_achat_id(ordreAchat),
      ordre_vente_id(ordreVente),
      action_id(action),
      prix_execution(prix),
      quantite(qte),
      date_heure(date)
{
}

long long Transaction::getTransactionId() const {
    return transaction_id;
}

long long Transaction::getOrdreAchatId() const {
    return ordre_achat_id;
}

long long Transaction::getOrdreVenteId() const {
    return ordre_vente_id;
}

long long Transaction::getActionId() const {
    return action_id;
}

double Transaction::getPrixExecution() const {
    return prix_execution;
}

int Transaction::getQuantite() const {
    return quantite;
}

std::string Transaction::getDateHeure() const {
    return date_heure;
}

void Transaction::enregistrerCSV(const std::string& fichier) const {
    std::ofstream out(fichier, std::ios::app);
    out << transaction_id << ","
        << ordre_achat_id << ","
        << ordre_vente_id << ","
        << action_id << ","
        << prix_execution << ","
        << quantite << ","
        << date_heure << "\n";
}