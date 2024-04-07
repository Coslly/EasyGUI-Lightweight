#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include <thread>
#include <iomanip>
#include <sstream>
#include <algorithm>
#pragma comment(lib, "MSIMG32.LIB")
using namespace std;
namespace EasyGUI//EasyGUI Release[2024-04-07 12:00]
{
    /*
    int main()
    {
        ShowWindow(GetConsoleWindow(), true);//Show Console Window
        system("cls"); printf("EasyGUI-Lightweight\nGithub: https://github.com/Coslly/EasyGUI-Lightweight.git\n");
        EasyGUI::EasyGUI GUI_Variable;//Initialize GUI variables
        GUI_Variable.Window_Create(590, 360, "Test Windows", true);
        GUI_Variable.Window_SetAlpha(250);
        while (true)
        {
            static BOOL UI_Checkbox = false;
            static int UI_Slider_int = 5;
            static float UI_Slider_float = 5;
            static BOOL UI_Button = false;
            static BOOL UI_Button_Small = false;
            static int UI_KeySelector = 4;
            static BOOL UI_InvertScreenColor = false;
            static EasyGUI::Vector4 UI_ColorSelector = { 255,255,255 };
            static EasyGUI::Vector3 UI_PosSelector = { 0.23,100,1000 };
            static int UI_PanelSelector = 0;
            static string UI_InputText = "Input text";
            static int UI_List = 0;
            EasyGUI::EasyGUI_IO GUI_IO = GUI_Variable.Get_IO();//Get Global Input/Output Value
            if (!GUI_Variable.Window_Move())//MoveWindow Funtion (You must add!! cause it have MessageLoop)
            {
                GUI_Variable.GUI_BackGround(true);//BackGround
                GUI_Variable.GUI_Block_Panel(30, 30, 100, 300, "Panel", { "Panel 1","Panel 2","Panel 3" }, UI_PanelSelector);
                if (UI_PanelSelector == 0)//Panel 1 Screen
                {
                    const auto Block = GUI_Variable.GUI_Block(160, 30, 300, "Block");//Block
                    GUI_Variable.GUI_Checkbox(Block, 1, "This is a Checkbox", UI_Checkbox);
                    GUI_Variable.GUI_KeySelector<class CALSS_EasyGUI_1>(Block, 1, UI_KeySelector);
                    GUI_Variable.GUI_Slider<int, class CALSS_EasyGUI_2>(Block, 2, "Slider int", 0, 10, UI_Slider_int);
                    GUI_Variable.GUI_Slider<float, class CALSS_EasyGUI_3>(Block, 3, "Slider float", 0, 10, UI_Slider_float);
                    GUI_Variable.GUI_Button(Block, 4, "Button", UI_Button);
                    static auto ButtonClick = 0;
                    if (UI_Button || UI_Button_Small)ButtonClick++;
                    GUI_Variable.GUI_Text(Block, 5, "Button hit: " + to_string(ButtonClick));
                    GUI_Variable.GUI_Checkbox(Block, 6, "Invert screen color", UI_InvertScreenColor);
                    GUI_Variable.GUI_Text(Block, 7, "Main color");
                    GUI_Variable.GUI_ColorSelector(Block, 7, UI_ColorSelector);
                    GUI_Variable.Global_Set_EasyGUI_Color(UI_ColorSelector);
                    GUI_Variable.GUI_Text(Block, 8, "Pos selector");
                    GUI_Variable.GUI_PosSelector(Block, 8, UI_PosSelector);
                    GUI_Variable.GUI_Button_Small(Block, 2, UI_Button_Small);
                    GUI_Variable.GUI_Text(Block, 9, "FPS: " + to_string(GUI_IO.DrawFPS));
                    GUI_Variable.GUI_Tips(Block, 1, "Some tips");
                }
                else if (UI_PanelSelector == 1)//Panel 2 Screen
                {
                    const auto Block = GUI_Variable.GUI_Block(160, 30, 300, "Block");//Block
                    GUI_Variable.GUI_InputText<class CALSS_EasyGUI_4>(Block, 1, UI_InputText);
                    GUI_Variable.GUI_List(Block, 2, { "Hello","C++","Java","CS","Windows" }, UI_List);
                }
                GUI_Variable.Draw_GUI(UI_InvertScreenColor);
            }
        }
    }
    */
    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept//消息循环(用于解决窗口未响应问题 接收窗口消息)
    {
        switch (msg)
        {
        case WM_ERASEBKGND:return TRUE; break;
        case WM_PAINT:return TRUE; break;//一直重绘
        case WM_CLOSE:exit(0); break;//接收到关闭窗口事件时返回全部线程
        }
        return DefWindowProc(hwnd, msg, wp, lp);//定义回调函数的返回值
    }
    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    struct Vector2//用来储存坐标数据 XY
    {
        constexpr Vector2(const int x = 0, const int y = 0) noexcept :x(x), y(y) { }
        constexpr const Vector2 operator+(const Vector2 other) const noexcept
        {
            return Vector2{ x + other.x, y + other.y };
        }
        constexpr const Vector2 operator-(const Vector2 other) const noexcept
        {
            return Vector2{ x - other.x, y - other.y };
        }
        constexpr const Vector2 operator*(const int factor) const noexcept
        {
            return Vector2{ x * factor, y * factor };
        }
        constexpr const Vector2 operator/(const int factor) const noexcept
        {
            return Vector2{ x / factor, y / factor };
        }
        constexpr const bool IsZero() const noexcept { return x == 0 && y == 0; }
        int x, y;
    };
    struct Vector3//用来储存坐标数据 XYZ
    {
        constexpr Vector3(const float x = 0, const float y = 0, const float z = 0) noexcept :x(x), y(y), z(z) { }
        constexpr const Vector3 operator+(const Vector3 other) const noexcept
        {
            return Vector3{ x + other.x, y + other.y, z + other.z };
        }
        constexpr const Vector3 operator-(const Vector3 other) const noexcept
        {
            return Vector3{ x - other.x, y - other.y, z - other.z };
        }
        constexpr const Vector3 operator*(const float factor) const noexcept
        {
            return Vector3{ x * factor, y * factor, z * factor };
        }
        constexpr const Vector3 operator/(const float factor) const noexcept
        {
            return Vector3{ x / factor, y / factor, z / factor };
        }
        constexpr const Vector3 ToAngle() const noexcept
        {
            return Vector3{ atan2(-z, hypot(x, y)) * (180.0f / (float)acos(-1)),atan2(y, x) * (180.0f / (float)acos(-1)),0 };
        }
        constexpr const bool IsZero() const noexcept { return x == 0 && y == 0 && z == 0; }
        float x, y, z;
    };
    struct Vector4//用来储存颜色数据 RGBA
    {
        constexpr Vector4(const int r = 0, const int g = 0, const int b = 0, const int a = 255) noexcept :r(r), g(g), b(b), a(a) {}
        constexpr const Vector4 operator+(const Vector4 other) const noexcept
        {
            return Vector4{ r + other.r, g + other.g, b + other.b, a };
        }
        constexpr const Vector4 operator-(const Vector4 other) const noexcept
        {
            return Vector4{ r - other.r, g - other.g, b - other.b, a };
        }
        constexpr const Vector4 operator*(const int factor) const noexcept
        {
            return Vector4{ r * factor, g * factor, b * factor, a };
        }
        constexpr const Vector4 operator/(const int factor) const noexcept
        {
            return Vector4{ r / factor, g / factor, b / factor, a };
        }
        constexpr const Vector4 D_Alpha(const int Alpha, const int Limit_s = 0) const noexcept { if (Alpha <= Limit_s)return { r,g,b,Limit_s }; else return { r,g,b,Alpha }; }
        constexpr const Vector4 Re_Col() const noexcept
        {
            Vector4 Color_Var = Vector4{ r, g , b , a };
            if (Color_Var.r <= 0)Color_Var.r = 0; else if (Color_Var.r >= 255)Color_Var.r = 255;
            if (Color_Var.g <= 0)Color_Var.g = 0; else if (Color_Var.g >= 255)Color_Var.g = 255;
            if (Color_Var.b <= 0)Color_Var.b = 0; else if (Color_Var.b >= 255)Color_Var.b = 255;
            if (Color_Var.a <= 0)Color_Var.a = 0; else if (Color_Var.a >= 255)Color_Var.a = 255;
            return Color_Var;
        }
        int r, g, b, a;
    };
    //using namespace Variable;//变量类型库 Head.h
    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    struct EasyGUI_IO
    {
        int DrawFPS = 0;//绘制帧数
        HWND HWND = 0;//全局GUI窗口HWND
        HDC HDC = 0;//全局GUI窗口HDC
        string FontName = "";//全局GUI字体名字
        int FontSize = 0;//全局GUI字体大小
        Vector4 GUIColor = { 0,0,0 };//全局GUI主题色
        int GUIColor_Alpha = 0;//全局GUI主题色(透明度)
        Vector2 WindowPos = { 0,0 };//全局GUI窗口坐标
        Vector2 WindowSize = { 0,0 };//全局GUI窗口大小
        string WindowTitle = "";//全局GUI窗口标题
        Vector2 MousePos = { 0,0 };//GUI检测的鼠标坐标
        vector<int> GUIColor_Rainbow = { 0,0,0,0,0,0,0,0,0 };//全局GUI彩虹颜色
    };
    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    class EasyGUI
    {
    private:
        //-----------菜单风格
        string Global_EasyGUIFont = "Verdana";//全局字体
        int Global_EasyGUIFontSize = 13;//字体大小
        Vector4 Global_EasyGUIColor = { 255,255,255 };//全局主题颜色
        int Global_EasyGUIColor_Alpha = 250;
        //------------------
        HWND EasyGUI_WindowHWND = NULL;//GUI Window HWND
        HDC EasyGUI_WindowHDC = NULL;//GUI Window HDC
        Vector2 PaintSize;//DoubleBufferPaint Size 画布大小
        HDC EasyGUI_DrawHDC = NULL;//EasyGUI DrawHDC GUI要绘制的HDC
        POINT EasyGUI_MousePos;//EasyGUI鼠标坐标
        RECT EasyGUI_WindowPos;//EasyGUI窗口坐标
        int EasyGUI_FPS = 0;//EasyGUI绘制帧数
        //------------------
        BOOL Mouse_Block_, Mouse_Slider_ = false;
        //---------------------------------------------------------------------
        void In_DrawRect(int X, int Y, int XX, int YY, Vector4 Color) noexcept//绘制矩形 (方便制作GUI)
        {
            //------------------------初始化
            TRIVERTEX vert[2]; GRADIENT_RECT gRect;
            vert[0].Alpha = 0x0000; vert[1].Alpha = 0x0000;
            gRect.UpperLeft = 0; gRect.LowerRight = 1;
            //------------------------
            const COLORREF Color_ = RGB(Color.r, Color.g, Color.b);
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
        void In_DrawGradientRect(int X, int Y, int XX, int YY, Vector4 Color_1, Vector4 Color_2, BOOL Draw_Style = false) noexcept//绘制渐变矩形 (方便制作GUI)
        {//false = 横向; true = 竖向
            //------------------------初始化
            TRIVERTEX vert[2]; GRADIENT_RECT gRect;
            vert[0].Alpha = 0x0000; vert[1].Alpha = 0x0000;
            gRect.UpperLeft = 0; gRect.LowerRight = 1;
            //------------------------
            const COLORREF Color1 = RGB(Color_1.r, Color_1.g, Color_1.b);
            const COLORREF Color2 = RGB(Color_2.r, Color_2.g, Color_2.b);
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
        void In_DrawLine(int X, int Y, int XX, int YY, Vector4 Color, int LineThickness = 1) noexcept//屏幕画线 (方便制作GUI)
        {
            const auto LineColor = SelectObject(EasyGUI_DrawHDC, CreatePen(PS_SOLID, LineThickness, RGB(Color.r, Color.g, Color.b)));
            MoveToEx(EasyGUI_DrawHDC, X, Y, NULL);
            LineTo(EasyGUI_DrawHDC, XX, YY);
            DeleteObject(LineColor);
        }
        //---------------------------------------------------------------------
        void In_DrawString(int X, int Y, string String, Vector4 TextColor, string Fount_Name, short Fount_Size, short Font_Width = FW_NORMAL, BOOL AntiAlias = true) noexcept//绘制文字 (方便制作GUI)
        {
            HGDIOBJ FontPen;
            if (AntiAlias)FontPen = SelectObject(EasyGUI_DrawHDC, CreateFontA(Fount_Size, 0, 0, 0, Font_Width, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, Fount_Name.c_str()));
            else FontPen = SelectObject(EasyGUI_DrawHDC, CreateFontA(Fount_Size, 0, 0, 0, Font_Width, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, Fount_Name.c_str()));
            SetTextColor(EasyGUI_DrawHDC, RGB(TextColor.r, TextColor.g, TextColor.b));//文字颜色
            SetBkMode(EasyGUI_DrawHDC, TRANSPARENT);//背景透明
            const auto len = MultiByteToWideChar(CP_UTF8, 0, String.c_str(), -1, NULL, 0);//转码 UTF-8 (为了显示中文)
            wchar_t* wide_text = new wchar_t[len];
            MultiByteToWideChar(CP_UTF8, 0, String.c_str(), -1, wide_text, len);//转码 UTF-8 (为了显示中文)
            TextOutW(EasyGUI_DrawHDC, X, Y, wide_text, len - 1);
            DeleteObject(FontPen);
            delete[] wide_text;
        }
        //---------------------------------------------------------------------
        void In_DrawString_Simple(int X, int Y, string String, Vector4 TextColor = { 255,255,255 }) noexcept//绘制简单文字 (方便制作GUI)
        {
            HGDIOBJ FontPen = SelectObject(EasyGUI_DrawHDC, CreateFontA(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, "Small Fonts"));
            SetBkMode(EasyGUI_DrawHDC, TRANSPARENT);//背景透明
            SetTextColor(EasyGUI_DrawHDC, RGB(0, 0, 0));//文字颜色
            TextOutA(EasyGUI_DrawHDC, X + 1, Y + 1, String.c_str(), strlen(String.c_str()));
            TextOutA(EasyGUI_DrawHDC, X - 1, Y - 1, String.c_str(), strlen(String.c_str()));
            TextOutA(EasyGUI_DrawHDC, X + 1, Y - 1, String.c_str(), strlen(String.c_str()));
            TextOutA(EasyGUI_DrawHDC, X - 1, Y + 1, String.c_str(), strlen(String.c_str()));
            TextOutA(EasyGUI_DrawHDC, X + 1, Y, String.c_str(), strlen(String.c_str()));
            TextOutA(EasyGUI_DrawHDC, X - 1, Y, String.c_str(), strlen(String.c_str()));
            TextOutA(EasyGUI_DrawHDC, X, Y - 1, String.c_str(), strlen(String.c_str()));
            TextOutA(EasyGUI_DrawHDC, X, Y + 1, String.c_str(), strlen(String.c_str()));
            SetTextColor(EasyGUI_DrawHDC, RGB(TextColor.r, TextColor.g, TextColor.b));//文字颜色
            TextOutA(EasyGUI_DrawHDC, X, Y, String.c_str(), strlen(String.c_str()));
            DeleteObject(FontPen);
        }
        //---------------------------------------------------------------------
        BOOL In_MouseEventJudgment(int X, int Y, int XX, int YY) noexcept//检测鼠标坐标是否在窗口矩形坐标内
        {
            if (!(EasyGUI_MousePos.x >= EasyGUI_WindowPos.left && EasyGUI_MousePos.x <= EasyGUI_WindowPos.right && EasyGUI_MousePos.y >= EasyGUI_WindowPos.top && EasyGUI_MousePos.y <= EasyGUI_WindowPos.bottom))return false;//当指针不在窗口内
            if (EasyGUI_MousePos.x - EasyGUI_WindowPos.left >= X && EasyGUI_MousePos.x - EasyGUI_WindowPos.left <= X + XX && EasyGUI_MousePos.y - EasyGUI_WindowPos.top >= Y && EasyGUI_MousePos.y - EasyGUI_WindowPos.top <= Y + YY)return true;
            else return false;
        }
        //---------------------------------------------------------------------
        BOOL In_KeyEvent(int VK_CODE, BOOL Release = false) noexcept//检测按键是否被按下 (后者参数为按下后是否立马释放)
        {
            const BOOL Key_State = GetAsyncKeyState(VK_CODE) & 0x8000;
            if (Release && Key_State)//释放按键
            {
                if (VK_CODE == VK_LBUTTON)mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//鼠标键盘判断
                else if (VK_CODE == VK_RBUTTON)mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                else if (VK_CODE == VK_MBUTTON)mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
                else keybd_event(VK_CODE, 0, KEYEVENTF_KEYUP, 0);
            }
            return Key_State;
        }
        //---------------------------------------------------------------------
        template<class CreateClassName>//防止冲突
        float In_Animation(float Value, float Speed = 1.3, Vector2 Limit = { 0,0 }) noexcept//快到慢动画
        {
            static float ReturnValue = Value;
            if (Value > ReturnValue)ReturnValue += (Value - ReturnValue) / Speed;
            else if (Value < ReturnValue)ReturnValue -= (ReturnValue - Value) / Speed;
            if (Limit.x != 0 || Limit.y != 0)//限制动画输出值 (默认值(最小值,最大值)0,0为不限制)
            {
                if (Limit.x > ReturnValue)ReturnValue = Limit.x;
                else if (Limit.y < ReturnValue)ReturnValue = Limit.y;
            }
            return ReturnValue;
        }
        //---------------------------------------------------------------------
        template<class CreateClassName>//防止同函数同步
        BOOL In_TickSleep(int Time_MS) noexcept//不受线程影响的Sleep函数
        {
            const long Tick = GetTickCount64(); static long OldTick = Tick;
            if (Tick - OldTick >= Time_MS) { OldTick = Tick; return true; }//当达到一定数值返回并且重写变量
            else return false;
        }
        //---------------------------------------------------------------------
    public:
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Global_Set_EasyGUI_Font(string Font) noexcept { Global_EasyGUIFont = Font; }//设置全局GUI字体
        void Global_Set_EasyGUI_FontSize(int Size) noexcept { Global_EasyGUIFontSize = Size; }//设置全局GUI字体大小
        void Global_Set_EasyGUI_Color(Vector4 GlobalColor) noexcept { Global_EasyGUIColor = GlobalColor; }//设置全局主题颜色
        string Global_Get_EasyGUI_Font() noexcept { return Global_EasyGUIFont; }//获取全局GUI字体
        int Global_Get_EasyGUI_FontSize() noexcept { return Global_EasyGUIFontSize; }//获取全局GUI字体大小
        Vector4 Global_Get_EasyGUI_Color() noexcept { return Global_EasyGUIColor; }//获取全局主题颜色
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        Vector2 Initialization_Fast(int Window_Size_Y_ = 400) noexcept//快速初始化 (创建窗口 创建1区块!!! 为了调试减少代码量制作的单一函数)
        {
            /*Example****
            while (true)
            {
                static EasyGUI::EasyGUI GUI_Variable;//Initialize GUI variables
                const auto Block = GUI_Variable.Initialization_Fast();
                if (!GUI_Variable.Window_Move())
                {
                    //Your Controls Code***


                    GUI_Variable.Draw_GUI();
                }
            }
            */
            static BOOL In_OneSt__ = true;
            if (In_OneSt__)//创建窗口 || 只执行一次(由于之放置一个函数 则不用添加模板)
            {
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
                RenderWindowM.lpszClassName = L"Test Windows  ";//窗口类的名称，操作系统根据类的名称做映射
                RegisterClass(&RenderWindowM);//将这个窗体注册（告诉）到操作系统
                const HWND hWnd = CreateWindowEx(WS_EX_LAYERED, L"Test Windows  ", L"Test Windows  ", WS_POPUP, GetSystemMetrics(SM_CXSCREEN) / 2 - 460 / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - Window_Size_Y_ / 2, 460, Window_Size_Y_, 0, 0, GetModuleHandle(NULL), 0);
                if (hWnd)//当创建成功
                {
                    UpdateWindow(hWnd);
                    ShowWindow(hWnd, SW_SHOW);
                    SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), Global_EasyGUIColor_Alpha, LWA_ALPHA);
                    EasyGUI_WindowHWND = hWnd;
                    EasyGUI_WindowHDC = GetWindowDC(hWnd);
                    //---------------------------------------双缓冲开始绘制
                    PaintSize = { 460 + 100, Window_Size_Y_ + 100 };//设定坐标上加上100缓冲区
                    EasyGUI_DrawHDC = CreateCompatibleDC(EasyGUI_WindowHDC);
                    SelectObject(EasyGUI_DrawHDC, (HBITMAP)CreateCompatibleBitmap(EasyGUI_WindowHDC, PaintSize.x, PaintSize.y));
                    //---------------------------------------------
                }
                In_OneSt__ = false;
            }
            In_DrawRect(0, 0, 460, Window_Size_Y_, { 0,0,0 });
            In_DrawRect(1, 1, 460 - 2, Window_Size_Y_ - 2, { 60,60,60 });
            In_DrawRect(2, 2, 460 - 4, Window_Size_Y_ - 4, { 30,30,30 });
            In_DrawRect(5, 5, 460 - 10, Window_Size_Y_ - 10, { 60,60,60 });
            In_DrawGradientRect(6, 6, 460 - 12, Window_Size_Y_ - 12, { 5,5,5 }, { 30,30,30 }, true);//BackGround Gradient
            //---------------------------------------------------------------------------------------------------------------
            In_DrawRect(30, 30, 400, Window_Size_Y_ - 60, { 0,0,0 });//黑色外边框
            In_DrawRect(30 + 1, 30 + 1, 400 - 2, Window_Size_Y_ - 60 - 2, { 60,60,60 });//白色外边框
            In_DrawGradientRect(30 + 2, 30 + 2, 400 - 4, Window_Size_Y_ - 60 - 4, { 10,10,10 }, Global_EasyGUIColor / 10, true);//渐变背景
            In_DrawString(30 + 20 + 1, 30 - 7 + 1, "Block", { 50,50,50 }, "Small Fonts", 14, 700);
            In_DrawString(30 + 20, 30 - 7, "Block", { 200,200,200 }, "Small Fonts", 14, 700);
            if ((EasyGUI_MousePos.x - EasyGUI_WindowPos.left >= 30 && EasyGUI_MousePos.x - EasyGUI_WindowPos.left <= 30 + 400 && EasyGUI_MousePos.y - EasyGUI_WindowPos.top >= 30 && EasyGUI_MousePos.y - EasyGUI_WindowPos.top <= 30 + Window_Size_Y_ - 60) || !(EasyGUI_MousePos.x >= EasyGUI_WindowPos.left && EasyGUI_MousePos.x <= EasyGUI_WindowPos.right && EasyGUI_MousePos.y >= EasyGUI_WindowPos.top && EasyGUI_MousePos.y <= EasyGUI_WindowPos.bottom))Mouse_Block_ = true;
            return { 30,30 };
        }
        BOOL Window_Create(int Size_X, int Size_Y, string WindowTitle, BOOL IfTop = false) noexcept//创建窗口
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
            RenderWindowM.lpszClassName = wstring(WindowTitle.begin(), WindowTitle.end()).c_str();//窗口类的名称，操作系统根据类的名称做映射
            RegisterClass(&RenderWindowM);//将这个窗体注册（告诉）到操作系统
            const HWND hWnd = CreateWindowEx(窗口类型, wstring(WindowTitle.begin(), WindowTitle.end()).c_str(), wstring(WindowTitle.begin(), WindowTitle.end()).c_str(), WS_POPUP, GetSystemMetrics(SM_CXSCREEN) / 2 - Size_X / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - Size_Y / 2, Size_X, Size_Y, 0, 0, GetModuleHandle(NULL), 0);
            if (hWnd)//当创建成功
            {
                UpdateWindow(hWnd);
                ShowWindow(hWnd, SW_SHOW);
                SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), Global_EasyGUIColor_Alpha, LWA_ALPHA);
                EasyGUI_WindowHWND = hWnd;
                EasyGUI_WindowHDC = GetWindowDC(hWnd);
                //---------------------------------------双缓冲开始绘制
                PaintSize = { Size_X + 300,Size_Y + 300 };//设定坐标上加上300缓冲区
                EasyGUI_DrawHDC = CreateCompatibleDC(EasyGUI_WindowHDC);//内存画板 (如果不是最终绘制 请绘制到这里!!!)
                SelectObject(EasyGUI_DrawHDC, (HBITMAP)CreateCompatibleBitmap(EasyGUI_WindowHDC, PaintSize.x, PaintSize.y));
                //---------------------------------------------
                return true;
            }
            else return false;
        }
        void Draw_GUI(BOOL ReverseColor = false) noexcept//双缓冲结束绘制 (绘制最终返回图片)
        {
            if (EasyGUI_MousePos.x == 0 && EasyGUI_MousePos.y == 0)In_DrawString_Simple(0, 0, "You are a unique star in the universe.", Global_EasyGUIColor);//你是宇宙中独有的一颗星
            if (ReverseColor)BitBlt(EasyGUI_DrawHDC, 0, 0, PaintSize.x, PaintSize.y, EasyGUI_DrawHDC, 0, 0, PATINVERT);//反转颜色
            BitBlt(EasyGUI_WindowHDC, 0, 0, PaintSize.x, PaintSize.y, EasyGUI_DrawHDC, 0, 0, SRCCOPY);//最终绘制内存中的图像
            //--------------------------------消息循环
            MSG msg = { 0 };
            if (GetMessage(&msg, 0, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            GetCursorPos(&EasyGUI_MousePos); GetWindowRect(EasyGUI_WindowHWND, &EasyGUI_WindowPos);//刷新鼠标窗口坐标
            //--------------------------------帧数计算
            static int m_fps = 0; m_fps++;
            const int Tick = GetTickCount64(); static int Tick_Old = Tick;
            if (Tick >= Tick_Old + 1000)//每1秒刷新 (计时器)
            {
                Tick_Old = Tick;
                EasyGUI_FPS = m_fps;
                m_fps = 0;
            }
            //----------------------------------------
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        HWND Window_HWND() noexcept { return EasyGUI_WindowHWND; }//获取GUI窗口HWND
        HDC Window_HDC() noexcept { return EasyGUI_DrawHDC; }//获取GUI窗口HDC
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Window_SetPos(Vector2 WindowPos) noexcept//修改GUI窗口坐标
        {
            RECT m_Windowrect; GetWindowRect(EasyGUI_WindowHWND, &m_Windowrect);
            MoveWindow(EasyGUI_WindowHWND, WindowPos.x, WindowPos.y, m_Windowrect.right - m_Windowrect.left, m_Windowrect.bottom - m_Windowrect.top, TRUE);
        }
        Vector2 Window_GetPos() noexcept//获取GUI窗口坐标
        {
            RECT m_Windowrect; GetWindowRect(EasyGUI_WindowHWND, &m_Windowrect);
            return { m_Windowrect.left ,m_Windowrect.top };
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Window_SetSize(Vector2 WindowSize) noexcept//修改GUI窗口大小
        {
            RECT m_Windowrect; GetWindowRect(EasyGUI_WindowHWND, &m_Windowrect);
            MoveWindow(EasyGUI_WindowHWND, m_Windowrect.left, m_Windowrect.top, WindowSize.x, WindowSize.y, TRUE);
        }
        Vector2 Window_GetSize() noexcept//获取GUI窗口大小
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
        void Window_SetAlpha(short WindowAlpha) noexcept//修改GUI窗口整体阿尔法通道
        {
            if (WindowAlpha >= 255)WindowAlpha = 255; else if (WindowAlpha <= 0)WindowAlpha = 0;
            SetLayeredWindowAttributes(EasyGUI_WindowHWND, RGB(0, 0, 0), WindowAlpha, LWA_ALPHA);
            Global_EasyGUIColor_Alpha = WindowAlpha;
        }
        int Window_GetAlpha() noexcept//获取GUI窗口整体阿尔法通道
        {
            return Global_EasyGUIColor_Alpha;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Window_SetTitle(string WindowTitle) noexcept//修改GUI窗口标题
        {
            SetWindowTextA(EasyGUI_WindowHWND, WindowTitle.c_str());//修改窗口标题
        }
        string Window_GetTitle() noexcept//获取GUI窗口标题
        {
            CHAR pszMem[MAX_PATH] = { 0 }; GetWindowTextA(EasyGUI_WindowHWND, pszMem, GetWindowTextLength(EasyGUI_WindowHWND) + 1);
            return pszMem;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        int Window_FPS() noexcept { return EasyGUI_FPS; }//获取GUI绘制帧数
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL Window_Move(short Draw_ms = 5) noexcept//移动GUI窗口 (在GUI循环线程内加入此函数不需要添加延时函数来降低CPU占用)
        {
            //--------------------------------消息循环
            MSG msg = { 0 };
            if (GetMessage(&msg, 0, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            GetCursorPos(&EasyGUI_MousePos); GetWindowRect(EasyGUI_WindowHWND, &EasyGUI_WindowPos);//刷新鼠标窗口坐标
            //---------------------------------------
            static BOOL 防止脱离 = false;
            static int OldX, OldY;//按下时坐标
            static BOOL 保存鼠标坐标 = false;
            if (GetForegroundWindow() == EasyGUI_WindowHWND)//检测窗口是否在最前端
            {
                if (!Mouse_Block_ && In_KeyEvent(VK_LBUTTON) && !防止脱离)//当鼠标指针不在Block上则可以移动窗口
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
                else if (防止脱离 && In_KeyEvent(VK_LBUTTON))
                {
                    MoveWindow(EasyGUI_WindowHWND, EasyGUI_MousePos.x - OldX, EasyGUI_MousePos.y - OldY, EasyGUI_WindowPos.right - EasyGUI_WindowPos.left, EasyGUI_WindowPos.bottom - EasyGUI_WindowPos.top, TRUE);//移动窗口到鼠标坐标
                    Mouse_Block_ = true;
                    if (In_TickSleep<class CLASS_EasyGUI_WindowMove_FPS_Delay_>(100))return false;//定时返回false (用来刷新面板)
                    return true;
                }
                else {
                    防止脱离 = false;
                    保存鼠标坐标 = true;
                    if (In_KeyEvent(VK_LBUTTON))Sleep(1);
                    else Sleep(Draw_ms);//降低CPU占用
                    Mouse_Block_ = false;
                    return false;
                }
            }
            else Sleep(20); return false;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        EasyGUI_IO Get_IO() noexcept//获取GUI数据
        {
            struct EasyGUI_IO IO;
            IO.DrawFPS = EasyGUI_FPS;
            IO.HWND = EasyGUI_WindowHWND;
            IO.HDC = EasyGUI_DrawHDC;
            IO.FontName = Global_EasyGUIFont;
            IO.FontSize = Global_EasyGUIFontSize;
            IO.GUIColor = Global_EasyGUIColor;
            IO.GUIColor_Alpha = Global_EasyGUIColor_Alpha;
            RECT Windowrect; GetWindowRect(EasyGUI_WindowHWND, &Windowrect);
            IO.WindowPos = { Windowrect.left ,Windowrect.top };
            IO.WindowSize = { Windowrect.right - Windowrect.left ,Windowrect.bottom - Windowrect.top };
            CHAR Windowtitle[MAX_PATH] = { 0 }; GetWindowTextA(EasyGUI_WindowHWND, Windowtitle, GetWindowTextLength(EasyGUI_WindowHWND) + 1);
            IO.WindowTitle = Windowtitle;
            IO.MousePos = { EasyGUI_MousePos.x,EasyGUI_MousePos.y };
            IO.GUIColor_Rainbow = {
                 (int)floor(sin((float)GetTickCount64() / 3500 * 2 + 3) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3500 * 2 + 2 + 3) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3500 * 2 + 4 + 3) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3500 * 2 + 2) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3500 * 2 + 2 + 2) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3500 * 2 + 4 + 2) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3500 * 2 + 1) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3500 * 2 + 2 + 1) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3500 * 2 + 4 + 1) * 127 + 128),
            };
            return IO;
        }
        //-------------------------------------------------------------------------------------------------------------------------------------------以下是控件函数*
        void GUI_BackGround(short BackGround_StyleCode = 0, BOOL Particle_Animation = false) noexcept//绘制GUI窗口背景
        {
            const short XX = EasyGUI_WindowPos.right - EasyGUI_WindowPos.left; const short YY = EasyGUI_WindowPos.bottom - EasyGUI_WindowPos.top;
            vector<int> 彩虹条颜色 = { 0,255,255,255,0,255,255,255,0 };
            vector<int> 主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,5,5,5,30,30,30 };
            if (BackGround_StyleCode == 0)//毛都没有
            {
                彩虹条颜色 = { 16,16,16,16,16,16,16,16,16 };
                主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,15,15,15,Global_EasyGUIColor.r / 7,Global_EasyGUIColor.g / 7 ,Global_EasyGUIColor.b / 7 };
            }
            else if (BackGround_StyleCode == 1337)//仿
            {
                彩虹条颜色 = { 100,255,255,255,100,255,255,255,100 };
                主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,5,5,5,Global_EasyGUIColor.r / 7,Global_EasyGUIColor.g / 7 ,Global_EasyGUIColor.b / 7 };
            }
            else if (BackGround_StyleCode == 1367)//仿2
            {
                彩虹条颜色 = { 0,255,255,255,0,255,255,255,0 };
                主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,3,3,3,Global_EasyGUIColor.r / 7,Global_EasyGUIColor.g / 7 ,Global_EasyGUIColor.b / 7 };
            }
            else if (BackGround_StyleCode == 1368)//彩色变色渐变条*****************
            {
                彩虹条颜色 = {
                    (int)floor(sin((float)GetTickCount64() / 3500 * 2 + 3) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / 3500 * 2 + 2 + 3) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / 3500 * 2 + 4 + 3) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / 3500 * 2 + 2) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / 3500 * 2 + 2 + 2) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / 3500 * 2 + 4 + 2) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / 3500 * 2 + 1) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / 3500 * 2 + 2 + 1) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / 3500 * 2 + 4 + 1) * 127 + 128),
                };
                主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,3,3,3, Global_EasyGUIColor.r / 7,Global_EasyGUIColor.g / 7 ,Global_EasyGUIColor.b / 7 };
                Global_EasyGUIColor = { 彩虹条颜色[3],彩虹条颜色[4], 彩虹条颜色[5] };
            }
            else if (BackGround_StyleCode == 1369 || BackGround_StyleCode == 1)//主题色渐变条*****************
            {
                const Vector3 Sins = { sin((float)GetTickCount64() / 1000 + 0), sin((float)GetTickCount64() / 1000 + 1),sin((float)GetTickCount64() / 1000 + 2) };
                彩虹条颜色 = {
                    (int)(Sins.z * Global_EasyGUIColor.r / 2 + Global_EasyGUIColor.r / 2),
                    (int)(Sins.z * Global_EasyGUIColor.g / 2 + Global_EasyGUIColor.g / 2),
                    (int)(Sins.z * Global_EasyGUIColor.b / 2 + Global_EasyGUIColor.b / 2),
                    (int)(Sins.y * Global_EasyGUIColor.r / 2 + Global_EasyGUIColor.r / 2),
                    (int)(Sins.y * Global_EasyGUIColor.g / 2 + Global_EasyGUIColor.g / 2),
                    (int)(Sins.y * Global_EasyGUIColor.b / 2 + Global_EasyGUIColor.b / 2),
                    (int)(Sins.x * Global_EasyGUIColor.r / 2 + Global_EasyGUIColor.r / 2),
                    (int)(Sins.x * Global_EasyGUIColor.g / 2 + Global_EasyGUIColor.g / 2),
                    (int)(Sins.x * Global_EasyGUIColor.b / 2 + Global_EasyGUIColor.b / 2)
                };
                主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,0,0,0,Global_EasyGUIColor.r / 7,Global_EasyGUIColor.g / 7,Global_EasyGUIColor.b / 7 };
            }
            In_DrawRect(0, 0, XX, YY, { 主题颜色[0], 主题颜色[1], 主题颜色[2] });
            In_DrawRect(1, 1, XX - 2, YY - 2, { 主题颜色[3], 主题颜色[4], 主题颜色[5] });
            In_DrawRect(2, 2, XX - 4, YY - 4, { 主题颜色[6], 主题颜色[7], 主题颜色[8] });
            In_DrawRect(5, 5, XX - 10, YY - 10, { 主题颜色[3], 主题颜色[4], 主题颜色[5] });
            In_DrawGradientRect(6, 6, XX - 12, YY - 12, { 主题颜色[12], 主题颜色[13], 主题颜色[14] }, { 主题颜色[15], 主题颜色[16], 主题颜色[17] }, true);//BackGround Gradient
            if (BackGround_StyleCode != 0)//彩虹条
            {
                In_DrawGradientRect(7, 7, (XX - 7 * 2) / 2, 2, { 彩虹条颜色[0] / 2, 彩虹条颜色[1] / 2, 彩虹条颜色[2] / 2 }, { 彩虹条颜色[3] / 2, 彩虹条颜色[4] / 2, 彩虹条颜色[5] / 2 }, false);
                In_DrawGradientRect(7 + (XX - 7 * 2) / 2, 7, (XX - 7 * 2) / 2, 2, { 彩虹条颜色[3] / 2, 彩虹条颜色[4] / 2, 彩虹条颜色[5] / 2 }, { 彩虹条颜色[6] / 2, 彩虹条颜色[7] / 2, 彩虹条颜色[8] / 2 }, false);
                In_DrawGradientRect(7, 7, (XX - 7 * 2) / 2, 1, { 彩虹条颜色[0], 彩虹条颜色[1], 彩虹条颜色[2] }, { 彩虹条颜色[3], 彩虹条颜色[4], 彩虹条颜色[5] }, false);
                In_DrawGradientRect(7 + (XX - 7 * 2) / 2, 7, (XX - 7 * 2) / 2, 1, { 彩虹条颜色[3], 彩虹条颜色[4], 彩虹条颜色[5] }, { 彩虹条颜色[6], 彩虹条颜色[7], 彩虹条颜色[8] }, false);
            }
            if (Particle_Animation)//动画背景背景
            {
                struct c_particle { int c, x, y; };//粒子结构体 { color, x, y }
                for (short i = 0; i <= 40; ++i)
                {
                    srand(i);//随机种子
                    const c_particle Par = { rand() % 200 + 55, rand() % (XX - 14) + 7, rand() % (YY - 17) + 10 };//粒子结构变量
                    const Vector2 MousePos = { EasyGUI_MousePos.x - EasyGUI_WindowPos.left ,EasyGUI_MousePos.y - EasyGUI_WindowPos.top };//窗口内的鼠标坐标
                    if (hypot(MousePos.x - Par.x, MousePos.y - Par.y) <= 300)In_DrawLine(MousePos.x, MousePos.y, Par.x, Par.y, { Global_EasyGUIColor.r / 6,Global_EasyGUIColor.g / 6 ,Global_EasyGUIColor.b / 6 });//绘制粒子连接线
                    In_DrawRect(Par.x, Par.y, 1, 1, { Par.c,Par.c,Par.c });//绘制粒子
                }
            }
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        Vector2 GUI_Block(int X, int Y, int YY, string BlockText, int XX = 400) noexcept//绘制按钮的区块
        {
            In_DrawRect(X, Y, XX, YY, { 0,0,0 });//黑色外边框
            In_DrawRect(X + 1, Y + 1, XX - 2, YY - 2, { 60,60,60 });//白色外边框
            In_DrawGradientRect(X + 2, Y + 2, XX - 4, YY - 4, { 10,10,10 }, Global_EasyGUIColor / 10, true);//渐变背景
            In_DrawString(X + 20 + 1, Y - 7 + 1, BlockText.c_str(), { 50,50,50 }, "Small Fonts", 14, 700);
            In_DrawString(X + 20, Y - 7, BlockText.c_str(), { 200,200,200 }, "Small Fonts", 14, 700);
            if ((EasyGUI_MousePos.x - EasyGUI_WindowPos.left >= X && EasyGUI_MousePos.x - EasyGUI_WindowPos.left <= X + XX && EasyGUI_MousePos.y - EasyGUI_WindowPos.top >= Y && EasyGUI_MousePos.y - EasyGUI_WindowPos.top <= Y + YY) || !(EasyGUI_MousePos.x >= EasyGUI_WindowPos.left && EasyGUI_MousePos.x <= EasyGUI_WindowPos.right && EasyGUI_MousePos.y >= EasyGUI_WindowPos.top && EasyGUI_MousePos.y <= EasyGUI_WindowPos.bottom))Mouse_Block_ = true;
            return { X,Y };
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        int GUI_Block_Panel(int X, int Y, int XX, int YY, string BlockText, vector<string>BlockText_, int& m_In_Block) noexcept//区块_大区块选择器
        {
            if (m_In_Block < 0)m_In_Block = 0; else if (m_In_Block >= BlockText_.size())m_In_Block = BlockText_.size() - 1;//范围限制
            In_DrawRect(X, Y, XX, YY, { 0,0,0 });//黑色外边框
            In_DrawRect(X + 1, Y + 1, XX - 2, YY - 2, { 60,60,60 });//白色外边框
            In_DrawGradientRect(X + 2, Y + 2, XX - 4, YY - 4, Global_EasyGUIColor / 8, { 10,10,10 }, true);//主题色渐变背景
            In_DrawString(X + 15 + 1, Y - 7 + 1, BlockText.c_str(), { 50,50,50 }, "Small Fonts", 14, 700);
            In_DrawString(X + 15, Y - 7, BlockText.c_str(), { 200,200,200 }, "Small Fonts", 14, 700);
            for (short i = 0; i < BlockText_.size(); ++i)//遍历坐标
            {
                const BOOL DetectMousePos = In_MouseEventJudgment(X, Y + 20 + 30 * i - 2 - 4, XX, 15 + 8);
                if (m_In_Block == i)
                {
                    In_DrawGradientRect(X + 2, Y + 20 + 30 * i - 5, XX - 4, 15 + 10, { 20,20,20 }, Global_EasyGUIColor / 4);
                    In_DrawGradientRect(X + 2, Y + 20 + 30 * i - 4, XX - 4, 15 + 8, Global_EasyGUIColor / 4, { 20,20,20 });
                }
                else if (DetectMousePos)
                {
                    In_DrawGradientRect(X + 2, Y + 20 + 30 * i - 4, XX - 4, 15 + 8, Global_EasyGUIColor / 5, { 20,20,20 });
                    if (GetForegroundWindow() == EasyGUI_WindowHWND && In_KeyEvent(VK_LBUTTON, true) && !Mouse_Slider_)m_In_Block = i;
                }
                In_DrawString(X + 20 + 1, Y + 20 + 30 * i + 1, BlockText_[i], { 0,0,0 }, Global_EasyGUIFont, 15);
                In_DrawString(X + 20 + 1, Y + 20 + 30 * i, BlockText_[i], { 220,220,220 }, Global_EasyGUIFont, 15);
            }
            if ((EasyGUI_MousePos.x - EasyGUI_WindowPos.left >= X && EasyGUI_MousePos.x - EasyGUI_WindowPos.left <= X + XX && EasyGUI_MousePos.y - EasyGUI_WindowPos.top >= Y && EasyGUI_MousePos.y - EasyGUI_WindowPos.top <= Y + YY) || !(EasyGUI_MousePos.x >= EasyGUI_WindowPos.left && EasyGUI_MousePos.x <= EasyGUI_WindowPos.right && EasyGUI_MousePos.y >= EasyGUI_WindowPos.top && EasyGUI_MousePos.y <= EasyGUI_WindowPos.bottom))Mouse_Block_ = true;
            return m_In_Block;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        string GUI_Text(Vector2 BlockPos, short LineRow, string Text, Vector4 TextColor = { 200,200,200 }) noexcept//行文字
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return 0;//当无block则不进行绘制
            In_DrawString(BlockPos.x + 22 + 30 + 1, BlockPos.y - 3 + (30 * LineRow) + 1, Text, { 0,0,0 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
            In_DrawString(BlockPos.x + 22 + 30 + 1, BlockPos.y - 3 + (30 * LineRow), Text, TextColor, Global_EasyGUIFont, Global_EasyGUIFontSize);
            return Text;
        }
        //--------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL GUI_Checkbox(Vector2 BlockPos, short LineRow, string Text, BOOL& m_CheckboxValue, Vector4 TextColor = { 200,200,200 }) noexcept//点击框
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return 0;//当无block则不进行绘制
            const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 30, BlockPos.y + (30 * LineRow) - 2, 140, 12);//窗口检测
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_ && DetectMousePos && In_KeyEvent(VK_LBUTTON, true))m_CheckboxValue = !m_CheckboxValue;//当最前端窗口为GUI窗口接收按钮事件
            In_DrawRect(BlockPos.x - 1 + 30, BlockPos.y - 1 + (30 * LineRow), 10, 10, { 0,0,0 });
            In_DrawString(BlockPos.x + 22 + 30 + 1, BlockPos.y - 3 + (30 * LineRow) + 1, Text, { 0,0,0 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
            In_DrawString(BlockPos.x + 22 + 30, BlockPos.y - 3 + (30 * LineRow), Text, TextColor, Global_EasyGUIFont, Global_EasyGUIFontSize);
            if (m_CheckboxValue)In_DrawGradientRect(BlockPos.x - 1 + 30 + 1, BlockPos.y - 1 + (30 * LineRow) + 1, 8, 8, Global_EasyGUIColor, Global_EasyGUIColor / 5, true);//绘制开关状态 (颜色主体)
            else
            {
                if (DetectMousePos)In_DrawGradientRect(BlockPos.x - 1 + 30 + 1, BlockPos.y - 1 + (30 * LineRow) + 1, 8, 8, Global_EasyGUIColor / 3, { 30,30,30 }, true);
                else In_DrawGradientRect(BlockPos.x - 1 + 30 + 1, BlockPos.y - 1 + (30 * LineRow) + 1, 8, 8, Global_EasyGUIColor / 4, { 30,30,30 }, true);
            }
            return m_CheckboxValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL GUI_Button(Vector2 BlockPos, short LineRow, string Text, BOOL& m_ButtonValue, short TextPos = 10) noexcept//单击按钮
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return 0;//当无block则不进行绘制
            if (m_ButtonValue)Sleep(30);//更好地让其他循环线程接收
            const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 55, BlockPos.y + (30 * LineRow) - 8, 230, 25);//窗口检测机制
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_)//当最前端窗口为GUI窗口接收按钮事件
            {
                if (!m_ButtonValue && DetectMousePos && In_KeyEvent(VK_LBUTTON, true))m_ButtonValue = true;
                else m_ButtonValue = false;
            }
            In_DrawRect(BlockPos.x - 2 + 55, BlockPos.y - 2 + (30 * LineRow) - 8, 234, 29, { 0,0,0 });
            In_DrawRect(BlockPos.x - 1 + 55, BlockPos.y - 1 + (30 * LineRow) - 8, 232, 27, { 60,60,60 });
            if (DetectMousePos && !m_ButtonValue)In_DrawGradientRect(BlockPos.x + 55, BlockPos.y + (30 * LineRow) - 8, 230, 25, Global_EasyGUIColor / 5, { 20,20,20 }, true);
            else In_DrawGradientRect(BlockPos.x + 55, BlockPos.y + (30 * LineRow) - 8, 230, 25, Global_EasyGUIColor / 7, { 20,20,20 }, true);
            In_DrawString(BlockPos.x + TextPos + 55 + 1, BlockPos.y + 6 + (30 * LineRow) - 8 + 1, Text, { 0,0,0 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
            In_DrawString(BlockPos.x + TextPos + 55, BlockPos.y + 6 + (30 * LineRow) - 8, Text, { 200,200,200 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
            return m_ButtonValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL GUI_Button_Small(Vector2 BlockPos, short LineRow, BOOL& m_ButtonValue) noexcept//单击按钮(小号)
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return 0;//当无block则不进行绘制
            if (m_ButtonValue)Sleep(30);//更好地让其他循环线程接收
            const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 10, BlockPos.y + (30 * LineRow) - 5, 13, 18);//窗口检测机制
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_)//当最前端窗口为GUI窗口接收按钮事件
            {
                if (!m_ButtonValue && DetectMousePos && In_KeyEvent(VK_LBUTTON, true))m_ButtonValue = true;
                else m_ButtonValue = false;
            }
            In_DrawRect(BlockPos.x - 2 + 10, BlockPos.y - 2 + (30 * LineRow) - 5, 17, 22, { 0,0,0 });
            In_DrawRect(BlockPos.x - 1 + 10, BlockPos.y - 1 + (30 * LineRow) - 5, 15, 20, { 60,60,60 });
            if (DetectMousePos && !m_ButtonValue)In_DrawGradientRect(BlockPos.x + 10, BlockPos.y + (30 * LineRow) - 5, 13, 18, Global_EasyGUIColor / 5, { 20,20,20 }, true);
            else In_DrawGradientRect(BlockPos.x + 10, BlockPos.y + (30 * LineRow) - 5, 13, 18, Global_EasyGUIColor / 7, { 20,20,20 }, true);
            In_DrawString_Simple(BlockPos.x + 10 + 2, BlockPos.y + (30 * LineRow) - 1, "...", { 200,200,200 });
            return m_ButtonValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        template<class ValueClass, class CreateClassName>
        ValueClass GUI_Slider(Vector2 BlockPos, short LineRow, string Text, ValueClass StartValue, ValueClass EndValue, ValueClass& m_SliderValue, string UnitString = "", Vector4 TextColor = { 200,200,200 }) noexcept//滑条
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return 0;//当无block则不进行绘制
            const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 55, BlockPos.y + (6 + 30 * LineRow), 230, 5);//窗口检测
            static BOOL OutSide = false;//防止指针脱落时失去控制力
            if (GetForegroundWindow() == EasyGUI_WindowHWND)//当最前端窗口为GUI窗口接收按钮事件
            {
                static const ValueClass ClassValueDetect = 0.1;//检测是否是浮点值 (变量)
                if (DetectMousePos && In_KeyEvent(VK_LEFT, true))//当鼠标移动到滑条上方 按键反馈事件
                {
                    if (ClassValueDetect == 0)m_SliderValue--;//检测是否是浮点值
                    else m_SliderValue -= 0.05;
                }
                else if (DetectMousePos && In_KeyEvent(VK_RIGHT, true))
                {
                    if (ClassValueDetect == 0)m_SliderValue++;//检测是否是浮点值
                    else m_SliderValue += 0.05;
                }
                if (In_KeyEvent(VK_LBUTTON) && DetectMousePos && !OutSide)OutSide = true;
                if (OutSide && In_KeyEvent(VK_LBUTTON))
                {
                    m_SliderValue = ((EasyGUI_MousePos.x - BlockPos.x - 54 - EasyGUI_WindowPos.left) * (EndValue - StartValue) / 230) + StartValue;
                    Mouse_Block_ = true; Mouse_Slider_ = true;
                }
                else if (!In_KeyEvent(VK_LBUTTON)) { OutSide = false; Mouse_Slider_ = false; }
            }
            int SliderPos = (float)(m_SliderValue - StartValue) / (float)(EndValue - StartValue) * 230;
            if (SliderPos >= 230)SliderPos = 230; else if (SliderPos <= 0) SliderPos = 0;
            if (m_SliderValue <= StartValue)m_SliderValue = StartValue; else if (m_SliderValue >= EndValue)m_SliderValue = EndValue;//范围限制
            stringstream ss; ss << fixed << setprecision(4) << m_SliderValue; ss >> m_SliderValue;//只保留4位小数点后数
            In_DrawRect(BlockPos.x - 1 + 55, BlockPos.y - 1 + (6 + 30 * LineRow), 230 + 2, 7, { 0,0,0 });//黑色外边框
            if (DetectMousePos || OutSide)In_DrawGradientRect(BlockPos.x + 55, BlockPos.y + (6 + 30 * LineRow), 230, 5, { 30,30,30 }, Global_EasyGUIColor / 4, true);//滑条背景
            else In_DrawGradientRect(BlockPos.x + 55, BlockPos.y + (6 + 30 * LineRow), 230, 5, { 20,20,20 }, Global_EasyGUIColor / 5, true);
            In_DrawGradientRect(BlockPos.x + 55, BlockPos.y + (6 + 30 * LineRow), In_Animation<CreateClassName>(SliderPos, 1.5, { 0,230 }), 5, Global_EasyGUIColor, Global_EasyGUIColor / 5, true);//滑条 (动画0.8果冻效果)
            In_DrawString(BlockPos.x + 55 + 1, BlockPos.y - 16 + (6 + 30 * LineRow) + 1, Text, { 0,0,0 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
            In_DrawString(BlockPos.x + 55, BlockPos.y - 16 + (6 + 30 * LineRow), Text, TextColor, Global_EasyGUIFont, Global_EasyGUIFontSize);
            In_DrawString_Simple(BlockPos.x + 230 + 10 + 55, BlockPos.y - 4 + (6 + 30 * LineRow), ss.str() + UnitString, { 150,150,150 });//返回值绘制
            return m_SliderValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        template<class CreateClassName>
        int GUI_KeySelector(Vector2 BlockPos, short LineRow, int& m_KeySelectValue) noexcept//按键选取按钮
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return 0;//当无block则不进行绘制
            if (m_KeySelectValue >= 0xCCCCCCCC)m_KeySelectValue = 0;//修复过量
            const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 350, BlockPos.y + 26 + (30 * (LineRow - 1)), 40, 12);//鼠标坐标检测
            static BOOL BoxMea = false;//只声明一次初始开关设定变量
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_)//当最前端窗口为GUI窗口接收按钮事件
            {
                if (!BoxMea && DetectMousePos && In_KeyEvent(VK_LBUTTON, true))BoxMea = true;
                else if (BoxMea)
                {
                    if (In_KeyEvent(VK_BACK, true) || In_KeyEvent(VK_ESCAPE, true)) { m_KeySelectValue = 0; BoxMea = false; }//默认无值
                    for (int i = 0x0; i < 0xFE; ++i)//VK键码遍历
                    {
                        if (In_KeyEvent(i, true))//当按下任意键
                        {
                            m_KeySelectValue = i;
                            BoxMea = false;
                        }
                    }
                }
            }
            if (!BoxMea)
            {
                string DrawString_VK = "";
                switch (m_KeySelectValue)
                {
                case 0x00: DrawString_VK = "[-]"; break;
                case 0x01: DrawString_VK = "[M1]"; break;//鼠标左键
                case 0x02: DrawString_VK = "[M2]"; break;//鼠标右键
                case 0x03: DrawString_VK = "[CAN]"; break;//鼠标中断处理
                case 0x04: DrawString_VK = "[M3]"; break;//鼠标中键
                case 0x05: DrawString_VK = "[M4]"; break;//鼠标侧键下
                case 0x06: DrawString_VK = "[M5]"; break;//鼠标侧键上
                case 0x07: DrawString_VK = "[NONE]"; break;
                case 0x08: DrawString_VK = "[BACK]"; break;
                case 0x09: DrawString_VK = "[TAB]"; break;
                case 0x0C: DrawString_VK = "[CLE]"; break;
                case 0x0D: DrawString_VK = "[ENT]"; break;
                case 0x10: DrawString_VK = "[SHF]"; break;
                case 0x11: DrawString_VK = "[CLR]"; break;
                case 0x12: DrawString_VK = "[ALT]"; break;
                case 0x13: DrawString_VK = "[PAU]"; break;
                case 0x14: DrawString_VK = "[CAP]"; break;
                case 0x15: DrawString_VK = "[KAN]"; break;
                case 0x16: DrawString_VK = "[KAN]"; break;
                case 0x17: DrawString_VK = "[JUN]"; break;
                case 0x18: DrawString_VK = "[FIN]"; break;
                case 0x19: DrawString_VK = "[HAN]"; break;
                case 0x1B: DrawString_VK = "[ESC]"; break;
                case 0x1C: DrawString_VK = "[CON]"; break;
                case 0x1D: DrawString_VK = "[NON]"; break;
                case 0x1E: DrawString_VK = "[ACC]"; break;
                case 0x1F: DrawString_VK = "[MOD]"; break;
                case 0x20: DrawString_VK = "[SPA]"; break;
                case 0x21: DrawString_VK = "[PRI]"; break;
                case 0x22: DrawString_VK = "[NEXT]"; break;
                case 0x23: DrawString_VK = "[END]"; break;
                case 0x24: DrawString_VK = "[HOME]"; break;
                case 0x25: DrawString_VK = "[LEFT]"; break;
                case 0x26: DrawString_VK = "[UP]"; break;
                case 0x27: DrawString_VK = "[RIGT]"; break;
                case 0x28: DrawString_VK = "[DOWN]"; break;
                case 0x29: DrawString_VK = "[SEL]"; break;
                case 0x2A: DrawString_VK = "[PRI]"; break;
                case 0x2B: DrawString_VK = "[EXE]"; break;
                case 0x2C: DrawString_VK = "[SNAP]"; break;
                case 0x2D: DrawString_VK = "[INS]"; break;
                case 0x2E: DrawString_VK = "[DEL]"; break;
                case 0x2F: DrawString_VK = "[HELP]"; break;
                case 0x30: DrawString_VK = "[0]"; break;
                case 0x31: DrawString_VK = "[1]"; break;
                case 0x32: DrawString_VK = "[2]"; break;
                case 0x33: DrawString_VK = "[3]"; break;
                case 0x34: DrawString_VK = "[4]"; break;
                case 0x35: DrawString_VK = "[5]"; break;
                case 0x36: DrawString_VK = "[6]"; break;
                case 0x37: DrawString_VK = "[7]"; break;
                case 0x38: DrawString_VK = "[8]"; break;
                case 0x39: DrawString_VK = "[9]"; break;
                case 0x41: DrawString_VK = "[A]"; break;
                case 0x42: DrawString_VK = "[B]"; break;
                case 0x43: DrawString_VK = "[C]"; break;
                case 0x44: DrawString_VK = "[D]"; break;
                case 0x45: DrawString_VK = "[E]"; break;
                case 0x46: DrawString_VK = "[F]"; break;
                case 0x47: DrawString_VK = "[G]"; break;
                case 0x48: DrawString_VK = "[H]"; break;
                case 0x49: DrawString_VK = "[I]"; break;
                case 0x4A: DrawString_VK = "[J]"; break;
                case 0x4B: DrawString_VK = "[K]"; break;
                case 0x4C: DrawString_VK = "[L]"; break;
                case 0x4D: DrawString_VK = "[M]"; break;
                case 0x4E: DrawString_VK = "[N]"; break;
                case 0x4F: DrawString_VK = "[O]"; break;
                case 0x50: DrawString_VK = "[P]"; break;
                case 0x51: DrawString_VK = "[Q]"; break;
                case 0x52: DrawString_VK = "[R]"; break;
                case 0x53: DrawString_VK = "[S]"; break;
                case 0x54: DrawString_VK = "[T]"; break;
                case 0x55: DrawString_VK = "[U]"; break;
                case 0x56: DrawString_VK = "[V]"; break;
                case 0x57: DrawString_VK = "[W]"; break;
                case 0x58: DrawString_VK = "[X]"; break;
                case 0x59: DrawString_VK = "[Y]"; break;
                case 0x5A: DrawString_VK = "[Z]"; break;
                case 0x5B: DrawString_VK = "[WIN]"; break;//L
                case 0x5C: DrawString_VK = "[WIN]"; break;//R
                case 0x5D: DrawString_VK = "[APP]"; break;
                case 0x5F: DrawString_VK = "[SLP]"; break;
                case 0x60: DrawString_VK = "[0]"; break;
                case 0x61: DrawString_VK = "[1]"; break;
                case 0x62: DrawString_VK = "[2]"; break;
                case 0x63: DrawString_VK = "[3]"; break;
                case 0x64: DrawString_VK = "[4]"; break;
                case 0x65: DrawString_VK = "[5]"; break;
                case 0x66: DrawString_VK = "[6]"; break;
                case 0x67: DrawString_VK = "[7]"; break;
                case 0x68: DrawString_VK = "[8]"; break;
                case 0x69: DrawString_VK = "[9]"; break;
                case 0x6A: DrawString_VK = "[*]"; break;
                case 0x6B: DrawString_VK = "[+]"; break;
                case 0x6C: DrawString_VK = "[SEP]"; break;
                case 0x6D: DrawString_VK = "[-]"; break;
                case 0x6E: DrawString_VK = "[.]"; break;
                case 0x6F: DrawString_VK = "[/]"; break;
                case 0x70: DrawString_VK = "[F1]"; break;
                case 0x71: DrawString_VK = "[F2]"; break;
                case 0x72: DrawString_VK = "[F3]"; break;
                case 0x73: DrawString_VK = "[F4]"; break;
                case 0x74: DrawString_VK = "[F5]"; break;
                case 0x75: DrawString_VK = "[F6]"; break;
                case 0x76: DrawString_VK = "[F7]"; break;
                case 0x77: DrawString_VK = "[F8]"; break;
                case 0x78: DrawString_VK = "[F9]"; break;
                case 0x79: DrawString_VK = "[F10]"; break;
                case 0x7A: DrawString_VK = "[F11]"; break;
                case 0x7B: DrawString_VK = "[F12]"; break;
                case 0x7C: DrawString_VK = "[F13]"; break;
                case 0x7D: DrawString_VK = "[F14]"; break;
                case 0x7E: DrawString_VK = "[F15]"; break;
                case 0x7F: DrawString_VK = "[F16]"; break;
                case 0x80: DrawString_VK = "[F17]"; break;
                case 0x81: DrawString_VK = "[F18]"; break;
                case 0x82: DrawString_VK = "[F19]"; break;
                case 0x83: DrawString_VK = "[F20]"; break;
                case 0x84: DrawString_VK = "[F21]"; break;
                case 0x85: DrawString_VK = "[F22]"; break;
                case 0x86: DrawString_VK = "[F23]"; break;
                case 0x87: DrawString_VK = "[F24]"; break;
                case 0x90: DrawString_VK = "[NUM]"; break;
                case 0x91: DrawString_VK = "[SCR]"; break;
                case 0xA0: DrawString_VK = "[SHF]"; break;//L
                case 0xA1: DrawString_VK = "[SHF]"; break;//R
                case 0xA2: DrawString_VK = "[CLR]"; break;//L
                case 0xA3: DrawString_VK = "[CLR]"; break;//R
                case 0xA4: DrawString_VK = "[ALT]"; break;//L
                case 0xA5: DrawString_VK = "[ALT]"; break;//R
                case 0xC0: DrawString_VK = "[~]"; break;
                case 0xBC: DrawString_VK = "[,]"; break;
                case 0xBE: DrawString_VK = "[.]"; break;
                case 0xBF: DrawString_VK = "[/]"; break;
                case 0xBA: DrawString_VK = "[;]"; break;
                case 0xDE: DrawString_VK = "[']"; break;
                case 0xDB: DrawString_VK = "[[]"; break;
                case 0xDD: DrawString_VK = "[]]"; break;
                case 0xDC: DrawString_VK = "[\]"; break;
                default: DrawString_VK = "[" + to_string(m_KeySelectValue) + "]"; break;//如果什么都不是直接返回编码
                }
                if (DetectMousePos)In_DrawString_Simple(BlockPos.x + 355, BlockPos.y + 27 + (30 * (LineRow - 1)), DrawString_VK, { 130,130,130 });
                else In_DrawString_Simple(BlockPos.x + 355, BlockPos.y + 27 + (30 * (LineRow - 1)), DrawString_VK, { 100,100,100 });
                return m_KeySelectValue;
            }
            else In_DrawString_Simple(BlockPos.x + 355, BlockPos.y + 27 + (30 * (LineRow - 1)), "[-]", { 150,130,100 });//激活读取
            return 0;//激活读取时返回0
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL GUI_Tips(Vector2 BlockPos, short LineRow, string TipsString, Vector4 TextColor = { 255,255,255 }) noexcept//鼠标指针提示(只支持单行字符)   (代码写在最后为了不被覆盖绘制)
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return 0;//当无block则不进行绘制
            In_DrawString_Simple(BlockPos.x + 8, BlockPos.y + 27 + (30 * (LineRow - 1)), "[?]", { 100,100,100 });//GUI绘制
            if (GetForegroundWindow() == EasyGUI_WindowHWND && In_MouseEventJudgment(BlockPos.x + 8, BlockPos.y + 26 + (30 * (LineRow - 1)), 13, 13) && !Mouse_Slider_)//当鼠标移动到问号 且GUI窗口为最顶层
            {
                In_DrawRect(EasyGUI_MousePos.x - EasyGUI_WindowPos.left + 15, EasyGUI_MousePos.y - EasyGUI_WindowPos.top + 10, strlen(TipsString.c_str()) * 6, 20, { 0,0,0 });
                In_DrawRect(EasyGUI_MousePos.x - EasyGUI_WindowPos.left + 15 + 1, EasyGUI_MousePos.y - EasyGUI_WindowPos.top + 10 + 1, strlen(TipsString.c_str()) * 6 - 2, 20 - 2, { 60,60,60 });
                In_DrawRect(EasyGUI_MousePos.x - EasyGUI_WindowPos.left + 15 + 2, EasyGUI_MousePos.y - EasyGUI_WindowPos.top + 10 + 2, strlen(TipsString.c_str()) * 6 - 4, 20 - 4, { 15,15,15 });
                In_DrawString_Simple(EasyGUI_MousePos.x - EasyGUI_WindowPos.left + 15 + 4, EasyGUI_MousePos.y - EasyGUI_WindowPos.top + 10 + 4, TipsString, TextColor);
                return true;
            }
            else return false;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        Vector4 GUI_ColorSelector(Vector2 BlockPos, short LineRow, Vector4& m_ColorValue) noexcept//颜色选择器
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return { -1,-1,-1 };//当无block则不进行绘制
            if (GetForegroundWindow() == EasyGUI_WindowHWND && In_MouseEventJudgment(BlockPos.x + 360, BlockPos.y - 6 + (30 * LineRow), 20, 20) && In_KeyEvent(VK_LBUTTON, true) && !Mouse_Slider_)//复制选取的颜色值
            {
                const string Color_String_Copy__ = to_string(m_ColorValue.r) + ", " + to_string(m_ColorValue.g) + ", " + to_string(m_ColorValue.b);//要复制的字符串
                OpenClipboard(NULL);//打开剪切板
                EmptyClipboard();//清空剪切板
                const auto hHandle = GlobalAlloc(GMEM_FIXED, strlen(Color_String_Copy__.c_str()) + 1);//分配内存
                strcpy_s((char*)GlobalLock(hHandle), strlen(Color_String_Copy__.c_str()) + 1, Color_String_Copy__.c_str());
                SetClipboardData(CF_TEXT, hHandle);//设置剪切板数据
                GlobalUnlock(hHandle);//解除锁定
                CloseClipboard();//关闭剪切板
                Beep(100, 20);//复制成功提醒
            }
            for (short Color_Bl = 0; Color_Bl <= 2; ++Color_Bl)
            {
                vector<int> UsedColor = { m_ColorValue.r,m_ColorValue.g,m_ColorValue.b };
                const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 218 + 46 * Color_Bl, BlockPos.y - 6 + (30 * LineRow), 41, 20);
                if (GetForegroundWindow() == EasyGUI_WindowHWND && DetectMousePos && !Mouse_Slider_)//当最前端窗口为GUI窗口接收按钮事件 当鼠标移动到滑条上方 按键反馈事件
                {
                    if (In_KeyEvent(VK_LBUTTON, true))UsedColor[Color_Bl]++;
                    else if (In_KeyEvent(VK_RBUTTON, true))UsedColor[Color_Bl]--;
                    if (In_KeyEvent(VK_LEFT, true))UsedColor[Color_Bl] += 5;
                    else if (In_KeyEvent(VK_RIGHT, true))UsedColor[Color_Bl] -= 5;
                }
                if (UsedColor[Color_Bl] >= 255)UsedColor[Color_Bl] = 255;//范围限制
                else if (UsedColor[Color_Bl] <= 0)UsedColor[Color_Bl] = 0;
                m_ColorValue = { UsedColor[0],UsedColor[1],UsedColor[2] };
                In_DrawRect(BlockPos.x + 218 + 46 * Color_Bl, BlockPos.y - 6 + (30 * LineRow), 41, 20, { 0,0,0 });//Color_Block
                if (DetectMousePos)In_DrawGradientRect(BlockPos.x + 218 + 46 * Color_Bl + 1, BlockPos.y - 6 + (30 * LineRow) + 1, 41 - 2, 20 - 2, Global_EasyGUIColor / 4, { 30,30,30 }, true);
                else In_DrawGradientRect(BlockPos.x + 218 + 46 * Color_Bl + 1, BlockPos.y - 6 + (30 * LineRow) + 1, 41 - 2, 20 - 2, Global_EasyGUIColor / 5, { 30,30,30 }, true);
            }
            In_DrawString_Simple(BlockPos.x + 218 + 5, BlockPos.y - 3 + (30 * LineRow) + 1, "R: " + to_string(m_ColorValue.r), { 150,150,150 });
            In_DrawString_Simple(BlockPos.x + 218 + 46 + 5, BlockPos.y - 3 + (30 * LineRow) + 1, "G: " + to_string(m_ColorValue.g), { 150,150,150 });
            In_DrawString_Simple(BlockPos.x + 218 + 46 * 2 + 5, BlockPos.y - 3 + (30 * LineRow) + 1, "B: " + to_string(m_ColorValue.b), { 150,150,150 });
            In_DrawRect(BlockPos.x + 360, BlockPos.y - 6 + (30 * LineRow), 20, 20, { 0,0,0 });//Color
            In_DrawGradientRect(BlockPos.x + 360 + 1, BlockPos.y - 6 + (30 * LineRow) + 1, 20 - 2, 20 - 2, m_ColorValue, m_ColorValue / 4, true);
            return m_ColorValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        Vector4 GUI_ColorSelector_a(Vector2 BlockPos, short LineRow, Vector4& m_ColorValue) noexcept//颜色选择器(包含Alpha 透明度值)
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return { -1,-1,-1,-1 };//当无block则不进行绘制
            if (GetForegroundWindow() == EasyGUI_WindowHWND && In_MouseEventJudgment(BlockPos.x + 360, BlockPos.y - 6 + (30 * LineRow), 20, 20) && In_KeyEvent(VK_LBUTTON, true) && !Mouse_Slider_)//复制选取的颜色值
            {
                const string Color_String_Copy__ = to_string(m_ColorValue.r) + ", " + to_string(m_ColorValue.g) + ", " + to_string(m_ColorValue.b) + ", " + to_string(m_ColorValue.a);//要复制的字符串
                OpenClipboard(NULL);//打开剪切板
                EmptyClipboard();//清空剪切板
                const auto hHandle = GlobalAlloc(GMEM_FIXED, strlen(Color_String_Copy__.c_str()) + 1);//分配内存
                strcpy_s((char*)GlobalLock(hHandle), strlen(Color_String_Copy__.c_str()) + 1, Color_String_Copy__.c_str());
                SetClipboardData(CF_TEXT, hHandle);//设置剪切板数据
                GlobalUnlock(hHandle);//解除锁定
                CloseClipboard();//关闭剪切板
                Beep(100, 20);//复制成功提醒
            }
            for (short Color_Bl = 0; Color_Bl <= 3; ++Color_Bl)
            {
                vector<int> UsedColor = { m_ColorValue.r,m_ColorValue.g,m_ColorValue.b,m_ColorValue.a };
                const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 172 + 46 * Color_Bl, BlockPos.y - 6 + (30 * LineRow), 41, 20);
                if (GetForegroundWindow() == EasyGUI_WindowHWND && DetectMousePos && !Mouse_Slider_)//当最前端窗口为GUI窗口接收按钮事件 当鼠标移动到滑条上方 按键反馈事件
                {
                    if (In_KeyEvent(VK_LBUTTON, true))UsedColor[Color_Bl]++;
                    else if (In_KeyEvent(VK_RBUTTON, true))UsedColor[Color_Bl]--;
                    if (In_KeyEvent(VK_LEFT, true))UsedColor[Color_Bl] += 5;
                    else if (In_KeyEvent(VK_RIGHT, true))UsedColor[Color_Bl] -= 5;
                }
                if (UsedColor[Color_Bl] >= 255)UsedColor[Color_Bl] = 255;//范围限制
                else if (UsedColor[Color_Bl] <= 0)UsedColor[Color_Bl] = 0;
                m_ColorValue = { UsedColor[0],UsedColor[1],UsedColor[2],UsedColor[3] };
                In_DrawRect(BlockPos.x + 172 + 46 * Color_Bl, BlockPos.y - 6 + (30 * LineRow), 41, 20, { 0,0,0 });
                if (DetectMousePos)In_DrawGradientRect(BlockPos.x + 172 + 46 * Color_Bl + 1, BlockPos.y - 6 + (30 * LineRow) + 1, 41 - 2, 20 - 2, Global_EasyGUIColor / 4, { 30,30,30 }, true);
                else In_DrawGradientRect(BlockPos.x + 172 + 46 * Color_Bl + 1, BlockPos.y - 6 + (30 * LineRow) + 1, 41 - 2, 20 - 2, Global_EasyGUIColor / 5, { 30,30,30 }, true);
            }
            In_DrawString_Simple(BlockPos.x + 172 + 5, BlockPos.y - 3 + (30 * LineRow) + 1, "R: " + to_string(m_ColorValue.r), { 150,150,150 });
            In_DrawString_Simple(BlockPos.x + 172 + 46 + 5, BlockPos.y - 3 + (30 * LineRow) + 1, "G: " + to_string(m_ColorValue.g), { 150,150,150 });
            In_DrawString_Simple(BlockPos.x + 172 + 46 * 2 + 5, BlockPos.y - 3 + (30 * LineRow) + 1, "B: " + to_string(m_ColorValue.b), { 150,150,150 });
            In_DrawString_Simple(BlockPos.x + 172 + 46 * 3 + 5, BlockPos.y - 3 + (30 * LineRow) + 1, "A: " + to_string(m_ColorValue.a), { 150,150,150 });
            In_DrawRect(BlockPos.x + 360, BlockPos.y - 6 + (30 * LineRow), 20, 20, { 0,0,0 });
            In_DrawGradientRect(BlockPos.x + 360 + 1, BlockPos.y - 6 + (30 * LineRow) + 1, 20 - 2, 20 - 2, m_ColorValue, m_ColorValue / 4, true);//Color
            return m_ColorValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        Vector3 GUI_PosSelector(Vector2 BlockPos, short LineRow, Vector3& m_PosValue) noexcept//坐标选择器
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return { -1,-1,-1 };//当无block则不进行绘制
            for (short Color_Bl = 0; Color_Bl <= 2; ++Color_Bl)
            {
                vector<float> UsedPos = { m_PosValue.x,m_PosValue.y,m_PosValue.z };
                const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 180 + 70 * Color_Bl, BlockPos.y - 6 + (30 * LineRow), 68, 20);
                if (GetForegroundWindow() == EasyGUI_WindowHWND && DetectMousePos && !Mouse_Slider_)//当最前端窗口为GUI窗口接收按钮事件 当鼠标移动到滑条上方 按键反馈事件
                {
                    if (In_KeyEvent(VK_LBUTTON, true))UsedPos[Color_Bl] += 0.03;
                    else if (In_KeyEvent(VK_RBUTTON, true))UsedPos[Color_Bl] -= 0.03;
                    if (In_KeyEvent(VK_LEFT, true))UsedPos[Color_Bl] += 1;
                    else if (In_KeyEvent(VK_RIGHT, true))UsedPos[Color_Bl] -= 1;
                    if (In_KeyEvent(VK_UP))UsedPos[Color_Bl] += 10;//快速变值
                    else if (In_KeyEvent(VK_DOWN))UsedPos[Color_Bl] -= 10;
                    m_PosValue = { UsedPos[0],UsedPos[1],UsedPos[2] };
                }
                In_DrawRect(BlockPos.x + 180 + 70 * Color_Bl, BlockPos.y - 6 + (30 * LineRow), 70, 20, { 0,0,0 });
                if (DetectMousePos)In_DrawGradientRect(BlockPos.x + 180 + 70 * Color_Bl + 1, BlockPos.y - 6 + (30 * LineRow) + 1, 70 - 2, 20 - 2, Global_EasyGUIColor / 4, { 30,30,30 }, true);
                else In_DrawGradientRect(BlockPos.x + 180 + 70 * Color_Bl + 1, BlockPos.y - 6 + (30 * LineRow) + 1, 70 - 2, 20 - 2, Global_EasyGUIColor / 5, { 30,30,30 }, true);
            }
            stringstream Float_X_; Float_X_ << fixed << setprecision(2) << m_PosValue.x; Float_X_ >> m_PosValue.x;//只保留2位小数点后数
            stringstream Float_Y_; Float_Y_ << fixed << setprecision(2) << m_PosValue.y; Float_Y_ >> m_PosValue.y;
            stringstream Float_Z_; Float_Z_ << fixed << setprecision(2) << m_PosValue.z; Float_Z_ >> m_PosValue.z;
            In_DrawString_Simple(BlockPos.x + 180 + 5, BlockPos.y - 3 + (30 * LineRow) + 1, "X: " + Float_X_.str(), { 150,150,150 });
            In_DrawString_Simple(BlockPos.x + 180 + 70 + 5, BlockPos.y - 3 + (30 * LineRow) + 1, "Y: " + Float_Y_.str(), { 150,150,150 });
            In_DrawString_Simple(BlockPos.x + 180 + 70 * 2 + 5, BlockPos.y - 3 + (30 * LineRow) + 1, "Z: " + Float_Z_.str(), { 150,150,150 });
            return m_PosValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        int GUI_List(Vector2 BlockPos, short StartLineRow, vector<string>LineString, int& m_InLine, short LimitLine = 0) noexcept//选择列表(缩小版 Panel)
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return 0;//当无block则不进行绘制
            if (m_InLine < 0)m_InLine = 0; else if (m_InLine >= LineString.size())m_InLine = LineString.size() - 1;//范围限制
            if (!LimitLine)LimitLine = LineString.size();
            In_DrawRect(BlockPos.x - 1 + 54, BlockPos.y - 2 + (30 * StartLineRow) - 8, 234, LimitLine * 25 + 5, { 0,0,0 });//黑色外边框
            In_DrawGradientRect(BlockPos.x + 54, BlockPos.y - 1 + (30 * StartLineRow) - 8, 232, LimitLine * 25 - 2 + 5, Global_EasyGUIColor / 8, { 10,10,10 }, true);//主题色渐变背景
            for (short i = 0; i < LineString.size(); ++i)
            {
                if (i >= LimitLine)continue;//限制行数
                const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 54, BlockPos.y + StartLineRow * 30 + i * 25 - 5, 232, 20);//光标检测范围
                if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_ && DetectMousePos && In_KeyEvent(VK_LBUTTON, true))m_InLine = i;//赋值选择
                if (m_InLine == i)
                {
                    In_DrawGradientRect(BlockPos.x + 54, BlockPos.y + StartLineRow * 30 + i * 25 - 5, 232, 20, Global_EasyGUIColor / 6, { 15,15,15 });
                    In_DrawString(BlockPos.x + 65 + 1, BlockPos.y + StartLineRow * 30 + i * 25 - 1 + 1, LineString[i], { 0,0,0 }, Global_EasyGUIFont, Global_EasyGUIFontSize, 600);
                    In_DrawString(BlockPos.x + 65, BlockPos.y + StartLineRow * 30 + i * 25 - 1, LineString[i], Global_EasyGUIColor, Global_EasyGUIFont, Global_EasyGUIFontSize, 600);
                }
                else {
                    if (DetectMousePos)In_DrawGradientRect(BlockPos.x + 54, BlockPos.y + StartLineRow * 30 + i * 25 - 5, 232, 20, Global_EasyGUIColor / 7, { 15,15,15 });//当光标选择时视觉反馈 (在上方时)
                    In_DrawString(BlockPos.x + 65 + 1, BlockPos.y + StartLineRow * 30 + i * 25 - 1 + 1, LineString[i], { 0,0,0 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
                    In_DrawString(BlockPos.x + 65, BlockPos.y + StartLineRow * 30 + i * 25 - 1, LineString[i], { 200,200,200 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
                }
            }
            return m_InLine;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        template<class CreateClassName>
        string GUI_InputText(Vector2 BlockPos, short LineRow, string& m_String) noexcept//字符串输入框 (英文数字 不支持UTF-8 最多30个字符)
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return 0;//当无block则不进行绘制
            const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 55, BlockPos.y + (30 * LineRow) - 9, 230, 25);//窗口检测机制
            static BOOL IsInput = false;//判断是否在输入变量
            string DrawString = m_String;//绘制字符串
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_)//当最前端窗口为GUI窗口接收输入框事件
            {
                if (!IsInput && DetectMousePos && In_KeyEvent(VK_LBUTTON, true))IsInput = true;//进入输入状态
                else if (IsInput)//在输入状态时
                {
                    string PressedKey = "";//按键记录变量
                    if (In_KeyEvent(VK_LCONTROL) || In_KeyEvent(VK_RCONTROL))//Ctrl键脚本
                    {
                        if (In_KeyEvent(0x43, true))//Ctrl + C 复制
                        {
                            OpenClipboard(NULL);//打开剪切板
                            EmptyClipboard();//清空剪切板
                            const auto hHandle = GlobalAlloc(GMEM_FIXED, strlen(m_String.c_str()) + 1);//分配内存
                            strcpy_s((char*)GlobalLock(hHandle), strlen(m_String.c_str()) + 1, m_String.c_str());
                            SetClipboardData(CF_TEXT, hHandle);//设置剪切板数据
                            GlobalUnlock(hHandle);//解除锁定
                            CloseClipboard();//关闭剪切板
                            Beep(100, 20);//复制成功提醒
                        }
                        if (In_KeyEvent(0x56, true))//Ctrl + V 粘贴
                        {
                            OpenClipboard(NULL);//打开剪贴板
                            if (IsClipboardFormatAvailable(CF_TEXT))
                            {
                                const auto h = GetClipboardData(CF_TEXT);//获取剪切板数据
                                m_String += ((char*)GlobalLock(h));//在尾部粘贴字符串内容
                                GlobalUnlock(h);//解除锁定
                            }
                            CloseClipboard();//关闭剪贴板
                            Beep(100, 20);//粘贴成功提醒
                        }
                    }
                    for (int i = 0x8; i < 0xFE; ++i)//VK键码遍历 (检测按下了什么键)
                    {
                        if (In_KeyEvent(VK_LCONTROL) || In_KeyEvent(VK_RCONTROL))continue;//不阻止Ctrl脚本事件
                        if (In_KeyEvent(i, true))
                        {
                            switch (i)//相比if函数执行更快
                            {
                            case 0x20:PressedKey = " "; break;
                            case 0x30:PressedKey = "0"; break;
                            case 0x31:PressedKey = "1"; break;
                            case 0x32:PressedKey = "2"; break;
                            case 0x33:PressedKey = "3"; break;
                            case 0x34:PressedKey = "4"; break;
                            case 0x35:PressedKey = "5"; break;
                            case 0x36:PressedKey = "6"; break;
                            case 0x37:PressedKey = "7"; break;
                            case 0x38:PressedKey = "8"; break;
                            case 0x39:PressedKey = "9"; break;
                            case 0x41:PressedKey = "a"; break;
                            case 0x42:PressedKey = "b"; break;
                            case 0x43:PressedKey = "c"; break;
                            case 0x44:PressedKey = "d"; break;
                            case 0x45:PressedKey = "e"; break;
                            case 0x46:PressedKey = "f"; break;
                            case 0x47:PressedKey = "g"; break;
                            case 0x48:PressedKey = "h"; break;
                            case 0x49:PressedKey = "i"; break;
                            case 0x4A:PressedKey = "j"; break;
                            case 0x4B:PressedKey = "k"; break;
                            case 0x4C:PressedKey = "l"; break;
                            case 0x4D:PressedKey = "m"; break;
                            case 0x4E:PressedKey = "n"; break;
                            case 0x4F:PressedKey = "o"; break;
                            case 0x50:PressedKey = "p"; break;
                            case 0x51:PressedKey = "q"; break;
                            case 0x52:PressedKey = "r"; break;
                            case 0x53:PressedKey = "s"; break;
                            case 0x54:PressedKey = "t"; break;
                            case 0x55:PressedKey = "u"; break;
                            case 0x56:PressedKey = "v"; break;
                            case 0x57:PressedKey = "w"; break;
                            case 0x58:PressedKey = "x"; break;
                            case 0x59:PressedKey = "y"; break;
                            case 0x5A:PressedKey = "z"; break;
                            case 0xBE:PressedKey = "."; break;
                            case 0xBF:PressedKey = "/"; break;
                            case 0x60:PressedKey = "0"; break;//以下小键盘按键**
                            case 0x61:PressedKey = "1"; break;
                            case 0x62:PressedKey = "2"; break;
                            case 0x63:PressedKey = "3"; break;
                            case 0x64:PressedKey = "4"; break;
                            case 0x65:PressedKey = "5"; break;
                            case 0x66:PressedKey = "6"; break;
                            case 0x67:PressedKey = "7"; break;
                            case 0x68:PressedKey = "8"; break;
                            case 0x69:PressedKey = "9"; break;
                            case 0x6A:PressedKey = "*"; break;
                            case 0x6B:PressedKey = "+"; break;
                            case 0x6D:PressedKey = "-"; break;
                            case 0x6E:PressedKey = "."; break;
                            case 0x6F:PressedKey = "/"; break;//以上小键盘按键**
                                //===================================================
                            case VK_BACK:if (m_String.size() > 0)m_String.erase(m_String.end() - 1); break;//擦除最后一个字符
                            case VK_DELETE:m_String = ""; break;//清除全部字符
                            case VK_ESCAPE:case VK_RETURN:IsInput = false; break;//按键解除输入状态
                            }
                            if (GetKeyState(0x14))transform(PressedKey.begin(), PressedKey.end(), PressedKey.begin(), toupper);//转换大写 (仅限CAPSLOCK)
                            m_String += PressedKey;//返回按下
                        }
                    }
                    m_String = m_String.substr(0, 30);//防止过量 (防止绘制在非绘制区域)
                    DrawString += "_";//输入中 绘制标识
                    if (!DetectMousePos && (In_KeyEvent(VK_LBUTTON) || In_KeyEvent(VK_RBUTTON)))IsInput = false;//鼠标解除输入状态
                }
            }
            In_DrawRect(BlockPos.x + 53, BlockPos.y - 2 + (30 * LineRow) - 7, 234, 27, { 0,0,0 });
            In_DrawRect(BlockPos.x + 54, BlockPos.y - 1 + (30 * LineRow) - 7, 232, 25, { 60,60,60 });
            if (DetectMousePos || IsInput)In_DrawGradientRect(BlockPos.x + 55, BlockPos.y + (30 * LineRow) - 7, 230, 23, { 15,15,15 }, Global_EasyGUIColor / 6, true);
            else In_DrawGradientRect(BlockPos.x + 55, BlockPos.y + (30 * LineRow) - 7, 230, 23, { 15,15,15 }, Global_EasyGUIColor / 8, true);
            In_DrawString(BlockPos.x + 55 + 8 + 1, BlockPos.y + 6 + (30 * LineRow) - 8 + 1, DrawString, { 0,0,0 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
            In_DrawString(BlockPos.x + 55 + 8, BlockPos.y + 6 + (30 * LineRow) - 8, DrawString, { 200,200,200 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
            return m_String;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
    };
}