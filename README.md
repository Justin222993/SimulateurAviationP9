# ✈️ Simulateur d'Aviation P9

Un simulateur de vol immersif développé en **C++** avec le framework **Qt 6**. Ceci est notre projet de session 2.

## 🚀 Prérequis

Avant de commencer, assurez-vous d'avoir installé :
* **Visual Studio Community 2022** (avec la charge de travail "Développement Desktop en C++").
* **Qt Framework** (version 6.x recommandée).
* **Extension Qt VS Tools** pour Visual Studio (disponible dans l'onglet "Extensions" de VS).

## 🛠️ Installation et Configuration

1.  **Ouvrir le projet :**
    * Lancez Visual Studio Community.
    * Faites `Fichier` > `Ouvrir` > `Projet/Solution` et sélectionnez votre fichier `.sln` ou `.vcxproj`.

2.  **Configurer Qt (Si c'est pas déjà fait):**
    * Allez dans l'onglet `Qt VS Tools` > `Qt Project Settings`.
    * Vérifiez que la version de Qt est bien sélectionnée dans `Qt Installation`.

3.  **Dossier Ressources :**
    * Assurez-vous que le dossier `ressources/` se trouve bien dans le répertoire de sortie (là où l'exécutable `.exe` est généré) ou à la racine du projet selon votre configuration.

## 🔨 Compilation

* **Nettoyer la solution :** `Clic droit sur la Solution` > `Nettoyer la solution` (Clean).
* **Générer :** `Générer` > `Générer la solution` (Build).
* **Lancer :** Appuyez sur `F5` ou sur le bouton "Débogage local Windows".

## 📁 Structure du Code

* `MenuPrincipale` : Gestion de l'interface et du premier contact utilisateur.
* `Transitions` : Classe statique pour les effets visuels de fondu.
* `GestionnaireScenes` : Orchestrateur du changement de scènes.
* `Simulation` : Scène future ou on va avoir la code pour la simulation
* `SimulateurAviationP9` : Main, run l'app et load la première scène dans la liste dicté pas `GestionnaireScenes`
