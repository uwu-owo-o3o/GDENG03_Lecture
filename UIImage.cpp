#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "UIImage.h"
#include "GraphicsEngine.h"

UIImage::UIImage()
{
    this->img_width = 0.0f;
    this->img_height = 0.0f;
    this->img_scale = 1.0f;
    this->img_texture = nullptr;
}

UIImage::UIImage(int img_width, int img_height, float img_scale)
{
    this->img_width = img_width;
    this->img_height = img_height;
    this->img_scale = img_scale;
    this->img_texture = nullptr;
}

UIImage::~UIImage()
{
}

void UIImage::createImage()
{
    bool img = loadTextureFromFile("Assets/Image/lozol.png", &this->img_texture, (int*)&this->img_width, (int*)&this->img_height);
    if (!img) {
        std::cout << "Failed to load image!" << std::endl;
        return;
    }
    IM_ASSERT(img);

}

void UIImage::drawImage()
{
    ImGui::Image((ImTextureID)(intptr_t)this->img_texture, ImVec2(this->img_width * this->img_scale, this->img_height * this->img_scale));
}

bool UIImage::loadImageTexture(const void* data, size_t data_size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load_from_memory((const unsigned char*)data, (int)data_size, &image_width, &image_height, NULL, 4);
    if (image_data == NULL) {
        std::cout << "image_data is null" << std::endl;
        return false;
    }

    // Create texture
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = image_width;
    desc.Height = image_height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    ID3D11Texture2D* pTexture = NULL;
    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = image_data;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;
    GraphicsEngine::get()->getRenderSystem()->m_d3d_device->CreateTexture2D(&desc, &subResource, &pTexture);

    // Create texture view
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;
    GraphicsEngine::get()->getRenderSystem()->m_d3d_device->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
    pTexture->Release();

    *out_width = image_width;
    *out_height = image_height;
    stbi_image_free(image_data);

    return true;
}

bool UIImage::loadTextureFromFile(const char* file_name, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
    FILE* f = fopen(file_name, "rb");
    if (f == NULL)
        return false;
    fseek(f, 0, SEEK_END);
    size_t file_size = (size_t)ftell(f);
    if (file_size == -1)
        return false;
    fseek(f, 0, SEEK_SET);
    void* file_data = IM_ALLOC(file_size);
    fread(file_data, 1, file_size, f);
    fclose(f);
    bool img = loadImageTexture(file_data, file_size, out_srv, out_width, out_height);
    IM_FREE(file_data);
    return img;
}