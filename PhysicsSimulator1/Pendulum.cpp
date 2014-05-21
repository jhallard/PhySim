/**
*    @author John Allard
*    This is where we implement the Pendulum Class.
*    This class only serves to hold the characteristics of a single pendulum.
*    The SimDoublePendulum class will hold two of these classes to collectively represent the double pendulum
*/

#include "Pendulum.h"
#include "ProgramDefines.h"



Pendulum::Pendulum(double length, double mass, double angle, double angvel) 
: DPMAXLENGTH(5.0), DPMINLENGTH(0.05), DPMAXMASS(40.0), DPMINMASS(0.0), DPMAXANGVEL(20.0), DPMINANGVEL(-20.0) // initialize class constants
{
    this->setLength(length).setMass(mass).setAngle(angle).setAngVel(angvel);
}

// these return a reference to the class to enable cascading
Pendulum & Pendulum::setLength(double length)
{
    if(length > Pendulum::DPMINLENGTH && length <Pendulum::DPMAXLENGTH)
    {
        this->length = length;
    }
    return *this;
}
Pendulum & Pendulum::setMass(double mass)
{
    if(mass > Pendulum::DPMINMASS && length < Pendulum::DPMAXMASS)
    {
        this->mass = mass;
    }
    return *this;
}
Pendulum & Pendulum::setAngle(double angle)
{    
        this->angle = angle;
    return *this;
}
Pendulum & Pendulum::setAngVel(double angvel)
{
    this->angvel = angvel;
    return *this;
}

double Pendulum::getLength() const
{
    return this->length;
}
double Pendulum::getMass() const
{
    return this->mass;
}
double Pendulum::getAngle() const
{
    return this->angle;
}
double Pendulum::getAngVel() const
{
    return this->angvel;
}
