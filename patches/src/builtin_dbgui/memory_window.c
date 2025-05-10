#include "dbgui.h"

#include "sys/memory.h"

static u32 address = 0x80000000;

static void heap_tab() {
    dbgui_textf("Total: %.2fk / %.2ffk (%.2f%%)",
        (memMonVal0 + memMonVal1 + memMonVal2) / 1024.0f,
        (gHeapList[0].memAllocated + gHeapList[1].memAllocated + gHeapList[2].memAllocated) / 1024.0f,
        ((f32)(memMonVal0 + memMonVal1 + memMonVal2) / (gHeapList[0].memAllocated + gHeapList[1].memAllocated + gHeapList[2].memAllocated)) * 100.0f);

    dbgui_textf("\nHeap 1:");
    dbgui_textf("  Mem: %.2fk / %.2ffk (%.2f%%)", 
        memMonVal0 / 1024.0f, gHeapList[0].memAllocated / 1024.0f, ((f32)memMonVal0 / gHeapList[0].memAllocated) * 100.0f);
    dbgui_textf("  Blocks: %d / %d (%.2f%%)", gHeapList[0].blockCount, gHeapList[0].maxBlocks,
        ((f32)gHeapList[0].blockCount / gHeapList[0].maxBlocks) * 100.0f);
        
    dbgui_textf("\nHeap 2:");
    dbgui_textf("  Mem: %.2fk / %.2fk (%.2f%%)", 
        memMonVal1 / 1024.0f, gHeapList[1].memAllocated / 1024.0f, ((f32)memMonVal1 / gHeapList[1].memAllocated) * 100.0f);
    dbgui_textf("  Blocks: %d / %d (%.2f%%)", gHeapList[1].blockCount, gHeapList[1].maxBlocks,
        ((f32)gHeapList[1].blockCount / gHeapList[1].maxBlocks) * 100.0f);

    dbgui_textf("\nHeap 3:");
    dbgui_textf("  Mem: %.2fk / %.2fk (%.2f%%)", 
        memMonVal2 / 1024.0f, gHeapList[2].memAllocated / 1024.0f, ((f32)memMonVal2 / gHeapList[2].memAllocated) * 100.0f);
    dbgui_textf("  Blocks: %d / %d (%.2f%%)", gHeapList[2].blockCount, gHeapList[2].maxBlocks,
        ((f32)gHeapList[2].blockCount / gHeapList[2].maxBlocks) * 100.0f);
}

static void memory_viewer_tab() {
    const static DbgUiInputIntOptions addressInputOptions = {
        .step = 0x8,
        .stepFast = 0x8 * 20,
        .flags = DBGUI_INPUT_TEXT_FLAGS_CharsHexadecimal
    };
    if (dbgui_input_int_ext("Address", (s32*)&address, &addressInputOptions)) {
        if ((u32)address < 0x80000000) {
            address = 0x80000000;
        } else if ((u32)address >= (0x80800000 - (2 * 4))) {
            address = 0x80800000 - (2 * 4);
        }
    }

    for (int i = 0; i < 20; i++) {
        u8 *addr = ((u8*)address) + (i * 2 * 4);
        if ((u32)addr < 0x80000000 || (u32)addr >= (0x80800000 - (2 * 4))) {
            continue;
        }

        dbgui_textf("%08X:  %02X %02X %02X %02X  %02X %02X %02X %02X", (u32)addr, 
            addr[0], addr[1], addr[2], addr[3],
            addr[4], addr[5], addr[6], addr[7]);
    }
}

void dbgui_memory_window(s32 *open) {
    if (dbgui_begin("Memory Debug", open)) {
        if (dbgui_begin_tab_bar("mem_tabs")) {
            if (dbgui_begin_tab_item("Heap", NULL)) {
                heap_tab();
                dbgui_end_tab_item();
            }
            if (dbgui_begin_tab_item("RDRAM", NULL)) {
                memory_viewer_tab();
                dbgui_end_tab_item();
            }
            
            dbgui_end_tab_bar();
        }
    }
    dbgui_end();
}
