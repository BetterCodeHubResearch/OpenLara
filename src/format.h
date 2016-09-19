#ifndef H_FORMAT
#define H_FORMAT

#include "utils.h"

#define TR1_DEMO

namespace TR {

    enum : int32 {
        ROOM_FLAG_WATER     = 0x0001,
        ROOM_FLAG_VISIBLE   = 0x8000
    };

    enum {
        FD_PORTAL   = 1,
        FD_FLOOR    = 2,
        FD_CEILING  = 3,
        FD_TRIGGER  = 4,
        FD_KILL     = 5,
    };

    enum {
        ANIM_CMD_MOVE    = 1,
        ANIM_CMD_SPEED   = 2,
        ANIM_CMD_EMPTY   = 3,
        ANIM_CMD_KILL    = 4,
        ANIM_CMD_SOUND   = 5,
        ANIM_CMD_SPECIAL = 6,
    };

    enum {
        ANIM_CMD_SPECIAL_FLIP   = 0,
        ANIM_CMD_SPECIAL_BUBBLE = 3,
        ANIM_CMD_SPECIAL_CTRL   = 12,
    };

    enum {
        SND_BUBBLE      = 37,
    };

    enum {
        TRIGGER_ACTIVATE = 0,
        TRIGGER_PAD      = 1,
        TRIGGER_SWITCH   = 2,
        TRIGGER_KEY      = 3,
        TRIGGER_PICKUP   = 4,
        TRIGGER_HEAVY    = 5,
        TRIGGER_ANTIPAD  = 6,
        TRIGGER_COMBAT   = 7,
        TRIGGER_DUMMY    = 8,
        TRIGGER_ANTI     = 9
    };

    enum Action {
        NONE            = -1,   // no action
        ACTIVATE        =  0,   // activate item
        CAMERA_SWITCH   =  1,   // switch to camera
        CAMERA_DELAY    =  2,   // camera delay
        FLIP_MAP        =  3,   // flip map
        FLIP_ON         =  4,   // flip on
        FLIP_OFF        =  5,   // flip off
        LOOK_AT         =  6,   // look at item
        END             =  7,   // end level
        SOUNDTRACK      =  8,   // play soundtrack
        HARDCODE        =  9,   // special hadrdcode trigger
        SECRET          = 10,   // secret found
        CLEAR_BODIES    = 11,   // clear bodies
        CAMERA_FLYBY    = 12,   // flyby camera sequence
        CUTSCENE        = 13,   // play cutscene
    };


    #define DATA_PORTAL     0x01
    #define DATA_FLOOR      0x02
    #define DATA_CEILING    0x03

    #define ENTITY_FLAG_CLEAR   0x0080
    #define ENTITY_FLAG_VISIBLE 0x0100
    #define ENTITY_FLAG_ACTIVE  0x3E00


    #define ENTITY_LARA                     0
    #define ENTITY_LARA_CUT                 77

    #define ENTITY_ENEMY_TWIN               6
    #define ENTITY_ENEMY_WOLF               7
    #define ENTITY_ENEMY_BEAR               8
    #define ENTITY_ENEMY_BAT                9
    #define ENTITY_ENEMY_CROCODILE_LAND     10
    #define ENTITY_ENEMY_CROCODILE_WATER    11
    #define ENTITY_ENEMY_LION_MALE          12
    #define ENTITY_ENEMY_LION_FEMALE        13
    #define ENTITY_ENEMY_PUMA               14
    #define ENTITY_ENEMY_GORILLA            15
    #define ENTITY_ENEMY_RAT_LAND           16
    #define ENTITY_ENEMY_RAT_WATER          17
    #define ENTITY_ENEMY_REX                18
    #define ENTITY_ENEMY_RAPTOR             19
    #define ENTITY_ENEMY_MUTANT             20

    #define ENTITY_ENEMY_CENTAUR            23
    #define ENTITY_ENEMY_MUMMY              24
    #define ENTITY_ENEMY_LARSON             27

    #define ENTITY_BLADE                    36

