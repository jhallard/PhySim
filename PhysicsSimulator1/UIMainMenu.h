#ifndef UIMAINMENU_H
#define UIMAINMENU_H


#include <Windows.h>
#include "ProgramDefines.h"


/**
* @author John Allard
*  This class serves as the database for the main menu
*  It holds all of the information for the ui activity, including pictures
*  Button information, text boxes, etc.
*/
class UIMainMenu
{

    private:

    // these 6 hold the handles to the various windows that can be opened by the main menu. They include the main menu itself
    // and the other 5 simulations that this program can perform
    WNDCLASSEX mainwindow;
    WNDCLASSEX doublependulum;
    WNDCLASSEX wavesim2d;
    WNDCLASSEX wavesim3d;
    WNDCLASSEX springsim;
    WNDCLASSEX trajectorysim;

    public:
    // constructor 
    // Pass in the instance of the window that is calling to initiate an object of this class
    UIMainMenu(const HINSTANCE &);

    WNDCLASSEX & getMainWindow();
    HWND createMainMenu();

    WNDCLASSEX & getDoublePendWindow();
    HWND createDoublePendWindow();
    
    WNDCLASSEX & get2DWaveWindow();
    HWND create2DWaveWindow();
    
    WNDCLASSEX & get3DWaveWindow();
    HWND create3DWaveWindow();
    
    WNDCLASSEX & getSpringWindow();
    HWND createSpringWindow();
    
    WNDCLASSEX & getTrajecWindow();
    HWND createTrajecWindow();

    // this function gets called to set all of the pictures on the main menu
    // @param HWND the handle of the window that is having the pictures set
    void SetPictures(const HWND &);

    // this function gets called to set all of the buttons on the main menu
    // @param HWND the handle of the window that is having the buttons set
    void SetButtons(const HWND &);

};


#endif