/**
*    @author John Allard
*    This file contains only one function, the WinMain function that is equivilent of the main() function in c++ console programs
*    This function simply serves to create the main menu window and to dispatch the mesages that are sent throughout our program.
*/

#include <Windows.h>
#include <commctrl.h>
#include <sstream>
#include <stdio.h>

#include "ProgramDefines.h"
#include "ProcDoublePendulum.h"
#include "ProcMainMenu.h"
#include "UIMainMenu.h"



int WINAPI WinMain( HINSTANCE MainInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{

  MSG  msg ; // name of the messages we send out   
  HWND hwnd; //hwnd for the main menu window to be called

  // this class holds the information about all the windows that can be created in this program.
  static UIMainMenu MainWindow(MainInstance);

   WNDCLASSEX mainwindow = MainWindow.getMainWindow();
   if (!RegisterClassEx(&mainwindow))
    {
        MessageBox(NULL, TEXT("Call to RegisterClassEx failed!: WinMain"), TEXT("Error!"), NULL);
    }

    // create the main menu window with this member function call
    hwnd = MainWindow.createMainMenu();


    ShowWindow(hwnd,nCmdShow);
    UpdateWindow(hwnd);


  // message dispatcher
  
  while( GetMessage(&msg, NULL, 0, 0))
  {
     TranslateMessage(&msg);
     DispatchMessage(&msg);
  }
  return (int) msg.wParam;
}




