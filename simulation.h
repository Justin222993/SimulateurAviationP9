#ifndef SIMULATION_H
#define SIMULATION_H

#include <QWidget>
#include <QLabel>

class Simulation : public QWidget {
    Q_OBJECT
public:
    Simulation(QWidget* parent = nullptr);
};
#endif