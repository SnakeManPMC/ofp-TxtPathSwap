// TxtPathSwapDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "MLODFile.h"


// CTxtPathSwapDlg dialog
class CTxtPathSwapDlg : public CDialog
{
// Construction
public:
	CTxtPathSwapDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TXTPATHSWAP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_EditFind;
	CString m_EditReplace;
	CListBox m_ListTextures;

	CMLODFile m_MlodFile;
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedReplace();
	afx_msg void OnLbnDblclkList1();
	afx_msg void OnLbnDblclkTextureList();
	afx_msg void OnBnClickedSave();
};
