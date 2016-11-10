
#include "stdafx.h"
#include "TestEMail.h"
#include "CSendMail/CSendMail.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CWinApp theApp;

using namespace std;



void TestSendMail()
{
	SMailInfo mailInfo;

	//126 smtp
	mailInfo.m_pcUserName =             "isaacsaga@gmail.com";        
	mailInfo.m_pcUserPassWord =         "password";        			
	mailInfo.m_pcSenderName =           "isaacsaga@gmail.com";         
	mailInfo.m_pcSender =               "isaacsaga@gmail.com";         

	mailInfo.m_pcReceiver =             "yzhou45@stevens.edu";       
	mailInfo.m_pcTitle =                "test email";              
	mailInfo.m_pcBody =                 "test";   
	mailInfo.m_pcIPAddr =               "";                       
	mailInfo.m_pcIPName =               "smtp.gmail.com" ;           


	CSendMail smtpMail;
	smtpMail.SendMail(mailInfo);
}



int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initiate MFC and return fail when it fails.
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		
		_tprintf(_T("¥ÌŒÛ: MFC ≥ı ºªØ ß∞‹\n"));
		nRetCode = 1;
	}
	else
	{
		what-else-needs-to-do;
	}

	TestSendMail();
	return nRetCode;
}

