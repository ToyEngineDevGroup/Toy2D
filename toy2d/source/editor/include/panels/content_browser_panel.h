#pragma once

namespace Toy2D {

    class ContentBrowserPanel {
    public:
        ContentBrowserPanel();

        void onImGuiRender();

    private:
        std::filesystem::path m_current_directory;
    };

} // namespace Toy2D