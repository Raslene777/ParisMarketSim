#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "system/Serveur.hpp"

class Interface {
private:
    Serveur serveur;

    void afficherMenu() const;
    void traiterOrdre();

public:
    Interface();
    void lancer();
};

#endif