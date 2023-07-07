#include <iostream>
#include <windows.h>
void m_click(int x, int y)
{
	INPUT click[3];
	click[0].type = INPUT_MOUSE;
	click[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	click[0].mi.dx = /*   */ x * 65535 / 1920;
	click[0].mi.dy = 65535 - y * 65535 / 1080;
	click[1].type = INPUT_MOUSE;
	click[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	click[2].type = INPUT_MOUSE;
	click[2].mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(3, click, sizeof(INPUT));
}
int main() {
	HDC hdcScreen;
	int x_min = 656, x_max = 1263, y_min = 1, y_max = 1080, n = 4,
		x_d = (x_max - x_min) / 8, y_d = (y_max - y_min) / n, y, j, x, color, last = 0, k = 0;
	for (;;)
	{
		std::cout << "-\tstopped" << std::endl;
		for (; !(GetKeyState('1') & 0x8000); Sleep(100)) {}
		std::cout << "+\tstarted" << std::endl;
		for (; !(GetKeyState('2') & 0x8000);)
		{
			hdcScreen = GetDC(NULL);
			color = 1;
			for (y = y_min + y_d / 2; y < y_max && color != 0; y += y_d)
			{
				for (j = 1; j < 8 && color != 0; j += 2)
				{
					if (j != last)
					{
						x = x_min + x_d * j;
						color = GetPixel(hdcScreen, x, 1080 - y);
						if (color == 0)
						{
							m_click(x, y);
							last = j;
						}
					}
				}
			}
			ReleaseDC(NULL, hdcScreen);
		}
	}
	return 0;
}
