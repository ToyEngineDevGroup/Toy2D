#pragma once

#include "runtime/function/render/render_system/render_pass.h"

namespace Toy2D {
    class UIPass final : public RenderPass {
    public:
        UIPass();
        ~UIPass();

        void preLoadResource() override;
        void delayDisposeResource(Chen::CDX12::FrameResource&) override;
        void drawPass(Chen::CDX12::FrameResource&, uint32_t frameIndex, bool offscreen = true) override;
        void drawPassIndirect(Chen::CDX12::FrameResource& frameRes, uint32_t frameIndex, bool offscreen = true) override;
    };
} // namespace Toy2D