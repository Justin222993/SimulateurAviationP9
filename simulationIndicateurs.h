#ifndef SIMULATIONINDICATEURS_H
#define SIMULATIONINDICATEURS_H

#include <QList>
#include <QStringList>
#include "indicateurComponent.h"
#include "avion.h"
#include "SerialManager.h"

class SimulationIndicateurs {
public:
    enum TypeInstrument {
        Anemometre,
        Horizon,
        Altimetre,
        Tachymetre,
        Virage,
        Cap,
        Variometre,
        Boussole,
        NB_INSTRUMENTS
    };

    inline static const QStringList NOMS_IMAGES = {
        "anemometre", "horizon-artificiel", "altimetre", "tachymetre",
        "coordonateur-de-virage", "indicateur-de-cap", "variometre", "boussole2"
    };

    struct PointValeur {
        double valeur;
        double angle;
    };

    SimulationIndicateurs();

    void creerAvion(double speed, double alt, double x, double y,
        double pitch, double yaw, double roll, double fuel);

    void setIndicateurs(QList<IndicateurComponent*> listeIndicateurs[], int nbInstruments);

    void handleAnemometre();
    void handleTachymetre();
    void handleBoussole();
    void handleCap();
	void handleAltimetre();
	void handleVariometre();
    void handleHorizon();

    void setAngleInstrument(int indexInstrument, int indexIndicateur, double angle);
    void setPosition(int indexInstrument, int indexIndicateur, double positionX, double positionY);

    void inputListener(Avion& p);
    void inputArduinoHandler(Avion& p);

    Avion& getAvion() { return p; }
    SerialManager* getSerialManager() { return serialManager; }

    inline static bool light1 = false;
    inline static bool light2 = false;
    inline static bool light3 = false;
    inline static bool light4 = false;

    inline static bool simulationEnCours = false;

    void updateLight(int lightNumber, bool state);

private:
    Avion p;
    SerialManager* serialManager = nullptr;
    QList<IndicateurComponent*>* listeIndicateurs = nullptr;
    int nbInstruments = 0;
};

#endif