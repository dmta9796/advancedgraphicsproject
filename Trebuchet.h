//
//  Trebuchet class

//
#ifndef TREBUCHET_H
#define TREBUCHET_H

#include "ex19viewer.h"
#include "Object.h"
#include "Cube.h"
#include "Cylinder.h"

class Trebuchet: public Object
{
private:
   int th,ph;       //  Trebuchet Angle
   QString texture; // Object Texture

public:
   Trebuchet(const QString tex="");            //  Constructor
   void setScale(float dx,float dy,float dz);  //  Set scale
   void display();                             //  Render the cube
   void arm();                                 //  Render arm
   void setRotationAngle(int nth);             //  Set angle
   void setFireAngle(int nph);                 //  Set angle
   QVector3D setCenteredRotation(float x, float y, float z); // translate around a center
};

#endif
