#include "AppWindow.h"
#include <Windows.h>
#include <iostream>
#include "InputSystem.h"

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	InputSystem::get()->addListener(this);

	m_swap_chain = GraphicsEngine::get()->getRenderSystem()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	this->worldCam.initialize();
	this->worldCam.setWindowReference(this->getClientWindowRect());

	this->iniCardReferences();
	this->formCardStructure();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::get()->update();

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.5, 0.5, 0.5, 1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewPortSize(rc.right - rc.left, rc.bottom - rc.top);

	this->worldCam.onUpdate();
	this->updateCards();
	this->drawCards();
	/*this->tiltCardRef1.onUpdate();
	this->tiltCardRef2.onUpdate();
	this->flatCardRef.onUpdate();

	this->tiltCardRef1.draw();
	this->tiltCardRef2.draw();
	this->flatCardRef.draw();*/

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();

	GraphicsEngine::get()->release();
}

void AppWindow::createRenderObjects()
{
		//cube.initialize();
		//cube.setWindowRef(this->getClientWindowRect());
		//cube.setCameraConstant(&this->worldCam.cc);
		//cube.obj_pos = Vector3D(0, 0.9, 0);
		//cube.isFlat = 1;


	/*	cube2.initialize();
		cube2.setWindowRef(this->getClientWindowRect());
		cube2.setCameraConstant(&this->worldCam.cc);
		cube2.obj_pos = Vector3D(-1.5, 2.0, 0);
		cube2.isFlat = 1;

		cube3.initialize();
		cube3.setWindowRef(this->getClientWindowRect());
		cube3.setCameraConstant(&this->worldCam.cc);
		cube3.obj_pos = Vector3D(-1.5, 3.0, -2);
		cube3.isFlat = 1;

		plane.initialize();
		plane.setWindowRef(this->getClientWindowRect());
		plane.setCameraConstant(&this->worldCam.cc);
		plane.obj_scale = Vector3D(10.0f, 0.1f, 10.0f);
		plane.obj_pos = Vector3D(0, -1.0, 0);
		plane.isFlat = 1;*/

}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::OnKeyDown(int key)
{
	this->worldCam.moveOnKey(key);
	this->flatCardRef.rotateObj(key);
	//this->selectedObjectHelper(key);

	//switch (this->currSelected) {
	//case 1:
	//	this->cube.onKeyDown(key);
	//	break;
	//case 2:
	//	this->cube2.onKeyDown(key);
	//	break;
	//case 3:
	//	this->cube3.onKeyDown(key);
	//	break;
	//case 4:
	//	this->plane.onKeyDown(key);
	//	break;
	//}
}

void AppWindow::OnKeyUp(int key)
{
	this->worldCam.OnKeyRelease();
}

void AppWindow::OnMouseMove(const Point& deltaMousePos)
{
}

void AppWindow::OnLeftMouseDown(const Point& deltaMousePos)
{
	//switch (this->currSelected) {
	//	case 1:
	//		this->cube.onMouseDown('L');
	//		break;
	//	case 2:
	//		this->cube2.onMouseDown('L');
	//		break;
	//	case 3:
	//		this->cube3.onMouseDown('L');
	//		break;
	//	case 4:
	//		this->plane.onMouseDown('L');
	//		break;
	//}
}

void AppWindow::OnLeftMouseUp(const Point& deltaMousePos)
{
}

void AppWindow::OnRightMouseDown(const Point& deltaMousePos)
{
	/*switch (this->currSelected) {
		case 1:
			this->cube.onMouseDown('R');
			break;
		case 2:
			this->cube2.onMouseDown('R');
			break;
		case 3:
			this->cube3.onMouseDown('R');
			break;
		case 4:
			this->plane.onMouseDown('R');
			break;
	}*/
}

void AppWindow::OnRightMouseUp(const Point& deltaMousePos)
{
}

void AppWindow::selectedObjectHelper(int key)
{
	/*if (key == '1') {
		this->currSelected = 1;
	}
	else if (key == '2') {
		this->currSelected = 2;
	}
	else if (key == '3') {
		this->currSelected = 3;
	}
	else if (key == '4') {
		this->currSelected = 4;
	}*/

}

void AppWindow::spawnCubes()
{
	srand(time(0));

	for (int i = 0; i < 50; i++) {
		RenderObject* spawnedCube = new RenderObject();
		spawnedCube->initialize();
		spawnedCube->setCameraConstant(&this->worldCam.cc);
		spawnedCube->setWindowRef(this->getClientWindowRect());
		spawnedCube->obj_pos = this->randomPosHelper();
		this->cubes.push_back(spawnedCube);

	}

}

