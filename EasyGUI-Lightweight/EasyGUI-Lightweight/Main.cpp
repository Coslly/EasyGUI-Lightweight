#include "EasyGUI.h"
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
        if (!GUI_Variable.Window_Move())//MoveWindow Funtion
        {
            GUI_Variable.GUI_BackGround(true);//BackGround
            GUI_Variable.GUI_Block_Panel<class CALSS_EasyGUI_1>(30, 30, 100, 300, "Panel", { "Panel 1","Panel 2","Panel 3" }, UI_PanelSelector);
            if (UI_PanelSelector == 0)//Panel 1 Screen
            {
                const auto Block = GUI_Variable.GUI_Block(160, 30, 300, "Block");//Block
                GUI_Variable.GUI_Checkbox(Block, 1, "This is a Checkbox", UI_Checkbox);
                GUI_Variable.GUI_KeySelector<class CALSS_EasyGUI_2>(Block, 1, UI_KeySelector);
                GUI_Variable.GUI_Slider<int, class CALSS_EasyGUI_3>(Block, 2, "Slider int", 0, 10, UI_Slider_int);
                GUI_Variable.GUI_Slider<float, class CALSS_EasyGUI_4>(Block, 3, "Slider float", 0, 10, UI_Slider_float);
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
                GUI_Variable.GUI_Tip(Block, 1, "Some tips");
            }
            else if (UI_PanelSelector == 1)//Panel 2 Screen
            {
                const auto Block = GUI_Variable.GUI_Block(160, 30, 300, "Block");//Block
                GUI_Variable.GUI_InputText<class CALSS_EasyGUI_5>(Block, 1, UI_InputText);
                GUI_Variable.GUI_List(Block, 2, { "Hello","C++","Java","CS","Windows" }, UI_List);
            }
            GUI_Variable.Draw_GUI(UI_InvertScreenColor);
        }
    }
}