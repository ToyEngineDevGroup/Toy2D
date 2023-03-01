#pragma once

#include "runtime/core/util/json_serializer.h"
#include "runtime/resource/resource.h"

namespace Toy2D {
    template <>
    class Resource<ResourceType::TileSheet> final : public IResource {
        struct TileSheetDesc {
            std::string tex_desc_path;
            uint16_t    row{1};
            uint16_t    col{1};
        };

    public:
        struct ResLoader final {
            using res_type = Scope<Resource<ResourceType::TileSheet>>;

            res_type operator()(const std::filesystem::path& path) const {
                rapidjson::Document doc;
                JsonSerialzer::deserialze(doc, path);
                auto          tex_desc_path = std::filesystem::path(TOY2D_XSTR(ROOT_DIR)) / "asset" / doc["tex_desc_path"].GetString();
                TileSheetDesc desc{
                    tex_desc_path.string(),
                    static_cast<uint16_t>(doc["row"].GetUint()),
                    static_cast<uint16_t>(doc["col"].GetUint())};

                return CreateScope<Resource<ResourceType::TileSheet>>(
                    (doc.HasMember("name")) ?
                        doc["name"].GetString() :
                        tex_desc_path.stem().string(),
                    desc);
            }
        };

    public:
        Resource(std::string_view name);
        Resource(std::string_view name, const TileSheetDesc& desc);

        bool validate() const { return m_is_valid; }

        uint16_t getRow() const { return m_row; }
        uint16_t getCol() const { return m_col; }

    private:
        uint16_t    m_row;
        uint16_t    m_col;
        std::string m_upper_tex;
    };

    class Tile {
    public:
        Tile() = default;

        Tile(Resource<ResourceType::TileSheet>* tile_sheet,
             const Vector2&                     coords,
             const Vector2&                     tile_size = {1.0f, 1.0f});

        Resource<ResourceType::TileSheet>* getTileSheet() const { return m_tile_sheet; }
        std::string_view                   getTileName() const { return m_tile_name; }

    private:
        bool                               m_is_valid{false};
        std::string                        m_tile_name;
        Resource<ResourceType::TileSheet>* m_tile_sheet;
    };
} // namespace Toy2D