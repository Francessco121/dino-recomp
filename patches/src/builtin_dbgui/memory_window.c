#include "debug_ui.h"

#include "sys/memory.h"

void dbgui_memory_window(s32 *open) {
    if (recomp_dbgui_begin("Memory Debug", open)) {
        recomp_dbgui_textf("Total: %.2fk / %fk (%.2f%%)",
            (memMonVal0 + memMonVal1 + memMonVal2) / 1024.0f,
            (gHeapList[0].memAllocated + gHeapList[1].memAllocated + gHeapList[2].memAllocated) / 1024.0f,
            ((f32)(memMonVal0 + memMonVal1 + memMonVal2) / (gHeapList[0].memAllocated + gHeapList[1].memAllocated + gHeapList[2].memAllocated)) * 100.0f);

        recomp_dbgui_textf("\nHeap 1:");
        recomp_dbgui_textf("  Mem: %.2fk / %fk (%.2f%%)", 
            memMonVal0 / 1024.0f, gHeapList[0].memAllocated / 1024.0f, ((f32)memMonVal0 / gHeapList[0].memAllocated) * 100.0f);
        recomp_dbgui_textf("  Blocks: %d / %d (%.2f%%)", gHeapList[0].blockCount, gHeapList[0].maxBlocks,
            ((f32)gHeapList[0].blockCount / gHeapList[0].maxBlocks) * 100.0f);
            
        recomp_dbgui_textf("\nHeap 2:");
        recomp_dbgui_textf("  Mem: %.2fk / %.2fk (%.2f%%)", 
            memMonVal1 / 1024.0f, gHeapList[1].memAllocated / 1024.0f, ((f32)memMonVal1 / gHeapList[1].memAllocated) * 100.0f);
        recomp_dbgui_textf("  Blocks: %d / %d (%.2f%%)", gHeapList[1].blockCount, gHeapList[1].maxBlocks,
            ((f32)gHeapList[1].blockCount / gHeapList[1].maxBlocks) * 100.0f);

        recomp_dbgui_textf("\nHeap 3:");
        recomp_dbgui_textf("  Mem: %.2fk / %.2fk (%.2f%%)", 
            memMonVal2 / 1024.0f, gHeapList[2].memAllocated / 1024.0f, ((f32)memMonVal2 / gHeapList[2].memAllocated) * 100.0f);
        recomp_dbgui_textf("  Blocks: %d / %d (%.2f%%)", gHeapList[2].blockCount, gHeapList[2].maxBlocks,
            ((f32)gHeapList[2].blockCount / gHeapList[2].maxBlocks) * 100.0f);
    }
    recomp_dbgui_end();
}
