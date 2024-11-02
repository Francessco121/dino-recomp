#include <filesystem>
#include <fstream>
#include <iomanip>

#include "ultramodern/config.hpp"
#include "librecomp/files.hpp"

#include "dino/config.hpp"
#include "dino/input.hpp"
#include "dino/renderer.hpp"
#include "dino/sound.hpp"

#if defined(_WIN32)
#include <Shlobj.h>
#elif defined(__linux__)
#include <unistd.h>
#include <pwd.h>
#endif

constexpr std::u8string_view general_filename = u8"general.json";
constexpr std::u8string_view graphics_filename = u8"graphics.json";
constexpr std::u8string_view controls_filename = u8"controls.json";
constexpr std::u8string_view sound_filename = u8"sound.json";
constexpr std::u8string_view program_id = u8"DinoPlanetRecompiled";

constexpr auto res_default            = ultramodern::renderer::Resolution::Auto;
constexpr auto hr_default             = ultramodern::renderer::HUDRatioMode::Clamp16x9;
constexpr auto api_default            = ultramodern::renderer::GraphicsApi::Auto;
constexpr auto ar_default             = ultramodern::renderer::AspectRatio::Expand;
constexpr auto msaa_default           = ultramodern::renderer::Antialiasing::MSAA2X;
constexpr auto rr_default             = ultramodern::renderer::RefreshRate::Display;
constexpr auto hpfb_default           = ultramodern::renderer::HighPrecisionFramebuffer::Auto;
constexpr int ds_default              = 1;
constexpr int rr_manual_default       = 60;
constexpr bool developer_mode_default = false;

static bool is_steam_deck = false;

ultramodern::renderer::WindowMode wm_default() {
    return is_steam_deck ? ultramodern::renderer::WindowMode::Fullscreen : ultramodern::renderer::WindowMode::Windowed;
}

#ifdef __gnu_linux__
void detect_steam_deck() {
    // Check if the board vendor is Valve.
    std::ifstream board_vendor_file("/sys/devices/virtual/dmi/id/board_vendor");
    std::string line;
    if (std::getline(board_vendor_file, line).good() && line == "Valve") {
        is_steam_deck = true;
        return;
    }

    // Check if the SteamDeck variable is set to 1.
    const char* steam_deck_env = getenv("SteamDeck");
    if (steam_deck_env != nullptr && std::string{steam_deck_env} == "1") {
        is_steam_deck = true;
        return;
    }

    is_steam_deck = false;
    return;
}
#else
void detect_steam_deck() { is_steam_deck = false; }
#endif

template <typename T>
T from_or_default(const json& j, const std::string& key, T default_value) {
    T ret;
    auto find_it = j.find(key);
    if (find_it != j.end()) {
        find_it->get_to(ret);
    }
    else {
        ret = default_value;
    }
    
    return ret;
}

template <typename T>
void call_if_key_exists(void (*func)(T), const json& j, const std::string& key) {
    auto find_it = j.find(key);
    if (find_it != j.end()) {
        T val;
        find_it->get_to(val);
        func(val);
    }
}

namespace ultramodern {
    void to_json(json& j, const renderer::GraphicsConfig& config) {
        j = json{
            {"res_option",      config.res_option},
            {"wm_option",       config.wm_option},
            {"hr_option",       config.hr_option},
            {"api_option",      config.api_option},
            {"ds_option",       config.ds_option},
            {"ar_option",       config.ar_option},
            {"msaa_option",     config.msaa_option},
            {"rr_option",       config.rr_option},
            {"hpfb_option",     config.hpfb_option},
            {"rr_manual_value", config.rr_manual_value},
            {"developer_mode",  config.developer_mode},
        };
    }

