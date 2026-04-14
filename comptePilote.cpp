#include "comptePilote.h"
#include <iostream>

ComptePilote::ComptePilote(QWidget* parent)
    : QWidget(parent)
    , m_piloteSelectionne(nullptr)
    , m_statsVisibles(false)
{
    Transitions::apparition(this, 1000);

    labelTitre = new QLabel("Comptes Pilotes", this);
    labelTitre->setStyleSheet(
        "color: rgba(0, 255, 0, 200);"
        "font-family: 'Consolas', monospace;"
        "font-size: 24px;"
        "letter-spacing: 4px;"
    );
    labelTitre->setAlignment(Qt::AlignCenter);

    labelPiloteActif = new QLabel("Aucun pilote selectionne", this);
    labelPiloteActif->setStyleSheet(
        "color: rgba(0, 200, 0, 150);"
        "font-family: 'Consolas', monospace;"
        "font-size: 14px;"
        "letter-spacing: 2px;"
    );
    labelPiloteActif->setAlignment(Qt::AlignCenter);

    champNom = new QLineEdit(this);
    champNom->setPlaceholderText("Nom du pilote...");
    champNom->setStyleSheet(
        "QLineEdit {"
        "   background-color: rgba(30, 30, 30, 150);"
        "   color: rgba(0, 255, 0, 200);"
        "   border: 1px solid rgba(0, 255, 0, 100);"
        "   border-radius: 2px;"
        "   padding: 8px;"
        "   font-family: 'Consolas', monospace;"
        "   font-size: 14px;"
        "   letter-spacing: 2px;"
        "}"
    );

    listePilotes = new QListWidget(this);
    listePilotes->setStyleSheet(
        "QListWidget {"
        "   background-color: rgba(20, 20, 20, 180);"
        "   color: rgba(0, 255, 0, 200);"
        "   border: 1px solid rgba(0, 255, 0, 100);"
        "   font-family: 'Consolas', monospace;"
        "   font-size: 14px;"
        "   letter-spacing: 2px;"
        "}"
        "QListWidget::item:selected {"
        "   background-color: rgba(0, 255, 0, 60);"
        "   color: #00FF00;"
        "}"
        "QListWidget::item:hover {"
        "   background-color: rgba(0, 255, 0, 30);"
        "}"
    );

    scrollStats = new QScrollArea(this);
    scrollStats->setStyleSheet(
        "QScrollArea {"
        "   background-color: rgba(20, 20, 20, 180);"
        "   border: 1px solid rgba(0, 255, 0, 100);"
        "}"
        "QScrollBar:vertical {"
        "   background: rgba(20, 20, 20, 180);"
        "   width: 8px;"
        "}"
        "QScrollBar::handle:vertical {"
        "   background: rgba(0, 255, 0, 100);"
        "   border-radius: 4px;"
        "}"
    );
    scrollStats->setWidgetResizable(true);
    scrollStats->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollStats->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollStats->hide();

    labelStats = new QLabel();
    labelStats->setStyleSheet(
        "color: rgba(0, 255, 0, 200);"
        "font-family: 'Consolas', monospace;"
        "font-size: 12px;"
        "border: none;"
        "padding: 8px;"
        "background: transparent;"
    );
    labelStats->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    labelStats->setWordWrap(true);
    labelStats->setMinimumWidth(100);
    labelStats->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    labelStats->setTextInteractionFlags(Qt::TextSelectableByMouse);
    scrollStats->setWidget(labelStats);

    boutonFermerStats = new QPushButton("< Retour a la liste", this);
    boutonFermerStats->setStyleSheet(
        "QPushButton {"
        "   background-color: rgba(30, 30, 30, 150);"
        "   color: rgba(0, 255, 0, 200);"
        "   border: 1px solid rgba(0, 255, 0, 100);"
        "   border-radius: 2px;"
        "   padding: 8px;"
        "   font-family: 'Consolas', monospace;"
        "   letter-spacing: 2px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(0, 255, 0, 40);"
        "   border: 1px solid rgba(0, 255, 0, 255);"
        "   color: #00FF00;"
        "}"
    );
    boutonFermerStats->hide();
    connect(boutonFermerStats, &QPushButton::clicked, this, [this]() {
        scrollStats->hide();
        boutonFermerStats->hide();
        m_statsVisibles = false;
        boutonVoirStats->setText("Voir historique de vol");
        });

    boutonAjouter = creerBouton("Ajouter pilote");
    connect(boutonAjouter, &QPushButton::clicked, this, &ComptePilote::ajouterPilote);

    boutonChoisir = creerBouton("Choisir ce pilote");
    connect(boutonChoisir, &QPushButton::clicked, this, &ComptePilote::choisirPilote);

    boutonVoirStats = creerBouton("Voir historique de vol");
    connect(boutonVoirStats, &QPushButton::clicked, this, &ComptePilote::afficherStats);

    boutonRetour = creerBouton("Retour au menu");
    connect(boutonRetour, &QPushButton::clicked, this, [this]() {
        emit demanderRetourMenu();
        });
}

