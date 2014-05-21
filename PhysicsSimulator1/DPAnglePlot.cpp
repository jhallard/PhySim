#include "DPAnglePlot.h"

/**
*    author John Allard
*    This is the implementation of the DPAnglePlot Class. This class holds all of the info and functionality
*    to fully describe a double pendulum angle vs time or parametric angle simulation. This includes the colors of the plot line
*    the type of plot (upper angle vs time, lower angle vs time, or upper angle vs lower angle (parametric)), and if the user
*    wants to have the angle normalized. Also it handles the units of the plot.
*
*/


DPAnglePlot::DPAnglePlot(int type, int system, bool hasgrid, std::string title, int plottype, double units, bool normalized, double linethickness)
    :DPPlotSettings(type, system, hasgrid, title)
{
    PROGRAMCOLORS = Colors();
    setAnglePlotType(plottype);
    setUnits(units);
    setNormalized(normalized);
    this->setLineThickness(linethickness);

    this->colors.push_back(PROGRAMCOLORS.colorlist[DEEPORANGE]); // set the default line color to deep orange
}

void DPAnglePlot::setLineThickness(double thickness)
{
    if(thickness > 0 && thickness < 2)
        this->linethickness = thickness;
}
void DPAnglePlot::setAnglePlotType(int type)
{
    if((type >= 0 && type <= PARAMETRICPLOT+1))
        this->angleplottype = type;
}
void DPAnglePlot::setUnits(int units)
{
    this->units = units;
}
void DPAnglePlot::setNormalized(bool value)
{
    this->normalized = value;
}

double DPAnglePlot::getLineThickness() const
{
    return this->linethickness;
}
int DPAnglePlot::getAnglePlotType() const
{
    return this->angleplottype;
}
int DPAnglePlot::getUnits() const
{
    return this->units;
}
bool DPAnglePlot::getNormalized() const
{
    return this->normalized;
}

void DPAnglePlot::setColor(int key, int color[3])
{
    if(key < colors.size())
    {
        for(int i = 0; i < 3; i++)
            this->colors[key][i] = color[i];
    }
}
int* DPAnglePlot::getColor(int key) const
{
    int * ptrcolor;
    if(key < colors.size())
        ptrcolor = this->colors[key];
    else
        ptrcolor = colors[0];

    return ptrcolor;
}

