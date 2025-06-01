#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include "RenderSystem.h"
#include "TextureManager.h"
#include "Prerequisites.h"

class GraphicsEngine
{
	public:
		GraphicsEngine();
		~GraphicsEngine();
		RenderSystem* getRenderSystem();
		TextureManager* getTextureManager();

	public:
		static GraphicsEngine* get();
		static void create();
		static void release();

	private:
		RenderSystem* m_render_system = nullptr;
		TextureManager* m_tex_manager = nullptr;
		static GraphicsEngine* m_engine;
};

