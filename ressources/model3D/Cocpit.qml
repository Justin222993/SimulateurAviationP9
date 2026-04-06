import QtQuick
import QtQuick3D

Node {
    id: node

    // Resources
    property url textureData: "maps/textureData.png"
    property url textureData44: "maps/textureData44.png"
    property url textureData5: "maps/textureData5.png"
    property url textureData27: "maps/textureData27.png"
    property url textureData7: "maps/textureData7.png"
    property url textureData40: "maps/textureData40.png"
    property url textureData9: "maps/textureData9.png"
    property url textureData29: "maps/textureData29.png"
    property url textureData11: "maps/textureData11.png"
    property url textureData38: "maps/textureData38.png"
    property url textureData31: "maps/textureData31.png"
    property url textureData14: "maps/textureData14.png"
    property url textureData42: "maps/textureData42.png"
    property url textureData16: "maps/textureData16.png"
    property url textureData33: "maps/textureData33.png"
    property url textureData18: "maps/textureData18.png"
    property url textureData47: "maps/textureData47.png"
    property url textureData20: "maps/textureData20.png"
    property url textureData58: "maps/textureData58.png"
    property url textureData53: "maps/textureData53.png"
    property url textureData51: "maps/textureData51.png"
    property url textureData49: "maps/textureData49.png"
    property url textureData62: "maps/textureData62.png"
    property url textureData73: "maps/textureData73.png"
    property url textureData64: "maps/textureData64.png"
    property url textureData69: "maps/textureData69.png"
    property url textureData71: "maps/textureData71.png"
    property url textureData75: "maps/textureData75.png"
    property url textureData80: "maps/textureData80.png"
    property url textureData82: "maps/textureData82.png"
    Texture {
        id: _7_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData20
    }
    Texture {
        id: _8_texture
        indexUV: 1
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData27
    }
    Texture {
        id: _9_texture
        indexUV: 1
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData29
    }
    Texture {
        id: _10_texture
        indexUV: 1
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData31
    }
    Texture {
        id: _11_texture
        indexUV: 1
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData33
    }
    Texture {
        id: _12_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData38
    }
    Texture {
        id: _13_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData40
    }
    Texture {
        id: _14_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData42
    }
    Texture {
        id: _23_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData64
    }
    Texture {
        id: _16_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData47
    }
    Texture {
        id: _17_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData49
    }
    Texture {
        id: _18_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData51
    }
    Texture {
        id: _19_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData53
    }
    Texture {
        id: _20_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData58
    }
    Texture {
        id: _21_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData
    }
    Texture {
        id: _22_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData62
    }
    Texture {
        id: _0_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData5
    }
    Texture {
        id: _1_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData7
    }
    Texture {
        id: _2_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData9
    }
    Texture {
        id: _24_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData69
    }
    Texture {
        id: _3_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData11
    }
    Texture {
        id: _25_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData71
    }
    Texture {
        id: _15_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData44
    }
    Texture {
        id: _26_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData73
    }
    Texture {
        id: _27_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData75
    }
    Texture {
        id: _4_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData14
    }
    Texture {
        id: _28_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData80
    }
    Texture {
        id: _5_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData16
    }
    Texture {
        id: _29_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData82
    }
    Texture {
        id: _6_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData18
    }
    PrincipledMaterial {
        id: meshlight4Emission_material
        objectName: "Meshlight4Emission"
        baseColorMap: _24_texture
        metalnessMap: _25_texture
        roughnessMap: _25_texture
        metalness: 1
        roughness: 1
        normalMap: _26_texture
        emissiveMap: _27_texture
        emissiveFactor: Qt.vector3d(1, 1, 1)
        cullMode: PrincipledMaterial.NoCulling
        alphaMode: PrincipledMaterial.Blend
    }
    PrincipledMaterial {
        id: meshlight3Emission_material
        objectName: "Meshlight3Emission"
        baseColorMap: _20_texture
        metalnessMap: _21_texture
        roughnessMap: _21_texture
        metalness: 1
        roughness: 1
        normalMap: _22_texture
        emissiveMap: _23_texture
        emissiveFactor: Qt.vector3d(1, 1, 1)
        cullMode: PrincipledMaterial.NoCulling
        alphaMode: PrincipledMaterial.Blend
    }
    PrincipledMaterial {
        id: meshlight1Emission_material
        objectName: "Meshlight1Emission"
        baseColorMap: _16_texture
        metalnessMap: _17_texture
        roughnessMap: _17_texture
        metalness: 1
        roughness: 1
        normalMap: _18_texture
        emissiveMap: _19_texture
        emissiveFactor: Qt.vector3d(1, 1, 1)
        cullMode: PrincipledMaterial.NoCulling
        alphaMode: PrincipledMaterial.Blend
    }
    PrincipledMaterial {
        id: contour_material
        objectName: "Contour"
        baseColor: "#ff000000"
        roughness: 1
        cullMode: PrincipledMaterial.NoCulling
        alphaMode: PrincipledMaterial.Opaque
    }
    PrincipledMaterial {
        id: screenContour_material
        objectName: "ScreenContour"
        baseColorMap: _8_texture
        metalnessMap: _9_texture
        roughnessMap: _9_texture
        metalness: 1
        roughness: 1
        normalMap: _10_texture
        emissiveMap: _11_texture
        emissiveFactor: Qt.vector3d(1, 1, 1)
        cullMode: PrincipledMaterial.NoCulling
        alphaMode: PrincipledMaterial.Blend
    }
    PrincipledMaterial {
        id: pannels_material
        objectName: "Pannels"
        baseColorMap: _4_texture
        metalnessMap: _5_texture
        roughnessMap: _5_texture
        metalness: 1
        roughness: 1
        normalMap: _6_texture
        emissiveMap: _7_texture
        emissiveFactor: Qt.vector3d(1, 1, 1)
        cullMode: PrincipledMaterial.NoCulling
        alphaMode: PrincipledMaterial.Blend
    }
    PrincipledMaterial {
        id: base_material
        objectName: "Base"
        baseColorMap: _0_texture
        metalnessMap: _1_texture
        roughnessMap: _1_texture
        metalness: 1
        roughness: 1
        normalMap: _2_texture
        emissiveMap: _3_texture
        cullMode: PrincipledMaterial.NoCulling
        alphaMode: PrincipledMaterial.Blend
    }
    PrincipledMaterial {
        id: metalLightPart_material
        objectName: "MetalLightPart"
        baseColorMap: _12_texture
        metalnessMap: _13_texture
        roughnessMap: _13_texture
        metalness: 1
        roughness: 1
        normalMap: _14_texture
        emissiveMap: _15_texture
        cullMode: PrincipledMaterial.NoCulling
        alphaMode: PrincipledMaterial.Blend
    }
    PrincipledMaterial {
        id: meshLightColor2_material
        objectName: "MeshLightColor2"
        baseColorMap: _28_texture
        metalnessMap: _29_texture
        roughnessMap: _29_texture
        metalness: 1
        roughness: 1
        normalMap: _18_texture
        emissiveMap: _19_texture
        emissiveFactor: Qt.vector3d(1, 1, 1)
        cullMode: PrincipledMaterial.NoCulling
        alphaMode: PrincipledMaterial.Blend
    }
    PrincipledMaterial {
        id: screen_material
        objectName: "Screen"
        baseColor: "#ff0000e7"
        roughness: 0.5
        emissiveFactor: Qt.vector3d(0, 0.699876, 1)
        cullMode: PrincipledMaterial.NoCulling
        alphaMode: PrincipledMaterial.Opaque
    }

    // Nodes:
    Node {
        id: root
        objectName: "ROOT"
        Model {
            id: dashboard
            objectName: "Dashboard"
            source: "meshes/dashboard_mesh.mesh"
            materials: [
                base_material,
                pannels_material,
                contour_material
            ]
        }
        Model {
            id: screen
            objectName: "Screen"
            scale: Qt.vector3d(1, 1, 1.03872)
            source: "meshes/screen_mesh.mesh"
            materials: [
                screen_material,
                screenContour_material
            ]
        }
        Model {
            id: meshLight1
            objectName: "MeshLight1"
            position: Qt.vector3d(0, 0, -0.0255831)
            source: "meshes/meshLight1_mesh.mesh"
            materials: [
                metalLightPart_material,
                meshlight1Emission_material
            ]
        }
        Model {
            id: meshLight3
            objectName: "MeshLight3"
            position: Qt.vector3d(0, 0, -0.0255831)
            source: "meshes/meshLight3_mesh.mesh"
            materials: [
                metalLightPart_material,
                meshlight3Emission_material
            ]
        }
        Model {
            id: meshLight4
            objectName: "MeshLight4"
            position: Qt.vector3d(0, 0, -0.0777725)
            source: "meshes/meshLight4_mesh.mesh"
            materials: [
                metalLightPart_material,
                meshlight4Emission_material
            ]
        }
        Model {
            id: meshLight2
            objectName: "MeshLight2"
            position: Qt.vector3d(0, 0, -0.098239)
            source: "meshes/meshLight2_mesh.mesh"
            materials: [
                metalLightPart_material,
                meshLightColor2_material
            ]
        }
    }

    // Animations:
}