void DPAnglePlot::setButtonsPictures(HWND& hwnd)    
{
    HWND background = CreateWindowExW(NULL, L"STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 10 , 10, 0, 0, hwnd, 0, NULL, NULL);
    HANDLE background1 = LoadImage(NULL, L"..//Pictures//DPSim//Dialog//AngleBackGround.bmp",IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SendMessage(background, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) background1);

    // checkbox to normalize angles
    CreateWindow(TEXT("button"), 
        TEXT(""),
        WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,
        140, 125, 12, 12,
        hwnd,
        (HMENU) cbDPNORMALIZE,
        NULL, NULL);
    // initialize the textboxes based on the class data
    if(this->getNormalized())
        CheckDlgButton(hwnd, cbDPNORMALIZE , BST_CHECKED);
    else
        CheckDlgButton(hwnd, cbDPNORMALIZE , BST_UNCHECKED);


    DPPlotSettings::setButtonsPictures(hwnd);
}
std::vector<HWND> DPAnglePlot::setEditText(HWND& hwnd,const HINSTANCE & hInst)
{
    if(edittext.size() == 1)
        edittext.clear();

    this->edittext.push_back(
        CreateWindowW(L"Edit", L"", 
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        140, 175, 40, 20, hwnd, (HMENU) etDPLINEWIDTH ,
        hInst, NULL));

    // set value of linethickness text box
    double x = this->getLineThickness();
    wchar_t newvalue[20];
    swprintf(newvalue, L"%f", x);

    newvalue[3] = '\0'; // set sigfigs
    changeText(0, newvalue);

    DPPlotSettings::setEditText(hwnd, hInst);
    return this->edittext;
}
std::vector<HWND> DPAnglePlot::setDropDown(HWND& hwnd)
{
    // for when the user reopens the window
    if(dropdownboxes.size() == 3)
        dropdownboxes.clear();

    // Type of angle simulation
    this->dropdownboxes.push_back(CreateWindow(WC_COMBOBOX, TEXT(""), 
        CBS_DROPDOWNLIST | CBS_HASSTRINGS |  WS_BORDER |WS_CHILD  | WS_VISIBLE,
        220, 70, 140, 300,
        hwnd, (HMENU) ddDPANGLETYPE, 
        NULL,NULL));

    // Units for simulation
    this->dropdownboxes.push_back(CreateWindow(WC_COMBOBOX, TEXT(""), 
        CBS_DROPDOWNLIST | CBS_HASSTRINGS |  WS_BORDER |WS_CHILD  | WS_VISIBLE,
        220, 95, 140, 300,
        hwnd, (HMENU) ddDPANGLEUNITS, 
        NULL,NULL));

    // line color
    this->dropdownboxes.push_back(CreateWindow(WC_COMBOBOX, TEXT(""), 
        CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD  | WS_VISIBLE,
        140, 146, 130, 300,
        hwnd, (HMENU) ddDPANGLECOLOR, 
        NULL,NULL));

    for(int i = 0; i < 3; i++)
    {

        if(i == 0)
        {
            TCHAR A[25];
            TCHAR holds[30] = TEXT("Upper vs Time");
            wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds);
            SendMessage(this->dropdownboxes[i],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A);

            TCHAR holds1[30] = TEXT("Lower vs. Time");
            wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds1);
            SendMessage(this->dropdownboxes[i],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 

            TCHAR holds2[30] = TEXT("Upper vs. Lower");
            wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds2);
            SendMessage(this->dropdownboxes[i],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 
        }

        else if(i == 1)
        {
            TCHAR A[25];
            TCHAR holds[30] = TEXT("Degrees");
            wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds);
            SendMessage(this->dropdownboxes[i],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A);

            TCHAR holds1[30] = TEXT("Radians");
            wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds1);
            SendMessage(this->dropdownboxes[i],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 

            TCHAR holds2[30] = TEXT("Revolutions");
            wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)holds2);
            SendMessage(this->dropdownboxes[i],(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 
        }

        else if(i == 2)
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

    }

    SendMessage(this->dropdownboxes[0], CB_SETCURSEL, (WPARAM)this->getAnglePlotType(), (LPARAM)0);
    SendMessage(this->dropdownboxes[1], CB_SETCURSEL, (WPARAM)this->getUnits(), (LPARAM)0);
    for(int j = 0; j < 13; j++)
    {
        // since all colors have unique first elements, we only see if the first elements are the same in making a decision
        if(this->getColor(0)[0] == PROGRAMCOLORS.colorlist[j][0])
            SendMessage(this->dropdownboxes[2], CB_SETCURSEL, (WPARAM)j, (LPARAM)0);
    }

    return this->dropdownboxes;
}
std::vector<HWND> DPAnglePlot::setSpinControl(HWND & hwnd)
{
    if(this->spincontrols.size() == 1)
        spincontrols.clear();

    this->spincontrols.push_back(CreateWindowW(UPDOWN_CLASS, NULL, 
        WS_CHILD | WS_VISIBLE | UDS_ARROWKEYS,
        180, 175, 25, 20, 
        hwnd, (HMENU) scDPLINEWIDTH, NULL, NULL));

    DPPlotSettings::setSpinControl(hwnd);
    return this->spincontrols;
}

void DPAnglePlot::processMessage(HWND & hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
                if(lParam == (LPARAM)this->dropdownboxes[0])
                {
                    int ItemIndex = SendMessage((HWND) lParam, (UINT) CB_GETCURSEL,(WPARAM) 0, (LPARAM) 0);
                    this->setAnglePlotType(ItemIndex);
                }
                else if(lParam == (LPARAM)this->dropdownboxes[1])
                {
                    int ItemIndex = SendMessage((HWND) lParam, (UINT) CB_GETCURSEL,(WPARAM) 0, (LPARAM) 0);
                    this->setUnits(ItemIndex);
                }
                else if(lParam == (LPARAM)this->dropdownboxes[2])
                {
                    int ItemIndex = SendMessage((HWND) lParam, (UINT) CB_GETCURSEL,(WPARAM) 0, (LPARAM) 0);
                    this->colors[0] = PROGRAMCOLORS.colorlist[ItemIndex];
                }// end if the drop down list was #1


            }// end if drop down list


            //---- CHECKBOXES ----
            switch((wParam))
            {
            case(cbDPNORMALIZE):
                this->setNormalized(!IsDlgButtonChecked(hwnd, cbDPNORMALIZE));

                if(IsDlgButtonChecked(hwnd, cbDPNORMALIZE))
                    CheckDlgButton(hwnd, cbDPNORMALIZE , BST_UNCHECKED);
                else
                    CheckDlgButton(hwnd, cbDPNORMALIZE , BST_CHECKED);
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