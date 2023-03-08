#include "runtime/function/scene/components.h"
#include "runtime/core/base/application.h"

namespace Toy2D {
    TileComponent::TileComponent(std::string_view tile_sheet_name) {
        tile_sheet = Toy2D::Application::get().getResourceMngr()->get<Toy2D::ResourceType::TileSheet>(std::string(tile_sheet_name));
    }
} // namespace Toy2D