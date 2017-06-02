// Score.cpp : 实现文件
//

#include "stdafx.h"
#include "TestingSystem.h"
#include "Score.h"
#include "afxdialogex.h"
#include "PDFLib\PDFLib.hpp"
#pragma comment(lib, "PDFLib\\PDFLib.lib")
using namespace pdflib;
using namespace std;
// CScore 对话框

IMPLEMENT_DYNAMIC(CScore, CDialogEx)

CScore::CScore(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_edit1(_T(""))
	, m_user(_T(""))
	, m_admission(_T(""))
	, m_id(_T(""))
	, m_question(_T(""))
	, m_true(_T(""))
	, m_speed(_T(""))
	, m_time(_T(""))
	, m_score(_T(""))
	, m_filename(_T(""))
{

}

CScore::~CScore()
{
}

void CScore::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_STATIC1, m_user);
	DDX_Text(pDX, IDC_STATIC2, m_admission);
	DDX_Text(pDX, IDC_STATIC3, m_id);
	DDX_Text(pDX, IDC_STATIC4, m_question);
	DDX_Text(pDX, IDC_STATIC5, m_true);
	DDX_Text(pDX, IDC_STATIC6, m_speed);
	DDX_Text(pDX, IDC_STATIC7, m_time);
	DDX_Text(pDX, IDC_STATIC8, m_score);
}

BEGIN_MESSAGE_MAP(CScore, CDialogEx)
	ON_BN_CLICKED(IDOK, &CScore::OnBnClickedOk)
END_MESSAGE_MAP()


// CScore 消息处理程序

