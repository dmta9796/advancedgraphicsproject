//
//  Cubemap class
//  The constructor sets the position, size and rotation
//  All parameters are assigned default values
//
#ifndef CUBEMAP_H
#define CUBEMAP_H

#include "Object.h"

class Cubemap: public Object
{
private:
   float sx,sy,sz;  //  Dimensions in X/Y/Z directions
   float tx,ty,tz;  //  Positions  in X/Y/Z directions
   QOpenGLBuffer   cube_buffer;  //  Vertex buffer
   static const int cube_size=36;
   QOpenGLTexture* texture;

float skyboxVertices[36*3] = {
    // positions          
     10.0f, -10.0f,  10.0f,
     10.0f,  10.0f,  10.0f,
    -10.0f,  10.0f,  10.0f,
    -10.0f,  10.0f,  10.0f,
    -10.0f, -10.0f,  10.0f,
     10.0f, -10.0f,  10.0f,

     10.0f,  10.0f, -10.0f,
     10.0f,  10.0f,  10.0f,
     10.0f, -10.0f,  10.0f,
     10.0f, -10.0f,  10.0f,
     10.0f, -10.0f, -10.0f,
     10.0f,  10.0f, -10.0f,

    -10.0f,  10.0f,  10.0f,
    -10.0f,  10.0f, -10.0f,
    -10.0f, -10.0f, -10.0f,
    -10.0f, -10.0f, -10.0f,
    -10.0f, -10.0f,  10.0f,
    -10.0f,  10.0f,  10.0f,

     10.0f,  10.0f, -10.0f,
     10.0f, -10.0f, -10.0f,
    -10.0f, -10.0f, -10.0f,
    -10.0f, -10.0f, -10.0f,
    -10.0f,  10.0f, -10.0f,
     10.0f,  10.0f, -10.0f,

     10.0f, -10.0f,  10.0f,
    -10.0f, -10.0f,  10.0f,
    -10.0f, -10.0f, -10.0f,
    -10.0f, -10.0f, -10.0f,
     10.0f, -10.0f, -10.0f,
     10.0f, -10.0f,  10.0f,

     10.0f,  10.0f,  10.0f,
     10.0f,  10.0f, -10.0f,
    -10.0f,  10.0f,  10.0f,
    -10.0f,  10.0f,  10.0f,
     10.0f,  10.0f, -10.0f,
    -10.0f,  10.0f, -10.0f
};


public:
   Cubemap(const QString tex="");                 //  Constructor
   void setRotationAngle(int nth);             //  Set angle
   void setFireAngle(int nph);                 //  Set angle
   void display();                             //  Render the cube
   ~Cubemap();
};

#endif