    #define ENTITY_CRYSTAL                  83

    #define ENTITY_MEDIKIT_SMALL            93
    #define ENTITY_MEDIKIT_BIG              94

    #define ENTITY_TRAP_FLOOR               35
    #define ENTITY_TRAP_SPIKES              37
    #define ENTITY_TRAP_STONE               38
    #define ENTITY_TRAP_DART                40

    #define ENTITY_SWITCH                   55
    #define ENTITY_SWITCH_WATER             56

    #define ENTITY_DOOR_1                   57
    #define ENTITY_DOOR_2                   58
    #define ENTITY_DOOR_3                   59
    #define ENTITY_DOOR_4                   60
    #define ENTITY_DOOR_BIG_1               61  
    #define ENTITY_DOOR_BIG_2               62
    #define ENTITY_DOOR_5                   63
    #define ENTITY_DOOR_6                   64
    #define ENTITY_DOOR_FLOOR_1             65
    #define ENTITY_DOOR_FLOOR_2             66

    #define ENTITY_GUN_SHOTGUN              85

    #define ENTITY_AMMO_UZI                 91
    #define ENTITY_AMMO_SHOTGUN             89
    #define ENTITY_AMMO_MAGNUM              90

    #define ENTITY_HOLE_PUZZLE              118
    #define ENTITY_HOLE_KEY                 137
    #define ENTITY_VIEW_TARGET              169

    #pragma pack(push, 1)

    struct fixed {
        uint16  L;
        int16   H;
        operator float() const {
            return H + L / 65535.0f;
        }
    };

    struct RGB {
        uint8 r, g, b;
    };

    struct RGBA {
        uint8 r, g, b, a;
    };

    struct Vertex {
        int16 x, y, z;

        operator vec3() const { return vec3((float)x, (float)y, (float)z); };
    };

    struct Rectangle {
        uint16 vertices[4];
        uint16 texture;     // 15 bit - double-sided
    };

    struct Triangle {
        uint16 vertices[3];
        uint16 texture;
    };

    struct Tile8 {
        uint8 index[256 * 256];
    };

    struct Room {

        struct Info {
            int32 x, z;
            int32 yBottom, yTop;
        } info;

        struct Data {
            uint32      size;       // Number of data words (uint16_t's)

            int16       vCount;
            int16       rCount;
            int16       tCount;
            int16       sCount;

            struct Vertex {
                TR::Vertex  vertex;
                int16       lighting;   // 0 (bright) .. 0x1FFF (dark)
            } *vertices;

            Rectangle   *rectangles;
            Triangle    *triangles;

            struct Sprite {
                int16       vertex;
                int16       texture;
            } *sprites;
        } data;

        uint16  portalsCount;
        uint16  zSectors;
        uint16  xSectors;
        uint16  ambient;    // 0 (bright) .. 0x1FFF (dark)
        uint16  lightsCount;
        uint16  meshesCount;
        int16   alternateRoom;
        int16   flags;

        struct Portal {
            uint16  roomIndex;
            Vertex  normal;
            Vertex  vertices[4];
        } *portals;

        struct Sector {
            uint16  floorIndex; // Index into FloorData[]
            uint16  boxIndex;   // Index into Boxes[] (-1 if none)
            uint8   roomBelow;  // 255 is none
            int8    floor;      // Absolute height of floor * 256
            uint8   roomAbove;  // 255 if none
            int8    ceiling;    // Absolute height of ceiling * 256
        } *sectors;

        struct Light {
            int32   x, y, z;
            uint16  align;          // ! not exists in file !
            uint16  intensity;
            uint32  attenuation;
        } *lights;

        struct Mesh {
            int32   x, y, z;
            uint16  rotation;
            uint16  intensity;
            uint16  meshID;
            uint16  flags;          // ! not exists in file !
        } *meshes;
    };

