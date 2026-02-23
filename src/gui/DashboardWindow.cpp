#include "gui/DashboardWindow.hpp"
#include "system/Serveur.hpp"
#include "user/Client.hpp"
#include "user/Portefeuille.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QScrollArea>
#include <QDateTime>

#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>

DashboardWindow::DashboardWindow(long long compteId,
                                 Serveur* serveur,
                                 QWidget *parent)
    : QMainWindow(parent),
      compte_id(compteId),
      serveur_ptr(serveur)
{
    QWidget* central = new QWidget;
    setCentralWidget(central);

    QVBoxLayout* mainLayout = new QVBoxLayout(central);

    QHBoxLayout* topLayout = new QHBoxLayout;

    QLabel* accountLabel = new QLabel("Compte: " + QString::number(compte_id));
    budgetLabel = new QLabel;
    marketLabel = new QLabel;

    topLayout->addWidget(accountLabel);
    topLayout->addStretch();
    topLayout->addWidget(budgetLabel);
    topLayout->addStretch();
    topLayout->addWidget(marketLabel);

    mainLayout->addLayout(topLayout);

    QHBoxLayout* middleLayout = new QHBoxLayout;

    QGroupBox* orderBox = new QGroupBox("New Order");
    QVBoxLayout* orderLayout = new QVBoxLayout;

    stockInput = new QLineEdit;
    stockInput->setPlaceholderText("Stock ID");

    quantityInput = new QLineEdit;
    quantityInput->setPlaceholderText("Quantity");

    priceInput = new QLineEdit;
    priceInput->setPlaceholderText("Price");

    buyButton = new QPushButton("BUY");
    sellButton = new QPushButton("SELL");

    statusLabel = new QLabel;

    orderLayout->addWidget(stockInput);
    orderLayout->addWidget(quantityInput);
    orderLayout->addWidget(priceInput);
    orderLayout->addWidget(buyButton);
    orderLayout->addWidget(sellButton);
    orderLayout->addWidget(statusLabel);

    orderBox->setLayout(orderLayout);

    QGroupBox* visualizationBox = new QGroupBox("Market Visualization");
    QVBoxLayout* vizLayout = new QVBoxLayout;
    vizLayout->addWidget(new QLabel("Live price trend"));
    visualizationBox->setLayout(vizLayout);

    QGroupBox* priceBox = new QGroupBox("Live Prices");
    QVBoxLayout* priceLayout = new QVBoxLayout;

    priceTable = new QTableWidget;
    priceTable->setColumnCount(4);
    priceTable->setHorizontalHeaderLabels({"ID","Stock","Price","Date"});
    priceTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    priceTable->setShowGrid(false);
    priceTable->setFrameShape(QFrame::NoFrame);

    priceLayout->addWidget(priceTable);
    priceBox->setLayout(priceLayout);

    middleLayout->addWidget(orderBox);
    middleLayout->addWidget(visualizationBox);
    middleLayout->addWidget(priceBox);

    mainLayout->addLayout(middleLayout);

    QGroupBox* portfolioBox = new QGroupBox("Last 5 Traded Stocks");
    QVBoxLayout* portWrapper = new QVBoxLayout;

    QScrollArea* scroll = new QScrollArea;
    QWidget* portfolioContainer = new QWidget;
    portfolioLayout = new QHBoxLayout;
    portfolioContainer->setLayout(portfolioLayout);

    scroll->setWidget(portfolioContainer);
    scroll->setWidgetResizable(true);

    portWrapper->addWidget(scroll);
    portfolioBox->setLayout(portWrapper);

    mainLayout->addWidget(portfolioBox);

    connect(buyButton, &QPushButton::clicked, this, &DashboardWindow::sendOrder);
    connect(sellButton, &QPushButton::clicked, this, &DashboardWindow::sendOrder);
    connect(stockInput, &QLineEdit::textChanged, this, &DashboardWindow::refreshPrices);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DashboardWindow::updateClock);
    timer->start(1000);

    applyTheme();
    updateBudget();
    refreshPrices();
    refreshPortfolio();
}

