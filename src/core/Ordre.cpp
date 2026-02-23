#include "../../include/core/Ordre.hpp"
#include <fstream>
#include <sstream>
#include <vector>

Ordre::Ordre(long long id,
             long long compte,
             long long action,
             TypeOrdre t,
             int q,
             double prix,
             const std::string& date)
    : ordre_id(id),
      compte_id(compte),
      action_id(action),
      type(t),
      quantite(q),
      prix_limite(prix),
      date_creation(date)
{
}

bool Ordre::valider() const {
    return quantite > 0 && prix_limite > 0;
}

long long Ordre::getOrdreId() const { return ordre_id; }
long long Ordre::getCompteId() const { return compte_id; }
long long Ordre::getActionId() const { return action_id; }
int Ordre::getQuantite() const { return quantite; }
double Ordre::getPrix() const { return prix_limite; }
TypeOrdre Ordre::getType() const { return type; }

void Ordre::enregistrerCSV(const std::string& fichier) const {
    std::ofstream out(fichier, std::ios::app);
    out << ordre_id << ","
        << compte_id << ","
        << action_id << ","
        << (type == TypeOrdre::ACHAT ? "ACHAT" : "VENTE") << ","
        << quantite << ","
        << prix_limite << ","
        << date_creation << ",EN_ATTENTE\n";
}

void Ordre::mettreAJourStatut(const std::string& fichier,
                              const std::string& nouveauStatut) const {

    std::ifstream in(fichier);
    std::vector<std::string> lignes;
    std::string ligne;

    while (std::getline(in, ligne)) {

        std::stringstream ss(ligne);
        std::string token;
        std::getline(ss, token, ',');
        long long id = std::stoll(token);

        if (id == ordre_id) {
            std::vector<std::string> fields;
            std::stringstream ss2(ligne);
            std::string field;
            while (std::getline(ss2, field, ','))
                fields.push_back(field);

            fields[7] = nouveauStatut;

            ligne = fields[0];
            for (size_t i = 1; i < fields.size(); ++i)
                ligne += "," + fields[i];
        }

        lignes.push_back(ligne);
    }

    in.close();

    std::ofstream out(fichier, std::ios::trunc);
    for (const auto& l : lignes)
        out << l << "\n";
}