    union FloorData {
        uint16 data;
        struct Command {
            uint16 func:8, sub:7, end:1;
        } cmd;
        struct Slant {
            int8 x:8, z:8;
        } slant;
        struct TriggerInfo {
            uint16  timer:8, once:1, mask:5, :2;
        } triggerInfo;
        struct TriggerCommand {
            uint16 args:10, func:5, end:1;
        } triggerCmd;
    };

    struct Overlap {
        uint16 boxIndex:15, end:1;
    };

    struct Collider {
        uint16 radius:10, info:6;
        uint16 flags:16;
    };

    struct Mesh {
        Vertex      center;
        Collider    collider;

        uint16      vCount;
        Vertex      *vertices;  // List of vertices (relative coordinates)
 
        int16       nCount;
        union {
            Vertex  *normals;
            int16   *lights;    // if nCount < 0 -> (abs(nCount))
        };

        uint16      rCount;
        Rectangle   *rectangles;

        uint16      tCount;
        Triangle    *triangles;

        uint16      crCount;
        Rectangle   *crectangles;

        uint16      ctCount;
        Triangle    *ctriangles;
    };

    struct Entity {
        int16   id;             // Object Identifier (matched in Models[], or SpriteSequences[], as appropriate)
        int16   room;           // which room contains this item
        int32   x, y, z;        // world coords
        int16   rotation;       // ((0xc000 >> 14) * 90) degrees
        int16   intensity;      // (constant lighting; -1 means use mesh lighting)
        uint16  flags;          // 0x0100 indicates "initially invisible", 0x3e00 is Activation Mask
                                // 0x3e00 indicates "open" or "activated";  these can be XORed with
                                // related FloorData::FDlist fields (e.g. for switches)
    // not exists in file
        uint16  align;
        void    *controller;    // Controller implementation or NULL 
    };

    struct Animation {
        uint32  frameOffset;    // Byte offset into Frames[] (divide by 2 for Frames[i])
        uint8   frameRate;      // Engine ticks per frame
        uint8   frameSize;      // Number of int16_t's in Frames[] used by this animation

        uint16  state;

        fixed   speed;
        fixed   accel;

        uint16  frameStart;     // First frame in this animation
        uint16  frameEnd;       // Last frame in this animation
        uint16  nextAnimation;
        uint16  nextFrame;

        uint16  scCount;
        uint16  scOffset;       // Offset into StateChanges[]

        uint16  acCount;        // How many of them to use.
        uint16  animCommand;    // Offset into AnimCommand[]
    };

    struct AnimState {
        uint16  state;
        uint16  rangesCount;    // number of ranges
        uint16  rangesOffset;   // Offset into animRanges[]
    };

    struct AnimRange {
        int16   low;            // Lowest frame that uses this range
        int16   high;           // Highest frame that uses this range
        int16   nextAnimation;  // Animation to dispatch to
        int16   nextFrame;      // Frame offset to dispatch to
    };

    struct MinMax {
        int16 minX, maxX, minY, maxY, minZ, maxZ;

        vec3 min() const { return vec3((float)minX, (float)minY, (float)minZ); }
        vec3 max() const { return vec3((float)maxX, (float)maxY, (float)maxZ); }
    };

    struct AnimFrame {
        MinMax  box;
        Vertex  pos;   // Starting offset for this model
        int16   aCount;
        uint16  angles[0];          // angle frames in YXZ order

        vec3 getAngle(int index) {
            #define ANGLE_SCALE (2.0f * PI / 1024.0f)

            uint16 b = angles[index * 2 + 0];
            uint16 a = angles[index * 2 + 1];

            return vec3((a & 0x3FF0) >> 4, ( ((a & 0x000F) << 6) | ((b & 0xFC00) >> 10)), b & 0x03FF) * ANGLE_SCALE;
        }
    };

    struct AnimTexture {
        int16   count;        // number of texture offsets - 1 in group
        int16   textures[0];  // offsets into objectTextures[]
    };

    struct Node {
        uint32  flags;
        int32   x, y, z;
    };

