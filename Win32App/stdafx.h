// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <atlbase.h>
#include <atlstr.h>

// TODO: reference additional headers your program requires here



#include <atlwin.h>
#include <atltypes.h>
#include <atlcoll.h>
#include <atlimage.h>
#include <cstdarg>
#include <Dbghelp.h>
#include <locale.h>
#include <time.h>
#include <list>
#include <vcclr.h>
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>



using namespace ATL;
using namespace System;
using namespace System::Windows;
using namespace System::Windows::Documents;
using namespace System::Threading;
using namespace System::Windows::Controls;
using namespace System::Windows::Media;
using namespace System::Windows::Media::Animation;
using namespace HhdWpfLib;
using namespace msclr::interop;



extern HINSTANCE g_hInst;