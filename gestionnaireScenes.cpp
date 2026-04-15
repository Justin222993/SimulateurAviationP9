#include "gestionnaireScenes.h"

GestionnaireScenes::GestionnaireScenes(QWidget* parent)
    : QStackedWidget(parent)
{
    this->setStyleSheet("background-color: black;");

    m_container = new QWidget(this);
    m_container->setStyleSheet("background-color: black;");

    m_stack = new QStackedWidget(m_container);

    // Initialisation des scènes, appel le constructor de chacun
    m_menu = new MenuPrincipale();
    m_simulationVol = new Simulation();
    m_simulationCockpit = new SimulationCockpit();
    m_comptePilote = new ComptePilote();

    // Ajout à la pile de pages
    m_stack->addWidget(m_menu);
    m_stack->addWidget(m_simulationVol);
    m_stack->addWidget(m_simulationCockpit);
    m_stack->addWidget(m_comptePilote);

    // size suivant le ratio 16/9
    this->resize(1000, 562);
    this->setMinimumSize(1000, 562);

    this->setWindowFlags(Qt::Window | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);

    // On écoute le signal du menu pour changer de scène avec les clicks de boutons
    connect(m_menu, &MenuPrincipale::demanderSimulationVol,
        this, &GestionnaireScenes::afficherSimulationVol);

    connect(m_menu, &MenuPrincipale::demanderSimulationCockpit,
        this, &GestionnaireScenes::afficherSimulationCockpit);

    connect(m_menu, &MenuPrincipale::demanderComptePilote,
        this, &GestionnaireScenes::afficherComptePilote);

    connect(m_comptePilote, &ComptePilote::demanderRetourMenu,
        this, &GestionnaireScenes::afficherMenu);

    connect(m_menu, &MenuPrincipale::demanderComptePilote,
        this, &GestionnaireScenes::afficherComptePilote);

    m_piloteActif = nullptr;

    // Connection des signaux de la page de compte
    connect(m_comptePilote, &ComptePilote::piloteChoisi, this, [this](Pilote* p) {
        m_piloteActif = p;
        std::cout << "Pilote actif: " << p->getNom().toStdString() << std::endl;
        });

    connect(m_comptePilote, &ComptePilote::piloteChoisi, this, [this](Pilote* p) {
        m_piloteActif = p;
        m_simulationVol->setPiloteActif(p);
        m_simulationCockpit->setPiloteActif(p);
        });

    connect(m_comptePilote, &ComptePilote::demanderRetourMenu,
        this, &GestionnaireScenes::afficherMenu);

    connect(m_comptePilote, &ComptePilote::piloteChoisi, this, [this](Pilote* p) {
        m_piloteActif = p;
        m_simulationVol->setPiloteActif(p);
        m_simulationCockpit->setPiloteActif(p);
        m_menu->setPiloteActif(p->getNom());
        });

    // Connection des signaux de la simulation en ville
    connect(m_simulationVol, &Simulation::demanderRetourMenu, this, [this]() {
        afficherMenu();
        });

    // Connection des signaux de la simulation cockpit
    connect(m_simulationCockpit, &SimulationCockpit::demanderRetourMenu, this, [this]() {
        afficherMenu();
        });
}

// Montre le menu
void GestionnaireScenes::afficherMenu()
{
    m_stack->setCurrentWidget(m_menu);
}

// Montre la ville et commence la simulation
void GestionnaireScenes::afficherSimulationVol()
{
    m_stack->setCurrentWidget(m_simulationVol);
    m_simulationVol->demarrer();
}

// Montre le cockpit et commence la simulation
void GestionnaireScenes::afficherSimulationCockpit()
{
    m_stack->setCurrentWidget(m_simulationCockpit);
    m_simulationCockpit->demarrer();
}

// Affiche la page d'ajout et selection du pilote
void GestionnaireScenes::afficherComptePilote()
{
    m_stack->setCurrentWidget(m_comptePilote);
}

// Pour garder le ratio 16/9 de l'ecran, mets des bordures autour du container si la size match pas
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