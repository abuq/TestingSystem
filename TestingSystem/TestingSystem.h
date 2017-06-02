
// TestingSystem.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CTestingSystemApp: 
// 有关此类的实现，请参阅 TestingSystem.cpp
//

class CTestingSystemApp : public CWinApp
{
public:
	CTestingSystemApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

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