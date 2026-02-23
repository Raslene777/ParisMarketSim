#ifndef DASHBOARDWINDOW_HPP
#define DASHBOARDWINDOW_HPP

#include <QMainWindow>
#include <QTimer>

class Serveur;
class QLabel;
class QLineEdit;
class QPushButton;
class QTableWidget;
class QHBoxLayout;

class DashboardWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DashboardWindow(long long compteId,
                             Serveur* serveur,
                             QWidget *parent = nullptr);

private slots:
    void sendOrder();
    void refreshPrices();
    void refreshPortfolio();
    void updateClock();

private:
    void applyTheme();
    void updateBudget();

    long long compte_id;
    Serveur* serveur_ptr;

    QLabel* budgetLabel;
    QLabel* marketLabel;
    QLabel* statusLabel;

    QLineEdit* stockInput;
    QLineEdit* quantityInput;
    QLineEdit* priceInput;

    QPushButton* buyButton;
    QPushButton* sellButton;

    QTableWidget* priceTable;
    QHBoxLayout* portfolioLayout;

    QTimer* timer;
};

#endif