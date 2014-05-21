#include "DPPositionPlot.h"

/**
*    @author John Allard
*    This is the implementation of the DPPositionPlot class. This class holds all of the data necessary to fully describe the
*    position plot of a double pendulum system as it moves throughout time.
*/    


DPPositionPlot::DPPositionPlot(int plottype, int system, bool hasgrid, std::string title, bool hasline)
    :DPPlotSettings(plottype, system, hasgrid, "Position Simulation")
{
    this->setHasLine(hasline);
    this->setLineThickness(.5);
    this->colors.push_back(PROGRAMCOLORS.colorlist[DEEPORANGE]);
    this->colors.push_back(PROGRAMCOLORS.colorlist[DEEPBLUE]);
    this->colors.push_back(PROGRAMCOLORS.colorlist[RED]);
}

void DPPositionPlot::setHasLine(bool hasline)
{
    this->hasline = hasline;
}
bool DPPositionPlot::getHasLine() const
{
    return this->hasline;
}

void DPPositionPlot::setLineThickness(double thickness)
{
    if(thickness > 0 && thickness < 3)
    {
        this->linethickness = thickness;
    }
}
double DPPositionPlot::getLineThickness() const
{
    return this->linethickness;
}

void DPPositionPlot::setColor(int key, int color[3])
{
    for(int i = 0; i < 3; i++)
    {
        this->colors[key][i] = color[i];
    }
}
int* DPPositionPlot::getColor(int key)
{
    int * ptrcolor;
    ptrcolor = this->colors[key];

    return ptrcolor;
}

void DPPositionPlot::setButtonsPictures(HWND& hwnd)    
{

    // background picture for position plot menu
    HWND background = CreateWindowExW(NULL, L"STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 10 , 10, 0, 0, hwnd, 0, NULL, NULL);
    HANDLE background1 = LoadImage(NULL, L"..//Pictures//DPSim//Dialog//PositionBackGround.bmp",IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SendMessage(background, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) background1);

    // checkbox to include trailing line
    CreateWindow(TEXT("button"), 
                 TEXT(""),
                 WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,
                 177, 129, 12, 12,
                 hwnd,
                 (HMENU) cbDPINCLUDELINE,
                 NULL, NULL);    

    if(this->getHasLine())
        CheckDlgButton(hwnd, cbDPINCLUDELINE , BST_CHECKED);
    else
        CheckDlgButton(hwnd, cbDPINCLUDELINE , BST_UNCHECKED);

    DPPlotSettings::setButtonsPictures(hwnd);
}
std::vector<HWND> DPPositionPlot::setEditText(HWND& hwnd, const HINSTANCE & hInst)
{
    if(edittext.size() == 1)
        edittext.clear();

     this->edittext.push_back(
            CreateWindowW(L"Edit", L"", 
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            177, 175, 40, 20, hwnd, (HMENU) etDPLINETHICKNESS ,
            hInst, NULL));

     double x = this->getLineThickness();
     wchar_t newvalue[20];
     swprintf(newvalue, L"%f", x);
    
    newvalue[3] = '\0'; // set the end of the new value based on the number of significant figures
    changeText(0, newvalue);

    DPPlotSettings::setEditText(hwnd);

    return this->edittext;
}

std::vector<HWND> DPPositionPlot::setSpinControl(HWND & hwnd)
{
    if(this->spincontrols.size() == 1)
        spincontrols.clear();
    this->spincontrols.push_back(CreateWindowW(UPDOWN_CLASS, NULL, 
               WS_CHILD | WS_VISIBLE | UDS_ARROWKEYS,
               217, 175, 25, 20, 
               hwnd, (HMENU) scDPLINETHICKNESS, NULL, NULL));

    DPPlotSettings::setSpinControl(hwnd);
    return this->spincontrols;
}

std::vector<HWND> DPPositionPlot::setDropDown(HWND& hwnd)
{

    if(dropdownboxes.size() == 3)
        dropdownboxes.clear();

    // upper mass color
    this->dropdownboxes.push_back(CreateWindow(WC_COMBOBOX, TEXT(""), 
        CBS_DROPDOWNLIST | CBS_HASSTRINGS |  WS_BORDER |WS_CHILD  | WS_VISIBLE,
        177, 71, 130, 300,
        hwnd, (HMENU) ddDPUMASSCOLOR, 
        NULL,NULL));

    // lower mass color
    this->dropdownboxes.push_back(CreateWindow(WC_COMBOBOX, TEXT(""), 
        CBS_DROPDOWNLIST | CBS_HASSTRINGS |  WS_BORDER |WS_CHILD  | WS_VISIBLE,
        177, 98, 130, 300,
        hwnd, (HMENU) ddDPLMASSCOLOR, 
        NULL,NULL));

    // line color
    this->dropdownboxes.push_back(CreateWindow(WC_COMBOBOX, TEXT(""), 
        CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD  | WS_VISIBLE,
        177, 146, 130, 300,
        hwnd, (HMENU) ddDPLINECOLOR, 
        NULL,NULL));

    for(int i = 0; i < 3; i++)
    {
        TCHAR A[25];
        TCHAR holds[30] = TEXT("black");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds);
        SendMessage(this->dropdownboxes[i],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A);

        TCHAR holds1[30] = TEXT("white");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds1);
        SendMessage(this->dropdownboxes[i],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 

        TCHAR holds2[30] = TEXT("red");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds2);
        SendMessage(this->dropdownboxes[i],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 
        TCHAR holds3[30] = TEXT("deep red");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds3);
        SendMessage(this->dropdownboxes[i],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A);

        TCHAR holds4[30] = TEXT("orange");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds4);
        SendMessage(this->dropdownboxes[i],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 
        TCHAR holds5[30] = TEXT("deep orange");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds5);
        SendMessage(this->dropdownboxes[i],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A);

        TCHAR holds6[30] = TEXT("green");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds6);
        SendMessage(this->dropdownboxes[i],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 
        TCHAR holds7[30] = TEXT("deep green");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds7);
        SendMessage(this->dropdownboxes[i],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A);

        TCHAR holds8[30] = TEXT("blue");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds8);
        SendMessage(this->dropdownboxes[i],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 
        TCHAR holds9[30] = TEXT("deep blue");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds9);
        SendMessage(this->dropdownboxes[i],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A);

        TCHAR holds10[30] = TEXT("purple");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds10);
        SendMessage(this->dropdownboxes[i],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 

        TCHAR holds11[30] = TEXT("gray");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds11);
        SendMessage(this->dropdownboxes[i],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A);
        TCHAR holds12[30] = TEXT("deep gray");
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds12);
        SendMessage(this->dropdownboxes[i],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A);
    }

    // set the drop down box selection to match the color that it stored in the class
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 13; j++)
        {
            // since all colors have unique first elements, we only see if the first elements are the same in making a decision
            if(this->getColor(i)[0] == PROGRAMCOLORS.colorlist[j][0])
                SendMessage(this->dropdownboxes[i], CB_SETCURSEL, (WPARAM)j, (LPARAM)0);
        }
    }
    return this->dropdownboxes;
}