    struct Model {
        uint32  id;         // Item Identifier (matched in Entities[])
        uint16  mCount;     // number of meshes in this object
        uint16  mStart;     // stating mesh (offset into MeshPointers[])
        uint32  node;       // offset into MeshTree[]
        uint32  frame;      // byte offset into Frames[] (divide by 2 for Frames[i])
        uint16  animation;  // offset into Animations[]
        uint16  align;      // ! not exists in file !
    };

    struct StaticMesh {
        uint32  id;             // Static Mesh Identifier
        uint16  mesh;           // Mesh (offset into MeshPointers[])
        MinMax  box[2];         // visible (minX, maxX, minY, maxY, minZ, maxZ) & collision
        uint16  flags;

        void getBox(bool collision, int rotation, vec3 &min, vec3 &max) {
            int k = rotation / 16384;

            MinMax &m = box[collision];

            ASSERT(m.minX <= m.maxX && m.minY <= m.maxY && m.minZ <= m.maxZ);

            switch (k) {
                case 0 : 
                    min = vec3(m.minX, m.minY, m.minZ);
                    max = vec3(m.maxX, m.maxY, m.maxZ);
                    break;
                case 1 : 
                    min = vec3(m.minZ, m.minY, -m.maxX);
                    max = vec3(m.maxZ, m.maxY, -m.minX);
                    break;
                case 2 : 
                    min = vec3(-m.maxX, m.minY, -m.maxZ);
                    max = vec3(-m.minX, m.maxY, -m.minZ);
                    break;
                case 3 : 
                    min = vec3(-m.maxZ, m.minY, m.minX);
                    max = vec3(-m.minZ, m.maxY, m.maxX);
                    break;
                default :
                    ASSERT(false);
            }
            ASSERT(min.x <= max.x && min.y <= max.y && min.z <= max.z);
        }
    };

    struct Tile {
        uint16 index:14, undefined:1, triangle:1;  // undefined - need check is animated, animated - is animated
    };

    struct ObjectTexture  {
        uint16  attribute;  // 0 - opaque, 1 - transparent, 2 - blend additive
        Tile    tile;       // 0..14 - tile, 15 - is triangle
        struct {
            uint8   Xcoordinate; // 1 if Xpixel is the low value, 255 if Xpixel is the high value in the object texture
            uint8   Xpixel;
            uint8   Ycoordinate; // 1 if Ypixel is the low value, 255 if Ypixel is the high value in the object texture
            uint8   Ypixel;
        } vertices[4]; // The four corners of the texture
    };

    struct SpriteTexture {
        uint16  tile;
        uint8   u, v;
        uint16  w, h;   // (ActualValue  * 256) + 255
        int16   l, t, r, b;
    };

    struct SpriteSequence {
        int32   id;         // Sprite identifier
        int16   sCount;     // Negative of ``how many sprites are in this sequence''
        int16   sStart;     // Where (in sprite texture list) this sequence starts
    };

    struct Camera {
        int32   x, y, z;
        int16   room;
        uint16  flags;
    };

    struct CameraFrame {
        int16   rotY;
        int16   rotZ;
        int16   unused1;
        int16   posZ;
        int16   posY;
        int16   posX;
        int16   unknown;
        int16   rotX;
    };

    struct SoundSource {
        int32   x, y, z;    // absolute position of sound source (world coordinates)
        uint16  id;         // internal sample index
        uint16  flags;      // 0x40, 0x80, or 0xC0
    };

    struct Box {
        uint32  minZ, maxZ; // Horizontal dimensions in global units
        uint32  minX, maxX;
        int16   floor;      // Height value in global units
        uint16  overlap;    // Index into Overlaps[].

        bool contains(uint32 x, uint32 z) {
            return x >= minX && x <= maxX && z >= minZ && z <= maxZ;
        }
    };

    struct Zone {
        struct {
            uint16  groundZone1;
            uint16  groundZone2;
            uint16  flyZone;
        } normal, alternate;
    };

    struct SoundInfo {
       uint16 offset;
       uint16 volume;
       uint16 chance;   // If !=0 and ((rand()&0x7fff) > Chance), this sound is not played
       uint16 flags;    // Bits 0-1: Looped flag, bits 2-5: num samples, bits 6-7: UNUSED
    };

