#ifndef SIMULATION_H
#define SIMULATION_H

#include <QWidget>
#include <QLabel>
#include <QList>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QRandomGenerator>
#include <iostream>
#include <thread>
#include <conio.h>
#include <iomanip>
#include "indicateurComponent.h"
#include "avion.h"

class Simulation : public QWidget {
    Q_OBJECT

public:
    // L'ordre ici doit correspondre strictement à l'ordre de nomsBase dans le .cpp
    enum TypeInstrument {
        Anemometre,
        Horizon,
        Altimetre,
        Tachymetre,
        Virage,
        Cap,
        Variometre,
        Boussole,
        NB_INSTRUMENTS
    };

    inline static const QStringList NOMS_IMAGES = {
        "anemometre", "horizon-artificiel", "altimetre", "tachymetre",
        "coordonateur-de-virage", "indicateur-de-cap", "variometre", "boussole"
    };

    explicit Simulation(QWidget* parent = nullptr);
    void setAngleInstrument(int indexInstrument, int indexIndicateur, double angle);
    void setPosition(int indexInstrument, int indexIndicateur, double positionX, double positionY);
    void demarrer();

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    QLabel* fondDashboard;
    QLabel* instruments[NB_INSTRUMENTS];
    QList<IndicateurComponent*> listeIndicateurs[NB_INSTRUMENTS];
    void inputListener(Avion& p);
    Avion p;
    QTimer* timerAnimation;
    QTimer* timerDonnees;
    void setupIndicateurs();
    void messagesWarning();
    void handleAnemometre();
};

#endif