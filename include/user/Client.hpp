#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include "system/Serveur.hpp"

class Client {
private:
    long long client_id;
    Serveur* serveur;

public:
    Client(long long id, Serveur* s);

    void envoyerOrdre(long long compte_id,
                      long long action_id,
                      TypeOrdre type,
                      int quantite,
                      double prix);
};

#endif