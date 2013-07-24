
// EnvSetterDlg.h : ͷ�ļ�
//

#pragma once


// CEnvSetterDlg �Ի���
class CEnvSetterDlg : public CDialogEx
{
// ����
public:
	CEnvSetterDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ENVSETTER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
