#include "EasyGUI.h"
int main()
{
    ShowWindow(GetConsoleWindow(), true);//ShowConsoleWindow
    EasyGUI::EasyGUI GUI_Variable;//Initialize GUI variables
    GUI_Variable.Window_Create(500, 500, L"Test Window", false);
    GUI_Variable.Window_SetAlpha(240);
    GUI_Variable.Global_Set_EasyGUI_Color({ 200,200,255 });
    vector<int> Block;
    while (1)
    {
        static BOOL Checkbox = false;
        static int Slider_int = 5;
        static float Slider_float = 5;
        static BOOL Button = false;
        static int KeySelect = 5;
        if (!GUI_Variable.Window_Move())//MoveWindow Funtion
        {
            GUI_Variable.GUI_BackGround(1367);//BackGround
            Block = GUI_Variable.GUI_Block(30, 30, 400, "Block");//Block
            GUI_Variable.GUI_Checkbox(Block, 1, "This is a Checkbox.", Checkbox);
            GUI_Variable.GUI_KeySelect<class A_1>(Block, 1, KeySelect);
            GUI_Variable.GUI_Slider<int, class A_2>(Block, 2, "Slider int", 0, 10, Slider_int);
            GUI_Variable.GUI_Slider<float, class A_3>(Block, 3, "Slider float", 0, 10, Slider_float);
            GUI_Variable.GUI_Button(Block, 4, "Button", 90, Button);
            static int ButtonClick = 0;
            if (Button)
            {
                ButtonClick++;
                Beep(100, 20);
            }
            GUI_Variable.GUI_Text(Block, 5, "Button: " + to_string(ButtonClick));
            GUI_Variable.GUI_Tips(Block, 1, "Some Tips.");
            GUI_Variable.Draw_GUI();
        }
    }
}