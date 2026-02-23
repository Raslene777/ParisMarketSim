#include "../../include/system/Interface.hpp"
#include "../../include/user/Client.hpp"
#include <iostream>

Interface::Interface() {
}

void Interface::afficherMenu() const {
    std::cout << "\n===== SERVEUR BOURSIER =====\n";
    std::cout << "1. Envoyer un ordre\n";
    std::cout << "0. Quitter\n";
    std::cout << "Choix: ";
}

void Interface::traiterOrdre() {

    long long client_id;
    long long compte_id;
    long long action_id;
    int type;
    int quantite;
    double prix;

    std::cout << "Client ID: ";
    std::cin >> client_id;

    std::cout << "Compte ID: ";
    std::cin >> compte_id;

    std::cout << "Action ID: ";
    std::cin >> action_id;

    std::cout << "Type (0 = Achat, 1 = Vente): ";
    std::cin >> type;

    std::cout << "Quantite: ";
    std::cin >> quantite;

    std::cout << "Prix limite: ";
    std::cin >> prix;

    Client client(client_id, &serveur);

    client.envoyerOrdre(
        compte_id,
        action_id,
        type == 0 ? TypeOrdre::ACHAT : TypeOrdre::VENTE,
        quantite,
        prix
    );

    std::cout << "Ordre envoye.\n";
}

void Interface::lancer() {

    int choix = -1;

    while (choix != 0) {

        afficherMenu();
        std::cin >> choix;

        if (choix == 1) {
            traiterOrdre();
        }
    }

    std::cout << "Arret du systeme.\n";
}