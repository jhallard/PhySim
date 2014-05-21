
#include "UIDPDialog.h"
#include "ProgramDefines.h"

#include <Windows.h>

/**
*    @author John Allard
*    This is the implementation of the UIDPDialog class, which is the class that holds all of the UI information and
*    Functionality for the Simulation Settings Dialog Window inside the Double Pendulum function. 
*
*/


UIDPDialog::UIDPDialog() 
{
    this->setCurrentTab(-1); // set to default
    //TODO: think of something to do inside the constructor

}

void UIDPDialog::setCurrentTab(int tab)
{
    this->currenttab = tab;
}
int UIDPDialog::getCurrentTab() const
{
    return this->currenttab;
}

// these are the set functions for the standard, static window UI. these buttons do not change
void UIDPDialog::setStaticUI(HWND & hwnd) const
{

    int startx = 10; int starty = 20;
    int sizex = 60; int sizey = 25;
    int inc = 25;

    //===============================================
    //================== BUTTONS BELOW ==============
    //===============================================

    //// This button opens the Figure Settings "tab"
    //    CreateWindow(TEXT("button"), 
    //             TEXT("Figure"),
    //             WS_VISIBLE | WS_CHILD | BS_MULTILINE,
    //             startx, starty, sizex, sizey,
    //             hwnd,
    //             (HMENU) bDPDIALOGFIGURE,
    //             NULL, NULL);
    //// this button opens up the plot settings of the plot #1 as defined by the user
    //    CreateWindow(TEXT("button"), 
    //        TEXT("Plot #1"),
    //             WS_VISIBLE | WS_CHILD | BS_MULTILINE,
    //             startx, starty + inc, sizex, sizey,
    //             hwnd,
    //             (HMENU) bDPDIALOGPLOT1SETTINGS,
    //             NULL, NULL);
    //// this button opens up plot settings to plot #2 as defined by the user
    //    CreateWindow(TEXT("button"), 
    //        TEXT("Plot #2"),
    //             WS_VISIBLE | WS_CHILD | BS_MULTILINE,
    //             startx, starty + 2*inc, sizex, sizey,
    //             hwnd,
    //             (HMENU) bDPDIALOGPLOT2SETTINGS,
    //             NULL, NULL);


    //// this button saves the data entered and closes the window
    //    CreateWindow(TEXT("button"), 
    //        TEXT("Save"),
    //             WS_VISIBLE | WS_CHILD | BS_MULTILINE,
    //             startx, starty+9*inc, sizex, sizey+10,
    //             hwnd,
    //             (HMENU) bDPDIALOGSAVE,
    //             NULL, NULL);

    //    // these creates the white box around the area that changes 
    //    CreateWindow(TEXT("BUTTON"), TEXT(""), WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
 //            78,            /* X Position */
 //            10,            /* Y Position */
 //            400,           /* X Width */
 //            270,           /* Y Height */
 //            hwnd, (HMENU) -1, NULL, NULL);
}


void UIDPDialog::setFigureSettingsUI(HWND & hwnd)
{
    // this if statement prevents us from changing the dialog to the Figure settings if we are already in the figure settings
    if(this->getCurrentTab() != 0)
    {
        this->setCurrentTab(0);// set the current tab to this one

        // disable the UI for all other UI tabs
        /*disableAnglePlotUI();
        disableAngVelPlotUI();
        disablePosPlotUI();*/

        //===================================
        //========= PICTURES ================
        //===================================

        // TOP PICTURE
        //main menu title static box and image
        this->picFigure.push_back(CreateWindowExW(NULL, L"STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 170 , 7, 0, 0, hwnd, 0, NULL, NULL));
        HANDLE DPDialogFigureTitleImage = LoadImage(NULL, L"..//Pictures//DPSim//Dialog//DialogfigureTitle.bmp",IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        SendMessage(picFigure[0], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) DPDialogFigureTitleImage);

        


    }// end if we were in a different tab
}
void UIDPDialog::disableFigureSettingsUI()
{

}