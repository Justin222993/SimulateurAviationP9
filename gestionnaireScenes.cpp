#include "gestionnaireScenes.h"

GestionnaireScenes::GestionnaireScenes(QWidget* parent) : QStackedWidget(parent)
{
    // Background noir derrière les images
    this->setStyleSheet("background-color: black;");

    // taille de base en pixels
    this->resize(800, 600);

    // Taille minimale
    this->setMinimumSize(800, 600);

    // On garde les boutons standards (réduire, agrandir/plein écran, fermer)
    this->setWindowFlags(Qt::Window | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);

    // Initialisation des scènes
    m_menu = new MenuPrincipale();
    m_simulation = new Simulation();

    // Ajout à la pile
    this->addWidget(m_menu);
    this->addWidget(m_simulation);

    // On écoute le signal du menu pour changer de scène
    connect(m_menu, &MenuPrincipale::demanderSimulation, this, &GestionnaireScenes::afficherSimulation);
}

void GestionnaireScenes::afficherMenu()
{
    this->setCurrentWidget(m_menu);
}

void GestionnaireScenes::afficherSimulation()
{
    this->setCurrentWidget(m_simulation);
}

// Pour changer de scène:

// 1. Créer un bouton/action qui va trigger la scène

// 2. Écoute pour l'appel d'une fonction, ex: connect(m_menu, &MenuPrincipale::demanderSimulation, this, &GestionnaireScenes::afficherSimulation);

// 3. Rajoute le dans les signals du .h ex: signals:
//                                              void demanderSimulation();

// 4. Ensuite tu peut le connecter a un bouton ou juste appeler le emit sous l'action. ex:
//  connect(boutonCommencer, &QPushButton::clicked, this, [this]() {
//      emit demanderSimulation();
//  });