//
//  cylinder class

//
#ifndef CYLINDER_H
#define CYLINDER_H

#include "Object.h"
#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))

class Cylinder: public Object
{
private:
   float sx,sy,sz;  //  Dimensions in X/Y/Z directions
public:
   Cylinder(const QString tex="");                 //  Constructor
   void setScale(float dx,float dy,float dz);  //  Set scale
   void setRotationAngle(int nth);             //  Set angle
   void setFireAngle(int nph);                 //  Set angle
   void display();                             //  Render the cube
   ~Cylinder();
};

#endif
