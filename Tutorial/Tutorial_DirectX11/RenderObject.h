#pragma once
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Vertex.h"
#include "Matrix4x4.h"
#include "Point.h"
#include "Windows.h"


class RenderObject
{
	public:
		RenderObject();
		RenderObject(const wchar_t* filepath);
		~RenderObject();

	public:
		void initialize();
		virtual void onUpdate();
		void draw();
		void onRelease();

	public:
		void onKeyDown(int key);
		void onKeyRelease();

		void onMouseDown(char c);
		void onMouseUp();
		void onMouseMove(const Point& delta_mouse_pos);

		void translateObj(int key);
		void rotateObj(int key);
		void scaleObj(char c);

	public:
		void setWindowRef(RECT window);
		void setCameraConstant(constant* cam_cc);
		void createMesh(const wchar_t* filepath);

	public:
		//unsigned long m_old_time = 0;
		float m_old_time = 0;
		float m_new_time = 0;
		float m_delta_time = 0;

	private:
		RECT windowRef;

	protected:
		VertexBufferPtr m_vb;	
		ConstantBufferPtr m_cb;
		IndexBufferPtr m_ib;

		VertexShaderPtr m_vs;
		PixelShaderPtr m_ps;

		TexturePtr m_tex;
		MeshPtr m_mesh;

		constant cc;
		constant* camCC;

	public:
		Vector3D currentColor;

		Vector4D obj_pos;
		Vector4D obj_rot;
		Vector4D obj_scale;
		

};

