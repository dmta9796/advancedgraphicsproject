//
//  Trees class
//  The constructor sets the position, size and rotation
//  All parameters are assigned default values
//
#ifndef TREES_H
#define TREES_H

#include "Object.h"
#include "Noise.h"

class Trees: public Object
{
private:
   float sx,sy,sz;  //  Dimensions in X/Y/Z directions
   float tx,ty,tz;  //  Positions  in X/Y/Z directions
   QOpenGLBuffer   tree_buffer;  //  Vertex buffer
   const float tree_size=36;
   QOpenGLTexture* texture;
   const float tree_data[36*12] =  // Vertex data
   {
		//  X     Y     Z  W       Nx Ny Nz    R G B   s t   Tx Ty Tz    Bx By Bz
		//  Front
		+0.25,+0.25,+0.005,+1,      0, 0,+1,    1,0,0,  1,1,   1, 0, 0,    0, 1, 0,
		-0.25,+0.25,+0.005,+1,      0, 0,+1,    1,0,0,  0,1,   1, 0, 0,    0, 1, 0,
		+0.25,-0.25,+0.005,+1,      0, 0,+1,    1,0,0,  1,0,   1, 0, 0,    0, 1, 0,
		+0.25,-0.25,+0.005,+1,      0, 0,+1,    1,0,0,  1,0,   1, 0, 0,    0, 1, 0,
		-0.25,+0.25,+0.005,+1,      0, 0,+1,    1,0,0,  0,1,   1, 0, 0,    0, 1, 0,
		-0.25,-0.25,+0.005,+1,      0, 0,+1,    1,0,0,  0,0,   1, 0, 0,    0, 1, 0,
		//  Back
	    +0.25,-0.25,-0.005,+1,      0, 0,-1,    0,0,1,  0,0,  -1, 0, 0,    0,-1, 0,
		-0.25,-0.25,-0.005,+1,      0, 0,-1,    0,0,1,  1,0,  -1, 0, 0,    0,-1, 0,	
		-0.25,+0.25,-0.005,+1,      0, 0,-1,    0,0,1,  1,1,  -1, 0, 0,    0,-1, 0,
		+0.25,-0.25,-0.005,+1,      0, 0,-1,    0,0,1,  0,0,  -1, 0, 0,    0,-1, 0,
		-0.25,+0.25,-0.005,+1,      0, 0,-1,    0,0,1,  1,1,  -1, 0, 0,    0,-1, 0,
		+0.25,+0.25,-0.005,+1,      0, 0,-1,    0,0,1,  0,1,  -1, 0, 0,    0,-1, 0,
		//  Right
	    +0.005,+0.25,+0.25,+1,     +1, 0, 0,    1,1,0,  0,1,   0, 1, 0,    0, 0, 1,
	    +0.005,-0.25,+0.25,+1,     +1, 0, 0,    1,1,0,  0,0,   0, 1, 0,    0, 0, 1,
	    +0.005,+0.25,-0.25,+1,     +1, 0, 0,    1,1,0,  1,1,   0, 1, 0,    0, 0, 1,
	    +0.005,+0.25,-0.25,+1,     +1, 0, 0,    1,1,0,  1,1,   0, 1, 0,    0, 0, 1,
	    +0.005,-0.25,+0.25,+1,     +1, 0, 0,    1,1,0,  0,0,   0, 1, 0,    0, 0, 1,
	    +0.005,-0.25,-0.25,+1,     +1, 0, 0,    1,1,0,  1,0,   0, 1, 0,    0, 0, 1,
	    //  Left
	   -0.005,+0.25,+0.25,+1,      -1, 0, 0,    0,1,0,  1,1,   0,-1, 0,    0, 0,-1,
	   -0.005,+0.25,-0.25,+1,      -1, 0, 0,    0,1,0,  0,1,   0,-1, 0,    0, 0,-1,
	   -0.005,-0.25,+0.25,+1,      -1, 0, 0,    0,1,0,  1,0,   0,-1, 0,    0, 0,-1,
	   -0.005,-0.25,+0.25,+1,      -1, 0, 0,    0,1,0,  1,0,   0,-1, 0,    0, 0,-1,
	   -0.005,+0.25,-0.25,+1,      -1, 0, 0,    0,1,0,  0,1,   0,-1, 0,    0, 0,-1,
	   -0.005,-0.25,-0.25,+1,      -1, 0, 0,    0,1,0,  0,0,   0,-1, 0,    0, 0,-1
	};
public:
   Trees(const QString tex="");                  //  Constructor
   void setRotationAngle(int nth);             //  Set angle
   void setFireAngle(int nph);                 //  Set angle
   void display();                                 //  Render the cube
};

#endif



