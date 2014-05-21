#ifndef PROCDPDIALOG_H
#define PROCDPDIALOG_H

#include  "UIDPDialog.h"
#include "ProgramDefines.h"
#include "SIMDoublePendulum.h"


/**
*    @author John Allard
*    This file contains the callback procedure for all of the different plot settings dialog windows that
*    allow the user to configure the simulations to their specifications. This callback is for 4 different types of windows
*    that are all very similar, one is for position plot, one for energy plot, one for angle plot, one for angular velocity plot
*/

LRESULT CALLBACK ProcDPDialog( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) 
{
    const static HINSTANCE & DPProcInst = GetModuleHandle(NULL); // instance of this callback proc

    static SIMDoublePendulum * DPSimSettings = NULL;             // this class holds a reference to the DPSimulation class that holds
                                                                 // all of the simulation settings objects the user can configure

    static DPPlotSettings * plotsettings = NULL;                 // pointer to whichever plot we are currently editing, out of the
                                                                 // 8 availble in the SIMDoublePendulum class

    switch(msg)
    {

        // set all of the window UI features and get the data sent from the parent window
        case (WM_CREATE):
            // get the simulation settings object that was passed to the dialog window
            DPSimSettings = (SIMDoublePendulum*) GetWindowLongPtr(hwnd, GWLP_USERDATA);

            // get the plot object the user wishes to edit from the simulation object
            if(DPSimSettings->getCurrentPlot() == 1)
                plotsettings = DPSimSettings->getPlot1();
            else
                plotsettings = DPSimSettings->getPlot2();
            
            // set the UI corresponding to the edit plot window the user has initiated
            plotsettings->setButtonsPictures(hwnd);
            plotsettings->setSpinControl(hwnd);
            plotsettings->setEditText(hwnd,DPProcInst);
            plotsettings->setDropDown(hwnd);
        break;



        case(WM_COMMAND):
        case(WM_VSCROLL):
        case(WM_NOTIFY):
            // use the plot settings classes to handle to the dialog feedback
            // the function processMessage is virtual, so the message handling will depend  
            // on what type of derived class the plotsettings pointer points to
            plotsettings->processMessage(hwnd, msg, wParam, lParam);
        break;


    
        case WM_DESTROY:
        // TODO: delete any dynamic memory if you create any
        break;

    }// end switch on message

      return DefWindowProc(hwnd, msg, wParam, lParam); 
}



#endif