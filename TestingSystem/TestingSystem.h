
// TestingSystem.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestingSystemApp: 
// �йش����ʵ�֣������ TestingSystem.cpp
//

class CTestingSystemApp : public CWinApp
{
public:
	CTestingSystemApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
public:
	CString m_user;
	CString m_admission;
	CString m_id;
	CString m_question;
	CString m_true;
	CString m_speed;
	CString m_time;
	CString m_score;
	CString m_filename;
//	bool m_IsOk;
//	virtual void HtmlHelp(DWORD_PTR dwData, UINT nCmd = 0x000F);
};

extern CTestingSystemApp theApp;