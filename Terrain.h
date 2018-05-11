//
//  Terrain class
//  The constructor sets the position, size and rotation
//  All parameters are assigned default values
//
#ifndef TERRAIN_H
#define TERRAIN_H

#include "Object.h"
#include "Noise.h"

class Terrain: public Object
{
private:
   float sx,sy,sz;  //  Scale      in X/Y/Z directions
   float x0,y0,z0;  //  Positions  in X/Y/Z directions
   float th,rx,ry,rz;     //  Rotations  in X/Y/Z directions
public:
   Terrain(const QString tex="");                  //  Constructor
   void setRotationAngle(int nth);             //  Set angle
   void setFireAngle(int nph);                 //  Set angle
   void display();                                 //  Render the cube
};

#endif


