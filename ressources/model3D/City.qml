import QtQuick
import QtQuick3D

Node {
    id: node

    // Resources
    property url textureData: "maps/textureData.png"
    property url textureData44: "maps/textureData44.png"
    property url textureData42: "maps/textureData42.png"
    property url textureData37: "maps/textureData37.png"
    property url textureData20: "maps/textureData20.png"
    property url textureData48: "maps/textureData48.png"
    property url textureData26: "maps/textureData26.png"
    property url textureData11: "maps/textureData11.png"
    property url textureData22: "maps/textureData22.png"
    property url textureData13: "maps/textureData13.png"
    property url textureData35: "maps/textureData35.png"
    property url textureData15: "maps/textureData15.png"
    property url textureData33: "maps/textureData33.png"
    property url textureData31: "maps/textureData31.png"
    property url textureData24: "maps/textureData24.png"
    property url textureData46: "maps/textureData46.png"
    Texture {
        id: _1_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData11
    }
    Texture {
        id: _2_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData13
    }
    Texture {
        id: _4_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData20
    }
    Texture {
        id: _6_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData24
    }
    Texture {
        id: _7_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData26
    }
    Texture {
        id: _3_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData15
    }
    Texture {
        id: _8_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData31
    }
    Texture {
        id: _9_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData33
    }
    Texture {
        id: _10_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData35
    }
    Texture {
        id: _11_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData37
    }
    Texture {
        id: _12_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData42
    }
    Texture {
        id: _5_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData22
    }
    Texture {
        id: _14_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData46
    }
    Texture {
        id: _0_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData
    }
    Texture {
        id: _15_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData48
    }
    Texture {
        id: _13_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: node.textureData44
    }
    PrincipledMaterial {
        id: material_003_material
        objectName: "Material.003"
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
        id: material_002_material
        objectName: "Material.002"
        baseColorMap: _8_texture
        metalnessMap: _9_texture
        roughnessMap: _9_texture
        metalness: 1
        roughness: 1
        normalMap: _10_texture
        emissiveMap: _11_texture
        cullMode: PrincipledMaterial.NoCulling
        alphaMode: PrincipledMaterial.Blend
    }
    PrincipledMaterial {
        id: principledMaterial
        metalness: 1
        roughness: 1
        alphaMode: PrincipledMaterial.Opaque
    }
    PrincipledMaterial {
        id: city3_material
        objectName: "City3"
        baseColorMap: _4_texture
        metalnessMap: _5_texture
        roughnessMap: _5_texture
        metalness: 1
        roughness: 1
        normalMap: _6_texture
        emissiveMap: _7_texture
        cullMode: PrincipledMaterial.NoCulling
        alphaMode: PrincipledMaterial.Blend
    }
    PrincipledMaterial {
        id: material_001_material
        objectName: "Material.001"
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

    // Nodes:
    Node {
        id: root
        objectName: "ROOT"
        Model {
            id: plane_004
            objectName: "Plane.004"
            source: "meshes/plane_005_mesh.mesh"
            materials: [
                principledMaterial
            ]
        }
        Model {
            id: plane
            objectName: "Plane"
            source: "meshes/plane_mesh.mesh"
            materials: [
                material_001_material
            ]
        }
        Model {
            id: plane_001
            objectName: "Plane.001"
            source: "meshes/plane_001_mesh.mesh"
            materials: [
                city3_material
            ]
        }
        Model {
            id: plane_002
            objectName: "Plane.002"
            source: "meshes/plane_002_mesh.mesh"
            materials: [
                material_002_material
            ]
        }
        Model {
            id: plane_003
            objectName: "Plane.003"
            source: "meshes/plane_004_mesh.mesh"
            materials: [
                material_003_material
            ]
        }
    }

    // Animations:
}
