#ifndef PORTEFEUILLE_HPP
#define PORTEFEUILLE_HPP

#include <string>

class Portefeuille {

private:
    long long compte_id;

public:
    Portefeuille(long long compte);

    int getQuantite(long long action_id) const;

    bool aAssez(long long action_id, int quantite) const;

    bool retirerAction(long long action_id, int quantite);

    void ajouterAction(long long action_id, int quantite);

    bool peutDebiter(double montant) const;
};

#endif