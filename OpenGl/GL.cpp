#include "pch.h"
#include "GL.h"


COpenGL::COpenGL(void)
{
}


COpenGL::~COpenGL(void)
{
    wglMakeCurrent(hDC, NULL);
    wglDeleteContext(hRC);
}


void COpenGL::Init(void)
{
    // �� ������ �������� ���� ��������� ��������� �������, ����� ��� "����������� �������� �������"
}


bool COpenGL::SetupPixelFormat(HDC hdc)
{
    hDC = hdc;

    PIXELFORMATDESCRIPTOR pfd =
    {
               sizeof(PIXELFORMATDESCRIPTOR), // ������ ��������� pfd
               1, // ����� ������
               PFD_DRAW_TO_WINDOW | // ��������� ��������� � ����
               PFD_SUPPORT_OPENGL | // ��������� OpenGL
               PFD_DOUBLEBUFFER, // ����� �������� ������
               PFD_TYPE_RGBA, // �������� ����� RGBA
               24, // 24-������ ������� �����
               0, 0, 0, 0, 0, 0, // ������������ ���� �����
               0, // ��� ���� ��������������
               0, // ������������ ���� ������
               0, // ��� ������ ����������
               0, 0, 0, 0, // ������������ ��� ����������
               32, // ����� ������� 32 ����   
               0, // ��� ���� ��������
               0, // ��� ���������������� ����
               PFD_MAIN_PLANE, // �������� ����
               0, // ���������������
               0, 0, 0 // ������������ ����, ��������� � ����� �����������
    };

    int nPixelFormat; // ������ ��������
    if (!(nPixelFormat = ChoosePixelFormat(hDC, &pfd)))
    {
        MessageBox(NULL, L"can not find proper mode", L"Error", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    SetPixelFormat(hDC, nPixelFormat, &pfd);
    hRC = wglCreateContext(hDC); // ������� ��������������� HGLRC, ��������� HDC, ������������ ��� ��������� GDI
    wglMakeCurrent(hDC, hRC); // ������� HGLRC ������������ OpenGL ��� ��������� �������� ����������� ���������

    return TRUE;
}


void COpenGL::Render(COpenGlDoc *pDoc)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float fColor1[4], fColor2[4];
    float par[4];
    long i, j, k, n;

    if (pDoc->m_Vert.size() == 0) return;

    // ���������� �������� ���������
    static float mat_shininess[] = { 128.0f };
    static float mat_specular[] = { 1.0f, 1.0f, 1.0f, 0.5f };
    static float mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 0.9f };
    static float mat_ambient[] = { 0.6f, 0.6f, 0.6f, 1.0f };

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);


    glScalef(pDoc->m_Scale, pDoc->m_Scale, pDoc->m_Scale);

    glTranslatef(pDoc->trans.x, pDoc->trans.y, pDoc->trans.z);

    glRotatef(pDoc->Rotation.x, 1, 0, 0);
    glRotatef(pDoc->Rotation.y, 0, 1, 0);
    glRotatef(pDoc->Rotation.z, 0, 0, 1);

    glEnable(GL_NORMALIZE);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT0 + 1);

    static float ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    static float diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    static float specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    static float position0[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    static float position1[] = { 0.0f, 0.0f, 0.5f, 0.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position0);

   

    glLightfv(GL_LIGHT0 + 1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0 + 1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0 + 1, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0 + 1, GL_POSITION, position1);
 
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    
    glClearDepth(1.0f);

    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

  
   glMatrixMode(GL_MODELVIEW);

   
    glBegin(GL_TRIANGLES);

    //	���������� ����� ������� � �������� �����������
    COLORREF color1 = RGB(100,0,0);
    COLORREF color2 = RGB(127, 127, 127);

    fColor1[0] = GetRValue(color1) / 255.f;
    fColor1[1] = GetGValue(color1) / 255.f;
    fColor1[2] = GetBValue(color1) / 255.f;
    fColor1[3] = 1.0f;

    fColor2[0] = GetRValue(color2) / 255.f;
    fColor2[1] = GetGValue(color2) / 255.f;
    fColor2[2] = GetBValue(color2) / 255.f;
    fColor2[3] = 1.0f;

    //		������������� �������� ��������� ������� �����������
    for (i = 0; i < 4; i++) par[i] = mat_diffuse[i] * fColor1[i];
    glMaterialfv(GL_FRONT, GL_DIFFUSE, par);

    for (i = 0; i < 4; i++) par[i] = mat_ambient[i] * fColor1[i];
    glMaterialfv(GL_FRONT, GL_AMBIENT, par);

    //		������������� �������� ��������� �������� �����������
    for (i = 0; i < 4; i++) par[i] = mat_diffuse[i] * fColor2[i];
    glMaterialfv(GL_BACK, GL_DIFFUSE, par);

    for (i = 0; i < 4; i++) par[i] = mat_ambient[i] * fColor2[i];
    glMaterialfv(GL_BACK, GL_AMBIENT, par);

    //		������ �������� �����������
    for (int i = 0; i < pDoc->m_Vert.size(); i++)
    {
        vertex v = pDoc->m_Vert.at(i);
        glNormal3f(v.v.x, v.v.y, v.v.z);
        glVertex3f(v.p1.x, v.p1.y, v.p1.z);

        glNormal3f(v.v.x, v.v.y, v.v.z);
        glVertex3f(v.p2.x, v.p2.y, v.p2.z);

        glNormal3f(v.v.x, v.v.y, v.v.z);
        glVertex3f(v.p3.x, v.p3.y, v.p3.z);
 
    }
     
    
   
    glEnd();

  
    SwapBuffers(hDC);
}


void COpenGL::Reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    
}