    #pragma pack(pop)

    struct Level {
        uint32          version;    // version (4 bytes)

        int32           tilesCount;
        Tile8           *tiles;     // 8-bit (palettized) textiles 256x256

        uint32          unused;     // 32-bit unused value (4 bytes)

        uint16          roomsCount;
        Room            *rooms;

        int32           floorsCount;
        FloorData       *floors;

        int32           meshDataSize;
        uint16          *meshData;

        int32           meshOffsetsCount;
        uint32          *meshOffsets;

        int32           animsCount;
        Animation       *anims;

        int32           statesCount;
        AnimState       *states;

        int32           rangesCount;
        AnimRange       *ranges;

        int32           commandsCount;
        int16           *commands;

        int32           nodesDataSize;
        uint32          *nodesData;

        int32           frameDataSize;
        uint16          *frameData;

        int32           modelsCount;
        Model           *models;

        int32           staticMeshesCount;
        StaticMesh      *staticMeshes;

        int32           objectTexturesCount;
        ObjectTexture   *objectTextures;

        int32           spriteTexturesCount;
        SpriteTexture   *spriteTextures;

        int32           spriteSequencesCount;
        SpriteSequence  *spriteSequences;

        int32           camerasCount;
        Camera          *camera;

        int32           soundSourcesCount;
        SoundSource     *soundSources;

        int32           boxesCount;
        Box             *boxes;
        int32           overlapsCount;
        Overlap         *overlaps;
        Zone            *zones;

        int32           animTexturesDataSize;
        uint16          *animTexturesData;

        int32           entitiesCount;
        Entity          *entities;

        RGB             *palette;

        uint16          cameraFramesCount;
        CameraFrame     *cameraFrames;

        uint16          demoDataSize;
        uint8           *demoData;

        int16           *soundsMap;

        int32           soundsInfoCount;
        SoundInfo       *soundsInfo;

        int32           soundDataSize;
        uint8           *soundData;

        int32           soundOffsetsCount;
        uint32          *soundOffsets;

