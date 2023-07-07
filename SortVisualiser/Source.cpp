#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>
//--------------------------------------------------
int n = 0, swaps = 0, checks = 0, draws = 0, X, Y;
int delay[] = { 0,0,0,0,0,0 };
int optimisation = 2;
std::vector<LPCTSTR> symbols = { L" ", L"@", L"█" };
std::vector<int> a, b;
//--------------------------------------------------
void SetWindow(int Width, int Height);
void _swap(int i, int j);
void _draw(int d = 0);
void _shuffle();
void selectionSort();
void bubbleSort();
int partition(int low, int high);
void quickSort(int low, int high);
int getMax(int n);
void countSort(int exp);
void radixSort();
void cocktailSort();
void insertionSort();
//--------------------------------------------------
int main(int argc, char* argv[])
{
	//SetWindow(100, 25);
	//srand(int(time(NULL)));
	system("cls");
	std::cin.tie(nullptr);
	std::ios_base::sync_with_stdio(false);
	std::vector<std::string> types = { "selection", "bubble", "quick", "radix", "cocktail", "insertion" };
	if (argc != 1)
	{
		n = int(*argv[1] - '0');
		if (n == 0)
			n = rand() % types.size() + 1;
	}
	if (n == 0)
	{
		for (int i = 0; i < types.size(); i++)
			std::cout << i + 1 << ") " << types[i] << "\t\n";
		std::cin >> n;
		system("cls");
	}
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	X = (int)(csbi.srWindow.Right - csbi.srWindow.Left + 1);
	Y = (int)(csbi.srWindow.Bottom - csbi.srWindow.Top);
	for (int i = 0; i < X; i++)
	{
		a.push_back(i);
		b.push_back(-1);
	}
	_draw(1000);
	_shuffle();
	_draw(1000);
	swaps = draws = 0;
	switch (n)
	{
	case 1:
		selectionSort();
		break;
	case 2:
		bubbleSort();
		break;
	case 3:
		quickSort(0, X - 1);
		break;
	case 4:
		radixSort();
		break;
	case 5:
		cocktailSort();
		break;
	case 6:
		insertionSort();
		break;
	default:
		return 0;
	}
	system("cls");
	std::cout << "size:\t" << X << "\nswaps:\t" << swaps << "\nchecks:\t" << checks << "\ndraws:\t" << draws << std::endl;
	for (int i = 0; i < X; i++)
		b[i] = -1;
	_draw();
	if (argc == 1)
		system("pause");
	return 0;
}
//--------------------------------------------------
void SetWindow(int Width, int Height)
{
	_COORD coord = { short(Width), short(Height) };
	_SMALL_RECT Rect = { 0, 0, short(Width - 1), short(Height - 1) };
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(Handle, coord);
	SetConsoleWindowInfo(Handle, TRUE, &Rect);
}
//--------------------------------------------------
void _swap(int i, int j)
{
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
	swaps++;
}
//--------------------------------------------------
void _draw(int d)
{

	DWORD dw;
	COORD here = { 0, 0 };
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (optimisation == 2)
	{
		for (here.X = 0; here.X < X; here.X++)
		{
			if (a[here.X] != b[here.X])
			{
				int j;
				for (j = 0; !(j * X > a[here.X] * (Y + 1)); j++)
				{
					if (a[here.X] > b[here.X])
					{
						draws++;
						here.Y = Y - j;
						WriteConsoleOutputCharacter(hStdOut, symbols[1], 1, here, &dw);
					}
				}
				if (a[here.X] < b[here.X])
				{
					for (; j < Y + 1; j++)
					{
						draws++;
						here.Y = Y - j;
						WriteConsoleOutputCharacter(hStdOut, symbols[0], 1, here, &dw);
					}
				}
				b[here.X] = a[here.X];
			}
		}
	}
	else
	{
		if (optimisation == 1)
		{
			system("cls");
			for (here.X = 0; here.X < X; here.X++)
			{
				int j;
				for (j = 0; !(j * X > a[here.X] * (Y + 1)); j++)
				{
					draws++;
					here.Y = Y - j;
					WriteConsoleOutputCharacter(hStdOut, symbols[1], 1, here, &dw);
				}
			}
		}
		else
		{
			if (optimisation == 0)
			{
				std::stringstream ss;
				system("cls");
				for (here.Y = 0; here.Y < Y; here.Y++) {
					for (here.X = 0; here.X < X; here.X++)
					{
						if (!((here.Y) * X > a[X - 1 - here.X] * (Y - 1)))
							ss << symbols[1];
						else
							ss << symbols[0];
					}
					ss << std::endl;
				}
				draws++;
				std::cout << ss.str();
			}
		}
	}
	if (d != 0)
		Sleep(d);
	else
		if (delay[n - 1] != 0)
			Sleep(delay[n - 1]);
}
//--------------------------------------------------
void _shuffle()
{
	for (int i = 0; i < X; i++)
	{
		_swap(i, floor(rand() * i % (X - 1)));
		_draw();
	}
}
//--------------------------------------------------
void bubbleSort()
{
	for (int i = 0; i < X; i++)
	{
		for (int j = X - 1; j > i; j--)
		{
			if (a[j] < a[j - 1]) {
				_swap(j, j - 1);
				_draw();
			}
			checks++;
		}
	}
}
//--------------------------------------------------
void selectionSort()
{
	for (int i = 0; i < X - 1; i++)
	{
		int min = i;
		for (int j = i; j < X; j++)
		{
			if (a[j] < a[min])
			{
				min = j;
			}
			checks++;
		}
		_swap(i, min);
		_draw();
	}
}
//--------------------------------------------------
int partition(int low, int high) {
	int pivot = a[high];
	int i = low - 1;
	for (int j = low; j <= high - 1; j++)
	{
		if (a[j] < pivot)
		{
			i++;
			_swap(i, j);
			_draw();
		}
		checks++;
	}
	_swap(i + 1, high);
	return i + 1;
}
void quickSort(int low, int high)
{
	if (low < high)
	{
		int pi = partition(low, high);
		quickSort(low, pi - 1);
		quickSort(pi + 1, high);
	}
}
//--------------------------------------------------
int getMax(int n)
{
	int mx = a[0];
	for (int i = 1; i < n; i++)
		if (a[i] > mx)
			mx = a[i];
	return mx;
}
void countSort(int exp)
{
	int* output = new int[X];
	int i, count[10] = { 0 };
	for (i = 0; i < X; i++)
		count[(a[i] / exp) % 10]++;
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];
	for (i = X - 1; i >= 0; i--)
	{
		output[count[(a[i] / exp) % 10] - 1] = a[i];
		count[(a[i] / exp) % 10]--;
	}
	for (i = 0; i < X; i++)
		a[i] = output[i];
	delete[] output;
}
void radixSort()
{
	int m = getMax(X);
	for (int exp = 1; m / exp > 0; exp *= 10)
	{
		countSort(exp);
		_draw();
	}
}
//--------------------------------------------------
void cocktailSort()
{
	int start = 0, end = X - 1;
	for (int n = 1; n == 1 || n == 2;)
	{
		if (n == 1)
		{
			n = 0;
			for (int i = start; i < end; i++)
			{
				if (a[i] > a[i + 1])
				{
					_swap(i, i + 1);
					_draw();
					n = 2;
				}
				checks++;
			}
			end--;
		}
		else
		{
			if (n == 2)
			{
				n = 0;
				for (int i = end - 1; i >= start; i--)
				{
					if (a[i] > a[i + 1])
					{
						_swap(i, i + 1);
						_draw();
						n = 1;
					}
					checks++;
				}
				start++;
			}
		}
	}
}
//--------------------------------------------------
void insertionSort()
{
	int i, key, j;
	for (i = 1; i < X; i++)
	{
		key = a[i];
		j = i - 1;
		while (j >= 0 && a[j] > key)
		{
			a[j + 1] = a[j];
			j = j - 1;
			_draw();
			swaps++;
		}
		a[j + 1] = key;
		swaps++;
	}
}
//--------------------------------------------------
