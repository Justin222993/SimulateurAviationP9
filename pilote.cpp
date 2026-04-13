#include "pilote.h"

Pilote::Pilote(const QString& nom) : m_nom(nom) {}

QString Pilote::getNom() const { return m_nom; }
void Pilote::setNom(const QString& nom) { m_nom = nom; }

void Pilote::ajouterVol(const DonneesVol& vol) {
    m_historiqueVols.append(vol);
}

QList<DonneesVol> Pilote::getHistoriqueVols() const {
    return m_historiqueVols;
}

int Pilote::getNbVols() const {
    return m_historiqueVols.size();
}

int Pilote::getNbMorts() const {
    int count = 0;
    for (const DonneesVol& v : m_historiqueVols)
        if (v.estMort) count++;
    return count;
}

int Pilote::getNbWarningsTotal() const {
    int count = 0;
    for (const DonneesVol& v : m_historiqueVols)
        count += v.nbWarnings;
    return count;
}