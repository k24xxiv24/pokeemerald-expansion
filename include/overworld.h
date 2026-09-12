#ifndef GUARD_OVERWORLD_H
#define GUARD_OVERWORLD_H

#include "constants/map_types.h"

#define LINK_KEY_CODE_NULL 0x00
#define LINK_KEY_CODE_EMPTY 0x11
#define LINK_KEY_CODE_DPAD_DOWN 0x12
#define LINK_KEY_CODE_DPAD_UP 0x13
#define LINK_KEY_CODE_DPAD_LEFT 0x14
#define LINK_KEY_CODE_DPAD_RIGHT 0x15
#define LINK_KEY_CODE_READY 0x16
#define LINK_KEY_CODE_EXIT_ROOM 0x17
#define LINK_KEY_CODE_START_BUTTON 0x18
#define LINK_KEY_CODE_A_BUTTON 0x19
#define LINK_KEY_CODE_IDLE 0x1A

// These two are a hack to stop user input until link stuff can be
// resolved.
#define LINK_KEY_CODE_HANDLE_RECV_QUEUE 0x1B
#define LINK_KEY_CODE_HANDLE_SEND_QUEUE 0x1C
#define LINK_KEY_CODE_EXIT_SEAT 0x1D
#define LINK_KEY_CODE_UNK_8 0x1E

#define MOVEMENT_MODE_FREE 0
#define MOVEMENT_MODE_FROZEN 1
#define MOVEMENT_MODE_SCRIPTED 2

#define SKIP_OBJECT_EVENT_LOAD  1

// trigger a time-of-day blend once
#define HOURS_BLEND_ONCE 25
// don't update gTimeBlend
#define HOURS_FREEZE_BLEND 26

struct InitialPlayerAvatarState
{
    u8 transitionFlags;
    u8 direction;
};

struct LinkPlayerObjectEvent
{
    u8 active;
    u8 linkPlayerId;
    u8 objEventId;
    u8 movementMode;
};

struct CreditsOverworldCmd
{
    s16 unk_0;
    s16 unk_2;
    s16 unk_4;
};

enum {
    MUSIC_DISABLE_OFF,
    MUSIC_DISABLE_STOP,
    MUSIC_DISABLE_KEEP,
};

// Exported RAM declarations
extern struct WarpData gLastUsedWarp;
extern struct LinkPlayerObjectEvent gLinkPlayerObjectEvents[4];

extern u16 *gOverworldTilemapBuffer_Bg2;
extern u16 *gOverworldTilemapBuffer_Bg1;
extern u16 *gOverworldTilemapBuffer_Bg3;
extern u16 gHeldKeyCodeToSend;
extern void (*gFieldCallback)(void);
extern bool8 (*gFieldCallback2)(void);
extern u8 gLocalLinkPlayerId;
extern u8 gFieldLinkPlayerCount;
extern bool8 gExitStairsMovementDisabled;
extern bool8 gSkipShowMonAnim;
extern u8 gTimeOfDay;
extern s16 gTimeUpdateCounter;
extern u8 gDisableMapMusicChangeOnMapLoad;

extern struct TimeBlendSettings gTimeBlend;

extern const struct UCoords32 gDirectionToVectors[];

