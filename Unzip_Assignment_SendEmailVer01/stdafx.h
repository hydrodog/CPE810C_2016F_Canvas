

#pragma once

#ifndef WINVER				
#define WINVER 0x0501		
#endif

#ifndef _WIN32_WINNT		
#define _WIN32_WINNT 0x0501
#endif						

#ifndef _WIN32_WINDOWS		
#define _WIN32_WINDOWS 0x0410 
#endif

#ifndef _WIN32_IE			
#define _WIN32_IE 0x0600	//those 4 allow your code can be used in different version of windows os.
#endif

#include <stdio.h>
#include <tchar.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		
#endif

#include <afx.h>
#include <afxwin.h>         // MFC core and std
#include <afxext.h>         // MFC extend
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		 
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			
#endif 

#include <iostream>


#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	

#include <atlbase.h>
#include <atlstr.h>

#pragma warning( disable : 4996)
#pragma warning( disable : 4267)


