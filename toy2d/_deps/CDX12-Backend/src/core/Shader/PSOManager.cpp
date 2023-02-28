#include <filesystem>

#include <CDX12/GeneralDesc.h>
#include <CDX12/Shader/BasicShader.h>
#include <CDX12/Shader/PSOManager.h>

namespace Chen::CDX12 {
    PSOManager::PSOManager(ID3D12Device* device) :
        device(device) {
    }

    PSOManager::~PSOManager() {
    }

    ID3D12PipelineState* PSOManager::GetPipelineState(D3D12_GRAPHICS_PIPELINE_STATE_DESC const& stateDesc) {
        auto emplaceResult = pipelineStates.try_emplace(stateDesc);
        // New pipeline state
        if (emplaceResult.second) {
            ThrowIfFailed(device->CreateGraphicsPipelineState(&stateDesc, IID_PPV_ARGS(&emplaceResult.first->second)));
        }
        return emplaceResult.first->second.Get();
    }

    ID3D12PipelineState* PSOManager::GetPipelineState(
        std::span<D3D12_INPUT_ELEMENT_DESC const> meshLayout,
        BasicShader const*                        shader,
        std::span<DXGI_FORMAT>                    rtvFormats,
        DXGI_FORMAT                               depthFormat,
        D3D12_PRIMITIVE_TOPOLOGY_TYPE             topologyType) {
        D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
        psoDesc.InputLayout                        = {meshLayout.data(), uint(meshLayout.size())};
        psoDesc.pRootSignature                     = shader->RootSig();

        auto GetByteCode = [](ComPtr<ID3DBlob> const& blob) -> D3D12_SHADER_BYTECODE {
            if (blob) {
                return CD3DX12_SHADER_BYTECODE(blob.Get());
            }
            else {
                return CD3DX12_SHADER_BYTECODE(nullptr, 0);
            }
        };

        psoDesc.VS                    = GetByteCode(shader->vsShader);
        psoDesc.PS                    = GetByteCode(shader->psShader);
        psoDesc.HS                    = GetByteCode(shader->hsShader);
        psoDesc.DS                    = GetByteCode(shader->dsShader);
        psoDesc.RasterizerState       = shader->rasterizerState;
        psoDesc.DepthStencilState     = shader->depthStencilState;
        psoDesc.BlendState            = shader->blendState;
        psoDesc.SampleMask            = UINT_MAX;
        psoDesc.PrimitiveTopologyType = topologyType;

        size_t rtSize            = std::min<size_t>(rtvFormats.size(), 8);
        psoDesc.NumRenderTargets = rtSize;
        for (size_t i = 0; i < rtSize; ++i) {
            psoDesc.RTVFormats[i] = rtvFormats[i];
        }
        psoDesc.DSVFormat        = depthFormat;
        psoDesc.SampleDesc.Count = 1;
        return GetPipelineState(psoDesc);
    }
} // namespace Chen::CDX12
