#ifndef GESTIONNAIRESCENES_H
#define GESTIONNAIRESCENES_H

#include <QStackedWidget>
#include "menuPrincipale.h"
#include "Simulation.h"

class GestionnaireScenes : public QStackedWidget
{
    Q_OBJECT

public:
    GestionnaireScenes(QWidget* parent = nullptr);

private slots:
    // Fonctions pour changer de vue
    void afficherSimulation();
    void afficherMenu();

private:
    MenuPrincipale* m_menu;
    Simulation* m_simulation;
};

#endif