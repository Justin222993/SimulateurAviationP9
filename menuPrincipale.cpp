#include "menuPrincipale.h"

MenuPrincipale::MenuPrincipale(QWidget* parent) : QWidget(parent)
{
    // Fade-in 3.5s
    Transitions::apparition(this, 3500);

    // Background
    QLabel* fondAnime = new QLabel(this);
    fondAnime->setScaledContents(true);
    fondAnime->setAttribute(Qt::WA_TransparentForMouseEvents);
    fondAnimation = new QMovie("ressources/menuPrincipale/introCockpit.gif");
    fondAnime->setMovie(fondAnimation);

    if (!fondAnimation->isValid()) {
        std::cout << "Attention: GIF introuvable dans ressources/" << std::endl;
    }

    fondAnimation->start();
    fondAnime->lower();


    // Bouttons
    boutonCommencer = creerBouton("Demarrer les moteurs");

    connect(boutonCommencer, &QPushButton::clicked, this, [this]() {
        std::cout << "Lancement de la simulation..." << std::endl;
        emit demanderSimulation();
    });

    boutonQuitter = creerBouton("Quitter le cockpit");

    connect(boutonQuitter, &QPushButton::clicked, this, [this]() {
        std::cout << "Vous avez quitter l'application par le bouton" << std::endl;
        Transitions::disparition(this, 500); // Disparition rapide

        // On ferme l'app après la transition
        QTimer::singleShot(500, []() {
            QCoreApplication::quit();
        });
    });

    // Titre
    titre = new QLabel(this);
    QPixmap pix("ressources/menuPrincipale/aviationTitre.png");
    titre->setPixmap(pix);
    titre->setScaledContents(true);
    titre->raise();
}

void MenuPrincipale::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    // Update du background
    for (auto child : children()) {
        QLabel* lbl = qobject_cast<QLabel*>(child);
        if (lbl && lbl->movie()) {
            lbl->resize(this->size());
        }
    }

    // Boutons
    // Bouton Commencer
    if (boutonCommencer) {
        int btnW = 250;
        int btnH = 50;

        // Position - milieu-droit a 80% du haut
        int x = (this->width() - btnW) / 2 + 150;
        int y = this->height() * 0.8;

        boutonCommencer->setGeometry(x, y, btnW, btnH);
    }

    // Bouton Quitter
    if (boutonQuitter) {
        int btnW = 250;
        int btnH = 50;

        // Position - milieu-gauche a 80% du haut
        int x = (this->width() - btnW) / 2 - 150;
        int y = this->height() * 0.8;

        boutonQuitter->setGeometry(x, y, btnW, btnH);
    }

    // Titre
    if (titre) {
        // Position - milieu a 10% du haut
        int logoW = 400;
        int logoH = 120;

        // Centré horizontalement, placé à 10% du haut
        int logoX = (this->width() - logoW) / 2;
        int logoY = this->height() * 0.1;

        titre->setGeometry(logoX, logoY, logoW, logoH);
    }
}

QPushButton* MenuPrincipale::creerBouton(std::string message) {
    QPushButton* le_bouton = new QPushButton(QString::fromStdString(message), this);

    le_bouton->raise();

    le_bouton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgba(30, 30, 30, 150);"
        "   color: rgba(0, 255, 0, 200);"
        "   border: 1px solid rgba(0, 255, 0, 100);"
        "   border-radius: 2px;"
        "   padding: 10px;"
        "   font-family: 'Consolas', monospace;"
        "   font-size: 16px;"
        "   letter-spacing: 2px;"
        "}"

        "QPushButton:hover {"
        "   background-color: rgba(0, 255, 0, 40);"
        "   border: 1px solid rgba(0, 255, 0, 255);"
        "   color: #00FF00;"
        "}"

        "QPushButton:pressed {"
        "   background-color: rgba(0, 255, 0, 80);"
        "   color: #ffffff;"
        "}"
    );

    return le_bouton;
}