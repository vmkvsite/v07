#### vježba 7

Koristeći [GDI+ biblioteku](https://learn.microsoft.com/en-us/windows/win32/api/_gdiplus/) napišite preglednik slika koji učitava barem sljedeće formate: JPEG, PNG, BMP, GIF, TIFF, EMF 
(standardni File Open dijalog ima filter za te formate). <br>
Naziv datoteke je ispisan pri dnu prozora (i ima sjenu).

Uputstva:
* za učitavanje slike koristite [Image::FromFile](https://learn.microsoft.com/en-us/windows/win32/api/gdiplusheaders/nf-gdiplusheaders-image-fromfile)
* za prikaz slike koristite [DrawImage](https://learn.microsoft.com/en-us/windows/win32/api/gdiplusgraphics/nf-gdiplusgraphics-graphics-drawimage(image_constrectf_))
* za prikaz teksta koristite [DrawString](https://learn.microsoft.com/en-us/windows/win32/api/gdiplusgraphics/nf-gdiplusgraphics-graphics-drawstring(constwchar_int_constfont_constrectf__conststringformat_constbrush))
* da biste izbjegli bljeskanje prikaza obradite i poruku WM_ERASEBKGND (`on_erase_bkgnd()`)
* naziv datoteke iz punog *path*-a možete dobiti koristeći [filename](https://en.cppreference.com/w/cpp/filesystem/path/filename) (iz `<filesystem>`)

![drawing](/screenshot.jpg?raw=true)

Za one koje želi znati više:<br>
`Image::FromFile` zapravo ne učitava sliku (učitavanje se događa na `DrawImage`). 
Bolje performanse se mogu postići ako se umjesto 
`Image*` zapamti `HBITMAP` (`Bitmap::GetHBITMAP`) 
i u `on_paint` koristi `StretchBlt` za crtanje slike.