    void from_json(const json& j, renderer::GraphicsConfig& config) {
        config.res_option       = from_or_default(j, "res_option",      res_default);
        config.wm_option        = from_or_default(j, "wm_option",       wm_default());
        config.hr_option        = from_or_default(j, "hr_option",       hr_default);
        config.api_option       = from_or_default(j, "api_option",      api_default);
        config.ds_option        = from_or_default(j, "ds_option",       ds_default);
        config.ar_option        = from_or_default(j, "ar_option",       ar_default);
        config.msaa_option      = from_or_default(j, "msaa_option",     msaa_default);
        config.rr_option        = from_or_default(j, "rr_option",       rr_default);
        config.hpfb_option      = from_or_default(j, "hpfb_option",     hpfb_default);
        config.rr_manual_value  = from_or_default(j, "rr_manual_value", rr_manual_default);
        config.developer_mode   = from_or_default(j, "developer_mode",  developer_mode_default);
    }
}

namespace dino::input {
    void to_json(json& j, const InputField& field) {
        j = json{ {"input_type", field.input_type}, {"input_id", field.input_id} };
    }

    void from_json(const json& j, InputField& field) {
        j.at("input_type").get_to(field.input_type);
        j.at("input_id").get_to(field.input_id);
    }
}

std::filesystem::path dino::config::get_app_folder_path() {
   // directly check for portable.txt (windows and native linux binary)    
   if (std::filesystem::exists("portable.txt")) {
       return std::filesystem::current_path();
   }

   std::filesystem::path recomp_dir{};

#if defined(_WIN32)
   // Deduce local app data path.
   PWSTR known_path = NULL;
   HRESULT result = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &known_path);
   if (result == S_OK) {
       recomp_dir = std::filesystem::path{known_path} / dino::config::program_id;
   }

   CoTaskMemFree(known_path);
#elif defined(__linux__)
   // check for APP_FOLDER_PATH env var used by AppImage
   if (getenv("APP_FOLDER_PATH") != nullptr) {
       return std::filesystem::path{getenv("APP_FOLDER_PATH")};
   }

   const char *homedir;

   if ((homedir = getenv("HOME")) == nullptr) {
       homedir = getpwuid(getuid())->pw_dir;
   }

   if (homedir != nullptr) {
       recomp_dir = std::filesystem::path{homedir} / (std::u8string{u8".config/"} + std::u8string{dino::config::program_id});
   }
#endif

    return recomp_dir;
}

bool read_json(std::ifstream input_file, nlohmann::json& json_out) {
    if (!input_file.good()) {
        return false;
    }

    try {
        input_file >> json_out;
    }
    catch (nlohmann::json::parse_error&) {
        return false;
    }
    return true;
}

bool read_json_with_backups(const std::filesystem::path& path, nlohmann::json& json_out) {
    // Try reading and parsing the base file.
    if (read_json(std::ifstream{path}, json_out)) {
        return true;
    }

    // Try reading and parsing the backup file.
    if (read_json(recomp::open_input_backup_file(path), json_out)) {
        return true;
    }

    // Both reads failed.
    return false;
}

bool save_json_with_backups(const std::filesystem::path& path, const nlohmann::json& json_data) {
    {
        std::ofstream output_file = recomp::open_output_file_with_backup(path);
        if (!output_file.good()) {
            return false;
        }

        output_file << std::setw(4) << json_data;
    }
    return recomp::finalize_output_file_with_backup(path);
}

bool save_general_config(const std::filesystem::path& path) {    
    nlohmann::json config_json{};

    dino::config::to_json(config_json["targeting_mode"], dino::config::get_targeting_mode());
    dino::input::to_json(config_json["background_input_mode"], dino::input::get_background_input_mode());
    config_json["rumble_strength"] = dino::input::get_rumble_strength();
    config_json["gyro_sensitivity"] = dino::input::get_gyro_sensitivity();
    config_json["mouse_sensitivity"] = dino::input::get_mouse_sensitivity();
    config_json["joystick_deadzone"] = dino::input::get_joystick_deadzone();
    config_json["autosave_mode"] = dino::config::get_autosave_mode();
    config_json["camera_invert_mode"] = dino::config::get_camera_invert_mode();
    config_json["analog_cam_mode"] = dino::config::get_analog_cam_mode();
    config_json["analog_camera_invert_mode"] = dino::config::get_analog_camera_invert_mode();
    config_json["debug_mode"] = dino::config::get_debug_mode_enabled();
    
    return save_json_with_backups(path, config_json);
}

