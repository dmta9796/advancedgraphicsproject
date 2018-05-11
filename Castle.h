//
//  Castle class

//
#ifndef CASTLE_H
#define CASTLE_H

#include "Object.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Cone.h"

class Castle: public Object
{
private:
   float sx,sy,sz;  //  Dimensions in X/Y/Z directions
   float tx,ty,tz;  //  Positions  in X/Y/Z directions
   int th;          //  Trebuchet Angle
   QString texture; // Object Texture

public:
   Castle(const QString tex="");            //  Constructor
   void setRotationAngle(int nth);             //  Set angle
   void setFireAngle(int nph);                 //  Set angle
   void display();                             //  Render the cube
};

#endif
