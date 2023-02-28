#pragma once
#include <CDX12/DXUtil.h>

namespace Chen::CDX12 {
    class IStackAllocVisitor {
    public:
        virtual uint64 Allocate(uint64 size)     = 0;
        virtual void   DeAllocate(uint64 handle) = 0;
    };

    class StackAllocator {
        uint64              capacity;
        IStackAllocVisitor* visitor;
        struct Buffer {
            uint64 handle;
            uint64 fullSize;
            uint64 leftSize;
        };
        std::vector<Buffer> allocatedBuffers;

    public:
        StackAllocator(
            uint64              initCapacity,
            IStackAllocVisitor* visitor);
        ~StackAllocator();
        struct Chunk {
            uint64 handle;
            uint64 offset;
        };
        Chunk Allocate(
            uint64 targetSize);
        Chunk Allocate(
            uint64 targetSize,
            uint64 align);
        void Clear();
    };

} // namespace Chen::CDX12