        Level(Stream &stream) {
        // read version
            stream.read(version);
        // tiles
            stream.read(tiles, stream.read(tilesCount));
            stream.read(unused);
        // rooms
            rooms = new Room[stream.read(roomsCount)];
            for (int i = 0; i < roomsCount; i++) {
                Room &r = rooms[i];
                Room::Data &d = r.data;
            // room info
                stream.read(r.info);
            // room data
                stream.read(d.size);
                int pos = stream.pos;
                stream.read(d.vertices,     stream.read(d.vCount));
                stream.read(d.rectangles,   stream.read(d.rCount));
                stream.read(d.triangles,    stream.read(d.tCount));
                stream.read(d.sprites,      stream.read(d.sCount));
                stream.setPos(pos + d.size * 2);
            // portals
                stream.read(r.portals,  stream.read(r.portalsCount));
            // sectors
                stream.read(r.zSectors);
                stream.read(r.xSectors);
                stream.read(r.sectors, r.zSectors * r.xSectors);
            // ambient light luminance
                stream.read(r.ambient);
            // lights
                r.lights = new Room::Light[stream.read(r.lightsCount)];
                for (int i = 0; i < r.lightsCount; i++) {
                    Room::Light &light = r.lights[i];
                    stream.read(light.x);
                    stream.read(light.y);
                    stream.read(light.z);
                    stream.read(light.intensity);
                    stream.read(light.attenuation);
                }
            //    stream.read(r.lights,   stream.read(r.lightsCount));
            // meshes
                r.meshes = new Room::Mesh[stream.read(r.meshesCount)];
                for (int i = 0; i < r.meshesCount; i++)
                    stream.raw(&r.meshes[i], sizeof(r.meshes[i]) - sizeof(r.meshes[i].flags));
            // misc flags
                stream.read(r.alternateRoom);
                stream.read(r.flags);
            }

        // floors
            stream.read(floors,         stream.read(floorsCount));
        // meshes
            stream.read(meshData,       stream.read(meshDataSize));
            stream.read(meshOffsets,    stream.read(meshOffsetsCount));
        // animations
            stream.read(anims,          stream.read(animsCount));
            stream.read(states,         stream.read(statesCount));
            stream.read(ranges,         stream.read(rangesCount));
            stream.read(commands,       stream.read(commandsCount));
            stream.read(nodesData,      stream.read(nodesDataSize));
            stream.read(frameData,      stream.read(frameDataSize));
        // models
            models = new Model[stream.read(modelsCount)];
            for (int i = 0; i < modelsCount; i++)
                stream.raw(&models[i], sizeof(models[i]) - sizeof(models[i].align));
            stream.read(staticMeshes,   stream.read(staticMeshesCount));
        // textures & UV
            stream.read(objectTextures,     stream.read(objectTexturesCount));
            stream.read(spriteTextures,     stream.read(spriteTexturesCount));
            stream.read(spriteSequences,    stream.read(spriteSequencesCount));

        #ifdef TR1_DEMO
            stream.read(palette,        256);
        #endif

        // cameras
            stream.read(camera,         stream.read(camerasCount));
        // sound sources
            stream.read(soundSources,   stream.read(soundSourcesCount));
        // AI
            stream.read(boxes,          stream.read(boxesCount));
            stream.read(overlaps,       stream.read(overlapsCount));
            stream.read(zones,          boxesCount);
        // animated textures
            stream.read(animTexturesData,   stream.read(animTexturesDataSize));
        // entities (enemies, items, lara etc.)
            entities = new Entity[stream.read(entitiesCount)];
            for (int i = 0; i < entitiesCount; i++) {
                stream.raw(&entities[i], sizeof(entities[i]) - sizeof(entities[i].align) - sizeof(entities[i].controller));
                entities[i].align = 0;
                entities[i].controller = NULL;
            }
        // palette
            stream.seek(32 * 256);  // skip lightmap palette

        #ifndef TR1_DEMO
            stream.read(palette,        256);
        #endif

        // cinematic frames for cameras
            stream.read(cameraFrames,   stream.read(cameraFramesCount));
        // demo data
            stream.read(demoData,       stream.read(demoDataSize));
        // sounds
            stream.read(soundsMap,      256);
            stream.read(soundsInfo,     stream.read(soundsInfoCount));
            stream.read(soundData,      stream.read(soundDataSize));
            stream.read(soundOffsets,   stream.read(soundOffsetsCount));

        // modify palette colors from 6-bit Amiga colorspace
            int m = 0;
            for (int i = 0; i < 256; i++) {
                RGB &c = palette[i];
                c.r <<= 2;
                c.g <<= 2;
                c.b <<= 2;
            }
        }

        ~Level() {
            delete[] tiles;
        // rooms
            for (int i = 0; i < roomsCount; i++) {
                Room &r = rooms[i];
                delete[] r.data.vertices;
                delete[] r.data.rectangles;
                delete[] r.data.triangles;
                delete[] r.data.sprites;
                delete[] r.portals;
                delete[] r.sectors;
                delete[] r.lights;
                delete[] r.meshes;
            }
            delete[] rooms;
            delete[] floors;
            delete[] meshData;
            delete[] meshOffsets;
            delete[] anims;
            delete[] states;
            delete[] ranges;
            delete[] commands;
            delete[] nodesData;
            delete[] frameData;
            delete[] models;
            delete[] staticMeshes;
            delete[] objectTextures;
            delete[] spriteTextures;
            delete[] spriteSequences;
            delete[] camera;
            delete[] soundSources;
            delete[] boxes;
            delete[] overlaps;
            delete[] zones;
            delete[] animTexturesData;
            delete[] entities;
            delete[] palette;
            delete[] cameraFrames;
            delete[] demoData;
            delete[] soundsMap;
            delete[] soundsInfo;
            delete[] soundData;
            delete[] soundOffsets;
        }

    // common methods

