//
//  Sphere class
//  The constructor sets the position, radius and color
//  All parameters are assigned default values
//
#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"

class Sphere: public Object
{
private:
   int   inc;  //  Increment
   float sr;   //  Radius
public:
   Sphere(int patches,const QString tex="",const float size=1.0,const Color col=Color(1,1,1));       //  Constuctor
   void setRotationAngle(int nth);             //  Set angle
   void setFireAngle(int nph);                 //  Set angle
   void setScale(float r);
   void display();         //  Render the sphere
};

#endif
