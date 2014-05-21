#include <Windows.h> 
#include <CommCtrl.h> 
#include <ctime>
#include <random>

  
#include "UIDoublePendulum.h" 
#include "ProgramDefines.h" 
#include "ProcDPDialog.h"
#include "ProcDPHelpWindow.h" 
  
  
  
/** 
*   @author John Allard 
*   this file is the implementation and definiton of the functions defined in the class UIDoublePendulum 
*   This class will define all of the get andset functions, the functions to create and set all of the UI 
*   elements for the double pendulum window, and of course it will define the constructor.  
*/
  
  
  
// Constructor 
UIDoublePendulum::UIDoublePendulum(const HINSTANCE & hInst, int currentsystem)
    : DPINSTANCE(hInst)
{ 
    this->currentsystem = currentsystem;


    // help window wndexclass
     WNDCLASSEX hold = {0};  
     this->helpwindow                   = hold;  
     this->helpwindow.cbSize           = sizeof(WNDCLASSEX);  
     this->helpwindow.lpfnWndProc      = (WNDPROC) ProcDPHelpWindow;
     this->helpwindow.hInstance        = DPINSTANCE;  
     this->helpwindow.hbrBackground    = BACKGROUNDCOLOR;  
     this->helpwindow.lpszClassName    = TEXT("DPHELPWINDOW"); 

     // simulation settings dialog window wndexclass
     this->settingsdialogwindow                     = hold;  
     this->settingsdialogwindow.cbSize           = sizeof(WNDCLASSEX);  
     this->settingsdialogwindow.lpfnWndProc      = (WNDPROC) ProcDPDialog;  
     this->settingsdialogwindow.hInstance        = DPINSTANCE;  
     this->settingsdialogwindow.hbrBackground    = BACKGROUNDCOLOR;  
     this->settingsdialogwindow.lpszClassName    = TEXT("DPSETTINGSWINDOW"); 
  
} 
  
  
//returns the WNDEXCLASS helpwindow to the window that this function is being called from 
WNDCLASSEX & UIDoublePendulum::getHelpWindow() 
{ 
    return this->helpwindow; 
} 
HWND UIDoublePendulum::createHelpWindow() 
{ 
    HWND hwnd = CreateWindow(  
        this->getHelpWindow().lpszClassName,  
        TEXT(" Double Pendulum - Help Menu "),  
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,  
        100, 100,  
        490, 455,  
        NULL,  
        NULL,  
        helpwindow.hInstance,  
        NULL);  
return hwnd;
}

//returns the WNDEXCLASS helpwindow to the window that this function is being called from 
WNDCLASSEX & UIDoublePendulum::getSettingsDialogWindow() 
{ 
    return this->settingsdialogwindow; 
} 
// called when the user hits the "Simulation Settings" button
HWND UIDoublePendulum::createSettingDialogBox()
{
    HWND hwnd = CreateWindow(  
        this->getSettingsDialogWindow().lpszClassName,  
        TEXT(" Double Pendulum - Simulation Settings"),  
        WS_OVERLAPPEDWINDOW,  
        540, 170,  
        412, 293,  
        NULL,  
        NULL,  
        settingsdialogwindow.hInstance,  
        NULL  
    );  
return hwnd;
}





