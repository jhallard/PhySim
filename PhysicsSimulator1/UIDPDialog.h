#ifndef UIDPDIALOG_H
#define UIDPDIALOG_H


#include "ProgramDefines.h"
#include <vector>

/**
*    @author This is the UI class for the Simulation Settings Dialog box.
*    Here we define all of the UI elements and store all the relevant data from them.
*    The dialog box has 4 main "Tabs". The first one let's the user choose which plots they want to include and where
*    For instance, they can choose to just do a pendulum position plot, or a pendulum position plot and a angular velocity plot, et all..
*    This means we will have vectors of UI elements for each of the tabs, we will also have set and diable functions for all the UI elements each tab
*    this way, when the user selects tab two, we disable all of the UI elements on their previous tab, and set all the UI elements for tab 2
*    this effectively lets us change through multiple windows while just using one small dialog box
*
*/
class UIDPDialog
{
private:
    int currenttab; // 0 = figure tab, 1 = plot#1 tab, 2 = plot#2 tab, 3 = plot#3 tab
    // these vectors of HWND's hold the handles to all of the UI elements windows of each type (b = button, et = edit text, sc = spincontrol)
    // They are grouped into 3's this is to allow us easy access to the UI elements that correspond to each window (FigureSettings, PosPlot, AnglePlot, AngvelPlot)
    std::vector<HWND> rbFigure;
    std::vector<HWND> bFigure;
    std::vector<HWND> picFigure;
    

public:

    UIDPDialog();

    void setCurrentTab(int);
    int getCurrentTab() const;
    
    // these are the set functions for the standard, static window UI. these buttons do not change
    void setStaticUI(HWND &) const;

    // these are the set and get gunctions for the Figure Settings UI tab
    void setFigureSettingsUI(HWND &);
    void disableFigureSettingsUI();



};



#endif