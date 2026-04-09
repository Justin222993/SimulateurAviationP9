#ifndef SIMULATIONCOCKPIT_H
#define SIMULATIONCOCKPIT_H

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
#include <QQuickWidget>
#include <QMetaObject>
#include <QQuickItem>
#include "indicateurComponent.h"
#include "simulationIndicateurs.h"

class SimulationCockpit : public QWidget {
    Q_OBJECT
public:
    SimulationCockpit(QWidget* parent = nullptr);
    void demarrer();

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    SimulationIndicateurs sim;

    QLabel* instruments[SimulationIndicateurs::NB_INSTRUMENTS];
    QLabel* ecranText;
    QList<IndicateurComponent*> listeIndicateurs[SimulationIndicateurs::NB_INSTRUMENTS];

    QTimer* timerAnimation;
    QTimer* timerDonnees;

    QQuickWidget* view3d;

    void setupIndicateurs();
    void messagesWarning();
    void messagesMorts();
};

#endif