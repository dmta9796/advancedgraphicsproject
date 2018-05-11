
//
//  Particle class
//
#include "Particle.h"
#include "CUgl.h"
#include <math.h>

//
//  Constructor
//
Particle::Particle(const QString tex)
{
   sx = sy = sz = 1;
   //texture for cube
   if (tex.length()>0) setTexture(tex);
   //  Array Pointers
   N=50;
   float* vert  = new float[3*N*N];
   float* color = new float[3*N*N];
   float* vel   = new float[3*N*N];
   float* start = new float[N*N];
   //  Loop over NxN patch
   n=N;
   for (int i=0;i<n;i++)
      for (int j=0;j<n;j++)
      {
         //  Location x,y,z
         *vert++ = 0;//((i+0.5)/n-0.75);
         *vert++ = 0;
         *vert++ = 0;//((j+0.5)/n-0.75);
         //  Color r,g,b (0.5-1.0)
         *color++ = 0;//frand(0.5,0.5);
         *color++ = 0;//frand(0.5,0.5);
         *color++ = 0;//frand(0.5,0.5);
         //  Velocity
         *vel++ = 0;//frand( 1.0,3.0);
         *vel++ = 0;//frand(10.0,0.0);
         *vel++ = 0;//frand( 1.0,3.0);
         //  Launch time
         *start++ = frand(2.0,0.0);
      }
}

//
//  Set scaling
//
void Particle::setScale(float dx,float dy,float dz)
{
   sx = dx;
   sy = dy;
   sz = dz;
}

//
//  Display the cube
//
void Particle::display()
{
  // QOpenGLFunctions glf(QOpenGLContext::currentContext());
   //  Set particle size
   glPointSize(15);
   //  Point vertex location to local array Vert
   glVertexPointer(3,GL_FLOAT,0,vert);
   //  Point color array to local array Color
   glColorPointer(3,GL_FLOAT,0,color);
   //  Point attribute arrays to local arrays
  // glf.glVertexAttribPointer(VELOCITY_ARRAY,3,GL_FLOAT,GL_FALSE,0,vel);
  // glf.glVertexAttribPointer(START_ARRAY,1,GL_FLOAT,GL_FALSE,0,start);
   //  Enable arrays used by DrawArrays
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
  // glf.glEnableVertexAttribArray(VELOCITY_ARRAY);
  // glf.glEnableVertexAttribArray(START_ARRAY);
   //  Set transparent large particles
   glEnable(GL_POINT_SPRITE);
   glTexEnvi(GL_POINT_SPRITE,GL_COORD_REPLACE,GL_TRUE);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE);
   glDepthMask(0);
   //  Draw arrays
   glDrawArrays(GL_POINTS,0,n*n);
   //  Reset
   glDisable(GL_POINT_SPRITE);
   glDisable(GL_BLEND);
   glDepthMask(1);
   //  Disable arrays
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
  // glf.glDisableVertexAttribArray(VELOCITY_ARRAY);
  // glf.glDisableVertexAttribArray(START_ARRAY);
}

float Particle::frand(float rng,float off)
{
   return rand()*rng/RAND_MAX+off;
}

