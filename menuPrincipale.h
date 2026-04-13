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
    void setPiloteActif(const QString& nom);
protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    QPushButton* boutonCommencerVol;
    QPushButton* boutonCommencerCockpit;
    QPushButton* boutonQuitter;
    QPushButton* boutonComptePilote;
    QLabel* labelPiloteActif;
    QMovie* fondAnimation;
    QLabel* titre;
    QPushButton* creerBouton(std::string message);

signals:
    void demanderSimulationVol();
    void demanderSimulationCockpit();
    void demanderComptePilote();
};

#endif