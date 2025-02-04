#include "debug_ui.h"
#include "common.h"

// TODO: use decomp def
extern void warpPlayer(s32 warpIndex, s32 param2);

struct WarpEntry {
    s32 idx;
    char *name;
};

static struct WarpEntry warpEntries[] = {
    //{ 0, "0" }, // Exists but drops into void
    { 2, "2: Ice Mountain" },
    { 5, "5: Warlock Mountain Back" },
    { 6, "6: Warlock Mountain Front" },
    { 12, "12: Cell" },
    { 14, "14: SwapStone Circle" },
    { 15, "15: SwapStone Hollow" },
    { 25, "25: Warlock Mountain" },
    { 26, "26: Ice Mountain" },
    { 29, "29: Boss Galadon" },
    { 30, "30: Boss Galadon Mouth" },
    { 31, "31: Desert" },
    { 34, "34: Warlock Mountain" },
    { 35, "35: Warlock Mountain" },
    { 36, "36: Trial" },
    { 37, "37: Trial" },
    { 38, "38: Trial" },
    { 39, "39: Trial" },
    { 40, "40: Trial" },
    { 41, "41: Trial" },
    { 42, "42: Trial" },
    { 43, "43: Trial" },
    { 48, "48: Warlock Mountain" },
    { 49, "49: Warlock Mountain" },
    { 50, "50: Warlock Mountain" },
    { 51, "51: Warlock Mountain" },
    { 52, "52: Warlock Mountain" },
    { 53, "53: Warlock Mountain" },
    { 54, "54: Boss Galadon" },
    { 55, "55: Boss Galadon Outro" },
    { 56, "56: Warlock Mountain" },
    { 57, "57: Warlock Mountain" },
    { 58, "58: Warlock Mountain" },
    { 59, "59: Warlock Mountain" },
    { 60, "60: CloudRunner Fortress?" },
    { 61, "61: Inside Galleon" },
    { 63, "63: Warlock Mountain" },
    { 64, "64: Discovery Falls" },
    { 66, "66: Diamond Bay" },
    //{ 68, "68" }, // Exists but drops into void
    { 73, "73: Moon Mountain Pass" },
    { 76, "76: ?" },
    { 78, "78: Warlock Mountain" },
    { 80, "80: Lightfoot Village" },
    { 81, "81: Volcano Force Point" },
    { 82, "82: i forgor what this is called" },
    { 85, "85: SwapStone Circle" },
    { 86, "86: Shop" },
    { 87, "87: Magic Cave" },
    { 88, "88: Dragon Rock Minecarts" },
    { 90, "90: Boss Klanadack" },
    { 91, "91: Walled City" },
    { 92, "92: Boss Galadon Intro" },
    { 95, "95: Northern Wastes" }
};
const u32 WARP_ENTRIES_COUNT = sizeof(warpEntries) / sizeof(struct WarpEntry);
struct WarpEntry *selectedWarpEntry = &warpEntries[0];

void dbgui_warp_cheat_window(s32 *open) {
    if (recomp_dbgui_begin("Warp Cheat", open)) {
        if (recomp_dbgui_begin_combo("Warp Location", selectedWarpEntry->name)) {
            for (u32 i = 0; i < WARP_ENTRIES_COUNT; i++) {
                struct WarpEntry *entry = &warpEntries[i];
                if (recomp_dbgui_selectable(entry->name, entry == selectedWarpEntry)) {
                    selectedWarpEntry = entry;
                }
            }
            recomp_dbgui_end_combo();
        }

        if (recomp_dbgui_button("Warp")) {
            warpPlayer(selectedWarpEntry->idx, /*fade*/FALSE);
        }
    }
    recomp_dbgui_end();
}
