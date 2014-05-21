/**  
*   @author John Allard  
*   This file contains the definitions of the functions that are declared in the Main Menu class  
*   inside of MainMenu.h.  
*/
    
#include <Windows.h>  
#include <commctrl.h>  
    
#include "ProgramDefines.h"  
#include "UIMainMenu.h" 
#include "Resource.h"
    
//we must forward declare the callback procedures for the windows that are defined in this class 
LRESULT CALLBACK ProcMainMenu( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );  
LRESULT CALLBACK ProcDoublePendulum( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ); 
  
//=======================  
//   Constructor  
//=======================  
UIMainMenu::UIMainMenu(const HINSTANCE & hInst)  
{  
    
    //TODO: initialize all of the window member variables to their respective values that will be used in the program.  
     WNDCLASSEX hold = {0};  
     this->mainwindow = hold;  
     this->mainwindow.cbSize           = sizeof(WNDCLASSEX);  
     this->mainwindow.lpfnWndProc      = (WNDPROC) ProcMainMenu;  
     this->mainwindow.hInstance        = hInst;  
     this->mainwindow.hbrBackground    = BACKGROUNDCOLOR;  
     this->mainwindow.hIcon            = LoadIcon (hInst, MAKEINTRESOURCE(IDI_ICON1));
     this->mainwindow.lpszClassName    = TEXT("PhysicsProgramMain"); 
     this->mainwindow.lpszMenuName  = MAKEINTRESOURCE(TOPMENUMAINWINDOW);
     

    
  
     this->doublependulum = hold;  
     this->doublependulum.cbSize           = sizeof(WNDCLASSEX);  
     this->doublependulum.lpfnWndProc      = (WNDPROC) ProcDoublePendulum;
     this->doublependulum.hIcon            = LoadIcon (hInst, MAKEINTRESOURCE(IDI_ICON1));
     this->doublependulum.hInstance        = hInst;  
     this->doublependulum.hbrBackground    = BACKGROUNDCOLOR;  
     this->doublependulum.lpszClassName    = TEXT("DPWindowMain"); 
     this->doublependulum.lpszMenuName  = MAKEINTRESOURCE(TOPMENUDPSIM);

}  
    
//=================================================  
// Sub WNDCLASSEX windows that can be created from the main menu have their get functions below  
//=================================================  
WNDCLASSEX & UIMainMenu::getMainWindow()   
{  
    return this->mainwindow;  
}  
    
HWND UIMainMenu::createMainMenu()  
{  
    HWND hwnd = CreateWindow(  
        this->getMainWindow().lpszClassName,  
        TEXT(" Physics Simulator -- Main Menu"),  
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,  
        60, 100,  
        450, 295,  
        NULL,  
        NULL,  
        mainwindow.hInstance,  
        NULL  
    );  
    
    return hwnd;  
}  
    

WNDCLASSEX & UIMainMenu::getDoublePendWindow()  
{  
    return this->doublependulum;  
}  
HWND UIMainMenu::createDoublePendWindow()  
{  
    HWND hwnd = CreateWindow(  
        this->getDoublePendWindow().lpszClassName,  
        TEXT(" Double Pendulum Simulator"),  
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,  
        50, 70,  
        525, 510, 
        NULL,  
        NULL,  
        doublependulum.hInstance,  
        NULL  
    );  
    return hwnd;  
}  
  
WNDCLASSEX & UIMainMenu::get2DWaveWindow()  
{  
    return this->wavesim2d;  
}  
HWND UIMainMenu::create2DWaveWindow()  
{  
    HWND hwnd = NULL;  
    //TODO add CreateWindow(...) function for the 2D WaveSim window  
    return hwnd;  
}  
    
WNDCLASSEX & UIMainMenu::get3DWaveWindow()  
{  
    return this->wavesim3d;  
}  
HWND UIMainMenu::create3DWaveWindow()  
{  
    HWND hwnd = NULL;  
    //TODO add CreateWindow(...) function for the 3D WaveSim window  
    return hwnd;  
}  
    
WNDCLASSEX & UIMainMenu::getSpringWindow()  
{  
    return this->springsim;  
}  
HWND UIMainMenu::createSpringWindow()  
{  
    HWND hwnd = NULL;  
    //TODO add CreateWindow(...) function for the Spring Simulator window  
    return hwnd;  
}  
    
WNDCLASSEX & UIMainMenu::getTrajecWindow()  
{  
    return this->trajectorysim;  
}  
HWND UIMainMenu::createTrajecWindow()  
{  
    HWND hwnd = NULL;  
    //TODO add CreateWindow(...) function for the 2D WaveSim window  
    return hwnd;  
}  
    
   
  
  
// =================================================== 
//---------------------------------------------------- 
// =====---- UI ELEMENTS FOR MAIN MENU BELOW ----======= 
  
  
  
//=========================================  
//============= Set Pictures Below ========  
//========================================= 
void UIMainMenu::SetPictures(const HWND & hwnd)
{
    //  menu option labels static box and image
    HWND MenuOptionsTitleBox = CreateWindowExW(NULL, L"STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 5 , 10, 380, 350, hwnd, 0, NULL, NULL);
    HANDLE MenuOptionsTitleImage = LoadImage(NULL, L"..//Pictures//MainMenu//MenuLabels.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SendMessage(MenuOptionsTitleBox, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) MenuOptionsTitleImage);
}


//==========================
// Set Buttons Below =======
//-=========================
void UIMainMenu::SetButtons(const HWND & hwnd)
{
    // these ints describe the spacial relations between the buttons
    int sizex = 80;
    int sizey = 27;
    int startx = 330;
    int starty = 67;
    int inc = 29;
    //button to start double pendulum simulation
    CreateWindow(TEXT("button"), 
                 TEXT("Start"),
                 WS_VISIBLE | WS_CHILD ,
                 startx, starty, sizex, sizey,
                 hwnd,
                 (HMENU) bDPSIM,
                 NULL, NULL); 
            
    //button to start 2D Wave Simulation
    CreateWindow(TEXT("button"), 
                 TEXT("Start"),
                 WS_VISIBLE | WS_CHILD ,
                 startx, starty+inc, sizex, sizey,
                 hwnd,
                 (HMENU) b2DWAVE,
                 NULL, NULL);

    //button to start 2D Wave Simulation
    CreateWindow(TEXT("button"), 
                 TEXT("Start"),
                 WS_VISIBLE | WS_CHILD ,
                 startx, starty+2*inc, sizex, sizey,
                 hwnd,
                 (HMENU) b3DWAVE,
                 NULL, NULL);

    //button to start Spring and Mass Simulation
    CreateWindow(TEXT("button"), 
                 TEXT("Start"),
                 WS_VISIBLE | WS_CHILD ,
                 startx, starty+3*inc, sizex, sizey,
                 hwnd,
                 (HMENU) bSPRING,
                 NULL, NULL);

    //button to start Trajectory Simulatioin
    CreateWindow(TEXT("button"), 
                 TEXT("Start"),
                 WS_VISIBLE | WS_CHILD ,
                 startx, starty+4*inc, sizex, sizey,
                 hwnd,
                 (HMENU) bTRAJEC,
                 NULL, NULL);

}