#pragma once

#include "editor_layer.h"

namespace Toy2D {
    class Editor : public Toy2D::Application {
    public:
        Editor() {
            pushLayer(new EditorLayer());
        }

        ~Editor() {
        }
    };

    Toy2D::Application* createApp() {
        Toy2D::RendererAPI::setEditorModeEnabled(true);
        return new Editor();
    }
} // namespace Toy2D