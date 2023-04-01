#pragma once

namespace Toy2D {
    class ConfigManager {
    public:
        explicit ConfigManager(const std::filesystem::path& game_root_path);

        const std::filesystem::path& getRootFolder() const;
        const std::filesystem::path& getAssetFolder() const;
        const std::filesystem::path& getScriptFolder() const;

    private:
        std::filesystem::path m_root_folder;
        std::filesystem::path m_asset_folder;
        std::filesystem::path m_script_folder;
    };
} // namespace Toy2D