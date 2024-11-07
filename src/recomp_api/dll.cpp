#include <map>

#include "ultramodern/ultramodern.hpp"
#include "librecomp/recomp.h"

static std::map<int, const char*> dllNames = {
    { 0x01, "cmdmenu" },
    { 0x02, "camcontrol" },
    { 0x03, "ANIM" },
    { 0x04, "Race" },
    { 0x05, "AMSEQ1" },
    { 0x05, "AMSEQ2" },
    { 0x06, "AMSFX" },
    { 0x07, "newday" },
    { 0x08, "newfog" },
    { 0x09, "newclouds" },
    { 0x0A, "newstars" },
    { 0x0B, "newlfx" },
    { 0x0C, "minic" },
    { 0x0D, "expgfx" },
    { 0x0E, "modgfx" },
    { 0x0F, "projgfx" },
    { 0x11, "partfx" },
    { 0x12, "objfsa" },
    { 0x14, "SCREENS" },
    { 0x15, "text" },
    { 0x16, "subtitles" },
    { 0x18, "waterfx" },
    { 0x19, "paths" },
    { 0x1A, "CURVES" },
    { 0x1C, "clrscr" },
    { 0x1D, "gplay" },
    { 0x1E, "tasktext" },
    { 0x1F, "Save" },
    { 0x36, "pickup" },
    { 0x38, "putdown" },
    { 0x4A, "picmenu" },
    { 0x4B, "frontend" },
};

extern "C" void load_overlay_by_id(uint32_t id, uint32_t ram_addr);
extern "C" void unload_overlay_by_id(uint32_t id);

extern "C" void recomp_on_dll_load(uint32_t id, uint32_t ram_addr) {
    load_overlay_by_id(id - 1, ram_addr);

    auto dllNameIt = dllNames.find(id);
    if (dllNameIt == dllNames.end()) {
        printf("Loaded DLL %u to address 0x%08X\n", id, ram_addr);
    } else {
        printf("Loaded DLL %u \"%s\" to address 0x%08X\n", id, dllNameIt->second, ram_addr);
    }
}

extern "C" void recomp_on_dll_unload(uint32_t id) {
    unload_overlay_by_id(id - 1);

    auto dllNameIt = dllNames.find(id);
    if (dllNameIt == dllNames.end()) {
        printf("Unloaded DLL %u\n", id);
    } else {
        printf("Unloaded DLL %u \"%s\"\n", id, dllNameIt->second);
    }
}