Pilote* ComptePilote::getPiloteSelectionne() const {
    return m_piloteSelectionne;
}

void ComptePilote::ajouterPilote() {
    QString nom = champNom->text().trimmed();
    if (nom.isEmpty()) return;

    Pilote* p = new Pilote(nom);
    m_pilotes.append(p);
    listePilotes->addItem(nom);
    champNom->clear();
}

void ComptePilote::choisirPilote() {
    int index = listePilotes->currentRow();
    if (index < 0 || index >= m_pilotes.size()) return;

    m_piloteSelectionne = m_pilotes[index];
    mettreAJourLabel();
    scrollStats->hide();
    boutonFermerStats->hide();
    m_statsVisibles = false;

    emit piloteChoisi(m_piloteSelectionne);
}

void ComptePilote::mettreAJourLabel() {
    if (m_piloteSelectionne)
        labelPiloteActif->setText("Pilote actif: " + m_piloteSelectionne->getNom());
}

void ComptePilote::afficherStats() {
    int index = listePilotes->currentRow();
    if (index < 0 || index >= m_pilotes.size()) return;
    Pilote* p = m_pilotes[index];

    if (m_statsVisibles) {
        scrollStats->hide();
        boutonFermerStats->hide();
        m_statsVisibles = false;
        boutonVoirStats->setText("Voir historique de vol");
        return;
    }

    labelStats->setText(genererTexteStats(p));
    labelStats->adjustSize();
    scrollStats->verticalScrollBar()->setValue(0);
    scrollStats->show();
    scrollStats->raise();
    boutonFermerStats->show();
    boutonFermerStats->raise();
    m_statsVisibles = true;
    boutonVoirStats->setText("Masquer historique");
}

QString ComptePilote::genererTexteStats(Pilote* p) {
    if (p->getNbVols() == 0)
        return "Aucun vol enregistre pour ce pilote.";

    QString texte = "=== HISTORIQUE DE VOL : " + p->getNom() + " ===\n\n";
    texte += "Nombre de vols : " + QString::number(p->getNbVols()) + "\n";
    texte += "Crashs : " + QString::number(p->getNbMorts()) + "\n";

    QSet<QString> warningsUniques = p->getTypesWarningsUniques();
    if (warningsUniques.isEmpty()) {
        texte += "Warnings : Aucun\n\n";
    }
    else {
        texte += "Warnings rencontres :\n";
        for (const QString& w : warningsUniques)
            texte += "  - " + w + "\n";
        texte += "\n";
    }

    const QList<DonneesVol>& vols = p->getHistoriqueVols();
    for (int i = 0; i < vols.size(); ++i) {
        const DonneesVol& v = vols[i];
        texte += "--- Vol #" + QString::number(i + 1) + " ---\n";
        texte += "Type : " + v.typeVol + "\n";
        texte += "Date : " + v.dateVol.toString("yyyy-MM-dd hh:mm") + "\n";
        texte += "Crash : " + QString(v.estMort ? "OUI" : "NON") + "\n";
        texte += "Alt max : " + QString::number(v.altitudeMax, 'f', 1) + "\n";
        texte += "Speed max : " + QString::number(v.speedMax, 'f', 1) + "\n";

        if (v.typesWarnings.isEmpty()) {
            texte += "Warnings : Aucun\n\n";
        }
        else {
            texte += "Warnings :\n";
            for (const QString& w : v.typesWarnings)
                texte += "  - " + w + "\n";
            texte += "\n";
        }
    }

    return texte;
}

void ComptePilote::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    int w = event->size().width();
    int h = event->size().height();

    int margeH = w * 0.2;
    int largeur = w - (margeH * 2);

    labelTitre->setGeometry(margeH, h * 0.05, largeur, 40);
    labelPiloteActif->setGeometry(margeH, h * 0.13, largeur, 30);
    champNom->setGeometry(margeH, h * 0.22, largeur * 0.7, 40);
    boutonAjouter->setGeometry(margeH + largeur * 0.72, h * 0.22, largeur * 0.28, 40);
    listePilotes->setGeometry(margeH, h * 0.32, largeur, h * 0.25);
    boutonChoisir->setGeometry(margeH, h * 0.60, largeur, 40);
    boutonVoirStats->setGeometry(margeH, h * 0.68, largeur, 40);
    boutonRetour->setGeometry(margeH, h * 0.85, largeur, 45);
    scrollStats->setGeometry(margeH, h * 0.32, largeur, h * 0.45);
    if (labelStats)
        labelStats->setMinimumWidth(scrollStats->width() - 20);
    boutonFermerStats->setGeometry(margeH, h * 0.79, largeur, 40);
}

QPushButton* ComptePilote::creerBouton(const QString& message) {
    QPushButton* le_bouton = new QPushButton(message, this);
    le_bouton->raise();
    le_bouton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgba(30, 30, 30, 150);"
        "   color: rgba(0, 255, 0, 200);"
        "   border: 1px solid rgba(0, 255, 0, 100);"
        "   border-radius: 2px;"
        "   padding: 10px;"
        "   font-family: 'Consolas', monospace;"
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

//#include "moc_comptePilote.cpp"