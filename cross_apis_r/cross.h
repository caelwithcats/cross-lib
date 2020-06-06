//#pragma once

#ifdef __MINGW32__ || _WIN32
    #include <windows.h>
    #include <string.h>
    #include <tchar.h>
    #include <commctrl.h>
#else
    #include <time.h>
    #include <X11/Xlib.h>
    #include <gtk/gtk.h>
    #include <unistd.h>
    #include <thread>
#endif

// Put headers here that are not OS dependent and are used by both operating systems
#include "cross_features.h"
#include <cstddef>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <cstring>
#include <type_traits>
#include <random>
#include <cstdlib>
#include <ctime>
#include <math.h>
#define IsLINUX 1
#define IsWIN 0
#ifdef _WIN32
    #undef IsWIN
    #define IsWIN 1
    #undef IsLINUX
    #define IsLINUX 0
#endif

#ifdef __linux__
    #undef IsLINUX
    #define IsLINUX 1
    #undef IsWIN
    #define IsWIN 0
#endif

// Declare functions
#ifdef IsWIN
// Windows Functions
#endif
// Typedefs

namespace crossStd{
class randomClass{
public:
    void InitSeed(){
        srand(time(0));
    }
    int EasyRandomNumberGenerator(int min, int max){
        //srand(time(0));
        return rand() % max+min;
    }

};


struct crossEvent
{
    std::string typeOfEvent;
    std::string from;
};
#if CROSS_FEATURES_EXTRA
struct executable_info{
    std::string getExeName(){
        #if IsWIN
            char szExeFileName[MAX_PATH]; 
            GetModuleFileName(NULL, szExeFileName, MAX_PATH);
            return szExeFileName;
        #endif
        #if IsLINUX
        #endif
    }
};
struct compiler_info{
    std::string getCompilerTargetOS(){
        #ifdef _WIN32
            return "Win32";
        #endif
        #ifdef _WIN64
            return "Win64";
        #endif
        #if IsLINUX
            return "Linux";
        #endif
    }
    std::string getCompilerTargetArchitecture(){
        // for windows cross compiler
        #if _WIN32 || _WIN64
        #if _WIN64
        #define ENVIRONMENT64
        #else
        #define ENVIRONMENT32
        #endif
        #endif

        // for Normal gcc compiler
        #if __GNUC__
        #if __x86_64__ || __ppc64__
        #define ENVIRONMENT64
        return "x64";
        #else
        #define ENVIRONMENT32
        return "x32";
        #endif
        #endif
    };
};
#endif
// Sleep for a certain amount of time in milliseconds
void sleepf(unsigned int sleepTime){
    #if IsLINUX
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    #endif
    #if IsWIN
    Sleep(sleepTime);
    #endif
}
class point2d{
    public:
        int x = 0;
        int y = 0;
};
class point3d{
    public:
        int x = 0;
        int y = 0;
        int z = 0;
};
struct time_obj
{
    int getDay(){
        // Code
        #if IsWIN
            SYSTEMTIME lt = {0};
            GetLocalTime(&lt);
            return lt.wDay;
        #endif
        #if IsLINUX
            time_t linuxTime = time(NULL);
            struct tm *time_result = localtime(&linuxTime);
            return time_result->tm_mday;
        #endif
    }
    int getMonth(){
        // Code
        // The month index for linux starts at 0 and Windows starts at 1.
        // This inconsistency can be fixed by adding 1 to the linux month
        #if IsWIN
            SYSTEMTIME lt = {0};
            GetLocalTime(&lt);
            return lt.wMonth;
        #endif
        #if IsLINUX
            time_t linuxTime = time(NULL);
            struct tm *time_result = localtime(&linuxTime);
            return time_result->tm_mon + 1;
        #endif
    }
    int getYear(){
        // Code
        #if IsWIN
            SYSTEMTIME lt = {0};
            GetLocalTime(&lt);
            return lt.wYear;
        #endif
        #if IsLINUX
            time_t linuxTime = time(NULL);
            struct tm *time_result = localtime(&linuxTime);
            return time_result->tm_year + 1900;
        #endif
    }
    int getTwentyFourHourTime_Hours(){
        // Code
        #if IsWIN
            SYSTEMTIME lt = {0};
            GetLocalTime(&lt);
            return lt.wHour;
        #endif
        #if IsLINUX
            time_t linuxTime = time(NULL);
            struct tm *time_result = localtime(&linuxTime);
            return time_result->tm_hour;
        #endif
    }
    int getTwentyFourHourTime_Minutes(){
        // Code
        #if IsWIN
            SYSTEMTIME lt = {0};
            GetLocalTime(&lt);
            return lt.wMinute;
        #endif
        #if IsLINUX
            time_t linuxTime = time(NULL);
            struct tm *time_result = localtime(&linuxTime);
            return time_result->tm_min;
        #endif
    }
};

};

