#include "../../include/user/Client.hpp"
#include "../../include/core/Ordre.hpp"
#include <ctime>

Client::Client(long long id, Serveur* s)
    : client_id(id), serveur(s)
{
}

void Client::envoyerOrdre(long long compte_id,
                          long long action_id,
                          TypeOrdre type,
                          int quantite,
                          double prix)
{
    long long ordre_id = std::time(nullptr);

    Ordre ordre(ordre_id,
                compte_id,
                action_id,
                type,
                quantite,
                prix,
                "2026-01-01");

    if (ordre.valider()) {
        serveur->recevoirOrdre(ordre);
    }
}