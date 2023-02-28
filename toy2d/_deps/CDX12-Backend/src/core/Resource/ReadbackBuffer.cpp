#include <CDX12/FrameResource.h>
#include <CDX12/Resource/ReadbackBuffer.h>

namespace Chen::CDX12 {
    ReadbackBuffer::ReadbackBuffer(
        ID3D12Device* device,
        uint64_t      byteSize) :
        Buffer(device),
        byteSize(byteSize) {
        auto prop   = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_READBACK);
        auto buffer = CD3DX12_RESOURCE_DESC::Buffer(byteSize);
        ThrowIfFailed(device->CreateCommittedResource(
            &prop,
            D3D12_HEAP_FLAG_NONE,
            &buffer,
            D3D12_RESOURCE_STATE_COPY_DEST,
            nullptr,
            IID_PPV_ARGS(&resource)));
    }

    ReadbackBuffer::~ReadbackBuffer() {}

    void ReadbackBuffer::CopyData(
        uint64_t           offset,
        std::span<uint8_t> data) const {
        void*       mapPtr;
        D3D12_RANGE range;
        range.Begin = offset;
        range.End   = (byteSize < offset + data.size()) ? byteSize : offset + data.size();

        ThrowIfFailed(resource->Map(0, &range, (void**)(&mapPtr)));
        memcpy(data.data(), reinterpret_cast<uint8_t const*>(mapPtr) + offset, range.End - range.Begin);
        resource->Unmap(0, nullptr);
    }

    void ReadbackBuffer::DelayDispose(FrameResource* frameRes) const {
        frameRes->AddDelayDisposeResource(resource);
    }
} // namespace Chen::CDX12
