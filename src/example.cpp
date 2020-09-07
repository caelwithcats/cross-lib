#include "cross.h"
//#include "cross_gui.hpp"
cross_gui myGui;
void secWinSetup(){
    myGui.cross_createButton(20,60,100,20,"Click this one too","button2","secWin");
    myGui.cross_setWindowTitle("hi the title was changed","secWin");
}
void setupGUI(){
    crossStd::point2d curPos = myGui.getCursorPositionOnMonitor();
    std::cout << "Cursor position = x:" << curPos.x << " y:" << curPos.y << std::endl;
    std::cout << "Window size: width is " << myGui.getWindowWidth("mui") << "px and the height is " << myGui.getWindowHeight("mui") << "px" << std::endl;
    crossStd::point3d winPos = myGui.getWindowPosition("mui");
    std::cout << "Window positon: x:" << winPos.x << " y:" << winPos.y << std::endl;
    myGui.cross_setWindowTitle("Title was changed","mui");
    myGui.cross_createButton(20,20,100,32,"Click Me!","button","mui");
    std::cout << "Button Height = " << myGui.getControlHeight("button") << ", Width = " << myGui.getControlWidth("button") << std::endl;
    myGui.cross_createButton(20,60,100,20,"Click Me too!","button2","mui");
    myGui.cross_changeButtonText("button","button text changed");
    myGui.cross_createTextbox(20,130,100,20,"Label", "label1","mui");
    myGui.cross_createCheckbox(20,90,100,32,"check me","check","mui");
    myGui.cross_createSlider(20,150,200,30,"slider",true,50,100,"slider1","mui");
    int msgBox = myGui.cross_messagebox("Welcome to the interactive tour! This will guide you through the features in crossLib","Thank YOU!",cross_gui::crossButton_AbortRetryIgnore,cross_gui::crossIcon_Info,"mui");
    if(msgBox == cross_gui::crossMessageboxResult_OK){
        printf("OK was pressed.\n");
    }else if(msgBox == cross_gui::crossMessageboxResult_Cancel){
        printf("CANCEL was pressed.\n");
    }
    else if(msgBox == cross_gui::crossMessageboxResult_Abort){
        printf("ABORT was pressed.\n");
    }else if(msgBox == cross_gui::crossMessageboxResult_Retry){
        printf("RETRY was pressed.\n");
    }else if(msgBox == cross_gui::crossMessageboxResult_Ignore){
        printf("IGNORE was pressed.\n");
    }
    myGui.cross_setCheckboxState("check", true);
    sleep(2);
    std::cout << myGui.isWindowFocused("mui") << std::endl;
}
void repeatGUI(crossStd::crossEvent eventArgs){
    /*if(eventArgs.typeOfEvent == "ButtonPress"){
        std::cout << "Button " + eventArgs.from + " Clicked" << std::endl;

    }if(eventArgs.typeOfEvent == "Hover"){
        myGui.cross_changeButtonText("myButton","hello");
        myGui.cross_changeButtonText("myButton","hello world");

    }*/
};
int main(){
    crossStd::time_obj myTimeObject;
    std::cout << myTimeObject.getDay();
    std::cout << "/";
    std::cout << myTimeObject.getMonth();
    std::cout << "/";
    std::cout << myTimeObject.getYear() << std::endl;
    std::cout << "\n";
    std::cout << myTimeObject.getTwentyFourHourTime_Hours();
    std::cout << ":";
    std::cout << myTimeObject.getTwentyFourHourTime_Minutes() << std::endl;
    crossStd::compiler_info myCompilerInfo;
    std::cout << myCompilerInfo.getCompilerTargetOS() + " " + myCompilerInfo.getCompilerTargetArchitecture() << std::endl;
    myGui.cross_setupcode = setupGUI;
    // Important feature comming soon: Events
    //myGui.cross_repeatcode = repeatGUI;
    // mui: my user interface
    myGui.cross_createWindow(500,500,"Hello","mui");
    return 0;
}
