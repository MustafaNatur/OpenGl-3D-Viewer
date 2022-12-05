#pragma once
#include "OpenGlDoc.h"
class COpenGL
{
private:
	HDC hDC; // ���������� ����� ����������, ������������ � ��������� GDI
	HGLRC hRC; // ���������� ����� ����������, ������������ ��� ���������� OpenGL

public:
	COpenGL(void);
	virtual ~COpenGL(void);

	bool SetupPixelFormat(HDC hdc); // ������������� ������ �������� � ������, ���������� ��� OpenGL
	void Init(void); // �������������� ��������� �������� �� ����� ����������
	void Render(COpenGlDoc* pDoc); // ��� ���������

	void Reshape(int width, int height); // ��������, ����������� � ����� ��� ��������� ������� ����
};