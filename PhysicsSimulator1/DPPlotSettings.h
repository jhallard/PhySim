#ifndef DPPLOTSETTINGS_H
#define DPPLOTSETTINGS_H

#include "ProgramDefines.h"

// these defines are the integer codes that represent which plot this class is for.
// Int at the end up the define represents the system
#define POSITIONPLOT1 0
#define ENERGYPLOT1   1
#define ANGLEPLOT1      2
#define ANGVELPLOT1      3
#define POSITIONPLOT2 4
#define ENERGYPLOT2   5
#define ANGLEPLOT2      6
#define ANGVELPLOT2      7

/**
*    @author John Allard
*    This file holds the declaration of the Double Pendulum Plot Settings Class (DPPlotSettings)
*    This is a  base class of the hierachy of classes that represents all of
*   the different plots that the double pendulum simulation can create. This class holds all of the
*    data and functionality that is common to all of the plots, like if it has a grid, what the title is, what system it's
*    representing, and what type of plot it idenitifies itself as. This class is not thorough enough the fully represent any
*    single plot, so that is why it is an abstract class
*/


class DPPlotSettings
{
private:
    int system;                    // the system (1 or 2) that this class represents
    int plottype;                // this variable will hold a defined value that corresponds to this plots type
    bool gridstate;                // true is there is a grid and visa versa
    std::string title;          // title of the plot

protected:
    std::vector<HWND> edittext;
    std::vector<HWND> spincontrols;
    std::vector<HWND> dropdownboxes;

    

public:
    //@params double pendulum system for this class, which plot this class is for (position, energy, etc.), include a grid, and the title string
    DPPlotSettings(int, int, bool = true, std::string = "");

    // holds all of the colors these types of plots can use
    Colors PROGRAMCOLORS; 

    virtual void setButtonsPictures(HWND&);               // set the buttons for window
    virtual std::vector<HWND> setEditText(HWND&,const HINSTANCE & = NULL);      // set the edit text boxes for the window
    virtual std::vector<HWND> setDropDown(HWND&);      // set the drop down buttons
    virtual std::vector<HWND> setSpinControl(HWND&);   // set the spin control
    virtual void processMessage(HWND & hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    void changeText(int key, wchar_t arr[]);            // change the #key edit box text to arr[]
    void etIncrement(bool updown, int key);                // increment/decrement the edit box text at index 'key' based on bool updown
    double etGetValue(int key);                            // get the value from the 'key' edit box

    void setPlotType(int);                                // set the type of plot that this class corresponds to, see the #defines at the top of this class
    int getPlotType() const;                            // returns an int that corresponds to the type of plot that this class represents 
    
    void setGridState(bool);                            // get if the user wants a grid on the plot
    bool getGridState() const;                            // set if the user wants a grid on the plot

    void setSystem(int);                                // set which double pendulum system this plot settings class is for
    int getSystem() const;                                // get which double pendulum system this plot settings class is for

    std::string getTitle() const;                        // get the string that represents the title of the plot
    void setTitle(std::string);                            // set the title for the plot, we currently won't let this be called by the user, we will just set a default title


};



#endif