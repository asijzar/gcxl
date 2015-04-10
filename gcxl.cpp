/*
gcxl.cpp
Graphic ConteXt Library
Created by Asijzar, 2015
All rights reserved
*/

#include "gcxl.h"

using namespace nsgcxl;

LRESULT CALLBACK gcxl::static_wnd_proc(HWND h_wnd, UINT u_msg, WPARAM w_param, LPARAM l_param) {
	HDC h_dc;
	PAINTSTRUCT ps;
	RECT rect;

	COLORREF color = RGB(255, 0, 0);
	
	switch (u_msg) {
		case WM_PAINT:
			h_dc = BeginPaint(h_wnd, &ps); 
			for (int i = 0; i < 100; i++)
				for (int j = 0; j < 100; j++)
					SetPixel(h_dc, i, j, color);
			EndPaint(h_wnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(NULL);
			break;
		default:
			return DefWindowProc(h_wnd, u_msg, w_param, l_param);
	}
	return NULL;
}

int APIENTRY gcxl::WinMain(HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR lp_cmd_line, int n_cmd_show) {
	HWND h_main_wnd;
	TCHAR sz_class_name[] = "w_class";
	MSG msg;

	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = static_wnd_proc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = sz_class_name;
	wc.cbWndExtra = NULL;
	wc.cbClsExtra = NULL;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hInstance = h_instance;
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Wrong window class!", "Error", MB_OK);
		return NULL;
	}

	h_main_wnd = CreateWindow(
		sz_class_name,
		win_name.c_str(),
		WS_OVERLAPPEDWINDOW | WS_VSCROLL,
		CW_USEDEFAULT,
		NULL,
		win_width,
		win_height,
		HWND(NULL),
		NULL,
		h_instance,
		NULL
	);
	if (!h_main_wnd) {
		MessageBox(NULL, "Can't create window!", "Error", MB_OK);
		return NULL;
	}

	ShowWindow(h_main_wnd, n_cmd_show);
	UpdateWindow(h_main_wnd);

	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

gcxl::gcxl() : win_width(400), win_height(400), win_name("Window"), clear_color(0) {}
		
int gcxl::get_window_width() {
	return win_width;
}

int gcxl::get_window_height() {
	return win_height;
}

void gcxl::set_window_size(int width, int height) {
	win_width = width;
	win_height = height;
}

void gcxl::set_window_name(const char* name) {
	win_name = name;
}

void gcxl::set_clear_color(int color) {
	clear_color = color;
}

void gcxl::init() {
	STARTUPINFOW si;
	GetStartupInfoW(&si);
	WinMain(GetModuleHandle(0), NULL, GetCommandLineA(), si.wShowWindow);
}