// ArrLib.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "ArrLib.h"

#include <iostream>
using namespace std;


// This is an example of an exported variable
ARRLIB_API int nArrLib=0;

// This is an example of an exported function.
ARRLIB_API int fnArrLib(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CArrLib::CArrLib()
{
    return;
}

ARRLIB_API void arrPrint(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << '\t';
    }
    cout << '\n';
}