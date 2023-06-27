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
    LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept//辅助
    {
        switch (msg)
        {
        case WM_ERASEBKGND:return TRUE; break;
        case WM_PAINT:return TRUE; break;//一直重绘
        }
        return DefWindowProc(hwnd, msg, wp, lp);  //定义回调函数的返回值
    }
    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    class EasyGUI
    {
        //-----------菜单风格
        LPCWSTR Global_EasyGUIFont = L"Verdana";//全局字体
        int Global_EasyGUIFontSize = 13;//字体大小
        vector<int> Global_EasyGUIColor = { 255,255,255 };//全局主题颜色
        short Global_EasyGUIStyleCode = 1337;//全局菜单风格代码
        //------------------
        HWND EasyGUI_WindowHWND = NULL;//GUI Window HWND
        HDC EasyGUI_WindowHDC = NULL;//GUI Window HDC
        vector<int> PaintSize;//DoubleBufferPaint Size 画布大小
        HDC EasyGUI_DrawHDC = NULL;//EasyGUI DrawHDC GUI要绘制的HDC
        POINT EasyGUI_MousePos;//EasyGUI鼠标坐标
        RECT EasyGUI_WindowPos;//EasyGUI窗口坐标
        //------------------
        BOOL Mouse_Block_ = false;
        BOOL Mouse_Slider_ = false;
        //---------------------------------------------------------------------
        void In_DrawRect(int X, int Y, int XX, int YY, vector<int>Color) noexcept//绘制矩形 (方便制作GUI)
        {
            //------------------------初始化
            TRIVERTEX vert[2]; GRADIENT_RECT gRect;
            vert[0].Alpha = 0x0000; vert[1].Alpha = 0x0000;
            gRect.UpperLeft = 0; gRect.LowerRight = 1;
            //------------------------
            const COLORREF Color_ = RGB(Color[0], Color[1], Color[2]);
            vert[0].x = X;
            vert[0].y = Y;
            vert[1].x = X + XX;
            vert[1].y = Y + YY;
            vert[0].Red = GetRValue(Color_) << 8;
            vert[0].Green = GetGValue(Color_) << 8;
            vert[0].Blue = GetBValue(Color_) << 8;
            vert[1].Red = GetRValue(Color_) << 8;
            vert[1].Green = GetGValue(Color_) << 8;
            vert[1].Blue = GetBValue(Color_) << 8;
            GradientFill(EasyGUI_DrawHDC, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_V);
        }
        //---------------------------------------------------------------------
        void In_DrawGradientRect(int X, int Y, int XX, int YY, vector<int>Color_1, vector<int> Color_2, BOOL Draw_Style = false) noexcept//绘制渐变矩形 (方便制作GUI)
        {//false = 横向; true = 竖向
            //------------------------初始化
            TRIVERTEX vert[2]; GRADIENT_RECT gRect;
            vert[0].Alpha = 0x0000; vert[1].Alpha = 0x0000;
            gRect.UpperLeft = 0; gRect.LowerRight = 1;
            //------------------------
            const COLORREF Color1 = RGB(Color_1[0], Color_1[1], Color_1[2]);
            const COLORREF Color2 = RGB(Color_2[0], Color_2[1], Color_2[2]);
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
        void In_DrawString(int X, int Y, string String, vector<int> TextColor, LPCWSTR Fount_Name, short Fount_Size, short Font_Width = FW_NORMAL, BOOL AntiAlias = true) noexcept//绘制文字 (方便制作GUI)
        {
            const HDC StringHdc = EasyGUI_DrawHDC;
            HGDIOBJ FontPen;
            if (AntiAlias)FontPen = SelectObject(StringHdc, CreateFont(Fount_Size, 0, 0, 0, Font_Width, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, Fount_Name));
            else FontPen = SelectObject(StringHdc, CreateFont(Fount_Size, 0, 0, 0, Font_Width, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, Fount_Name));
            SetTextColor(StringHdc, RGB(TextColor[0], TextColor[1], TextColor[2]));//文字颜色
            SetBkMode(StringHdc, TRANSPARENT);//背景透明
            TextOutA(StringHdc, X, Y, String.c_str(), strlen(String.c_str()));
            DeleteObject(FontPen);
        }
        void In_DrawString_Simple(int X, int Y, string String, vector<int> TextColor) noexcept//绘制简单文字 (方便制作GUI)
        {
            const HDC StringHdc = EasyGUI_DrawHDC;
            HGDIOBJ FontPen = SelectObject(StringHdc, CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, L"Small Fonts"));
            SetBkMode(StringHdc, TRANSPARENT);//背景透明
            SetTextColor(StringHdc, RGB(0, 0, 0));//文字颜色
            TextOutA(StringHdc, X + 1, Y + 1, String.c_str(), strlen(String.c_str()));
            TextOutA(StringHdc, X - 1, Y - 1, String.c_str(), strlen(String.c_str()));
            TextOutA(StringHdc, X + 1, Y - 1, String.c_str(), strlen(String.c_str()));
            TextOutA(StringHdc, X - 1, Y + 1, String.c_str(), strlen(String.c_str()));
            TextOutA(StringHdc, X + 1, Y, String.c_str(), strlen(String.c_str()));
            TextOutA(StringHdc, X - 1, Y, String.c_str(), strlen(String.c_str()));
            TextOutA(StringHdc, X, Y - 1, String.c_str(), strlen(String.c_str()));
            TextOutA(StringHdc, X, Y + 1, String.c_str(), strlen(String.c_str()));
            SetTextColor(StringHdc, RGB(TextColor[0], TextColor[1], TextColor[2]));//文字颜色
            TextOutA(StringHdc, X, Y, String.c_str(), strlen(String.c_str()));
            DeleteObject(FontPen);
        }
        //---------------------------------------------------------------------
        string In_VKCode_to_String(int VK_code) noexcept//通过VK键码获取按键名称
        {
            switch (VK_code)
            {
            case 0x01: return "[M1]";//鼠标左键
            case 0x02: return "[M2]";//鼠标右键
            case 0x03: return "[CAN]";//鼠标中断处理
            case 0x04: return "[M3]";//鼠标中键
            case 0x05: return "[M4]";//鼠标侧键下
            case 0x06: return "[M5]";//鼠标侧键上
            case 0x07: return "[NONE]";
            case 0x08: return "[BACK]";
            case 0x09: return "[TAB]";
            case 0x0C: return "[CLE]";
            case 0x0D: return "[ENT]";
            case 0x10: return "[SHF]";
            case 0x11: return "[CLR]";
            case 0x12: return "[ALT]";
            case 0x13: return "[PAU]";
            case 0x14: return "[CAP]";
            case 0x15: return "[KAN]";
            case 0x16: return "[KAN]";
            case 0x17: return "[JUN]";
            case 0x18: return "[FIN]";
            case 0x19: return "[HAN]";
            case 0x1B: return "[ESC]";
            case 0x1C: return "[CON]";
            case 0x1D: return "[NON]";
            case 0x1E: return "[ACC]";
            case 0x1F: return "[MOD]";
            case 0x20: return "[SPA]";
            case 0x21: return "[PRI]";
            case 0x22: return "[NEXT]";
            case 0x23: return "[END]";
            case 0x24: return "[HOME]";
            case 0x25: return "[LEFT]";
            case 0x26: return "[UP]";
            case 0x27: return "[RIGT]";
            case 0x28: return "[DOWN]";
            case 0x29: return "[SEL]";
            case 0x2A: return "[PRI]";
            case 0x2B: return "[EXE]";
            case 0x2C: return "[SNAP]";
            case 0x2D: return "[INS]";
            case 0x2E: return "[DEL]";
            case 0x2F: return "[HELP]";
            case 0x30: return "[0]";
            case 0x31: return "[1]";
            case 0x32: return "[2]";
            case 0x33: return "[3]";
            case 0x34: return "[4]";
            case 0x35: return "[5]";
            case 0x36: return "[6]";
            case 0x37: return "[7]";
            case 0x38: return "[8]";
            case 0x39: return "[9]";
            case 0x41: return "[A]";
            case 0x42: return "[B]";
            case 0x43: return "[C]";
            case 0x44: return "[D]";
            case 0x45: return "[E]";
            case 0x46: return "[F]";
            case 0x47: return "[G]";
            case 0x48: return "[H]";
            case 0x49: return "[I]";
            case 0x4A: return "[J]";
            case 0x4B: return "[K]";
            case 0x4C: return "[L]";
            case 0x4D: return "[M]";
            case 0x4E: return "[N]";
            case 0x4F: return "[O]";
            case 0x50: return "[P]";
            case 0x51: return "[Q]";
            case 0x52: return "[R]";
            case 0x53: return "[S]";
            case 0x54: return "[T]";
            case 0x55: return "[U]";
            case 0x56: return "[V]";
            case 0x57: return "[W]";
            case 0x58: return "[X]";
            case 0x59: return "[Y]";
            case 0x5A: return "[Z]";
            case 0x5B: return "[WIN]";//L
            case 0x5C: return "[WIN]";//R
            case 0x5D: return "[APP]";
            case 0x5F: return "[SLP]";
            case 0x60: return "[0]";
            case 0x61: return "[1]";
            case 0x62: return "[2]";
            case 0x63: return "[3]";
            case 0x64: return "[4]";
            case 0x65: return "[5]";
            case 0x66: return "[6]";
            case 0x67: return "[7]";
            case 0x68: return "[8]";
            case 0x69: return "[9]";
            case 0x6A: return "[*]";
            case 0x6B: return "[+]";
            case 0x6C: return "[SEP]";
            case 0x6D: return "[-]";
            case 0x6E: return "[.]";
            case 0x6F: return "[/]";
            case 0x70: return "[F1]";
            case 0x71: return "[F2]";
            case 0x72: return "[F3]";
            case 0x73: return "[F4]";
            case 0x74: return "[F5]";
            case 0x75: return "[F6]";
            case 0x76: return "[F7]";
            case 0x77: return "[F8]";
            case 0x78: return "[F9]";
            case 0x79: return "[F10]";
            case 0x7A: return "[F11]";
            case 0x7B: return "[F12]";
            case 0x7C: return "[F13]";
            case 0x7D: return "[F14]";
            case 0x7E: return "[F15]";
            case 0x7F: return "[F16]";
            case 0x80: return "[F17]";
            case 0x81: return "[F18]";
            case 0x82: return "[F19]";
            case 0x83: return "[F20]";
            case 0x84: return "[F21]";
            case 0x85: return "[F22]";
            case 0x86: return "[F23]";
            case 0x87: return "[F24]";
            case 0x90: return "[NUM]";
            case 0x91: return "[SCR]";
            case 0xA0: return "[SHF]";//L
            case 0xA1: return "[SHF]";//R
            case 0xA2: return "[CLR]";//L
            case 0xA3: return "[CLR]";//R
            case 0xA4: return "[ALT]";//L
            case 0xA5: return "[ALT]";//R
            case 0xC0: return "[~]";
            case 0xBC: return "[,]";
            case 0xBE: return "[.]";
            case 0xBF: return "[/]";
            case 0xBA: return "[;]";
            case 0xDE: return "[']";
            case 0xDB: return "[[]";
            case 0xDD: return "[]]";
            case 0xDC: return "[\]";
            default: return "[" + to_string(VK_code) + "]";//如果什么都不是直接返回编码
            }
        }
        //---------------------------------------------------------------------
        BOOL In_MouseEventJudgment(int X, int Y, int XX, int YY) noexcept//检测鼠标坐标是否在窗口矩形坐标内
        {
            if (!(EasyGUI_MousePos.x >= EasyGUI_WindowPos.left && EasyGUI_MousePos.x <= EasyGUI_WindowPos.right && EasyGUI_MousePos.y >= EasyGUI_WindowPos.top && EasyGUI_MousePos.y <= EasyGUI_WindowPos.bottom))return false;//当指针不在窗口内
            if (EasyGUI_MousePos.x - EasyGUI_WindowPos.left >= X && EasyGUI_MousePos.x - EasyGUI_WindowPos.left <= X + XX && EasyGUI_MousePos.y - EasyGUI_WindowPos.top >= Y && EasyGUI_MousePos.y - EasyGUI_WindowPos.top <= Y + YY)return true;
            else return false;
        }
        //---------------------------------------------------------------------
    public:
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Global_Set_EasyGUI_Font(LPCWSTR Font) noexcept//设置全局GUI字体
        {
            Global_EasyGUIFont = Font;
        }
        void Global_Set_EasyGUI_FontSize(int Size) noexcept//设置全局GUI字体大小
        {
            Global_EasyGUIFontSize = Size;
        }
        void Global_Set_EasyGUI_Color(vector<int> GlobalColor) noexcept//设置全局主题颜色
        {
            Global_EasyGUIColor = GlobalColor;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL Window_Create(int SizeX, int SizeY, LPCWSTR m_WindowTitle, BOOL IfTop = false) noexcept//创建窗口
        {
            static int 窗口类型 = WS_EX_LAYERED;
            if (IfTop)窗口类型 = WS_EX_TOPMOST | WS_EX_LAYERED;//WS_EX_TOOLWINDOW
            WNDCLASS RenderWindowM;
            memset(&RenderWindowM, 0, sizeof(RenderWindowM));
            RenderWindowM.style = CS_HREDRAW | CS_VREDRAW;
            RenderWindowM.lpfnWndProc = WndProc;//关联消息处理函数,告诉操作系统，如果有事件发生调用这个函数
            RenderWindowM.cbClsExtra = 0;
            RenderWindowM.cbWndExtra = 0;
            RenderWindowM.hInstance = GetModuleHandle(NULL);//实例句柄
            RenderWindowM.hIcon = LoadIcon(NULL, IDI_SHIELD);//图标
            RenderWindowM.hCursor = LoadCursor(NULL, IDC_ARROW);//光标样式
            RenderWindowM.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);//画刷
            RenderWindowM.lpszMenuName = NULL;
            RenderWindowM.lpszClassName = m_WindowTitle;//窗口类的名称，操作系统根据类的名称做映射
            RegisterClass(&RenderWindowM);//将这个窗体注册（告诉）到操作系统
            const HWND hWnd = CreateWindowEx(窗口类型, m_WindowTitle, m_WindowTitle, WS_POPUP, GetSystemMetrics(SM_CXSCREEN) / 2 - SizeX / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - SizeY / 2, SizeX, SizeY, 0, 0, GetModuleHandle(NULL), 0);
            if (hWnd)//当创建成功
            {
                UpdateWindow(hWnd);
                ShowWindow(hWnd, SW_SHOW);
                SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 255, LWA_ALPHA);
                EasyGUI_WindowHWND = hWnd;
                EasyGUI_WindowHDC = GetWindowDC(hWnd);
                //---------------------------------------双缓冲开始绘制
                PaintSize = { SizeX + 100,SizeY + 100 };//设定坐标上加上100缓冲区
                EasyGUI_DrawHDC = CreateCompatibleDC(EasyGUI_WindowHDC);
                SelectObject(EasyGUI_DrawHDC, (HBITMAP)CreateCompatibleBitmap(EasyGUI_WindowHDC, PaintSize[0], PaintSize[1]));
                //---------------------------------------------
                return true;
            }
            else return false;
        }
        void Draw_GUI() noexcept//双缓冲结束绘制 (绘制最终返回图片)
        {
            BitBlt(EasyGUI_WindowHDC, 0, 0, PaintSize[0], PaintSize[1], EasyGUI_DrawHDC, 0, 0, SRCCOPY);
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        HWND Window_HWND() noexcept//获取GUI窗口HWND
        {
            return EasyGUI_WindowHWND;
        }
        HDC Window_HDC() noexcept//获取GUI窗口HDC
        {
            return EasyGUI_DrawHDC;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Window_SetPos(vector<int> m_Pos) noexcept//修改GUI窗口坐标
        {
            RECT m_Windowrect; GetWindowRect(EasyGUI_WindowHWND, &m_Windowrect);
            MoveWindow(EasyGUI_WindowHWND, m_Pos[0], m_Pos[1], m_Windowrect.right - m_Windowrect.left, m_Windowrect.bottom - m_Windowrect.top, TRUE);
        }
        vector<int> Window_GetPos() noexcept//获取GUI窗口坐标
        {
            RECT m_Windowrect; GetWindowRect(EasyGUI_WindowHWND, &m_Windowrect);
            return { m_Windowrect.left ,m_Windowrect.top };
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Window_SetSize(vector<int> m_Size) noexcept//修改GUI窗口大小
        {
            RECT m_Windowrect; GetWindowRect(EasyGUI_WindowHWND, &m_Windowrect);
            MoveWindow(EasyGUI_WindowHWND, m_Windowrect.left, m_Windowrect.top, m_Size[0], m_Size[1], TRUE);
        }
        vector<int> Window_GetSize() noexcept//获取GUI窗口大小
        {
            RECT m_Windowrect; GetWindowRect(EasyGUI_WindowHWND, &m_Windowrect);
            return { m_Windowrect.right - m_Windowrect.left ,m_Windowrect.bottom - m_Windowrect.top };
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Window_Show() noexcept//修改GUI窗口为最前端
        {
            SetForegroundWindow(EasyGUI_WindowHWND);
            ShowWindow(EasyGUI_WindowHWND, true);
        }
        void Window_Hide() noexcept//隐藏GUI窗口
        {
            ShowWindow(EasyGUI_WindowHWND, false);
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Window_SetAlpha(short m_Alpha) noexcept//修改GUI窗口整体阿尔法通道
        {
            if (m_Alpha >= 255)m_Alpha = 255; else if (m_Alpha <= 0)m_Alpha = 0;
            SetLayeredWindowAttributes(EasyGUI_WindowHWND, RGB(0, 0, 0), m_Alpha, LWA_ALPHA);
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Window_SetTitle(LPCWSTR m_Title) noexcept//修改GUI窗口标题
        {
            SetWindowTextW(EasyGUI_WindowHWND, m_Title);//修改窗口标题
        }
        char* Window_GetTitle() noexcept//获取GUI窗口标题
        {
            CHAR pszMem[MAX_PATH] = { 0 }; GetWindowTextA(EasyGUI_WindowHWND, pszMem, GetWindowTextLength(EasyGUI_WindowHWND) + 1);
            return pszMem;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL Window_Move(const BOOL Window_Move_ = true) noexcept//移动GUI窗口（放在循环(不用放等待函数和消息循环函数) 非事件）
        {
            //--------------------------------消息循环
            MSG msg = { 0 };
            if (GetMessage(&msg, 0, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            //----------------------------------------
            GetCursorPos(&EasyGUI_MousePos); GetWindowRect(EasyGUI_WindowHWND, &EasyGUI_WindowPos);//刷新坐标
            static BOOL 防止脱离 = false;
            static int OldX; static int OldY;//按下时坐标
            static BOOL 保存鼠标坐标 = false;
            if (GetForegroundWindow() == EasyGUI_WindowHWND)//检测窗口是否在最前端
            {
                if (!Mouse_Block_ && GetAsyncKeyState(VK_LBUTTON) && !防止脱离 && Window_Move_)//当鼠标指针不在Block上则可以移动窗口
                {
                    if (保存鼠标坐标)
                    {
                        OldX = (EasyGUI_MousePos.x - EasyGUI_WindowPos.left);
                        OldY = (EasyGUI_MousePos.y - EasyGUI_WindowPos.top);
                        保存鼠标坐标 = false;
                    }
                    MoveWindow(EasyGUI_WindowHWND, EasyGUI_MousePos.x - OldX, EasyGUI_MousePos.y - OldY, EasyGUI_WindowPos.right - EasyGUI_WindowPos.left, EasyGUI_WindowPos.bottom - EasyGUI_WindowPos.top, TRUE);//移动窗口到鼠标坐标
                    防止脱离 = true;
                }
                else if (防止脱离 && GetAsyncKeyState(VK_LBUTTON))
                {
                    MoveWindow(EasyGUI_WindowHWND, EasyGUI_MousePos.x - OldX, EasyGUI_MousePos.y - OldY, EasyGUI_WindowPos.right - EasyGUI_WindowPos.left, EasyGUI_WindowPos.bottom - EasyGUI_WindowPos.top, TRUE);//移动窗口到鼠标坐标
                    this_thread::sleep_for(chrono::nanoseconds(50));//降低CPU占用 纳秒单位等待函数
                    Mouse_Block_ = true;
                    return true;
                }
                else {
                    防止脱离 = false;
                    保存鼠标坐标 = true;
                    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)this_thread::sleep_for(chrono::nanoseconds(200));
                    else Sleep(15);//降低CPU占用
                    Mouse_Block_ = false;
                    return false;
                }
            }
            else Sleep(30); return false;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void GUI_BackGround(short m_BackGroundStyleCode = 0) noexcept//绘制GUI窗口背景
        {
            CHAR pszMem[MAX_PATH] = { 0 }; GetWindowTextA(EasyGUI_WindowHWND, pszMem, GetWindowTextLength(EasyGUI_WindowHWND) + 1);
            const short XX = EasyGUI_WindowPos.right - EasyGUI_WindowPos.left; const short YY = EasyGUI_WindowPos.bottom - EasyGUI_WindowPos.top;
            vector<int> 彩虹条颜色 = { 0,255,255,255,0,255,255,255,0 };
            vector<int> 主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,5,5,5,30,30,30 };
            if (m_BackGroundStyleCode == 0)//经典黑色主题
            {
                彩虹条颜色 = { 0,255,255,255,0,255,255,255,0 };
                主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,5,5,5,30,30,30 };
            }
            else if (m_BackGroundStyleCode == 1)//白色
            {
                彩虹条颜色 = { 255,255,255,255,255,255,255,255,255 };
                主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,3,3,3,50,50,50 };
            }
            else if (m_BackGroundStyleCode == 2)//黑白色
            {
                彩虹条颜色 = { 150,150,150,255,255,255,150,150,150 };
                主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,3,3,3,30,30,30 };
            }
            else if (m_BackGroundStyleCode == 1337)//仿Gamesense
            {
                彩虹条颜色 = { 100,255,255,255,100,255,255,255,100 };
                主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,5,5,5,30,30,30 };
            }
            else if (m_BackGroundStyleCode == 1367)//仿Gamesense2
            {
                彩虹条颜色 = { 0,255,255,255,0,255,255,255,0 };
                主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,3,3,3,30,30,30 };
            }
            else if (m_BackGroundStyleCode == 1368)//彩色变色渐变条*****************
            {
                彩虹条颜色 = {
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
                主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,3,3,3, Global_EasyGUIColor[0] / 7,Global_EasyGUIColor[1] / 7 ,Global_EasyGUIColor[2] / 7 };
            }
            else if (m_BackGroundStyleCode == 1369)//黑白变色渐变条*****************
            {
                彩虹条颜色 = {
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
                主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,15,15,15,5,5,5 };
            }
            else if (m_BackGroundStyleCode == -1)//粉蓝色
            {
                彩虹条颜色 = { 255,150,255,200,170,255,150,200,255 };
                主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,3,3,3,30,25,35 };
            }
            else if (m_BackGroundStyleCode == -2)//橙黄色
            {
                彩虹条颜色 = { 230,80,80,230,120,60,255,200,30 };
                主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,3,3,3,40,25,25 };
            }
            else if (m_BackGroundStyleCode == -3)//青绿色
            {
                彩虹条颜色 = { 100,200,100,100,200,150,100,180,230 };
                主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,3,3,3,0,30,30 };
            }
            else if (m_BackGroundStyleCode == 999)//毛都没有
            {
                彩虹条颜色 = { 16,16,16,16,16,16,16,16,16 };
                主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,15,15,15,15,15,15 };
            }
            In_DrawRect(0, 0, XX, YY, { 主题颜色[0], 主题颜色[1], 主题颜色[2] });
            In_DrawRect(1, 1, XX - 2, YY - 2, { 主题颜色[3], 主题颜色[4], 主题颜色[5] });
            In_DrawRect(2, 2, XX - 4, YY - 4, { 主题颜色[6], 主题颜色[7], 主题颜色[8] });
            In_DrawRect(5, 5, XX - 10, YY - 10, { 主题颜色[3], 主题颜色[4], 主题颜色[5] });
            In_DrawGradientRect(6, 6, XX - 12, YY - 12, { 主题颜色[12], 主题颜色[13], 主题颜色[14] }, { 主题颜色[15], 主题颜色[16], 主题颜色[17] }, true);//BackGround Gradient
            //-----------彩虹条
            if (m_BackGroundStyleCode != 999)//毛都没有
            {
                In_DrawGradientRect(7, 7, (XX - 7 * 2) / 2, 2, { 彩虹条颜色[0] / 2, 彩虹条颜色[1] / 2, 彩虹条颜色[2] / 2 }, { 彩虹条颜色[3] / 2, 彩虹条颜色[4] / 2, 彩虹条颜色[5] / 2 }, false);
                In_DrawGradientRect(7 + (XX - 7 * 2) / 2, 7, (XX - 7 * 2) / 2, 2, { 彩虹条颜色[3] / 2, 彩虹条颜色[4] / 2, 彩虹条颜色[5] / 2 }, { 彩虹条颜色[6] / 2, 彩虹条颜色[7] / 2, 彩虹条颜色[8] / 2 }, false);
                In_DrawGradientRect(7, 7, (XX - 7 * 2) / 2, 1, { 彩虹条颜色[0], 彩虹条颜色[1], 彩虹条颜色[2] }, { 彩虹条颜色[3], 彩虹条颜色[4], 彩虹条颜色[5] }, false);
                In_DrawGradientRect(7 + (XX - 7 * 2) / 2, 7, (XX - 7 * 2) / 2, 1, { 彩虹条颜色[3], 彩虹条颜色[4], 彩虹条颜色[5] }, { 彩虹条颜色[6], 彩虹条颜色[7], 彩虹条颜色[8] }, false);
            }
            //-----------
            if (m_BackGroundStyleCode != 1337 && m_BackGroundStyleCode != 1367 && m_BackGroundStyleCode != 1368 && m_BackGroundStyleCode != 1369)//排除特定背景标题
            {
                In_DrawString(8 + 1, YY - Global_EasyGUIFontSize - 5, pszMem, { 0,0,0 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
                In_DrawString(8, YY - Global_EasyGUIFontSize - 5, pszMem, { Global_EasyGUIColor[0] / 2,Global_EasyGUIColor[1] / 2 ,Global_EasyGUIColor[2] / 2 }, Global_EasyGUIFont, Global_EasyGUIFontSize, 400);
            }
            if (m_BackGroundStyleCode == 1369)//1369主题独有的星星
            {
                for (short SI = 0; SI < 50; ++SI)
                {
                    srand(SI);
                    const short StarColor = rand() % 200 + 55;
                    In_DrawRect(rand() % (XX - 14) + 7, rand() % (YY - 17) + 10, 1, 1, { StarColor,StarColor,StarColor });
                }
            }
            Global_EasyGUIStyleCode = m_BackGroundStyleCode;//套写菜单风格代码变量(用于和其他函数共享)
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        vector<int> GUI_Block(int X, int Y, int YY, string m_BlockText) noexcept//绘制用以绘制按钮的区块
        {
            In_DrawRect(X, Y, 400, YY, { 0,0,0 });//黑色外边框
            In_DrawRect(X + 1, Y + 1, 400 - 2, YY - 2, { 60,60,60 });//白色外边框
            if (Global_EasyGUIStyleCode == 1368)In_DrawGradientRect(X + 2, Y + 2, 400 - 4, YY - 4, { 10,10,10 }, { Global_EasyGUIColor[0] / 10,Global_EasyGUIColor[1] / 10 ,Global_EasyGUIColor[2] / 10 }, true);//菜单代码渐变背景
            else In_DrawRect(X + 2, Y + 2, 400 - 4, YY - 4, { 15,15,15 });//默认背景
            In_DrawString(X + 20 + 1, Y - 7 + 1, m_BlockText.c_str(), { 50,50,50 }, L"Small Fonts", 14, 700);
            In_DrawString(X + 20, Y - 7, m_BlockText.c_str(), { 200,200,200 }, L"Small Fonts", 14, 700);
            if ((EasyGUI_MousePos.x - EasyGUI_WindowPos.left >= X && EasyGUI_MousePos.x - EasyGUI_WindowPos.left <= X + 400 && EasyGUI_MousePos.y - EasyGUI_WindowPos.top >= Y && EasyGUI_MousePos.y - EasyGUI_WindowPos.top <= Y + YY) || !(EasyGUI_MousePos.x >= EasyGUI_WindowPos.left && EasyGUI_MousePos.x <= EasyGUI_WindowPos.right && EasyGUI_MousePos.y >= EasyGUI_WindowPos.top && EasyGUI_MousePos.y <= EasyGUI_WindowPos.bottom))Mouse_Block_ = true;
            return { X,Y };
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void GUI_Text(vector<int>BlockPos, short LineRow, string Text, vector<int> TextColor = { 200,200,200 }) noexcept//绘制行文字
        {
            if (BlockPos[0] == 0 && BlockPos[1] == 0)return;//当无block则不进行绘制
            In_DrawString(BlockPos[0] + 22 + 30 + 1, BlockPos[1] - 3 + (30 * LineRow) + 1, Text, { 0,0,0 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
            In_DrawString(BlockPos[0] + 22 + 30 + 1, BlockPos[1] - 3 + (30 * LineRow), Text, TextColor, Global_EasyGUIFont, Global_EasyGUIFontSize);
        }
        //--------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL GUI_Checkbox(vector<int>BlockPos, short LineRow, string Text, BOOL& m_CheckboxValue, vector<int> TextColor = { 200,200,200 }) noexcept//绘制点击框
        {
            if (BlockPos[0] == 0 && BlockPos[1] == 0)return 0;//当无block则不进行绘制
            const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos[0] + 30, BlockPos[1] + (30 * LineRow) - 2, 250, 12);//窗口检测
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_)//当最前端窗口为GUI窗口接收按钮事件
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
            In_DrawRect(BlockPos[0] - 1 + 30, BlockPos[1] - 1 + (30 * LineRow), 10, 10, { 0,0,0 });
            In_DrawString(BlockPos[0] + 22 + 30 + 1, BlockPos[1] - 3 + (30 * LineRow) + 1, Text, { 0,0,0 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
            In_DrawString(BlockPos[0] + 22 + 30, BlockPos[1] - 3 + (30 * LineRow), Text, TextColor, Global_EasyGUIFont, Global_EasyGUIFontSize);
            if (m_CheckboxValue)//绘制
            {
                In_DrawGradientRect(BlockPos[0] - 1 + 30 + 1, BlockPos[1] - 1 + (30 * LineRow) + 1, 8, 8, Global_EasyGUIColor, { Global_EasyGUIColor[0] / 5,Global_EasyGUIColor[1] / 5,Global_EasyGUIColor[2] / 5 }, true);
                return true;
            }
            else {
                if (DetectMousePos)In_DrawGradientRect(BlockPos[0] - 1 + 30 + 1, BlockPos[1] - 1 + (30 * LineRow) + 1, 8, 8, { 110,110,110 }, { 30,30,30 }, true);//移动到按钮按钮变亮
                else In_DrawGradientRect(BlockPos[0] - 1 + 30 + 1, BlockPos[1] - 1 + (30 * LineRow) + 1, 8, 8, { 80,80,80 }, { 30,30,30 }, true);
                return false;
            }
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL GUI_Button(vector<int>BlockPos, short LineRow, string Text, short TextPos, BOOL& m_ButtonValue) noexcept//绘制单击按钮
        {
            if (BlockPos[0] == 0 && BlockPos[1] == 0)return 0;//当无block则不进行绘制
            const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos[0] + 55, BlockPos[1] + (30 * LineRow) - 8, 230, 25);//窗口检测机制
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_)//当最前端窗口为GUI窗口接收按钮事件
            {
                if (!m_ButtonValue && GetAsyncKeyState(VK_LBUTTON) & 0x8000 && DetectMousePos)
                {
                    m_ButtonValue = true;
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                }
                else m_ButtonValue = false;
            }
            In_DrawRect(BlockPos[0] - 2 + 55, BlockPos[1] - 2 + (30 * LineRow) - 8, 234, 29, { 0,0,0 });
            In_DrawRect(BlockPos[0] - 1 + 55, BlockPos[1] - 1 + (30 * LineRow) - 8, 232, 27, { 60,60,60 });
            if (DetectMousePos)In_DrawGradientRect(BlockPos[0] + 55, BlockPos[1] + (30 * LineRow) - 8, 230, 25, { 40,40,40 }, { 20,20,20 }, true);
            else In_DrawGradientRect(BlockPos[0] + 55, BlockPos[1] + (30 * LineRow) - 8, 230, 25, { 30,30,30 }, { 20,20,20 }, true);
            In_DrawString(BlockPos[0] + TextPos + 55 + 1, BlockPos[1] + 6 + (30 * LineRow) - 8 + 1, Text, { 0,0,0 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
            In_DrawString(BlockPos[0] + TextPos + 55, BlockPos[1] + 6 + (30 * LineRow) - 8, Text, { 200,200,200 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
            return m_ButtonValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        template<class ValueClass, class CreateClassName>
        ValueClass GUI_Slider(vector<int>BlockPos, short LineRow, string Text, ValueClass StartValue, ValueClass EndValue, ValueClass& m_SliderValue, vector<int> TextColor = { 200,200,200 }) noexcept//绘制滑条
        {
            if (BlockPos[0] == 0 && BlockPos[1] == 0)return 0;//当无block则不进行绘制
            const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos[0] + 55, BlockPos[1] + (6 + 30 * LineRow), 230, 5);//窗口检测
            static BOOL OutSide = false;//防止指针脱落时失去控制力
            if (GetForegroundWindow() == EasyGUI_WindowHWND)//当最前端窗口为GUI窗口接收按钮事件
            {
                static const ValueClass ClassValueDetect = 0.1;
                if (DetectMousePos && GetAsyncKeyState(VK_LEFT) & 0x8000)//当鼠标移动到滑条上方 按键反馈事件
                {
                    if (ClassValueDetect == 0)m_SliderValue--;//检测是否是浮点值
                    else m_SliderValue -= 0.05;
                    keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
                }
                else if (DetectMousePos && GetAsyncKeyState(VK_RIGHT) & 0x8000) {
                    if (ClassValueDetect == 0)m_SliderValue++;//检测是否是浮点值
                    else m_SliderValue += 0.05;
                    keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
                }
                if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && DetectMousePos && !OutSide)OutSide = true;
                if (OutSide && GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                    m_SliderValue = ((EasyGUI_MousePos.x - BlockPos[0] - 54 - EasyGUI_WindowPos.left) * (EndValue - StartValue) / 230) + StartValue;
                    Mouse_Block_ = true; Mouse_Slider_ = true;
                }
                else if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
                {
                    OutSide = false; Mouse_Slider_ = false;
                }
            }
            int SliderPos = (float)(m_SliderValue - StartValue) / (float)(EndValue - StartValue) * 230;
            if (SliderPos >= 230)SliderPos = 230; else if (SliderPos <= 0) SliderPos = 0;
            if (m_SliderValue <= StartValue)m_SliderValue = StartValue; else if (m_SliderValue >= EndValue)m_SliderValue = EndValue;
            stringstream ss; ss << fixed << setprecision(4) << m_SliderValue; ss >> m_SliderValue;//只保留4位小数点后数
            In_DrawRect(BlockPos[0] - 1 + 55, BlockPos[1] - 1 + (6 + 30 * LineRow), 230 + 2, 7, { 0,0,0 });//黑色外边框
            if (DetectMousePos || OutSide)In_DrawGradientRect(BlockPos[0] + 55, BlockPos[1] + (6 + 30 * LineRow), 230, 5, { 40,40,40 }, { 60,60,60 }, true);//滑条背景
            else In_DrawGradientRect(BlockPos[0] + 55, BlockPos[1] + (6 + 30 * LineRow), 230, 5, { 30,30,30 }, { 60,60,60 }, true);
            In_DrawGradientRect(BlockPos[0] + 55, BlockPos[1] + (6 + 30 * LineRow), SliderPos, 5, Global_EasyGUIColor, { Global_EasyGUIColor[0] / 5,Global_EasyGUIColor[1] / 5,Global_EasyGUIColor[2] / 5 }, true);//滑条
            In_DrawString(BlockPos[0] + 55 + 1, BlockPos[1] - 16 + (6 + 30 * LineRow) + 1, Text, { 0,0,0 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
            In_DrawString(BlockPos[0] + 55, BlockPos[1] - 16 + (6 + 30 * LineRow), Text, TextColor, Global_EasyGUIFont, Global_EasyGUIFontSize);
            In_DrawString_Simple(BlockPos[0] + 230 + 10 + 55, BlockPos[1] - 4 + (6 + 30 * LineRow), ss.str(), { 150,150,150 });//返回值绘制
            return m_SliderValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        template<class CreateClassName>
        int GUI_KeySelector(vector<int>BlockPos, short LineRow, int& m_KeySelectValue) noexcept//绘制按键选取按钮
        {
            if (BlockPos[0] == 0 && BlockPos[1] == 0)return 0;//当无block则不进行绘制
            if (m_KeySelectValue == 0xCCCCCCCC)m_KeySelectValue = 0;//修复过量
            const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos[0] + 350, BlockPos[1] + 26 + (30 * (LineRow - 1)), 40, 12);//窗口检测
            static BOOL BoxMea = false;//只声明一次初始开关设定变量
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_)//当最前端窗口为GUI窗口接收按钮事件
            {
                if (!BoxMea && GetAsyncKeyState(VK_LBUTTON) & 0x8000 && DetectMousePos)
                {
                    BoxMea = true;
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                }
                else if (BoxMea)
                {
                    for (int i = 0x01; i < 0xFE; ++i)//vk键码遍历
                    {
                        if (GetAsyncKeyState(i) & 0x8000)//当按下任意键
                        {
                            m_KeySelectValue = i;
                            BoxMea = false;
                        }
                    }
                }
            }
            if (!BoxMea)
            {
                if (DetectMousePos)In_DrawString_Simple(BlockPos[0] + 355, BlockPos[1] + 27 + (30 * (LineRow - 1)), In_VKCode_to_String(m_KeySelectValue), { 130,130,130 });
                else In_DrawString_Simple(BlockPos[0] + 355, BlockPos[1] + 27 + (30 * (LineRow - 1)), In_VKCode_to_String(m_KeySelectValue), { 100,100,100 });
                return m_KeySelectValue;
            }
            else {
                In_DrawString_Simple(BlockPos[0] + 355, BlockPos[1] + 27 + (30 * (LineRow - 1)), "[-]", { 180,130,100 });
                return 0;
            }
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL GUI_Tips(vector<int>BlockPos, short LineRow, string m_TipsString) noexcept//鼠标指针提示(只支持单行字符)   (代码写在最后为了不被覆盖绘制)
        {
            if (BlockPos[0] == 0 && BlockPos[1] == 0)return 0;//当无block则不进行绘制
            In_DrawString_Simple(BlockPos[0] + 7, BlockPos[1] + 27 + (30 * (LineRow - 1)), "[?]", { 100,100,100 });//GUI绘制
            if (GetForegroundWindow() == EasyGUI_WindowHWND && In_MouseEventJudgment(BlockPos[0] + 7, BlockPos[1] + 26 + (30 * (LineRow - 1)), 13, 12) && !Mouse_Slider_)//当鼠标移动到问号 且GUI窗口为最顶层
            {
                In_DrawRect(EasyGUI_MousePos.x - EasyGUI_WindowPos.left + 15, EasyGUI_MousePos.y - EasyGUI_WindowPos.top + 15, strlen(m_TipsString.c_str()) * 6, 20, { 0,0,0 });
                In_DrawRect(EasyGUI_MousePos.x - EasyGUI_WindowPos.left + 15 + 1, EasyGUI_MousePos.y - EasyGUI_WindowPos.top + 15 + 1, strlen(m_TipsString.c_str()) * 6 - 2, 20 - 2, { 60,60,60 });
                In_DrawRect(EasyGUI_MousePos.x - EasyGUI_WindowPos.left + 15 + 2, EasyGUI_MousePos.y - EasyGUI_WindowPos.top + 15 + 2, strlen(m_TipsString.c_str()) * 6 - 4, 20 - 4, { 15,15,15 });
                In_DrawString_Simple(EasyGUI_MousePos.x - EasyGUI_WindowPos.left + 15 + 4, EasyGUI_MousePos.y - EasyGUI_WindowPos.top + 15 + 4, m_TipsString, { 255,255,255 });
                return true;
            }
            else return false;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        vector<int> GUI_ColorSelector(vector<int>BlockPos, short LineRow, vector<int>& m_ColorValue) noexcept//颜色选择器
        {
            if (BlockPos[0] == 0 && BlockPos[1] == 0)return { -1,-1,-1 };//当无block则不进行绘制
            if (In_MouseEventJudgment(BlockPos[0] + 360, BlockPos[1] - 6 + (30 * LineRow), 20, 20) && (GetAsyncKeyState(VK_LBUTTON) & 0x8000) && !Mouse_Slider_)//复制选取的颜色值
            {
                const string Color_String_Copy__ = to_string(m_ColorValue[0]) + ", " + to_string(m_ColorValue[1]) + ", " + to_string(m_ColorValue[2]);//要复制的字符串
                OpenClipboard(NULL);//打开剪切板
                EmptyClipboard();//清空剪切板
                const HANDLE hHandle = GlobalAlloc(GMEM_FIXED, strlen(Color_String_Copy__.c_str()) + 1);//分配内存
                strcpy_s((char*)GlobalLock(hHandle), strlen(Color_String_Copy__.c_str()) + 1, Color_String_Copy__.c_str());
                SetClipboardData(CF_TEXT, hHandle);//设置剪切板数据
                GlobalUnlock(hHandle);//解除锁定
                CloseClipboard();//关闭剪切板
                Beep(100, 30);//复制成功提醒
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            }
            for (short Color_Bl = 0; Color_Bl <= 2; ++Color_Bl)
            {
                const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos[0] + 218 + 46 * Color_Bl, BlockPos[1] - 6 + (30 * LineRow), 41, 20);
                if (GetForegroundWindow() == EasyGUI_WindowHWND && DetectMousePos && !Mouse_Slider_)//当最前端窗口为GUI窗口接收按钮事件 //当鼠标移动到滑条上方 按键反馈事件
                {
                    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)m_ColorValue[Color_Bl]++;
                    else if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)m_ColorValue[Color_Bl]--;
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                    if (GetAsyncKeyState(VK_LEFT) & 0x8000)m_ColorValue[Color_Bl] += 5;
                    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)m_ColorValue[Color_Bl] -= 5;
                }
                if (m_ColorValue[Color_Bl] >= 255)m_ColorValue[Color_Bl] = 255;
                else if (m_ColorValue[Color_Bl] <= 0)m_ColorValue[Color_Bl] = 0;
                In_DrawRect(BlockPos[0] + 218 + 46 * Color_Bl, BlockPos[1] - 6 + (30 * LineRow), 41, 20, { 0,0,0 });//Color_Block
                if (DetectMousePos)In_DrawGradientRect(BlockPos[0] + 218 + 46 * Color_Bl + 1, BlockPos[1] - 6 + (30 * LineRow) + 1, 41 - 2, 20 - 2, { 60,60,60 }, { 30,30,30 }, true);
                else In_DrawGradientRect(BlockPos[0] + 218 + 46 * Color_Bl + 1, BlockPos[1] - 6 + (30 * LineRow) + 1, 41 - 2, 20 - 2, { 50,50,50 }, { 30,30,30 }, true);
            }
            In_DrawString_Simple(BlockPos[0] + 218 + 5, BlockPos[1] - 3 + (30 * LineRow) + 1, "R: " + to_string(m_ColorValue[0]), { 150,150,150 });
            In_DrawString_Simple(BlockPos[0] + 218 + 46 + 5, BlockPos[1] - 3 + (30 * LineRow) + 1, "G: " + to_string(m_ColorValue[1]), { 150,150,150 });
            In_DrawString_Simple(BlockPos[0] + 218 + 46 * 2 + 5, BlockPos[1] - 3 + (30 * LineRow) + 1, "B: " + to_string(m_ColorValue[2]), { 150,150,150 });
            In_DrawRect(BlockPos[0] + 360, BlockPos[1] - 6 + (30 * LineRow), 20, 20, { 0,0,0 });//Color
            In_DrawGradientRect(BlockPos[0] + 360 + 1, BlockPos[1] - 6 + (30 * LineRow) + 1, 20 - 2, 20 - 2, m_ColorValue, { m_ColorValue[0] / 4,m_ColorValue[1] / 4,m_ColorValue[2] / 4 }, true);
            return m_ColorValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        vector<float> GUI_PosSelector(vector<int>BlockPos, short LineRow, vector<float>& m_PosValue) noexcept//坐标选择器
        {
            if (BlockPos[0] == 0 && BlockPos[1] == 0)return { -1,-1,-1 };//当无block则不进行绘制
            for (short Color_Bl = 0; Color_Bl <= 2; ++Color_Bl)
            {
                const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos[0] + 180 + 70 * Color_Bl, BlockPos[1] - 6 + (30 * LineRow), 68, 20);
                if (GetForegroundWindow() == EasyGUI_WindowHWND && DetectMousePos && !Mouse_Slider_)//当最前端窗口为GUI窗口接收按钮事件 //当鼠标移动到滑条上方 按键反馈事件
                {
                    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)m_PosValue[Color_Bl] += 0.03;
                    else if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)m_PosValue[Color_Bl] -= 0.03;
                    if (GetAsyncKeyState(VK_LEFT) & 0x8000)m_PosValue[Color_Bl] += 1;
                    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)m_PosValue[Color_Bl] -= 1;
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                    keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
                    keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
                    if (GetAsyncKeyState(VK_UP) & 0x8000)m_PosValue[Color_Bl] += 10;//快速变值
                    else if (GetAsyncKeyState(VK_DOWN) & 0x8000)m_PosValue[Color_Bl] -= 10;
                }
                In_DrawRect(BlockPos[0] + 180 + 70 * Color_Bl, BlockPos[1] - 6 + (30 * LineRow), 70, 20, { 0,0,0 });//Color_Block
                if (DetectMousePos)In_DrawGradientRect(BlockPos[0] + 180 + 70 * Color_Bl + 1, BlockPos[1] - 6 + (30 * LineRow) + 1, 70 - 2, 20 - 2, { 60,60,60 }, { 30,30,30 }, true);
                else In_DrawGradientRect(BlockPos[0] + 180 + 70 * Color_Bl + 1, BlockPos[1] - 6 + (30 * LineRow) + 1, 70 - 2, 20 - 2, { 50,50,50 }, { 30,30,30 }, true);
            }
            stringstream Float_X_; Float_X_ << fixed << setprecision(2) << m_PosValue[0]; Float_X_ >> m_PosValue[0];//只保留2位小数点后数
            stringstream Float_Y_; Float_Y_ << fixed << setprecision(2) << m_PosValue[1]; Float_Y_ >> m_PosValue[1];
            stringstream Float_Z_; Float_Z_ << fixed << setprecision(2) << m_PosValue[2]; Float_Z_ >> m_PosValue[2];
            In_DrawString_Simple(BlockPos[0] + 180 + 5, BlockPos[1] - 3 + (30 * LineRow) + 1, "X: " + Float_X_.str(), { 150,150,150 });
            In_DrawString_Simple(BlockPos[0] + 180 + 70 + 5, BlockPos[1] - 3 + (30 * LineRow) + 1, "Y: " + Float_Y_.str(), { 150,150,150 });
            In_DrawString_Simple(BlockPos[0] + 180 + 70 * 2 + 5, BlockPos[1] - 3 + (30 * LineRow) + 1, "Z: " + Float_Z_.str(), { 150,150,150 });
            return m_PosValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        int GUI_Block_PanelSelector(int X, int Y, int XX, int YY, string m_BlockText, vector<string>m_BlockText_, int& m_In_B_Block) noexcept//区块_大区块选择器
        {
            In_DrawRect(X, Y, XX, YY, { 0,0,0 });//黑色外边框
            In_DrawRect(X + 1, Y + 1, XX - 2, YY - 2, { 60,60,60 });//白色外边框
            In_DrawRect(X + 2, Y + 2, XX - 4, YY - 4, { 20,20,20 });//默认背景
            In_DrawString(X + 15 + 1, Y - 7 + 1, m_BlockText.c_str(), { 50,50,50 }, L"Small Fonts", 14, 700);
            In_DrawString(X + 15, Y - 7, m_BlockText.c_str(), { 200,200,200 }, L"Small Fonts", 14, 700);
            for (short i = 0; i < m_BlockText_.size(); ++i)//遍历坐标
            {
                const BOOL DetectMousePos = In_MouseEventJudgment(X, Y + 20 + 30 * i - 2 - 4, XX, 15 + 8);
                if (m_In_B_Block == i)
                {
                    In_DrawGradientRect(X + 2, Y + 20 + 30 * i - 5, XX - 4, 15 + 10, { 20,20,20 }, { Global_EasyGUIColor[0] / 3,Global_EasyGUIColor[1] / 3,Global_EasyGUIColor[2] / 3 });
                    In_DrawGradientRect(X + 2, Y + 20 + 30 * i - 4, XX - 4, 15 + 8, { Global_EasyGUIColor[0] / 3,Global_EasyGUIColor[1] / 3,Global_EasyGUIColor[2] / 3 }, { 20,20,20 });
                }
                else if (DetectMousePos)
                {
                    In_DrawGradientRect(X + 2, Y + 20 + 30 * i - 4, XX - 4, 15 + 8, { 40,40,40 }, { 20,20,20 });
                    if (GetForegroundWindow() == EasyGUI_WindowHWND && GetAsyncKeyState(VK_LBUTTON) & 0x8000 && !Mouse_Slider_)
                    {
                        m_In_B_Block = i;
                        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                    }
                }
                In_DrawString(X + 20 + 1, Y + 20 + 30 * i + 1, m_BlockText_[i], { 0,0,0 }, Global_EasyGUIFont, 15);
                In_DrawString(X + 20 + 1, Y + 20 + 30 * i, m_BlockText_[i], { 220,220,220 }, Global_EasyGUIFont, 15);
            }
            if ((EasyGUI_MousePos.x - EasyGUI_WindowPos.left >= X && EasyGUI_MousePos.x - EasyGUI_WindowPos.left <= X + XX && EasyGUI_MousePos.y - EasyGUI_WindowPos.top >= Y && EasyGUI_MousePos.y - EasyGUI_WindowPos.top <= Y + YY) || !(EasyGUI_MousePos.x >= EasyGUI_WindowPos.left && EasyGUI_MousePos.x <= EasyGUI_WindowPos.right && EasyGUI_MousePos.y >= EasyGUI_WindowPos.top && EasyGUI_MousePos.y <= EasyGUI_WindowPos.bottom))Mouse_Block_ = true;
            return m_In_B_Block;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
    private:
    };
}
