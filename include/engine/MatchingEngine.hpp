#ifndef MATCHINGENGINE_HPP
#define MATCHINGENGINE_HPP

#include <vector>
#include "core/Ordre.hpp"

class MatchingEngine {
private:
    std::vector<Ordre> buyOrders;
    std::vector<Ordre> sellOrders;

    void executerMatch();
    void updateCompteSolde(long long compte_id,
                           double montant,
                           bool debit);

public:
    MatchingEngine();
    void ajouterOrdre(const Ordre& ordre);
};

#endif