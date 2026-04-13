#ifndef PILOTE_H
#define PILOTE_H

#include <QString>
#include <QList>
#include <QDateTime>

struct DonneesVol {
    QString typeVol;
    int nbWarnings;
    bool estMort;
    QDateTime dateVol;
    double altitudeMax;
    double speedMax;
};

class Pilote {
public:
    Pilote(const QString& nom);
    QString getNom() const;
    void setNom(const QString& nom);

    void ajouterVol(const DonneesVol& vol);
    QList<DonneesVol> getHistoriqueVols() const;
    int getNbVols() const;
    int getNbMorts() const;
    int getNbWarningsTotal() const;

private:
    QString m_nom;
    QList<DonneesVol> m_historiqueVols;
};

#endif