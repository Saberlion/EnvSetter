
// EnvSetterDlg.h : 头文件
//

#pragma once


// CEnvSetterDlg 对话框
class CEnvSetterDlg : public CDialogEx
{
// 构造
public:
	CEnvSetterDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ENVSETTER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	BOOL CEnvSetterDlg::AddEnv(LPCTSTR szName,LPCTSTR szPath);
	afx_msg void OnBnClickedBackupcurenv();
	afx_msg void OnBnClickedRestoreenv();
	afx_msg void OnBnClickedSetjavaenv();
	CString GetEnv(LPCTSTR name);
	BOOL SetEnv(LPCTSTR name, LPCTSTR value);
};
