#include "recomp_ui.h"
#include "dino/config.hpp"
#include "librecomp/game.hpp"
#include "ultramodern/ultramodern.hpp"
#include "RmlUi/Core.h"
#include "nfd.h"
#include <filesystem>

static std::string version_string;

Rml::DataModelHandle model_handle;
bool rom_valid = false;

extern std::vector<recomp::GameEntry> supported_games;

void select_rom() {
	nfdnchar_t* native_path = nullptr;
	nfdresult_t result = NFD_OpenDialogN(&native_path, nullptr, 0, nullptr);

	if (result == NFD_OKAY) {
		std::filesystem::path path{native_path};

		NFD_FreePathN(native_path);
		native_path = nullptr;

		recomp::RomValidationError rom_error = recomp::select_rom(path, supported_games[0].game_id);
        switch (rom_error) {
            case recomp::RomValidationError::Good:
                rom_valid = true;
                model_handle.DirtyVariable("rom_valid");
                break;
            case recomp::RomValidationError::FailedToOpen:
                recompui::message_box("Failed to open ROM file.");
                break;
            case recomp::RomValidationError::NotARom:
                recompui::message_box("This is not a valid ROM file.");
                break;
            case recomp::RomValidationError::IncorrectRom:
                recompui::message_box("This ROM is not the correct game.");
                break;
            case recomp::RomValidationError::NotYet:
                recompui::message_box("This game isn't supported yet.");
                break;
            case recomp::RomValidationError::IncorrectVersion:
                recompui::message_box(
                        "This ROM is the correct game, but the wrong version.\nThis project requires the unmodified beta ROM.");
                break;
            case recomp::RomValidationError::OtherError:
                recompui::message_box("An unknown error has occurred.");
                break;
        }
    }
}

class LauncherMenu : public recompui::MenuController {
public:
    LauncherMenu() {
		rom_valid = recomp::is_rom_valid(supported_games[0].game_id);
    }
	~LauncherMenu() override {

	}
	Rml::ElementDocument* load_document(Rml::Context* context) override {
        return context->LoadDocument("assets/launcher.rml");
	}
	void register_events(recompui::UiEventListenerInstancer& listener) override {
		recompui::register_event(listener, "select_rom",
			[](const std::string& param, Rml::Event& event) {
				select_rom();
			}
		);
		recompui::register_event(listener, "rom_selected",
			[](const std::string& param, Rml::Event& event) {
				rom_valid = true;
				model_handle.DirtyVariable("rom_valid");
			}
		);
		recompui::register_event(listener, "start_game",
			[](const std::string& param, Rml::Event& event) {
				recomp::start_game(supported_games[0].game_id);
				recompui::set_current_menu(recompui::Menu::None);
			}
		);
        recompui::register_event(listener, "open_controls",
			[](const std::string& param, Rml::Event& event) {
                recompui::set_current_menu(recompui::Menu::Config);
				recompui::set_config_submenu(recompui::ConfigSubmenu::Controls);
			}
		);
        recompui::register_event(listener, "open_settings",
			[](const std::string& param, Rml::Event& event) {
                recompui::set_current_menu(recompui::Menu::Config);
                recompui::set_config_submenu(recompui::ConfigSubmenu::General);
			}
		);
        recompui::register_event(listener, "exit_game",
			[](const std::string& param, Rml::Event& event) {
				ultramodern::quit();
			}
		);
	}
	void make_bindings(Rml::Context* context) override {
		Rml::DataModelConstructor constructor = context->CreateDataModel("launcher_model");

		constructor.Bind("rom_valid", &rom_valid);

		version_string = recomp::get_project_version().to_string();
		constructor.Bind("version_number", &version_string);

		model_handle = constructor.GetModelHandle();
	}
};

std::unique_ptr<recompui::MenuController> recompui::create_launcher_menu() {
    return std::make_unique<LauncherMenu>();
}
