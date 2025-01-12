#include "librecomp/mods.hpp"

#include "dino/init.hpp"
#include "dino/renderer.hpp"

void enable_texture_pack(recomp::mods::ModContext& context, const recomp::mods::ModHandle& mod) {
    (void)context;
    dino::renderer::enable_texture_pack(mod);
}

void disable_texture_pack(recomp::mods::ModContext& context, const recomp::mods::ModHandle& mod) {
    (void)context;
    dino::renderer::disable_texture_pack(mod);
}

void dino::init::register_mods() {
    // Register the texture pack content type with rt64.json as its content file.
    recomp::mods::ModContentType texture_pack_content_type{
        .content_filename = "rt64.json",
        .allow_runtime_toggle = true,
        .on_enabled = enable_texture_pack,
        .on_disabled = disable_texture_pack,
    };
    auto texture_pack_content_type_id = recomp::mods::register_mod_content_type(texture_pack_content_type);

    // Register the .rtz texture pack file format with the previous content type as its only allowed content type.
    recomp::mods::register_mod_container_type("rtz", std::vector{ texture_pack_content_type_id }, false);

    recomp::mods::scan_mods();

    printf("Found mods:\n");
    for (const auto& mod : recomp::mods::get_mod_details("dino-planet")) {
        printf("  %s(%s)\n", mod.mod_id.c_str(), mod.version.to_string().c_str());
        if (!mod.authors.empty()) {
            printf("    Authors: %s", mod.authors[0].c_str());
            for (size_t author_index = 1; author_index < mod.authors.size(); author_index++) {
                const std::string& author = mod.authors[author_index];
                printf(", %s", author.c_str());
            }
            printf("\n");
            printf("    Runtime toggleable: %d\n", mod.runtime_toggleable);
        }
        if (!mod.dependencies.empty()) {
            printf("    Dependencies: %s:%s", mod.dependencies[0].mod_id.c_str(), mod.dependencies[0].version.to_string().c_str());
            for (size_t dep_index = 1; dep_index < mod.dependencies.size(); dep_index++) {
                const recomp::mods::Dependency& dep = mod.dependencies[dep_index];
                printf(", %s:%s", dep.mod_id.c_str(), dep.version.to_string().c_str());
            }
            printf("\n");
        }
        // TODO load all mods as a temporary solution to not having a UI yet.
        recomp::mods::enable_mod(mod.mod_id, true);
    }
    printf("\n");
}
