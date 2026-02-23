#include "user/Portefeuille.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <filesystem>

namespace fs = std::filesystem;

static std::string dataPath(const std::string& file)
{
    fs::path p = fs::current_path();

    if (p.filename() == "cmake-build-debug")
        p = p.parent_path();

    p /= "data";
    p /= file;

    return p.string();
}

Portefeuille::Portefeuille(long long compte)
    : compte_id(compte)
{
}

int Portefeuille::getQuantite(long long action_id) const {

    std::ifstream in(dataPath("portefeuilles.csv"));
    std::string ligne;

    while (std::getline(in, ligne)) {

        std::stringstream ss(ligne);
        std::string token;

        std::getline(ss, token, ',');
        std::getline(ss, token, ',');
        long long compte = std::stoll(token);

        std::getline(ss, token, ',');
        long long action = std::stoll(token);

        std::getline(ss, token, ',');
        int quantite = std::stoi(token);

        if (compte == compte_id && action == action_id)
            return quantite;
    }

    return 0;
}

bool Portefeuille::aAssez(long long action_id, int quantite) const {
    return getQuantite(action_id) >= quantite;
}

bool Portefeuille::retirerAction(long long action_id, int quantite) {

    std::ifstream in(dataPath("portefeuilles.csv"));
    std::vector<std::string> lignes;
    std::string ligne;
    bool modified = false;

    while (std::getline(in, ligne)) {

        std::stringstream ss(ligne);
        std::string token;

        std::getline(ss, token, ',');
        std::string portefeuille_id = token;

        std::getline(ss, token, ',');
        long long compte = std::stoll(token);

        std::getline(ss, token, ',');
        long long action = std::stoll(token);

        std::getline(ss, token, ',');
        int q = std::stoi(token);

        if (compte == compte_id && action == action_id) {

            if (q < quantite)
                return false;

            q -= quantite;

            ligne = portefeuille_id + "," +
                    std::to_string(compte) + "," +
                    std::to_string(action) + "," +
                    std::to_string(q);

            modified = true;
        }

        lignes.push_back(ligne);
    }

    in.close();

    if (!modified)
        return false;

    std::ofstream out(dataPath("portefeuilles.csv"), std::ios::trunc);
    for (const auto& l : lignes)
        out << l << "\n";

    return true;
}

void Portefeuille::ajouterAction(long long action_id, int quantite) {

    std::ifstream in(dataPath("portefeuilles.csv"));
    std::vector<std::string> lignes;
    std::string ligne;
    bool found = false;

    while (std::getline(in, ligne)) {

        std::stringstream ss(ligne);
        std::string token;

        std::getline(ss, token, ',');
        std::string portefeuille_id = token;

        std::getline(ss, token, ',');
        long long compte = std::stoll(token);

        std::getline(ss, token, ',');
        long long action = std::stoll(token);

        std::getline(ss, token, ',');
        int q = std::stoi(token);

        if (compte == compte_id && action == action_id) {

            q += quantite;

            ligne = portefeuille_id + "," +
                    std::to_string(compte) + "," +
                    std::to_string(action) + "," +
                    std::to_string(q);

            found = true;
        }

        lignes.push_back(ligne);
    }

    in.close();

    if (!found) {
        long long new_id = static_cast<long long>(std::time(nullptr));

        lignes.push_back(
            std::to_string(new_id) + "," +
            std::to_string(compte_id) + "," +
            std::to_string(action_id) + "," +
            std::to_string(quantite)
        );
    }

    std::ofstream out(dataPath("portefeuilles.csv"), std::ios::trunc);
    for (const auto& l : lignes)
        out << l << "\n";
}

bool Portefeuille::peutDebiter(double montant) const {

    std::ifstream in(dataPath("comptes.csv"));
    std::string ligne;

    while (std::getline(in, ligne)) {

        std::stringstream ss(ligne);
        std::string token;

        std::getline(ss, token, ',');
        long long id = std::stoll(token);

        if (id == compte_id) {

            std::vector<std::string> fields;
            std::stringstream ss2(ligne);
            std::string field;

            while (std::getline(ss2, field, ','))
                fields.push_back(field);

            double solde = std::stod(fields[3]);
            return solde >= montant;
        }
    }

    return false;
}