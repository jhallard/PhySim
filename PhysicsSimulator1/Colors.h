#ifndef COLORS_h
#define COLORS_H

#define  BLACK 0
#define  WHITE 1
#define     RED 2
#define     DEEPRED 3
#define     ORANGE 4
#define     DEEPORANGE 5
#define     GREEN 6
#define     DEEPGREEN 7
#define     BLUE 8
#define     DEEPBLUE 9
#define  PURPLE 10
#define     GRAY 11
#define     DEEPGRAY 12

#include <vector>
/**
*    @author John Allard
*    This class holds all of the colors that our program needs to operate. 
*    I probably should have found a library instead of defining these myself, not like anyone is going to read this though
*/ 

 class Colors
{
public:
      int black[3];
      int white[3];

     int deeporange[3];
     int orange[3];

     int deepblue[3];
     int blue[3];

     int deepred[3];
     int red[3];

     int deepgreen[3];
     int green[3];

     int deepyellow[3];
     int yellow[3];

     int deepgray[3];
     int gray[3];

     int purple[3];

    Colors();

     void doubleToInt(double*, int*);
     void intToDouble(int*, double*);

     static std::vector<int*> colorlist;



};




#endif