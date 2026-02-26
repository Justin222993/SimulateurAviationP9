import QtQuick
import QtQuick3D

Node {
    id: node

    // Resources
    PrincipledMaterial {
        id: lightHouseRed_material
        objectName: "LightHouseRed"
        baseColor: "#ffe70009"
        roughness: 0.5
        cullMode: PrincipledMaterial.NoCulling
        alphaMode: PrincipledMaterial.Opaque
    }
    PrincipledMaterial {
        id: lightHouseLight_material
        objectName: "LightHouseLight"
        baseColor: "#ffe7e7e7"
        roughness: 0.5
        emissiveFactor: Qt.vector3d(1, 0.896351, 0)
        cullMode: PrincipledMaterial.NoCulling
        alphaMode: PrincipledMaterial.Opaque
    }
    PrincipledMaterial {
        id: lightHouseWhite_material
        objectName: "LightHouseWhite"
        baseColor: "#ffe7e7e7"
        roughness: 0.5
        cullMode: PrincipledMaterial.NoCulling
        alphaMode: PrincipledMaterial.Opaque
    }
    PrincipledMaterial {
        id: lightHouseBaseGrey_material
        objectName: "LightHouseBaseGrey"
        baseColor: "#ff616161"
        roughness: 0.5
        cullMode: PrincipledMaterial.NoCulling
        alphaMode: PrincipledMaterial.Opaque
    }
    PrincipledMaterial {
        id: lightHouseBlackDoor_material
        objectName: "LightHouseBlackDoor"
        baseColor: "#ff000000"
        roughness: 0.5
        cullMode: PrincipledMaterial.NoCulling
        alphaMode: PrincipledMaterial.Opaque
    }
    PrincipledMaterial {
        id: water_material
        objectName: "Water"
        baseColor: "#ff000022"
        metalness: 1
        roughness: 0.19545453786849976
        cullMode: PrincipledMaterial.NoCulling
        alphaMode: PrincipledMaterial.Opaque
    }
    PrincipledMaterial {
        id: rock_material
        objectName: "Rock"
        baseColor: "#ff565656"
        roughness: 0.8181818127632141
        cullMode: PrincipledMaterial.NoCulling
        alphaMode: PrincipledMaterial.Opaque
    }
    PrincipledMaterial {
        id: houseYellow_material
        objectName: "HouseYellow"
        baseColor: "#ff9e9a80"
        roughness: 0.5
        cullMode: PrincipledMaterial.NoCulling
        alphaMode: PrincipledMaterial.Opaque
    }
    PrincipledMaterial {
        id: houseRed_material
        objectName: "HouseRed"
        baseColor: "#ff87242a"
        roughness: 0.5
        cullMode: PrincipledMaterial.NoCulling
        alphaMode: PrincipledMaterial.Opaque
    }

    // Nodes:
    Node {
        id: root
        objectName: "ROOT"
        Model {
            id: lighthouse
            objectName: "Lighthouse"
            position: Qt.vector3d(-1.53773, 1.23039, 1.87398)
            scale: Qt.vector3d(0.459135, 0.459135, 0.459135)
            source: "meshes/lighthouse_mesh.mesh"
            materials: [
                lightHouseRed_material,
                lightHouseLight_material,
                lightHouseWhite_material,
                lightHouseBaseGrey_material,
                lightHouseBlackDoor_material
            ]
        }
        Model {
            id: water
            objectName: "Water"
            scale: Qt.vector3d(5.63979, 5.63979, 5.63979)
            source: "meshes/plane_mesh.mesh"
            materials: [
                water_material
            ]
        }
        Model {
            id: baseRock
            objectName: "BaseRock"
            source: "meshes/icosphere_001_mesh.mesh"
            materials: [
                rock_material
            ]
        }
        DirectionalLight {
            id: sun_light
            objectName: "Sun"
            position: Qt.vector3d(-5.04001, 7.98303, 0.835629)
            rotation: Qt.quaternion(0.221127, -0.644033, -0.0550649, 0.730269)
            color: "#ff2b36ff"
            brightness: 1472.740234375
        }
        Node {
            id: point
            objectName: "Point"
            position: Qt.vector3d(-0.320188, 1.70193, 3.09392)
            rotation: Qt.quaternion(0.707107, -0.707107, 0, 0)
            scale: Qt.vector3d(1, 1, 1)
        }
        Node {
            id: point_001
            objectName: "Point.001"
            position: Qt.vector3d(0.598311, 1.26057, 2.18367)
            rotation: Qt.quaternion(0.707107, -0.707107, 0, 0)
            scale: Qt.vector3d(1, 1, 1)
        }
        PointLight {
            id: point_002_light
            objectName: "Point.002"
            position: Qt.vector3d(1.54097, 0.758243, -0.3945)
            rotation: Qt.quaternion(0.707107, -0.707107, 0, 0)
            scale: Qt.vector3d(1, 1, 1)
            color: "#ffffe9ad"
            brightness: 23.82366943359375
            quadraticFade: 10000
        }
        PointLight {
            id: point_003_light
            objectName: "Point.003"
            position: Qt.vector3d(5.53201, 0.59899, 3.38417)
            rotation: Qt.quaternion(0.707107, -0.707107, 0, 0)
            scale: Qt.vector3d(1, 1, 1)
            color: "#ffff0002"
            brightness: 41.20588302612305
            quadraticFade: 10000
        }
        PointLight {
            id: light_light
            objectName: "Light"
            position: Qt.vector3d(4.27955, 0.0687619, 1.71299)
            rotation: Qt.quaternion(0.523275, -0.284166, 0.726942, 0.342034)
            scale: Qt.vector3d(1, 1, 1)
            color: "#ffce21ff"
            brightness: 11920.8271484375
            quadraticFade: 10000
        }
        PerspectiveCamera {
            id: camera_camera
            objectName: "Camera"
            position: Qt.vector3d(23.7292, 3.11231, 14.2077)
            rotation: Qt.quaternion(0.87755, -0.0275777, 0.478456, 0.0150359)
            scale: Qt.vector3d(1, 1, 1)
            clipNear: 0.10000000149011612
            clipFar: 100
            fieldOfView: 39.59775924682617
            fieldOfViewOrientation: PerspectiveCamera.Horizontal
        }
        Model {
            id: cube_001
            objectName: "Cube.001"
            position: Qt.vector3d(3.98388, 0.95827, -0.909405)
            rotation: Qt.quaternion(0.948792, 0, 0.315902, 0)
            scale: Qt.vector3d(0.160336, 0.160336, 0.160336)
            source: "meshes/cube_001_mesh.mesh"
            materials: [
                houseYellow_material,
                houseRed_material
            ]
        }
        Model {
            id: cube_003
            objectName: "Cube.003"
            position: Qt.vector3d(-0.570233, 1.81563, 3.3702)
            scale: Qt.vector3d(0.160336, 0.160336, 0.160336)
            source: "meshes/cube_003_mesh.mesh"
            materials: [
                houseYellow_material,
                houseRed_material
            ]
        }
        Model {
            id: cube_004
            objectName: "Cube.004"
            position: Qt.vector3d(5.27374, 0.686473, 3.69664)
            scale: Qt.vector3d(0.160336, 0.160336, 0.160336)
            source: "meshes/cube_004_mesh.mesh"
            materials: [
                houseYellow_material,
                houseRed_material
            ]
        }
        Model {
            id: cube_006
            objectName: "Cube.006"
            position: Qt.vector3d(3.05792, 0.913387, -0.909848)
            rotation: Qt.quaternion(0.335982, -0.0394126, 0.940971, -0.0116392)
            scale: Qt.vector3d(0.160336, 0.160336, 0.160336)
            source: "meshes/cube_006_mesh.mesh"
            materials: [
                houseYellow_material,
                houseRed_material
            ]
        }
        Model {
            id: cube_002
            objectName: "Cube.002"
            position: Qt.vector3d(4.72824, 0.626532, -1.61047)
            rotation: Qt.quaternion(0.783357, 0, -0.621572, 0)
            scale: Qt.vector3d(0.160336, 0.160336, 0.160336)
            source: "meshes/cube_002_mesh.mesh"
            materials: [
                houseYellow_material,
                houseRed_material
            ]
        }
        Model {
            id: cube_007
            objectName: "Cube.007"
            position: Qt.vector3d(2.13711, 0.760387, -1.14613)
            rotation: Qt.quaternion(0.536077, 0, 0.844169, 0)
            scale: Qt.vector3d(0.160336, 0.160336, 0.160336)
            source: "meshes/cube_007_mesh.mesh"
            materials: [
                houseYellow_material,
                houseRed_material
            ]
        }
        Model {
            id: cube_008
            objectName: "Cube.008"
            position: Qt.vector3d(-0.0546791, 1.76965, 3.27278)
            rotation: Qt.quaternion(0.941992, 0, 0.335636, 0)
            scale: Qt.vector3d(0.160336, 0.160336, 0.160336)
            source: "meshes/cube_008_mesh.mesh"
            materials: [
                houseYellow_material,
                houseRed_material
            ]
        }
        Model {
            id: cube_009
            objectName: "Cube.009"
            position: Qt.vector3d(6.30386, 0.661554, 4.0227)
            rotation: Qt.quaternion(0.484041, 0, 0.875045, 0)
            scale: Qt.vector3d(0.160336, 0.160336, 0.160336)
            source: "meshes/cube_009_mesh.mesh"
            materials: [
                houseYellow_material,
                houseRed_material
            ]
        }
        Model {
            id: cube_010
            objectName: "Cube.010"
            position: Qt.vector3d(6.27627, 0.863348, -0.166408)
            rotation: Qt.quaternion(0.716101, 0, 0.697997, 0)
            scale: Qt.vector3d(0.160336, 0.160336, 0.160336)
            source: "meshes/cube_010_mesh.mesh"
            materials: [
                houseYellow_material,
                houseRed_material
            ]
        }
        Model {
            id: cube_011
            objectName: "Cube.011"
            position: Qt.vector3d(1.56026, 0.525519, 4.36873)
            rotation: Qt.quaternion(0.783357, 0, -0.621572, 0)
            scale: Qt.vector3d(0.160336, 0.160336, 0.160336)
            source: "meshes/cube_011_mesh.mesh"
            materials: [
                houseYellow_material,
                houseRed_material
            ]
        }
        Model {
            id: cube_012
            objectName: "Cube.012"
            position: Qt.vector3d(4.33583, 0.683133, 3.59416)
            rotation: Qt.quaternion(-0.14798, 0, 0.98899, 0)
            scale: Qt.vector3d(0.160336, 0.160336, 0.160336)
            source: "meshes/cube_012_mesh.mesh"
            materials: [
                houseYellow_material,
                houseRed_material
            ]
        }
        Model {
            id: cube_013
            objectName: "Cube.013"
            position: Qt.vector3d(5.49286, 0.851045, -0.229301)
            rotation: Qt.quaternion(0.390787, 0, 0.920481, 0)
            scale: Qt.vector3d(0.160336, 0.160336, 0.160336)
            source: "meshes/cube_013_mesh.mesh"
            materials: [
                houseYellow_material,
                houseRed_material
            ]
        }
        Model {
            id: cube_014
            objectName: "Cube.014"
            position: Qt.vector3d(-0.662547, 1.74007, 1.08768)
            rotation: Qt.quaternion(-0.19002, 0.0236042, 0.979505, 0.0624907)
            scale: Qt.vector3d(0.160336, 0.160336, 0.160336)
            source: "meshes/cube_014_mesh.mesh"
            materials: [
                houseYellow_material,
                houseRed_material
            ]
        }
        Model {
            id: cube_015
            objectName: "Cube.015"
            position: Qt.vector3d(1.45934, 0.855537, -0.0929765)
            rotation: Qt.quaternion(0.1463, 0, 0.98924, 0)
            scale: Qt.vector3d(0.160336, 0.160336, 0.160336)
            source: "meshes/cube_015_mesh.mesh"
            materials: [
                houseYellow_material,
                houseRed_material
            ]
        }
        Model {
            id: cube_016
            objectName: "Cube.016"
            position: Qt.vector3d(1.27018, 0.897217, 3.57944)
            rotation: Qt.quaternion(0.925302, 0.120697, 0.358532, -0.0265122)
            scale: Qt.vector3d(0.160336, 0.160336, 0.160336)
            source: "meshes/cube_016_mesh.mesh"
            materials: [
                houseYellow_material,
                houseRed_material
            ]
        }
        Model {
            id: cube_017
            objectName: "Cube.017"
            position: Qt.vector3d(0.750093, 1.2879, 2.48917)
            rotation: Qt.quaternion(-0.341154, 0.0934867, 0.935346, 0.00152434)
            scale: Qt.vector3d(0.160336, 0.160336, 0.160336)
            source: "meshes/cube_017_mesh.mesh"
            materials: [
                houseYellow_material,
                houseRed_material
            ]
        }
        Model {
            id: cube_018
            objectName: "Cube.018"
            position: Qt.vector3d(-1.38131, 1.17968, -0.0975773)
            rotation: Qt.quaternion(0.921337, -0.161703, 0.352335, 0.0291686)
            scale: Qt.vector3d(0.160336, 0.160336, 0.160336)
            source: "meshes/cube_018_mesh.mesh"
            materials: [
                houseYellow_material,
                houseRed_material
            ]
        }
    }

    // Animations:
}
