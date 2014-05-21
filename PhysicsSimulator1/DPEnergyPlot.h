#ifndef DPENERGYPLOT_H    
#define DPENERGYPLOT_H

#include "ProgramDefines.h"
#include "DPPlotSettings.h"

/**
*    @author John Allard
*    This class fully describes the energy related plot that can be created by the double pendulum simulator.
*    This class can represent the plot of one entire double pendulum system, and it completely user customizable.
*    This class will store information about what types of energy the user wants plotted and the colors of those bars.
*
*/

class DPEnergyPlot : public DPPlotSettings
{

private:
    std::vector<int*> colors; // holds 3 colors
    Colors PROGRAMCOLORS;

    bool kinetic;
    bool potential;
    bool total;



public:

    virtual void setButtonsPictures(HWND&);             // set the buttons for window
    virtual std::vector<HWND> setEditText(HWND&,const HINSTANCE &); // this function will get implemented by the child classes based on what UI that specific class needs
    virtual std::vector<HWND> setDropDown(HWND&);    // set the drop down buttons
    virtual std::vector<HWND> setSpinControl(HWND&);// set the spin control
    virtual void processMessage(HWND & hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


    DPEnergyPlot(int type = 2, int system = 1, bool hasgrid = true, std::string = "",bool kin = true, bool pot = true, bool total = true);

    void setKinetic(bool);
    bool getKinetic() const;

    void setPotential(bool);
    bool getPotential() const;

    void setTotal(bool);
    bool getTotal() const;

    void setColor(int, int[3]);
    int* getColor(int);




};




#endif