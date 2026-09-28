// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the ARRLIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// ARRLIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef ARRLIB_EXPORTS
#define ARRLIB_API __declspec(dllexport)
#else
#define ARRLIB_API __declspec(dllimport)
#endif

// This class is exported from the dll
class ARRLIB_API CArrLib {
public:
	CArrLib(void);
	// TODO: add your methods here.
};

extern ARRLIB_API int nArrLib;

ARRLIB_API int fnArrLib(void);

extern "C" ARRLIB_API void arrPrint(int arr[], int n);
