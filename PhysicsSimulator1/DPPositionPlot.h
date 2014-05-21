#ifndef DPPOSITIONPLOT_H    
#define DPPOSITIONPLOT_H

#include "ProgramDefines.h"
#include "DPPlotSettings.h"

/**
*    @author John Allard
*    This class extends the DPPlotSettings class, and it implements all of the data and functionality neccesary to
*    fully describe the position plot of a double pendulum system. This class will implement a method for the user to decide
*    if they want a line to trail the lower pendulum, the color and thickness of that line, what color the two objects will be, 
*    and that is it for right now. We will most likely add more functionaliy later
*/

class DPPositionPlot : public DPPlotSettings
{

private:

    bool hasline;              // if the plot has a trailing line that shows the trajectory of the lower pendulum
    double linethickness;      // thickness of the above line, only applies if @param hasline is true
    std::vector<int*> colors; // 1 is line color, 2 is umass color, 3 is lmass color


public:

    DPPositionPlot(int type = 1, int system = 1, bool hasgrid = true, std::string = "", bool hasline = true);
    void setHasLine(bool);
    bool getHasLine() const;

    void setLineThickness(double);
    double getLineThickness() const;

    void setColor(int, int[3]);
    int* getColor(int);


    virtual void setButtonsPictures(HWND&);             // set the buttons for window
    virtual std::vector<HWND> setEditText(HWND&, const HINSTANCE &);     // this function will get implemented by the child classes based on what UI that specific class needs
    virtual std::vector<HWND> setDropDown(HWND&);     // set the drop down buttons
    virtual std::vector<HWND> setSpinControl(HWND&); // set the spin control
    virtual void processMessage(HWND & hwnd, UINT msg, WPARAM wParam, LPARAM lParam); // process UI messages 


};



#endif