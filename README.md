# CrossLib
CrossLib is a C++ API specificly made for compiling using a cross compiler. This will allow you to compile your code on multiple operating systems (linux and windows). For more infomation go to [link to be decided].

The source code for CrossLib can be found in `src/cross.h`.
To install CrossLib, you will need to install the dependencies

```shell-script
sudo apt-get -y install libgtk-3-dev mingw-w64 g++ gcc build-essential libx11-dev
```
## Creating your first graphical application
Clone the CrossLib repository by typing in your terminal
```shell-script
git clone https://github.com/caelwithcats/cross-lib.git
```
A newly created folder called `cross-lib` should be created

Copy the the `cross.h` and `cross-features.h` files from the `cross_apis_r` folder into project. 
To import CrossLib into your existing C++ project add this line to your C++ file

```c++
#include <cross.h>
```
And that's it you now have CrossLib installed in your C++ project.
CrossLib has a GUI framework called CrossGUI. This is what we will be using to create the hello world project. Create a new C++ file called `crossExample.cpp` and add the following code to it:

```c++
#include "cross.h"
cross_gui myGui;

void setupGUI(){
    myGui.cross_createButton(20,20,100,32,"Click Me!","button","mui");
    myGui.cross_changeButtonText("button","button text changed");
    myGui.cross_createButton(20,60,100,20,"Click Me too!","button2","mui");
    myGui.cross_createTextbox(20,130,100,20,"Label", "label1","mui");
    myGui.cross_createCheckbox(20,90,100,32,"check me","check","mui");
    myGui.cross_createSlider(20,150,200,30,"slider",true,50,100,"slider1","mui");
    int msgBox = myGui.cross_messagebox("Welcome to crossLib!","Welcome",cross_gui::crossButton_OK,cross_gui::crossIcon_Info,"mui");
    if(msgBox == cross_gui::crossMessageboxResult_OK){
        printf("OK was pressed.\n");
    }else if(msgBox == cross_gui::crossMessageboxResult_Cancel){
        printf("CANCEL was pressed.\n");
    }
}
int main(){
    // mui: my user interface
    myGui.cross_setupcode = setupGUI;
    myGui.cross_createWindow(500,500,"Hello","mui");
    return 0;
}
```

Copy the `compile.sh` file from the the `cross_apis_r` folder and build using one of these commands

Compile for Windows using:

    bash compile.sh win32 64
Compile for Linux:

    bash compile.sh linux 64
Run using

```shell-script
./out # for linux
wine windows-out.exe # test in WINE if installed
```
## Additional infomation about CrossLib

### CrossGUI
CrossGUI provides tools and functions to create cross platform Graphical User Interfaces (or GUIs). CrossGUI uses GTK3 (native linux GUI framework) and the win32 api. Using these two it has compatibility for Linux and Windows.

### CrossStd
CrossStd is a general purpose libary that provides tools and features that work cross platform. 

----------------
## To-do

* [ ] Add a reliable input system. Senses mouse clicks, hover events,etc
