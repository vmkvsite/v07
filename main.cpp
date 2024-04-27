#include "main.h"
#include "rc.h"
#include <filesystem>

void main_window::on_paint(HDC hdc) 
{
}

void main_window::on_command(int id) 
{
	switch (id) 
	{
		case ID_OPEN:
			break;
		case ID_EXIT:
			DestroyWindow(*this);
			break;
	}
}

void main_window::on_destroy() 
{
	::PostQuitMessage(0);
}

int WINAPI _tWinMain(HINSTANCE instance, HINSTANCE, LPTSTR, int)
{
	gdiplus_application app;
	main_window wnd;
	wnd.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP 7"), (int64_t)LoadMenu(instance, MAKEINTRESOURCE(IDM_MAIN)));
	return app.run();
}
