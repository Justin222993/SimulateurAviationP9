#ifndef GESTIONNAIRESCENES_H
#define GESTIONNAIRESCENES_H

#include <QStackedWidget>
#include "menuPrincipale.h"
#include "simulation.h"
#include "simulationCockpit.h"
#include "comptePilote.h"

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
    void afficherComptePilote();

private:
    QWidget* m_container;
    QStackedWidget* m_stack;

    // scenes
    MenuPrincipale* m_menu;
    Simulation* m_simulationVol;
    SimulationCockpit* m_simulationCockpit;
    ComptePilote* m_comptePilote;

    Pilote* m_piloteActif;

protected:
    void resizeEvent(QResizeEvent* event) override;
};

#endif