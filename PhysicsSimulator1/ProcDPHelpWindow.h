#ifndef PROCDPHELPWINDOW_H
#define PROCDPHELPWINDOW_H

#include "ProgramDefines.h"
/**
*    @author John Allard
*    This is the callback function for the 'help' window for the double pendulum simulator. 
*    This window will simply contain a background image that contains text that lets the user know how to
*     properly use this program. There will also be a few buttons that allow the user to navigate/close the window
*/

LRESULT CALLBACK ProcDPHelpWindow( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )  
{ 
    switch(msg)
    {
    
        //called once only when the window is created, sets all the UI elements
        case(WM_CREATE):
        
            HWND DPTitleBox = CreateWindowExW(NULL, L"STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 10 , 40, 0, 0, hwnd, 0, NULL, NULL);
            HANDLE DPTitleImage = LoadImage(NULL, L"..//Pictures//DPSim//HelpWindow//MainBackground.bmp",IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); //"C://Users//John//Documents//Visual Studio 2012//Projects//PhysicsSimulator1//Pictures//DPSim//Title.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            SendMessage(DPTitleBox, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) DPTitleImage);
        break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);  
}


# endif