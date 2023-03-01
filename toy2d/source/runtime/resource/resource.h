#pragma once

namespace Toy2D {
    enum class ResourceType {
        Unknown,
        Texture,
        Mesh,
        Animation,
        TileSheet
    };

    class IResource {
    public:
        explicit IResource(std::string_view name);
        virtual ~IResource() = default;

        std::string_view getName() const;
        size_t           getUUID() const;

        virtual bool validate() const { return true; }

    protected:
        std::string m_name;
    };

    template <ResourceType Type>
    class Resource : public IResource {
    public:
        Resource() = default;

        virtual ~Resource() override = default;
    };

} // namespace Toy2D
