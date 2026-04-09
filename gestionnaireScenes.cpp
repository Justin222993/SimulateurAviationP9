#include "gestionnaireScenes.h"

GestionnaireScenes::GestionnaireScenes(QWidget* parent)
    : QStackedWidget(parent)
{
    this->setStyleSheet("background-color: black;");

    m_container = new QWidget(this);
    m_container->setStyleSheet("background-color: black;");

    m_stack = new QStackedWidget(m_container);

    // Initialisation des scènes
    m_menu = new MenuPrincipale();
    m_simulationVol = new Simulation();
    m_simulationCockpit = new SimulationCockpit();

    // Ajout à la pile
    m_stack->addWidget(m_menu);
    m_stack->addWidget(m_simulationVol);
    m_stack->addWidget(m_simulationCockpit);

    this->resize(800, 450);

    this->setMinimumSize(800, 450);
    this->setMaximumSize(1920, 1080);

    this->setWindowFlags(Qt::Window | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);

    // On écoute le signal du menu pour changer de scène
    connect(m_menu, &MenuPrincipale::demanderSimulationVol,
        this, &GestionnaireScenes::afficherSimulationVol);

    connect(m_menu, &MenuPrincipale::demanderSimulationCockpit,
        this, &GestionnaireScenes::afficherSimulationCockpit);
}

void GestionnaireScenes::afficherMenu()
{
    m_stack->setCurrentWidget(m_menu);
}

void GestionnaireScenes::afficherSimulationVol()
{
    m_stack->setCurrentWidget(m_simulationVol);
    m_simulationVol->demarrer();
}

void GestionnaireScenes::afficherSimulationCockpit()
{
    m_stack->setCurrentWidget(m_simulationCockpit);
    m_simulationCockpit->demarrer();
}

// Pour garder le ratio 16/9 de l'ecran, mais des bordures autour du container si la size match pas
void GestionnaireScenes::resizeEvent(QResizeEvent* event)
{
    QSize s = event->size();

    const float targetRatio = 16.0f / 9.0f;

    int w = s.width();
    int h = s.height();

    int newW, newH;

    if ((float)w / h > targetRatio) {

        newW = h * targetRatio;
        newH = h;
    }
    else {

        newW = w;
        newH = w / targetRatio;
    }

    int x = (w - newW) / 2;
    int y = (h - newH) / 2;

    m_container->setGeometry(x, y, newW, newH);

    m_stack->setGeometry(0, 0, newW, newH);

    QStackedWidget::resizeEvent(event);
}