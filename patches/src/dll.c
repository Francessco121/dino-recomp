// #include "patches.h"
// #include "patch_helpers.h"
// #include "recomp_funcs.h"
// #include "sys/dll.h"
// #include "sys/fs.h"
// #include "sys/memory.h"
// #include "common.h"

//#define MAX_LOADED_DLLS 128

// extern DLLFile * dll_load_from_tab(u16 id, s32 * sizeOut);
//extern void dll_relocate(DLLFile* dll);

// RECOMP_PATCH u32* dll_load(u16 id, u16 exportCount, s32 arg2)
// {
//     DLLFile * dll;
//     u32 i;
//     u32 totalSize;
//     u32* result;

//     if (id >= 0x8000) {
//         id -= 0x8000;
//         // bank2
//         id += gFile_DLLS_TAB->entries[1].bssSize;       // bank 2 end
//     } else if (id >= 0x2000) {
//         id -= 0x2000;
//         // bank1
//         id += gFile_DLLS_TAB->entries[0].bssSize + 1;   // bank 1 end + 1
//     } else if (id >= 0x1000) {
//         id -= 0x1000;
//         // bank0
//         id += gFile_DLLS_TAB->entries[0].offset + 1;    // bank 0 end + 1
//     }

//     // Check if DLL is already loaded, and if so, increment the reference count
//     for (i = 0; i < gLoadedDLLCount; i++)
//     {
//         if (id == gLoadedDLLList[i].id) {
//             ++gLoadedDLLList[i].refCount;
//             return &gLoadedDLLList[i].exports;
//         }
//     }

//     dll = dll_load_from_tab(id, &totalSize);
//     if (!dll) {
//         return 0;
//     }

//     if (dll->exportCount < exportCount) {
//         free(dll);
//         return 0;
//     }

//     // Find an open slot in the DLL list
//     for (i = 0; i < (u32)gLoadedDLLCount; i++)
//     {
//         if (0xFFFFFFFF == gLoadedDLLList[i].id) {
//             break;
//         }
//     }
    
//     // If no open slots were available, try to add a new slot
//     if (i == gLoadedDLLCount) {
//         if (gLoadedDLLCount == MAX_LOADED_DLLS) {
//             free(dll);
//             return 0;
//         }

//         ++gLoadedDLLCount;
//     }

//     gLoadedDLLList[i].id = id;
//     gLoadedDLLList[i].exports = dll->exports;
//     gLoadedDLLList[i].end = (u32 *)((u32)dll + totalSize);
//     gLoadedDLLList[i].refCount = 1;
//     result = &gLoadedDLLList[i].exports;

//     if (arg2 != 0) {
//         dll->ctor((u32)dll);
//     }

//     return result;
// }

// RECOMP_PATCH DLLFile * dll_load_from_tab(u16 id, s32 * sizeOut)
// {
//     DLLFile * dll;
//     s32 offset;
//     s32 dllSize; // t0
//     s32 bssSize;

//     id++;
//     offset = ((DLLTab*)((u8*)gFile_DLLS_TAB + id * 2 * 4u))->entries[0].offset;
//     dllSize = ((DLLTab*)((u8*)gFile_DLLS_TAB + id * 2 * 4u))->entries[1].offset - offset;
//     bssSize = ((DLLTab*)((u8*)gFile_DLLS_TAB + id * 2 * 4u))->entries[0].bssSize;

//     dll = malloc((u32)(dllSize + bssSize), ALLOC_TAG_DLL_COL, NULL);
//     if (dll != NULL) {
//         read_file_region(DLLS_BIN, dll, offset, dllSize);
//     }

//     if (dll != NULL)
//     {
//         if (bssSize != 0) {
//             bzero((u32)dll + dllSize, bssSize);
//         }

//         dll_relocate(dll);
//         osInvalICache(dll, 0x4000);
//         osInvalDCache(dll, 0x4000);

//         *sizeOut = dllSize + bssSize;
//     }

//     // @recomp Load DLL
//     recomp_load_overlay_by_id(id - 2, (void*)((u8*)dll + dll->code));

//     return dll;
// }
