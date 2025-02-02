#ifndef OBJ_ZONE_H
#define OBJ_ZONE_H

#include "GameAPI/Game.h"

// Macro to reduce ifdefs needed when calling RandSeeded with Zone->randSeed, ensures easy pre-plus compatibility
#if MANIA_USE_PLUS
#define ZONE_RAND(min, max) RSDK.RandSeeded(min, max, &Zone->randSeed)
#else
#define ZONE_RAND(min, max) RSDK.Rand(min, max)
#endif

#define Zone_AddVSSwapCallback(callback)                                                                                                             \
    if (Zone->vsSwapCBCount < 0x10) {                                                                                                                \
        Zone->vsSwapCB[Zone->vsSwapCBCount] = callback;                                                                                              \
        ++Zone->vsSwapCBCount;                                                                                                                       \
    }

typedef enum {
    ZONE_INVALID = -1,
    ZONE_GHZ,
    ZONE_CPZ,
    ZONE_SPZ,
    ZONE_FBZ,
    ZONE_PGZ,
    ZONE_SSZ,
    ZONE_HCZ,
    ZONE_MSZ,
    ZONE_OOZ,
    ZONE_LRZ,
    ZONE_MMZ,
    ZONE_TMZ,
    ZONE_ERZ,
#if MANIA_USE_PLUS
    ZONE_AIZ,
#endif
    // total zone count
    ZONE_COUNT,
    // zone count for save files
    ZONE_COUNT_SAVEFILE = ZONE_ERZ + 1,
} ZoneIDs;

// Object Class
typedef struct {
    RSDK_OBJECT
    int32 actID;
    StateMachine(stageFinishCallback);
    bool32 shouldRecoverPlayers; // a little misleading, forces the player on-screen before an act transition if enabled
    StateMachine(vsSwapCB[0x10]);
    int32 vsSwapCBCount;
#if MANIA_USE_PLUS
    int32 playerSwapEnabled[PLAYER_COUNT];
    uint8 swapPlayerID;
    uint8 swapPlayerCount;
    uint8 preSwapPlayerIDs[PLAYER_COUNT];
    uint8 swappedPlayerIDs[PLAYER_COUNT];
#else
    bool32 playerSwapEnabled;
#endif
    int32 listPos;
    int32 prevListPos;
    int32 ringFrame;
    int32 timer;
    int32 persistentTimer;
    int32 cameraBoundsL[PLAYER_COUNT];
    int32 cameraBoundsR[PLAYER_COUNT];
    int32 cameraBoundsT[PLAYER_COUNT];
    int32 cameraBoundsB[PLAYER_COUNT];
    int32 playerBoundsL[PLAYER_COUNT];
    int32 playerBoundsR[PLAYER_COUNT];
    int32 playerBoundsT[PLAYER_COUNT];
    int32 playerBoundsB[PLAYER_COUNT];
    int32 deathBoundary[PLAYER_COUNT];
    int32 playerBoundActiveL[PLAYER_COUNT];
    int32 playerBoundActiveR[PLAYER_COUNT];
    int32 playerBoundActiveT[PLAYER_COUNT];
    int32 playerBoundActiveB[PLAYER_COUNT];
    int32 autoScrollSpeed;
    bool32 setATLBounds;
    bool32 gotTimeOver;
    StateMachine(timeOverCallback);
    uint16 collisionLayers;
    uint16 fgLayer[2]; // { lowPriority, highPriority }
    uint16 moveLayer;
#if MANIA_USE_PLUS
    uint16 scratchLayer;
#endif
    uint16 fgLayerMask[2]; // { lowPriority, highPriority }
    uint16 moveLayerMask;
    uint8 fgDrawGroup[2];     // { lowPriority, highPriority }
    uint8 objectDrawGroup[2]; // { lowPriority, highPriority }
    uint8 playerDrawGroup[2]; // { lowPriority, highPriority }
    uint8 hudDrawGroup;
    uint16 sfxFail;
#if MANIA_USE_PLUS
    EntityBase entityStorage[16];
    int32 screenPosX[PLAYER_COUNT];
    int32 screenPosY[PLAYER_COUNT];
    bool32 swapGameMode;
    bool32 teleportActionActive;
    int32 randSeed;
#endif
} ObjectZone;

// Object Struct
extern ObjectZone *Zone;

// Extra Entity Functions

extern int32 (*Zone_GetZoneID)(void);
// Fades out & loads the active stage
extern void (*Zone_StartFadeOut)(int32 fadeSpeed, int32 fadeColor);

#endif //! OBJ_ZONE_H
