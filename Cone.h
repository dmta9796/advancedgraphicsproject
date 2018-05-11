
//
//  Cone class

//
#ifndef CONE_H
#define CONE_H

#include "Object.h"
#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))

class Cone: public Object
{
private:
   float sx,sy,sz;  //  Dimensions in X/Y/Z directions
   float tx,ty,tz;  //  Positions  in X/Y/Z directions
   int th;          //  Trebuchet Angle
   QString texture; // Object Texture

public:
   Cone(const QString tex="");            //  Constructor
   void setRotationAngle(int nth);             //  Set angle
   void setFireAngle(int nph);                 //  Set angle
   void display();                             //  Render the cube
};

#endif
