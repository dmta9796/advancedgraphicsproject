//
//  Water class
//  The constructor sets the position, size and rotation
//  All parameters are assigned default values
//
#ifndef WATER_H
#define WATER_H

#include "Object.h"
#include "Noise.h"
#include <QMatrix4x4>

class Water: public Object
{
private:
   float sx,sy,sz;  //  Dimensions in X/Y/Z directions
   float tx,ty,tz;  //  Positions  in X/Y/Z directions
public:
   Water(const QString tex="");                  //  Constructor
   void setRotationAngle(int nth);             //  Set angle
   void setFireAngle(int nph);                 //  Set angle
   void display();                                 //  Render the cube
};

#endif



