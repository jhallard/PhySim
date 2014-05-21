#ifndef PENDULUM_H
#define PENDULUM_H

#include "ProgramDefines.h"

/**
*    @author John Allard
*    This class completely describes a single pendulum object, such as its length, intial angle, etc. 
*    There will be two of these inside each DoublePendulumSystem class, which there will then be two of
*    inside our SIMDoublePendulum class, representing our two double pendulum systems.
*
*/
class Pendulum
{
    //TODO: add operator<< to cout the pendulum information

private:

    double length;
    double mass;
    double angle;
    double angvel;

public:
    Pendulum(double = 0.5, double = 1, double = 45.0, double = 0.0);

    // these return a reference to the class to enable cascading
    Pendulum & setLength(double);
    Pendulum & setMass(double);
    Pendulum & setAngle(double);
    Pendulum & setAngVel(double);

    double getLength() const;
    double getMass() const;
    double getAngle() const;
    double getAngVel() const;

    // defines the max and min characteristics of the pendulum
    const double DPMAXLENGTH;
    const double DPMINLENGTH;
    const double DPMAXMASS;
    const double DPMINMASS;
    const double DPMAXANGVEL;
    const double DPMINANGVEL;


};



#endif