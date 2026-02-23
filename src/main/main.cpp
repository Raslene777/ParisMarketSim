#include <QApplication>
#include "gui/LoginWindow.hpp"
#include "system/Serveur.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Serveur serveur;

    LoginWindow login(&serveur);
    login.show();

    return app.exec();
}