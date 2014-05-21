#include "DPPlotSettings.h"
#include "ProgramDefines.h"

/**
*    @author John Allard
*    This is the implementation of the abstract DPPlotSettings class. This is the base class for a
*    hierarchy of classes that represent all of the different types of plots that the double pendulum simulation
*    can create. This class holds the information and functions common to all of the plots, but it is not specific
*    enough to be implemented as an actual plot thus it is a virtual class
*/

    // base class constructor, sets all data fields in the base class
    DPPlotSettings::DPPlotSettings(int type,int system, bool grid, std::string title)
    {
        this->setPlotType(type);
        this->setSystem(system);
        this->setGridState(grid);
        this->setTitle(title);
        this->PROGRAMCOLORS = Colors();
    }

    // processes the messages that are common to all derived classes
    void DPPlotSettings::processMessage(HWND & hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch(msg)
        {
            // this is where commands from UI elements are set
            case WM_COMMAND:
            {
                //==========================
                //=== BUTTONS ==========
                //==========================
                switch(LOWORD(wParam))
                {
                    case bDPDIALOGCLOSE:
                        DestroyWindow(hwnd);
                    break;

                    case bDPDIALOGSAVE:
                        DestroyWindow(hwnd);
                    break;
                }// end switch on command id


                //==========================
                //=== CHECK BOXES ==========
                //==========================
                switch((wParam))
                {
                    // include grid check box
                    case cbDPINCLUDEGRID:
                        if(IsDlgButtonChecked(hwnd, cbDPINCLUDEGRID))
                            CheckDlgButton(hwnd, cbDPINCLUDEGRID , BST_UNCHECKED);
                        else
                            CheckDlgButton(hwnd, cbDPINCLUDEGRID , BST_CHECKED);
                        this->setGridState(IsDlgButtonChecked(hwnd, cbDPINCLUDEGRID));
                    break;

                    // include title check box
                    case cbDPINCLUDETITLE:
                        if(IsDlgButtonChecked(hwnd, cbDPINCLUDETITLE))
                            CheckDlgButton(hwnd, cbDPINCLUDETITLE , BST_UNCHECKED);
                        else
                            CheckDlgButton(hwnd, cbDPINCLUDETITLE , BST_CHECKED);
                    break;
                }// end switch on checkboxes

            }// end case WM_COMMAND
            break;

        }// end switch on message
    }// end function process message


    void DPPlotSettings::setButtonsPictures(HWND& hwnd)    
    {
        // Pictures

        HWND test = CreateWindowExW(NULL, L"STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 10 , 45, 0, 0, hwnd, 0, NULL, NULL);
        HANDLE test1 = LoadImage(NULL, L"..//Pictures//DPSim//Dialog//BackGround.bmp",IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        SendMessage(test, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) test1);

        HWND SystemTitle;
        HANDLE SystemTitle1;

        // we have a different picture based on if it is plotting for double pend. system 1 or 2
        if(this->getSystem() == 1)
        {
            HWND SystemTitle = CreateWindowExW(NULL, L"STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 20 , 15, 0, 0, hwnd, 0, NULL, NULL);
            HANDLE SystemTitle1 = LoadImage(NULL, L"..//Pictures//DPSim//Dialog//System1Title.bmp",IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            SendMessage(SystemTitle, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) SystemTitle1);
        }
        else if(this->getSystem() == 2)
        {
            HWND SystemTitle = CreateWindowExW(NULL, L"STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 20 , 15, 0, 0, hwnd, 0, NULL, NULL);
            HANDLE SystemTitle1 = LoadImage(NULL, L"..//Pictures//DPSim//Dialog//System2Title.bmp",IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            SendMessage(SystemTitle, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) SystemTitle1);
        }


        // Buttons

            // save the changed made to the plot
        CreateWindow(TEXT("button"), 
                 TEXT("Save"),
                 WS_VISIBLE | WS_CHILD ,
                 270, 211, 90, 27,
                 hwnd,
                 (HMENU) bDPDIALOGSAVE,
                 NULL, NULL);

        // exit without saving changes
        CreateWindow(TEXT("button"), 
                 TEXT("Close"),
                 WS_VISIBLE | WS_CHILD ,
                 30, 211, 90, 27,
                 hwnd,
                 (HMENU) bDPDIALOGCLOSE,
                 NULL, NULL);

        // include grid check box
        CreateWindow(TEXT("button"), 
                 TEXT(""),
                 WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,
                 120, 50, 12, 12,
                 hwnd,
                 (HMENU) cbDPINCLUDEGRID,
                 NULL, NULL);
        
        // include grid check box
        CreateWindow(TEXT("button"), 
                 TEXT(""),
                 WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,
                 275, 50, 12, 12,
                 hwnd,
                 (HMENU) cbDPINCLUDETITLE,
                 NULL, NULL);

        if(this->getGridState())
            CheckDlgButton(hwnd, cbDPINCLUDEGRID , BST_CHECKED);
        else
            CheckDlgButton(hwnd, cbDPINCLUDEGRID , BST_UNCHECKED);

        if(this->getTitle().c_str() != "")
            CheckDlgButton(hwnd, cbDPINCLUDETITLE , BST_CHECKED);
        else
            CheckDlgButton(hwnd, cbDPINCLUDETITLE , BST_UNCHECKED);

    }
    std::vector<HWND> DPPlotSettings::setEditText(HWND& hwnd, const HINSTANCE & hInst)
    {
        std::vector<HWND> hold;
        return hold;
    }
    std::vector<HWND> DPPlotSettings::setDropDown(HWND& hwnd)
    {
        std::vector<HWND> hold;
        return hold;
    }
    std::vector<HWND> DPPlotSettings::setSpinControl(HWND& hwnd)
    {
        std::vector<HWND> hold;
        return hold;
    }
    
    void DPPlotSettings::setPlotType(int plottype)
    {
        if(plottype > POSITIONPLOT1-1 && plottype < ANGVELPLOT2+1)
            this->plottype = plottype;
    }
    int DPPlotSettings::getPlotType() const
    {
        return this->plottype;
    }
    void DPPlotSettings::setGridState(bool state)
    {
        this->gridstate = state;
    }
    bool DPPlotSettings::getGridState() const
    {
        return this->gridstate;
    }

    std::string DPPlotSettings::getTitle() const
    {
        return this->title;

    }
    void DPPlotSettings::setTitle(std::string title) 
    {
        if(title.length() > 0 && title.length() < 30)
            this->title = title;
    }

    void DPPlotSettings::setSystem(int system)
    {
        if(system == 1 || system == 2)
            this->system = system;
    }

    int DPPlotSettings::getSystem() const
    {
        return this->system;
    }


    
double DPPlotSettings::etGetValue(int i)
{

         int length = GetWindowTextLengthW(edittext[i])+ 1;
         wchar_t* text =  new wchar_t[length+1];


         GetWindowTextW(edittext[i], text, length);
        
         char holdvalue[100];
        
         for(int iii = 0;iii<length;iii++)
             holdvalue[iii] = *(text+iii);

         delete [] text;
         return atof(holdvalue); // converts c string to doubles
}
// increments the value of an edit box, corresponding to a user clicking a spin wheel
// @param incdec - true means to increment, false means to decrement
// @*param i      - which editbox to increment/decrement
void DPPlotSettings::etIncrement(bool incdec, int i)
{
    double change = 0.1; 
    double value = 0;
    int sigfigs = 3;
    wchar_t newvalue[15];

    // changes the sign based on if the user is incrementing or decrementing the text box value
    (incdec)?  change : change*=-1.0;
    value = this->etGetValue(i);

    // determines the significant figures based on the previous values
    if(value <= 0 && value > -10-2*change)
        sigfigs = 4;
    else if(value <= -10.0-2*change && value > -100-2*change)
        sigfigs = 5;
    else if(value <= -100.0-2*change)
        sigfigs = 6;
    else
    {
        (value >= 10.0-change && value < 100-change)? sigfigs = 4: sigfigs = 3;
        (value >= 100-change)? sigfigs = 5: true;
    }
    
    value += change;
            
    swprintf(newvalue, L"%f", value);
    if((i == 0 && value >= 0.1) && (i == 0 && value <= 1.0))
    {
        newvalue[sigfigs] = '\0'; // set the end of the new value based on the number of significant figures
        changeText(i, newvalue);
    }

}
// change/set the text of the ith edit box
void DPPlotSettings::changeText(int i, wchar_t arr[])
{
  if(edittext.size() != 0)
        SetWindowTextW(edittext[i], arr);
}