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
namespace EasyGUI//控件
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
            EasyGUI::EasyGUI_IO GUI_IO = GUI_Variable.Global_GetIO();//Get Global Input/Output Value
            if (!GUI_Variable.Window_Move())//MoveWindow Funtion
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
                    GUI_Variable.Global_SetMainColor(UI_ColorSelector);
                    GUI_Variable.GUI_Text(Block, 8, "Pos selector");
                    GUI_Variable.GUI_PosSelector(Block, 8, UI_PosSelector);
                    GUI_Variable.GUI_Button_Small(Block, 2, UI_Button_Small);
                    GUI_Variable.GUI_Text(Block, 9, "FPS: " + to_string(GUI_IO.DrawFPS));
                    GUI_Variable.GUI_Tip(Block, 1, "Some tips");
                }
                else if (UI_PanelSelector == 1)//Panel 2 Screen
                {
                    const auto Block = GUI_Variable.GUI_Block(160, 30, 300, "Block");//Block
                    GUI_Variable.GUI_InputText<class CALSS_EasyGUI_4>(Block, 1, UI_InputText);
                    GUI_Variable.GUI_List<class CALSS_EasyGUI_5>(Block, 2, { "Hello","C++","Java","CS","Windows" }, UI_List);
                }
                GUI_Variable.Draw_GUI(UI_InvertScreenColor);
            }
        }
    }
    */
    struct Vector2//用来储存坐标数据 XY
    {
        Vector2(const int x = 0, const int y = 0) noexcept :x(x), y(y) {} int x, y;
        BOOL operator==(Vector2 other) const noexcept { return x == other.x && y == other.y; }
        BOOL operator!=(Vector2 other) const noexcept { return x != other.x || y != other.y; }
        Vector2 operator+(Vector2 other) const noexcept { return Vector2{ x + other.x, y + other.y }; }
        Vector2 operator-(Vector2 other) const noexcept { return Vector2{ x - other.x, y - other.y }; }
        Vector2 operator+=(Vector2 other) noexcept { x += other.x, y += other.y; return *this; }
        Vector2 operator-=(Vector2 other) noexcept { x -= other.x, y -= other.y; return *this; }
        Vector2 operator*(int other) const noexcept { return Vector2{ x * other, y * other }; }
        Vector2 operator/(int other) const noexcept { return Vector2{ x / other, y / other }; }
        Vector2 operator*(float other) const noexcept { return Vector2{ (int)(x * other), (int)(y * other) }; }
        Vector2 operator/(float other) const noexcept { return Vector2{ (int)(x / other), (int)(y / other) }; }
        Vector2 operator*(double other) const noexcept { return Vector2{ (int)(x * other), (int)(y * other) }; }
        Vector2 operator/(double other) const noexcept { return Vector2{ (int)(x / other), (int)(y / other) }; }
        BOOL IsZero() const noexcept { return x == 0 && y == 0; }//判断是否为0
        template<class CreateClassName> Vector2 Animation(float speed = 10) const noexcept//Vector2坐标动画
        {
            if (speed == 1)return *this; static auto ReturnValue = *this;//无动画时直接返回
            if (x > ReturnValue.x)ReturnValue.x += (x - ReturnValue.x) / speed + 1; else if (x < ReturnValue.x)ReturnValue.x -= (ReturnValue.x - x) / speed + 1;
            if (y > ReturnValue.y)ReturnValue.y += (y - ReturnValue.y) / speed + 1; else if (y < ReturnValue.y)ReturnValue.y -= (ReturnValue.y - y) / speed + 1;
            return ReturnValue;
        }
    };
    struct Vector3//用来储存坐标数据 XYZ
    {
        Vector3(const float x = 0, const float y = 0, const float z = 0) noexcept :x(x), y(y), z(z) {} float x, y, z;
        BOOL operator==(Vector3 other) const noexcept { return x == other.x && y == other.y && z == other.z; }
        BOOL operator!=(Vector3 other) const noexcept { return x != other.x || y != other.y || z != other.z; }
        Vector3 operator+(Vector3 other) const noexcept { return Vector3{ x + other.x, y + other.y, z + other.z }; }
        Vector3 operator-(Vector3 other) const noexcept { return Vector3{ x - other.x, y - other.y, z - other.z }; }
        Vector3 operator+=(Vector3 other) noexcept { x += other.x, y += other.y, z += other.z; return *this; }
        Vector3 operator-=(Vector3 other) noexcept { x -= other.x, y -= other.y, z -= other.z; return *this; }
        Vector3 operator*(int other) const noexcept { return Vector3{ x * other, y * other, z * other }; }
        Vector3 operator/(int other) const noexcept { return Vector3{ x / other, y / other, z / other }; }
        Vector3 operator*(float other) const noexcept { return Vector3{ x * other, y * other, z * other }; }
        Vector3 operator/(float other) const noexcept { return Vector3{ x / other, y / other, z / other }; }
        Vector3 operator*(double other) const noexcept { return Vector3{ (float)(x * other), (float)(y * other), (float)(z * other) }; }
        Vector3 operator/(double other) const noexcept { return Vector3{ (float)(x / other), (float)(y / other), (float)(z / other) }; }
        BOOL IsZero() const noexcept { return x == 0 && y == 0 && z == 0; }//判断是否为0
        Vector3 ToAngle() const noexcept { return Vector3{ atan2(-z, hypot(x, y)) * (180 / (float)acos(-1)),atan2(y, x) * (180 / (float)acos(-1)) }; }
        Vector3 Normalize() const noexcept { const auto len = sqrt(x * x + y * y + z * z); if (!len)return {}; return { x / len, y / len, z / len }; }//归一化向量
        template<class CreateClassName> Vector3 Animation(float speed = 10) const noexcept//Vector3坐标动画
        {
            if (speed == 1)return *this; static auto ReturnValue = *this;//无动画时直接返回
            if (x > ReturnValue.x)ReturnValue.x += (x - ReturnValue.x) / speed + 0.1; else if (x < ReturnValue.x)ReturnValue.x -= (ReturnValue.x - x) / speed + 0.1;
            if (y > ReturnValue.y)ReturnValue.y += (y - ReturnValue.y) / speed + 0.1; else if (y < ReturnValue.y)ReturnValue.y -= (ReturnValue.y - y) / speed + 0.1;
            if (z > ReturnValue.z)ReturnValue.z += (z - ReturnValue.z) / speed + 0.1; else if (z < ReturnValue.z)ReturnValue.z -= (ReturnValue.z - z) / speed + 0.1;
            return ReturnValue;
        }
    };
    struct Vector4//用来储存颜色数据 RGBA
    {
        Vector4(const int r = 0, const int g = 0, const int b = 0, const int a = 255) noexcept :r(r), g(g), b(b), a(a) {} int r, g, b, a = 255;
        BOOL operator==(Vector4 other) const noexcept { return r == other.r && g == other.g && b == other.b && a == other.a; }
        BOOL operator!=(Vector4 other) const noexcept { return r != other.r || g != other.g || b != other.b || a != other.a; }
        Vector4 operator+(Vector4 other) const noexcept { return Vector4{ r + other.r, g + other.g, b + other.b, a }; }
        Vector4 operator-(Vector4 other) const noexcept { return Vector4{ r - other.r, g - other.g, b - other.b, a }; }
        Vector4 operator*(int other) const noexcept { return Vector4{ r * other, g * other, b * other, a }; }
        Vector4 operator/(int other) const noexcept { return Vector4{ r / other, g / other, b / other, a }; }
        Vector4 operator*(float other) const noexcept { return Vector4{ (int)(r * other), (int)(g * other), (int)(b * other), a }; }
        Vector4 operator/(float other) const noexcept { return Vector4{ (int)(r / other), (int)(g / other), (int)(b / other), a }; }
        Vector4 operator*(double other) const noexcept { return Vector4{ (int)(r * other), (int)(g * other), (int)(b * other), a }; }
        Vector4 operator/(double other) const noexcept { return Vector4{ (int)(r / other), (int)(g / other), (int)(b / other), a }; }
        BOOL IsZero() const noexcept { return r == 0 && g == 0 && b == 0; }//判断是否为0
        Vector4 D_Alpha(int alpha, int limit = 0) const noexcept { if (alpha <= limit)return { r,g,b,limit }; else return { r,g,b,alpha }; }//原有基础上设置特定透明度
        Vector4 Re_Col() const noexcept//限制颜色值过量 (0~255)
        {
            auto Color_Var = *this;
            if (Color_Var.r < 0)Color_Var.r = 0; else if (Color_Var.r > 255)Color_Var.r = 255;
            if (Color_Var.g < 0)Color_Var.g = 0; else if (Color_Var.g > 255)Color_Var.g = 255;
            if (Color_Var.b < 0)Color_Var.b = 0; else if (Color_Var.b > 255)Color_Var.b = 255;
            if (Color_Var.a < 0)Color_Var.a = 0; else if (Color_Var.a > 255)Color_Var.a = 255;
            return Color_Var;
        }
        Vector4 Min_Bri(int bright = 0) const noexcept//最小亮度
        {
            auto Color_Var = *this;
            if (Color_Var.r < bright)Color_Var.r = bright;
            if (Color_Var.g < bright)Color_Var.g = bright;
            if (Color_Var.b < bright)Color_Var.b = bright;
            return Color_Var;
        }
        Vector4 Max_Bri(int bright = 0) const noexcept//最大亮度
        {
            auto Color_Var = *this;
            if (Color_Var.r > bright)Color_Var.r = bright;
            if (Color_Var.g > bright)Color_Var.g = bright;
            if (Color_Var.b > bright)Color_Var.b = bright;
            return Color_Var;
        }
        Vector4 Sat(float saturation = 1, float grey = 0, float brightness = 1) const noexcept//色调设置
        {
            float rNorm = r / 255.f, gNorm = g / 255.f, bNorm = b / 255.f, max_val = max(rNorm, max(gNorm, bNorm)), min_val = min(rNorm, min(gNorm, bNorm)), delta = max_val - min_val, h = 0, s = 0, v = max_val + grey; if (v > 1)v = 1;
            if (delta == 0)h = 0; else if (max_val == rNorm) h = 60 * (((gNorm - bNorm) / delta) + (gNorm < bNorm ? 6 : 0));
            else if (max_val == gNorm)h = 60 * (((bNorm - rNorm) / delta) + 2); else h = 60 * (((rNorm - gNorm) / delta) + 4);
            s = (max_val == 0) ? 0 : (delta / max_val); s *= saturation / 1; if (s < 0)s = 0; else if (s > 1)s = 1;
            int i = static_cast<int>(h / 60) % 6;
            float f = h / 60 - i, p = v * (1 - s), q = v * (1 - f * s), t = v * (1 - (1 - f) * s), newR = 0, newG = 0, newB = 0;
            switch (i)
            {
            case 0: newR = v; newG = t; newB = p; break;
            case 1: newR = q; newG = v; newB = p; break;
            case 2: newR = p; newG = v; newB = t; break;
            case 3: newR = p; newG = q; newB = v; break;
            case 4: newR = t; newG = p; newB = v; break;
            case 5: newR = v; newG = p; newB = q; break;
            }
            return Vector4{ (int)(newR * 255 * brightness) ,(int)(newG * 255 * brightness) ,(int)(newB * 255 * brightness) };
        }
        template<class CreateClassName> Vector4 Animation(float Speed = 10) const noexcept//Vector4颜色动画
        {
            if (Speed <= 1)return *this; static auto ReturnValue = *this;//无动画时直接返回
            if (r > ReturnValue.r)ReturnValue.r += (r - ReturnValue.r) / Speed + 1; else if (r < ReturnValue.r)ReturnValue.r -= (ReturnValue.r - r) / Speed + 1;
            if (g > ReturnValue.g)ReturnValue.g += (g - ReturnValue.g) / Speed + 1; else if (g < ReturnValue.g)ReturnValue.g -= (ReturnValue.g - g) / Speed + 1;
            if (b > ReturnValue.b)ReturnValue.b += (b - ReturnValue.b) / Speed + 1; else if (b < ReturnValue.b)ReturnValue.b -= (ReturnValue.b - b) / Speed + 1;
            if (a > ReturnValue.a)ReturnValue.a += (a - ReturnValue.a) / Speed + 1; else if (a < ReturnValue.a)ReturnValue.a -= (ReturnValue.a - a) / Speed + 1;
            return ReturnValue;
        }
    };
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
    auto Mouse_Icon = IDC_ARROW;//鼠标图标变量 (修改图标时更改该变量即可)
    LRESULT CALLBACK EasyGUI_WndProc(HWND Hwnd, UINT Message, WPARAM wParam, LPARAM lParam) noexcept//消息循环(用于解决窗口未响应问题 接收窗口消息)
    {
        switch (Message)
        {
        case WM_ERASEBKGND:return true; break;
        case WM_PAINT:return true; break;//一直重绘
        case WM_CLOSE:exit(0); break;//接收到关闭窗口事件时返回全部线程
        case WM_MOUSEWHEEL://鼠标滚轮事件
        {
            const auto Delta = GET_WHEEL_DELTA_WPARAM(wParam);
            if (Delta > 0)keybd_event(VK_UP, 0, 0, 0); else if (Delta < 0)keybd_event(VK_DOWN, 0, 0, 0);
            return true;
        } break;
        case WM_SETCURSOR: { SetCursor(LoadCursorW(0, Mouse_Icon)); Mouse_Icon = IDC_ARROW; return true; } break;//鼠标图标事件
        }
        return DefWindowProc(Hwnd, Message, wParam, lParam);//定义回调函数的返回值
    }
    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    class EasyGUI
    {
    private:
        //-----------菜单风格
        string Global_EasyGUI_Font = "Verdana";//全局字体名称
        int Global_EasyGUI_FontSize = 13;//全局字体大小
        Vector4 Global_EasyGUI_Color = { 255,255,255,250 };//全局主题颜色 (包含窗口透明度)
        //------------------
        HWND EasyGUI_WindowHWND = 0;//EasyGUI窗口HWND
        HDC EasyGUI_WindowHDC = 0;//EasyGUI窗口HDC
        Vector2 PaintSize = { 0,0 };//EasyGUI双缓冲画布大小
        HDC EasyGUI_DrawHDC = 0;//EasyGUI要绘制的HDC
        POINT EasyGUI_MousePos; RECT EasyGUI_WindowPos;//EasyGUI窗口鼠标坐标
        int EasyGUI_FPS = 0;//EasyGUI绘制帧数 (需要后期计算得出)
        float EasyGUI_ColorSat = 0.5, EasyGUI_ColorGrey = 0.04, EasyGUI_ColorBrig = 1;//EasyGUI主题色调
        int EasyGUI_ClickSound = 0;//EasyGUI点击音效音调
        //------------------
        BOOL Mouse_Block_, Mouse_Slider_, Mouse_Move_ = false;//防止控件函数之间冲突的判断变量
        //------------------
    public:
        //---------------------------------------------------------------------开发者函数 (方便制作GUI)
        void In_DrawRect(int X, int Y, int Width, int Length, Vector4 Color) noexcept//绘制矩形
        {
            Color = Color.Sat(EasyGUI_ColorSat, EasyGUI_ColorGrey, EasyGUI_ColorBrig);
            TRIVERTEX vert[2]; GRADIENT_RECT gRect;
            vert[0].Alpha = 0x0000, vert[1].Alpha = 0x0000;
            gRect.UpperLeft = 0; gRect.LowerRight = 1;
            const auto Color_ = RGB(Color.r, Color.g, Color.b);
            vert[0].x = X; vert[0].y = Y; vert[1].x = X + Width; vert[1].y = Y + Length;
            vert[0].Red = GetRValue(Color_) << 8; vert[0].Green = GetGValue(Color_) << 8; vert[0].Blue = GetBValue(Color_) << 8;
            vert[1].Red = GetRValue(Color_) << 8; vert[1].Green = GetGValue(Color_) << 8; vert[1].Blue = GetBValue(Color_) << 8;
            GradientFill(EasyGUI_DrawHDC, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_V);
        }
        //---------------------------------------------------------------------
        void In_DrawGradientRect(int X, int Y, int Width, int Length, Vector4 Color_1, Vector4 Color_2, BOOL Gradient_Direction = false) noexcept//绘制渐变矩形
        {
            Color_1 = Color_1.Sat(EasyGUI_ColorSat, EasyGUI_ColorGrey, EasyGUI_ColorBrig); Color_2 = Color_2.Sat(EasyGUI_ColorSat, EasyGUI_ColorGrey, EasyGUI_ColorBrig);
            TRIVERTEX vert[2]; GRADIENT_RECT gRect;
            vert[0].Alpha = 0x0000, vert[1].Alpha = 0x0000;
            gRect.UpperLeft = 0; gRect.LowerRight = 1;
            const auto Color1 = RGB(Color_1.r, Color_1.g, Color_1.b);
            const auto Color2 = RGB(Color_2.r, Color_2.g, Color_2.b);
            vert[0].x = X; vert[0].y = Y; vert[1].x = X + Width; vert[1].y = Y + Length;
            vert[0].Red = GetRValue(Color1) << 8; vert[0].Green = GetGValue(Color1) << 8; vert[0].Blue = GetBValue(Color1) << 8;
            vert[1].Red = GetRValue(Color2) << 8; vert[1].Green = GetGValue(Color2) << 8; vert[1].Blue = GetBValue(Color2) << 8;
            if (Gradient_Direction)GradientFill(EasyGUI_DrawHDC, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_V);//渐变方向 (false:横向 true:竖向)
            else GradientFill(EasyGUI_DrawHDC, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_H);
        }
        //---------------------------------------------------------------------
        void In_DrawTriangle(vector<int> Pos_Point, Vector4 Color) noexcept//绘制三角形
        {
            Color = Color.Sat(EasyGUI_ColorSat, EasyGUI_ColorGrey, EasyGUI_ColorBrig);
            TRIVERTEX vert[3]; GRADIENT_TRIANGLE gTRi;
            gTRi.Vertex1 = 0, gTRi.Vertex2 = 1, gTRi.Vertex3 = 2;
            const auto Color_ = RGB(Color.r, Color.g, Color.b);
            vert[0].x = Pos_Point[0]; vert[0].y = Pos_Point[1];
            vert[1].x = Pos_Point[2]; vert[1].y = Pos_Point[3];
            vert[2].x = Pos_Point[4]; vert[2].y = Pos_Point[5];
            vert[0].Red = GetRValue(Color_) << 8; vert[0].Green = GetGValue(Color_) << 8; vert[0].Blue = GetBValue(Color_) << 8; vert[0].Alpha = 0x0000;
            vert[1].Red = GetRValue(Color_) << 8; vert[1].Green = GetGValue(Color_) << 8; vert[1].Blue = GetBValue(Color_) << 8; vert[1].Alpha = 0x0000;
            vert[2].Red = GetRValue(Color_) << 8; vert[2].Green = GetGValue(Color_) << 8; vert[2].Blue = GetBValue(Color_) << 8; vert[2].Alpha = 0x0000;
            GradientFill(EasyGUI_DrawHDC, vert, 3, &gTRi, 1, GRADIENT_FILL_TRIANGLE);
        }
        //---------------------------------------------------------------------
        void In_DrawArrow(int X, int Y, int Width, int Length, Vector4 Color, BOOL UpDown = true) noexcept//绘制箭头
        {
            Color = Color.Sat(EasyGUI_ColorSat, EasyGUI_ColorGrey, EasyGUI_ColorBrig);
            TRIVERTEX vert[3]; GRADIENT_TRIANGLE gTRi;
            gTRi.Vertex1 = 0, gTRi.Vertex2 = 1, gTRi.Vertex3 = 2;
            const auto Color_1 = RGB(Color.r, Color.g, Color.b);
            const auto Color_2 = RGB(Color.r / 2, Color.g / 2, Color.b / 2);
            if (UpDown)//向上箭头
            {
                vert[0].x = X + Width / 2; vert[0].y = Y;
                vert[1].x = X; vert[1].y = Y + Length;
                vert[2].x = X + Width; vert[2].y = Y + Length;
            }
            else {//向下箭头
                vert[0].x = X + Width / 2; vert[0].y = Y + Length;
                vert[1].x = X + Width; vert[1].y = Y;
                vert[2].x = X; vert[2].y = Y;
            }
            vert[0].Red = GetRValue(Color_1) << 8; vert[0].Green = GetGValue(Color_1) << 8; vert[0].Blue = GetBValue(Color_1) << 8; vert[0].Alpha = 0x0000;
            vert[1].Red = GetRValue(Color_2) << 8; vert[1].Green = GetGValue(Color_2) << 8; vert[1].Blue = GetBValue(Color_2) << 8; vert[1].Alpha = 0x0000;
            vert[2].Red = GetRValue(Color_2) << 8; vert[2].Green = GetGValue(Color_2) << 8; vert[2].Blue = GetBValue(Color_2) << 8; vert[2].Alpha = 0x0000;
            GradientFill(EasyGUI_DrawHDC, vert, 3, &gTRi, 1, GRADIENT_FILL_TRIANGLE);
        }
        //---------------------------------------------------------------------
        void In_DrawLine(int X, int Y, int Way_X, int Way_Y, Vector4 Color, int Line_Thickness = 1) noexcept//绘制直线
        {
            Color = Color.Sat(EasyGUI_ColorSat, EasyGUI_ColorGrey, EasyGUI_ColorBrig); const auto LineColor = SelectObject(EasyGUI_DrawHDC, CreatePen(0, Line_Thickness, RGB(Color.r, Color.g, Color.b)));
            MoveToEx(EasyGUI_DrawHDC, X, Y, 0); LineTo(EasyGUI_DrawHDC, Way_X, Way_Y); DeleteObject(LineColor);
        }
        //---------------------------------------------------------------------
        void In_DrawCircle(int X, int Y, int Size, Vector4 Color) noexcept//绘制圆形
        {
            Color = Color.Sat(EasyGUI_ColorSat, EasyGUI_ColorGrey, EasyGUI_ColorBrig);
            const auto OutSide = SelectObject(EasyGUI_DrawHDC, CreatePen(PS_SOLID, 1, RGB(Color.r, Color.g, Color.b)));
            const auto InSide = SelectObject(EasyGUI_DrawHDC, CreateSolidBrush(RGB(Color.r, Color.g, Color.b)));
            Ellipse(EasyGUI_DrawHDC, X - Size / 2, Y - Size / 2, X + Size / 2, Y + Size / 2);
            DeleteObject(OutSide); DeleteObject(InSide);
        }
        //---------------------------------------------------------------------
        int In_DrawString(int X, int Y, string String, Vector4 Color, string Fount_Name, short Fount_Size, short Font_Width = FW_NORMAL) noexcept//绘制文字
        {
            Color = Color.Sat(EasyGUI_ColorSat, EasyGUI_ColorGrey, EasyGUI_ColorBrig); if (String == "" || Fount_Size == 0)return 0; String = String.substr(0, 100);
            BOOL Transform = true; if (String.find("UTT") != string::npos) { String.erase(String.find("UTT"), 3); Transform = false; }//转换UTF-8
            const auto FontPen = SelectObject(EasyGUI_DrawHDC, CreateFontA(Fount_Size, 0, 0, 0, Font_Width, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, Fount_Name.c_str()));
            SIZE TextSize; GetTextExtentPoint32A(EasyGUI_DrawHDC, String.c_str(), strlen(String.c_str()), &TextSize); if (X >= 10000)X -= 10000 + TextSize.cx / 2; if (Y >= 10000)Y -= 10000 + TextSize.cy / 2; if (!X && !Y) { DeleteObject(FontPen); return TextSize.cx; }//坐标大于10000时采用居中坐标
            SetTextColor(EasyGUI_DrawHDC, RGB(Color.r, Color.g, Color.b));//文字颜色
            SetBkMode(EasyGUI_DrawHDC, TRANSPARENT);//背景透明
            if (Transform)//转换UTF-8
            {
                const auto len = MultiByteToWideChar(CP_UTF8, 0, String.c_str(), -1, 0, 0);//转码 UTF-8 (为了显示中文)
                wchar_t* wide_text = new wchar_t[len]; MultiByteToWideChar(CP_UTF8, 0, String.c_str(), -1, wide_text, len);
                TextOutW(EasyGUI_DrawHDC, X, Y, wide_text, len - 1); delete[] wide_text;
            }
            else TextOutA(EasyGUI_DrawHDC, X, Y, String.c_str(), strlen(String.c_str()));//不转换UTF-8直接绘制
            DeleteObject(FontPen);
            return TextSize.cx;
        }
        //---------------------------------------------------------------------
        int In_DrawString_Simple(int X, int Y, string String, Vector4 Color_1 = { 255,255,255 }, Vector4 Color_2 = { 0,0,0 }, short Font_Width = FW_NORMAL) noexcept//绘制简单文字
        {
            Color_1 = Color_1.Sat(EasyGUI_ColorSat, EasyGUI_ColorGrey, EasyGUI_ColorBrig), Color_2 = Color_2.Sat(EasyGUI_ColorSat, EasyGUI_ColorGrey, EasyGUI_ColorBrig); if (String == "")return 0; String = String.substr(0, 100);
            const auto FontPen = SelectObject(EasyGUI_DrawHDC, CreateFontA(12, 0, 0, 0, Font_Width, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, "Small Fonts"));
            SIZE TextSize; GetTextExtentPoint32A(EasyGUI_DrawHDC, String.c_str(), strlen(String.c_str()), &TextSize); if (X >= 10000)X -= 10000 + TextSize.cx / 2; if (Y >= 10000)Y -= 10000 + TextSize.cy / 2; if (!X && !Y) { DeleteObject(FontPen); return TextSize.cx; }//坐标大于10000时采用居中坐标
            SetBkMode(EasyGUI_DrawHDC, TRANSPARENT);//背景透明
            SetTextColor(EasyGUI_DrawHDC, RGB(Color_2.r, Color_2.g, Color_2.b));//文字颜色
            TextOutA(EasyGUI_DrawHDC, X + 1, Y + 1, String.c_str(), strlen(String.c_str()));
            TextOutA(EasyGUI_DrawHDC, X - 1, Y - 1, String.c_str(), strlen(String.c_str()));
            TextOutA(EasyGUI_DrawHDC, X + 1, Y - 1, String.c_str(), strlen(String.c_str()));
            TextOutA(EasyGUI_DrawHDC, X - 1, Y + 1, String.c_str(), strlen(String.c_str()));
            TextOutA(EasyGUI_DrawHDC, X + 1, Y, String.c_str(), strlen(String.c_str()));
            TextOutA(EasyGUI_DrawHDC, X - 1, Y, String.c_str(), strlen(String.c_str()));
            TextOutA(EasyGUI_DrawHDC, X, Y - 1, String.c_str(), strlen(String.c_str()));
            TextOutA(EasyGUI_DrawHDC, X, Y + 1, String.c_str(), strlen(String.c_str()));
            SetTextColor(EasyGUI_DrawHDC, RGB(Color_1.r, Color_1.g, Color_1.b));//文字颜色
            TextOutA(EasyGUI_DrawHDC, X, Y, String.c_str(), strlen(String.c_str()));
            DeleteObject(FontPen);
            return TextSize.cx;
        }
        //---------------------------------------------------------------------
        BOOL In_MouseEventJudgment(int X, int Y, int Width, int Length) noexcept//检测鼠标坐标是否在窗口矩形坐标内
        {
            if (!(EasyGUI_MousePos.x >= EasyGUI_WindowPos.left && EasyGUI_MousePos.x <= EasyGUI_WindowPos.right && EasyGUI_MousePos.y >= EasyGUI_WindowPos.top && EasyGUI_MousePos.y <= EasyGUI_WindowPos.bottom))return false;//当指针不在窗口内
            if (EasyGUI_MousePos.x - EasyGUI_WindowPos.left >= X && EasyGUI_MousePos.x - EasyGUI_WindowPos.left <= X + Width && EasyGUI_MousePos.y - EasyGUI_WindowPos.top >= Y && EasyGUI_MousePos.y - EasyGUI_WindowPos.top <= Y + Length)return true;
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
                if (EasyGUI_ClickSound && (VK_CODE == VK_LBUTTON || VK_CODE == VK_RBUTTON))Beep(EasyGUI_ClickSound * 1000, 3);//点击音效
            }
            return Key_State;
        }
        //---------------------------------------------------------------------
        template<class CreateClassName>//防止同函数同步
        BOOL In_TickSleep(int Time_MS) noexcept//不受线程影响的Sleep函数
        {
            const long Tick = GetTickCount64(); static long OldTick = Tick;
            if (Tick - OldTick >= Time_MS) { OldTick = Tick; return true; }//当达到一定数值返回并且重写变量
            else return false;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Global_SetFont(string FontName) noexcept { if (FontName == "")Global_EasyGUI_Font = "Verdana"; else Global_EasyGUI_Font = FontName; }//设置全局字体
        void Global_SetFontSize(int FontSize) noexcept { if (!FontSize)Global_EasyGUI_FontSize = 13; else Global_EasyGUI_FontSize = FontSize; }//设置全局字体大小
        void Global_SetMainColor(Vector4 MainColor) noexcept { Global_EasyGUI_Color = MainColor; }//设置全局主题颜色
        void Global_SetMainColorHue(float Sat = -1, float Grey = -1, float Bri = -1) noexcept { if (Sat >= 0)EasyGUI_ColorSat = Sat; if (Grey >= 0)EasyGUI_ColorGrey = Grey; if (Bri >= 0)EasyGUI_ColorBrig = Bri; }//设置全局主题色调
        void Global_SetClickSound(int Tone) noexcept { EasyGUI_ClickSound = Tone; }//设置全局点击音效
        string Global_GetFont() noexcept { return Global_EasyGUI_Font; }//获取全局字体
        int Global_GetFontSize() noexcept { return Global_EasyGUI_FontSize; }//获取全局字体大小
        Vector4 Global_GetMainColor() noexcept { return Global_EasyGUI_Color; }//获取全局主题颜色
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        HWND Window_Create(int Size_X, int Size_Y, string WindowTitle, BOOL IfTop = false) noexcept//创建窗口
        {
            while (true)
            {
                int 窗口类型 = WS_EX_LAYERED;
                if (IfTop)窗口类型 = WS_EX_TOPMOST | WS_EX_LAYERED;
                WNDCLASS RenWin; memset(&RenWin, 0, sizeof(RenWin));
                RenWin.style = CS_HREDRAW | CS_VREDRAW;
                RenWin.lpfnWndProc = EasyGUI_WndProc;//关联消息处理函数,告诉操作系统,如果有事件发生调用这个函数
                RenWin.cbClsExtra = 0; RenWin.cbWndExtra = 0;
                RenWin.hInstance = GetModuleHandle(0);//实例句柄
                RenWin.hCursor = LoadCursor(0, IDC_ARROW);//光标样式
                RenWin.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);//画刷
                RenWin.lpszMenuName = 0;
                RenWin.lpszClassName = wstring(WindowTitle.begin(), WindowTitle.end()).c_str();//窗口类的名称，操作系统根据类的名称做映射
                RegisterClass(&RenWin);//将这个窗体注册（告诉）到操作系统
                const auto hWnd = CreateWindowEx(窗口类型, wstring(WindowTitle.begin(), WindowTitle.end()).c_str(), wstring(WindowTitle.begin(), WindowTitle.end()).c_str(), WS_POPUP, GetSystemMetrics(SM_CXSCREEN) / 2 - Size_X / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - Size_Y / 2, Size_X, Size_Y, 0, 0, GetModuleHandle(0), 0);
                if (hWnd)//当创建成功
                {
                    UpdateWindow(hWnd); ShowWindow(hWnd, SW_SHOW); SetForegroundWindow(hWnd);
                    MSG MSG = { 0 }; if (GetMessage(&MSG, 0, 0, 0)) { TranslateMessage(&MSG); DispatchMessage(&MSG); }
                    SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), Global_EasyGUI_Color.a, LWA_ALPHA);
                    EasyGUI_WindowHWND = hWnd; EasyGUI_WindowHDC = GetWindowDC(hWnd);
                    //---------------------------------------双缓冲开始绘制
                    PaintSize = { Size_X + 400,Size_Y + 400 };//设定坐标上加上400缓冲区
                    EasyGUI_DrawHDC = CreateCompatibleDC(EasyGUI_WindowHDC);//内存画板 (如果不是最终绘制 请绘制到这里!!!)
                    SelectObject(EasyGUI_DrawHDC, (HBITMAP)CreateCompatibleBitmap(EasyGUI_WindowHDC, PaintSize.x, PaintSize.y));
                    //---------------------------------------------
                    return hWnd;//返回窗口HWND
                }
            }
        }
        void Draw_GUI(BOOL ReverseColor = false) noexcept//双缓冲结束绘制 (绘制最终返回图片)
        {
            //if (EasyGUI_MousePos.x == 0 && EasyGUI_MousePos.y == 0)In_DrawString_Simple(0, 0, "You are a unique star in the universe.", Global_EasyGUI_Color);//你是宇宙中独有的一颗星 (彩蛋)
            if (ReverseColor)BitBlt(EasyGUI_DrawHDC, 0, 0, PaintSize.x, PaintSize.y, EasyGUI_DrawHDC, 0, 0, PATINVERT);//反转颜色
            BitBlt(EasyGUI_WindowHDC, 0, 0, PaintSize.x, PaintSize.y, EasyGUI_DrawHDC, 0, 0, SRCCOPY);//最终绘制内存中的图像
            //--------------------------------消息循环
            In_KeyEvent(VK_UP, true); In_KeyEvent(VK_DOWN, true);//释放滚轮消息
            MSG MSG = { 0 }; if (GetMessage(&MSG, 0, 0, 0)) { TranslateMessage(&MSG); DispatchMessage(&MSG); }
            GetCursorPos(&EasyGUI_MousePos); GetWindowRect(EasyGUI_WindowHWND, &EasyGUI_WindowPos);//刷新鼠标窗口坐标
            //--------------------------------帧数计算
            static int m_fps = 0; m_fps++;
            const int Tick = GetTickCount64(); static int Tick_Old = Tick;
            if (Tick >= Tick_Old + 1000) { Tick_Old = Tick; EasyGUI_FPS = m_fps; m_fps = 0; }//每1秒刷新 (计时器)
            //----------------------------------------
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        HWND Window_HWND() noexcept { return EasyGUI_WindowHWND; }//获取GUI窗口HWND
        HDC Window_HDC() noexcept { return EasyGUI_DrawHDC; }//获取GUI窗口HDC
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Window_SetPos(Vector2 WindowPos) noexcept//修改GUI窗口坐标
        {
            RECT m_Windowrect; GetWindowRect(EasyGUI_WindowHWND, &m_Windowrect);
            MoveWindow(EasyGUI_WindowHWND, WindowPos.x, WindowPos.y, m_Windowrect.right - m_Windowrect.left, m_Windowrect.bottom - m_Windowrect.top, true);
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
            MoveWindow(EasyGUI_WindowHWND, m_Windowrect.left, m_Windowrect.top, WindowSize.x, WindowSize.y, true);
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
        void Window_SetAlpha(short WindowAlpha = 255) noexcept//修改GUI窗口整体阿尔法通道
        {
            if (WindowAlpha >= 255)WindowAlpha = 255; else if (WindowAlpha <= 0)WindowAlpha = 0;
            SetLayeredWindowAttributes(EasyGUI_WindowHWND, RGB(0, 0, 0), WindowAlpha, LWA_ALPHA);
            Global_EasyGUI_Color.a = WindowAlpha;
        }
        int Window_GetAlpha() noexcept//获取GUI窗口整体阿尔法通道
        {
            return Global_EasyGUI_Color.a;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Window_SetTitle(string WindowTitle) noexcept//修改GUI窗口标题
        {
            SetWindowTextA(EasyGUI_WindowHWND, WindowTitle.c_str());//修改窗口标题
        }
        string Window_GetTitle() noexcept//获取GUI窗口标题
        {
            CHAR pszMem[MAX_PATH] = { 0 }; GetWindowTextA(EasyGUI_WindowHWND, pszMem, GetWindowTextLength(EasyGUI_WindowHWND) + 1); return pszMem;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        int Window_FPS() noexcept { return EasyGUI_FPS; }//获取GUI绘制帧数
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL Window_Move(short Draw_Delay = 3, BOOL Limit_Edge = false) noexcept//移动GUI窗口 (在GUI循环线程内加入此函数不需要添加延时函数来降低CPU占用)
        {
            //--------------------------------消息循环
            MSG MSG = { 0 }; if (GetMessage(&MSG, 0, 0, 0)) { TranslateMessage(&MSG); DispatchMessage(&MSG); }
            GetCursorPos(&EasyGUI_MousePos); GetWindowRect(EasyGUI_WindowHWND, &EasyGUI_WindowPos);//刷新鼠标窗口坐标
            //---------------------------------------
            static BOOL 防止脱离, 保存鼠标坐标; static Vector2 OldPos;//按下时坐标
            if (GetForegroundWindow() == EasyGUI_WindowHWND)//检测窗口是否在最前端
            {
                if (!Mouse_Block_ && In_KeyEvent(VK_LBUTTON) && !防止脱离)//触发移动窗口机制
                {
                    if (保存鼠标坐标) { OldPos = { EasyGUI_MousePos.x - EasyGUI_WindowPos.left ,EasyGUI_MousePos.y - EasyGUI_WindowPos.top }; 保存鼠标坐标 = false; }
                    防止脱离 = true;//触发移动窗口事件变量
                }
                else if (防止脱离 && In_KeyEvent(VK_LBUTTON))//移动窗口时
                {
                    Mouse_Block_ = true; Mouse_Move_ = true;
                    if (Limit_Edge)//限制窗口不超过显示器像素区域
                    {
                        const Vector2 Scre = { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };//系统显示器像素
                        const Vector2 Size = { EasyGUI_WindowPos.right - EasyGUI_WindowPos.left, EasyGUI_WindowPos.bottom - EasyGUI_WindowPos.top };//窗口大小
                        Vector2 Move = { EasyGUI_MousePos.x - OldPos.x, EasyGUI_MousePos.y - OldPos.y };//窗口坐标
                        if (Move.x + Size.x >= Scre.x)Move.x = Scre.x - Size.x; else if (Move.x <= 0)Move.x = 0;//限制左右
                        if (Move.y + Size.y >= Scre.y)Move.y = Scre.y - Size.y; else if (Move.y <= 0)Move.y = 0;//限制上下
                        MoveWindow(EasyGUI_WindowHWND, Move.x, Move.y, Size.x, Size.y, true);//移动窗口
                    }
                    else MoveWindow(EasyGUI_WindowHWND, EasyGUI_MousePos.x - OldPos.x, EasyGUI_MousePos.y - OldPos.y, EasyGUI_WindowPos.right - EasyGUI_WindowPos.left, EasyGUI_WindowPos.bottom - EasyGUI_WindowPos.top, true);//移动窗口到鼠标坐标
                    if (In_TickSleep<class CLASS_EasyGUI_WindowMove_FPS_Delay_>(100))return false; else return true;//定时返回false (用来刷新面板)
                }
                else {//闲置时
                    防止脱离 = false; 保存鼠标坐标 = true; Mouse_Block_ = false; Mouse_Move_ = false;
                    if (!Mouse_Slider_)
                    {
                        if (EasyGUI_FPS > 30)//帧率无法低于30
                        {
                            if (In_KeyEvent(VK_LBUTTON))Sleep(1);
                            else Sleep(Draw_Delay);//降低CPU占用
                        }
                    }
                    else this_thread::sleep_for(chrono::nanoseconds(88));//纳秒休眠函数 (让滑条更加顺滑)
                    return false;
                }
            }
            else Sleep(20); return false;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        EasyGUI_IO Global_GetIO() noexcept//获取GUI数据
        {
            struct EasyGUI_IO IO;
            IO.DrawFPS = EasyGUI_FPS;
            IO.HWND = EasyGUI_WindowHWND;
            IO.HDC = EasyGUI_DrawHDC;
            IO.FontName = Global_EasyGUI_Font;
            IO.FontSize = Global_EasyGUI_FontSize;
            IO.GUIColor = Global_EasyGUI_Color;
            RECT Windowrect; GetWindowRect(EasyGUI_WindowHWND, &Windowrect);
            IO.WindowPos = { Windowrect.left ,Windowrect.top };
            IO.WindowSize = { Windowrect.right - Windowrect.left ,Windowrect.bottom - Windowrect.top };
            CHAR Windowtitle[MAX_PATH] = { 0 }; GetWindowTextA(EasyGUI_WindowHWND, Windowtitle, GetWindowTextLength(EasyGUI_WindowHWND) + 1);
            IO.WindowTitle = Windowtitle;
            IO.MousePos = { EasyGUI_MousePos.x,EasyGUI_MousePos.y };
            IO.GUIColor_Rainbow = {
                 (int)floor(sin((float)GetTickCount64() / 3000 * 2 + 3) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3000 * 2 + 5) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3000 * 2 + 7) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3000 * 2 + 2) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3000 * 2 + 4) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3000 * 2 + 6) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3000 * 2 + 1) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3000 * 2 + 3) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3000 * 2 + 5) * 127 + 128),
            };
            return IO;
        }
        //-------------------------------------------------------------------------------------------------------------------------------------------以下是控件函数*
        void GUI_BackGround(short BackGround_StyleCode = 0) noexcept//绘制GUI窗口背景
        {
            const Vector2 Window_Size = { EasyGUI_WindowPos.right - EasyGUI_WindowPos.left ,EasyGUI_WindowPos.bottom - EasyGUI_WindowPos.top };
            vector<int> LineColor = { 0,255,255,255,0,255,255,255,0 };
            vector<int> StyleColor = { 0,0,0,60,60,60,30,30,30,15,15,15,5,5,5,30,30,30 };
            if (BackGround_StyleCode == 0)//毛都没有
            {
                LineColor = { 16,16,16,16,16,16,16,16,16 };
                StyleColor = { 0,0,0,60,60,60,30,30,30,15,15,15,15,15,15,Global_EasyGUI_Color.r / 10,Global_EasyGUI_Color.g / 10,Global_EasyGUI_Color.b / 10 };
            }
            else if (BackGround_StyleCode == 1)
            {
                LineColor = { 100,255,255,255,100,255,255,255,100 };
                StyleColor = { 0,0,0,60,60,60,30,30,30,15,15,15,5,5,5,Global_EasyGUI_Color.r / 10,Global_EasyGUI_Color.g / 10,Global_EasyGUI_Color.b / 10 };
            }
            else if (BackGround_StyleCode == 2)
            {
                LineColor = { 0,255,255,255,0,255,255,255,0 };
                StyleColor = { 0,0,0,60,60,60,30,30,30,15,15,15,3,3,3,Global_EasyGUI_Color.r / 10,Global_EasyGUI_Color.g / 10,Global_EasyGUI_Color.b / 10 };
            }
            else if (BackGround_StyleCode == 3)//彩色变色渐变条
            {
                const auto Speed = 3000;//渐变条变化速度
                LineColor = {
                    (int)floor(sin((float)GetTickCount64() / Speed * 2 + 3) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / Speed * 2 + 5) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / Speed * 2 + 7) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / Speed * 2 + 2) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / Speed * 2 + 4) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / Speed * 2 + 6) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / Speed * 2 + 1) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / Speed * 2 + 3) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / Speed * 2 + 5) * 127 + 128),
                };
                StyleColor = { 0,0,0,60,60,60,30,30,30,15,15,15,3,3,3,Global_EasyGUI_Color.r / 10,Global_EasyGUI_Color.g / 10,Global_EasyGUI_Color.b / 10 };
                Global_EasyGUI_Color = { LineColor[3],LineColor[4], LineColor[5] };
            }
            else if (BackGround_StyleCode == 4)//主题色渐变条
            {
                const auto Speed = 800;//渐变条变化速度
                const Vector3 Sins = { sin((float)GetTickCount64() / Speed), sin((float)GetTickCount64() / Speed + 1),sin((float)GetTickCount64() / Speed + 2) };
                LineColor = {
                    (int)(Sins.z * Global_EasyGUI_Color.r / 2 + Global_EasyGUI_Color.r / 2),
                    (int)(Sins.z * Global_EasyGUI_Color.g / 2 + Global_EasyGUI_Color.g / 2),
                    (int)(Sins.z * Global_EasyGUI_Color.b / 2 + Global_EasyGUI_Color.b / 2),
                    (int)(Sins.y * Global_EasyGUI_Color.r / 2 + Global_EasyGUI_Color.r / 2),
                    (int)(Sins.y * Global_EasyGUI_Color.g / 2 + Global_EasyGUI_Color.g / 2),
                    (int)(Sins.y * Global_EasyGUI_Color.b / 2 + Global_EasyGUI_Color.b / 2),
                    (int)(Sins.x * Global_EasyGUI_Color.r / 2 + Global_EasyGUI_Color.r / 2),
                    (int)(Sins.x * Global_EasyGUI_Color.g / 2 + Global_EasyGUI_Color.g / 2),
                    (int)(Sins.x * Global_EasyGUI_Color.b / 2 + Global_EasyGUI_Color.b / 2)
                };
                for (int i = 0; i <= 8; ++i)if (LineColor[i] < 50)LineColor[i] = 50;//颜色最小值
                StyleColor = { 0,0,0,60,60,60,30,30,30,15,15,15,0,0,0,Global_EasyGUI_Color.r / 10,Global_EasyGUI_Color.g / 10,Global_EasyGUI_Color.b / 10 };
            }
            In_DrawRect(0, 0, Window_Size.x, Window_Size.y, { StyleColor[0], StyleColor[1], StyleColor[2] });
            In_DrawRect(1, 1, Window_Size.x - 2, Window_Size.y - 2, { StyleColor[3], StyleColor[4], StyleColor[5] });
            In_DrawRect(2, 2, Window_Size.x - 4, Window_Size.y - 4, { StyleColor[6], StyleColor[7], StyleColor[8] });
            In_DrawRect(5, 5, Window_Size.x - 10, Window_Size.y - 10, { StyleColor[3], StyleColor[4], StyleColor[5] });
            In_DrawGradientRect(6, 6, Window_Size.x - 12, Window_Size.y - 12, { StyleColor[12], StyleColor[13], StyleColor[14] }, { StyleColor[15], StyleColor[16], StyleColor[17] }, true);//BackGround Gradient
            if (BackGround_StyleCode)//彩虹条
            {
                In_DrawGradientRect(7, 7, (Window_Size.x - 14) / 2, 2, { LineColor[0] / 2, LineColor[1] / 2, LineColor[2] / 2 }, { LineColor[3] / 2, LineColor[4] / 2, LineColor[5] / 2 }, false);
                In_DrawGradientRect(7 + (Window_Size.x - 14) / 2, 7, (Window_Size.x - 14) / 2, 2, { LineColor[3] / 2, LineColor[4] / 2, LineColor[5] / 2 }, { LineColor[6] / 2, LineColor[7] / 2, LineColor[8] / 2 }, false);
                In_DrawGradientRect(7, 7, (Window_Size.x - 14) / 2, 1, { LineColor[0], LineColor[1], LineColor[2] }, { LineColor[3], LineColor[4], LineColor[5] }, false);
                In_DrawGradientRect(7 + (Window_Size.x - 14) / 2, 7, (Window_Size.x - 14) / 2, 1, { LineColor[3], LineColor[4], LineColor[5] }, { LineColor[6], LineColor[7], LineColor[8] }, false);
            }
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        Vector2 GUI_Block(int X, int Y, int Length, string BlockText, int Width = 400, BOOL Block_Judgment = true) noexcept//区块
        {
            In_DrawRect(X, Y, Width, Length, { 0,0,0 });//黑色外边框
            In_DrawRect(X + 1, Y + 1, Width - 2, Length - 2, { 60,60,60 });//白色外边框
            In_DrawGradientRect(X + 2, Y + 2, Width - 4, Length - 4, { 10,10,10 }, Global_EasyGUI_Color / 10, true);//渐变背景
            if (BlockText != "")
            {
                const auto TextSize = In_DrawString(0, 0, BlockText, { 0,0,0 }, "Small Fonts", 14, 600);//获取文字大小
                In_DrawGradientRect(X + TextSize + 15, Y + 1, Width - TextSize - 16, 1, { 20,20,20 }, { 60,60,60 });//渐变头条
                In_DrawRect(X + 15, Y, TextSize + 10, 3, { 10,10,10 });//文字后遮挡边框
            }
            In_DrawString(X + 21, Y - 6, BlockText, { 0,0,0 }, "Small Fonts", 14, 600);
            In_DrawString(X + 20, Y - 7, BlockText, { 200,200,200 }, "Small Fonts", 14, 600);
            if (Block_Judgment && ((EasyGUI_MousePos.x - EasyGUI_WindowPos.left >= X && EasyGUI_MousePos.x - EasyGUI_WindowPos.left <= X + Width && EasyGUI_MousePos.y - EasyGUI_WindowPos.top >= Y && EasyGUI_MousePos.y - EasyGUI_WindowPos.top <= Y + Length) || !(EasyGUI_MousePos.x >= EasyGUI_WindowPos.left && EasyGUI_MousePos.x <= EasyGUI_WindowPos.right && EasyGUI_MousePos.y >= EasyGUI_WindowPos.top && EasyGUI_MousePos.y <= EasyGUI_WindowPos.bottom)))Mouse_Block_ = true;
            return { X,Y };
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        Vector2 GUI_Block_Page(int X, int Y, int Length, string BlockText, int& m_PageID, short MaxPage = 1, int Width = 400) noexcept//区块_分页的区块
        {
            if (m_PageID < 0)m_PageID = 0; else if (m_PageID > MaxPage)m_PageID = MaxPage;//页面数量限制
            In_DrawRect(X, Y, Width, Length, { 0,0,0 });//黑色外边框
            In_DrawRect(X + 1, Y + 1, Width - 2, Length - 2, { 60,60,60 });//白色外边框
            In_DrawGradientRect(X + 2, Y + 2, Width - 4, Length - 4, { 10,10,10 }, Global_EasyGUI_Color / 10, true);//渐变背景
            if (BlockText != "")
            {
                const auto TextSize = In_DrawString(0, 0, BlockText, { 0,0,0 }, "Small Fonts", 14, 600);//获取文字大小
                In_DrawGradientRect(X + TextSize + 15, Y + 1, Width - TextSize - 16, 1, { 20,20,20 }, { 60,60,60 });//渐变头条
                In_DrawRect(X + 15, Y, TextSize + 10, 3, { 10,10,10 });//文字后遮挡边框
            }
            In_DrawString(X + 21, Y - 6, BlockText, { 0,0,0 }, "Small Fonts", 14, 600);
            In_DrawString(X + 20, Y - 7, BlockText, { 200,200,200 }, "Small Fonts", 14, 600);
            const static short ArrowZoom = 4;//缩小箭头像素
            if (m_PageID)In_DrawArrow(X + Width - 20 + ArrowZoom, Y + 5 + ArrowZoom, 15 - ArrowZoom * 2, 15 - ArrowZoom * 2, { 60,60,60 }, true);
            if (m_PageID != MaxPage)In_DrawArrow(X + Width - 20 + ArrowZoom, Y + Length - 20 + ArrowZoom, 15 - ArrowZoom * 2, 15 - ArrowZoom * 2, { 60,60,60 }, false);//绘制箭头
            const auto PreviousPage = In_MouseEventJudgment(X + Width - 20, Y + 5, 15, 15), NextPage = In_MouseEventJudgment(X + Width - 20, Y + Length - 20, 15, 15);//鼠标指针坐标判断
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_ && !Mouse_Move_)//判断是否可输入
            {
                if (m_PageID && PreviousPage && In_KeyEvent(VK_LBUTTON, true))m_PageID--; else if (m_PageID != MaxPage && NextPage && In_KeyEvent(VK_LBUTTON, true))m_PageID++;
                if (In_MouseEventJudgment(X + Width - 20, Y, 20, Length)) { if (In_KeyEvent(VK_UP, true))--m_PageID; else if (In_KeyEvent(VK_DOWN, true))++m_PageID; Mouse_Icon = IDC_SIZENS; }//滚轮按键赋值
                if (m_PageID < 0)m_PageID = 0; else if (m_PageID > MaxPage)m_PageID = MaxPage;//页面数量限制
            }
            if ((EasyGUI_MousePos.x - EasyGUI_WindowPos.left >= X && EasyGUI_MousePos.x - EasyGUI_WindowPos.left <= X + Width && EasyGUI_MousePos.y - EasyGUI_WindowPos.top >= Y && EasyGUI_MousePos.y - EasyGUI_WindowPos.top <= Y + Length) || !(EasyGUI_MousePos.x >= EasyGUI_WindowPos.left && EasyGUI_MousePos.x <= EasyGUI_WindowPos.right && EasyGUI_MousePos.y >= EasyGUI_WindowPos.top && EasyGUI_MousePos.y <= EasyGUI_WindowPos.bottom))Mouse_Block_ = true;
            return { X,Y };
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        int GUI_Block_Panel(int X, int Y, int Width, int Length, string BlockText, vector<string>BlockText_, int& m_In_Block, short TextPos_X = 25) noexcept//区块_大区块选择器
        {
            if (m_In_Block < 0)m_In_Block = 0; else if (m_In_Block >= BlockText_.size())m_In_Block = BlockText_.size() - 1;//范围限制
            In_DrawRect(X, Y, Width, Length, { 0,0,0 });//黑色外边框
            In_DrawRect(X + 1, Y + 1, Width - 2, Length - 2, { 60,60,60 });//白色外边框
            In_DrawGradientRect(X + 2, Y + 2, Width - 4, Length - 4, Global_EasyGUI_Color / 10, { 10,10,10 }, true);//主题色渐变背景
            if (BlockText != "")In_DrawRect(X + 10, Y, In_DrawString(0, 0, BlockText, { 0,0,0 }, "Small Fonts", 14, 600) + 10, 3, Global_EasyGUI_Color / 10);//文字后遮挡边框
            In_DrawString(X + 16, Y - 6, BlockText, { 0,0,0 }, "Small Fonts", 14, 600);
            In_DrawString(X + 15, Y - 7, BlockText, { 200,200,200 }, "Small Fonts", 14, 600);
            for (short i = 0; i < BlockText_.size(); ++i)//遍历坐标
            {
                if (In_MouseEventJudgment(X, Y, Width, Length) && GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_ && !Mouse_Move_)
                {
                    if (In_KeyEvent(VK_UP, true))--m_In_Block; else if (In_KeyEvent(VK_DOWN, true))++m_In_Block;//滚轮按键赋值
                    if (m_In_Block < 0)m_In_Block = 0; else if (m_In_Block >= BlockText_.size())m_In_Block = BlockText_.size() - 1;//范围限制
                }
                if (In_MouseEventJudgment(X, Y + 14 + 30 * i, Width, 23))
                {
                    In_DrawGradientRect(X + 2, Y + 16 + 30 * i, Width - 4, 23, Global_EasyGUI_Color / 6, { 20,20,20 });
                    if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_ && !Mouse_Move_ && m_In_Block != i && In_KeyEvent(VK_LBUTTON, true))m_In_Block = i;//鼠标赋值选择
                }
                if (m_In_Block == i)
                {
                    In_DrawGradientRect(X + 2, Y + 16 + 30 * i, Width - 4, 25, { 20,20,20 }, Global_EasyGUI_Color / 4);
                    In_DrawGradientRect(X + 2, Y + 16 + 30 * i + 1, Width - 4, 23, Global_EasyGUI_Color / 4, { 20,20,20 });
                }
                In_DrawString(X + TextPos_X + 1, 10000 + Y + 29 + 30 * i, BlockText_[i], { 0,0,0 }, Global_EasyGUI_Font, Global_EasyGUI_FontSize + 2);
                In_DrawString(X + TextPos_X, 10000 + Y + 28 + 30 * i, BlockText_[i], { 220,220,220 }, Global_EasyGUI_Font, Global_EasyGUI_FontSize + 2);
            }
            if ((EasyGUI_MousePos.x - EasyGUI_WindowPos.left >= X && EasyGUI_MousePos.x - EasyGUI_WindowPos.left <= X + Width && EasyGUI_MousePos.y - EasyGUI_WindowPos.top >= Y && EasyGUI_MousePos.y - EasyGUI_WindowPos.top <= Y + Length) || !(EasyGUI_MousePos.x >= EasyGUI_WindowPos.left && EasyGUI_MousePos.x <= EasyGUI_WindowPos.right && EasyGUI_MousePos.y >= EasyGUI_WindowPos.top && EasyGUI_MousePos.y <= EasyGUI_WindowPos.bottom))Mouse_Block_ = true;
            return m_In_Block;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        int GUI_Text(Vector2 BlockPos, short LineRow, string Text, Vector4 TextColor = { 200,200,200 }) noexcept//行文字
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return 0;//当无block则不进行绘制
            In_DrawString(BlockPos.x + 53, 10000 + BlockPos.y + 4 + 30 * LineRow, Text, { 0,0,0 }, Global_EasyGUI_Font, Global_EasyGUI_FontSize);
            return In_DrawString(BlockPos.x + 52, 10000 + BlockPos.y + 3 + 30 * LineRow, Text, TextColor, Global_EasyGUI_Font, Global_EasyGUI_FontSize);
        }
        //--------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL GUI_Checkbox(Vector2 BlockPos, short LineRow, string Text, BOOL& m_CheckboxValue, Vector4 TextColor = { 200,200,200 }) noexcept//点击框
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return false;//当无block则不进行绘制
            const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 30, BlockPos.y + 30 * LineRow - 2, 140, 12);//窗口检测
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_ && !Mouse_Move_ && DetectMousePos && In_KeyEvent(VK_LBUTTON, true))m_CheckboxValue = !m_CheckboxValue;//当最前端窗口为GUI窗口接收按钮事件
            In_DrawRect(BlockPos.x + 29, BlockPos.y - 1 + 30 * LineRow, 10, 10, { 0,0,0 });
            In_DrawString(BlockPos.x + 53, 10000 + BlockPos.y + 4 + 30 * LineRow, Text, { 0,0,0 }, Global_EasyGUI_Font, Global_EasyGUI_FontSize);
            In_DrawString(BlockPos.x + 52, 10000 + BlockPos.y + 3 + 30 * LineRow, Text, TextColor, Global_EasyGUI_Font, Global_EasyGUI_FontSize);
            if (m_CheckboxValue)In_DrawGradientRect(BlockPos.x + 30, BlockPos.y + 30 * LineRow, 8, 8, Global_EasyGUI_Color, Global_EasyGUI_Color / 5, true);//绘制开关状态 (颜色主体)
            else {
                if (DetectMousePos)In_DrawGradientRect(BlockPos.x + 30, BlockPos.y + 30 * LineRow, 8, 8, Global_EasyGUI_Color / 3, { 30,30,30 }, true);
                else In_DrawGradientRect(BlockPos.x + 30, BlockPos.y + 30 * LineRow, 8, 8, Global_EasyGUI_Color / 4, { 30,30,30 }, true);
            }
            return m_CheckboxValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL GUI_Button(Vector2 BlockPos, short LineRow, string Text, BOOL& m_ButtonValue) noexcept//单击按钮
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return false;//当无block则不进行绘制
            if (m_ButtonValue)Sleep(30);//更好地让其他循环线程接收
            const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 55, BlockPos.y + 30 * LineRow - 8, 230, 25);//窗口检测机制
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_ && !Mouse_Move_)m_ButtonValue = !m_ButtonValue && DetectMousePos && In_KeyEvent(VK_LBUTTON, true);//当最前端窗口为GUI窗口接收按钮事件
            In_DrawRect(BlockPos.x + 53, BlockPos.y - 10 + 30 * LineRow, 234, 29, { 0,0,0 });
            In_DrawRect(BlockPos.x + 54, BlockPos.y - 9 + 30 * LineRow, 232, 27, { 60,60,60 });
            if (DetectMousePos && !m_ButtonValue)In_DrawGradientRect(BlockPos.x + 55, BlockPos.y + 30 * LineRow - 8, 230, 25, Global_EasyGUI_Color / 5, { 20,20,20 }, true);
            else In_DrawGradientRect(BlockPos.x + 55, BlockPos.y + 30 * LineRow - 8, 230, 25, Global_EasyGUI_Color / 7, { 20,20,20 }, true);
            In_DrawString(10000 + BlockPos.x + 171, 10000 + BlockPos.y + 30 * LineRow + 5, Text, { 0,0,0 }, Global_EasyGUI_Font, Global_EasyGUI_FontSize);
            In_DrawString(10000 + BlockPos.x + 170, 10000 + BlockPos.y + 30 * LineRow + 4, Text, { 200,200,200 }, Global_EasyGUI_Font, Global_EasyGUI_FontSize);
            return m_ButtonValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL GUI_Button_Small(Vector2 BlockPos, short LineRow, BOOL& m_ButtonValue, string Text = "...") noexcept//单击按钮(小号)
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return false;//当无block则不进行绘制
            if (m_ButtonValue)Sleep(30);//更好地让其他循环线程接收
            const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 10, BlockPos.y + 30 * LineRow - 5, 13, 18);//窗口检测机制
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_ && !Mouse_Move_)m_ButtonValue = !m_ButtonValue && DetectMousePos && In_KeyEvent(VK_LBUTTON, true);//当最前端窗口为GUI窗口接收按钮事件
            In_DrawRect(BlockPos.x + 8, BlockPos.y - 7 + 30 * LineRow, 17, 22, { 0,0,0 });
            In_DrawRect(BlockPos.x + 9, BlockPos.y - 6 + 30 * LineRow, 15, 20, { 60,60,60 });
            if (DetectMousePos && !m_ButtonValue)In_DrawGradientRect(BlockPos.x + 10, BlockPos.y + 30 * LineRow - 5, 13, 18, Global_EasyGUI_Color / 5, { 20,20,20 }, true);
            else In_DrawGradientRect(BlockPos.x + 10, BlockPos.y + 30 * LineRow - 5, 13, 18, Global_EasyGUI_Color / 7, { 20,20,20 }, true);
            In_DrawString_Simple(BlockPos.x + 12, BlockPos.y + 30 * LineRow - 1, Text, { 200,200,200 });
            return m_ButtonValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        template<class ValueClass, class CreateClassName>
        ValueClass GUI_Slider(Vector2 BlockPos, short LineRow, string Text, ValueClass StartValue, ValueClass EndValue, ValueClass& m_SliderValue, string Unit = "%s", Vector4 TextColor = { 200,200,200 }) noexcept//滑条
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return false;//当无block则不进行绘制
            const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 55, BlockPos.y + 6 + 30 * LineRow, 230, 5);//窗口检测
            static BOOL OutSide = false;//防止指针脱落时失去控制力
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Move_)//当最前端窗口为GUI窗口接收按钮事件
            {
                static const ValueClass ClassValueDetect = 0.1;//检测是否是浮点值 (变量)
                if (DetectMousePos && (In_KeyEvent(VK_LEFT, true) || In_KeyEvent(VK_UP, true)))//当鼠标移动到滑条上方 按键反馈事件
                {
                    if (ClassValueDetect == 0)m_SliderValue--; else m_SliderValue -= 0.05;//检测是否是浮点值
                }
                else if (DetectMousePos && (In_KeyEvent(VK_RIGHT, true) || In_KeyEvent(VK_DOWN, true)))
                {
                    if (ClassValueDetect == 0)m_SliderValue++; else m_SliderValue += 0.05;//检测是否是浮点值
                }
                if (In_KeyEvent(VK_LBUTTON) && DetectMousePos && !OutSide)OutSide = true;
                if (OutSide && In_KeyEvent(VK_LBUTTON)) { m_SliderValue = ((EasyGUI_MousePos.x - BlockPos.x - EasyGUI_WindowPos.left - 54) * (EndValue - StartValue) / 230) + StartValue; Mouse_Block_ = true; Mouse_Slider_ = true; }
                else if (!In_KeyEvent(VK_LBUTTON)) { OutSide = false; Mouse_Slider_ = false; }
            }
            int SliderPos = (float)(m_SliderValue - StartValue) / (float)(EndValue - StartValue) * 230; if (SliderPos > 230)SliderPos = 230; else if (SliderPos < 0) SliderPos = 0;
            if (m_SliderValue <= StartValue)m_SliderValue = StartValue; else if (m_SliderValue >= EndValue)m_SliderValue = EndValue;//范围限制
            stringstream ss; ss << fixed << setprecision(3) << m_SliderValue; ss >> m_SliderValue;//只保留3位小数点后数
            if (Unit.find("%d") != string::npos)Unit.erase(Unit.find("%d"), ((string)"%d").length());//删除掉%d字符串
            else if (Unit.find("%s") != string::npos)Unit.replace(Unit.find("%s"), ((string)"%s").length(), ss.str());//替换掉%s字符串
            else Unit = ss.str() + Unit;//不存在特殊字符串时
            In_DrawString(BlockPos.x + 56, 10000 + BlockPos.y - 3 + 30 * LineRow, Text, { 0,0,0 }, Global_EasyGUI_Font, Global_EasyGUI_FontSize);
            In_DrawString(BlockPos.x + 55, 10000 + BlockPos.y - 4 + 30 * LineRow, Text, TextColor, Global_EasyGUI_Font, Global_EasyGUI_FontSize);
            In_DrawRect(BlockPos.x + 54, BlockPos.y + 5 + 30 * LineRow, 232, 7, { 0,0,0 });//黑色外边框
            if (DetectMousePos || OutSide)In_DrawGradientRect(BlockPos.x + 55, BlockPos.y + 6 + 30 * LineRow, 230, 5, { 25,25,25 }, Global_EasyGUI_Color / 4, true);//滑条背景
            else In_DrawGradientRect(BlockPos.x + 55, BlockPos.y + 6 + 30 * LineRow, 230, 5, { 20,20,20 }, Global_EasyGUI_Color / 5, true);
            In_DrawGradientRect(BlockPos.x + 55, BlockPos.y + 6 + 30 * LineRow, SliderPos, 5, Global_EasyGUI_Color, Global_EasyGUI_Color / 5, true);//滑条
            In_DrawString_Simple(BlockPos.x + 295, BlockPos.y + 2 + 30 * LineRow, Unit, { 150,150,150 });//返回值绘制
            //In_DrawString_Simple(10000 + BlockPos.x + 55 + SliderPos, BlockPos.y + 6 + 30 * LineRow, Unit, { 150,150,150 }, { 0,0,0 }, 600);//居中返回值绘制
            return m_SliderValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        template<class CreateClassName>
        int GUI_KeySelector(Vector2 BlockPos, short LineRow, int& m_KeySelectValue, string Mark = "") noexcept//按键选取按钮
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return false;//当无block则不进行绘制
            if (m_KeySelectValue >= 0xCCCCCCCC)m_KeySelectValue = 0;//修复过量
            if (Mark != "")BlockPos.x -= 5;//让出空间
            const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 350, BlockPos.y + 26 + 30 * (LineRow - 1), 40, 12);//鼠标坐标检测
            static BOOL BoxMea = false;//只声明一次初始开关设定变量
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_ && !Mouse_Move_)//当最前端窗口为GUI窗口接收按钮事件
            {
                if (!BoxMea && DetectMousePos && In_KeyEvent(VK_LBUTTON, true))BoxMea = true;
                else if (BoxMea)
                {
                    if (In_KeyEvent(VK_BACK, true) || In_KeyEvent(VK_ESCAPE, true)) { m_KeySelectValue = 0; BoxMea = false; }//默认无值
                    for (int i = 0x0; i < 0xFE; ++i)if (In_KeyEvent(i, true)) { m_KeySelectValue = i; BoxMea = false; }//当按下任意键
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
                if (DetectMousePos)In_DrawString_Simple(BlockPos.x + 355, BlockPos.y + 27 + 30 * (LineRow - 1), Mark + DrawString_VK, { 130,130,130 });
                else In_DrawString_Simple(BlockPos.x + 355, BlockPos.y + 27 + 30 * (LineRow - 1), Mark + DrawString_VK, { 100,100,100 });
                return m_KeySelectValue;
            }
            else In_DrawString_Simple(BlockPos.x + 355, BlockPos.y + 27 + 30 * (LineRow - 1), Mark + "[-]", Global_EasyGUI_Color / 1.5);//激活读取
            return false;//激活读取时返回false
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL GUI_Tip(Vector2 BlockPos, short LineRow, string TipsString, Vector4 TextColor = { 200,200,200 }) noexcept//鼠标指针提示 (只支持单行字符,代码写在最后为了不被覆盖绘制)
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return false;//当无block则不进行绘制
            In_DrawString_Simple(BlockPos.x + 8, BlockPos.y + 27 + 30 * (LineRow - 1), "[?]", { 100,100,100 });//GUI绘制
            if (GetForegroundWindow() == EasyGUI_WindowHWND && In_MouseEventJudgment(BlockPos.x + 8, BlockPos.y + 26 + 30 * (LineRow - 1), 13, 13) && !Mouse_Slider_)//当鼠标移动到问号 且GUI窗口为最顶层
            {
                if (TipsString.find("\n") != string::npos)//当在字符串中找到\n
                {
                    vector<string> AnalyzeStr = {}; string _Line = ""; istringstream _Stream(TipsString); string LongestStr = "";
                    while (getline(_Stream, _Line)) { if (_Line.length() > LongestStr.length())LongestStr = _Line; AnalyzeStr.push_back(_Line); }//字符串解析 (将每次\n出现时列入到vector数组中)
                    const Vector2 Rect_Size = { In_DrawString_Simple(0, 0, LongestStr) + 10, 15 * (int)AnalyzeStr.size() + 7 };//提示框长度
                    In_DrawRect(BlockPos.x + 23, BlockPos.y + 37 + 30 * (LineRow - 1), Rect_Size.x, Rect_Size.y, { 0,0,0 });
                    In_DrawRect(BlockPos.x + 24, BlockPos.y + 38 + 30 * (LineRow - 1), Rect_Size.x - 2, Rect_Size.y - 2, { 60,60,60 });
                    In_DrawGradientRect(BlockPos.x + 25, BlockPos.y + 39 + 30 * (LineRow - 1), Rect_Size.x - 4, Rect_Size.y - 4, Global_EasyGUI_Color / 15, Global_EasyGUI_Color / 10, true);
                    for (int l = 0; l < AnalyzeStr.size(); ++l)In_DrawString_Simple(BlockPos.x + 27, BlockPos.y + 41 + 30 * (LineRow - 1) + 15 * l, AnalyzeStr[l], TextColor);//遍历并绘制每一行
                }
                else {
                    const auto Rect_Length = In_DrawString_Simple(0, 0, TipsString) + 10;//提示框长度
                    In_DrawRect(BlockPos.x + 23, BlockPos.y + 37 + 30 * (LineRow - 1), Rect_Length, 20, { 0,0,0 });
                    In_DrawRect(BlockPos.x + 24, BlockPos.y + 38 + 30 * (LineRow - 1), Rect_Length - 2, 18, { 60,60,60 });
                    In_DrawGradientRect(BlockPos.x + 25, BlockPos.y + 39 + 30 * (LineRow - 1), Rect_Length - 4, 16, Global_EasyGUI_Color / 15, Global_EasyGUI_Color / 10, true);
                    In_DrawString_Simple(BlockPos.x + 27, BlockPos.y + 41 + 30 * (LineRow - 1), TipsString, TextColor);
                }
                return true;
            }
            else return false;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        Vector4 GUI_ColorSelector(Vector2 BlockPos, short LineRow, Vector4& m_ColorValue) noexcept//颜色选择器
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return { -1,-1,-1 };//当无block则不进行绘制
            if (GetForegroundWindow() == EasyGUI_WindowHWND && In_MouseEventJudgment(BlockPos.x + 360, BlockPos.y - 6 + 30 * LineRow, 20, 20) && !Mouse_Slider_ && !Mouse_Move_ && In_KeyEvent(VK_LBUTTON, true))//复制选取的颜色值
            {
                const string Color_String_Copy__ = to_string(m_ColorValue.r) + ", " + to_string(m_ColorValue.g) + ", " + to_string(m_ColorValue.b);//要复制的字符串
                OpenClipboard(0);//打开剪切板
                EmptyClipboard();//清空剪切板
                const auto hHandle = GlobalAlloc(0, strlen(Color_String_Copy__.c_str()) + 1);//分配内存
                strcpy_s((char*)GlobalLock(hHandle), strlen(Color_String_Copy__.c_str()) + 1, Color_String_Copy__.c_str());
                SetClipboardData(1, hHandle);//设置剪切板数据
                GlobalUnlock(hHandle);//解除锁定
                CloseClipboard();//关闭剪切板
            }
            for (short Color_Bl = 0; Color_Bl <= 2; ++Color_Bl)
            {
                vector<int> UsedColor = { m_ColorValue.r,m_ColorValue.g,m_ColorValue.b };
                const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 218 + 46 * Color_Bl, BlockPos.y - 6 + 30 * LineRow, 41, 20);
                if (GetForegroundWindow() == EasyGUI_WindowHWND && DetectMousePos && !Mouse_Slider_ && !Mouse_Move_)//当最前端窗口为GUI窗口接收按钮事件 当鼠标移动到滑条上方 按键反馈事件
                {
                    if (In_KeyEvent(VK_LBUTTON, true))UsedColor[Color_Bl]++;
                    else if (In_KeyEvent(VK_RBUTTON, true))UsedColor[Color_Bl]--;
                    if (In_KeyEvent(VK_LEFT, true) || In_KeyEvent(VK_UP, true))UsedColor[Color_Bl] += 5;
                    else if (In_KeyEvent(VK_RIGHT, true) || In_KeyEvent(VK_DOWN, true))UsedColor[Color_Bl] -= 5;
                    if (In_KeyEvent(VK_DELETE, true))UsedColor[Color_Bl] = 0;
                }
                if (UsedColor[Color_Bl] >= 255)UsedColor[Color_Bl] = 255;
                else if (UsedColor[Color_Bl] <= 0)UsedColor[Color_Bl] = 0;//范围限制
                m_ColorValue = { UsedColor[0],UsedColor[1],UsedColor[2] };
                In_DrawRect(BlockPos.x + 218 + 46 * Color_Bl, BlockPos.y - 6 + 30 * LineRow, 41, 20, { 0,0,0 });//Color_Block
                if (DetectMousePos)In_DrawGradientRect(BlockPos.x + 219 + 46 * Color_Bl, BlockPos.y - 5 + 30 * LineRow, 39, 18, Global_EasyGUI_Color / 4, { 30,30,30 }, true);
                else In_DrawGradientRect(BlockPos.x + 219 + 46 * Color_Bl, BlockPos.y - 5 + 30 * LineRow, 39, 18, Global_EasyGUI_Color / 5, { 30,30,30 }, true);
            }
            In_DrawString_Simple(BlockPos.x + 223, BlockPos.y - 2 + 30 * LineRow, "R: " + to_string(m_ColorValue.r), { 150,150,150 });
            In_DrawString_Simple(BlockPos.x + 269, BlockPos.y - 2 + 30 * LineRow, "G: " + to_string(m_ColorValue.g), { 150,150,150 });
            In_DrawString_Simple(BlockPos.x + 315, BlockPos.y - 2 + 30 * LineRow, "B: " + to_string(m_ColorValue.b), { 150,150,150 });
            In_DrawRect(BlockPos.x + 360, BlockPos.y - 6 + 30 * LineRow, 20, 20, { 0,0,0 });//Color
            In_DrawGradientRect(BlockPos.x + 361, BlockPos.y - 5 + 30 * LineRow, 18, 18, m_ColorValue, m_ColorValue / 4, true);
            return m_ColorValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        Vector4 GUI_ColorSelector_a(Vector2 BlockPos, short LineRow, Vector4& m_ColorValue) noexcept//颜色选择器(包含Alpha 透明度值)
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return { -1,-1,-1,-1 };//当无block则不进行绘制
            if (GetForegroundWindow() == EasyGUI_WindowHWND && In_MouseEventJudgment(BlockPos.x + 360, BlockPos.y - 6 + 30 * LineRow, 20, 20) && !Mouse_Slider_ && !Mouse_Move_ && In_KeyEvent(VK_LBUTTON, true))//复制选取的颜色值
            {
                const string Color_String_Copy__ = to_string(m_ColorValue.r) + ", " + to_string(m_ColorValue.g) + ", " + to_string(m_ColorValue.b) + ", " + to_string(m_ColorValue.a);//要复制的字符串
                OpenClipboard(0);//打开剪切板
                EmptyClipboard();//清空剪切板
                const auto hHandle = GlobalAlloc(0, strlen(Color_String_Copy__.c_str()) + 1);//分配内存
                strcpy_s((char*)GlobalLock(hHandle), strlen(Color_String_Copy__.c_str()) + 1, Color_String_Copy__.c_str());
                SetClipboardData(1, hHandle);//设置剪切板数据
                GlobalUnlock(hHandle);//解除锁定
                CloseClipboard();//关闭剪切板
            }
            for (short Color_Bl = 0; Color_Bl <= 3; ++Color_Bl)
            {
                vector<int> UsedColor = { m_ColorValue.r,m_ColorValue.g,m_ColorValue.b,m_ColorValue.a };
                const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 172 + 46 * Color_Bl, BlockPos.y - 6 + 30 * LineRow, 41, 20);
                if (GetForegroundWindow() == EasyGUI_WindowHWND && DetectMousePos && !Mouse_Slider_ && !Mouse_Move_)//当最前端窗口为GUI窗口接收按钮事件 当鼠标移动到滑条上方 按键反馈事件
                {
                    if (In_KeyEvent(VK_LBUTTON, true))UsedColor[Color_Bl]++;
                    else if (In_KeyEvent(VK_RBUTTON, true))UsedColor[Color_Bl]--;
                    if (In_KeyEvent(VK_LEFT, true) || In_KeyEvent(VK_UP, true))UsedColor[Color_Bl] += 5;
                    else if (In_KeyEvent(VK_RIGHT, true) || In_KeyEvent(VK_DOWN, true))UsedColor[Color_Bl] -= 5;
                    if (In_KeyEvent(VK_DELETE, true))UsedColor[Color_Bl] = 0;
                }
                if (UsedColor[Color_Bl] >= 255)UsedColor[Color_Bl] = 255;//范围限制
                else if (UsedColor[Color_Bl] <= 0)UsedColor[Color_Bl] = 0;
                m_ColorValue = { UsedColor[0],UsedColor[1],UsedColor[2],UsedColor[3] };
                In_DrawRect(BlockPos.x + 172 + 46 * Color_Bl, BlockPos.y - 6 + 30 * LineRow, 41, 20, { 0,0,0 });
                if (DetectMousePos)In_DrawGradientRect(BlockPos.x + 173 + 46 * Color_Bl, BlockPos.y - 5 + 30 * LineRow, 39, 18, Global_EasyGUI_Color / 4, { 30,30,30 }, true);
                else In_DrawGradientRect(BlockPos.x + 173 + 46 * Color_Bl, BlockPos.y - 5 + 30 * LineRow, 39, 18, Global_EasyGUI_Color / 5, { 30,30,30 }, true);
            }
            In_DrawString_Simple(BlockPos.x + 177, BlockPos.y - 2 + 30 * LineRow, "R: " + to_string(m_ColorValue.r), { 150,150,150 });
            In_DrawString_Simple(BlockPos.x + 223, BlockPos.y - 2 + 30 * LineRow, "G: " + to_string(m_ColorValue.g), { 150,150,150 });
            In_DrawString_Simple(BlockPos.x + 269, BlockPos.y - 2 + 30 * LineRow, "B: " + to_string(m_ColorValue.b), { 150,150,150 });
            In_DrawString_Simple(BlockPos.x + 315, BlockPos.y - 2 + 30 * LineRow, "A: " + to_string(m_ColorValue.a), { 150,150,150 });
            In_DrawRect(BlockPos.x + 360, BlockPos.y - 6 + 30 * LineRow, 20, 20, { 0,0,0 });
            In_DrawGradientRect(BlockPos.x + 361, BlockPos.y - 5 + 30 * LineRow, 18, 18, m_ColorValue, m_ColorValue / 4, true);//Color
            return m_ColorValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        Vector3 GUI_PosSelector(Vector2 BlockPos, short LineRow, Vector3& m_PosValue) noexcept//坐标选择器
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return { -1,-1,-1 };//当无block则不进行绘制
            for (short Pos_Bl = 0; Pos_Bl <= 2; ++Pos_Bl)
            {
                vector<float> UsedPos = { m_PosValue.x,m_PosValue.y,m_PosValue.z };
                const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 180 + 70 * Pos_Bl, BlockPos.y - 6 + 30 * LineRow, 68, 20);
                if (GetForegroundWindow() == EasyGUI_WindowHWND && DetectMousePos && !Mouse_Slider_ && !Mouse_Move_)//当最前端窗口为GUI窗口接收按钮事件 当鼠标移动到滑条上方 按键反馈事件
                {
                    if (In_KeyEvent(VK_LBUTTON, true))UsedPos[Pos_Bl] += 0.03;
                    else if (In_KeyEvent(VK_RBUTTON, true))UsedPos[Pos_Bl] -= 0.03;
                    if (In_KeyEvent(VK_LEFT, true))UsedPos[Pos_Bl] += 1;
                    else if (In_KeyEvent(VK_RIGHT, true))UsedPos[Pos_Bl] -= 1;
                    if (In_KeyEvent(VK_UP, true))UsedPos[Pos_Bl] += 10;//快速变值
                    else if (In_KeyEvent(VK_DOWN, true))UsedPos[Pos_Bl] -= 10;
                    if (In_KeyEvent(VK_DELETE, true))UsedPos[Pos_Bl] = 0;
                    m_PosValue = { UsedPos[0],UsedPos[1],UsedPos[2] };
                }
                In_DrawRect(BlockPos.x + 180 + 70 * Pos_Bl, BlockPos.y - 6 + 30 * LineRow, 70, 20, { 0,0,0 });
                if (DetectMousePos)In_DrawGradientRect(BlockPos.x + 181 + 70 * Pos_Bl, BlockPos.y - 5 + 30 * LineRow, 68, 18, Global_EasyGUI_Color / 4, { 30,30,30 }, true);
                else In_DrawGradientRect(BlockPos.x + 181 + 70 * Pos_Bl, BlockPos.y - 5 + 30 * LineRow, 68, 18, Global_EasyGUI_Color / 5, { 30,30,30 }, true);
            }
            stringstream Float_X, Float_Y, Float_Z;//只保留2位小数点后数
            Float_X << fixed << setprecision(2) << m_PosValue.x; Float_X >> m_PosValue.x;
            Float_Y << fixed << setprecision(2) << m_PosValue.y; Float_Y >> m_PosValue.y;
            Float_Z << fixed << setprecision(2) << m_PosValue.z; Float_Z >> m_PosValue.z;
            In_DrawString_Simple(BlockPos.x + 185, BlockPos.y - 2 + 30 * LineRow, "X: " + Float_X.str(), { 150,150,150 });
            In_DrawString_Simple(BlockPos.x + 255, BlockPos.y - 2 + 30 * LineRow, "Y: " + Float_Y.str(), { 150,150,150 });
            In_DrawString_Simple(BlockPos.x + 325, BlockPos.y - 2 + 30 * LineRow, "Z: " + Float_Z.str(), { 150,150,150 });
            return m_PosValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        template<class CreateClassName>
        int GUI_List(Vector2 BlockPos, short StartLineRow, vector<string>LineString, int& m_InLine, short LimitLine = 0, BOOL FilterNULL = false) noexcept//选择列表
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return false;//当无block则不进行绘制
            const auto LineStringSize = LineString.size();//获取行列数
            if (m_InLine < 0)m_InLine = 0; else if (m_InLine >= LineStringSize)m_InLine = LineStringSize - 1;//赋值范围限制
            static int StartLinePos = 0; if (!LimitLine)LimitLine = LineStringSize; if (!LineStringSize)m_InLine = -1;//防止过量访问崩溃
            if (!FilterNULL)//不过滤无效字符
            {
                if (In_MouseEventJudgment(BlockPos.x + 53, BlockPos.y - 10 + 30 * StartLineRow, 234, LimitLine * 25 + 5) && GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_ && !Mouse_Move_) { if (In_KeyEvent(VK_UP, true))--StartLinePos; else if (In_KeyEvent(VK_DOWN, true))++StartLinePos; }//鼠标滚轮调整绘制起始位置
                if (StartLinePos + LimitLine > LineStringSize)StartLinePos = LineStringSize - LimitLine; if (StartLinePos < 0)StartLinePos = 0;//开始行列位置范围限制
                In_DrawRect(BlockPos.x + 53, BlockPos.y - 10 + 30 * StartLineRow, 234, LimitLine * 25 + 5, { 0,0,0 });//黑色外边框
                In_DrawGradientRect(BlockPos.x + 54, BlockPos.y - 9 + 30 * StartLineRow, 232, LimitLine * 25 + 3, Global_EasyGUI_Color / 10, { 10,10,10 }, true);//主题色渐变背景
                for (short i = StartLinePos; i < LineStringSize; ++i)
                {
                    if (i - StartLinePos >= LimitLine)continue;//限制行数
                    if (In_MouseEventJudgment(BlockPos.x + 54, BlockPos.y + StartLineRow * 30 + (i - StartLinePos) * 25 - 5, 232, 20))//鼠标赋值选择
                    {
                        if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_ && !Mouse_Move_ && m_InLine != i && In_KeyEvent(VK_LBUTTON, true))m_InLine = i;
                        In_DrawGradientRect(BlockPos.x + 54, BlockPos.y + StartLineRow * 30 + (i - StartLinePos) * 25 - 5, 232, 20, Global_EasyGUI_Color / 8, { 15,15,15 });
                    }
                    if (m_InLine == i)
                    {
                        In_DrawGradientRect(BlockPos.x + 54, BlockPos.y + StartLineRow * 30 + (i - StartLinePos) * 25 - 5, 232, 20, Global_EasyGUI_Color / 6, { 15,15,15 });
                        In_DrawString(BlockPos.x + 66, 10000 + BlockPos.y + StartLineRow * 30 + (i - StartLinePos) * 25 + 6, LineString[i], { 0,0,0 }, Global_EasyGUI_Font, Global_EasyGUI_FontSize, 600);
                        In_DrawString(BlockPos.x + 65, 10000 + BlockPos.y + StartLineRow * 30 + (i - StartLinePos) * 25 + 5, LineString[i], Global_EasyGUI_Color, Global_EasyGUI_Font, Global_EasyGUI_FontSize, 600);
                    }
                    else {
                        In_DrawString(BlockPos.x + 66, 10000 + BlockPos.y + StartLineRow * 30 + (i - StartLinePos) * 25 + 6, LineString[i], { 0,0,0 }, Global_EasyGUI_Font, Global_EasyGUI_FontSize);
                        In_DrawString(BlockPos.x + 65, 10000 + BlockPos.y + StartLineRow * 30 + (i - StartLinePos) * 25 + 5, LineString[i], { 200,200,200 }, Global_EasyGUI_Font, Global_EasyGUI_FontSize);
                    }
                }
                if (LineStringSize > LimitLine)//只有在内容超出可视区域时才会绘制滚动条
                {
                    const int ListHeight = LimitLine * 25 + 1, ScrollBarY = BlockPos.y - 10 + 30 * StartLineRow + 2, MaxScroll = LineStringSize - LimitLine;
                    const int ScrollBarHeight = max(int(ListHeight * float(LimitLine) / LineStringSize), 10);
                    In_DrawRect(BlockPos.x + 283, ScrollBarY, 2, ListHeight, Global_EasyGUI_Color / 7);//滚动条背景槽
                    In_DrawRect(BlockPos.x + 283, ScrollBarY + int((float)(MaxScroll > 0 ? float(StartLinePos) / MaxScroll : 0.f) * (ListHeight - ScrollBarHeight)), 2, ScrollBarHeight, Global_EasyGUI_Color / 2);//滚动条
                }
            }
            else {//过滤无效字符
                In_DrawRect(BlockPos.x + 53, BlockPos.y - 10 + 30 * StartLineRow, 234, LimitLine * 25 + 5, { 0,0,0 });//黑色外边框
                In_DrawGradientRect(BlockPos.x + 54, BlockPos.y - 9 + 30 * StartLineRow, 232, LimitLine * 25 + 3, Global_EasyGUI_Color / 10, { 10,10,10 }, true);//主题色渐变背景
                int LinePos = 0;
                for (short i = 0; i < LineStringSize; ++i)
                {
                    auto Toup_Str = LineString[i]; transform(Toup_Str.begin(), Toup_Str.end(), Toup_Str.begin(), toupper);//字符串转换大写 (方便判断无效字符)
                    if (Toup_Str == "NULL" || Toup_Str == "NONE" || Toup_Str == "")continue;//过滤无效内容
                    if (LinePos >= LimitLine)continue;//限制行数
                    if (In_MouseEventJudgment(BlockPos.x + 54, BlockPos.y + StartLineRow * 30 + LinePos * 25 - 5, 232, 20))//鼠标赋值选择
                    {
                        if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_ && !Mouse_Move_ && m_InLine != i && In_KeyEvent(VK_LBUTTON, true))m_InLine = i;
                        In_DrawGradientRect(BlockPos.x + 54, BlockPos.y + StartLineRow * 30 + LinePos * 25 - 5, 232, 20, Global_EasyGUI_Color / 7, { 15,15,15 });
                    }
                    if (m_InLine == i)
                    {
                        In_DrawGradientRect(BlockPos.x + 54, BlockPos.y + StartLineRow * 30 + LinePos * 25 - 5, 232, 20, Global_EasyGUI_Color / 6, { 15,15,15 });
                        In_DrawString(BlockPos.x + 66, 10000 + BlockPos.y + StartLineRow * 30 + LinePos * 25 + 6, LineString[i], { 0,0,0 }, Global_EasyGUI_Font, Global_EasyGUI_FontSize, 600);
                        In_DrawString(BlockPos.x + 65, 10000 + BlockPos.y + StartLineRow * 30 + LinePos * 25 + 5, LineString[i], Global_EasyGUI_Color, Global_EasyGUI_Font, Global_EasyGUI_FontSize, 600);
                    }
                    else {
                        In_DrawString(BlockPos.x + 66, 10000 + BlockPos.y + StartLineRow * 30 + LinePos * 25 + 6, LineString[i], { 0,0,0 }, Global_EasyGUI_Font, Global_EasyGUI_FontSize);
                        In_DrawString(BlockPos.x + 65, 10000 + BlockPos.y + StartLineRow * 30 + LinePos * 25 + 5, LineString[i], { 200,200,200 }, Global_EasyGUI_Font, Global_EasyGUI_FontSize);
                    }
                    LinePos++;
                }
            }
            return m_InLine;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        template<class CreateClassName>
        string GUI_InputText(Vector2 BlockPos, short LineRow, string& m_String, string NormalText = "", BOOL HideString = false) noexcept//字符串输入框 (英文数字 不支持UTF-8 最多30个字符)
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return "";//当无block则不进行绘制
            const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 55, BlockPos.y + 30 * LineRow - 9, 230, 25);//窗口检测机制
            static BOOL IsInput = false;//判断是否在输入变量
            string DrawString = m_String;//绘制字符串
            if (HideString) { const auto StrSize = DrawString.size(); DrawString = ""; for (short i = 0; i < StrSize; ++i)DrawString += "*"; }//隐藏字符串 (通常输入密码时使用)
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_ && !Mouse_Move_)//当最前端窗口为GUI窗口接收输入框事件
            {
                if (!IsInput && DetectMousePos && In_KeyEvent(VK_LBUTTON, true))IsInput = true;//进入输入状态
                else if (IsInput)//在输入状态时
                {
                    string PressedKey = "";//按键记录变量
                    if (In_KeyEvent(VK_LCONTROL) || In_KeyEvent(VK_RCONTROL))//Ctrl键脚本
                    {
                        if (In_KeyEvent('C', true) && OpenClipboard(0))//Ctrl + C 复制
                        {
                            EmptyClipboard();//清空剪切板
                            const auto hHandle = GlobalAlloc(GMEM_MOVEABLE, strlen(m_String.c_str()) + 1);//分配内存
                            strcpy_s((char*)GlobalLock(hHandle), strlen(m_String.c_str()) + 1, m_String.c_str());
                            SetClipboardData(CF_TEXT, hHandle);//设置剪切板数据
                            GlobalUnlock(hHandle);//解除锁定
                            CloseClipboard();//关闭剪切板
                        }
                        if (In_KeyEvent('V', true) && OpenClipboard(0))//Ctrl + V 粘贴
                        {
                            if (IsClipboardFormatAvailable(CF_TEXT))
                            {
                                const auto c_data = GetClipboardData(CF_TEXT);//获取剪切板数据
                                m_String += ((char*)GlobalLock(c_data));//在字符串尾部粘贴字符串内容
                                GlobalUnlock(c_data);//解除锁定
                            }
                            CloseClipboard();//关闭剪切板
                        }
                    }
                    else {//不阻止Ctrl脚本事件
                        const auto Is_Shift = In_KeyEvent(VK_SHIFT) || In_KeyEvent(VK_LSHIFT) || In_KeyEvent(VK_RSHIFT);//Shift键脚本
                        for (int i = 0x8; i < 0xFE; ++i)//VK键码遍历 (检测按下了什么键)
                        {
                            if (i != VK_SHIFT && i != VK_LSHIFT && i != VK_RSHIFT && In_KeyEvent(i, true))
                            {
                                switch (i)//相比if函数执行更快
                                {
                                case 0x20:PressedKey = " "; break;
                                case 0x30:PressedKey = Is_Shift ? ")" : "0"; break;
                                case 0x31:PressedKey = Is_Shift ? "!" : "1"; break;
                                case 0x32:PressedKey = Is_Shift ? "@" : "2"; break;
                                case 0x33:PressedKey = Is_Shift ? "#" : "3"; break;
                                case 0x34:PressedKey = Is_Shift ? "$" : "4"; break;
                                case 0x35:PressedKey = Is_Shift ? "%" : "5"; break;
                                case 0x36:PressedKey = Is_Shift ? "^" : "6"; break;
                                case 0x37:PressedKey = Is_Shift ? "&" : "7"; break;
                                case 0x38:PressedKey = Is_Shift ? "*" : "8"; break;
                                case 0x39:PressedKey = Is_Shift ? "(" : "9"; break;
                                case 0x41:PressedKey = Is_Shift ? "A" : "a"; break;
                                case 0x42:PressedKey = Is_Shift ? "B" : "b"; break;
                                case 0x43:PressedKey = Is_Shift ? "C" : "c"; break;
                                case 0x44:PressedKey = Is_Shift ? "D" : "d"; break;
                                case 0x45:PressedKey = Is_Shift ? "E" : "e"; break;
                                case 0x46:PressedKey = Is_Shift ? "F" : "f"; break;
                                case 0x47:PressedKey = Is_Shift ? "G" : "g"; break;
                                case 0x48:PressedKey = Is_Shift ? "H" : "h"; break;
                                case 0x49:PressedKey = Is_Shift ? "I" : "i"; break;
                                case 0x4A:PressedKey = Is_Shift ? "J" : "j"; break;
                                case 0x4B:PressedKey = Is_Shift ? "K" : "k"; break;
                                case 0x4C:PressedKey = Is_Shift ? "L" : "l"; break;
                                case 0x4D:PressedKey = Is_Shift ? "M" : "m"; break;
                                case 0x4E:PressedKey = Is_Shift ? "N" : "n"; break;
                                case 0x4F:PressedKey = Is_Shift ? "O" : "o"; break;
                                case 0x50:PressedKey = Is_Shift ? "P" : "p"; break;
                                case 0x51:PressedKey = Is_Shift ? "Q" : "q"; break;
                                case 0x52:PressedKey = Is_Shift ? "R" : "r"; break;
                                case 0x53:PressedKey = Is_Shift ? "S" : "s"; break;
                                case 0x54:PressedKey = Is_Shift ? "T" : "t"; break;
                                case 0x55:PressedKey = Is_Shift ? "U" : "u"; break;
                                case 0x56:PressedKey = Is_Shift ? "V" : "v"; break;
                                case 0x57:PressedKey = Is_Shift ? "W" : "w"; break;
                                case 0x58:PressedKey = Is_Shift ? "X" : "x"; break;
                                case 0x59:PressedKey = Is_Shift ? "Y" : "y"; break;
                                case 0x5A:PressedKey = Is_Shift ? "Z" : "z"; break;
                                case 0xBA:PressedKey = Is_Shift ? ":" : ";"; break;
                                case 0xBB:PressedKey = Is_Shift ? "+" : "="; break;
                                case 0xBC:PressedKey = Is_Shift ? "<" : ","; break;
                                case 0xBD:PressedKey = Is_Shift ? "_" : "-"; break;
                                case 0xBE:PressedKey = Is_Shift ? ">" : "."; break;
                                case 0xBF:PressedKey = Is_Shift ? "?" : "/"; break;
                                case 0xC0:PressedKey = Is_Shift ? "~" : "`"; break;
                                case 0xDB:PressedKey = Is_Shift ? "{" : "["; break;
                                case 0xDC:PressedKey = Is_Shift ? "|" : "\\"; break;
                                case 0xDD:PressedKey = Is_Shift ? "}" : "]"; break;
                                case 0xDE:PressedKey = Is_Shift ? "\"" : "'"; break;
                                case 0x60:PressedKey = "0"; break;//小键盘按键 (0x6开头)
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
                                case 0x6F:PressedKey = "/"; break;
                                case VK_BACK:if (m_String.size() > 0)m_String.erase(m_String.end() - 1); break;//擦除最后一个字符
                                case VK_DELETE:m_String = ""; break;//清除全部字符
                                case VK_ESCAPE:case VK_RETURN:IsInput = false; break;//按键解除输入状态
                                }
                                if (GetKeyState(0x14))transform(PressedKey.begin(), PressedKey.end(), PressedKey.begin(), toupper);//CapsLock大写转换
                                m_String += PressedKey;//返回按下
                            }
                        }
                    }
                    DrawString = DrawString.substr(0, 30); if (m_String.size() > 30)DrawString += "...";//防止过量 (防止绘制在非绘制区域)
                    else if ((GetTickCount64() / 250) % 2 == 0)DrawString += "_";//输入中绘制标识
                    if (!DetectMousePos && (In_KeyEvent(VK_LBUTTON) || In_KeyEvent(VK_RBUTTON)))IsInput = false;//鼠标解除输入状态
                }
            }
            if (DetectMousePos)Mouse_Icon = IDC_IBEAM;//输入框鼠标图标
            In_DrawRect(BlockPos.x + 53, BlockPos.y - 9 + 30 * LineRow, 234, 27, { 0,0,0 });
            In_DrawRect(BlockPos.x + 54, BlockPos.y - 8 + 30 * LineRow, 232, 25, { 60,60,60 });
            if (DetectMousePos || IsInput)In_DrawGradientRect(BlockPos.x + 55, BlockPos.y + 30 * LineRow - 7, 230, 23, { 15,15,15 }, Global_EasyGUI_Color / 6, true);
            else In_DrawGradientRect(BlockPos.x + 55, BlockPos.y + 30 * LineRow - 7, 230, 23, { 15,15,15 }, Global_EasyGUI_Color / 8, true);
            if (!IsInput && DrawString == "")In_DrawString(BlockPos.x + 63, 10000 + BlockPos.y + 4 + 30 * LineRow, NormalText, { 50,50,50 }, Global_EasyGUI_Font, Global_EasyGUI_FontSize);//默认显示文字
            else {//已输入的文字
                In_DrawString(BlockPos.x + 64, 10000 + BlockPos.y + 5 + 30 * LineRow, DrawString, { 0,0,0 }, Global_EasyGUI_Font, Global_EasyGUI_FontSize);
                In_DrawString(BlockPos.x + 63, 10000 + BlockPos.y + 4 + 30 * LineRow, DrawString, { 200,200,200 }, Global_EasyGUI_Font, Global_EasyGUI_FontSize);
            }
            return m_String;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
    };
}