        StaticMesh* getMeshByID(int id) const { // TODO: map this
            for (int i = 0; i < staticMeshesCount; i++)
                if (staticMeshes[i].id == id)
                    return &staticMeshes[i];
            return NULL;
        }

        struct FloorInfo {
            int floor, ceiling;
            int roomNext, roomBelow, roomAbove;
            int floorIndex;
            bool kill;
            int trigger;
            FloorData::TriggerInfo trigInfo;
            FloorData::TriggerCommand trigCmd[16];
            int trigCmdCount;
        };

        Room::Sector& getSector(int roomIndex, int x, int z, int &dx, int &dz) const {
            ASSERT(roomIndex >= 0 && roomIndex < roomsCount);
            Room &room = rooms[roomIndex];

            int sx = x - room.info.x;
            int sz = z - room.info.z;

            sx = clamp(sx, 0, (room.xSectors - 1) * 1024);
            sz = clamp(sz, 0, (room.zSectors - 1) * 1024);

            dx = sx % 1024;
            dz = sz % 1024;
            sx /= 1024;
            sz /= 1024;

            return room.sectors[sx * room.zSectors + sz];
        }

        void getFloorInfo(int roomIndex, int x, int z, FloorInfo &info) const {
            int dx, dz;
            Room::Sector &s = getSector(roomIndex, x, z, dx, dz);

            info.floor        = 256 * (int)s.floor;
            info.ceiling      = 256 * (int)s.ceiling;
            info.roomNext     = 255;
            info.roomBelow    = s.roomBelow;
            info.roomAbove    = s.roomAbove;
            info.floorIndex   = s.floorIndex;
            info.kill         = false;
            info.trigger      = -1;
            info.trigCmdCount = 0;

            if (!s.floorIndex) return;

            FloorData *fd = &floors[s.floorIndex];
            FloorData::Command cmd;

            do {
                cmd = (*fd++).cmd;
                
                switch (cmd.func) {

                    case FD_PORTAL  :
                        info.roomNext = (*fd++).data;
                        break;

                    case FD_FLOOR   : // floor & ceiling
                    case FD_CEILING : { 
                        FloorData::Slant slant = (*fd++).slant;
                        int sx = (int)slant.x;
                        int sz = (int)slant.z;
                        if (cmd.func == FD_FLOOR) {
                            info.floor -= sx * (sx > 0 ? (dx - 1024) : dx) >> 2;
                            info.floor -= sz * (sz > 0 ? (dz - 1024) : dz) >> 2;
                        } else {
                            info.ceiling -= sx * (sx < 0 ? (dx - 1024) : dx) >> 2; 
                            info.ceiling += sz * (sz > 0 ? (dz - 1024) : dz) >> 2; 
                        }
                        break;
                    }

                    case FD_TRIGGER :  {
                        info.trigger        = cmd.sub;
                        info.trigCmdCount   = 0;
                        info.trigInfo       = (*fd++).triggerInfo;
                        FloorData::TriggerCommand trigCmd;
                        do {
                            trigCmd = (*fd++).triggerCmd; // trigger action
                            info.trigCmd[info.trigCmdCount++] = trigCmd;
                            switch (trigCmd.func) {
                                case  0 : break; // activate item
                                case  1 : break; // switch to camera
                                case  2 : break; // camera delay
                                case  3 : break; // flip map
                                case  4 : break; // flip on
                                case  5 : break; // flip off
                                case  6 : break; // look at item
                                case  7 : break; // end level
                                case  8 : break; // play soundtrack
                                case  9 : break; // special hadrdcode trigger
                                case 10 : break; // secret found
                                case 11 : break; // clear bodies
                                case 12 : break; // flyby camera sequence
                                case 13 : break; // play cutscene
                            }
                            // ..
                        } while (!trigCmd.end);                       
                        break;
                    }

                    case FD_KILL :
                        info.kill = true;
                        break;

                    default : LOG("unknown func: %d\n", cmd.func);
                }

            } while (!cmd.end);
        }

    }; // struct Level
}

#endif