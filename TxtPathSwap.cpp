// TxtPathSwap.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TxtPathSwap.h"
#include "TxtPathSwapDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTxtPathSwapApp

BEGIN_MESSAGE_MAP(CTxtPathSwapApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTxtPathSwapApp construction

CTxtPathSwapApp::CTxtPathSwapApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTxtPathSwapApp object

CTxtPathSwapApp theApp;


// CTxtPathSwapApp initialization

BOOL CTxtPathSwapApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();


	CTxtPathSwapDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
