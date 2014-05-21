#ifndef DOUBLEPENDULUMSYSTEM_H
#define DOUBLEPENDULUMSYSTEM_H

/*
*    @author John Allard
*    This class represents a double pendulum system. There will be two instances of this class inside of the SIMDoublePendulum
*    class, representing the two double pendulum systems that the user can create and simulate. This class will consist of all of the
*    physical parameters necessary to fully describe one of the double pendulum systems
*/

#include "Pendulum.h"
#include "ProgramDefines.h"

class DoublePendulumSystem
{
private:
    // objects that represent the upper and lower pendulums of the system
    Pendulum upperpendulum;
    Pendulum lowerpendulum;

    double gravity;    // gravitational constant (m/s^2)
    bool friction;  // currently unimplemented, would be to include friction in the hinges of the pendulums


public:
    DoublePendulumSystem(Pendulum = Pendulum(), Pendulum = Pendulum(), double = 9.81);

    void setUpper(Pendulum);
    void setLower(Pendulum);
    Pendulum getUpper();
    Pendulum getLower();

    // these set/get the value of the gravitational contant (default = 9.81)
    void setGravity(double);
    double getGravity() const;

};


#endif