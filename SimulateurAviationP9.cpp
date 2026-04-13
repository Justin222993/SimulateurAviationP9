 #include <QApplication>
#include "gestionnaireScenes.h"
#include "SerialManager.h"
/// <summary>
/// initialisation de l'application, création du gestionnaire de scènes et lancement de la boucle d'événements Qt
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
void networkTickMaker() {
    while (true) {
        SerialManager::GetInstance().DoNetworkTick();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
int main(int argc, char* argv[])
{
    // Initialisation des services de communication série
    SerialManager::GetInstance();

    //std::thread t3(networkTickMaker);

    //t3.detach();


    QApplication a(argc, argv);

    GestionnaireScenes w;


    w.show();

    return a.exec();
}