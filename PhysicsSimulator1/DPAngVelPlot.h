#ifndef DPANGVELPLOT_H
#define DPANGVELPLOT_H


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
*    This class completely describes all of the data and functionality of the angular velocity plot
*    that can be simulated by the double pendulum simulator. This class very much follows the same path as the angle
*    plot class (DPAnglePlot.h), so for more information look there.
*
*/

class DPAngVelPlot : public DPPlotSettings
{

    private:

    double linethickness;
    std::vector<int*> colors; // only holds 1, line color
    int angvelplottype;       // 1 = upper angle vs time, 2 = lower angle vs time, 3 = parametric
    int units;                  // 1 is degrees, 2 is radians, 3 is revolutions



public:

    Colors PROGRAMCOLORS;
    DPAngVelPlot(int type = 4, int system = 1, bool hasgrid = true, std::string = "", int plottype = PARAMETRICPLOT, int units = RADIANS, double linethickness = 1);

    void setLineThickness(double);
    void setAngVelPlotType(int);
    void setUnits(int);

    double getLineThickness() const;
    int getAngVelPlotType() const;
    int getUnits() const;

    void setColor(int, int[3]);
    int* getColor(int) const;

    virtual void setButtonsPictures(HWND&);                       // set the buttons for window
    virtual std::vector<HWND> setEditText(HWND&,const HINSTANCE &); // this function will get implemented by the child classes based on what UI that specific class needs
    virtual std::vector<HWND> setDropDown(HWND&); // set the drop down buttons
    virtual std::vector<HWND> setSpinControl(HWND&);// set the spin control
    virtual void processMessage(HWND & hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

};



#endif