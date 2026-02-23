#include "../../include/system/Serveur.hpp"
#include "../../include/engine/MatchingEngine.hpp"

MatchingEngine engine;

Serveur::Serveur() {
}

void Serveur::recevoirOrdre(const Ordre& ordre) {

    ordre.enregistrerCSV("../../data/ordres.csv");

    engine.ajouterOrdre(ordre);
}