#ifndef SIMDOUBLEPENDULUM_H
#define SIMDOUBLEPENDULUM_H

#include <vector>
#include <Windows.h>

#include "ProgramDefines.h"
#include "Pendulum.h"
#include "DoublePendulumSystem.h"
#include "DPPlotSettings.h"
#include "DPPositionPlot.h"
#include "DPEnergyPlot.h"
#include "DPAnglePlot.h"
#include "DPAngVelPlot.h"





/**
*    @author John Allard
*    This is the main simulation class for the double pendulum simulator. This simulator is divided into two main parts,
*    the UI, which is handled in the UIDoublePendulum class, and all the data the that is needed to accurately represent the two
*    double pendulum systems (like the masses, the lengths, the simulation speed, the simulation time, info about the two systems
*    the colors used in the plots, what plots the user wants to make, etc.) are contained inside this class. This is an attempt to
*    follow the separation between the model and the view. One important note, all of the information about the dialog windows to
*    edit the plots are contained inside this class. This includes the 4+ classes derived from the DPPlotSettings class. 
*/


class SIMDoublePendulum
{

private:

    double simulationtime;  // time length of the simulation from t = 0 to end
    double simulationspeed; // 0.0 - 3.0 represents the percentage of normal speed (0.5 = 50% of normal)
    
    // objects that represent the two double pendulum systems that the user can simulate
    // these classes contain two Pendulum classes each, representing the upper and lower pendulums of each system respectively
    DoublePendulumSystem system1;
    DoublePendulumSystem system2;

    // these two hold ints that represent which plot is the first and which plot is second
    // the value will correspond to one of the #define'd ints inside DPPlotSettings.h, and
    // they represent which of the available plots the user wants to make as their first and second plots respectively
    static int plot1;
    static int plot2;

    // array of plots that the user can make, they will select two of the 8 to plot at any one time.
    // this array is type DPPlotSettings but will be filled with the addresses of objects that are
    // of the classes derived from DPPlotSettings
    static DPPlotSettings * plotlist[8];

    // this is needed so the plot settings dialog window that opens knows which plot it is currently editing
    static int currentplot;

    
public:
      
    // constructor                                                        // ===== @Params =======
    SIMDoublePendulum(DoublePendulumSystem = DoublePendulumSystem(),    // 1st double pendulum system
                      DoublePendulumSystem = DoublePendulumSystem(),    // 2nd double pendulum system
                      double = 15.0,                                    // simulation length in seconds
                      double = 1.0);                                    // simulation speed, % in decimal form
                                                                   

    ~SIMDoublePendulum(); // deletes dynamic memory allocated in constructor and assigned to plotlist[8]

    // set and get functions for the two DoublePendulumSystem objects
    void setSystem1(DoublePendulumSystem);
    void setSystem2(DoublePendulumSystem);
    DoublePendulumSystem getSystem1() const;
    DoublePendulumSystem getSystem2() const;

    // set, remove, and get function for the vector of plots the user wants to create
    // returns a pointer to the plots the user is working with, allows the dialog window to directly
    // edit the relevant plots.
    DPPlotSettings * getPlot1() const;
    DPPlotSettings * getPlot2() const;

    // instead of passing in a plot object to be copied we will let the user choose which of the 8 plots they
    // want set, this allows us to keep the data about all 8 possible plots and let the user select previously 
    // saved plot data if they so wish. The first half of the plotlist array are objects that the first plot can
    // use, the last half  of the plotlist array are objects the second plot can use. This allows the user to make
    // the same simulation on both sides, and to prevent a plot 1 to edit a class that plot 2 is using.
    void setPlot1(int);
    void setPlot2(int);

    // these only deal with plot 1 or plot 2, and they only serve for the configure window to know which plot the
    // user is working with
    void setCurrentPlot(int);
    int getCurrentPlot() const;
    

    // these deal with the length of the simulation
    void setSimulationTime(double);
    double getSimulationTime() const;

    // set and get the simulation speed (a percent in decimal value ranging from .1 - 3.0, a.k.a 10%-300%)
    double getSimulationSpeed() const;
    void setSimulationSpeed(double);


    // CREATE SIMULATION FUNCTION
    void createSimulation(); 


};

#endif