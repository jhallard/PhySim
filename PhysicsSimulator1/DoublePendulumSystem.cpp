#include "DoublePendulumSystem.h"
#include "ProgramDefines.h"

/*
*    @author John Allard
*    This is the implementation of the double pendulum system class. This class holds all of the data
*    needed to physically describe the initial conditions of the double pendulum system.
*/

DoublePendulumSystem::DoublePendulumSystem(Pendulum upper, Pendulum lower, double gravity)
{
    this->setUpper(upper);
    this->setLower(lower);
    this->setGravity(gravity);
}
void DoublePendulumSystem::setUpper(Pendulum pend)
{
    this->upperpendulum.setAngle(pend.getAngle());
    this->upperpendulum.setAngVel(pend.getAngVel());
    this->upperpendulum.setLength(pend.getLength());
    this->upperpendulum.setMass(pend.getMass());
}
void DoublePendulumSystem::setLower(Pendulum pend)
{
    this->lowerpendulum.setAngle(pend.getAngle());
    this->lowerpendulum.setAngVel(pend.getAngVel());
    this->lowerpendulum.setLength(pend.getLength());
    this->lowerpendulum.setMass(pend.getMass());
}
Pendulum DoublePendulumSystem::getUpper()
{
    return this->upperpendulum;
}
Pendulum DoublePendulumSystem::getLower()
{
    return this->lowerpendulum;
}

// these set/get value of the gravitational contant (default = 9.81)
void DoublePendulumSystem::setGravity(double gravity)
{
    this->gravity = gravity;
}
double DoublePendulumSystem::getGravity() const
{
    return this->gravity;
}