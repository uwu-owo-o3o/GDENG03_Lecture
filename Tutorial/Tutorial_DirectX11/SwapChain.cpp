#include "SwapChain.h"
#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include <exception>
#include <iostream>

SwapChain::SwapChain(HWND hwnd, UINT width, UINT height, RenderSystem* m_system) : m_system(m_system)
{
    ID3D11Device* device = m_system->m_d3d_device;

    if (m_system) {
        std::cerr << "Valid m_system SwapChain constructor." << std::endl;
    }

    if (hwnd || ::IsWindow(hwnd)) {
        std::cerr << "Valid or not null HWND passed to SwapChain constructor." << std::endl;
        //throw std::runtime_error("Invalid HWND.");
    }

    if (device) {
        std::cerr << "D3D11 device is not null" << std::endl;
    }

    DXGI_SWAP_CHAIN_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.BufferCount = 1;
    desc.BufferDesc.Width = width;
    desc.BufferDesc.Height = height;
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferDesc.RefreshRate.Numerator = 60;
    desc.BufferDesc.RefreshRate.Denominator = 1;

    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.OutputWindow = hwnd;

    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Windowed = TRUE;

    HRESULT hr = m_system->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);

    if (FAILED(hr)) {
        throw std::exception("SwapChain not created successfully.");
    }

    ID3D11Texture2D* buffer = NULL;
    hr = m_swap_chain->GetBuffer(0, _uuidof(ID3D11Texture2D), (void**)&buffer);

    if (FAILED(hr)) {
        throw std::exception("SwapChain buffer not retrieved successfully.");
    }

    hr = device->CreateRenderTargetView(buffer, NULL, &m_rtv);
    buffer->Release();


    if (FAILED(hr)) {
        throw std::exception("SwapChain not created successfully.");
    }

    D3D11_TEXTURE2D_DESC tex_desc = {};
    tex_desc.Width = width;
    tex_desc.Height = height;
    tex_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    tex_desc.Usage = D3D11_USAGE_DEFAULT;
    tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    tex_desc.MipLevels = 1;
    tex_desc.SampleDesc.Count = 1;
    tex_desc.SampleDesc.Quality = 0;
    tex_desc.MiscFlags = 0;
    tex_desc.ArraySize = 1;
    tex_desc.CPUAccessFlags = 0;

    hr = device->CreateTexture2D(&tex_desc, nullptr, &buffer);


    if (FAILED(hr)) {
        throw std::exception("SwapChain not created successfully.");
    }

    hr = device->CreateDepthStencilView(buffer, nullptr, &m_dsv);
    buffer->Release();
    if (FAILED(hr)) {
        throw std::exception("SwapChain not created successfully.");
    }
}

bool SwapChain::present(bool vsync)
{
    m_swap_chain->Present(vsync, NULL);
    return true;
}

SwapChain::~SwapChain()
{
    m_swap_chain->Release();
    m_rtv->Release();
}
