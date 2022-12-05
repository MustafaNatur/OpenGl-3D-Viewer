
// OpenGlDoc.cpp: реализация класса COpenGlDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "OpenGl.h"
#include <string>
#include <sstream>
#include <fstream>
#endif

#include "OpenGlDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// COpenGlDoc

IMPLEMENT_DYNCREATE(COpenGlDoc, CDocument)

BEGIN_MESSAGE_MAP(COpenGlDoc, CDocument)
END_MESSAGE_MAP()


// Создание или уничтожение COpenGlDoc

COpenGlDoc::COpenGlDoc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора

}

COpenGlDoc::~COpenGlDoc()
{
}

BOOL COpenGlDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)
	m_Scale = 0.3f;
	trans.x = trans.z = 0.0f;
	trans.y = 0;
	
	Rotation.x = 45;
	Rotation.y = Rotation.z = 0;

	return TRUE;
}




// Сериализация COpenGlDoc

void COpenGlDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
		m_Vert.clear();
	
		
		std::ifstream file(ar.m_strFileName);
		int n = 0;
		vertex vr;
		while (!file.eof())
		{			
			char buf[100];
			file.getline(buf,100);
			
			std::stringstream s(buf);
			
			std::string word;

			s >> word;

			if (word.find("endfacet", 0) != std::string::npos)
			{
				continue;
			}

			if (word.find("facet", 0) != std::string::npos)
			{
				std::string val;
				s >> val;
				s >> val;
				sscanf_s(val.c_str(), "%lf",&vr.v.x);
				s >> val;
				sscanf_s(val.c_str(), "%lf",&vr.v.y);
				s >> val;
				sscanf_s(val.c_str(), "%lf",&vr.v.z);
			}
			if (word.find("outer", 0) != std::string::npos)
			{
				n = 0;
			}
			if (word.find("vertex", 0) != std::string::npos)
			{
				n++;
				std::string val;
				if (n == 1)
				{
					s >> val;
					sscanf_s(val.c_str(), "%lf", &vr.p1.x);
					s >> val;
					sscanf_s(val.c_str(), "%lf", &vr.p1.y);
					s >> val;
					sscanf_s(val.c_str(), "%lf", &vr.p1.z);
				}
				if (n == 2)
				{
					s >> val;
					sscanf_s(val.c_str(), "%lf", &vr.p2.x);
					s >> val;
					sscanf_s(val.c_str(), "%lf", &vr.p2.y);
					s >> val;
					sscanf_s(val.c_str(), "%lf", &vr.p2.z);
				}
				if (n == 3)
				{
					s >> val;
					sscanf_s(val.c_str(), "%lf", &vr.p3.x);
					s >> val;
					sscanf_s(val.c_str(), "%lf", &vr.p3.y);
					s >> val;
					sscanf_s(val.c_str(), "%lf", &vr.p3.z);
				}
			}
			if (word.find("endloop", 0) != std::string::npos)
			{
				n = 0;
				m_Vert.push_back(vr);
			}

		}
			file.close();
	
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void COpenGlDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void COpenGlDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void COpenGlDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика COpenGlDoc

#ifdef _DEBUG
void COpenGlDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COpenGlDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды COpenGlDoc
