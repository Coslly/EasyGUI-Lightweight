#include "EasyGUI.h"
int main()
{
    ShowWindow(GetConsoleWindow(), true);//ShowConsoleWindow
    EasyGUI::EasyGUI GUI_Variable;//Initialize GUI variables
    GUI_Variable.Window_Create(590, 360, L"Test Windows", false);
    GUI_Variable.Window_SetAlpha(250);
    GUI_Variable.Global_Set_EasyGUI_Color({ 200,200,255 });
    while (1)
    {
        static BOOL UI_Checkbox = false;
        static int UI_Slider_int = 5;
        static float UI_Slider_float = 5;
        static BOOL UI_Button = false;
        static int UI_KeySelector = 4;
        static vector<int> UI_ColorSelector = { 255,255,255 };
        static vector<float> UI_PosSelector = { 0.23,100,1000 };
        static int UI_PanelSelector = 0;
        GUI_Variable.Global_Set_EasyGUI_Color(UI_ColorSelector);
        if (!GUI_Variable.Window_Move())//MoveWindow Funtion
        {
            GUI_Variable.GUI_BackGround();//BackGround
            GUI_Variable.GUI_Block_Panel(30, 30, 100, 300, "Panel", { "Panel 1","Panel 2","Panel 3" }, UI_PanelSelector);
            if (UI_PanelSelector == 0)
            {
                vector<int> Block = GUI_Variable.GUI_Block(160, 30, 300, "Block");//Block
                GUI_Variable.GUI_Checkbox(Block, 1, "This is a Checkbox.", UI_Checkbox);
                GUI_Variable.GUI_KeySelector<class A_1>(Block, 1, UI_KeySelector);
                GUI_Variable.GUI_Slider<int, class A_2>(Block, 2, "Slider int", 0, 10, UI_Slider_int);
                GUI_Variable.GUI_Slider<float, class A_3>(Block, 3, "Slider float", 0, 10, UI_Slider_float);
                GUI_Variable.GUI_Button(Block, 4, "Button", 90, UI_Button);
                static int ButtonClick = 0;
                if (UI_Button)
                {
                    ButtonClick++;
                    Beep(100, 20);
                }
                GUI_Variable.GUI_Text(Block, 5, "Button: " + to_string(ButtonClick));
                GUI_Variable.GUI_Text(Block, 6, "Main Color");
                GUI_Variable.GUI_ColorSelector(Block, 6, UI_ColorSelector);
                GUI_Variable.GUI_Text(Block, 7, "Pos");
                GUI_Variable.GUI_PosSelector(Block, 7, UI_PosSelector);
                GUI_Variable.GUI_Tips(Block, 1, "Some Tips.");
            }
            GUI_Variable.Draw_GUI();
        }
    }
}