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
recomp_get_pending_warp = 0x8F000020;
recomp_dbgui_begin = 0x8F000024;
recomp_dbgui_end = 0x8F000028;
recomp_dbgui_label_text = 0x8F00002C;
bcopy_recomp = 0x8F000030;
recomp_dbgui_ui_frame_begin = 0x8F000034;
recomp_dbgui_ui_frame_end = 0x8F000038;
recomp_dbgui_begin_combo = 0x8F00003C;
recomp_dbgui_end_combo = 0x8F000040;
recomp_dbgui_selectable = 0x8F000044;
recomp_dbgui_button = 0x8F000048;
recomp_dbgui_is_open = 0x8F00004C;
recomp_dbgui_begin_main_menu_bar = 0x8F000050;
recomp_dbgui_end_main_menu_bar = 0x8F000054;
recomp_dbgui_begin_menu = 0x8F000058;
recomp_dbgui_end_menu = 0x8F00005C;
recomp_dbgui_menu_item = 0x8F000060;
recomp_dbgui_text = 0x8F000064;
recomp_dbgui_same_line = 0x8F000068;
recomp_dbgui_collapsing_header = 0x8F00006C;
recomp_dbgui_tree_node = 0x8F000070;
recomp_dbgui_tree_pop = 0x8F000074;
recomp_dbgui_begin_child = 0x8F000078;
recomp_dbgui_end_child = 0x8F00007C;
recomp_dbgui_checkbox = 0x8F000080;
recomp_dbgui_input_int = 0x8F000084;
recomp_dbgui_input_float = 0x8F000088;
recomp_dbgui_is_enabled = 0x8F00008C;
recomp_dbgui_color_float4_to_u32 = 0x8F000090;
recomp_dbgui_foreground_text = 0x8F000094;
recomp_dbgui_foreground_line = 0x8F000098;
recomp_dbgui_foreground_circle = 0x8F00009C;
recomp_dbgui_foreground_circle_filled = 0x8F000100;
recomp_dbgui_foreground_ellipse = 0x8F000104;
recomp_dbgui_foreground_ellipse_filled = 0x8F000108;
recomp_dbgui_foreground_rect = 0x8F00010C;
recomp_dbgui_foreground_rect_filled = 0x8F000110;
recomp_dbgui_is_item_hovered = 0x8F000114;
recomp_dbgui_get_display_size = 0x8F000118;
recomp_eputs = 0x8F00011C;
