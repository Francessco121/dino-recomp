__start = 0x80000000;

/* Dummy addresses that get recompiled into function calls */
recomp_puts = 0x8F000000;
malloc_recomp = 0x8F000004;
read_file_region_recomp = 0x8F000008;
bzero_recomp = 0x8F00000C;
dll_relocate_recomp = 0x8F000010;
osInvalICache_recomp = 0x8F000014;
osInvalDCache_recomp = 0x8F000018;
recomp_load_overlay_by_id = 0x8F00001C;
