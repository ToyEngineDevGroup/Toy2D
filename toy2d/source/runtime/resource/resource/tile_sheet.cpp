#include "runtime/resource/resource/tile_sheet.h"
#include "runtime/core/base/application.h"
#include "runtime/function/render/render_system/buffer.h"

namespace Toy2D {
    Resource<ResourceType::TileSheet>::Resource(std::string_view name) :
        IResource(name) {
    }

    Resource<ResourceType::TileSheet>::Resource(std::string_view name, const TileSheetDesc& desc) :
        IResource(name), m_upper_tex(std::string(name)), m_row(desc.row), m_col(desc.col) {
        Application::get().getResourceMngr()->add<ResourceType::Texture>(name, desc.tex_desc_path);
    }

    Tile::Tile(Resource<ResourceType::TileSheet>* tile_sheet,
               const Vector2&                     coords,
               const Vector2&                     tile_size) :
        m_tile_name(std::string(tile_sheet->getName())
                    + std::to_string(int(coords.x))
                    + std::to_string(int(coords.y))
                    + std::to_string(int(tile_size.x))
                    + std::to_string(int(tile_size.y))),
        m_tile_sheet(tile_sheet) {
        m_is_valid = true;

        if (Application::get().getResourceMngr()->has<ResourceType::Mesh>(m_tile_name)) return;

        Vector2 min = {
            coords.x / tile_sheet->getCol(),
            coords.y / tile_sheet->getRow()};

        Vector2 max = {
            (coords.x + tile_size.x) / tile_sheet->getCol(),
            (coords.y + tile_size.y) / tile_sheet->getRow()};

        uint32_t     indices[]  = {0, 3, 1, 3, 2, 1};
        VertexData2D vertices[] = {
            VertexData2D{{-0.5f, -0.5f, 0.0f}, {min.x, 1.0f - min.y}},
            VertexData2D{{0.5f, -0.5f, 0.0f}, {max.x, 1.0f - min.y}},
            VertexData2D{{0.5f, 0.5f, 0.0f}, {max.x, 1.0f - max.y}},
            VertexData2D{{-0.5f, 0.5f, 0.0f}, {min.x, 1.0f - max.y}}};

        VertexBufferLayout layout;

        Application::get().getResourceMngr()->add<ResourceType::Mesh>(
            m_tile_name,
            vertices,
            array_count(vertices) * sizeof(VertexData2D) / layout.structSize,
            indices,
            array_count(indices));
    }
} // namespace Toy2D
