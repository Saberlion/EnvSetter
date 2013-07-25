
// EnvSetterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EnvSetter.h"
#include "EnvSetterDlg.h"
#include "afxdialogex.h"
#include <cstdlib>
#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CEnvSetterDlg 对话框




CEnvSetterDlg::CEnvSetterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEnvSetterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEnvSetterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CEnvSetterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BACKUPCURENV, &CEnvSetterDlg::OnBnClickedBackupcurenv)
	ON_BN_CLICKED(IDC_RESTOREENV, &CEnvSetterDlg::OnBnClickedRestoreenv)
	ON_BN_CLICKED(IDC_SETJAVAENV, &CEnvSetterDlg::OnBnClickedSetjavaenv)
END_MESSAGE_MAP()


// CEnvSetterDlg 消息处理程序

BOOL CEnvSetterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CEnvSetterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEnvSetterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CEnvSetterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CEnvSetterDlg::OnBnClickedBackupcurenv()
{
	CString path=GetEnv("path");
	CString   strFilename=_T("");   
	char  szFileters[]="save files (*.txt)|*.txt|ALL files (*.*)|*.*||";   
	CFileDialog  savedlg (FALSE,"txt","*.txt",OFN_OVERWRITEPROMPT,szFileters,this);   
	if (savedlg.DoModal()==IDOK)
	{   
		strFilename=savedlg.GetPathName();
		CStdioFile wFile;
		wFile.Open(strFilename,CFile::modeCreate|CFile::modeWrite);
		if (path)
		{
			wFile.WriteString(path);
		}
		wFile.Close();
		AfxMessageBox("备份环境变量成功");
	}
}


void CEnvSetterDlg::OnBnClickedRestoreenv()
{
	CString   strFilename=_T("");   
	char  szFileters[]="open files (*.txt)|*.txt|ALL files (*.*)|*.*||";   
	CFileDialog  opendlg (TRUE,"txt","*.txt",OFN_OVERWRITEPROMPT,szFileters,this);   
	if (opendlg.DoModal()==IDOK)
	{   
		strFilename=opendlg.GetPathName();   
	}
	CStdioFile rFile;
	CString strPath;
	rFile.Open(strFilename,CFile::modeRead);
	rFile.ReadString(strPath);
	AfxMessageBox(strPath);
	if (SetEnv("Path",strPath))
	{
		AfxMessageBox("还原环境变量成功");
	}
	else
	{
		AfxMessageBox("还原环境变量失败");
	}
	
}


void CEnvSetterDlg::OnBnClickedSetjavaenv()
{
	char szPath[MAX_PATH];     //存放选择的目录路径
	CString str;

	ZeroMemory(szPath, sizeof(szPath));  

	BROWSEINFO bi;  
	bi.hwndOwner = this->GetSafeHwnd();  
	bi.pidlRoot = NULL;  
	bi.pszDisplayName = szPath;  
	bi.lpszTitle = "请选择JAVA安装目录：";  
	bi.ulFlags = 0;  
	bi.lpfn = NULL;  
	bi.lParam = 0;  
	bi.iImage = 0;  
	//弹出选择目录对话框
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);  

	if(lp && SHGetPathFromIDList(lp, szPath))  
	{
		CFileFind finder;
		CString strJavaPath;
		strJavaPath = (CString)szPath + "\\bin\\java.exe";
		BOOL bWorking = finder.FindFile(strJavaPath);
		if(bWorking)
		{
			CString strPath = (CString)szPath + "\\bin";
			AddEnv("Path",strPath);
			strPath = (CString)szPath + "\\jre\\bin";
			AddEnv("Path",strPath);
			CString strClasspath = (CString)szPath + "\\lib\\dt.jar;" + (CString)szPath + "\\lib\\tools.jar";
			SetEnv("classpath",strClasspath);
			AfxMessageBox("环境变量设置完成");
		}
		else 
		{
			AfxMessageBox("目录选择错误，请重新选择！");
		}
	}
}


BOOL CEnvSetterDlg::AddEnv(LPCTSTR szName,LPCTSTR szPath)
{
	CString strKey = "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment";

	HKEY hKey;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, strKey, 0L, KEY_ALL_ACCESS, &hKey);

	DWORD dwType = 0, dw = 0;
	RegQueryValueEx(hKey, _T(szName), NULL, &dwType, NULL, &dw);

	CString sPath;
	LPTSTR lpsz = sPath.GetBufferSetLength(dw);
	RegQueryValueEx(hKey, _T(szName), NULL, &dwType, (BYTE*)lpsz, &dw);
	sPath.ReleaseBuffer();

	sPath = CString(szPath) + _T(";") + sPath;
	RegSetValueEx(hKey, _T(szName), NULL, REG_EXPAND_SZ,
		(BYTE * const)(LPCSTR)sPath, (sPath.GetLength()+1)*sizeof(TCHAR));

	RegCloseKey(hKey);

	DWORD dwRet;
	SendMessageTimeout(HWND_BROADCAST,WM_SETTINGCHANGE,0,
		(LPARAM)"Environment", SMTO_ABORTIFHUNG, 5000,&dwRet);

	return TRUE;
}




CString CEnvSetterDlg::GetEnv(LPCTSTR name)
{
	CString strKey = "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment";

	HKEY hKey;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, strKey, 0L, KEY_ALL_ACCESS, &hKey);

	DWORD dwType = 0, dw = 0;
	RegQueryValueEx(hKey, _T(name), NULL, &dwType, NULL, &dw);

	CString sPath;
	LPTSTR lpsz = sPath.GetBufferSetLength(dw);
	RegQueryValueEx(hKey, _T(name), NULL, &dwType, (BYTE*)lpsz, &dw);
	sPath.ReleaseBuffer();
	AfxMessageBox(sPath);
	return sPath;
}


BOOL CEnvSetterDlg::SetEnv(LPCTSTR name, LPCTSTR value)
{
	CString strKey = "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment";

	HKEY hKey;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, strKey, 0L, KEY_ALL_ACCESS, &hKey);

	CString sPath;
	sPath = CString(value) + _T(";") ;
	RegSetValueEx(hKey, _T(name), NULL, REG_EXPAND_SZ,
		(BYTE * const)(LPCSTR)sPath, (sPath.GetLength()+1)*sizeof(TCHAR));

	RegCloseKey(hKey);

	DWORD dwRet;
	SendMessageTimeout(HWND_BROADCAST,WM_SETTINGCHANGE,0,
		(LPARAM)"Environment", SMTO_ABORTIFHUNG, 5000,&dwRet);
	return TRUE;
}