void set_general_settings_from_json(const nlohmann::json& config_json) {
    dino::config::set_targeting_mode(from_or_default(config_json, "targeting_mode", dino::config::TargetingMode::Switch));
    dino::input::set_background_input_mode(from_or_default(config_json, "background_input_mode", dino::input::BackgroundInputMode::On));
    dino::input::set_rumble_strength(from_or_default(config_json, "rumble_strength", 25));
    dino::input::set_gyro_sensitivity(from_or_default(config_json, "gyro_sensitivity", 50));
    dino::input::set_mouse_sensitivity(from_or_default(config_json, "mouse_sensitivity", is_steam_deck ? 50 : 0));
    dino::input::set_joystick_deadzone(from_or_default(config_json, "joystick_deadzone", 5));
    dino::config::set_autosave_mode(from_or_default(config_json, "autosave_mode", dino::config::AutosaveMode::On));
    dino::config::set_camera_invert_mode(from_or_default(config_json, "camera_invert_mode", dino::config::CameraInvertMode::InvertY));
    dino::config::set_analog_cam_mode(from_or_default(config_json, "analog_cam_mode", dino::config::AnalogCamMode::Off));
    dino::config::set_analog_camera_invert_mode(from_or_default(config_json, "analog_camera_invert_mode", dino::config::CameraInvertMode::InvertNone));
    dino::config::set_debug_mode_enabled(from_or_default(config_json, "debug_mode", false));
}

bool load_general_config(const std::filesystem::path& path) {
    nlohmann::json config_json{};
    if (!read_json_with_backups(path, config_json)) {
        return false;
    }

    set_general_settings_from_json(config_json);
    return true;
}

void assign_mapping(dino::input::InputDevice device, dino::input::GameInput input, const std::vector<dino::input::InputField>& value) {
    for (size_t binding_index = 0; binding_index < std::min(value.size(), dino::input::bindings_per_input); binding_index++) {
        dino::input::set_input_binding(input, binding_index, device, value[binding_index]);
    }
};

// same as assign_mapping, except will clear unassigned bindings if not in value
void assign_mapping_complete(dino::input::InputDevice device, dino::input::GameInput input, const std::vector<dino::input::InputField>& value) {
    for (size_t binding_index = 0; binding_index < dino::input::bindings_per_input; binding_index++) {
        if (binding_index >= value.size()) {
            dino::input::set_input_binding(input, binding_index, device, dino::input::InputField{});
        } else {
            dino::input::set_input_binding(input, binding_index, device, value[binding_index]);
        }
    }
};

void assign_all_mappings(dino::input::InputDevice device, const dino::input::DefaultN64Mappings& values) {
    assign_mapping_complete(device, dino::input::GameInput::A, values.a);
    assign_mapping_complete(device, dino::input::GameInput::B, values.b);
    assign_mapping_complete(device, dino::input::GameInput::Z, values.z);
    assign_mapping_complete(device, dino::input::GameInput::START, values.start);
    assign_mapping_complete(device, dino::input::GameInput::DPAD_UP, values.dpad_up);
    assign_mapping_complete(device, dino::input::GameInput::DPAD_DOWN, values.dpad_down);
    assign_mapping_complete(device, dino::input::GameInput::DPAD_LEFT, values.dpad_left);
    assign_mapping_complete(device, dino::input::GameInput::DPAD_RIGHT, values.dpad_right);
    assign_mapping_complete(device, dino::input::GameInput::L, values.l);
    assign_mapping_complete(device, dino::input::GameInput::R, values.r);
    assign_mapping_complete(device, dino::input::GameInput::C_UP, values.c_up);
    assign_mapping_complete(device, dino::input::GameInput::C_DOWN, values.c_down);
    assign_mapping_complete(device, dino::input::GameInput::C_LEFT, values.c_left);
    assign_mapping_complete(device, dino::input::GameInput::C_RIGHT, values.c_right);

    assign_mapping_complete(device, dino::input::GameInput::X_AXIS_NEG, values.analog_left);
    assign_mapping_complete(device, dino::input::GameInput::X_AXIS_POS, values.analog_right);
    assign_mapping_complete(device, dino::input::GameInput::Y_AXIS_NEG, values.analog_down);
    assign_mapping_complete(device, dino::input::GameInput::Y_AXIS_POS, values.analog_up);

    assign_mapping_complete(device, dino::input::GameInput::TOGGLE_MENU, values.toggle_menu);
    assign_mapping_complete(device, dino::input::GameInput::ACCEPT_MENU, values.accept_menu);
    assign_mapping_complete(device, dino::input::GameInput::APPLY_MENU, values.apply_menu);
};

