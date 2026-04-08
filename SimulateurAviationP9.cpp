 #include <QApplication>
#include "gestionnaireScenes.h"
#include "SerialManager.h"
/// <summary>
/// initialisation de l'application, création du gestionnaire de scènes et lancement de la boucle d'événements Qt
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char* argv[])
{
    // Initialisation des services de communication série
    SerialManager::GetInstance();

    QApplication a(argc, argv);

    GestionnaireScenes w;

	
    w.show();

    return a.exec();
}