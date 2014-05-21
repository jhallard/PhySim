#ifndef ANGLEPLOT_H
#define ANGLEPLOT_H

#include "DPPlotSettings.h"
#include "ProgramDefines.h"

#define UPPERANGLEPLOT 0
#define LOWERANGLEPLOT 1
#define PARAMETRICPLOT 2

#define DEGREES        0
#define RADIANS        1
#define REVOLUTIONS 2


/**
*    @author John Allard
*    This class completely describes the Angle Plot that the double pendulum simulator can create.
*    This is one of the more complicated plot settings classes, as this one has many options the user can choose.
*    First, they can choose if they want to plot the upper angle, lower angle, or a parametric plot of the angles.
*    Then they can choose is if they want the units to be in degrees, radians, or revolutions.
*    Then they can choose what they want they want to use true angles or normalized with respect to 360 degrees
*
*    They can also choose the line color and thickness of the line. 
*
*
*/

class DPAnglePlot : public DPPlotSettings
{
private:
    double linethickness;
    std::vector<int*> colors; // only holds 1, line color
    int angleplottype; // 1 = upper angle vs time, 2 = lower angle vs time, 3 = parametric
    int units; 
    bool normalized; // true if the user wants the angles normalized with respect to {0, 2pi}


public:
    Colors PROGRAMCOLORS;
    DPAnglePlot(int type = 3, int system = 1, bool hasgrid = true, std::string = "",
            int plottype = PARAMETRICPLOT, double units = RADIANS, bool normalized = false, double linethickness = 1);

    void setLineThickness(double);
    void setAnglePlotType(int);
    void setUnits(int);
    void setNormalized(bool);

    double getLineThickness() const;
    int getAnglePlotType() const;
    int getUnits() const;
    bool getNormalized() const;

    void setColor(int, int[3]);
    int* getColor(int) const;

    virtual void setButtonsPictures(HWND&);                       // set the buttons for window
    virtual std::vector<HWND> setEditText(HWND&,const HINSTANCE &); // this function will get implemented by the child classes based on what UI that specific class needs
    virtual std::vector<HWND> setDropDown(HWND&); // set the drop down buttons
    virtual std::vector<HWND> setSpinControl(HWND&);// set the spin control
    virtual void processMessage(HWND & hwnd, UINT msg, WPARAM wParam, LPARAM lParam);



};



#endif