#include "DPEnergyPlot.h"
/**
*    @author John Allard
*    This is the implementation of the DPEnergyPlot class that completely describes the Energy bar plot
*    of a single double pendulum system.
*
*/

DPEnergyPlot::DPEnergyPlot(int type, int system, bool hasgrid, std::string title,bool kinetic, bool potential, bool total)
    : DPPlotSettings(type, system, hasgrid, title)
{
    PROGRAMCOLORS = Colors();
    this->setKinetic(kinetic);
    this->setPotential(potential);
    this->setTotal(total);

    // kinetic energy color, potential energy color, total energy color
    this->colors.push_back(PROGRAMCOLORS.colorlist[DEEPBLUE]);
    this->colors.push_back(PROGRAMCOLORS.colorlist[DEEPORANGE]);
    this->colors.push_back(PROGRAMCOLORS.colorlist[DEEPRED]);

}

void DPEnergyPlot::setKinetic(bool value)
{
    this->kinetic = value;
}
bool DPEnergyPlot::getKinetic() const
{
    return this->kinetic;
}
void DPEnergyPlot::setPotential(bool value)
{
    this->potential = value;
}
bool DPEnergyPlot::getPotential() const
{
    return this->potential;
}
void DPEnergyPlot::setTotal(bool value)
{
    this->total = value;
}
bool DPEnergyPlot::getTotal() const
{
    return this->total;
}

void DPEnergyPlot::setColor(int key, int color[3])
{
    if(key < colors.size())
    {
        for(int i = 0; i < 3; i++)
        {
            this->colors[key][i] = color[i];
        }
    }
}
int* DPEnergyPlot::getColor(int key)
{
    int * ptrcolor;
    if(key < colors.size())
         ptrcolor = this->colors[key];
    else
        ptrcolor = colors[0];

    return ptrcolor;
}


void DPEnergyPlot::setButtonsPictures(HWND& hwnd)    
{
    HWND background = CreateWindowExW(NULL, L"STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 10 , 10, 0, 0, hwnd, 0, NULL, NULL);
    HANDLE background1 = LoadImage(NULL, L"..//Pictures//DPSim//Dialog//EnergyBackGround.bmp",IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SendMessage(background, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) background1);


    // checkbox to include trailing line
    CreateWindow(TEXT("button"), 
                 TEXT(""),
                 WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,
                 90, 90, 12, 12,
                 hwnd,
                 (HMENU) cbDPINCLUDEKIN,
                 NULL, NULL);

    // checkbox to include trailing line
    CreateWindow(TEXT("button"), 
                 TEXT(""),
                 WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,
                 90, 138, 12, 12,
                 hwnd,
                 (HMENU) cbDPINCLUDEPOT,
                 NULL, NULL);    

    // checkbox to include trailing line
    CreateWindow(TEXT("button"), 
                 TEXT(""),
                 WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,
                 90, 184, 12, 12,
                 hwnd,
                 (HMENU) cbDPINCLUDETOT,
                 NULL, NULL);    

    // initialize the textboxes based on the class data
    if(this->getKinetic())
        CheckDlgButton(hwnd, cbDPINCLUDEKIN , BST_CHECKED);
    else
        CheckDlgButton(hwnd, cbDPINCLUDEKIN , BST_UNCHECKED);

    if(this->getPotential())
        CheckDlgButton(hwnd, cbDPINCLUDEPOT , BST_CHECKED);
    else
        CheckDlgButton(hwnd, cbDPINCLUDEPOT, BST_UNCHECKED);

    if(this->getTotal())
        CheckDlgButton(hwnd, cbDPINCLUDETOT , BST_CHECKED);
    else
        CheckDlgButton(hwnd, cbDPINCLUDETOT , BST_UNCHECKED);

    DPPlotSettings::setButtonsPictures(hwnd);
}
std::vector<HWND> DPEnergyPlot::setEditText(HWND& hwnd,const HINSTANCE & hInst)
{
    std::vector<HWND> hold;
    DPPlotSettings::setEditText(hwnd);

    return hold;
}
std::vector<HWND> DPEnergyPlot::setDropDown(HWND& hwnd)
{
    
    if(dropdownboxes.size() == 3)
        dropdownboxes.clear();

    // upper mass color
    this->dropdownboxes.push_back(CreateWindow(WC_COMBOBOX, TEXT(""), 
        CBS_DROPDOWNLIST | CBS_HASSTRINGS |  WS_BORDER |WS_CHILD  | WS_VISIBLE,
        210, 85, 130, 300,
        hwnd, (HMENU) ddDPUMASSCOLOR, 
        NULL,NULL));

    // lower mass color
    this->dropdownboxes.push_back(CreateWindow(WC_COMBOBOX, TEXT(""), 
        CBS_DROPDOWNLIST | CBS_HASSTRINGS |  WS_BORDER |WS_CHILD  | WS_VISIBLE,
        210, 130, 130, 300,
        hwnd, (HMENU) ddDPLMASSCOLOR, 
        NULL,NULL));

    // line color
    this->dropdownboxes.push_back(CreateWindow(WC_COMBOBOX, TEXT(""), 
        CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD  | WS_VISIBLE,
        210, 176, 130, 300,
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
std::vector<HWND> DPEnergyPlot::setSpinControl(HWND & hwnd)
{
    std::vector<HWND> hold;
    DPPlotSettings::setSpinControl(hwnd);
    return hold;
}

void DPEnergyPlot::processMessage(HWND & hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
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
                // include kinetic energy check box
                case(cbDPINCLUDEKIN):
                    this->setKinetic(!IsDlgButtonChecked(hwnd, cbDPINCLUDEKIN));

                    if(IsDlgButtonChecked(hwnd, cbDPINCLUDEKIN))
                        CheckDlgButton(hwnd, cbDPINCLUDEKIN , BST_UNCHECKED);
                    else
                        CheckDlgButton(hwnd, cbDPINCLUDEKIN , BST_CHECKED);
                break;

                // include kinetic energy check box
                case(cbDPINCLUDEPOT):
                    this->setPotential(!IsDlgButtonChecked(hwnd, cbDPINCLUDEPOT));

                    if(IsDlgButtonChecked(hwnd, cbDPINCLUDEPOT))
                        CheckDlgButton(hwnd, cbDPINCLUDEPOT , BST_UNCHECKED);
                    else
                        CheckDlgButton(hwnd, cbDPINCLUDEPOT , BST_CHECKED);
                break;

                // include kinetic energy check box
                case(cbDPINCLUDETOT):
                    this->setTotal(!IsDlgButtonChecked(hwnd, cbDPINCLUDETOT));

                    if(IsDlgButtonChecked(hwnd, cbDPINCLUDETOT))
                        CheckDlgButton(hwnd, cbDPINCLUDETOT , BST_UNCHECKED);
                    else
                        CheckDlgButton(hwnd, cbDPINCLUDETOT , BST_CHECKED);
                break;
            }// end switch for checkboxes


        }// end case WMCOMMAND
        break;

    }// end switch on message
    
    // forward to parent class to process heirarchy wide UI
    DPPlotSettings::processMessage(hwnd, msg, wParam, lParam);
}