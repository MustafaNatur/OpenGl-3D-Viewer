
// OpenGl.h: основной файл заголовка для приложения OpenGl
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// COpenGlApp:
// Сведения о реализации этого класса: OpenGl.cpp
//

class COpenGlApp : public CWinApp
{
public:
	COpenGlApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COpenGlApp theApp;