void DoWhiteOut(void);
void Overworld_ResetStateAfterFly(void);
void Overworld_ResetStateAfterTeleport(void);
void Overworld_ResetStateAfterDigEscRope(void);
void ResetGameStats(void);
void IncrementGameStat(u8 index);
u32 GetGameStat(u8 index);
void SetGameStat(u8 index, u32 value);
void ApplyNewEncryptionKeyToGameStats(u32 newKey);
void LoadObjEventTemplatesFromHeader(void);
void LoadSaveblockObjEventScripts(void);
void SetObjEventTemplateCoords(u8 localId, s16 x, s16 y);
void SetObjEventTemplateMovementType(u8 localId, u8 movementType);
const struct MapLayout *GetMapLayout(u16 mapLayoutId);
void ApplyCurrentWarp(void);
struct MapHeader const *const Overworld_GetMapHeaderByGroupAndId(u16 mapGroup, u16 mapNum);
struct MapHeader const *const GetDestinationWarpMapHeader(void);
void WarpIntoMap(void);
void SetWarpDestination(s8 mapGroup, s8 mapNum, s8 warpId, s8 x, s8 y);
void SetWarpDestinationToMapWarp(s8 mapGroup, s8 mapNum, s8 warpId);
void SetDynamicWarp(s32 unused, s8 mapGroup, s8 mapNum, s8 warpId);
void SetDynamicWarpWithCoords(s32 unused, s8 mapGroup, s8 mapNum, s8 warpId, s8 x, s8 y);
void SetWarpDestinationToDynamicWarp(u8 unusedWarpId);
void SetWarpDestinationToHealLocation(u8 healLocationId);
void SetWarpDestinationToLastHealLocation(void);
void SetWarpDestinationForTeleport(void);
void SetLastHealLocationWarp(u8 healLocationId);
void UpdateEscapeWarp(s16 x, s16 y);
void SetEscapeWarp(s8 mapGroup, s8 mapNum, s8 warpId, s8 x, s8 y);
void SetWarpDestinationToEscapeWarp(void);
void SetFixedDiveWarp(s8 mapGroup, s8 mapNum, s8 warpId, s8 x, s8 y);
void SetFixedHoleWarp(s8 mapGroup, s8 mapNum, s8 warpId, s8 x, s8 y);
void SetWarpDestinationToFixedHoleWarp(s16 x, s16 y);
void SetContinueGameWarpToHealLocation(u8 healLocationId);
void SetContinueGameWarpToDynamicWarp(int unused);
const struct MapConnection *GetMapConnection(u8 dir);
bool8 SetDiveWarpEmerge(u16 x, u16 y);
bool8 SetDiveWarpDive(u16 x, u16 y);
void LoadMapFromCameraTransition(u8 mapGroup, u8 mapNum);
void ResetInitialPlayerAvatarState(void);
void StoreInitialPlayerAvatarState(void);
bool32 Overworld_IsBikingAllowed(void);
void SetDefaultFlashLevel(void);
void SetFlashLevel(s32 flashLevel);
u8 GetFlashLevel(void);
void SetCurrentMapLayout(u16 mapLayoutId);
void SetObjectEventLoadFlag(u8 flag);
u16 GetLocationMusic(struct WarpData *warp);
u16 GetCurrLocationDefaultMusic(void);
u16 GetWarpDestinationMusic(void);
void Overworld_ResetMapMusic(void);
void Overworld_PlaySpecialMapMusic(void);
void Overworld_SetSavedMusic(u16 songNum);
void Overworld_ClearSavedMusic(void);
void Overworld_ChangeMusicToDefault(void);
void Overworld_ChangeMusicTo(u16 newMusic);
u8 GetMapMusicFadeoutSpeed(void);
void TryFadeOutOldMapMusic(void);
bool8 BGMusicStopped(void);
void Overworld_FadeOutMapMusic(void);
void UpdateAmbientCry(s16 *state, u16 *delayCounter);
enum MapType GetMapTypeByGroupAndId(s8 mapGroup, s8 mapNum);
enum MapType GetMapTypeByWarpData(struct WarpData *warp);
enum MapType GetCurrentMapType(void);
enum MapType GetLastUsedWarpMapType(void);
mapsec_u8_t GetLastUsedWarpMapSectionId(void);
bool8 IsMapTypeOutdoors(enum MapType mapType);
bool8 Overworld_MapTypeAllowsTeleportAndFly(enum MapType mapType);
bool8 IsMapTypeIndoors(enum MapType mapType);
mapsec_u8_t GetSavedWarpRegionMapSectionId(void);
mapsec_u8_t GetCurrentRegionMapSectionId(void);
enum MapBattleScene GetCurrentMapBattleScene(void);
void CleanupOverworldWindowsAndTilemaps(void);
bool32 IsOverworldLinkActive(void);
void CB1_Overworld(void);
void CB2_OverworldBasic(void);
void UpdateTimeOfDay(bool32 updateBlend);
bool32 MapHasNaturalLight(enum MapType mapType);
bool32 CurrentMapHasShadows(void);
void UpdateAltBgPalettes(u16 palettes);
void UpdatePalettesWithTime(u32);
void CB2_Overworld(void);
void SetMainCallback1(void (*cb)(void));
void SetUnusedCallback(void *func);
void CB2_NewGame(void);
void CB2_WhiteOut(void);
void CB2_LoadMap(void);
void CB2_ReturnToFieldContestHall(void);
void CB2_ReturnToFieldCableClub(void);
void CB2_ReturnToField(void);
void CB2_ReturnToFieldFromMultiplayer(void);
void CB2_ReturnToFieldWithOpenMenu(void);
void CB2_ReturnToFieldContinueScript(void);
void CB2_ReturnToFieldContinueScriptPlayMapMusic(void);
void CB2_ReturnToFieldFadeFromBlack(void);
void CB2_ContinueSavedGame(void);
void ResetAllMultiplayerState(void);
u32 GetCableClubPartnersReady(void);
u16 SetInCableClubSeat(void);
u16 SetLinkWaitingForScript(void);
u16 QueueExitLinkRoomKey(void);
u16 SetStartedCableClubActivity(void);
bool32 Overworld_IsRecvQueueAtMax(void);
bool32 Overworld_RecvKeysFromLinkIsRunning(void);
bool32 Overworld_SendKeysToLinkIsRunning(void);
bool32 IsSendingKeysOverCable(void);
void ClearLinkPlayerObjectEvents(void);
bool16 SetTimeOfDay(u16 hours);
bool8 MetatileBehavior_IsSurfableInSeafoamIslands(u16 metatileBehavior);

