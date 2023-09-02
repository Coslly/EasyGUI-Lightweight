#include "EasyGUI.h"
int main()
{
    ShowWindow(GetConsoleWindow(), true);//Show Console Window
    EasyGUI::EasyGUI GUI_Variable;//Initialize GUI variables
    GUI_Variable.Window_Create(590, 360, "Test Windows", true);
    GUI_Variable.Window_SetAlpha(250);
    while (1)
    {
        static BOOL UI_Checkbox = false;
        static int UI_Slider_int = 5;
        static float UI_Slider_float = 5;
        static BOOL UI_Button = false;
        static BOOL UI_Button_Small = false;
        static int UI_KeySelector = 4;
        static vector<int> UI_ColorSelector = { 255,255,255 };
        static vector<float> UI_PosSelector = { 0.23,100,1000 };
        static int UI_PanelSelector = 0;
        EasyGUI::EasyGUI_IO GUI_IO = GUI_Variable.Get_IO();//Get Global Input/Output Value
        if (!GUI_Variable.Window_Move())//MoveWindow Funtion (You must add!! cause it have  MessageLoop)
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
                if (UI_Button || UI_Button_Small)ButtonClick++;
                GUI_Variable.GUI_Text(Block, 5, "Button: " + to_string(ButtonClick));
                GUI_Variable.GUI_Text(Block, 6, "Main Color");
                GUI_Variable.GUI_ColorSelector(Block, 6, UI_ColorSelector);
                GUI_Variable.Global_Set_EasyGUI_Color(UI_ColorSelector);
                GUI_Variable.GUI_Text(Block, 7, "Pos");
                GUI_Variable.GUI_PosSelector(Block, 7, UI_PosSelector);
                GUI_Variable.GUI_Button_Small(Block, 2, UI_Button_Small);
                GUI_Variable.GUI_Text(Block, 8, "FPS: " + to_string(GUI_IO.DrawFPS));
                GUI_Variable.GUI_Tips(Block, 1, "Some Tips.");
            }
            GUI_Variable.Draw_GUI();
        }
    }
}