void dino::config::reset_input_bindings() {
    assign_all_mappings(dino::input::InputDevice::Keyboard, dino::input::default_n64_keyboard_mappings);
    assign_all_mappings(dino::input::InputDevice::Controller, dino::input::default_n64_controller_mappings);
}

void dino::config::reset_cont_input_bindings() {
    assign_all_mappings(dino::input::InputDevice::Controller, dino::input::default_n64_controller_mappings);
}

void dino::config::reset_kb_input_bindings() {
    assign_all_mappings(dino::input::InputDevice::Keyboard, dino::input::default_n64_keyboard_mappings);
}

void dino::config::reset_single_input_binding(dino::input::InputDevice device, dino::input::GameInput input) {
    assign_mapping_complete(
        device,
        input,
        dino::input::get_default_mapping_for_input(
            device == dino::input::InputDevice::Keyboard ?
                dino::input::default_n64_keyboard_mappings :
                dino::input::default_n64_controller_mappings,
            input
        )
    );
}

void reset_graphics_options() {
    ultramodern::renderer::GraphicsConfig new_config{};
    new_config.res_option = res_default;
    new_config.wm_option = wm_default();
    new_config.hr_option = hr_default;
    new_config.ds_option = ds_default;
    new_config.ar_option = ar_default;
    new_config.msaa_option = msaa_default;
    new_config.rr_option = rr_default;
    new_config.hpfb_option = hpfb_default;
    new_config.rr_manual_value = rr_manual_default;
    new_config.developer_mode = developer_mode_default;
    ultramodern::renderer::set_graphics_config(new_config);
}

bool save_graphics_config(const std::filesystem::path& path) {
    nlohmann::json config_json{};
    ultramodern::to_json(config_json, ultramodern::renderer::get_graphics_config());
    return save_json_with_backups(path, config_json);
}

bool load_graphics_config(const std::filesystem::path& path) {
    nlohmann::json config_json{};
    if (!read_json_with_backups(path, config_json)) {
        return false;
    }

    ultramodern::renderer::GraphicsConfig new_config{};
    ultramodern::from_json(config_json, new_config);
    ultramodern::renderer::set_graphics_config(new_config);
    return true;
}

void add_input_bindings(nlohmann::json& out, dino::input::GameInput input, dino::input::InputDevice device) {
    const std::string& input_name = dino::input::get_input_enum_name(input);
    nlohmann::json& out_array = out[input_name];
    out_array = nlohmann::json::array();
    for (size_t binding_index = 0; binding_index < dino::input::bindings_per_input; binding_index++) {
        out_array[binding_index] = dino::input::get_input_binding(input, binding_index, device);
    }
};

bool save_controls_config(const std::filesystem::path& path) {
    nlohmann::json config_json{};

    config_json["keyboard"] = {};
    config_json["controller"] = {};

    for (size_t i = 0; i < dino::input::get_num_inputs(); i++) {
        dino::input::GameInput cur_input = static_cast<dino::input::GameInput>(i);

        add_input_bindings(config_json["keyboard"], cur_input, dino::input::InputDevice::Keyboard);
        add_input_bindings(config_json["controller"], cur_input, dino::input::InputDevice::Controller);
    }

    return save_json_with_backups(path, config_json);
}

