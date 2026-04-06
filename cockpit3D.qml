import QtQuick
import QtQuick3D
import QtQuick3D.Helpers
import QtQuick.Controls
import "ressources/model3D"

// Holy Spaghetti code

Item {
    id: rootItem
    anchors.fill: parent

    // Material references
    property var mat1: null
    property var mat2: null
    property var mat3: null
    property var mat4: null

    function setLight(light, mat, brightness) {
        light.brightness = brightness
        if (mat) {
            var intensity = brightness / 100.0
            var c = light.color
            mat.baseColor = Qt.rgba(c.r * intensity, c.g * intensity, c.b * intensity, 1)
        }
    }

    View3D {
        id: view
        anchors.fill: parent

        environment: SceneEnvironment {
            clearColor: "gray"
            backgroundMode: SceneEnvironment.Color
            tonemapMode: SceneEnvironment.TonemapModeFilmic
            lightProbe: Texture {
                textureData: ProceduralSkyTextureData {}
            }
            probeExposure: 5.0
        }

        PerspectiveCamera {
            id: camera
            position: Qt.vector3d(500, 100, 0)
            eulerRotation: Qt.vector3d(0, 90, 0)
        }

        DirectionalLight {
            eulerRotation: Qt.vector3d(0, -90, 0)
            brightness: 5.0
        }

        PointLight {
            id: light1
            color: "#00ff00"
            brightness: 0
            quadraticFade: 0.1
            position: Qt.vector3d(100, 180, -25)
        }
        PointLight {
            id: light2
            color: "#ff0000"
            brightness: 0
            quadraticFade: 0.1
            position: Qt.vector3d(100, 180, -250)
        }
        PointLight {
            id: light3
            color: "#0044ff"
            brightness: 0
            quadraticFade: 0.1
            position: Qt.vector3d(100, 125, -25)
        }
        PointLight {
            id: light4
            color: "#ff9200"
            brightness: 0
            quadraticFade: 0.1
            position: Qt.vector3d(100, 125, -250)
        }

        Cocpit {
            id: world
            scale: Qt.vector3d(100, 100, 100)
            position: Qt.vector3d(0, 0, 0)

            Component.onCompleted: {
                function superFix(node) {
                    try { node.frustumCullingEnabled = false; } catch(e) {}
                    if (node.materials !== undefined) {
                        for (var i = 0; i < node.materials.length; i++) {
                            let mat = node.materials[i];
                            mat.alphaMode = PrincipledMaterial.Opaque;
                            mat.cullMode = PrincipledMaterial.NoCulling;
                            if (mat.objectName === "Meshlight1Emission") {
                                rootItem.mat1 = mat
                                mat.baseColor = Qt.rgba(0, 0, 0, 1)
                                mat.baseColorMap = null
                                mat.emissiveFactor = Qt.vector3d(0, 0, 0)
                                mat.lighting = PrincipledMaterial.NoLighting
                            }
                            if (mat.objectName === "MeshLightColor2") {
                                rootItem.mat2 = mat
                                mat.baseColor = Qt.rgba(0, 0, 0, 1)
                                mat.baseColorMap = null
                                mat.emissiveFactor = Qt.vector3d(0, 0, 0)
                                mat.lighting = PrincipledMaterial.NoLighting
                            }
                            if (mat.objectName === "Meshlight3Emission") {
                                rootItem.mat3 = mat
                                mat.baseColor = Qt.rgba(0, 0, 0, 1)
                                mat.baseColorMap = null
                                mat.emissiveFactor = Qt.vector3d(0, 0, 0)
                                mat.lighting = PrincipledMaterial.NoLighting
                            }
                            if (mat.objectName === "Meshlight4Emission") {
                                rootItem.mat4 = mat
                                mat.baseColor = Qt.rgba(0, 0, 0, 1)
                                mat.baseColorMap = null
                                mat.emissiveFactor = Qt.vector3d(0, 0, 0)
                                mat.lighting = PrincipledMaterial.NoLighting
                            }
                        }
                    }
                    for (var j = 0; j < node.children.length; j++) superFix(node.children[j])
                }
                superFix(world)
            }
        }

        WasdController {
            id: wasd
            controlledObject: camera
            speed: 0.1
            mouseEnabled: true
        }
    }

    Rectangle {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 10
        width: 300
        color: "#bb000000"
        radius: 8

        ScrollView {
            anchors.fill: parent
            anchors.margins: 12
            clip: true

            Column {
                width: 276
                spacing: 16

                Text {
                    text: "Light Controls"
                    color: "white"
                    font.pixelSize: 14
                    font.bold: true
                }

                Column {
                    spacing: 6
                    Text { text: "Light 1 (Green)"; color: "#00ff00"; font.pixelSize: 12; font.bold: true }
                    LightToggle { label: "On/Off"; onToggled: function(on) { rootItem.setLight(light1, rootItem.mat1, on ? 100 : 0) } }
                    LightSlider { label: "Brightness"; from: 0; to: 500; value: 0; onMoved: function(v) { rootItem.setLight(light1, rootItem.mat1, v) } }
                    LightSlider { label: "X"; from: -500; to: 500; value: 100; onMoved: function(v) { light1.x = v } }
                    LightSlider { label: "Y"; from: -500; to: 500; value: 180; onMoved: function(v) { light1.y = v } }
                    LightSlider { label: "Z"; from: -500; to: 500; value: -25; onMoved: function(v) { light1.z = v } }
                }

                Column {
                    spacing: 6
                    Text { text: "Light 2 (Red)"; color: "#ff4444"; font.pixelSize: 12; font.bold: true }
                    LightToggle { label: "On/Off"; onToggled: function(on) { rootItem.setLight(light2, rootItem.mat2, on ? 100 : 0) } }
                    LightSlider { label: "Brightness"; from: 0; to: 500; value: 0; onMoved: function(v) { rootItem.setLight(light2, rootItem.mat2, v) } }
                    LightSlider { label: "X"; from: -500; to: 500; value: 100; onMoved: function(v) { light2.x = v } }
                    LightSlider { label: "Y"; from: -500; to: 500; value: 180; onMoved: function(v) { light2.y = v } }
                    LightSlider { label: "Z"; from: -500; to: 500; value: -250; onMoved: function(v) { light2.z = v } }
                }

                Column {
                    spacing: 6
                    Text { text: "Light 3 (Blue)"; color: "#4488ff"; font.pixelSize: 12; font.bold: true }
                    LightToggle { label: "On/Off"; onToggled: function(on) { rootItem.setLight(light3, rootItem.mat3, on ? 100 : 0) } }
                    LightSlider { label: "Brightness"; from: 0; to: 500; value: 0; onMoved: function(v) { rootItem.setLight(light3, rootItem.mat3, v) } }
                    LightSlider { label: "X"; from: -500; to: 500; value: 100; onMoved: function(v) { light3.x = v } }
                    LightSlider { label: "Y"; from: -500; to: 500; value: 125; onMoved: function(v) { light3.y = v } }
                    LightSlider { label: "Z"; from: -500; to: 500; value: -25; onMoved: function(v) { light3.z = v } }
                }

                Column {
                    spacing: 6
                    Text { text: "Light 4 (Orange)"; color: "#ff9200"; font.pixelSize: 12; font.bold: true }
                    LightToggle { label: "On/Off"; onToggled: function(on) { rootItem.setLight(light4, rootItem.mat4, on ? 100 : 0) } }
                    LightSlider { label: "Brightness"; from: 0; to: 500; value: 0; onMoved: function(v) { rootItem.setLight(light4, rootItem.mat4, v) } }
                    LightSlider { label: "X"; from: -500; to: 500; value: 100; onMoved: function(v) { light4.x = v } }
                    LightSlider { label: "Y"; from: -500; to: 500; value: 125; onMoved: function(v) { light4.y = v } }
                    LightSlider { label: "Z"; from: -500; to: 500; value: -250; onMoved: function(v) { light4.z = v } }
                }

                Rectangle {
                    width: 240
                    height: 36
                    color: "#446644"
                    radius: 6
                    Text {
                        anchors.centerIn: parent
                        text: "Print positions to console"
                        color: "white"
                        font.pixelSize: 12
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            console.log("Light1:", light1.x, light1.y, light1.z, "brightness:", light1.brightness)
                            console.log("Light2:", light2.x, light2.y, light2.z, "brightness:", light2.brightness)
                            console.log("Light3:", light3.x, light3.y, light3.z, "brightness:", light3.brightness)
                            console.log("Light4:", light4.x, light4.y, light4.z, "brightness:", light4.brightness)
                        }
                    }
                }
            }
        }
    }

    component LightSlider: Row {
        property alias label: lbl.text
        property alias from: sl.from
        property alias to: sl.to
        property alias value: sl.value
        signal moved(real value)
        spacing: 6
        Text {
            id: lbl
            color: "white"
            font.pixelSize: 11
            width: 70
            anchors.verticalCenter: parent.verticalCenter
        }
        Slider {
            id: sl
            width: 140
            onMoved: function() { parent.moved(sl.value) }
        }
        Text {
            text: Math.round(sl.value)
            color: "#aaaaaa"
            font.pixelSize: 11
            width: 36
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    component LightToggle: Row {
        property alias label: lbl.text
        signal toggled(bool on)
        spacing: 6
        Text {
            id: lbl
            color: "white"
            font.pixelSize: 11
            width: 70
            anchors.verticalCenter: parent.verticalCenter
        }
        Switch {
            id: sw
            onToggled: function() { parent.toggled(sw.checked) }
        }
    }

    focus: true
    Keys.onPressed: (event) => {
        if (event.key === Qt.Key_Shift) wasd.speed = 0.01
    }
    Keys.onReleased: (event) => {
        if (event.key === Qt.Key_Shift) wasd.speed = 0.1
    }
}
