#ifndef COMPTEPILOTE_H
#define COMPTEPILOTE_H

#include <QWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QResizeEvent>
#include <QList>
#include "pilote.h"
#include "transitions.h"

class ComptePilote : public QWidget {
    Q_OBJECT
public:
    ComptePilote(QWidget* parent = nullptr);
    Pilote* getPiloteSelectionne() const;
protected:
    void resizeEvent(QResizeEvent* event) override;
private:
    QPushButton* boutonRetour;
    QPushButton* boutonAjouter;
    QPushButton* boutonChoisir;
    QPushButton* boutonVoirStats;
    QPushButton* boutonFermerStats;
    QLineEdit* champNom;
    QListWidget* listePilotes;
    QLabel* labelTitre;
    QLabel* labelPiloteActif;
    QScrollArea* scrollStats;
    QLabel* labelStats;
    QList<Pilote*> m_pilotes;
    Pilote* m_piloteSelectionne;
    bool m_statsVisibles;
    QPushButton* creerBouton(const QString& message);
    void ajouterPilote();
    void choisirPilote();
    void mettreAJourLabel();
    void afficherStats();
    QString genererTexteStats(Pilote* p);
signals:
    void demanderRetourMenu();
    void piloteChoisi(Pilote* pilote);
};
#endif