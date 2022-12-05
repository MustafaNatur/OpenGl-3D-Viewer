#pragma once
#include "OpenGlDoc.h"
class COpenGL
{
private:
	HDC hDC; // Дескриптор среды устройства, используемый в отрисовке GDI
	HGLRC hRC; // Дескриптор среды рендеринга, используемой при рендеринге OpenGL

public:
	COpenGL(void);
	virtual ~COpenGL(void);

	bool SetupPixelFormat(HDC hdc); // Устанавливаем формат пикселей в формат, подходящий для OpenGL
	void Init(void); // Инициализируем настройку свойства во время рендеринга
	void Render(COpenGlDoc* pDoc); // Код отрисовки

	void Reshape(int width, int height); // Операция, выполняемая с окном при изменении размера окна
};