#include <CDX12/DescriptorHeapMngr.h>

namespace Chen::CDX12 {
    void DescriptorHeapMngr::Init(
        ID3D12Device* device,
        uint32_t      numCpuCSU,
        uint32_t      numCpuRTV,
        uint32_t      numCpuDSV,
        uint32_t      numGpuCSU_static,
        uint32_t      numGpuCSU_dynamic) {
        assert(!isInit);

        CSU_CpuDH = new CPUDescriptorHeap{
            device,
            numCpuCSU,
            D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
            D3D12_DESCRIPTOR_HEAP_FLAG_NONE};

        RTV_CpuDH = new CPUDescriptorHeap{
            device,
            numCpuRTV,
            D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
            D3D12_DESCRIPTOR_HEAP_FLAG_NONE};

        DSV_CpuDH = new CPUDescriptorHeap{
            device,
            numCpuDSV,
            D3D12_DESCRIPTOR_HEAP_TYPE_DSV,
            D3D12_DESCRIPTOR_HEAP_FLAG_NONE};

        CSU_GpuDH = new GPUDescriptorHeap{
            device,
            numGpuCSU_static,
            numGpuCSU_dynamic,
            D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
            D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE};

        isInit = true;
    }

    void DescriptorHeapMngr::Clear() {
        isInit = false;

        delete CSU_CpuDH;
        delete RTV_CpuDH;
        delete DSV_CpuDH;
        delete CSU_GpuDH;

        CSU_CpuDH = nullptr;
        RTV_CpuDH = nullptr;
        DSV_CpuDH = nullptr;
        CSU_GpuDH = nullptr;
    }

    DescriptorHeapMngr::~DescriptorHeapMngr() {
        Clear();
    }
} // namespace Chen::CDX12
