#include "gui/LoginWindow.hpp"
#include "gui/DashboardWindow.hpp"
#include "system/Serveur.hpp"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QTextStream>

#include <fstream>
#include <sstream>

LoginWindow::LoginWindow(Serveur* srv, QWidget *parent)
    : QWidget(parent), serveur(srv)
{
    setWindowTitle("Serveur Boursier - Login");
    setFixedSize(400, 220);

    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* title = new QLabel("Enter Compte ID");
    compteEdit = new QLineEdit;
    compteEdit->setPlaceholderText("Compte ID");

    QPushButton* loginBtn = new QPushButton("Login");
    statusLabel = new QLabel;

    layout->addWidget(title);
    layout->addWidget(compteEdit);
    layout->addWidget(loginBtn);
    layout->addWidget(statusLabel);

    setStyleSheet(
        "QWidget{background-color:#0d0d0d;color:#00ff88;}"
        "QLineEdit{background:#1a1a1a;color:#00ff88;border:1px solid #00ff88;padding:6px;}"
        "QPushButton{background:#002200;color:#00ff88;border:1px solid #00ff88;padding:6px;}"
        "QPushButton:hover{background:#004400;}"
    );

    connect(loginBtn, &QPushButton::clicked, this, &LoginWindow::handleLogin);
}

void LoginWindow::handleLogin()
{
    long long compteId = compteEdit->text().toLongLong();

    if(compteId == 0)
    {
        statusLabel->setText("Invalid Compte ID");
        return;
    }

    std::ifstream in("data/comptes.csv");
    std::string line;
    bool found = false;

    while(std::getline(in,line))
    {
        std::stringstream ss(line);
        std::string token;
        std::getline(ss,token,',');

        if(std::stoll(token) == compteId)
        {
            found = true;
            break;
        }
    }

    if(!found)
    {
        statusLabel->setText("Compte not found");
        return;
    }

    DashboardWindow* dashboard =
        new DashboardWindow(compteId, serveur);

    dashboard->resize(1200,700);
    dashboard->show();

    this->close();
}