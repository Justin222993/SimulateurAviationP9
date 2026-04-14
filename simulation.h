#ifndef SIMULATION_H
#define SIMULATION_H
#include <QWidget>
#include <QLabel>
#include <QList>
#include <QTimer>
#include <QDebug>
#include <QRandomGenerator>
#include <QQuickWidget>
#include <QMetaObject>
#include <QQuickItem>
#include "indicateurComponent.h"
#include "simulationIndicateurs.h"
#include "pilote.h"

class Simulation : public QWidget {
    Q_OBJECT
public:
    Simulation(QWidget* parent = nullptr);
    void demarrer();
    void setPiloteActif(Pilote* p);
    void terminerVol(bool estMort, const QString& typeVol);
protected:
    void resizeEvent(QResizeEvent* event) override;
private:
    SimulationIndicateurs sim;
    QLabel* instruments[SimulationIndicateurs::NB_INSTRUMENTS];
    QList<IndicateurComponent*> listeIndicateurs[SimulationIndicateurs::NB_INSTRUMENTS];
    QTimer* timerAnimation;
    QTimer* timerDonnees;
    QQuickWidget* view3d;
    Pilote* m_piloteActif;
    QSet<QString> m_typesWarnings;
    double m_altitudeMax;
    double m_speedMax;
    void setupIndicateurs();
    void messagesWarning();
    void messagesMorts();
signals:
    void demanderRetourMenu();
};
#endif