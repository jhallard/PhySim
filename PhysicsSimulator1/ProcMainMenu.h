#ifndef PROCMAINMENU_H
#define PROCMAINMENU_H


#include <Windows.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <commctrl.h>


#include "ProgramDefines.h"
#include "UIMainMenu.h"


/** 
 *    - @author John Allard
 *  - This is the callback procedure for the main menu window of our program.
 *  - From this window, the user is able to start any of the 5 sub-simulation programs
 *  - contained in this project. This is basically the callback for the starting point of the
 *  - program.
 */
LRESULT CALLBACK ProcMainMenu( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    const HINSTANCE & MainProcInst = GetModuleHandle(NULL); // instance of this callback proc


    // this object holds the values to all of the windows that will be created in this function
    // The windows capable of being created are the main windows for all 5 sub-simulations of this program
    static UIMainMenu SimWindows(MainProcInst);

    // here we declare the window for the double pendulum window that will be created from the main menu
    WNDCLASSEX doublependwindow = SimWindows.getDoublePendWindow();
    WNDCLASSEX d2wavewindow     = SimWindows.get2DWaveWindow();
    WNDCLASSEX d3wavewindow     = SimWindows.get3DWaveWindow();
    WNDCLASSEX springwindow     = SimWindows.getSpringWindow();
    WNDCLASSEX trajecwindow     = SimWindows.getTrajecWindow();
    

    // switch on msg
    switch(msg)
    {

        // case WM_CREATE gets called only once when the window is instantiated. Here we set all of the UI elements, they are coded and commented below 
    case WM_CREATE:
        {
            //======================================
            // Set UI elements of the Main Menu
            // using the functions in the UIMainMenu class
            //======================================
            SimWindows.SetPictures(hwnd);
            
            SimWindows.SetButtons(hwnd);


            //=======================
            // register all of the windows
            // that can be made from the main window
            //=======================
            if (!RegisterClassEx(&doublependwindow))
                {
                     MessageBox(NULL, TEXT("Call to RegisterClassEx failed!: ProcMain"), TEXT("Error!"), NULL);
                }

            //******************TODO******************
            // add register class functions for the rest of the windows
            //******************TODO******************

        }break; //end case WM_CREATE


    // case WM_COMMAND handles all of the UI feedback, for instance a button press
    case WM_COMMAND:
        {

            switch(LOWORD(wParam))
            {
                
                // case user wants to create the Double Pendulum Window
                case(ID_NEWSIMULATION_SPRINGANDMASSSIMULATION):
                case(bDPSIM):
                {
                    SimWindows.createDoublePendWindow();
                }break;

                // case user wants to create 2d wave simulation
                case(b2DWAVE):
                {
                    // TODO
                }break;

                // case user wants to create 3d wave simulation
                case(b3DWAVE):
                {
                    // TODO
                }break;

                // case user wants to create Spring simulation
                case(bSPRING):
                {
                    // TODO
                }break;

                // case user wants to create trajectory simulation
                case(bTRAJEC):
                {
                    // TODO
                }break;
            }// end switch on the id of the UI element that send the WM_COMMAND message
        }
        break;// end WM_COMMAND case



    case WM_DESTROY:
        {
            PostQuitMessage(0);
        }
        break;// end case WM Destroy
        


    }// end switch on MSG


    return DefWindowProc(hwnd, msg, wParam, lParam);
}// end ProcMainMenu



#endif