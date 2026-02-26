import QtQuick
import QtQuick3D
import QtQuick3D.AssetUtils
import "ressources/model3D"

Item {
    id: rootItem

    property var activeCamera: view.camera

    property real originX: 0
    property real originY: 0
    property real originZ: 0
    property real originPitch: 0
    property real originYaw: 0
    property real originRoll: 0

    property real targetPitch: 0
    property real targetRoll: 0

    // Valeur de 1000 probablement a descendre quand on aura la manette
    Behavior on targetPitch { NumberAnimation { duration: 1000; easing.type: Easing.OutCubic } }
    Behavior on targetRoll  { NumberAnimation { duration: 1000; easing.type: Easing.OutCubic } }

    // La fonction appelée par QMetaObject::invokeMethod de simulation.cpp
    // Elle reçoit l'objet data
    function updateCamera(data) {
        if (activeCamera) {
            let scale = 0.002 // La scène 3D a un différentt scale, donc on a juste

        activeCamera.x = originX - (data.x * scale)
        activeCamera.y = (data.altitude * scale) // On garde pas l'altitude de base pour que le sol 0 soit le même que dans le plan 3D
        activeCamera.z = originZ - (data.y * scale) // "-" pour avancer dans Qt, J'ai aussi mis l'origin Z - le data y parce que les axes sont pas pareilles (J'ai choisis z pour l'altitude mais c'est y pour le modèle 3D)

        // 30 est un magic number pour calibrer la rotation du monde blender et la rotation du monde Qt
        activeCamera.eulerRotation.y = originYaw - data.yaw + 30

        // On lerp visuellement le pitch et le roll pour que sa soit plus smooth
        targetPitch = data.pitch 
        targetRoll = data.roll

        activeCamera.eulerRotation.x = originPitch + targetPitch
        activeCamera.eulerRotation.z = originRoll - targetRoll
        }
    }

    View3D {
        id: view
        anchors.fill: parent

        environment: SceneEnvironment {
            clearColor: "black"
            backgroundMode: SceneEnvironment.Color
    
            antialiasingMode: SceneEnvironment.MSAA
            antialiasingQuality: SceneEnvironment.High

            tonemapMode: SceneEnvironment.TonemapModeLinear
        }

        MiniHouses {
            id: world

            Component.onCompleted: {
                // Pour trouver les objets dans le modele 3d .qml
                function findObject(root, name) {
                    if (root.objectName === name) return root;
                    for (var i = 0; i < root.children.length; i++) {
                        var found = findObject(root.children[i], name);
                        if (found) return found;
                    }
                    return null;
                }

                // Trouve et set la caméra
                var cam = findObject(world, "Camera");
                if (cam) {
                    view.camera = cam;
  
                    rootItem.activeCamera = cam;
                    rootItem.originX = cam.x;
                    rootItem.originY = cam.y;
                    rootItem.originZ = cam.z;
                    rootItem.originPitch = cam.eulerRotation.x;
                    rootItem.originYaw = cam.eulerRotation.y;
                    rootItem.originRoll = cam.eulerRotation.z;

                    console.log("Position initiale de la camera: X: " + rootItem.originX + ", Y: " + rootItem.originY + ", Z: " + rootItem.originZ);
                    console.log("Rotation initiale de la camera: Pitch: " + rootItem.originPitch + ", Yaw: " + rootItem.originRoll + ", Roll: " + rootItem.originRoll);
                }
        
                // Soleil (Valeur de brightness ajusté)
                var sun = findObject(world, "Sun");
                if (sun) sun.brightness = 10;

                // Quelques lampes que j'ai dû ajuster la valeur de
                var bigLight = findObject(world, "Light");
                if (bigLight) bigLight.brightness = 3;

                var p2 = findObject(world, "Point.002");
                if (p2) p2.brightness = 1; 

                var p3 = findObject(world, "Point.003");
                if (p3) p3.brightness = 1;
            }
        }
    }
}