Vector3D AppWindow::randomPosHelper()
{
	float x_ub = 3.0f;
	float x_lb = -3.0f;

	float y_ub = 3.0f;
	float y_lb = -3.0f;

	float z_ub = 2.0f;
	float z_lb = 1.0f;


	float rand_x = x_lb + (x_ub - x_lb) * ((float)rand() / (float)RAND_MAX);
	float rand_y = y_lb + (y_ub - y_lb) * ((float)rand() / (float)RAND_MAX);
	float rand_z = z_lb + (z_ub - z_lb) * ((float)rand() / (float)RAND_MAX);

	Vector3D newPos = Vector3D(rand_x, rand_y, rand_z);

	return newPos;
}

void AppWindow::updateCubes()
{
	for (int i = 0; i < this->cubes.size(); i++) {
		this->cubes[i]->onUpdate();
	}
}

void AppWindow::drawCubes()
{
	for (int i = 0; i < this->cubes.size(); i++) {
		this->cubes[i]->draw();
	}
}

void AppWindow::iniCardReferences()
{
	this->tiltCardRef1 = RenderObject();
	this->tiltCardRef1.initialize();
	this->tiltCardRef1.setCameraConstant(&this->worldCam.cc);
	this->tiltCardRef1.setWindowRef(this->getClientWindowRect());
	this->tiltCardRef1.obj_scale = Vector3D(0.1f, 5.0f, 1.0f);
	this->tiltCardRef1.obj_rot = Vector3D(0.0f, 0.0f, 2.7f);

	this->tiltCardRef2 = RenderObject();
	this->tiltCardRef2.initialize();
	this->tiltCardRef2.setCameraConstant(&this->worldCam.cc);
	this->tiltCardRef2.setWindowRef(this->getClientWindowRect());

	this->tiltCardRef2.obj_pos = Vector3D(2.1f, 0.0f, 0.0f); // 2 units difference of width from 1 card to another.
	this->tiltCardRef2.obj_scale = Vector3D(0.1f,5.0f, 1.0f);
	this->tiltCardRef2.obj_rot = Vector3D(0.0f, 0.0f, -2.7f);


	this->flatCardRef = RenderObject();
	this->flatCardRef.initialize();
	this->flatCardRef.setCameraConstant(&this->worldCam.cc);
	this->flatCardRef.setWindowRef(this->getClientWindowRect());

	this->flatCardRef.obj_pos = Vector3D(2.5f, 2.3f, 0.0f); // 2.5 units difference of width from first tilted card and 2.3f for height.
	this->flatCardRef.obj_scale = Vector3D(0.1f, 5.0f, 1.0f);
	this->flatCardRef.obj_rot = Vector3D(0.0f, 0.0f, 1.576f);
}

void AppWindow::formCardStructure()
{
	for (int i = 0; i < 15; i++) {
		RenderObject* spawnedCard = new RenderObject();
		spawnedCard->initialize();
		spawnedCard->setCameraConstant(&this->worldCam.cc);
		spawnedCard->setWindowRef(this->getClientWindowRect());
		this->setCard(i, spawnedCard);
		this->cards.push_back(spawnedCard);
	}
}

