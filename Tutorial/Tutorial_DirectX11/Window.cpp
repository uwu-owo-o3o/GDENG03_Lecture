#include "Window.h"
#include <exception>

Window* window = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
    case WM_CREATE:

        break;
    case WM_SETFOCUS:
        //Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        if (window) window->onFocus();
        break;
    case WM_KILLFOCUS:
        //Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        if (window) window->onKillFocus();
        break;
    case WM_DESTROY:
        window->onDestroy();
        ::PostQuitMessage(0);
        break;
    default:
        return ::DefWindowProc(hwnd, msg, wparam, lparam);
    }

    return NULL;
}

Window::Window()
{
    WNDCLASSEX wc;
    wc.cbClsExtra = NULL;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbWndExtra = NULL;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = NULL;
    wc.lpszClassName = L"MyWindowClass";
    wc.lpszMenuName = L"";
    wc.style = NULL;

    wc.lpfnWndProc = &WndProc;

    if (!::RegisterClassEx(&wc)) //If Registration of class fails, return false
        throw std::exception("Window Class Register failed.");

    if (!window)
        window = this;

    m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
        NULL, NULL, NULL, this);

    ::ShowWindow(m_hwnd, SW_SHOW);
    ::UpdateWindow(m_hwnd);

    m_isRun = true;
   
}



bool Window::broadcast()
{
    MSG msg;
    if (!this->m_is_init) {
        //Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
        SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
        
        window->onCreate();
        this->m_is_init = true;
    }

    window->onUpdate();
    while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    Sleep(0);
    return true;
}


Window::~Window()
{
    
}

bool Window::isRun()
{
    if (m_isRun) {
        this->broadcast();
    }
    return m_isRun;
}

RECT Window::getClientWindowRect()
{
    RECT rc;
    ::GetClientRect(this->m_hwnd, &rc);
    return rc;
}

void Window::onUpdate()
{
}

void Window::onDestroy()
{
    m_isRun = false;
}

void Window::onFocus()
{
}

void Window::onKillFocus()
{
}
