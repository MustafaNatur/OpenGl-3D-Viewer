
// OpenGlDoc.h: интерфейс класса COpenGlDoc 
//
#include <vector>

#pragma once
struct point
{
		double x, y, z;
};

struct vertex
{
	point p1, p2, p3, v;
};

class COpenGlDoc : public CDocument
{
protected: // создать только из сериализации
	COpenGlDoc() noexcept;
	DECLARE_DYNCREATE(COpenGlDoc)

// Атрибуты
public:
	std::vector <vertex> m_Vert;
	float m_Scale = 1;
	point trans;

	point Rotation;

	


// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~COpenGlDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
