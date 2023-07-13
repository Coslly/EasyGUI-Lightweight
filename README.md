# 🤖EasyGUI
Lightweight GUI library for console programs



Which projects use it?
- [TaHack](https://github.com/Coslly/TaHack.git)
# 😀Features
- For people(beginner,student)
- C++ worker
- Fast
- Simple
- Can be modified at will.
# 🥰Showcase(example)
![image](https://github.com/Coslly/EasyGUI-Lightweight/blob/main/PAA.png?raw=true)
# 😧How to use?
### - Initialization
```cpp
//Initialize GUI variables
EasyGUI::EasyGUI GUI_Variable;
GUI_Variable.Window_Create(500, 500, L"Test Windows", false);
```
### - Add controls
You need to add a control block.

If you add the Window_Move() function inside the loop then you don't need to add the Sleep() function
```cpp
while (1)
{
    //Variable
    static BOOL UI_Checkbox = false;
    static BOOL UI_Button = false;

    GUI_Variable.GUI_BackGround();//BackGround

    vector<int> Block = GUI_Variable.GUI_Block(30, 30, 300, "Test Block");//Block

    GUI_Variable.GUI_Checkbox(Block, 1, "Checkbox", UI_Checkbox);
    GUI_Variable.GUI_Button(Block, 2, "Button", 90, UI_Button);
    //Draw
    GUI_Variable.Draw_GUI();
    Sleep(1);
}
```
Window_Move() function
```cpp
while (1)
{
    //Variable
    static BOOL UI_Checkbox = false;
    static BOOL UI_Button = false;

    GUI_Variable.GUI_BackGround();//BackGround

    if (!GUI_Variable.Window_Move())//MoveWindow Funtion
    {
        vector<int> Block = GUI_Variable.GUI_Block(30, 30, 300, "Test Block");//Block

        GUI_Variable.GUI_Checkbox(Block, 1, "Checkbox", UI_Checkbox);
        GUI_Variable.GUI_Button(Block, 2, "Button", 90, UI_Button);
        //Draw
        GUI_Variable.Draw_GUI();
    }
}
```
### - Function special class
When the same function is executed, different classes need to be entered in the template. Of course you can create. :)
```cpp
while (1)
{
    //Variable
    static int UI_Slider_1 = 0;
    static int UI_Slider_2 = 10;

    GUI_Variable.GUI_BackGround();//BackGround

    vector<int> Block = GUI_Variable.GUI_Block(30, 30, 300, "Test Block");//Block

    GUI_Variable.GUI_Slider<int, class GUI_Class_1>(Block, 1, "Slider 1", 0, 10, UI_Slider_1);
    GUI_Variable.GUI_Slider<int, class GUI_Class_2>(Block, 1, "Slider 2", 0, 10, UI_Slider_2);
    //Draw
    GUI_Variable.Draw_GUI();
    Sleep(1);
}
```
### - Overall code
```cpp
EasyGUI::EasyGUI GUI_Variable;//Initialize GUI variables
GUI_Variable.Window_Create(500, 300, L"Test Windows", false);
while (1)
{
    //Variable
    static BOOL UI_Checkbox = false;
    static int UI_Slider = 0;
    static BOOL UI_Button = false;
    if (!GUI_Variable.Window_Move())//MoveWindow Funtion
    {
        //BackGround
        GUI_Variable.GUI_BackGround();

        vector<int> Block = GUI_Variable.GUI_Block(30, 30, 200, "Block");//Block

        GUI_Variable.GUI_Checkbox(Block, 1, "Checkbox", UI_Checkbox);
        GUI_Variable.GUI_Slider<int, class GUI_Class_1>(Block, 2, "Slider", 0, 10, UI_Slider);
        GUI_Variable.GUI_Button(Block, 3, "Button", 90, UI_Button);

        //Draw
        GUI_Variable.Draw_GUI();
    }
}
```
