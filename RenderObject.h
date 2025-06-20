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
#include "Point.h"
#include "Matrix4x4.h"
#include "Prerequisites.h"

class RenderObject
{
	public:
		RenderObject();
		~RenderObject();

	public:
		void initialize();
		void onUpdate();
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

	public:
		float m_old_time = 0;
		float m_new_time = 0;
		float m_delta_time = 0;

		float m_time_elapsed = 0;
		float m_delay_threshold = 2.0f;

	private:
		RECT windowRef;
		constant cc;
		constant* camCC;

	private:
		VertexBufferPtr m_vb;		
		ConstantBufferPtr m_cb;
		IndexBufferPtr m_ib;

		VertexShaderPtr m_vs;
		PixelShaderPtr m_ps;

	public:
		Vector3D obj_pos;
		Vector3D obj_rot;
		Vector3D obj_scale;

		Vector3D flat_color;

		Vector3D startScale;
		Vector3D endScale;


		Vector3D startPos;
		Vector3D endPos;

		int isFlat;

		bool reachedEndScale;
		bool reachedEndPos;

};