#if CROSS_FEATURES_GUI

#if IsWIN
// Values from the Windows API will be passed into these variables
HINSTANCE win_hInst;
HINSTANCE win_hPrevInst;
HWND win_hWnd;
LPSTR win_args;
int win_ncmdshow;
int winMain_returnValue;
WPARAM win_wp;
UINT win_msg;
HINSTANCE win_prevInst;
//void(*win_repeatcode)();

//win_repeatcode = nullptr;
LRESULT CALLBACK WindowProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args,int ncmdshow){
    win_hInst = hInst;
    win_hPrevInst = hPrevInst;
    win_args = args;
    win_ncmdshow = ncmdshow;

    winMain_returnValue = 0;
    return winMain_returnValue;
}
LRESULT CALLBACK WindowProc(HWND hWnd,UINT msg,WPARAM wp,LPARAM lp){
    win_hWnd = hWnd;
    win_wp = wp;
    switch (msg)
    {
    case WM_CREATE:
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    
    default:
        return DefWindowProcW(hWnd,msg,wp,lp);
        break;
    }
}
#endif

// Creates a GUI
class cross_gui{
private:
#if IsWIN
    typedef HWND cross_window_type;
    typedef HWND cross_control_type;
#endif

#if IsLINUX
    // Typedefs
    typedef GtkWidget* cross_control_type;
    typedef GtkWidget* cross_window_type;
#endif
public:

enum CrossMessageBoxButtons
{
    crossButton_AbortRetryIgnore,
    crossButton_OK,
    crossButton_OKCancel,
    crossButton_RetryCancel,
    crossButton_YesNo,
    crossButton_YesNoCancel,
    crossButton_CancelRetryContinue,
    crossButton_Help,
    crossButton_NoButtons
};
enum CrossMessageBoxResult
{
    crossMessageboxResult_OK,
    crossMessageboxResult_Cancel,
    crossMessageboxResult_Abort,
    crossMessageboxResult_Retry,
    crossMessageboxResult_Ignore,
    crossMessageboxResult_No,
    crossMessageboxResult_Continue,
    crossMessageboxResult_Help,
    crossMessageboxResult_Yes,
};
enum CrossMessageBoxIcons
{
    crossIcon_Error,
    crossIcon_Question,
    crossIcon_Warning,
    crossIcon_Info,
    crossIcon_NoIcon
};
#if IsWIN
    HWND hwnd;
    std::map<std::string, cross_window_type> windows;
    std::map<std::string, std::pair<cross_control_type, int>> controls;
#endif

#ifdef _MINGW32

#endif
#ifdef _MINGW32

#endif
bool useFlatAppearance = false;
void(*cross_setupcode)();
void(*cross_repeatcode)(crossStd::crossEvent event);

#if IsLINUX
std::map<std::string, cross_control_type> controls;
std::map<std::string, std::pair<cross_window_type,cross_control_type>> windows;
#endif


std::string cross_openfiledialog(std::string title,std::string filter,std::string windowName){
/*    #ifdef _WIN32
        OPENFILENAME openFileName;

        char file_name[100];
        ZeroMemory(&openFileName,sizeof(OPENFILENAME));
        openFileName.lStructSize = sizeof(OPENFILEMNAME);
        /*openFileName.hwndOwner = // something 
        openFileName.lpstrFile = file_name;
        openFileName.lpstrFile[0] = '\0';
        openFileName.nMaxFile = 100;
        openFileName.lpstrFilter = // implement a universial non-OS-specific file filter
    #endif
    */
}


int cross_messagebox(std::string message, std::string title,CrossMessageBoxButtons buttons,CrossMessageBoxIcons icon, std::string windowName = ""){
        #if IsWIN
            long int dialogIcon = NULL;
            long int dialogButtons = NULL;
            if(icon == crossIcon_Error){
                dialogIcon = MB_ICONERROR;
            }
            if(icon == crossIcon_Info){
                dialogIcon = MB_ICONINFORMATION;
            }
            if(icon == crossIcon_Warning){
                dialogIcon = MB_ICONWARNING;
            }
            if(icon == crossIcon_Question){
                dialogIcon = MB_ICONQUESTION;
            }
            if(buttons == crossButton_AbortRetryIgnore){
                dialogButtons = MB_ABORTRETRYIGNORE;
            }
            if(buttons == crossButton_OK){
                dialogButtons = MB_OK;
            }
            if(buttons == crossButton_OKCancel){
                dialogButtons = MB_OKCANCEL;
            }
            if(buttons == crossButton_RetryCancel){
                dialogButtons = MB_RETRYCANCEL;
            }
            if(buttons == crossButton_YesNo){
                dialogButtons = MB_YESNO;
            }
            if(buttons == crossButton_YesNoCancel){
                dialogButtons = MB_YESNOCANCEL;
            }
            if(buttons == crossButton_CancelRetryContinue){
                dialogButtons = MB_CANCELTRYCONTINUE;
            }
            if(buttons == crossButton_Help){
                dialogButtons = MB_HELP;
            }
            if(buttons == crossButton_NoButtons){
            }
            bool dependentOnMainWindow;
            if(windowName == ""){
                dependentOnMainWindow = false;
            }else{
                dependentOnMainWindow = true;
            }
            int ret = MessageBox((dependentOnMainWindow ? windows[windowName] : NULL),message.c_str(),title.c_str(),dialogButtons | dialogIcon);
            switch (ret)
            {
            case IDYES:
                /* code */
                return crossMessageboxResult_Yes;
                break;
            case IDNO:
                return crossMessageboxResult_No;
                break;
            case IDCANCEL:
                return crossMessageboxResult_Cancel;
                break;
            case IDCONTINUE:
                return crossMessageboxResult_Continue;
                break;
            case IDIGNORE:
                return crossMessageboxResult_Ignore;
                break;
            case IDOK:
                return crossMessageboxResult_OK;
                break;
            case IDRETRY:
                return crossMessageboxResult_Retry;
                break;
            case IDABORT:
                return crossMessageboxResult_Abort;
                break;
            }
        #endif
        #if IsLINUX
            std::pair<cross_window_type,cross_control_type> &windowVals = windows[windowName];
            GtkWidget *dialog;
            GtkMessageType dialogIcon = GTK_MESSAGE_OTHER;
            if(icon == crossIcon_Error){
                dialogIcon = GTK_MESSAGE_ERROR;
            }
            if(icon == crossIcon_Info){
                dialogIcon = GTK_MESSAGE_INFO;
            }
            if(icon == crossIcon_Warning){
                dialogIcon = GTK_MESSAGE_WARNING;
            }
            if(icon == crossIcon_Question){
                dialogIcon = GTK_MESSAGE_QUESTION;
            }
            GtkWidget *hostWindow;
            if(windowName == ""){
                hostWindow = NULL;
            }else{
                hostWindow = windowVals.first;
            }
            dialog =  gtk_message_dialog_new(GTK_WINDOW(hostWindow), GTK_DIALOG_DESTROY_WITH_PARENT,dialogIcon,GTK_BUTTONS_NONE,message.c_str(),NULL,g_strerror(errno));
            if(buttons == crossButton_AbortRetryIgnore){
                gtk_dialog_add_button(GTK_DIALOG(dialog), "Abort",GTK_RESPONSE_NO);
                gtk_dialog_add_button(GTK_DIALOG(dialog), "Retry",GTK_RESPONSE_YES);
                gtk_dialog_add_button(GTK_DIALOG(dialog), "Ignore",GTK_RESPONSE_OK);
            }
            if(buttons == crossButton_OK){
                gtk_dialog_add_button(GTK_DIALOG(dialog), "OK",GTK_RESPONSE_OK);
            }
            if(buttons == crossButton_OKCancel){
                gtk_dialog_add_button(GTK_DIALOG(dialog), "OK",GTK_RESPONSE_OK);
                gtk_dialog_add_button(GTK_DIALOG(dialog), "Cancel",GTK_RESPONSE_CANCEL);
            }
            if(buttons == crossButton_RetryCancel){
                gtk_dialog_add_button(GTK_DIALOG(dialog), "Retry",GTK_RESPONSE_APPLY);
                gtk_dialog_add_button(GTK_DIALOG(dialog), "Cancel",GTK_RESPONSE_CANCEL);
            }
            if(buttons == crossButton_YesNo){
                gtk_dialog_add_button(GTK_DIALOG(dialog), "Yes",GTK_RESPONSE_YES);
                gtk_dialog_add_button(GTK_DIALOG(dialog), "No",GTK_RESPONSE_NO);
            }
            if(buttons == crossButton_YesNoCancel){
                gtk_dialog_add_button(GTK_DIALOG(dialog), "Yes",GTK_RESPONSE_YES);
                gtk_dialog_add_button(GTK_DIALOG(dialog), "No",GTK_RESPONSE_NO);
                gtk_dialog_add_button(GTK_DIALOG(dialog), "Cancel",GTK_RESPONSE_CANCEL);
            }
            if(buttons == crossButton_CancelRetryContinue){
                gtk_dialog_add_button(GTK_DIALOG(dialog), "Cancel",GTK_RESPONSE_CANCEL);
                gtk_dialog_add_button(GTK_DIALOG(dialog), "Retry",GTK_RESPONSE_APPLY);
                gtk_dialog_add_button(GTK_DIALOG(dialog), "Continue",GTK_RESPONSE_YES);
            }
            if(buttons == crossButton_Help){
                gtk_dialog_add_button(GTK_DIALOG(dialog), "Help",0);
            }
            if(buttons == crossButton_NoButtons){
                // A button must be added because Windows doesn't allow no buttons
                gtk_dialog_add_button(GTK_DIALOG(dialog), "OK",0);
            }
            gtk_window_set_title(GTK_WINDOW(dialog),title.c_str());
            gint ret = gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(GTK_WIDGET(dialog));
            if(ret == GTK_RESPONSE_CLOSE){
                    return crossMessageboxResult_Cancel;
            }
            if(buttons == crossButton_AbortRetryIgnore){
                if(ret == GTK_RESPONSE_NO){
                    return crossMessageboxResult_Abort;
                }
                if(ret == GTK_RESPONSE_YES){
                    return crossMessageboxResult_Retry;
                }
                if(ret == GTK_RESPONSE_OK){
                    return crossMessageboxResult_Ignore;
                }
            }
            else if(buttons == crossButton_OK){
                if(ret == GTK_RESPONSE_OK){
                    return crossMessageboxResult_OK;
                }
            }else if(buttons == crossButton_OKCancel){
                if(ret == GTK_RESPONSE_OK){
                    return crossMessageboxResult_OK;
                }
                if(ret == GTK_RESPONSE_CANCEL){
                    return crossMessageboxResult_Cancel;
                }
            }
            else if(buttons == crossButton_RetryCancel){
                if(ret == GTK_RESPONSE_APPLY){
                    return crossMessageboxResult_Retry;
                }
                if(ret == GTK_RESPONSE_CANCEL){
                    return crossMessageboxResult_Cancel;
                }
            }else if(buttons == crossButton_YesNo){
                if(ret == GTK_RESPONSE_YES){
                    return crossMessageboxResult_Yes;
                }
                if(ret == GTK_RESPONSE_NO){
                    return crossMessageboxResult_No;
                }
            }else if(buttons == crossButton_YesNoCancel){
                if(ret == GTK_RESPONSE_YES){
                    return crossMessageboxResult_Yes;
                }
                if(ret == GTK_RESPONSE_NO){
                    return crossMessageboxResult_No;
                }
                if(ret == GTK_RESPONSE_CANCEL){
                    return crossMessageboxResult_Cancel;
                }
            }else if(buttons == crossButton_CancelRetryContinue){
                if(ret == GTK_RESPONSE_CANCEL){
                    return crossMessageboxResult_Cancel;
                }
                if(ret == GTK_RESPONSE_APPLY){
                    return crossMessageboxResult_Retry;
                }
                if(ret == GTK_RESPONSE_YES){
                    return crossMessageboxResult_Continue;
                }
            }

        #endif
}
std::string getControlType(std::string controlName){
    #if IsWIN
    std::pair<cross_control_type,int> &controlVals = controls[controlName];
    TCHAR className[128];
    GetClassName(controlVals.first,className,128);
    std::cout << className << std::endl;
    LONG controlStyles = GetWindowLong(controlVals.first, GWL_STYLE);
    if(className == "Button"){
        return "button";
    }if(className == "msctls_trackbar32"){
        return "slider";
    }if(className == "Edit"){
        return "textbox";
    }if(className == "Static"){
        return "label";
    }
    return "unknown";
    #endif
}
void cross_changeButtonText(std::string control, std::string text){
        #if IsLINUX
            gtk_button_set_label(GTK_BUTTON(controls[control]), text.c_str());
        #endif
        #if IsWIN
            std::pair<cross_control_type,int> &controlVals = controls[control];
            SetWindowText(controlVals.first,text.c_str());
            int len = GetWindowTextLength(controlVals.first) + 1;
            char* Gtext = new char[len];
            GetWindowText(controlVals.first,&Gtext[0],len);
        #endif
}
void cross_createButton(int x, int y, int width, int height, std::string text, std::string controlName, std::string windowName){
    #if IsWIN
        std::pair<cross_control_type,int> &controlVals = controls[controlName];
        std::map<std::string, std::pair<cross_control_type, int>>::iterator it = controls.begin();
        int id;
        crossStd::randomClass randGenerator;
        id = randGenerator.EasyRandomNumberGenerator(1, RAND_MAX);
        while(it != controls.end()){
            std::pair<cross_control_type,int> &itVals = controls[it->first];
            if(itVals.second == id){
                //std::cout << "the id is the same as one of another value! changing..." << std::endl;
                id = randGenerator.EasyRandomNumberGenerator(1, RAND_MAX);
            }
            it++;
        }
        std::cout << "btn id: " << id << std::endl;
        controlVals.first = CreateWindowW(L"button",std::wstring(text.begin(), text.end()).c_str(),WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, x, y,width,height,windows[windowName],(HMENU)id,NULL,NULL);
    #endif
    #if IsLINUX
        std::pair<cross_window_type,cross_control_type> &windowVals = windows[windowName];
        GtkWidget* button;
        button = gtk_button_new_with_label(text.c_str());
        controls[controlName] = button;

        gtk_fixed_put(GTK_FIXED(windowVals.second),controls[controlName],(gint)x,(gint)y);
        gtk_fixed_move(GTK_FIXED(windowVals.second),controls[controlName],(gint)x,(gint)y);
        //gtk_widget_show(windowVals.second);
        gtk_widget_set_size_request(controls[controlName],width,height);

    #endif
}
void cross_createCheckbox(int x, int y, int width, int height, std::string text, std::string controlName, std::string windowName){
    #if IsWIN 
        std::pair<cross_control_type,int> &controlVals = controls[controlName];
        controlVals.first = CreateWindowW(L"button",std::wstring(text.begin(), text.end()).c_str(),WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_CHECKBOX, x, y,width,height,windows[windowName],NULL,NULL,NULL);
    #endif
    #if IsLINUX
        std::pair<cross_window_type,cross_control_type> &windowVals = windows[windowName];
        GtkWidget* checkbox;
        checkbox = gtk_check_button_new_with_label(text.c_str());
        controls[controlName] = checkbox;

        gtk_fixed_put(GTK_FIXED(windowVals.second),controls[controlName],(gint)x,(gint)y);
        gtk_fixed_move(GTK_FIXED(windowVals.second),controls[controlName],(gint)x,(gint)y);
        //gtk_widget_show(windowVals.second);
        gtk_widget_set_size_request(controls[controlName],width,height);

    #endif
}
void cross_setCheckboxState(std::string controlName, bool isChecked){
    #if IsWIN
    std::pair<cross_control_type,int> &controlVals = controls[controlName];

    SendMessage(controlVals.first, BM_SETCHECK, isChecked ? BST_CHECKED : BST_UNCHECKED, 0);
    #endif
    #if IsLINUX
    #endif
}
void cross_createLabel(int x, int y, int width, int height, std::string text, std::string controlName, std::string windowName){
    #if IsWIN
        std::pair<cross_control_type,int> &controlVals = controls[controlName];
        controlVals.first = CreateWindowW(L"static",std::wstring(text.begin(), text.end()).c_str(),WS_VISIBLE | WS_CHILD, x, y,width,height,windows[windowName],NULL,NULL,NULL);
    #endif
    #if IsLINUX
        std::pair<cross_window_type,cross_control_type> &windowVals = windows[windowName];
        GtkWidget* checkbox;
        checkbox = gtk_label_new(text.c_str());
        controls[controlName] = checkbox;

        gtk_fixed_put(GTK_FIXED(windowVals.second),controls[controlName],(gint)x,(gint)y);
        gtk_fixed_move(GTK_FIXED(windowVals.second),controls[controlName],(gint)x,(gint)y);

        gtk_widget_set_size_request(controls[controlName],width,height);
    #endif
}
void cross_createTextbox(int x, int y, int width, int height, std::string text, std::string controlName, std::string windowName){
    #if IsWIN
        std::pair<cross_control_type,int> &controlVals = controls[controlName];

        controlVals.first = CreateWindowW(L"edit",std::wstring(text.begin(), text.end()).c_str(),WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, x, y,width,height,windows[windowName],NULL,NULL,NULL);
    #endif
    #if IsLINUX
        std::pair<cross_window_type,cross_control_type> &windowVals = windows[windowName];
        GtkWidget* checkbox;
        checkbox = gtk_entry_new();
        gint tmp_pos = 0;
        gtk_editable_insert_text (GTK_EDITABLE (checkbox), text.c_str(), -1, &tmp_pos);
        controls[controlName] = checkbox;

        gtk_fixed_put(GTK_FIXED(windowVals.second),controls[controlName],(gint)x,(gint)y);
        gtk_fixed_move(GTK_FIXED(windowVals.second),controls[controlName],(gint)x,(gint)y);

        gtk_widget_set_size_request(controls[controlName],width,height);
    #endif
}
void cross_createSlider(int x, int y, int width, int height,std::string text, bool isVertical, int defaultValue, int maxValue, std::string controlName, std::string windowName){
    #if IsWIN
        std::pair<cross_control_type,int> &controlVals = controls[controlName];
        controlVals.first = CreateWindowW(TRACKBAR_CLASSW,std::wstring(text.begin(), text.end()).c_str(),WS_VISIBLE | WS_CHILD, x, y,width,height,windows[windowName],NULL,NULL,NULL);
        SendMessageW(controlVals.first, TBM_SETPOS, FALSE, 50); 

    #endif
    #if IsLINUX
        std::pair<cross_window_type,cross_control_type> &windowVals = windows[windowName];
        GtkWidget* slider;
        GtkAdjustment *hadjustment;
        hadjustment = gtk_adjustment_new(defaultValue, 0, maxValue, 1, 10, 0); 
        slider = gtk_scale_new (GTK_ORIENTATION_HORIZONTAL,hadjustment);
        gtk_scale_set_digits (GTK_SCALE (slider), 0); 
        gtk_widget_set_vexpand(slider, TRUE);
        controls[controlName] = slider;

        gtk_fixed_put(GTK_FIXED(windowVals.second),controls[controlName],(gint)x,(gint)y);
        gtk_fixed_move(GTK_FIXED(windowVals.second),controls[controlName],(gint)x,(gint)y);

        gtk_widget_set_size_request(controls[controlName],width,height);
    #endif
}
void cross_setWindowTitle(std::string title, std::string windowName){
    #if IsWIN
    SetWindowTextW(win_hWnd,std::wstring(title.begin(), title.end()).c_str());
    #endif
    #if IsLINUX
    std::pair<cross_window_type,cross_control_type> &windowVals = windows[windowName];
    gtk_window_set_title(GTK_WINDOW(windowVals.first),title.c_str());
    #endif
}
#if linux
void gtkRunSetup(GtkWidget *widget, gpointer data){
    cross_setupcode();
}
#endif
crossStd::point3d getWindowPosition(std::string windowName){
    #if IsWIN
    //int z = 0;
    RECT rectangle;
    GetWindowRect(windows[windowName], &rectangle);
    
    crossStd::point3d resultValue;
    resultValue.x = rectangle.left;
    resultValue.y = rectangle.top;
    //resultValue.z = z;
    return resultValue;
    #endif
    #if IsLINUX
    // https://developer.gnome.org/gtk3/stable/GtkWindow.html#gtk-window-get-size
    
    std::pair<cross_window_type,cross_control_type> &windowVals = windows[windowName];
    int windowX,windowY,windowZ;
    gtk_window_get_position(GTK_WINDOW(windowVals.first),&windowX,&windowY);
    crossStd::point3d resultValue;
    resultValue.x = windowX;
    resultValue.y = windowY;
    // TODO: Z axis needs to be implemented
    //resultValue.z = z;
    return resultValue;
    #endif
}
crossStd::point2d getControlPosition(std::string controlName){
    #if IsWIN
    std::pair<cross_control_type,int> &controlVals = controls[controlName];

    RECT rectangle;
    GetWindowRect(controlVals.first, &rectangle);
    crossStd::point2d resultValue;
    resultValue.x = rectangle.left;
    resultValue.y = rectangle.top;
    return resultValue;
    #endif
    #if IsLINUX    
    GValue controlX = G_VALUE_INIT,controlY = G_VALUE_INIT;
    g_object_get_property(G_OBJECT(controls[controlName]),"x", &controlX);
    g_object_get_property(G_OBJECT(controls[controlName]),"y", &controlY);
    crossStd::point2d resultValue;
    resultValue.x = g_value_get_int(&controlX);
    resultValue.y = g_value_get_int(&controlY);

    return resultValue;
    #endif
}
int getWindowWidth(std::string windowName){
    #if IsWIN
    RECT rectangle;
    GetWindowRect(windows[windowName], &rectangle);
    return (rectangle.right - rectangle.left);
    #endif
    #if IsLINUX
    // https://developer.gnome.org/gtk3/stable/GtkWindow.html#gtk-window-get-size
    
    std::pair<cross_window_type,cross_control_type> &windowVals = windows[windowName];
    int windowW,windowH;
    gtk_window_get_size(GTK_WINDOW(windowVals.first),&windowW,&windowH);
    return windowW;
    #endif
}
int getWindowHeight(std::string windowName){
    #if IsWIN
    RECT rectangle;
    GetWindowRect(windows[windowName], &rectangle);
    return (rectangle.bottom - rectangle.top);
    #endif
    #if IsLINUX
    // https://developer.gnome.org/gtk3/stable/GtkWindow.html#gtk-window-get-size
    
    std::pair<cross_window_type,cross_control_type> &windowVals = windows[windowName];
    int windowW,windowH;
    gtk_window_get_size(GTK_WINDOW(windowVals.first),&windowW,&windowH);
    return windowH;
    #endif
}
int getControlHeight(std::string controlName){
    #if IsWIN
    std::pair<cross_control_type,int> &controlVals = controls[controlName];
    RECT controlArea;
    if(GetWindowRect(controlVals.first,&controlArea)){
        int width = controlArea.right - controlArea.left;
        int height = controlArea.bottom - controlArea.top;
        return height;
    }else{
        #if CROSS_FEATURES_DEBUG
        std::cout << "ERROR: Could not get the height of \"" << controlName << "\"" << std::endl;
        return -1;
        #endif
    }
    #endif
    #if IsLINUX
    int controlH, controlW;
    gtk_widget_get_size_request(controls[controlName],&controlW,&controlH);
    return controlH;
    #endif
}
int getControlWidth(std::string controlName){
    #if IsWIN
    std::pair<cross_control_type,int> &controlVals = controls[controlName];
    RECT controlArea;
    if(GetWindowRect(controlVals.first,&controlArea)){
        int width = controlArea.right - controlArea.left;
        int height = controlArea.bottom - controlArea.top;
        return width;
    }else{
        #if CROSS_FEATURES_DEBUG
        std::cout << "ERROR: Could not get the width of \"" << controlName << "\"" << std::endl;
        return -1;
        #endif
    }
    #endif
    #if IsLINUX
    int controlH, controlW;
    gtk_widget_get_size_request(controls[controlName],&controlW,&controlH);
    return controlW;
    #endif
}

bool isWindowFocused(std::string windowName){
    
    #if IsWIN
    std::cout << GetForegroundWindow() <<  std::endl;
    // BUG: GetForegroundWindow function will only return the window HWND if it is a Windows 
    // application in the WINE compatibility layer. Fortunately this code is most likely to be
    // ran on Windows where no linux applications are ran, so this is not a problem.
    if(GetForegroundWindow() == windows[windowName]){
        return true;
    }else if(GetForegroundWindow() != windows[windowName]){
        return false;
    }
    #endif
    #if IsLINUX
    // FIXME: This code may look correct but it always returns 0
    std::pair<cross_window_type,cross_control_type> &windowVals = windows[windowName];
    gboolean result = gtk_widget_is_focus(windowVals.first);
    if(result){
        return true;
    }else{
        return false;
    }
    #endif
}
crossStd::point2d getCursorPositionOnMonitor(){
    #if IsWIN
    POINT cursor_pos = {};
    GetCursorPos(&cursor_pos);
    crossStd::point2d newPoint;
    newPoint.x = cursor_pos.x;
    newPoint.y = cursor_pos.y;
    return newPoint;
    #endif
    #if IsLINUX
    int yPos,xPos;
    GdkDisplay *display = gdk_display_get_default ();
    GdkDeviceManager *device_manager = gdk_display_get_device_manager (display);
    GdkDevice *device = gdk_device_manager_get_client_pointer (device_manager);
    gdk_device_get_position (device, NULL, &xPos, &yPos);
    crossStd::point2d newPoint;
    newPoint.x = xPos;
    newPoint.y = yPos;
    return newPoint;
    #endif
}
bool isMouseInBoundsOfWindow(std::string windowName){
    crossStd::point2d CursorPos = getCursorPositionOnMonitor();
    crossStd::point3d WinPos = getWindowPosition(windowName);
    int winHeight = getWindowHeight(windowName);
    int winWidth = getWindowWidth(windowName);
    crossStd::point2d MousePosWinRelative;
    MousePosWinRelative.x = CursorPos.x - WinPos.x;
    MousePosWinRelative.y = CursorPos.x - WinPos.x;
    if(MousePosWinRelative.x >= 0 || MousePosWinRelative.y >= 0){
        return true;
    }else{
        return false;
    }
}
int cross_createWindow(int width,int height, std::string title, std::string createWindowName){
        #if IsWIN
        srand(time(0));
        WNDCLASSW wc = {0};
        //win_setupcode = cross_setupcode;
        wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hInstance = win_hInst;
        wc.lpszClassName = std::wstring(createWindowName.begin(), createWindowName.end()).c_str();
        wc.lpfnWndProc = WindowProc;
        if(!RegisterClassW(&wc)){
            #if CROSS_FEATURES_DEBUG
            std::cout << "Error: Unable to register class" << std::endl;
            #endif
            winMain_returnValue = -1;
        }else{
        windows[createWindowName] = CreateWindowW(std::wstring(createWindowName.begin(), createWindowName.end()).c_str(),std::wstring(title.begin(), title.end()).c_str(),WS_OVERLAPPEDWINDOW | WS_VISIBLE,CW_USEDEFAULT,CW_USEDEFAULT,width,height,NULL,NULL,NULL,NULL);
        MSG msg = {0};
        cross_setupcode();

        while(GetMessage(&msg,NULL,NULL,NULL)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            int message = win_wp;
            int currentmsg;
            //std::pair<cross_control_type,int> &controlVals = controls[controlName];
            std::map<std::string, std::pair<cross_control_type, int>>::iterator it = controls.begin();
            while(it != controls.end()){
                crossStd::point2d CursorPos = getCursorPositionOnMonitor();
                crossStd::point3d WinPos = getWindowPosition(createWindowName);
                int winHeight = getWindowHeight(createWindowName);
                int winWidth = getWindowWidth(createWindowName);
                crossStd::point2d MousePosWinRelative;
                MousePosWinRelative.x = CursorPos.x - WinPos.x;
                MousePosWinRelative.y = CursorPos.x - WinPos.x;
                //std::cout << "MousePosWinRelative.x = " << MousePosWinRelative.x << " & MousePosWinRelative.y = " << MousePosWinRelative.y << " & id = " << it->first << std::endl;
                if(MousePosWinRelative.x >= 0 || MousePosWinRelative.y >= 0){
                    crossStd::point2d controlPosition = getControlPosition(it->first);
                    int controlWidth = getControlWidth(it->first);
                    int controlHeight = getControlHeight(it->first);
                    if(MousePosWinRelative.x <= controlPosition.x && MousePosWinRelative.x <= controlWidth){
                        //if(controlPosition.y <= MousePosWinRelative.y && MousePosWinRelative.y <= controlHeight){
                            // Hover event has occured
                            crossStd::crossEvent event;
                            event.from = it->first;
                            event.typeOfEvent = "hover";
                            if(cross_repeatcode != nullptr){
                            cross_repeatcode(event);
                            }
                            //break;
                        //}
                    }
                    
                }
                it++;
            }
        }

        }
        #endif
        #if IsLINUX
        int argC = 0;
        char** argV;
        GtkWidget *_LinuxWindow, *_Box;
        windows[createWindowName] = std::make_pair(_LinuxWindow, _Box);
        std::pair<cross_window_type,cross_control_type> &windowVals = windows[createWindowName];
   
        gtk_init(&argC,&argV);
        windowVals.first = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        windowVals.second = gtk_fixed_new();
        g_object_bind_property(G_OBJECT(windowVals.second),"has-focus",G_OBJECT(windowVals.first), "has-focus", G_BINDING_DEFAULT);
        gtk_window_set_title(GTK_WINDOW(windowVals.first),title.c_str());
        gtk_window_set_default_size(GTK_WINDOW(windowVals.first),(gint)width,(gint)height);
        gtk_widget_show(windowVals.first);
        cross_setupcode();
        gtk_container_add(GTK_CONTAINER(windowVals.first), windowVals.second);
        gtk_widget_show_all(windowVals.first);
        gtk_widget_show(windowVals.second);
        gtk_widget_show_all(windowVals.first);
        g_signal_connect(G_OBJECT(windowVals.first),"destroy",G_CALLBACK(gtk_main_quit), NULL);
        gtk_main();
        #endif
}
#ifdef _WIN32

#endif
};
#endif
