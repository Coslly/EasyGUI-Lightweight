# 🤖EasyGUI
Lightweight GUI library for console programs
# 😀Features
- For people(beginner,student)
- C++ worker
- Fast
- Simple
- Can be modified at will.
# 🥰Showcase(example)
![image](https://github.com/Coslly/EasyGUI-Lightweight/blob/main/PAA.png?raw=true)
# 😧How to use?
### Initialization
```cpp
//Initialize GUI variables
EasyGUI::EasyGUI GUI_Variable;
GUI_Variable.Window_Create(1000, 1000, L"Test Windows", true);
```
### Add controls
You need to add a control block.

If you add the Window_Move() function inside the loop then you don't need to add the Sleep() function
```cpp
while (1)
{
    //Variable
    static BOOL UI_Checkbox = false;
    static BOOL UI_Button = false;

    vector<int> Block = GUI_Variable.GUI_Block(30, 30, 300, "Test Block");//Block

    GUI_Variable.GUI_Checkbox(Block, 1, "Checkbox.", UI_Checkbox);
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
    if (!GUI_Variable.Window_Move())//MoveWindow Funtion
    {
        vector<int> Block = GUI_Variable.GUI_Block(30, 30, 300, "Test Block");//Block

        GUI_Variable.GUI_Checkbox(Block, 1, "Checkbox.", UI_Checkbox);
        GUI_Variable.GUI_Button(Block, 2, "Button", 90, UI_Button);
        //Draw
        GUI_Variable.Draw_GUI();
    }
}
```
