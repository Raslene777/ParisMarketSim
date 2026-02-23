#ifndef ORDRE_HPP
#define ORDRE_HPP

#include <string>

enum class TypeOrdre {
    ACHAT,
    VENTE
};

class Ordre {
private:
    long long ordre_id;
    long long compte_id;
    long long action_id;
    TypeOrdre type;
    int quantite;
    double prix_limite;
    std::string date_creation;

public:
    Ordre(long long id,
           long long compte,
           long long action,
           TypeOrdre t,
           int q,
           double prix,
           const std::string& date);

    bool valider() const;

    void enregistrerCSV(const std::string& fichier) const;
    void mettreAJourStatut(const std::string& fichier,
                           const std::string& nouveauStatut) const;

    long long getOrdreId() const;
    long long getCompteId() const;
    long long getActionId() const;
    int getQuantite() const;
    double getPrix() const;
    TypeOrdre getType() const;
};

#endif