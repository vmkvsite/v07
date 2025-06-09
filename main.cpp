#include "main.h"
#include "rc.h"
#include <filesystem>
#include <commdlg.h>

void main_window::on_paint(HDC hdc)
{
	RECT clientRect;
	GetClientRect(*this, &clientRect);

	using namespace Gdiplus;
	Graphics graphics(hdc);

	if (loaded_image && !current_filename.empty()) {
		graphics.DrawImage(loaded_image.get(), 0, 0, clientRect.right, clientRect.bottom);

		std::filesystem::path file_path(current_filename);
		std::wstring display_name = file_path.filename().wstring();

		Font text_font(L"Arial", 30);
		SolidBrush black_brush(Color::Black);
		SolidBrush white_brush(Color::White);

		RectF text_rect_shadow(static_cast<REAL>(clientRect.left + 3),
			static_cast<REAL>(clientRect.top + 3),
			static_cast<REAL>(clientRect.right),
			static_cast<REAL>(clientRect.bottom));
		RectF text_rect_main(static_cast<REAL>(clientRect.left),
			static_cast<REAL>(clientRect.top),
			static_cast<REAL>(clientRect.right),
			static_cast<REAL>(clientRect.bottom));

		StringFormat string_format;
		string_format.SetAlignment(StringAlignmentCenter);
		string_format.SetLineAlignment(StringAlignmentFar);

		graphics.DrawString(display_name.c_str(), -1, &text_font, text_rect_shadow, &string_format, &black_brush);

		graphics.DrawString(display_name.c_str(), -1, &text_font, text_rect_main, &string_format, &white_brush);
	}
}

void main_window::on_command(int id)
{
	switch (id)
	{
	case ID_OPEN:
	{
		TCHAR file_path[MAX_PATH];
		file_path[0] = _T('\0');

		TCHAR file_filter[] = _T("Image Files\0*.jpeg;*.jpg;*.png;*.bmp;*.gif;*.tiff;*.tif;*.emf\0")
			_T("JPEG Files\0*.jpeg;*.jpg\0")
			_T("PNG Files\0*.png\0")
			_T("BMP Files\0*.bmp\0")
			_T("GIF Files\0*.gif\0")
			_T("TIFF Files\0*.tiff;*.tif\0")
			_T("EMF Files\0*.emf\0")
			_T("All Files\0*.*\0\0");

		OPENFILENAME open_dialog;
		ZeroMemory(&open_dialog, sizeof(open_dialog));

		open_dialog.lStructSize = sizeof(open_dialog);
		open_dialog.hwndOwner = *this;
		open_dialog.lpstrFile = file_path;
		open_dialog.nMaxFile = MAX_PATH;
		open_dialog.lpstrFilter = file_filter;
		open_dialog.nFilterIndex = 1;
		open_dialog.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetOpenFileName(&open_dialog))
		{
			current_filename = file_path;
			loaded_image = std::make_unique<Gdiplus::Image>(file_path);

			if (loaded_image->GetLastStatus() == Gdiplus::Ok) {
				InvalidateRect(*this, nullptr, TRUE);
			}
			else {
				loaded_image.reset();
				current_filename.clear();
				MessageBox(*this, _T("Failed to load the selected image file."), _T("Error"), MB_OK | MB_ICONERROR);
			}
		}
	}
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

bool main_window::on_erase_bkgnd(HDC dc)
{
	return true;
}

int WINAPI _tWinMain(HINSTANCE instance, HINSTANCE, LPTSTR, int)
{
	gdiplus_application app;
	main_window wnd;
	wnd.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP 7"), (int64_t)LoadMenu(instance, MAKEINTRESOURCE(IDM_MAIN)));
	return app.run();
}