bool load_input_device_from_json(const nlohmann::json& config_json, dino::input::InputDevice device, const std::string& key) {
    // Check if the json object for the given key exists.
    auto find_it = config_json.find(key);
    if (find_it == config_json.end()) {
        return false;
    }

    const nlohmann::json& mappings_json = *find_it;

    for (size_t i = 0; i < dino::input::get_num_inputs(); i++) {
        dino::input::GameInput cur_input = static_cast<dino::input::GameInput>(i);
        const std::string& input_name = dino::input::get_input_enum_name(cur_input);

        // Check if the json object for the given input exists and that it's an array.
        auto find_input_it = mappings_json.find(input_name);
        if (find_input_it == mappings_json.end() || !find_input_it->is_array()) {
            assign_mapping(
                device,
                cur_input,
                dino::input::get_default_mapping_for_input(
                    device == dino::input::InputDevice::Keyboard ?
                    dino::input::default_n64_keyboard_mappings :
                    dino::input::default_n64_controller_mappings,
                    cur_input
                )
            );
            continue;
        }
        const nlohmann::json& input_json = *find_input_it;

        // Deserialize all the bindings from the json array (up to the max number of bindings per input).
        for (size_t binding_index = 0; binding_index < std::min(dino::input::bindings_per_input, input_json.size()); binding_index++) {
            dino::input::InputField cur_field{};
            dino::input::from_json(input_json[binding_index], cur_field);
            dino::input::set_input_binding(cur_input, binding_index, device, cur_field);
        }
    }

    return true;
}

bool load_controls_config(const std::filesystem::path& path) {
    nlohmann::json config_json{};
    if (!read_json_with_backups(path, config_json)) {
        return false;
    }

    if (!load_input_device_from_json(config_json, dino::input::InputDevice::Keyboard, "keyboard")) {
        assign_all_mappings(dino::input::InputDevice::Keyboard, dino::input::default_n64_keyboard_mappings);
    }

    if (!load_input_device_from_json(config_json, dino::input::InputDevice::Controller, "controller")) {
        assign_all_mappings(dino::input::InputDevice::Controller, dino::input::default_n64_controller_mappings);
    }
    return true;
}

bool save_sound_config(const std::filesystem::path& path) {
    nlohmann::json config_json{};

    config_json["main_volume"] = dino::sound::get_main_volume();
    config_json["bgm_volume"] = dino::sound::get_bgm_volume();
    config_json["low_health_beeps"] = dino::sound::get_low_health_beeps_enabled();
    
    return save_json_with_backups(path, config_json);
}

bool load_sound_config(const std::filesystem::path& path) {
    nlohmann::json config_json{};
    if (!read_json_with_backups(path, config_json)) {
        return false;
    }

    dino::sound::reset_sound_settings();
    call_if_key_exists(dino::sound::set_main_volume, config_json, "main_volume");
    call_if_key_exists(dino::sound::set_bgm_volume, config_json, "bgm_volume");
    call_if_key_exists(dino::sound::set_low_health_beeps_enabled, config_json, "low_health_beeps");
    return true;
}

void dino::config::load_config() {
    detect_steam_deck();

    std::filesystem::path recomp_dir = dino::config::get_app_folder_path();
    std::filesystem::path general_path = recomp_dir / general_filename;
    std::filesystem::path graphics_path = recomp_dir / graphics_filename;
    std::filesystem::path controls_path = recomp_dir / controls_filename;
    std::filesystem::path sound_path = recomp_dir / sound_filename;

    if (!recomp_dir.empty()) {
        std::filesystem::create_directories(recomp_dir);
    }

    // TODO error handling for failing to save config files after resetting them.

    if (!load_general_config(general_path)) {
        // Set the general settings from an empty json to use defaults.
        set_general_settings_from_json({});
        save_general_config(general_path);
    }

    if (!load_graphics_config(graphics_path)) {
        reset_graphics_options();
        save_graphics_config(graphics_path);
    }

    if (!load_controls_config(controls_path)) {
        dino::config::reset_input_bindings();
        save_controls_config(controls_path);
    }

    if (!load_sound_config(sound_path)) {
        dino::sound::reset_sound_settings();
        save_sound_config(sound_path);
    }
}

void dino::config::save_config() {
    std::filesystem::path recomp_dir = dino::config::get_app_folder_path();

    if (recomp_dir.empty()) {
        return;
    }

    std::filesystem::create_directories(recomp_dir);
    
    // TODO error handling for failing to save config files.

    save_general_config(recomp_dir / general_filename);
    save_graphics_config(recomp_dir / graphics_filename);
    save_controls_config(recomp_dir / controls_filename);
    save_sound_config(recomp_dir / sound_filename);
}