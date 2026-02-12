#include "simulation.h"

Simulation::Simulation(QWidget* parent) : QWidget(parent) {
    QLabel* label = new QLabel("SCENE DE SIMULATION EN COURS...", this);
    label->setGeometry(300, 250, 300, 50);
}