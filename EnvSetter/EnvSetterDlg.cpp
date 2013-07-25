
// EnvSetterDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CEnvSetterDlg �Ի���




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


// CEnvSetterDlg ��Ϣ�������

BOOL CEnvSetterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CEnvSetterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		AfxMessageBox("���ݻ��������ɹ�");
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
		AfxMessageBox("��ԭ���������ɹ�");
	}
	else
	{
		AfxMessageBox("��ԭ��������ʧ��");
	}
	
}


void CEnvSetterDlg::OnBnClickedSetjavaenv()
{
	char szPath[MAX_PATH];     //���ѡ���Ŀ¼·��
	CString str;

	ZeroMemory(szPath, sizeof(szPath));  

	BROWSEINFO bi;  
	bi.hwndOwner = this->GetSafeHwnd();  
	bi.pidlRoot = NULL;  
	bi.pszDisplayName = szPath;  
	bi.lpszTitle = "��ѡ��JAVA��װĿ¼��";  
	bi.ulFlags = 0;  
	bi.lpfn = NULL;  
	bi.lParam = 0;  
	bi.iImage = 0;  
	//����ѡ��Ŀ¼�Ի���
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
			AfxMessageBox("���������������");
		}
		else 
		{
			AfxMessageBox("Ŀ¼ѡ�����������ѡ��");
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
