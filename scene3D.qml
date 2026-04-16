import QtQuick
import QtQuick3D
import "ressources/model3D/city"

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

    //Behavior on targetPitch { NumberAnimation { duration: 1000; easing.type: Easing.OutCubic } }
    //Behavior on targetRoll  { NumberAnimation { duration: 1000; easing.type: Easing.OutCubic } }

    function updateCamera(data) {
        if (activeCamera) {
            let scale = 0.05

            activeCamera.x = originX - (data.x * scale)
            activeCamera.y = (data.altitude * scale)
            activeCamera.z = originZ - (data.y * scale)

            let calibrationQtBlender = 90
            activeCamera.eulerRotation.y = originYaw - data.yaw + calibrationQtBlender

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
            clearColor: "#87CEEB"
            backgroundMode: SceneEnvironment.Color
    
            antialiasingMode: SceneEnvironment.NoAA
            antialiasingQuality: SceneEnvironment.NoAA
            
            tonemapMode: SceneEnvironment.TonemapModeLinear
            
            depthTestEnabled: true
            depthPrePassEnabled: true
            
            fog: Fog {
                enabled: true
                color: "#b0c4de"
                depthEnabled: true
                depthNear: 300
                depthFar: 600
            }
        }

        PerspectiveCamera {
            id: mainCamera
            objectName: "Camera"
            position: Qt.vector3d(0, 6, 15)
            eulerRotation: Qt.vector3d(-10, 0, 0)
            clipNear: 0.1
            clipFar: 1000
            fieldOfView: 60
        }

        DirectionalLight {
            id: sunLight
            objectName: "Sun"
            eulerRotation: Qt.vector3d(-45, 30, 0)
            color: "#ffffff"
            brightness: 1.5
            castsShadow: false
        }

        DirectionalLight {
            eulerRotation: Qt.vector3d(45, -30, 0)
            color: "#8899bb"
            brightness: 0.3
        }

        Repeater3D {
            model: 25 
            
            City {
                id: cityTile
                property real tileWidth: 400
                property real tileDepth: 400
                property int gridSize: 5
                
                property int gridX: index % gridSize
                property int gridZ: Math.floor(index / gridSize)
                
                position: {
                    if (!rootItem.activeCamera) return Qt.vector3d(0, 0, 0);
                    
                    let camX = rootItem.activeCamera.x;
                    let camZ = rootItem.activeCamera.z;
                    
                    let localOffsetX = (gridX - 2) * tileWidth;
                    let localOffsetZ = (gridZ - 2) * tileDepth;

                    let finalX = Math.floor((camX - localOffsetX + (tileWidth * 2.5)) / (tileWidth * 5)) * (tileWidth * 5) + localOffsetX;
                    let finalZ = Math.floor((camZ - localOffsetZ + (tileDepth * 2.5)) / (tileDepth * 5)) * (tileDepth * 5) + localOffsetZ;

                    return Qt.vector3d(finalX, 0, finalZ);
                }
                
                Component.onCompleted: {
                    function fixMaterials(node) {
                        if (node.materials) {
                            for (var i = 0; i < node.materials.length; i++) {
                                if (node.materials[i]) {
                                    node.materials[i].alphaMode = PrincipledMaterial.Opaque;
                                }
                            }
                        }
                        for (var j = 0; j < node.children.length; j++) {
                            fixMaterials(node.children[j]);
                        }
                    }
                    fixMaterials(cityTile);
                }
            }
        }

        Component.onCompleted: {
            view.camera = mainCamera;
            rootItem.activeCamera = mainCamera;
            
            rootItem.originX = mainCamera.x;
            rootItem.originY = mainCamera.y;
            rootItem.originZ = mainCamera.z;
            rootItem.originPitch = mainCamera.eulerRotation.x;
            rootItem.originYaw = mainCamera.eulerRotation.y;
            rootItem.originRoll = mainCamera.eulerRotation.z;
        }
    }
}