void DashboardWindow::applyTheme()
{
    setStyleSheet(
        "QMainWindow{background-color:#0d0d0d;color:#00ff88;}"
        "QGroupBox{border:1px solid #00ff88;margin-top:10px;}"
        "QLabel{color:#00ff88;}"
        "QLineEdit{background:#1a1a1a;color:#00ff88;border:1px solid #00ff88;padding:6px;}"
        "QPushButton{background:#002200;color:#00ff88;border:1px solid #00ff88;padding:6px;}"
        "QPushButton:hover{background:#004400;}"
        "QTableWidget{background:#111;color:#00ff88;border:none;}"
        "QHeaderView::section{background:#003300;color:#00ff88;border:none;}"
    );
}

void DashboardWindow::updateBudget()
{
    std::ifstream in("data/comptes.csv");
    std::string line;

    while(std::getline(in,line))
    {
        std::stringstream ss(line);
        std::string token;
        std::getline(ss,token,',');

        if(std::stoll(token)==compte_id)
        {
            std::vector<std::string> fields;
            std::stringstream ss2(line);
            while(std::getline(ss2,token,','))
                fields.push_back(token);

            budgetLabel->setText("Solde: " + QString::fromStdString(fields[3]));
            break;
        }
    }
}

void DashboardWindow::refreshPrices()
{
    priceTable->setRowCount(0);

    if(stockInput->text().isEmpty())
        return;

    long long stockId = stockInput->text().toLongLong();

    std::ifstream in("data/cours_actions.csv");
    std::string line;
    std::vector<std::vector<QString>> rows;

    while(std::getline(in,line))
    {
        std::stringstream ss(line);
        std::string token;
        std::vector<QString> fields;

        while(std::getline(ss,token,','))
            fields.push_back(QString::fromStdString(token));

        if(fields.size()>=4 && fields[1].toLongLong()==stockId)
            rows.push_back(fields);
    }

    int start = std::max(0, (int)rows.size()-20);

    for(int i=start;i<rows.size();++i)
    {
        int r = priceTable->rowCount();
        priceTable->insertRow(r);
        for(int c=0;c<4;c++)
            priceTable->setItem(r,c,new QTableWidgetItem(rows[i][c]));
    }
}

void DashboardWindow::refreshPortfolio()
{
    QLayoutItem* item;
    while((item = portfolioLayout->takeAt(0)))
    {
        delete item->widget();
        delete item;
    }

    std::ifstream transFile("data/transactions.csv");
    std::string line;

    std::vector<std::vector<std::string>> transactions;

    while(std::getline(transFile,line))
    {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> fields;

        while(std::getline(ss,token,','))
            fields.push_back(token);

        if(fields.size() >= 7)
            transactions.push_back(fields);
    }

    std::reverse(transactions.begin(), transactions.end());

    std::set<long long> usedStocks;
    int displayed = 0;

    for(auto& t : transactions)
    {
        long long actionId = std::stoll(t[3]);
        std::string price = t[4];
        std::string date  = t[6];

        if(usedStocks.count(actionId))
            continue;

        usedStocks.insert(actionId);

        QTableWidget* table = new QTableWidget(1,4);
        table->setHorizontalHeaderLabels(
            {"Stock","Last Price","Last Trade","Quantity"}
        );

        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        table->setShowGrid(false);
        table->setFrameShape(QFrame::NoFrame);

        Portefeuille pf(compte_id);
        int quantity = pf.getQuantite(actionId);

        table->setItem(0,0,new QTableWidgetItem(QString::number(actionId)));
        table->setItem(0,1,new QTableWidgetItem(QString::fromStdString(price)));
        table->setItem(0,2,new QTableWidgetItem(QString::fromStdString(date)));
        table->setItem(0,3,new QTableWidgetItem(QString::number(quantity)));

        portfolioLayout->addWidget(table);

        displayed++;
        if(displayed>=5)
            break;
    }

    portfolioLayout->addStretch();
}

void DashboardWindow::updateClock()
{
    marketLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

void DashboardWindow::sendOrder()
{
    long long actionId = stockInput->text().toLongLong();
    int quantity = quantityInput->text().toInt();
    double price = priceInput->text().toDouble();

    if(actionId==0 || quantity<=0 || price<=0)
    {
        statusLabel->setText("Invalid order");
        return;
    }

    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    TypeOrdre type = (btn==buyButton) ? TypeOrdre::ACHAT : TypeOrdre::VENTE;

    Client client(1, serveur_ptr);
    client.envoyerOrdre(compte_id, actionId, type, quantity, price);

    statusLabel->setText(type==TypeOrdre::ACHAT ? "BUY executed" : "SELL executed");

    updateBudget();
    refreshPrices();
    refreshPortfolio();
}