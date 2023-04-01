#include "runtime/resource/config_manager/config_manager.h"

namespace Toy2D {
    ConfigManager::ConfigManager(const std::filesystem::path& game_root_path) {
        m_root_folder   = TOY2D_XSTR(ROOT_DIR); // std::filesystem::path(game_root_path);
        m_asset_folder  = m_root_folder / "asset";
        m_script_folder = m_root_folder / "script";
    }

    const std::filesystem::path& ConfigManager::getRootFolder() const { return m_root_folder; }
    const std::filesystem::path& ConfigManager::getAssetFolder() const { return m_asset_folder; }
    const std::filesystem::path& ConfigManager::getScriptFolder() const { return m_script_folder; }
} // namespace Toy2D