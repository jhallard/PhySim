/**
*    @author John Allard
*    This is the implementation of the class SimDoublePendulum. This class handles the storing, validation, and handling
*    of all the data needed to create one of the many possible double pendulum simulations.
*    It contains the data about the intitial conditions of the two double pendulums, as well as the other physical characteristics
*    of the system, such as the length and speed of the simulation. It also holds two DPPlotSettings classes, which hold the specs
*    (colors, linewidth, position, etc) about the plots that are going to be animated
*
*/ 

#include "SIMDoublePendulum.h"


// static variable definitions
DPPlotSettings * SIMDoublePendulum::plotlist[8] = {NULL};
int SIMDoublePendulum::plot1 = POSITIONPLOT1;
int SIMDoublePendulum::plot2 = ENERGYPLOT2;
int SIMDoublePendulum::currentplot = 1;


    SIMDoublePendulum::SIMDoublePendulum(DoublePendulumSystem pend1,DoublePendulumSystem pend2, double time, double simspeed)
    {
        // initialize the plotlist array to all 8 plots that can be made.
        // the first half belong to plot1, the last half belong to plot2
        plotlist[0] = new DPPositionPlot(POSITIONPLOT1);
        plotlist[1] = new DPEnergyPlot(ENERGYPLOT1);
        plotlist[2] = new DPAnglePlot(ANGLEPLOT1);
        plotlist[3] = new DPAngVelPlot(ANGVELPLOT1);
        plotlist[4] = new DPPositionPlot(POSITIONPLOT2);
        plotlist[5] = new DPEnergyPlot(ENERGYPLOT2);
        plotlist[6] = new DPAnglePlot(ANGLEPLOT2);
        plotlist[7] = new DPAngVelPlot(ANGVELPLOT2);

        this->setSystem1(pend1);
        this->setSystem2(pend2);

        // set the default plot choices for the user 
        this->setPlot1(POSITIONPLOT1);
        this->setPlot2(ENERGYPLOT2);
        
        this->setSimulationTime(time);
        this->setSimulationSpeed(simspeed);

    }

    SIMDoublePendulum::~SIMDoublePendulum()
    {
        // delete every dynamically allocated plot from the plotlist array. We do it this way 
        // because an array is not dynamically allocated at once, all of it's parts are dynamically
        // allocated derived classes of the plotlist base class pointer
        for(int i = 0; i < 8; i++)
            delete this->plotlist[i];
    }
    // set and get functions for the two pendulum objects
    void SIMDoublePendulum::setSystem1(DoublePendulumSystem pend)
    {
        this->system1.setGravity(pend.getGravity());
        this->system1.setLower(pend.getLower());
        this->system1.setUpper(pend.getUpper());
    }
    void SIMDoublePendulum::setSystem2(DoublePendulumSystem pend)
    {
        this->system2.setGravity(pend.getGravity());
        this->system2.setLower(pend.getLower());
        this->system2.setUpper(pend.getUpper());
    }
    DoublePendulumSystem SIMDoublePendulum::getSystem1() const
    {
        return this->system1;
    }
    DoublePendulumSystem SIMDoublePendulum::getSystem2() const
    {
        return this->system2;
    }

    // set, remove, and get function for the vector of plots the user wants to create
    DPPlotSettings *  SIMDoublePendulum::getPlot1() const
    {
        return this->plotlist[plot1];
    }
    DPPlotSettings * SIMDoublePendulum::getPlot2() const
    {
        return this->plotlist[plot2];
    }
    void SIMDoublePendulum::setPlot1(int plotnumber)
    {
        this->plot1 = plotnumber;
    }
    void SIMDoublePendulum::setPlot2(int plotnumber)
    {
        this->plot2 = plotnumber;
    }

    // this sets which plot the user is currently editing, so we know which
    // dialog window to bring up
    void SIMDoublePendulum::setCurrentPlot(int value)
    {
        if(value == 1 || value == 2)
            this->currentplot = value;
    }
    int SIMDoublePendulum::getCurrentPlot() const
    {
        return this->currentplot;
    }
    

    // these deal with the length of the simulation
    void SIMDoublePendulum::setSimulationTime(double time)
    {
        if(time > 0 && time < 1000)
            this->simulationtime = time;
        else
            time = 20;
    }
    double SIMDoublePendulum::getSimulationTime() const
    {
        return this->simulationtime;
    }

    // these deal with the speed of the simulation
    void SIMDoublePendulum::setSimulationSpeed(double speed)
    {
        if(speed > 10 && speed < 300)
            this->simulationspeed = speed;
        else
            this->simulationspeed = 100;
    }
    double SIMDoublePendulum::getSimulationSpeed() const
    {
        return this->simulationspeed;
    }