void CScore::OnBnClickedOk()
{
	PDFlib pdf;

	pdf.begin_document(L"D://Score.pdf",L"");
	pdf.set_info(L"Creator",L"PDF");
	pdf.set_info(L"Author",L"宋亚旭");
	pdf.set_info(L"Title", L"成绩单");
	pdf.set_info(L"Subject", L"PDF");
	pdf.set_info(L"Keywords", L"宏图法院速录评测系统");

	pdf.begin_page(a4_width, a4_height);
	int font_song = pdf.load_font(L"仿宋", L"unicode",L"");
	pdf.setfont(font_song, 12);
	pdf.set_text_pos(a4_width/2-20, a4_height - 70);
	pdf.setcolor(L"fill", L"rgb", 0.147f, 0.147f, 0.147f, 0);
	pdf.setfont(font_song, 6);
	pdf.continue_text(L"宏图法院速录评测系统");

	pdf.setcolor(L"stroke", L"rgb", 0, 0, 0, 0);
	pdf.moveto(50, a4_height - 80);
	pdf.lineto(a4_width - 50, a4_height - 80);
	pdf.moveto(50, a4_height - 78);
	pdf.lineto(a4_width - 50, a4_height - 78);
	pdf.moveto(50, a4_height - 100);
	pdf.lineto(a4_width - 50, a4_height - 100);
	pdf.moveto(50, a4_height - 100);
	pdf.lineto(50,a4_height-760);
	pdf.moveto(a4_width - 50, a4_height - 100);
	pdf.lineto(a4_width - 50, a4_height - 760);
	pdf.moveto(50, a4_height - 760);
	pdf.lineto(a4_width - 50, a4_height - 760);
	pdf.moveto(50, a4_height - 120);
	pdf.lineto(a4_width - 50, a4_height - 120);
	pdf.moveto(50, a4_height - 140);
	pdf.lineto(a4_width - 50, a4_height - 140);
	pdf.moveto(50, a4_height - 160);
	pdf.lineto(a4_width - 50, a4_height - 160);
	pdf.moveto(50, a4_height - 180);
	pdf.lineto(a4_width - 50, a4_height - 180);
	pdf.moveto(80, a4_height - 120);
	pdf.lineto(80, a4_height - 140);
	pdf.moveto(180, a4_height - 120);
	pdf.lineto(180, a4_height - 140);
	pdf.moveto(235, a4_height - 120);
	pdf.lineto(235, a4_height - 140);
	pdf.moveto(360, a4_height - 120);
	pdf.lineto(360, a4_height - 140);
	pdf.moveto(415, a4_height - 120);
	pdf.lineto(415, a4_height - 140);
	pdf.moveto(80, a4_height - 140);
	pdf.lineto(80, a4_height - 160);
	pdf.moveto(160, a4_height - 140);
	pdf.lineto(160, a4_height - 160);
	pdf.moveto(215, a4_height - 140);
	pdf.lineto(215, a4_height - 160);
	pdf.moveto(325, a4_height - 140);
	pdf.lineto(325, a4_height - 160);
	pdf.moveto(365, a4_height - 140);
	pdf.lineto(365, a4_height - 160);
	pdf.moveto(105, a4_height - 160);
	pdf.lineto(105, a4_height - 180);
	pdf.moveto(a4_width/2, a4_height - 160);
	pdf.lineto(a4_width/2, a4_height - 180);
	pdf.moveto(a4_width/2+55, a4_height - 160);
	pdf.lineto(a4_width/2+55, a4_height - 180);
	pdf.stroke();

	pdf.setfont(font_song,12);
	pdf.set_text_pos(a4_width / 2 - 10, a4_height - 113);
	pdf.show(L"成绩单");
	wstring USER = (LPCWSTR)CStringW(m_user);
	pdf.show_xy(L"用户 " + USER, 53, a4_height - 135);
	pdf.set_text_pos(183, a4_height - 135);
	wstring ID = (LPCWSTR)CStringW(m_id);
	pdf.show(L"身份证号 "+ ID);
	pdf.set_text_pos(363, a4_height - 135);
	wstring Admission = (LPCWSTR)CStringW(m_admission);
	pdf.show(L"准考证号 " + Admission);
	wstring  QUESTION = (LPCWSTR)CStringW(m_question);
	pdf.show_xy(L"题号 " + QUESTION, 53, a4_height - 155);
	wstring USETIME = (LPCWSTR)CStringW(m_time);
	pdf.show_xy(L"考试用时 " + USETIME, 163, a4_height - 155);
	wstring ACCURACY = (LPCWSTR)CStringW(m_true);
	pdf.show_xy(L"准确率 " + ACCURACY, 328, a4_height - 155);
	wstring SPEED = (LPCWSTR)CStringW(m_speed);
	pdf.show_xy(L"打字速度 " + SPEED, 53, a4_height - 175);
	wstring SCORE = (LPCWSTR)CStringW(m_score);
	pdf.show_xy(L"考试成绩 " + SCORE + L"分", a4_width / 2 + 3, a4_height - 175);

	wstring TEXT = (LPCWSTR)CStringW(m_edit1);
	pdf.show_xy(L"录入信息：",80, a4_height - 210);
	for (int i = 0; i < (TEXT.length()/30+1); i++)
	{
		wstring temp=TEXT;
		pdf.show_xy(temp.substr(i*30,30), 110,a4_height-(230+20*i));
	}

	pdf.setcolor(L"stroke", L"rgb", 0, 0, 0, 0);
	pdf.moveto(50, a4_height - 780);
	pdf.lineto(a4_width - 50, a4_height - 780);
	pdf.moveto(50, a4_height - 782);
	pdf.lineto(a4_width - 50, a4_height - 782);
	pdf.stroke();

	pdf.set_text_pos(a4_width / 2 - 20, a4_height - 70);
	pdf.setcolor(L"fill", L"rgb", 0.147f, 0.147f, 0.147f, 0);
	pdf.setfont(font_song, 6);
	pdf.show_xy(L"宏图法院速录评测系统", a4_width / 2 - 20, a4_height - 788);

	pdf.end_page();
	pdf.end_document(L"");

	ShellExecute(NULL, _T("open"), _T("D://Score.pdf"), NULL, NULL, SW_SHOW);
	CDialogEx::OnOK();
}


BOOL CScore::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_user = ((CTestingSystemApp *)AfxGetApp())->m_user;
	m_id = ((CTestingSystemApp *)AfxGetApp())->m_id;
	m_filename = ((CTestingSystemApp *)AfxGetApp())->m_filename;
	GetPrivateProfileString(_T("Info"), _T("Admission"),NULL, m_admission.GetBuffer(30), 30,_T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename + _T(".ini"));
	GetPrivateProfileString(_T("Info"), _T("Question"), NULL,m_question.GetBuffer(30),30, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename + _T(".ini"));
	GetPrivateProfileString(_T("Info"), _T("True"), NULL,m_true.GetBuffer(30), 30,_T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename + _T(".ini"));
	GetPrivateProfileString(_T("Info"), _T("Speed"), NULL, m_speed.GetBuffer(30),30, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename + _T(".ini"));
	GetPrivateProfileString(_T("Info"), _T("UseTime"), NULL, m_time.GetBuffer(30), 30,_T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename + _T(".ini"));
	GetPrivateProfileString(_T("Info"), _T("Score"), NULL,m_score.GetBuffer(30),30, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename + _T(".ini"));
	GetPrivateProfileString(_T("Text"), _T("Text"), NULL,m_edit1.GetBuffer(1000),1000, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename + _T(".ini"));
	UpdateData(false);
	return TRUE;  
}

