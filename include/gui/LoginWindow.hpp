#ifndef LOGINWINDOW_HPP
#define LOGINWINDOW_HPP

#include <QWidget>

class Serveur;
class QLineEdit;
class QPushButton;
class QLabel;

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(Serveur* srv, QWidget *parent = nullptr);

private slots:
    void handleLogin();

private:
    Serveur* serveur;
    QLineEdit* compteEdit;
    QLabel* statusLabel;
};

#endif