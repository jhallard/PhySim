#ifndef UIDOUBLEPENDULUM_H  
#define UIDOUBLEPENDULUM_H  
    
#include <Windows.h> 
#include <commctrl.h> 
#include <vector>

#include "SIMDoublePendulum.h"

/**  
*   @author John Allard  
*   This class will hold all of the UI data/functionality for the Double Pendulum Simulation. This means it will hold the values  
*   for all of the windows that are created from the Double Pendulum Simulation Menu. It will hold functions that are called 
*    from the ProcDP function that set both the pictures, buttons, text, and edit boxes for the window.  
*/
class UIDoublePendulum  
{  
    
    private:  
  
        // WNDCLASSEX windows that can be created from the double pendulum window 
        WNDCLASSEX helpwindow; 
        WNDCLASSEX settingsdialogwindow;

        // these are the window handles for the edit text boxes that will be made
        // they are stored in this order in the vector for both spincontrols and editboxes
        //  ulength, llength, umass, lmass, uangle, langle, uangularvelocity, langularvelocity, simulation time, simulation speed
        std::vector<HWND> editboxes;
        std::vector<HWND> spincontrols;

        int currentsystem; // current double pend. system the user is editing

        const HINSTANCE & DPINSTANCE;


    public: 
        // I really should make these private...
        std::vector<HWND> dropdownboxes;
        std::vector<HWND> checkboxes;

        // Constructor 
        UIDoublePendulum(const HINSTANCE &, int = 1); 


        // windows that can be created                                     
        WNDCLASSEX & getHelpWindow();            // return the handle to the help window 
        WNDCLASSEX & getAboutWindow();            //  return the About window class
        WNDCLASSEX & getSettingsDialogWindow(); // return the simulation settings window class

        HWND createHelpWindow();                // Called to create the HelpWindow 
        HWND createAboutWindow();                // Called to create the about window
        HWND createSettingDialogBox();            // called when the user hits the "Configure" button for one of the plots
        
  
        void SetPictures(HWND &);                // set the double pendulum main window pictures
        void SetButtons(HWND &);                // set the double pendulu main window buttons
        void SetDropDownBoxes(HWND &);            // set the double pendulum main window drop down boxes

        //edit boxes
        std::vector<HWND> SetEditText(HWND &);        // this one returns the HWND because we need to send messages to it in the future
        HWND & etGetHWND(int key);                    // get the handle to an edit text window
        double etGetValue(int);                        // get the value from an edit text window
        void etIncrement(bool, int );                // incements or decrements based on bool, increments the ith editbox
        void changeText(int, wchar_t[]);            // changes the text of the edittext[first param] to second parameter
        void resetTextBoxes();                        // reset textbox values to defaults
        void randomizeValues();                        // randomize the values of the parameters

        // spin control
        void SetSpinControl(HWND &);
        std::vector<HWND> & getSpinControls();

        // these two set and get the current double pendulum system that the user is working on
        void setCurrentSystem(int);
        int getCurrentSystem();

        void SaveSystem(int, SIMDoublePendulum *);                // save the current double pendulum system settings
        void LoadSystem(int, SIMDoublePendulum *);                // load the double pendulum system settings to the current UI

    
};  
    
    
#endif