#pragma once
#include "imgui.h"
#include <d3d11.h>
#include "iostream"

class UIImage
{
	public:
		UIImage();
		UIImage(int img_width, int img_height, float img_scale);
		~UIImage();

	public:
		void createImage();
		void drawImage();
		bool loadImageTexture(const void* data, size_t data_size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
		bool loadTextureFromFile(const char* file_name, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);

	public:
		ID3D11ShaderResourceView* img_texture = NULL;
		int img_width;
		int img_height;
		float img_scale;

};

