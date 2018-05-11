
//
//  Particle class
//  The constructor sets the position, size and rotation
//  All parameters are assigned default values
//
#ifndef PARTICLE_H
#define PARTICLE_H

#include "Object.h"
#include "CUgl.h"

class Particle: public Object
{
private:
   float sx,sy,sz;                //  Dimensions in X/Y/Z directions
   float tx,ty,tz;                //  Positions  in X/Y/Z directions
   QOpenGLTexture* texture;
   const int VELOCITY_ARRAY=4;
   const int START_ARRAY=5;
   int N;                         //  Particle count
   int n;                         //  Particle count
   float* vert;
   float* color;
   float* vel;
   float* start;
public:
   Particle(const QString tex="");                 //  Constructor
   void setScale(float dx,float dy,float dz);      //  Set scale
   void setTranslate(float nx,float ny,float nz);  //  Set scale
   void display();                                 //  Render the cube
   float frand(float rng,float off);        // Random number generator
};

#endif