void AppWindow::setCard(int index, RenderObject* cardSpawned)
{
	float width_diff = 2.1f;
	float flat_width_diff = 5.2f;
	float height_diff = 4.7f;
	switch (index) {
		case 0:
			cardSpawned->obj_pos = this->tiltCardRef1.obj_pos;
			cardSpawned->obj_rot = this->tiltCardRef1.obj_rot;
			cardSpawned->obj_scale = this->tiltCardRef1.obj_scale;
			break;
		case 1:
			cardSpawned->obj_pos = this->tiltCardRef2.obj_pos;
			cardSpawned->obj_rot = this->tiltCardRef2.obj_rot;
			cardSpawned->obj_scale = this->tiltCardRef2.obj_scale;
			break;
		case 2:
			cardSpawned->obj_pos = Vector3D(this->cards[index - 1]->obj_pos.m_x + width_diff, this->cards[index - 1]->obj_pos.m_y, this->cards[index - 1]->obj_pos.m_z);
			cardSpawned->obj_rot = this->tiltCardRef1.obj_rot;
			cardSpawned->obj_scale = this->tiltCardRef1.obj_scale;
			break;
		case 3:
			cardSpawned->obj_pos = Vector3D(this->cards[index - 1]->obj_pos.m_x + width_diff, this->cards[index - 1]->obj_pos.m_y, this->cards[index - 1]->obj_pos.m_z);
			cardSpawned->obj_rot = this->tiltCardRef2.obj_rot;
			cardSpawned->obj_scale = this->tiltCardRef2.obj_scale;
			break;
		case 4:
			cardSpawned->obj_pos = Vector3D(this->cards[index - 1]->obj_pos.m_x + width_diff, this->cards[index - 1]->obj_pos.m_y, this->cards[index - 1]->obj_pos.m_z);
			cardSpawned->obj_rot = this->tiltCardRef1.obj_rot;
			cardSpawned->obj_scale = this->tiltCardRef1.obj_scale;
			break;
		case 5:
			cardSpawned->obj_pos = Vector3D(this->cards[index - 1]->obj_pos.m_x + width_diff, this->cards[index - 1]->obj_pos.m_y, this->cards[index - 1]->obj_pos.m_z);
			cardSpawned->obj_rot = this->tiltCardRef2.obj_rot;
			cardSpawned->obj_scale = this->tiltCardRef2.obj_scale;
			break;
		case 6:
			cardSpawned->obj_pos = this->flatCardRef.obj_pos;
			cardSpawned->obj_rot = this->flatCardRef.obj_rot;
			cardSpawned->obj_scale = this->flatCardRef.obj_scale;
			break;
		case 7:
			cardSpawned->obj_pos = Vector3D(this->cards[index - 1]->obj_pos.m_x + flat_width_diff, this->cards[index - 1]->obj_pos.m_y, this->cards[index - 1]->obj_pos.m_z);
			cardSpawned->obj_rot = this->flatCardRef.obj_rot;
			cardSpawned->obj_scale = this->flatCardRef.obj_scale;
			break;
		case 8:
			cardSpawned->obj_pos = Vector3D(this->tiltCardRef1.obj_pos.m_x + width_diff, this->tiltCardRef1.obj_pos.m_y + height_diff, this->tiltCardRef1.obj_pos.m_z);
			cardSpawned->obj_rot = this->tiltCardRef1.obj_rot;
			cardSpawned->obj_scale = this->tiltCardRef1.obj_scale;
			break;
		case 9:
			cardSpawned->obj_pos = Vector3D(this->cards[index - 1]->obj_pos.m_x + width_diff, this->cards[index - 1]->obj_pos.m_y, this->cards[index - 1]->obj_pos.m_z);
			cardSpawned->obj_rot = this->tiltCardRef2.obj_rot;
			cardSpawned->obj_scale = this->tiltCardRef2.obj_scale;
			break;
		case 10:
			cardSpawned->obj_pos = Vector3D(this->cards[index - 1]->obj_pos.m_x + width_diff, this->cards[index - 1]->obj_pos.m_y, this->cards[index - 1]->obj_pos.m_z);
			cardSpawned->obj_rot = this->tiltCardRef1.obj_rot;
			cardSpawned->obj_scale = this->tiltCardRef1.obj_scale;
			break;
		case 11:
			cardSpawned->obj_pos = Vector3D(this->cards[index - 1]->obj_pos.m_x + width_diff, this->cards[index - 1]->obj_pos.m_y, this->cards[index - 1]->obj_pos.m_z);
			cardSpawned->obj_rot = this->tiltCardRef2.obj_rot;
			cardSpawned->obj_scale = this->tiltCardRef2.obj_scale;
			break;
		case 12:
			cardSpawned->obj_pos = Vector3D(this->flatCardRef.obj_pos.m_x + width_diff + 0.5f, this->flatCardRef.obj_pos.m_y + height_diff, this->flatCardRef.obj_pos.m_z);
			cardSpawned->obj_rot = this->flatCardRef.obj_rot;
			cardSpawned->obj_scale = this->flatCardRef.obj_scale;
			break;
		case 13:
			cardSpawned->obj_pos = Vector3D(this->tiltCardRef1.obj_pos.m_x + width_diff * 2, this->tiltCardRef1.obj_pos.m_y + height_diff * 2, this->tiltCardRef1.obj_pos.m_z);
			cardSpawned->obj_rot = this->tiltCardRef1.obj_rot;
			cardSpawned->obj_scale = this->tiltCardRef1.obj_scale;
			break;
		case 14:
			cardSpawned->obj_pos = Vector3D(this->cards[index - 1]->obj_pos.m_x + width_diff, this->cards[index - 1]->obj_pos.m_y, this->cards[index - 1]->obj_pos.m_z);
			cardSpawned->obj_rot = this->tiltCardRef2.obj_rot;
			cardSpawned->obj_scale = this->tiltCardRef2.obj_scale;
			break;

	}
}

void AppWindow::updateCards()
{
	for (int i = 0; i < this->cards.size(); i++) {
		this->cards[i]->onUpdate();
	}
}

void AppWindow::drawCards()
{
	for (int i = 0; i < this->cards.size(); i++) {
		this->cards[i]->draw();
	}
}
