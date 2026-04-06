#ifndef GESTIONNAIRESCENES_H
#define GESTIONNAIRESCENES_H

#include <QStackedWidget>
#include "menuPrincipale.h"
#include "simulation.h"
#include "simulationCockpit.h"

class GestionnaireScenes : public QStackedWidget
{
    Q_OBJECT

public:
    GestionnaireScenes(QWidget* parent = nullptr);

private slots:
    // Fonctions pour changer de vue
    void afficherSimulationVol();
    void afficherSimulationCockpit();
    void afficherMenu();

private:
    MenuPrincipale* m_menu;
    Simulation* m_simulationVol;
    SimulationCockpit* m_simulationCockpit;
};

#endif