#include "Colors.h"

/**
*    @author John Allard
*    This is the implementation of the colors class, which defines the colors used in this program.
*    The class is a static class, and it represents all color combinations as 3 index int arrays (RGB standard). It
*     also includes public utility functions that turn a int RGB array into a double RGb array normalized with respect to 255.
*/

std::vector<int*> Colors::colorlist;

Colors::Colors() 
{

    black[0] = 255;
    black[1] = 255;
    black[2] = 255;

    white[0] = 0;
    white[1] = 0;
    white[2] = 0;

    deeporange[0] = 251;
    deeporange[1] = 97;
    deeporange[2] = 4;

    deepblue[0] = 1;
    deepblue[1] = 25;
    deepblue[2] = 51;

    deepgray[0] = 51;
    deepgray[1] = 51;
    deepgray[2] = 51;

     gray[0] = 190;
     gray[1] = 190;
     gray[2] = 190;

     green[0] = 23;
     green[1] = 125; 
     green[2] = 54;

     deepgreen[0] = 2;
     deepgreen[1] = 64;
     deepgreen[2] = 1;

     purple[0] = 150;
     purple[1] = 67;
     purple[2] = 50;

     red[0] = 196;
     red[1] = 0;
     red[2] = 0;

     blue[0] = 5;
     blue[1] = 10;
     blue[2] = 128;

     orange[0] = 244;
     orange[1] = 142;
     orange[2] = 4;

     deepred[0] = 128;
     deepred[1] = 0;
     deepred[2] = 0;

     colorlist.push_back(black);
     colorlist.push_back(white);
     colorlist.push_back(red);
     colorlist.push_back(deepred);
     colorlist.push_back(orange);
     colorlist.push_back(deeporange);
     colorlist.push_back(green);
     colorlist.push_back(deepgreen);
     colorlist.push_back(blue);
     colorlist.push_back(deepblue);
     colorlist.push_back(purple);
     colorlist.push_back(gray);
     colorlist.push_back(deepgray);



}

void Colors::doubleToInt(double* before, int * after)
{
    for(int i = 0; i < 3; i++)
        *(after+i) = *(before+i)*255.0;
}
void Colors::intToDouble(int* before, double* after)
{
    for(int i = 0; i < 3; i++)
        *(after+i) = *(before+i)/255.0;
}