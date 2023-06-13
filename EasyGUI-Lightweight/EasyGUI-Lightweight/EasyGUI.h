#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include <thread>
#include <iomanip>
#include <sstream>
#pragma comment(lib, "MSIMG32.LIB")
using namespace std;
namespace EasyGUI
{
    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    LRESULT WINAPI EasyGUI_WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept//����
    {
        switch (msg)
        {
        case WM_ERASEBKGND:return TRUE; break;
        case WM_PAINT:return TRUE; break;//һֱ�ػ�
        }
        return DefWindowProcW(hwnd, msg, wp, lp);  //����ص������ķ���ֵ
    }
    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    void Message()
    {
        MSG msg = { 0 };
        if (GetMessageW(&msg, 0, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    class EasyGUI
    {
        //-----------�˵����
        LPCWSTR Global_EasyGUIFont = L"Small Fonts";//ȫ������
        int Global_EasyGUIFontSize = 14;//�����С
        vector<int> Global_EasyGUIColor = { 255,255,255 };//ȫ��������ɫ
        short Global_EasyGUIStyleCode = 1337;//ȫ�ֲ˵�������
        //------------------
        HWND EasyGUI_WindowHWND = NULL;//GUI Window HWND
        HDC EasyGUI_WindowHDC = NULL;//GUI Window HDC
        vector<int> PaintSize;//DoubleBufferPaint Size ������С
        HDC EasyGUI_DrawHDC = NULL;//EasyGUI DrawHDC GUIҪ���Ƶ�HDC
        //------------------
        BOOL Mouse_Block_ = false;
        BOOL Mouse_Slider_ = false;
        //---------------------------------------------------------------------
        void DrawRect(int X, int Y, int XX, int YY, vector<int>Color) noexcept//���ƾ��� (��������GUI)
        {
            //------------------------��ʼ��
            TRIVERTEX vert[2]; GRADIENT_RECT gRect;
            vert[0].Alpha = 0x0000; vert[1].Alpha = 0x0000;
            gRect.UpperLeft = 0; gRect.LowerRight = 1;
            //------------------------
            COLORREF ColorFF = RGB(Color[0], Color[1], Color[2]);
            vert[0].x = X;
            vert[0].y = Y;
            vert[1].x = X + XX;
            vert[1].y = Y + YY;
            vert[0].Red = GetRValue(ColorFF) << 8;
            vert[0].Green = GetGValue(ColorFF) << 8;
            vert[0].Blue = GetBValue(ColorFF) << 8;
            vert[1].Red = GetRValue(ColorFF) << 8;
            vert[1].Green = GetGValue(ColorFF) << 8;
            vert[1].Blue = GetBValue(ColorFF) << 8;
            GradientFill(EasyGUI_DrawHDC, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_V);
        }
        //---------------------------------------------------------------------
        void DrawGradientRect(int X, int Y, int XX, int YY, vector<int>Color_1, vector<int> Color_2, BOOL Draw_Style) noexcept//���ƽ������ (��������GUI)
        {//false = ����; true = ����
            //------------------------��ʼ��
            TRIVERTEX vert[2]; GRADIENT_RECT gRect;
            vert[0].Alpha = 0x0000; vert[1].Alpha = 0x0000;
            gRect.UpperLeft = 0; gRect.LowerRight = 1;
            //------------------------
            COLORREF Color1 = RGB(Color_1[0], Color_1[1], Color_1[2]);
            COLORREF Color2 = RGB(Color_2[0], Color_2[1], Color_2[2]);
            vert[0].x = X;
            vert[0].y = Y;
            vert[1].x = X + XX;
            vert[1].y = Y + YY;
            vert[0].Red = GetRValue(Color1) << 8;
            vert[0].Green = GetGValue(Color1) << 8;
            vert[0].Blue = GetBValue(Color1) << 8;
            vert[1].Red = GetRValue(Color2) << 8;
            vert[1].Green = GetGValue(Color2) << 8;
            vert[1].Blue = GetBValue(Color2) << 8;
            if (Draw_Style)GradientFill(EasyGUI_DrawHDC, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_V);
            else  GradientFill(EasyGUI_DrawHDC, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_H);
        }
        //---------------------------------------------------------------------
        void DrawString_None(int X, int Y, string String, vector<int> TextColor) noexcept//����Ĭ������ (��������GUI)
        {
            HDC StringHdc = EasyGUI_DrawHDC;
            HFONT h_Font = CreateFont(14, 0, 0, 0, 700, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, L"Small Fonts");
            HGDIOBJ FontPen = SelectObject(StringHdc, h_Font);
            SetTextColor(StringHdc, RGB(TextColor[0], TextColor[1], TextColor[2]));//������ɫ
            SetBkMode(StringHdc, TRANSPARENT);//����͸��
            TextOutA(StringHdc, X, Y + 1, String.c_str(), strlen(String.c_str()));
            DeleteObject(FontPen);
        }
        void DrawString(int X, int Y, string String, vector<int> TextColor) noexcept//�������� (��������GUI)
        {
            HDC StringHdc = EasyGUI_DrawHDC;
            HFONT h_Font = CreateFont(Global_EasyGUIFontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, Global_EasyGUIFont);
            if (Global_EasyGUIFont == L"Lucida Console")h_Font = CreateFont(Global_EasyGUIFontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, Global_EasyGUIFont);//ȥ�������
            HGDIOBJ FontPen = SelectObject(StringHdc, h_Font);
            SetTextColor(StringHdc, RGB(TextColor[0], TextColor[1], TextColor[2]));//������ɫ
            SetBkMode(StringHdc, TRANSPARENT);//����͸��
            TextOutA(StringHdc, X, Y, String.c_str(), strlen(String.c_str()));
            DeleteObject(FontPen);
        }
        void DrawString_Simple(int X, int Y, string String, vector<int> TextColor) noexcept//���Ƽ����� (��������GUI)
        {
            HDC StringHdc = EasyGUI_DrawHDC;
            HFONT h_Font = CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, L"Small Fonts");
            HGDIOBJ FontPen = SelectObject(StringHdc, h_Font);
            SetBkMode(StringHdc, TRANSPARENT);//����͸��
            SetTextColor(StringHdc, RGB(0, 0, 0));//������ɫ
            TextOutA(StringHdc, X + 1, Y + 1, String.c_str(), strlen(String.c_str()));
            TextOutA(StringHdc, X - 1, Y - 1, String.c_str(), strlen(String.c_str()));
            TextOutA(StringHdc, X + 1, Y - 1, String.c_str(), strlen(String.c_str()));
            TextOutA(StringHdc, X - 1, Y + 1, String.c_str(), strlen(String.c_str()));
            TextOutA(StringHdc, X + 1, Y, String.c_str(), strlen(String.c_str()));
            TextOutA(StringHdc, X - 1, Y, String.c_str(), strlen(String.c_str()));
            TextOutA(StringHdc, X, Y - 1, String.c_str(), strlen(String.c_str()));
            TextOutA(StringHdc, X, Y + 1, String.c_str(), strlen(String.c_str()));
            SetTextColor(StringHdc, RGB(TextColor[0], TextColor[1], TextColor[2]));//������ɫ
            TextOutA(StringHdc, X, Y, String.c_str(), strlen(String.c_str()));
            DeleteObject(FontPen);
        }
        //---------------------------------------------------------------------
    public:
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Global_Set_EasyGUI_Font(LPCWSTR Font) noexcept//����ȫ��GUI����
        {
            Global_EasyGUIFont = Font;
        }
        void Global_Set_EasyGUI_FontSize(int Size) noexcept//����ȫ��GUI�����С
        {
            Global_EasyGUIFontSize = Size;
        }
        void Global_Set_EasyGUI_Color(vector<int> GlobalColor) noexcept//����ȫ��������ɫ
        {
            Global_EasyGUIColor = GlobalColor;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL Window_Create(int SizeX, int SizeY, LPCWSTR m_WindowTitle, BOOL IfTop) noexcept//��������
        {
            static int �������� = WS_EX_LAYERED /* | WS_EX_TOOLWINDOW*/;
            if (IfTop)�������� = WS_EX_TOPMOST | WS_EX_LAYERED /* | WS_EX_TOOLWINDOW*/;
            WNDCLASS RenderWindowM;
            memset(&RenderWindowM, 0, sizeof(RenderWindowM));
            RenderWindowM.style = CS_HREDRAW | CS_VREDRAW;
            RenderWindowM.lpfnWndProc = EasyGUI_WndProc;//������Ϣ������,���߲���ϵͳ��������¼����������������
            RenderWindowM.cbClsExtra = 0;
            RenderWindowM.cbWndExtra = 0;
            RenderWindowM.hInstance = GetModuleHandle(NULL);//ʵ�����
            RenderWindowM.hIcon = LoadIcon(NULL, IDI_SHIELD);//ͼ��
            RenderWindowM.hCursor = LoadCursor(NULL, IDC_ARROW);//�����ʽ
            RenderWindowM.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);//��ˢ
            RenderWindowM.lpszMenuName = NULL;
            RenderWindowM.lpszClassName = m_WindowTitle;//����������ƣ�����ϵͳ�������������ӳ��
            RegisterClass(&RenderWindowM);//���������ע�ᣨ���ߣ�������ϵͳ
            HWND hWnd = CreateWindowEx(��������, m_WindowTitle, m_WindowTitle, WS_POPUP, GetSystemMetrics(SM_CXSCREEN) / 2 - SizeX / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - SizeY / 2, SizeX, SizeY, 0, 0, GetModuleHandle(NULL), 0);
            if (hWnd)//�������ɹ�
            {
                UpdateWindow(hWnd);
                ShowWindow(hWnd, SW_SHOW);
                SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 255, LWA_ALPHA);
                EasyGUI_WindowHWND = hWnd;
                EasyGUI_WindowHDC = GetWindowDC(hWnd);
                //---------------------------------------˫���忪ʼ����
                PaintSize = { SizeX + 100,SizeY + 100 };
                EasyGUI_DrawHDC = CreateCompatibleDC(EasyGUI_WindowHDC);
                SelectObject(EasyGUI_DrawHDC, (HBITMAP)CreateCompatibleBitmap(EasyGUI_WindowHDC, PaintSize[0], PaintSize[1]));
                //---------------------------------------------
                return true;
            }
            else return false;
        }
        void Draw_GUI() noexcept//˫����������� (�������շ���ͼƬ)
        {
            BitBlt(EasyGUI_WindowHDC, 0, 0, PaintSize[0], PaintSize[1], EasyGUI_DrawHDC, 0, 0, SRCCOPY);
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        HWND Window_HWND() noexcept//��ȡGUI����HWND
        {
            return EasyGUI_WindowHWND;
        }
        HDC Window_HDC() noexcept//��ȡGUI����HDC
        {
            return EasyGUI_DrawHDC;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Window_SetPOS(vector<int> m_Pos) noexcept//�޸�GUI��������
        {
            RECT Windowrect; GetWindowRect(EasyGUI_WindowHWND, &Windowrect);
            MoveWindow(EasyGUI_WindowHWND, m_Pos[0], m_Pos[1], Windowrect.right - Windowrect.left, Windowrect.bottom - Windowrect.top, TRUE);
        }
        vector<int> Window_GetPOS() noexcept//��ȡGUI��������
        {
            RECT Windowrect; GetWindowRect(EasyGUI_WindowHWND, &Windowrect);
            return { Windowrect.left ,Windowrect.top };
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Window_SetSize(vector<int> m_Size) noexcept//�޸�GUI���ڴ�С
        {
            RECT Windowrect; GetWindowRect(EasyGUI_WindowHWND, &Windowrect);
            MoveWindow(EasyGUI_WindowHWND, Windowrect.left, Windowrect.top, m_Size[0], m_Size[1], TRUE);
        }
        vector<int> Window_GetSize() noexcept//��ȡGUI���ڴ�С
        {
            RECT Windowrect; GetWindowRect(EasyGUI_WindowHWND, &Windowrect);
            return { Windowrect.right - Windowrect.left ,Windowrect.bottom - Windowrect.top };
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Window_Show() noexcept//�޸�GUI����Ϊ��ǰ��
        {
            SetForegroundWindow(EasyGUI_WindowHWND);
            ShowWindow(EasyGUI_WindowHWND, true);
        }
        void Window_Hide() noexcept//����GUI����
        {
            ShowWindow(EasyGUI_WindowHWND, false);
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Window_SetAlpha(short m_Alpha) noexcept//�޸�GUI�������尢����ͨ��
        {
            if (m_Alpha >= 255)m_Alpha = 255; else if (m_Alpha <= 0)m_Alpha = 0;
            SetLayeredWindowAttributes(EasyGUI_WindowHWND, RGB(0, 0, 0), m_Alpha, LWA_ALPHA);
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Window_SetTitle(LPCWSTR m_Title) noexcept//�޸�GUI���ڱ���
        {
            SetWindowTextW(EasyGUI_WindowHWND, m_Title);//�޸Ĵ��ڱ���
        }
        const char* Window_GetTitle() noexcept//��ȡGUI���ڱ���
        {
            CHAR pszMem[MAX_PATH] = { 0 }; GetWindowTextA(EasyGUI_WindowHWND, pszMem, GetWindowTextLength(EasyGUI_WindowHWND) + 1);
            return pszMem;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL Window_Move() noexcept//�ƶ�GUI���ڣ�����ѭ��(���÷ŵȴ���������Ϣѭ������) ���¼���
        {
            //--------------------------------��Ϣѭ��
            MSG msg = { 0 };
            if (GetMessageW(&msg, 0, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            //----------------------------------------
            static BOOL ��ֹ���� = false;
            static int OldX; static int OldY;//����ʱ����
            POINT MousePos; GetCursorPos(&MousePos);
            RECT Windowrect; GetWindowRect(EasyGUI_WindowHWND, &Windowrect);
            static BOOL ����������� = false;
            if (GetForegroundWindow() == EasyGUI_WindowHWND)//��ⴰ���Ƿ�����ǰ��
            {
                if (!Mouse_Block_ && GetAsyncKeyState(VK_LBUTTON) && !��ֹ����)//�����ָ�벻��Block��������ƶ�����
                {
                    if (�����������)
                    {
                        OldX = (MousePos.x - Windowrect.left);
                        OldY = (MousePos.y - Windowrect.top);
                        ����������� = false;
                    }
                    MoveWindow(EasyGUI_WindowHWND, MousePos.x - OldX, MousePos.y - OldY, Windowrect.right - Windowrect.left, Windowrect.bottom - Windowrect.top, TRUE);//�ƶ����ڵ��������
                    ��ֹ���� = true;
                }
                else if (��ֹ���� && GetAsyncKeyState(VK_LBUTTON))
                {
                    MoveWindow(EasyGUI_WindowHWND, MousePos.x - OldX, MousePos.y - OldY, Windowrect.right - Windowrect.left, Windowrect.bottom - Windowrect.top, TRUE);//�ƶ����ڵ��������
                    this_thread::sleep_for(chrono::nanoseconds(50));//����CPUռ�� ���뵥λ�ȴ�����
                    Mouse_Block_ = true;
                    return true;
                }
                else {
                    ��ֹ���� = false;
                    ����������� = true;
                    if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000))Sleep(20);//���̶ȼ���cpuռ�úͿ���
                    this_thread::sleep_for(chrono::nanoseconds(200));//����CPUռ�� ���뵥λ�ȴ�����
                    Mouse_Block_ = false;
                    return false;
                }
            }
            else Sleep(30); return false;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void GUI_BackGround(short m_BackGroundStyleCode) noexcept//����GUI���ڱ���
        {
            RECT Windowrect; GetWindowRect(EasyGUI_WindowHWND, &Windowrect);
            CHAR pszMem[MAX_PATH] = { 0 }; GetWindowTextA(EasyGUI_WindowHWND, pszMem, GetWindowTextLength(EasyGUI_WindowHWND) + 1);
            short XX = Windowrect.right - Windowrect.left; short YY = Windowrect.bottom - Windowrect.top;
            vector<int> �ʺ�����ɫ = { 0,255,255,255,0,255,255,255,0 };
            vector<int> ������ɫ = { 0,0,0,60,60,60,30,30,30,15,15,15,5,5,5,30,30,30 };
            if (m_BackGroundStyleCode == 0)//�����ɫ����
            {
                �ʺ�����ɫ = { 0,255,255,255,0,255,255,255,0 };
                ������ɫ = { 0,0,0,60,60,60,30,30,30,15,15,15,5,5,5,30,30,30 };
            }
            else if (m_BackGroundStyleCode == 1)//��ɫ
            {
                �ʺ�����ɫ = { 255,255,255,255,255,255,255,255,255 };
                ������ɫ = { 0,0,0,60,60,60,30,30,30,15,15,15,3,3,3,50,50,50 };
            }
            else if (m_BackGroundStyleCode == 2)//�ڰ�ɫ
            {
                �ʺ�����ɫ = { 150,150,150,255,255,255,150,150,150 };
                ������ɫ = { 0,0,0,60,60,60,30,30,30,15,15,15,3,3,3,30,30,30 };
            }
            else if (m_BackGroundStyleCode == 1337)//��Gamesense
            {
                �ʺ�����ɫ = { 100,255,255,255,100,255,255,255,100 };
                ������ɫ = { 0,0,0,60,60,60,30,30,30,15,15,15,5,5,5,30,30,30 };
            }
            else if (m_BackGroundStyleCode == 1367)//��Gamesense2
            {
                �ʺ�����ɫ = { 0,255,255,255,0,255,255,255,0 };
                ������ɫ = { 0,0,0,60,60,60,30,30,30,15,15,15,3,3,3,30,30,30 };
            }
            else if (m_BackGroundStyleCode == 1368)//��ɫ��ɫ������*****************
            {
                �ʺ�����ɫ = {
                    (int)floor(sin((float)GetTickCount64() / 1700 * 2 + 3) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / 1700 * 2 + 2 + 3) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / 1700 * 2 + 4 + 3) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / 1700 * 2 + 2) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / 1700 * 2 + 2 + 2) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / 1700 * 2 + 4 + 2) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / 1700 * 2 + 1) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / 1700 * 2 + 2 + 1) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / 1700 * 2 + 4 + 1) * 127 + 128),
                };
                ������ɫ = { 0,0,0,60,60,60,30,30,30,15,15,15,3,3,3, Global_EasyGUIColor[0] / 7,Global_EasyGUIColor[1] / 7 ,Global_EasyGUIColor[2] / 7 };
            }
            else if (m_BackGroundStyleCode == 1369)//�ڰױ�ɫ������*****************
            {
                �ʺ�����ɫ = {
                   55 + (int)floor(sin((float)GetTickCount64() / 500 + 3) * 100 + 100),
                   55 + (int)floor(sin((float)GetTickCount64() / 500 + 3) * 100 + 100),
                   55 + (int)floor(sin((float)GetTickCount64() / 500 + 3) * 100 + 100),
                   55 + (int)floor(sin((float)GetTickCount64() / 500 + 2) * 100 + 100),
                   55 + (int)floor(sin((float)GetTickCount64() / 500 + 2) * 100 + 100),
                   55 + (int)floor(sin((float)GetTickCount64() / 500 + 2) * 100 + 100),
                   55 + (int)floor(sin((float)GetTickCount64() / 500 + 1) * 100 + 100),
                   55 + (int)floor(sin((float)GetTickCount64() / 500 + 1) * 100 + 100),
                   55 + (int)floor(sin((float)GetTickCount64() / 500 + 1) * 100 + 100),
                };
                ������ɫ = { 0,0,0,60,60,60,30,30,30,15,15,15,15,15,15,5,5,5 };
            }
            else if (m_BackGroundStyleCode == -1)//����ɫ
            {
                �ʺ�����ɫ = { 255,150,255,200,170,255,150,200,255 };
                ������ɫ = { 0,0,0,60,60,60,30,30,30,15,15,15,3,3,3,30,25,35 };
            }
            else if (m_BackGroundStyleCode == -2)//�Ȼ�ɫ
            {
                �ʺ�����ɫ = { 230,80,80,230,120,60,255,200,30 };
                ������ɫ = { 0,0,0,60,60,60,30,30,30,15,15,15,3,3,3,40,25,25 };
            }
            else if (m_BackGroundStyleCode == -3)//����ɫ
            {
                �ʺ�����ɫ = { 100,200,100,100,200,150,100,180,230 };
                ������ɫ = { 0,0,0,60,60,60,30,30,30,15,15,15,3,3,3,0,30,30 };
            }
            else if (m_BackGroundStyleCode == 999)//ë��û��
            {
                �ʺ�����ɫ = { 16,16,16,16,16,16,16,16,16 };
                ������ɫ = { 0,0,0,60,60,60,30,30,30,15,15,15,15,15,15,15,15,15 };
            }
            DrawRect(0, 0, XX, YY, { ������ɫ[0], ������ɫ[1], ������ɫ[2] });
            DrawRect(1, 1, XX - 2, YY - 2, { ������ɫ[3], ������ɫ[4], ������ɫ[5] });
            DrawRect(2, 2, XX - 4, YY - 4, { ������ɫ[6], ������ɫ[7], ������ɫ[8] });
            DrawRect(5, 5, XX - 10, YY - 10, { ������ɫ[3], ������ɫ[4], ������ɫ[5] });
            DrawGradientRect(6, 6, XX - 12, YY - 12, { ������ɫ[12], ������ɫ[13], ������ɫ[14] }, { ������ɫ[15], ������ɫ[16], ������ɫ[17] }, true);//BackGround Gradient
            //-----------�ʺ���
            if (m_BackGroundStyleCode != 999)//ë��û��
            {
                DrawGradientRect(7, 7, (XX - 7 * 2) / 2, 2, { �ʺ�����ɫ[0] / 2, �ʺ�����ɫ[1] / 2, �ʺ�����ɫ[2] / 2 }, { �ʺ�����ɫ[3] / 2, �ʺ�����ɫ[4] / 2, �ʺ�����ɫ[5] / 2 }, false);
                DrawGradientRect(7 + (XX - 7 * 2) / 2, 7, (XX - 7 * 2) / 2, 2, { �ʺ�����ɫ[3] / 2, �ʺ�����ɫ[4] / 2, �ʺ�����ɫ[5] / 2 }, { �ʺ�����ɫ[6] / 2, �ʺ�����ɫ[7] / 2, �ʺ�����ɫ[8] / 2 }, false);
                DrawGradientRect(7, 7, (XX - 7 * 2) / 2, 1, { �ʺ�����ɫ[0], �ʺ�����ɫ[1], �ʺ�����ɫ[2] }, { �ʺ�����ɫ[3], �ʺ�����ɫ[4], �ʺ�����ɫ[5] }, false);
                DrawGradientRect(7 + (XX - 7 * 2) / 2, 7, (XX - 7 * 2) / 2, 1, { �ʺ�����ɫ[3], �ʺ�����ɫ[4], �ʺ�����ɫ[5] }, { �ʺ�����ɫ[6], �ʺ�����ɫ[7], �ʺ�����ɫ[8] }, false);
            }
            //-----------
            if (m_BackGroundStyleCode != 1337 && m_BackGroundStyleCode != 1367 && m_BackGroundStyleCode != 1368 && m_BackGroundStyleCode != 1369)//�ų��ض���������
            {
                DrawString(8 + 1, YY - Global_EasyGUIFontSize - 5, pszMem, { 0,0,0 });
                DrawString(8, YY - Global_EasyGUIFontSize - 5, pszMem, { Global_EasyGUIColor[0] / 2,Global_EasyGUIColor[1] / 2 ,Global_EasyGUIColor[2] / 2 });
            }
            Global_EasyGUIStyleCode = m_BackGroundStyleCode;//��д�˵����������(���ں�������������)
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        vector<int> GUI_Block(int X, int Y, int YY, string m_BlockText) noexcept//�������Ի��ư�ť������
        {
            POINT m_MousePos; GetCursorPos(&m_MousePos);//��ȡ�������
            RECT m_WindowPos; GetWindowRect(EasyGUI_WindowHWND, &m_WindowPos);//��ȡ��������
            DrawRect(X, Y, 400, YY, { 0,0,0 });//��ɫ��߿�
            DrawRect(X + 1, Y + 1, 400 - 2, YY - 2, { 60,60,60 });//��ɫ��߿�
            if (Global_EasyGUIStyleCode == 1368)DrawGradientRect(X + 2, Y + 2, 400 - 4, YY - 4, { 10,10,10 }, { Global_EasyGUIColor[0] / 10,Global_EasyGUIColor[1] / 10 ,Global_EasyGUIColor[2] / 10 }, true);//�˵����뽥�䱳��
            else DrawRect(X + 2, Y + 2, 400 - 4, YY - 4, { 15,15,15 });//Ĭ�ϱ���
            DrawString_None(X + 20 + 1, Y - 7 + 1, m_BlockText.c_str(), { 50,50,50 });
            DrawString_None(X + 20 + 1, Y - 7, m_BlockText.c_str(), { 200,200,200 });
            if ((m_MousePos.x - m_WindowPos.left >= X && m_MousePos.x - m_WindowPos.left <= X + 400 && m_MousePos.y - m_WindowPos.top >= Y && m_MousePos.y - m_WindowPos.top <= Y + YY) || !(m_MousePos.x >= m_WindowPos.left && m_MousePos.x <= m_WindowPos.right && m_MousePos.y >= m_WindowPos.top && m_MousePos.y <= m_WindowPos.bottom))
            {
                Mouse_Block_ = true;
            }
            return { X,Y };
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void GUI_Text(vector<int>BlockPos, short LineRow, string Text, ...) noexcept//����������
        {
            if (BlockPos[0] == 0 && BlockPos[1] == 0)return;//����block�򲻽��л���
            DrawString(BlockPos[0] + 22 + 30 + 1, BlockPos[1] - 3 + (30 * LineRow) + 1, Text, { 0,0,0 });
            DrawString(BlockPos[0] + 22 + 30 + 1, BlockPos[1] - 3 + (30 * LineRow), Text, { 200,200,200 });
        }
        //--------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL GUI_Checkbox(vector<int>BlockPos, short LineRow, string Text, BOOL& m_CheckboxValue) noexcept//���Ƶ����
        {
            if (BlockPos[0] == 0 && BlockPos[1] == 0)return 0;//����block�򲻽��л���
            POINT m_MousePos; GetCursorPos(&m_MousePos);//��ȡ�������
            RECT m_WindowPos; GetWindowRect(EasyGUI_WindowHWND, &m_WindowPos);//��ȡ��������
            BOOL DetectMousePos = m_MousePos.x - m_WindowPos.left >= BlockPos[0] + 30 && m_MousePos.x - m_WindowPos.left <= BlockPos[0] + 250 + 30 && m_MousePos.y - m_WindowPos.top >= BlockPos[1] + (30 * LineRow) - 2 && m_MousePos.y - m_WindowPos.top <= BlockPos[1] + 8 + (30 * LineRow) + 2;//���ڼ�����
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_)//����ǰ�˴���ΪGUI���ڽ��հ�ť�¼�
            {
                if (!m_CheckboxValue && GetAsyncKeyState(VK_LBUTTON) & 0x8000 && DetectMousePos)
                {
                    m_CheckboxValue = true;
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                }
                else if (m_CheckboxValue && GetAsyncKeyState(VK_LBUTTON) & 0x8000 && DetectMousePos)
                {
                    m_CheckboxValue = false;
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                }
            }
            DrawRect(BlockPos[0] - 1 + 30, BlockPos[1] - 1 + (30 * LineRow), 10, 10, { 0,0,0 });
            DrawString(BlockPos[0] + 22 + 30 + 1, BlockPos[1] - 3 + (30 * LineRow) + 1, Text, { 0,0,0 });
            DrawString(BlockPos[0] + 22 + 30, BlockPos[1] - 3 + (30 * LineRow), Text, { 200,200,200 });
            if (m_CheckboxValue)//����
            {
                DrawGradientRect(BlockPos[0] - 1 + 30 + 1, BlockPos[1] - 1 + (30 * LineRow) + 1, 8, 8, Global_EasyGUIColor, { Global_EasyGUIColor[0] / 5,Global_EasyGUIColor[1] / 5,Global_EasyGUIColor[2] / 5 }, true);
                return true;
            }
            else {
                if (DetectMousePos)DrawGradientRect(BlockPos[0] - 1 + 30 + 1, BlockPos[1] - 1 + (30 * LineRow) + 1, 8, 8, { 110,110,110 }, { 30,30,30 }, true);//�ƶ�����ť��ť����
                else DrawGradientRect(BlockPos[0] - 1 + 30 + 1, BlockPos[1] - 1 + (30 * LineRow) + 1, 8, 8, { 80,80,80 }, { 30,30,30 }, true);
                return false;
            }
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL GUI_Button(vector<int>BlockPos, short LineRow, string Text, short TextPos, BOOL& m_ButtonValue) noexcept//���Ƶ�����ť
        {
            if (BlockPos[0] == 0 && BlockPos[1] == 0)return 0;//����block�򲻽��л���
            POINT m_MousePos; GetCursorPos(&m_MousePos);//��ȡ�������
            RECT m_WindowPos; GetWindowRect(EasyGUI_WindowHWND, &m_WindowPos);//��ȡ��������
            BOOL DetectMousePos = m_MousePos.x - m_WindowPos.left >= BlockPos[0] + 55 && m_MousePos.x - m_WindowPos.left <= BlockPos[0] + 230 + 55 && m_MousePos.y - m_WindowPos.top >= BlockPos[1] + (30 * LineRow) - 8 && m_MousePos.y - m_WindowPos.top <= BlockPos[1] + 25 + (30 * LineRow) - 8;//���ڼ�����
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_)//����ǰ�˴���ΪGUI���ڽ��հ�ť�¼�
            {
                if (!m_ButtonValue && GetAsyncKeyState(VK_LBUTTON) & 0x8000 && DetectMousePos)
                {
                    m_ButtonValue = true;
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                }
                else m_ButtonValue = false;
            }
            DrawRect(BlockPos[0] - 2 + 55, BlockPos[1] - 2 + (30 * LineRow) - 8, 234, 29, { 0,0,0 });
            DrawRect(BlockPos[0] - 1 + 55, BlockPos[1] - 1 + (30 * LineRow) - 8, 232, 27, { 60,60,60 });
            if (DetectMousePos)DrawGradientRect(BlockPos[0] + 55, BlockPos[1] + (30 * LineRow) - 8, 230, 25, { 40,40,40 }, { 20,20,20 }, true);
            else DrawGradientRect(BlockPos[0] + 55, BlockPos[1] + (30 * LineRow) - 8, 230, 25, { 30,30,30 }, { 20,20,20 }, true);
            DrawString(BlockPos[0] + TextPos + 55 + 1, BlockPos[1] + 6 + (30 * LineRow) - 8 + 1, Text, { 0,0,0 });
            DrawString(BlockPos[0] + TextPos + 55, BlockPos[1] + 6 + (30 * LineRow) - 8, Text, { 200,200,200 });
            return m_ButtonValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        template<class ValueClass, class CreateClassName>
        ValueClass GUI_Slider(vector<int>BlockPos, short LineRow, string Text, ValueClass StartValue, ValueClass EndValue, ValueClass& m_SliderValue) noexcept//���ƻ���
        {
            if (BlockPos[0] == 0 && BlockPos[1] == 0)return 0;//����block�򲻽��л���
            ValueClass ClassValueDetect = 0.1;
            POINT m_MousePos; GetCursorPos(&m_MousePos);//��ȡ�������
            RECT m_WindowPos; GetWindowRect(EasyGUI_WindowHWND, &m_WindowPos);//��ȡ��������
            BOOL DetectMousePos = m_MousePos.x - m_WindowPos.left >= BlockPos[0] + 55 && m_MousePos.x - m_WindowPos.left <= BlockPos[0] + 230 + 55 && m_MousePos.y - m_WindowPos.top >= BlockPos[1] + (6 + 30 * LineRow) && m_MousePos.y - m_WindowPos.top <= BlockPos[1] + 5 + (6 + 30 * LineRow);//���ڼ�����
            static BOOL OutSide = false;//��ָֹ������ʱʧȥ������
            if (GetForegroundWindow() == EasyGUI_WindowHWND)//����ǰ�˴���ΪGUI���ڽ��հ�ť�¼�
            {
                if (DetectMousePos && GetAsyncKeyState(VK_LEFT) & 0x8000)//������ƶ��������Ϸ� ���������¼�
                {
                    if (ClassValueDetect == 0)m_SliderValue--;//����Ƿ��Ǹ���ֵ
                    else m_SliderValue -= 0.05;
                    keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
                }
                else if (DetectMousePos && GetAsyncKeyState(VK_RIGHT) & 0x8000) {
                    if (ClassValueDetect == 0)m_SliderValue++;//����Ƿ��Ǹ���ֵ
                    else m_SliderValue += 0.05;
                    keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
                }
                if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && DetectMousePos && !OutSide)OutSide = true;
                if (OutSide && GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                    m_SliderValue = ((m_MousePos.x - BlockPos[0] - 54 - m_WindowPos.left) * (EndValue - StartValue) / 230) + StartValue;
                    Mouse_Block_ = true; Mouse_Slider_ = true;
                }
                else if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
                {
                    OutSide = false; Mouse_Slider_ = false;
                }
            }
            int SliderPos = ((float)(m_SliderValue - StartValue) / (float)(EndValue - StartValue) * 230);
            if (SliderPos >= 230)SliderPos = 230; else if (SliderPos <= 0) SliderPos = 0;
            if (m_SliderValue <= StartValue)m_SliderValue = StartValue; else if (m_SliderValue >= EndValue)m_SliderValue = EndValue;
            stringstream ss; ss << fixed << setprecision(4) << m_SliderValue; ss >> m_SliderValue;//ֻ����4λС�������
            DrawRect(BlockPos[0] - 1 + 55, BlockPos[1] - 1 + (6 + 30 * LineRow), 230 + 2, 7, { 0,0,0 });//��ɫ��߿�
            if (DetectMousePos || OutSide)DrawGradientRect(BlockPos[0] + 55, BlockPos[1] + (6 + 30 * LineRow), 230, 5, { 40,40,40 }, { 60,60,60 }, true);//��������
            else DrawGradientRect(BlockPos[0] + 55, BlockPos[1] + (6 + 30 * LineRow), 230, 5, { 30,30,30 }, { 60,60,60 }, true);
            DrawGradientRect(BlockPos[0] + 55, BlockPos[1] + (6 + 30 * LineRow), SliderPos, 5, Global_EasyGUIColor, { Global_EasyGUIColor[0] / 5,Global_EasyGUIColor[1] / 5,Global_EasyGUIColor[2] / 5 }, true);//����
            DrawString(BlockPos[0] + 55 + 1, BlockPos[1] - 16 + (6 + 30 * LineRow) + 1, Text, { 0,0,0 });
            DrawString(BlockPos[0] + 55, BlockPos[1] - 16 + (6 + 30 * LineRow), Text, { 200,200,200 });
            DrawString_Simple(BlockPos[0] + 230 + 10 + 55, BlockPos[1] - 4 + (6 + 30 * LineRow), ss.str(), { 150,150,150 });//����ֵ����
            return m_SliderValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        template<class CreateClassName>
        int GUI_KeySelect(vector<int>BlockPos, short LineRow, int& m_KeySelectValue) noexcept//���ư���ѡȡ��ť
        {
            if (BlockPos[0] == 0 && BlockPos[1] == 0)return 0;//����block�򲻽��л���
            if (m_KeySelectValue == 0xCCCCCCCC)m_KeySelectValue = 0;//�޸�����
            POINT m_MousePos; GetCursorPos(&m_MousePos);//��ȡ�������
            RECT m_WindowPos; GetWindowRect(EasyGUI_WindowHWND, &m_WindowPos);//��ȡ��������
            BOOL DetectMousePos = m_MousePos.x - m_WindowPos.left >= BlockPos[0] + 350 && m_MousePos.x - m_WindowPos.left <= BlockPos[0] + 40 + 350 && m_MousePos.y - m_WindowPos.top >= BlockPos[1] + 26 + (30 * (LineRow - 1)) && m_MousePos.y - m_WindowPos.top <= BlockPos[1] + 12 + 26 + (30 * (LineRow - 1));//���ڼ�����
            static BOOL BoxMea = false;//ֻ����һ�γ�ʼ�����趨����
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_)//����ǰ�˴���ΪGUI���ڽ��հ�ť�¼�
            {
                if (!BoxMea && GetAsyncKeyState(VK_LBUTTON) & 0x8000 && DetectMousePos)
                {
                    BoxMea = true;
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                }
                else if (BoxMea)
                {
                    for (int i = 0x01; i < 0xFE; ++i)//vk�������
                    {
                        if (GetAsyncKeyState(i) & 0x8000)//�����������
                        {
                            m_KeySelectValue = i;
                            BoxMea = false;
                        }
                    }
                }
            }
            char KeyText[0x5F30]; sprintf_s(KeyText, 0x5F30, "[0x%X]", m_KeySelectValue);
            if (!BoxMea)
            {
                if (DetectMousePos)DrawString_Simple(BlockPos[0] + 355, BlockPos[1] + 27 + (30 * (LineRow - 1)), KeyText, { 130,130,130 });
                else DrawString_Simple(BlockPos[0] + 355, BlockPos[1] + 27 + (30 * (LineRow - 1)), KeyText, { 100,100,100 });
                return m_KeySelectValue;
            }
            else {
                DrawString_Simple(BlockPos[0] + 355, BlockPos[1] + 27 + (30 * (LineRow - 1)), "[-]", { 150,100,100 });
                return 0;
            }
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL GUI_Tips(vector<int>BlockPos, short LineRow, string m_TipsString) noexcept//���ָ����ʾ(ֻ֧�ֵ����ַ�)   (����д�����Ϊ�˲������ǻ���)
        {
            if (BlockPos[0] == 0 && BlockPos[1] == 0)return 0;//����block�򲻽��л���
            POINT m_MousePos; GetCursorPos(&m_MousePos);//��ȡ�������
            RECT m_WindowPos; GetWindowRect(EasyGUI_WindowHWND, &m_WindowPos);//��ȡ��������
            BOOL DetectMousePos = m_MousePos.x - m_WindowPos.left >= BlockPos[0] + 7 && m_MousePos.x - m_WindowPos.left <= BlockPos[0] + 13 + 7 && m_MousePos.y - m_WindowPos.top >= BlockPos[1] + 26 + (30 * (LineRow - 1)) && m_MousePos.y - m_WindowPos.top <= BlockPos[1] + 12 + 26 + (30 * (LineRow - 1));//���ڼ�����
            DrawString_Simple(BlockPos[0] + 7, BlockPos[1] + 27 + (30 * (LineRow - 1)), "[?]", { 100,100,100 });//GUI����
            if (GetForegroundWindow() == EasyGUI_WindowHWND && DetectMousePos)//������ƶ����ʺ� ��GUI����Ϊ���
            {
                DrawRect(m_MousePos.x - m_WindowPos.left + 15, m_MousePos.y - m_WindowPos.top + 15, strlen(m_TipsString.c_str()) * 6 + 5, 20, { 0,0,0 });
                DrawRect(m_MousePos.x - m_WindowPos.left + 15 + 1, m_MousePos.y - m_WindowPos.top + 15 + 1, strlen(m_TipsString.c_str()) * 6 + 5 - 2, 20 - 2, { 60,60,60 });
                DrawRect(m_MousePos.x - m_WindowPos.left + 15 + 2, m_MousePos.y - m_WindowPos.top + 15 + 2, strlen(m_TipsString.c_str()) * 6 + 5 - 4, 20 - 4, { 15,15,15 });
                DrawString_Simple(m_MousePos.x - m_WindowPos.left + 15 + 4, m_MousePos.y - m_WindowPos.top + 15 + 4, m_TipsString, { 255,255,255 });
                return true;
            }
            else return false;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
    private:
    };
}