// Item Description Headers
enum ItemObtainFlags
{
    FLAG_GET_ITEM_OBTAINED,
    FLAG_SET_ITEM_OBTAINED,
};
bool8 GetSetItemObtained(enum Item item, enum ItemObtainFlags caseId);

void Overworld_CreditsMainCB(void);
bool32 Overworld_DoScrollSceneForCredits(u8 *, const struct CreditsOverworldCmd *);



static const u8 sMapsecToRegion[] = {
    [MAPSEC_LITTLEROOT_TOWN]            = REGION_HOENN,
    [MAPSEC_OLDALE_TOWN]                = REGION_HOENN,
    [MAPSEC_DEWFORD_TOWN]               = REGION_HOENN,
    [MAPSEC_LAVARIDGE_TOWN]             = REGION_HOENN,
    [MAPSEC_FALLARBOR_TOWN]             = REGION_HOENN,
    [MAPSEC_VERDANTURF_TOWN]            = REGION_HOENN,
    [MAPSEC_PACIFIDLOG_TOWN]            = REGION_HOENN,
    [MAPSEC_PETALBURG_CITY]             = REGION_HOENN,
    [MAPSEC_SLATEPORT_CITY]             = REGION_HOENN,
    [MAPSEC_MAUVILLE_CITY]              = REGION_HOENN,
    [MAPSEC_RUSTBORO_CITY]              = REGION_HOENN,
    [MAPSEC_FORTREE_CITY]               = REGION_HOENN,
    [MAPSEC_LILYCOVE_CITY]              = REGION_HOENN,
    [MAPSEC_MOSSDEEP_CITY]              = REGION_HOENN,
    [MAPSEC_SOOTOPOLIS_CITY]            = REGION_HOENN,
    [MAPSEC_EVER_GRANDE_CITY]           = REGION_HOENN,
    [MAPSEC_ROUTE_101]                  = REGION_HOENN,
    [MAPSEC_ROUTE_102]                  = REGION_HOENN,
    [MAPSEC_ROUTE_103]                  = REGION_HOENN,
    [MAPSEC_ROUTE_104]                  = REGION_HOENN,
    [MAPSEC_ROUTE_105]                  = REGION_HOENN,
    [MAPSEC_ROUTE_106]                  = REGION_HOENN,
    [MAPSEC_ROUTE_107]                  = REGION_HOENN,
    [MAPSEC_ROUTE_108]                  = REGION_HOENN,
    [MAPSEC_ROUTE_109]                  = REGION_HOENN,
    [MAPSEC_ROUTE_110]                  = REGION_HOENN,
    [MAPSEC_ROUTE_111]                  = REGION_HOENN,
    [MAPSEC_ROUTE_112]                  = REGION_HOENN,
    [MAPSEC_ROUTE_113]                  = REGION_HOENN,
    [MAPSEC_ROUTE_114]                  = REGION_HOENN,
    [MAPSEC_ROUTE_115]                  = REGION_HOENN,
    [MAPSEC_ROUTE_116]                  = REGION_HOENN,
    [MAPSEC_ROUTE_117]                  = REGION_HOENN,
    [MAPSEC_ROUTE_118]                  = REGION_HOENN,
    [MAPSEC_ROUTE_119]                  = REGION_HOENN,
    [MAPSEC_ROUTE_120]                  = REGION_HOENN,
    [MAPSEC_ROUTE_121]                  = REGION_HOENN,
    [MAPSEC_ROUTE_122]                  = REGION_HOENN,
    [MAPSEC_ROUTE_123]                  = REGION_HOENN,
    [MAPSEC_ROUTE_124]                  = REGION_HOENN,
    [MAPSEC_ROUTE_125]                  = REGION_HOENN,
    [MAPSEC_ROUTE_126]                  = REGION_HOENN,
    [MAPSEC_ROUTE_127]                  = REGION_HOENN,
    [MAPSEC_ROUTE_128]                  = REGION_HOENN,
    [MAPSEC_ROUTE_129]                  = REGION_HOENN,
    [MAPSEC_ROUTE_130]                  = REGION_HOENN,
    [MAPSEC_ROUTE_131]                  = REGION_HOENN,
    [MAPSEC_ROUTE_132]                  = REGION_HOENN,
    [MAPSEC_ROUTE_133]                  = REGION_HOENN,
    [MAPSEC_ROUTE_134]                  = REGION_HOENN,
    [MAPSEC_UNDERWATER_124]             = REGION_HOENN,
    [MAPSEC_UNDERWATER_126]             = REGION_HOENN,
    [MAPSEC_UNDERWATER_127]             = REGION_HOENN,
    [MAPSEC_UNDERWATER_128]             = REGION_HOENN,
    [MAPSEC_UNDERWATER_SOOTOPOLIS]      = REGION_HOENN,
    [MAPSEC_GRANITE_CAVE]               = REGION_HOENN,
    [MAPSEC_MT_CHIMNEY]                 = REGION_HOENN,
    [MAPSEC_SAFARI_ZONE]                = REGION_HOENN,
    [MAPSEC_BATTLE_FRONTIER]            = REGION_HOENN,
    [MAPSEC_PETALBURG_WOODS]            = REGION_HOENN,
    [MAPSEC_RUSTURF_TUNNEL]             = REGION_HOENN,
    [MAPSEC_ABANDONED_SHIP]             = REGION_HOENN,
    [MAPSEC_NEW_MAUVILLE]               = REGION_HOENN,
    [MAPSEC_METEOR_FALLS]               = REGION_HOENN,
    [MAPSEC_METEOR_FALLS2]              = REGION_HOENN,
    [MAPSEC_MT_PYRE]                    = REGION_HOENN,
    [MAPSEC_AQUA_HIDEOUT_OLD]           = REGION_HOENN,
    [MAPSEC_SHOAL_CAVE]                 = REGION_HOENN,
    [MAPSEC_SEAFLOOR_CAVERN]            = REGION_HOENN,
    [MAPSEC_UNDERWATER_SEAFLOOR_CAVERN] = REGION_HOENN,
    [MAPSEC_VICTORY_ROAD]               = REGION_HOENN,
    [MAPSEC_MIRAGE_ISLAND]              = REGION_HOENN,
    [MAPSEC_CAVE_OF_ORIGIN]             = REGION_HOENN,
    [MAPSEC_SOUTHERN_ISLAND]            = REGION_HOENN,
    [MAPSEC_FIERY_PATH]                 = REGION_HOENN,
    [MAPSEC_FIERY_PATH2]                = REGION_HOENN,
    [MAPSEC_JAGGED_PASS]                = REGION_HOENN,
    [MAPSEC_JAGGED_PASS2]               = REGION_HOENN,
    [MAPSEC_SEALED_CHAMBER]             = REGION_HOENN,
    [MAPSEC_UNDERWATER_SEALED_CHAMBER]  = REGION_HOENN,
    [MAPSEC_SCORCHED_SLAB]              = REGION_HOENN,
    [MAPSEC_ISLAND_CAVE]                = REGION_HOENN,
    [MAPSEC_DESERT_RUINS]               = REGION_HOENN,
    [MAPSEC_ANCIENT_TOMB]               = REGION_HOENN,
    [MAPSEC_INSIDE_OF_TRUCK]            = REGION_HOENN,
    [MAPSEC_SKY_PILLAR]                 = REGION_HOENN,
    [MAPSEC_SECRET_BASE]                = REGION_HOENN,
    [MAPSEC_DYNAMIC]                    = REGION_HOENN,
    [MAPSEC_PALLET_TOWN]                = REGION_KANTO,
    [MAPSEC_VIRIDIAN_CITY]              = REGION_KANTO,
    [MAPSEC_PEWTER_CITY]                = REGION_KANTO,
    [MAPSEC_CERULEAN_CITY]              = REGION_KANTO,
    [MAPSEC_LAVENDER_TOWN]              = REGION_KANTO,
    [MAPSEC_VERMILION_CITY]             = REGION_KANTO,
    [MAPSEC_CELADON_CITY]               = REGION_KANTO,
    [MAPSEC_FUCHSIA_CITY]               = REGION_KANTO,
    [MAPSEC_CINNABAR_ISLAND]            = REGION_KANTO,
    [MAPSEC_INDIGO_PLATEAU]             = REGION_KANTO,
    [MAPSEC_SAFFRON_CITY]               = REGION_KANTO,
    [MAPSEC_ROUTE_1]                    = REGION_KANTO,
    [MAPSEC_ROUTE_2]                    = REGION_KANTO,
    [MAPSEC_ROUTE_3]                    = REGION_KANTO,
    [MAPSEC_ROUTE_4]                    = REGION_KANTO,
    [MAPSEC_ROUTE_5]                    = REGION_KANTO,
    [MAPSEC_ROUTE_6]                    = REGION_KANTO,
    [MAPSEC_ROUTE_7]                    = REGION_KANTO,
    [MAPSEC_ROUTE_8]                    = REGION_KANTO,
    [MAPSEC_ROUTE_9]                    = REGION_KANTO,
    [MAPSEC_ROUTE_10]                   = REGION_KANTO,
    [MAPSEC_ROUTE_11]                   = REGION_KANTO,
    [MAPSEC_ROUTE_12]                   = REGION_KANTO,
    [MAPSEC_ROUTE_13]                   = REGION_KANTO,
    [MAPSEC_ROUTE_14]                   = REGION_KANTO,
    [MAPSEC_ROUTE_15]                   = REGION_KANTO,
    [MAPSEC_ROUTE_16]                   = REGION_KANTO,
    [MAPSEC_ROUTE_17]                   = REGION_KANTO,
    [MAPSEC_ROUTE_18]                   = REGION_KANTO,
    [MAPSEC_ROUTE_19]                   = REGION_KANTO,
    [MAPSEC_ROUTE_20]                   = REGION_KANTO,
    [MAPSEC_ROUTE_21]                   = REGION_KANTO,
    [MAPSEC_ROUTE_22]                   = REGION_KANTO,
    [MAPSEC_ROUTE_23]                   = REGION_KANTO,
    [MAPSEC_ROUTE_24]                   = REGION_KANTO,
    [MAPSEC_ROUTE_25]                   = REGION_KANTO,
    [MAPSEC_VIRIDIAN_FOREST]            = REGION_KANTO,
    [MAPSEC_MT_MOON]                    = REGION_KANTO,
    [MAPSEC_S_S_ANNE]                   = REGION_KANTO,
    [MAPSEC_UNDERGROUND_PATH]           = REGION_KANTO,
    [MAPSEC_UNDERGROUND_PATH_2]         = REGION_KANTO,
    [MAPSEC_DIGLETTS_CAVE]              = REGION_KANTO,
    [MAPSEC_KANTO_VICTORY_ROAD]         = REGION_KANTO,
    [MAPSEC_ROCKET_HIDEOUT]             = REGION_KANTO,
    [MAPSEC_SILPH_CO]                   = REGION_KANTO,
    [MAPSEC_POKEMON_MANSION]            = REGION_KANTO,
    [MAPSEC_KANTO_SAFARI_ZONE]          = REGION_KANTO,
    [MAPSEC_POKEMON_LEAGUE]             = REGION_KANTO,
    [MAPSEC_ROCK_TUNNEL]                = REGION_KANTO,
    [MAPSEC_SEAFOAM_ISLANDS]            = REGION_KANTO,
    [MAPSEC_POKEMON_TOWER]              = REGION_KANTO,
    [MAPSEC_CERULEAN_CAVE]              = REGION_KANTO,
    [MAPSEC_POWER_PLANT]                = REGION_KANTO,
    [MAPSEC_ONE_ISLAND]                 = REGION_SEVII,
    [MAPSEC_TWO_ISLAND]                 = REGION_SEVII,
    [MAPSEC_THREE_ISLAND]               = REGION_SEVII,
    [MAPSEC_FOUR_ISLAND]                = REGION_SEVII,
    [MAPSEC_FIVE_ISLAND]                = REGION_SEVII,
    [MAPSEC_SEVEN_ISLAND]               = REGION_SEVII,
    [MAPSEC_SIX_ISLAND]                 = REGION_SEVII,
    [MAPSEC_KINDLE_ROAD]                = REGION_SEVII,
    [MAPSEC_TREASURE_BEACH]             = REGION_SEVII,
    [MAPSEC_CAPE_BRINK]                 = REGION_SEVII,
    [MAPSEC_BOND_BRIDGE]                = REGION_SEVII,
    [MAPSEC_THREE_ISLE_PORT]            = REGION_SEVII,
    [MAPSEC_RESORT_GORGEOUS]            = REGION_SEVII,
    [MAPSEC_WATER_LABYRINTH]            = REGION_SEVII,
    [MAPSEC_FIVE_ISLE_MEADOW]           = REGION_SEVII,
    [MAPSEC_MEMORIAL_PILLAR]            = REGION_SEVII,
    [MAPSEC_OUTCAST_ISLAND]             = REGION_SEVII,
    [MAPSEC_GREEN_PATH]                 = REGION_SEVII,
    [MAPSEC_WATER_PATH]                 = REGION_SEVII,
    [MAPSEC_RUIN_VALLEY]                = REGION_SEVII,
    [MAPSEC_TRAINER_TOWER]              = REGION_SEVII,
    [MAPSEC_CANYON_ENTRANCE]            = REGION_SEVII,
    [MAPSEC_SEVAULT_CANYON]             = REGION_SEVII,
    [MAPSEC_TANOBY_RUINS]               = REGION_SEVII,
    [MAPSEC_SEVII_ISLE_22]              = REGION_SEVII,
    [MAPSEC_SEVII_ISLE_23]              = REGION_SEVII,
    [MAPSEC_SEVII_ISLE_24]              = REGION_SEVII,
    [MAPSEC_NAVEL_ROCK_FRLG]            = REGION_SEVII,
    [MAPSEC_MT_EMBER]                   = REGION_SEVII,
    [MAPSEC_BERRY_FOREST]               = REGION_SEVII,
    [MAPSEC_ICEFALL_CAVE]               = REGION_SEVII,
    [MAPSEC_ROCKET_WAREHOUSE]           = REGION_SEVII,
    [MAPSEC_TRAINER_TOWER_2]            = REGION_SEVII,
    [MAPSEC_DOTTED_HOLE]                = REGION_SEVII,
    [MAPSEC_LOST_CAVE]                  = REGION_SEVII,
    [MAPSEC_PATTERN_BUSH]               = REGION_SEVII,
    [MAPSEC_ALTERING_CAVE_FRLG]         = REGION_SEVII,
    [MAPSEC_TANOBY_CHAMBERS]            = REGION_SEVII,
    [MAPSEC_THREE_ISLE_PATH]            = REGION_SEVII,
    [MAPSEC_TANOBY_KEY]                 = REGION_SEVII,
    [MAPSEC_BIRTH_ISLAND_FRLG]          = REGION_SEVII,
    [MAPSEC_MONEAN_CHAMBER]             = REGION_SEVII,
    [MAPSEC_LIPTOO_CHAMBER]             = REGION_SEVII,
    [MAPSEC_WEEPTH_CHAMBER]             = REGION_SEVII,
    [MAPSEC_DILFORD_CHAMBER]            = REGION_SEVII,
    [MAPSEC_SCUFIB_CHAMBER]             = REGION_SEVII,
    [MAPSEC_RIXY_CHAMBER]               = REGION_SEVII,
    [MAPSEC_VIAPOIS_CHAMBER]            = REGION_SEVII,
    [MAPSEC_EMBER_SPA]                  = REGION_SEVII,
    [MAPSEC_SPECIAL_AREA]               = REGION_KANTO,
    [MAPSEC_AQUA_HIDEOUT]               = REGION_HOENN,
    [MAPSEC_MAGMA_HIDEOUT]              = REGION_HOENN,
    [MAPSEC_MIRAGE_TOWER]               = REGION_HOENN,
    [MAPSEC_BIRTH_ISLAND]               = REGION_SEVII,
    [MAPSEC_FARAWAY_ISLAND]             = REGION_HOENN,
    [MAPSEC_ARTISAN_CAVE]               = REGION_HOENN,
    [MAPSEC_MARINE_CAVE]                = REGION_HOENN,
    [MAPSEC_UNDERWATER_MARINE_CAVE]     = REGION_HOENN,
    [MAPSEC_TERRA_CAVE]                 = REGION_HOENN,
    [MAPSEC_UNDERWATER_105]             = REGION_HOENN,
    [MAPSEC_UNDERWATER_125]             = REGION_HOENN,
    [MAPSEC_UNDERWATER_129]             = REGION_HOENN,
    [MAPSEC_DESERT_UNDERPASS]           = REGION_HOENN,
    [MAPSEC_ALTERING_CAVE]              = REGION_HOENN,
    [MAPSEC_NAVEL_ROCK]                 = REGION_SEVII,
    [MAPSEC_TRAINER_HILL]               = REGION_HOENN
};

#endif // GUARD_OVERWORLD_H
