
// EnvSetter.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEnvSetterApp:
// �йش����ʵ�֣������ EnvSetter.cpp
//

class CEnvSetterApp : public CWinApp
{
public:
	CEnvSetterApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CEnvSetterApp theApp;