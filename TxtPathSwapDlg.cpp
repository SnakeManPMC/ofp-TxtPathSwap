// TxtPathSwapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TxtPathSwap.h"
#include "TxtPathSwapDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTxtPathSwapDlg dialog



CTxtPathSwapDlg::CTxtPathSwapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTxtPathSwapDlg::IDD, pParent)
	, m_EditFind(_T(""))
	, m_EditReplace(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTxtPathSwapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_EditFind);
	DDV_MaxChars(pDX, m_EditFind, 31);
	DDX_Text(pDX, IDC_EDIT2, m_EditReplace);
	DDV_MaxChars(pDX, m_EditReplace, 31);
	DDX_Control(pDX, IDC_LIST1, m_ListTextures);
}

BEGIN_MESSAGE_MAP(CTxtPathSwapDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedOpen)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedReplace)
	ON_LBN_DBLCLK(IDC_LIST1, OnLbnDblclkTextureList)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedSave)
END_MESSAGE_MAP()


// CTxtPathSwapDlg message handlers

BOOL CTxtPathSwapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//ShowWindow(SW_MINIMIZE);

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTxtPathSwapDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTxtPathSwapDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTxtPathSwapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTxtPathSwapDlg::OnBnClickedOpen()
{
	CFileDialog filedialog(TRUE, ".p3d", NULL, OFN_FILEMUSTEXIST, "OFP MLOD Files(*.p3d)|*.p3d|All Files (*.*)|*.*||");
	if (filedialog.DoModal() != IDOK) return;

	CFile in;
	CFileException ex;
	if (!in.Open(filedialog.GetPathName(), CFile::modeRead | CFile::shareDenyWrite, &ex)) {
		ex.ReportError();
		return;
	}
	
	AfxGetApp()->DoWaitCursor(1);

	m_MlodFile.Read(&in);

	in.Close();

	m_ListTextures.ResetContent();

	POSITION pos = m_MlodFile.textureList.GetHeadPosition();
	for (int i = 0; i < m_MlodFile.textureList.GetCount(); i++) {
		LPCTSTR str = (LPCTSTR)m_MlodFile.textureList.GetNext(pos);
		if (m_ListTextures.FindStringExact(-1, str) == LB_ERR && strlen(str) > 0) {
			m_ListTextures.AddString(str);
		}
		
	}

	AfxGetApp()->DoWaitCursor(-1);
}

void CTxtPathSwapDlg::OnBnClickedReplace()
{

	UpdateData(TRUE);

	AfxGetApp()->DoWaitCursor(1);

	POSITION pos;


	pos = m_MlodFile.textureList.GetHeadPosition();

	CString findstr = m_EditFind;
	findstr.MakeLower();

	for (int i = 0; i < m_MlodFile.textureList.GetCount(); i++) {
		char *str = (char *)m_MlodFile.textureList.GetNext(pos);
		CString tmpstr = str;
		tmpstr.MakeLower();
		if (tmpstr.Find(findstr) != -1) {

			tmpstr.Replace(findstr, m_EditReplace);
			
			if (tmpstr.GetLength() > 31) {
				MessageBox("Texture path would exceed 31 chars");
				break;
			}
			strncpy(str, tmpstr, 31);
		}
	}
	m_ListTextures.ResetContent();

	pos = m_MlodFile.textureList.GetHeadPosition();
	for (int i = 0; i < m_MlodFile.textureList.GetCount(); i++) {
		LPCTSTR str = (LPCTSTR)m_MlodFile.textureList.GetNext(pos);
		if (m_ListTextures.FindStringExact(-1, str) == LB_ERR && strlen(str) > 0) {
			m_ListTextures.AddString(str);
		}
		
	}

	AfxGetApp()->DoWaitCursor(-1);
}
void CTxtPathSwapDlg::OnLbnDblclkTextureList()
{
	UpdateData(TRUE);
	
	int sel = m_ListTextures.GetCurSel();
	if (sel != LB_ERR) {
		m_ListTextures.GetText(sel, m_EditFind);
	}

	UpdateData(FALSE);
}

void CTxtPathSwapDlg::OnBnClickedSave()
{
	if (m_MlodFile.size < 1 || m_MlodFile.data == NULL) {
		MessageBox("No MLOD file loaded yet!");
		return;
	}

	CFileDialog filedialog(FALSE, ".p3d", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "OFP MLOD Files(*.p3d)|*.p3d|All Files (*.*)|*.*||");
	if (filedialog.DoModal() != IDOK) return;

	CFile out;
	CFileException ex;
	
	if (!out.Open(filedialog.GetPathName(), CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate)) {
		ex.ReportError();
		return;
	}

	if (m_MlodFile.Write(&out) != m_MlodFile.size) {
		MessageBox("Failure while writing output file!");
	};
	out.Close();
		
}