// ===================================================  \\
// =====--- UI ELEMENTS FOR MAIN MENU BELOW ---=======  \\
// ===================================================  \\
  
  
//=========================================  
//============= Set Pictures Below ========  
//========================================= 
void UIDoublePendulum::SetPictures(HWND & hwnd)
{
    HWND DPTitleBox = CreateWindowExW(NULL, L"STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 10 , 15, 0, 0, hwnd, 0, NULL, NULL);
    HANDLE DPTitleImage = LoadImage(NULL, L"..//Pictures//DPSim//Test.bmp",IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); //"C://Users//John//Documents//Visual Studio 2012//Projects//PhysicsSimulator1//Pictures//DPSim//Title.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SendMessage(DPTitleBox, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) DPTitleImage);
    
    HWND DPTitleBox1 = CreateWindowExW(NULL, L"STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 280 , 15, 0, 0, hwnd, 0, NULL, NULL);
    HANDLE DPTitleImage1 = LoadImage(NULL, L"..//Pictures//DPSim//SimSettingsPicture.bmp",IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); //"C://Users//John//Documents//Visual Studio 2012//Projects//PhysicsSimulator1//Pictures//DPSim//Title.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SendMessage(DPTitleBox1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) DPTitleImage1);

    HWND DPTitleBox2 = CreateWindowExW(NULL, L"STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 280, 360, 0, 0, hwnd, 0, NULL, NULL);
    HANDLE DPTitleImage2 = LoadImage(NULL, L"..//Pictures//DPSim//CreateSimBackground.bmp",IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); 
    SendMessage(DPTitleBox2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) DPTitleImage2);
}


//=========================
//======= SET BUTTONS======
//=========================
void UIDoublePendulum::SetButtons(HWND & hwnd)
{
    // location Parameters
    int startx = 13;
    int starty = 380;

    // Start Simulation Button
    CreateWindow(TEXT("button"), 
                 TEXT("Create"),
                 WS_VISIBLE | WS_CHILD ,
                 startx+280, starty-6, 100, 56,
                 hwnd,
                 (HMENU) bDPSTARTSIM,
                 NULL, NULL); 

    CreateWindow(TEXT("button"), 
                 TEXT("Help"),
                 WS_VISIBLE | WS_CHILD ,
                 startx+380, starty-6, 90, 28,
                 hwnd,
                 (HMENU) bDPHELP,
                 NULL, NULL); 

    CreateWindow(TEXT("button"), 
                 TEXT("About"),
                 WS_VISIBLE | WS_CHILD ,
                 startx+380, starty+22, 90, 28,
                 hwnd,
                 (HMENU) bDPABOUT,
                 NULL, NULL); 
    // advanced sim settings button
        CreateWindow(TEXT("button"), 
                 TEXT("Randomize"),
                 WS_VISIBLE | WS_CHILD ,
                 startx+20, starty, 100, 27,
                 hwnd,
                 (HMENU) bDPRANDOMIZE,
                 NULL, NULL);



    // randomize params button
        CreateWindow(TEXT("button"), 
                 TEXT("Reset"),
                 WS_VISIBLE | WS_CHILD ,
                 startx+20, starty+27, 100, 27,
                 hwnd,
                 (HMENU) bDPRESET,
                 NULL, NULL);

        // Load Data from a file
        CreateWindow(TEXT("button"), 
                 TEXT("Load"),
                 WS_VISIBLE | WS_CHILD ,
                 startx+120, starty, 100, 27,
                 hwnd,
                 (HMENU) bDPLOAD,
                 NULL, NULL);

        // save the current initial conditions
        CreateWindow(TEXT("button"), 
                 TEXT("Save"),
                 WS_VISIBLE | WS_CHILD ,
                 startx+120, starty+27, 100, 27,
                 hwnd,
                 (HMENU) bDPSAVE,
                 NULL, NULL);
        

            // save the current initial conditions
        CreateWindow(TEXT("button"), 
                 TEXT("Configure"),
                 WS_VISIBLE | WS_CHILD ,
                 300, 125, 120, 27,
                 hwnd,
                 (HMENU) bDPCONFIGURE1,
                 NULL, NULL);
        

        // save the current initial conditions
        CreateWindow(TEXT("button"), 
                 TEXT("Configure"),
                 WS_VISIBLE | WS_CHILD ,
                 300, 245, 120, 27,
                 hwnd,
                 (HMENU) bDPCONFIGURE2,
                 NULL, NULL);

        // Plot 1 system 1 selection check box
        checkboxes.push_back(CreateWindow(TEXT("button"), 
                 TEXT(""),
                 WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,
                 362, 76, 12, 12,
                 hwnd,
                 (HMENU) rbDPPLOT1SYS1,
                 NULL, NULL));
        CheckDlgButton(hwnd, rbDPPLOT1SYS1 , BST_CHECKED);

        // plot 1 system 2 selection check box
        checkboxes.push_back(CreateWindow(TEXT("button"), 
                 TEXT(""),
                 WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,
                 410, 76, 12, 12,
                 hwnd,
                 (HMENU) rbDPPLOT1SYS2,
                 NULL, NULL));

        // Plot 2 system 1 selection check box
        checkboxes.push_back(CreateWindow(TEXT("button"), 
                 TEXT(""),
                 WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                 362, 195, 12, 12,
                 hwnd,
                 (HMENU) rbDPPLOT2SYS1,
                 NULL, NULL));
        CheckDlgButton(hwnd, rbDPPLOT2SYS1 , BST_CHECKED);

        // plot 2 system 2 selection check box
        checkboxes.push_back(CreateWindow(TEXT("button"), 
                 TEXT(""),
                 WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                 410, 195, 12, 12,
                 hwnd,
                 (HMENU) rbDPPLOT2SYS2,
                 NULL, NULL));
    

}

//==============================
//======= DROP DOWN BOXES ======
//==============================
void UIDoublePendulum::SetDropDownBoxes(HWND & hwnd)
{

    int startx = 15;
    int starty = 380;
        // this is where the user selects which system they want to work with
        dropdownboxes.push_back( CreateWindow(WC_COMBOBOX, TEXT(""), 
        CBS_DROPDOWNLIST | CBS_HASSTRINGS |  WS_BORDER |WS_CHILD  | WS_VISIBLE,
        startx+75, 20, 160, 200,
        hwnd, (HMENU) cbDPSELECTSYSTEM, 
        NULL,NULL));

        {TCHAR A[25];
        TCHAR holds[30] = TEXT("Double Pendulum 1");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds);
        SendMessage(dropdownboxes[0],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 
        TCHAR holds1[30] = TEXT("Double Pendulum 2");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds1);
        SendMessage(dropdownboxes[0],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 

        SendMessage(dropdownboxes[0], CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
        }


        // this is where the user makes their plot choice for plot 1
        dropdownboxes.push_back( CreateWindow(WC_COMBOBOX, TEXT(""), 
        CBS_DROPDOWNLIST | CBS_HASSTRINGS |  WS_BORDER |WS_CHILD  | WS_VISIBLE,
        startx+285, 95, 160, 200,
        hwnd, (HMENU) cbDPSYSTEMPLOT1, 
        NULL,NULL));

        {// add the strings to the drop down list
        TCHAR A[40];
        TCHAR holds[40] = TEXT("Position Simulation");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds);
        SendMessage(dropdownboxes[1],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 

        TCHAR holds1[30] = TEXT("Energy Simulation");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds1);
        SendMessage(dropdownboxes[1],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 

        TCHAR holds2[30] = TEXT("Angle Simulation");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds2);
        SendMessage(dropdownboxes[1],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 

        TCHAR holds3[30] = TEXT("Velocity Simulation");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds3);
        SendMessage(dropdownboxes[1],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 

        TCHAR holds4[30] = TEXT("Static Plot");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds4);
        SendMessage(dropdownboxes[1],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 

        SendMessage(dropdownboxes[1], CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
        }


        // this si where the user makes their plot choice for plot 1
        dropdownboxes.push_back( CreateWindow(WC_COMBOBOX, TEXT(""), 
        CBS_DROPDOWNLIST | CBS_HASSTRINGS |  WS_BORDER |WS_CHILD  | WS_VISIBLE,
        startx+285, 215, 160, 200,
        hwnd, (HMENU) cbDPSYSTEMPLOT2, 
        NULL,NULL));

        {// add the strings to the drop down list
        TCHAR A[40];
        TCHAR holds[40] = TEXT("Position Simulation");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds);
        SendMessage(dropdownboxes[2],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 

        TCHAR holds1[30] = TEXT("Energy Simulation");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds1);
        SendMessage(dropdownboxes[2],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 

        TCHAR holds2[30] = TEXT("Angle Simulation");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds2);
        SendMessage(dropdownboxes[2],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 

        TCHAR holds3[30] = TEXT("Velocity Simulation");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds3);
        SendMessage(dropdownboxes[2],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 

        TCHAR holds4[30] = TEXT("Static Plot");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds4);
        SendMessage(dropdownboxes[2],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 

        SendMessage(dropdownboxes[2], CB_SETCURSEL, (WPARAM)1, (LPARAM)0);
        }

}


//==============================
//======= EDIT TEXT BOXES ======
//==============================
std::vector<HWND> UIDoublePendulum::SetEditText(HWND & hwnd)
{
    // location Parameters
    int startx = 183;
    int starty = 82;
    int sizex = 45;
    int sizey = 23;
    int inc = 26;
    
    // upper pend. length edit box
     this->editboxes.push_back(
         CreateWindowW(L"Edit", L"0.5", 
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        startx, starty, sizex, sizey, hwnd, (HMENU) etDPULENGTH ,
        DPINSTANCE, NULL)
     );

     //upper pend. mass edit box
     this->editboxes.push_back(
         CreateWindowW(L"Edit", L"1.0", 
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            startx, starty+inc, sizex, sizey, hwnd, (HMENU) etDPUMASS ,
            DPINSTANCE, NULL)
     );

     // upper pend. angle edit box
     this->editboxes.push_back(
         CreateWindowW(L"Edit", L"45", 
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            startx, starty+2*inc, sizex, sizey, hwnd, (HMENU) etDPUANGLE ,
            DPINSTANCE, NULL)
     );

     // upper pend. velocity edit box
     this->editboxes.push_back(
         CreateWindowW(L"Edit", L"0.0", 
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            startx, starty+3*inc, sizex, sizey, hwnd, (HMENU) etDPUVEL ,
            DPINSTANCE, NULL)
        );


     // LOWER PENDULUM EDIT BOXES

     starty += 150;
     // length edit box
     this->editboxes.push_back(
         CreateWindowW(L"Edit", L"0.5", 
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        startx, starty, sizex, sizey, hwnd, (HMENU) etDPLLENGTH ,
        DPINSTANCE, NULL)
     );

     // mass edit box
     this->editboxes.push_back(
         CreateWindowW(L"Edit", L"1.0", 
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        startx, starty+inc, sizex, sizey, hwnd, (HMENU) etDPLMASS ,
        DPINSTANCE, NULL)
     );
     // starting angle edit box
     this->editboxes.push_back(
         CreateWindowW(L"Edit", L"45", 
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        startx, starty+2*inc, sizex, sizey, hwnd, (HMENU) etDPLANGLE ,
        DPINSTANCE, NULL)
     );
     // starting velocity edit box
     this->editboxes.push_back(
         CreateWindowW(L"Edit", L"0.0", 
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        startx, starty+3*inc, sizex, sizey, hwnd, (HMENU) etDPLVEL ,
        DPINSTANCE, NULL)
     );

      // Gravity Edit Box
     this->editboxes.push_back(
         CreateWindowW(L"Edit", L"9.81", 
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        startx, 344, sizex, sizey, hwnd, (HMENU) etDPGRAVITY ,
        DPINSTANCE, NULL)
     );

       // Sim Length Edit Box
     this->editboxes.push_back(
         CreateWindowW(L"Edit", L"10", 
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        startx+245, 286, sizex-2, sizey, hwnd, (HMENU) etDPSIMLENGTH ,
        DPINSTANCE, NULL)
     );

      // Sim Speed Edit Box
     this->editboxes.push_back(
         CreateWindowW(L"Edit", L"100", 
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        startx+245, 312, sizex-2, sizey, hwnd, (HMENU) etDPSIMSPEED ,
        DPINSTANCE, NULL)
     );



     //TODO Create edit text boxes for Sim speed and simulation time!
    return this->editboxes;
}
HWND & UIDoublePendulum::etGetHWND(int key)
{
    return this->editboxes[key];
}
//gets the value from the text box
double UIDoublePendulum::etGetValue(int i)
{
    int length = GetWindowTextLengthW(editboxes[i])+ 1;
    wchar_t* text =  new wchar_t[length+1];

    GetWindowTextW(editboxes[i], text, length);
        
    char holdvalue[100];
        
    for(int iii = 0;iii<length;iii++)
        holdvalue[iii] = *(text+iii);

    delete [] text;
    return atof(holdvalue); // converts c string to doubles
}
// increments the value of an edit box, corresponding to a user clicking a spin wheel
// @param incdec - true means to increment, false means to decrement
// @*param i      - which editbox to increment/decrement
void UIDoublePendulum::etIncrement(bool incdec, int i)
{
    double change = 0.1; 
    double value = 0;
    int sigfigs = 3;
    wchar_t newvalue[15];

    // this switch determines how much we are changing the text box value based on which spin control was used
    switch(i)
    {
        case(0):
        case(4):
            change = 0.1;
        break;

        case(1):
        case(5):
            change = 0.1;
        break;

        case(2):
        case(6):
            change = 1.0;
        break;

        case(3):
        case(7):
            change = 0.1;
        break;
        
        case(8):
            change = 0.1;
        break;

        case(9):
            change = 0.5;
        break;

        case(10):
            change = 1.0;
        break;
    }// end switch on with edit text we are changing
    
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
    // don't let the user set the length or mass too small
    if(!(i == 0 && value <= 0.1 && change <= 0) && !(i == 4 && value <= 0.1 && change <= 0))
    {
        if(!(i == 1 && value <= 0.05 && change <= 0) && !(i == 5 && value <= 0.05 && change <= 0)) 
        {
            value += change;
            // this part normalizes the angle 
            if((i == 2 || i == 6) && (value > 360.0 || value < -360.0))
            {
                int hold = (int)value;
                double leftover = (double)value-hold;
                hold = hold%360;
                value = hold+leftover;
            }
            swprintf(newvalue, L"%f", value);

            newvalue[sigfigs] = '\0'; // set the end of the new value based on the number of significant figures
            changeText(i, newvalue);
        }
    }
}
// change/set the text of the ith edit box
void UIDoublePendulum::changeText(int i, wchar_t arr[])
{
  if(editboxes.size() != 0)
      if(!(i == 8 && (etGetValue(i) < 0.5 || etGetValue(i) > 60))) // set the bounds on how high the user can change the text
        SetWindowTextW(editboxes[i], arr);
}
void UIDoublePendulum::resetTextBoxes()
{
    for(int i = 0; i < this->getSpinControls().size(); i++)
    {
        if(i == 0 || i == 4)
            changeText(i, L"0.5"); // length default
        else if(i == 1 || i ==5)
            changeText(i, L"1.0"); // mass default
        else if(i == 2 || i == 6)
            changeText(i, L"45");  //theta default
        else if(i == 3 || i ==7)
            changeText(i, L"0.0"); // angular velocity default
        else if(i == 8)
            changeText(i, L"9.81");// gravity default

    }
}// end function randomize
void UIDoublePendulum::randomizeValues()
{
    static std::default_random_engine generator;
    static std::uniform_real_distribution<double> distribution(0, 1.0);
    double newrandomvalue = 0.0;
    wchar_t text[15];
    
    //randomize the upper length
    newrandomvalue = distribution(generator);
    newrandomvalue *= 6.0 + .2;  // {.2, 5.2}  
    swprintf(text, L"%f", newrandomvalue);
    text[4] = '\0';
    changeText(0, text);

    // randomize the upper mass
    newrandomvalue = distribution(generator);
    newrandomvalue *= 6.0 + .2; // {.2, 6.2}
    swprintf(text, L"%f", newrandomvalue);
    text[4] = '\0';
    changeText(1, text);
            
    // randomize the upper angle
    newrandomvalue = distribution(generator);
    newrandomvalue = newrandomvalue*360.0 - 180; // {-7, 7}
    (newrandomvalue >= 10 || newrandomvalue <= -10)? text[5] = '\0' : text[4] = '\0';
    swprintf(text, L"%d", (int)newrandomvalue);
    changeText(2, text);

    // randomize the upper velocity
    newrandomvalue = distribution(generator);
    newrandomvalue = newrandomvalue*14.0 - 7.0; // {-7, 7}
    swprintf(text, L"%f", newrandomvalue);
    text[4] = '\0';
    changeText(3, text);

    // the next 4 are the same but for the lower pendulum
    newrandomvalue = distribution(generator);
    newrandomvalue *= 5.0 + .2;
    swprintf(text, L"%f", newrandomvalue);
    text[4] = '\0';
    changeText(4, text);

    newrandomvalue = distribution(generator);
    newrandomvalue *= 6.0 + .2;
    swprintf(text, L"%f", newrandomvalue);
    text[4] = '\0';
    changeText(5, text);
            
    newrandomvalue = distribution(generator);
    newrandomvalue = newrandomvalue*360.0 - 180;
    swprintf(text, L"%d", (int)newrandomvalue);
    (newrandomvalue >= 10 || newrandomvalue <= -10)? text[5] = '\0' : text[4] = '\0';
    changeText(6, text);

    newrandomvalue = distribution(generator);
    newrandomvalue = newrandomvalue*14.0 - 7.0;
    swprintf(text, L"%f", newrandomvalue);
    text[4] = '\0';
    changeText(7, text);
    
}


//===================================
// ============ SPIN CONTROL ========
//===================================
void UIDoublePendulum::SetSpinControl(HWND & hwnd)
{
    int startx = 228;
    int starty = 83;
    int sizex = 50;
    int sizey = 22;
    
    // upper length
    this->spincontrols.push_back(CreateWindowW(UPDOWN_CLASS, NULL, WS_CHILD | WS_VISIBLE | UDS_ARROWKEYS,
                   startx, starty, sizex, sizey, hwnd, (HMENU) scDPULENGTH, NULL, NULL));

     // upper mass
     this->spincontrols.push_back(CreateWindowW(UPDOWN_CLASS, NULL, WS_CHILD | WS_VISIBLE | UDS_ARROWKEYS,
                   startx, starty+sizey+4, sizex, sizey, hwnd, (HMENU) scDPUMASS, NULL, NULL));

     // upper starting angle
     this->spincontrols.push_back(CreateWindowW(UPDOWN_CLASS, NULL, WS_CHILD | WS_VISIBLE | UDS_ARROWKEYS,
                   startx, starty+2*(sizey+4), sizex, sizey,hwnd, (HMENU) scDPUANGLE, NULL, NULL));

     // upper starting velocity
     this->spincontrols.push_back(CreateWindowW(UPDOWN_CLASS, NULL, WS_CHILD | WS_VISIBLE | UDS_ARROWKEYS,
                   startx, starty+3*(sizey+4), sizex, sizey, hwnd, (HMENU) scDPUVEL, NULL, NULL));


     starty = starty+150;
     // lower length
     this->spincontrols.push_back(CreateWindowW(UPDOWN_CLASS, NULL, WS_CHILD | WS_VISIBLE | UDS_ARROWKEYS,
                   startx, starty, sizex, sizey, hwnd, (HMENU) scDPLLENGTH, NULL, NULL));
     // lower mass
     this->spincontrols.push_back(CreateWindowW(UPDOWN_CLASS, NULL, WS_CHILD | WS_VISIBLE | UDS_ARROWKEYS,
                   startx, starty+sizey+4, sizex, sizey,hwnd, (HMENU) scDPLMASS, NULL, NULL));

     // lower starting angle
     this->spincontrols.push_back(CreateWindowW(UPDOWN_CLASS, NULL, WS_CHILD | WS_VISIBLE | UDS_ARROWKEYS,
                   startx, starty+2*(sizey+4), sizex, sizey, hwnd, (HMENU) scDPLANGLE, NULL, NULL));

     // lower starting velocity
     this->spincontrols.push_back(CreateWindowW(UPDOWN_CLASS, NULL, WS_CHILD | WS_VISIBLE | UDS_ARROWKEYS,
                   startx, starty+3*(sizey+4), sizex, sizey, hwnd, (HMENU) scDPLVEL, NULL, NULL));




     // simulation length
     this->spincontrols.push_back(CreateWindowW(UPDOWN_CLASS, NULL, WS_CHILD | WS_VISIBLE | UDS_ARROWKEYS,
                   startx, 345, sizex, sizey, hwnd, (HMENU) scDPGRAVITY, NULL, NULL));

     // simulation length
     this->spincontrols.push_back(CreateWindowW(UPDOWN_CLASS, NULL, WS_CHILD | WS_VISIBLE | UDS_ARROWKEYS,
                   startx+242, 287, sizex, sizey, hwnd, (HMENU) scDPSIMLENGTH, NULL, NULL));

     // simulation speed
     this->spincontrols.push_back(CreateWindowW(UPDOWN_CLASS, NULL, WS_CHILD | WS_VISIBLE | UDS_ARROWKEYS,
                   startx+242, 313, sizex, sizey, hwnd, (HMENU) scDPSIMSPEED, NULL, NULL));

}// end set spin control
std::vector<HWND> & UIDoublePendulum::getSpinControls()
{
    return this->spincontrols;
}


// =====================================
// ====== Pendulum System Control ======
// =====================================
void UIDoublePendulum::setCurrentSystem(int currentsystem)
{
    if(currentsystem == 1 || currentsystem == 2) // validate that we are setting it to either system 1 or 2
        this->currentsystem = currentsystem;
}
int UIDoublePendulum::getCurrentSystem()
{
    return this->currentsystem;
}

/*
*    @param key : which system to save, double pendulum system 1 or 2
*    @param sim : The SIMDoublePendulum class that contains all of the simulation information
*/
void UIDoublePendulum::SaveSystem(int key, SIMDoublePendulum * sim)
{
    DoublePendulumSystem holdsystem;
    Pendulum holdpend;

    // the numbers correspond to the text boxes from top to bottom
    holdpend.setLength (this->etGetValue(0));
    holdpend.setMass   (this->etGetValue(1));
    holdpend.setAngle  (this->etGetValue(2));
    holdpend.setAngVel (this->etGetValue(3));

    holdsystem.setUpper(holdpend);

    holdpend.setLength (this->etGetValue(4));
    holdpend.setMass   (this->etGetValue(5));
    holdpend.setAngle  (this->etGetValue(6));
    holdpend.setAngVel (this->etGetValue(7));

    holdsystem.setLower(holdpend);

    holdsystem.setGravity(this->etGetValue(8));

    if(key == 1)
        sim->setSystem1(holdsystem);
    else if(key == 2)
        sim->setSystem2(holdsystem);

}

/*
*    @param key : which system to save
*    @param sim : The SIMDoublePendulum class that contains all of the simulation information
*/
void UIDoublePendulum::LoadSystem(int key, SIMDoublePendulum* sim)
{
    double valuearray[9];

    // get all of the initial condition values from the system we are loading
    if(key == 1)
    {
        valuearray[0] = sim->getSystem1().getUpper().getLength();
        valuearray[1] = sim->getSystem1().getUpper().getMass();
        valuearray[2] = sim->getSystem1().getUpper().getAngle();
        valuearray[3] = sim->getSystem1().getUpper().getAngVel();
        valuearray[4] = sim->getSystem1().getLower().getLength();
        valuearray[5] = sim->getSystem1().getLower().getMass();
        valuearray[6] = sim->getSystem1().getLower().getAngle();
        valuearray[7] = sim->getSystem1().getLower().getAngVel();
        valuearray[8] = sim->getSystem1().getGravity();
    }
    else if(key == 2)
    {
        valuearray[0] = sim->getSystem2().getUpper().getLength();
        valuearray[1] = sim->getSystem2().getUpper().getMass();
        valuearray[2] = sim->getSystem2().getUpper().getAngle();
        valuearray[3] = sim->getSystem2().getUpper().getAngVel();
        valuearray[4] = sim->getSystem2().getLower().getLength();
        valuearray[5] = sim->getSystem2().getLower().getMass();
        valuearray[6] = sim->getSystem2().getLower().getAngle();
        valuearray[7] = sim->getSystem2().getLower().getAngVel();
        valuearray[8] = sim->getSystem2().getGravity();
    }
    for(int i = 0; i < 9; i++) // editbox.size-2 becuase we don't want to load the simulation time and simulation speed simboxes, those are constant
    {
        double change = .1;
        int sigfigs = 3;

        wchar_t newvalue[15];
        swprintf(newvalue, L"%f", valuearray[i]);
        // determines the significant figures 
        if(valuearray[i] <= 0 && valuearray[i] > -10+2*.1)
            sigfigs = 4;
        else if(valuearray[i] <= -10.0-2*change && valuearray[i] > -100+2*change)
            sigfigs = 5;
        else if(valuearray[i] <= -100.0+2*change)
            sigfigs = 6;
        else
        {
            (valuearray[i] < 9.9)? sigfigs = 4: true;
            (valuearray[i] >= 10.0-change && valuearray[i] < 100-change)? sigfigs = 5: sigfigs = 4;
            (valuearray[i] >= 100-change)? sigfigs = 5: true;
        }
        newvalue[sigfigs] = '\0';
        this->changeText(i, newvalue);
    }
}