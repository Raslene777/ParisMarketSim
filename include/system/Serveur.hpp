#ifndef SERVEUR_HPP
#define SERVEUR_HPP

#include "core/Ordre.hpp"

class Serveur {
public:
    Serveur();
    void recevoirOrdre(const Ordre& ordre);
};

#endif