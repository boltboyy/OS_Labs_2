#include <Windows.h>
#include <iostream>

using namespace std;

struct Data
{
	int* arr;
	int n, min, max;
	double average;
};
typedef void(*ArrPrintFunc)(int*, int);

DWORD WINAPI MinMax(LPVOID param);
DWORD WINAPI average(LPVOID param);

int main()
{
	int n;
	cin >> n;
	if (n <= 0)
	{
		cout << "n must be positive!" << '\n';
		return 1;
	}
	int* arr = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	Data data = {};
	data.arr = arr;
	data.n = n;
	HMODULE hLib = LoadLibraryA("ArrLib.dll");
	if (hLib == NULL)
	{
		delete[] arr;
		cout << "DLL not found";
		return 1;
	}
	ArrPrintFunc print = (ArrPrintFunc)GetProcAddress(hLib, "arrPrint");
	if (print == NULL)
	{
		delete[] arr;
		FreeLibrary(hLib);
		cout << "Function not found";
		return 1;
	}
	print(arr, n);
	FreeLibrary(hLib);
	DWORD idMinMax;
	HANDLE hMinMax = CreateThread(NULL, 0, MinMax, &data, 0, &idMinMax);
	if (hMinMax == NULL)
	{
		delete[] arr;
		return GetLastError();
	}
	DWORD idaverage;
	HANDLE haverage = CreateThread(NULL, 0, average, &data, 0, &idaverage);
	if (haverage == NULL)
	{
		delete[] arr;
		return GetLastError();
	}
	WaitForSingleObject(hMinMax, INFINITE);
	WaitForSingleObject(haverage, INFINITE);
	CloseHandle(hMinMax);
	CloseHandle(haverage);
	cout << "min= " << data.min << '\t' << "max= " << data.max << '\t' << "average= " << data.average << '\n';
	for (int i = 0; i < n; i++)
	{
		if (arr[i] == data.min || arr[i] == data.max) arr[i] = (int)data.average;
	}
	hLib = LoadLibraryA("ArrLib.dll");
	if (hLib == NULL)
	{
		delete[] arr;
		cout << "DLL not found";
		return 1;
	}
	print = (ArrPrintFunc)GetProcAddress(hLib, "arrPrint");
	if (print == NULL)
	{
		delete[] arr;
		FreeLibrary(hLib);
		cout << "Function not found";
		return 1;
	}
	print(arr, n);
	FreeLibrary(hLib);
	delete[] arr;
	return 0;
}

DWORD WINAPI MinMax(LPVOID param)
{
	Data* d = (Data*)param;
	d->min = d->arr[0];
	d->max = d->arr[0];
	for (int i = 1; i < d->n; i++)
	{
		if (d->arr[i] < d->min) d->min = d->arr[i];
		Sleep(7);
		if (d->arr[i] > d->max) d->max = d->arr[i];
		Sleep(7);
	}
	cout << "min= " << d->min << '\t' << "max= " <<  d->max << '\n';
	return 0;
}

DWORD WINAPI average(LPVOID param)
{
	Data* d = (Data*)param;
	double tmp = 0;
	for (int i = 0; i < d->n; i++)
	{
		tmp = tmp + d->arr[i];
		Sleep(12);
	}
	d->average = tmp / d->n;
	cout << "average= " << d->average << '\n';
	return 0;
}