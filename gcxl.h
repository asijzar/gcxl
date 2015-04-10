/*
gcxl.h
Graphic ConteXt Library
Created by Asijzar, 2015
All rights reserved
*/

#include <windows.h>
#include <string>
#include <map>

namespace nsgcxl {
	class gcxl {
	private:
		int win_width;
		int win_height;
		std::string win_name;
		int clear_color;
		
		static LRESULT CALLBACK static_wnd_proc(HWND h_wnd, UINT u_msg, WPARAM w_param, LPARAM l_param);
		int APIENTRY WinMain(HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR lp_cmd_line, int n_cmd_show);
		
	public:
		gcxl();
		
		int get_window_width();
		int get_window_height();
	
		void set_window_size(int width, int height);
		void set_window_name(const char* name);
		void set_clear_color(int color);
		
		void init();
	};
}