#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>

class Transaction {
private:
    long long transaction_id;
    long long ordre_achat_id;
    long long ordre_vente_id;
    long long action_id;
    double prix_execution;
    int quantite;
    std::string date_heure;

public:
    Transaction(long long id,
                long long ordreAchat,
                long long ordreVente,
                long long action,
                double prix,
                int qte,
                const std::string& date);

    long long getTransactionId() const;
    long long getOrdreAchatId() const;
    long long getOrdreVenteId() const;
    long long getActionId() const;
    double getPrixExecution() const;
    int getQuantite() const;
    std::string getDateHeure() const;

    void enregistrerCSV(const std::string& fichier) const;
};

#endif