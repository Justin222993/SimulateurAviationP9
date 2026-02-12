#ifndef MENUPRINCIPALE_H
#define MENUPRINCIPALE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QMovie>
#include <QResizeEvent>
#include <iostream>
#include <string>
#include "transitions.h"
#include <QTimer>

class MenuPrincipale : public QWidget {
    Q_OBJECT
public:
    MenuPrincipale(QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    QPushButton* boutonCommencer;
    QPushButton* boutonQuitter;
    QMovie* fondAnimation;
    QLabel* titre;
    QPushButton* creerBouton(std::string message);

signals:
    void demanderSimulation();
};

#endif