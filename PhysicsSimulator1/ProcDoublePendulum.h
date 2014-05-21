#ifndef PROCDOUBLEPENDULUM_H 
#define PROCDOUBLEPENDULUM_H 
  
#include <Windows.h> 
#include <CommCtrl.h> 
  
#include "UIDoublePendulum.h"
#include "SIMDoublePendulum.h"
#include "ProgramDefines.h"
  


/** 
*   @author John Allard 
*   This file holds the callpack procedure for the double pendulum simulation.  
*   the window is instantiated in ProcMainMenu, and from there control is transfered 
*   to this callback  procedure. This callback hadndles all of the UI element creation
*    and interaction from the Double Pendulum Simulator main window. It also is able to create
*    the double pendulum simulation, and to open the double pendulum settings dialog window
*/

LRESULT CALLBACK ProcDoublePendulum( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )  
{ 
    const static HINSTANCE & DPProcInst = GetModuleHandle(NULL); // instance of this callback proc

    static UIDoublePendulum *WindowUI = NULL;  // thrown on the heap to survive the in and out of this callback, is deleted in the
                                               // command WM_DESTROY, which is called whenever the window is destroyed. So no memory leaks!
    
    static SIMDoublePendulum *SimClass = NULL; // this pointer references a SimDoublePendulum class thrown on the heap to survive the programming going in and
                                               // out of the callback window. This class holds all of the simulation data

    static NMUPDOWN * updowncontrol = NULL;    // this is a pointer to whichever updown control made the last UI call. It is used to limit the range
                                               // of inputs a user can put into an edit box via the updown control

    static HWND settingsdialoghwnd = NULL;     // handle to the plot settings dialog window, used to pass info to the window via the SetWindowLongPtr method

    switch(msg)
    {
    
        //called once only when the window is created, sets all the UI elements
    case(WM_CREATE):
        {
            //initialize the simulation class for the double pendulum simulation
            SimClass = new SIMDoublePendulum();

            // initialize the UI class for the double pendulum window, then set the window features
            WindowUI = new UIDoublePendulum(DPProcInst);
            WindowUI->SetPictures(hwnd);
            WindowUI->SetButtons(hwnd);
            WindowUI->SetEditText(hwnd);
            WindowUI->SetSpinControl(hwnd);
            WindowUI->SetDropDownBoxes(hwnd);

            // register the simulation settings dialog window WNDCLASSEX class
            RegisterClassEx(&WindowUI->getSettingsDialogWindow());
            RegisterClassEx(&WindowUI->getHelpWindow());

        }break;// end case WM_CREATE




        //======================================
        //=========== CASE UI COMMAND ==========
        //======================================

        // called when the user interacts with a UI element
    case WM_COMMAND:
        {
            //=============================
            //----- DROP DOWN LISTS -------
            //=============================
            if(HIWORD(wParam) == CBN_SELCHANGE)
            {
                // drop down list #1; 
                // The list that lets the user choose which system they are currently working with
                if(lParam == (LPARAM)WindowUI->dropdownboxes[0])
                {
                    WindowUI->SaveSystem(WindowUI->getCurrentSystem(), SimClass);
                    int ItemIndex = SendMessage((HWND) lParam, (UINT) CB_GETCURSEL,(WPARAM) 0, (LPARAM) 0);

                    if(WindowUI->getCurrentSystem() != ItemIndex+1)
                    {
                        if(ItemIndex+1 == 1) // if they chose system 1
                        {
                            WindowUI->setCurrentSystem(1);
                            WindowUI->LoadSystem(1, SimClass);
                        }
                        else // else they chose system 2
                        {
                            WindowUI->setCurrentSystem(2);
                            WindowUI->LoadSystem(2, SimClass);
                        }
                    }// end if the user hasn't re-selected the current system

                }// end if the drop down list was #1


                // drop down list #2; 
                // Lets the user choose which type of plot they want to make for plot 1
                if(lParam == (LPARAM)WindowUI->dropdownboxes[1])
                {
                    WindowUI->SaveSystem(WindowUI->getCurrentSystem(), SimClass);
                    int ItemIndex = SendMessage((HWND) lParam, (UINT) CB_GETCURSEL,(WPARAM) 0, (LPARAM) 0);
                    for(int i = POSITIONPLOT1; i < ANGVELPLOT1+1; i++)
                    {
                        if(ItemIndex == i)
                            SimClass->setPlot1(i);
                    }

                    // now we set the system check box to reflect which system the selected plot is simulating
                    if(SimClass->getPlot1()->getSystem() == 1)
                        CheckDlgButton(hwnd, rbDPPLOT1SYS1 , BST_CHECKED),CheckDlgButton(hwnd, rbDPPLOT1SYS2 , BST_UNCHECKED);
                    else // else it equals 2
                        CheckDlgButton(hwnd, rbDPPLOT1SYS1 , BST_UNCHECKED), CheckDlgButton(hwnd, rbDPPLOT1SYS2 , BST_CHECKED);    
                }// end if


                // drop down list #3
                // Lets the user choose which type of plot they want to make for plot 2
                if(lParam == (LPARAM)WindowUI->dropdownboxes[2])
                {
                    WindowUI->SaveSystem(WindowUI->getCurrentSystem(), SimClass);
                    int ItemIndex = SendMessage((HWND) lParam, (UINT) CB_GETCURSEL,(WPARAM) 0, (LPARAM) 0);
                    for(int i = POSITIONPLOT2; i < ANGVELPLOT2+1; i++)
                    {
                        if(ItemIndex == i-POSITIONPLOT2)
                            SimClass->setPlot2(i);
                    }

                    if(SimClass->getPlot2()->getSystem() == 1)
                        CheckDlgButton(hwnd, rbDPPLOT2SYS1 , BST_CHECKED),CheckDlgButton(hwnd, rbDPPLOT2SYS2 , BST_UNCHECKED);
                    else
                        CheckDlgButton(hwnd, rbDPPLOT2SYS1 , BST_UNCHECKED), CheckDlgButton(hwnd, rbDPPLOT2SYS2 , BST_CHECKED);
                }

            }// end if the command was from a drop down list


            // switch on the UI control ID
            switch(LOWORD(wParam))
            {

                // ---- BUTTONS ---- //
                // case Start Simulation button
                case(bDPSTARTSIM):
                case(ID_START_SIMULATION):
                    WindowUI->SaveSystem(WindowUI->getCurrentSystem(), SimClass);
                    //TODO add start simulation function
                break;

                // case reset parameters
                case(bDPRESET):
                case(ID_SIMULATION_RESETVALUES):
                    WindowUI->resetTextBoxes();
                break;

                // randomize the parameters
                case(bDPRANDOMIZE):
                case(ID_SIMULATION_RANDOMIZEPARAMETERS):
                    WindowUI->randomizeValues();
                break;

                // load a saved double pendulum system from a file
                case(bDPLOAD):
                    // TODO : add dialog window to load double pendulum system
                break;

                // save the current double pendulum system to a file
                case(bDPSAVE):
                    // TODO : add dialog window to save double pendulum system
                break;

                // open up a help window that displays info about the program
                case(bDPHELP):
                    WindowUI->createHelpWindow();
                break;

                case(bDPABOUT):
                    // TODO : add dialog window to save double pendulum system
                break;

                // create the edit dialog for plot #1
                case(bDPCONFIGURE1):
                case(ID_SIMULATIONSETTINGS_PLOT1):
                    WindowUI->SaveSystem(WindowUI->getCurrentSystem(), SimClass);
                    // let the sim class know we are currently editing plot1
                    SimClass->setCurrentPlot(1);
                    settingsdialoghwnd = WindowUI->createSettingDialogBox();    
                    // pass in the SimClass to the new window
                    SetWindowLongPtr(settingsdialoghwnd, GWLP_USERDATA, (LONG_PTR) SimClass);
                    ShowWindow(settingsdialoghwnd, SW_SHOW);
                break;

                // create the edit dialog for plot #2
                case(bDPCONFIGURE2):
                case(ID_SIMULATIONSETTINGS_PLOT2):
                    WindowUI->SaveSystem(WindowUI->getCurrentSystem(), SimClass);
                    // let the sim class know we are currently editing plot2
                    SimClass->setCurrentPlot(2);
                    settingsdialoghwnd = WindowUI->createSettingDialogBox();
                    // pass in the SimClass to the new window
                    SetWindowLongPtr(settingsdialoghwnd, GWLP_USERDATA, (LONG_PTR) SimClass);
                    ShowWindow( settingsdialoghwnd, SW_SHOW);
                break;

            }// end switch on UI ID that sent WM_COMMAND message


            

            //==========================
            //=== CHECK BOXES ==========
            //==========================

            switch((wParam))
            {
                case(rbDPPLOT1SYS1):
                    if(IsDlgButtonChecked(hwnd, rbDPPLOT1SYS1))
                    {
                        CheckDlgButton(hwnd, rbDPPLOT1SYS1 , BST_UNCHECKED);
                        CheckDlgButton(hwnd, rbDPPLOT1SYS2 , BST_CHECKED);
                        SimClass->getPlot1()->setSystem(2);
                    }
                    else
                    {
                        CheckDlgButton(hwnd, rbDPPLOT1SYS1 , BST_CHECKED);
                        CheckDlgButton(hwnd, rbDPPLOT1SYS2 , BST_UNCHECKED);
                        SimClass->getPlot1()->setSystem(1);
                    }
                break;

                case(rbDPPLOT1SYS2):
                    if(IsDlgButtonChecked(hwnd, rbDPPLOT1SYS2))
                    {
                        CheckDlgButton(hwnd, rbDPPLOT1SYS2 , BST_UNCHECKED);
                        CheckDlgButton(hwnd, rbDPPLOT1SYS1 , BST_CHECKED);
                        SimClass->getPlot1()->setSystem(1);
                    }
                    else
                    {
                        CheckDlgButton(hwnd, rbDPPLOT1SYS2 , BST_CHECKED);
                        CheckDlgButton(hwnd, rbDPPLOT1SYS1 , BST_UNCHECKED);
                        SimClass->getPlot1()->setSystem(2);
                    }
                    break;

                case(rbDPPLOT2SYS1):
                    if(IsDlgButtonChecked(hwnd, rbDPPLOT2SYS1))
                    {
                        CheckDlgButton(hwnd, rbDPPLOT2SYS1 , BST_UNCHECKED);
                        CheckDlgButton(hwnd, rbDPPLOT2SYS2 , BST_CHECKED);
                        SimClass->getPlot2()->setSystem(2);
                    }
                    else
                    {
                        CheckDlgButton(hwnd, rbDPPLOT2SYS1 , BST_CHECKED);
                        CheckDlgButton(hwnd, rbDPPLOT2SYS2 , BST_UNCHECKED);
                        SimClass->getPlot2()->setSystem(1);
                    }
                break;

                case(rbDPPLOT2SYS2):
                    if(IsDlgButtonChecked(hwnd, rbDPPLOT2SYS2))
                    {
                        CheckDlgButton(hwnd, rbDPPLOT2SYS2 , BST_UNCHECKED);
                        CheckDlgButton(hwnd, rbDPPLOT2SYS1 , BST_CHECKED);
                        SimClass->getPlot2()->setSystem(1);
                    }
                    else
                    {
                        CheckDlgButton(hwnd, rbDPPLOT2SYS2 , BST_CHECKED);
                        CheckDlgButton(hwnd, rbDPPLOT2SYS1 , BST_UNCHECKED);
                        SimClass->getPlot2()->setSystem(2);
                    }
                break;
            }// end switch on wParam for check boxes

        }
        break;// end case WM_COMMAND

        

        //==========================
        //=== SPIN CONTROL FEEDBACK
        //==========================

        // oddly enough, the value and sign of the spin control change are only sent here, and not to the WM_VSCROLL message handler
        // but the ID of the spin control that was used is only sent to the WM_VSCROLL message handler, so we need both of these next 
        // two cases to properly process a spin control command
        case(WM_NOTIFY):
            updowncontrol = (LPNMUPDOWN) lParam; 
        break;
        case WM_VSCROLL:
        {
            if(updowncontrol != NULL)
            {
                boolean upordown = true; // true means up, false means down

                // determine if the user is trying to increase or decrease the counter
                if(updowncontrol->iDelta == -1.0)
                    upordown = true;
                else if(updowncontrol->iDelta == 1.0)
                    upordown = false;
                else
                    break; // it's a switch statement so breaks are okay!!
        
                for(int i = 0; i < WindowUI->getSpinControls().size(); i++)
                {    
                    // search through the vector of spincontrol handles to until we match the one that sent the increment message, then change the value in the corresponding text box
                    if((HWND)lParam == WindowUI->getSpinControls()[i])
                        WindowUI->etIncrement(upordown, i);            
                }
            }// end if
        }
        break; // end case WM_HSCROLL


        // case WM_DESTROY
        case WM_DESTROY:
            if(WindowUI != NULL)
                delete WindowUI; // delete the UIDoublePendulum object that we dynamically allocated
            if(SimClass != NULL)
                delete SimClass; // delete the SIMDoublePendulum object that we dynamically allocated
        break;


    }// end switch on message
  

    return DefWindowProc(hwnd, msg, wParam, lParam);  
} // end double pendulum callback procedure
  

  
  
#endif