// processes the messages that have to deal with the UI this class creates
void DPPositionPlot::processMessage(HWND & hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    
    static NMUPDOWN * updowncontrol = NULL;
    switch(msg)
    {

        // this is where commands from UI elements are         
        case WM_COMMAND:
        {
            //---- DROP DOWN LISTS ------//
            if(HIWORD(wParam) == CBN_SELCHANGE)
            {
                for(int i = 0; i < dropdownboxes.size(); i++)
                {
                    if(lParam == (LPARAM)this->dropdownboxes[i])
                    {
                        int ItemIndex = SendMessage((HWND) lParam, (UINT) CB_GETCURSEL,(WPARAM) 0, (LPARAM) 0);
                        this->colors[i] = PROGRAMCOLORS.colorlist[ItemIndex];
                    }// end if the drop down list was #1
                }// end for loop
    
            }// end if drop down list


            //---- CHECKBOXES ----
            switch((wParam))
            {
                case(cbDPINCLUDELINE):
                    this->setHasLine(!IsDlgButtonChecked(hwnd, cbDPINCLUDELINE));

                    if(IsDlgButtonChecked(hwnd, cbDPINCLUDELINE))
                        CheckDlgButton(hwnd, cbDPINCLUDELINE , BST_UNCHECKED);
                    else
                        CheckDlgButton(hwnd, cbDPINCLUDELINE , BST_CHECKED);
                break;
            }// end switch for checkboxes


        }// end case WMCOMMAND
        break;


        //------SPIN CONTROL--------
        case(WM_NOTIFY):
            updowncontrol = (LPNMUPDOWN) lParam;
        break;
        case(WM_VSCROLL):
        {
            if(updowncontrol != NULL)
            {
                boolean upordown = true; // true means up, false means down
                // determine if the user is trying to increase or decrease the counter
                if(updowncontrol->iDelta == -1.0)
                upordown = true;
                else if(updowncontrol->iDelta == 1.0)
                    upordown = false;
                else{break;} // it's a switch statement so breaks are okay!!

                etIncrement(upordown, 0);
                this->setLineThickness(etGetValue(0));
            }
        }
        break;

    }// end switch on message
    
    // forward to parent class to process heirarchy wide UI
    DPPlotSettings::processMessage(hwnd, msg, wParam, lParam);
}


