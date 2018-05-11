//
//  Cube class
//
#include "Cylinder.h"
#include <math.h>

//
//  Constructor
//
Cylinder::Cylinder(const QString tex)
{
   sx = sy = sz = 1;
   if (tex.length()>0) setTexture(tex);
}

//
//  Set scaling
//
void Cylinder::setScale(float dx,float dy,float dz)
{
   sx = dx;
   sy = dy;
   sz = dz;
}

//
//  Display the cube
//
void Cylinder::display()
{
   if (!show) return;
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
    int i,k;
   EnableTex();
   glEnable(GL_CULL_FACE);
   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   useTransform();
   //  Head & Tail
   glColor3f(1,1,1);
   for (i=1;i>=-1;i-=2)
   {
      glNormal3f(0,0,i);
      glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0.5,0.5);
      glVertex3f(0,0,i);
      for (k=0;k<=360;k+=10)
      {
         glTexCoord2f(0.5*Cos(k)+0.5,0.5*Sin(k)+0.5);
         glVertex3f(i*Cos(k),Sin(k),i);
      }
      glEnd();
   }
   //  Edge
   glColor3f(1.00,0.77,0.36);
   glBegin(GL_QUAD_STRIP);
   for (k=0;k<=360;k+=10)
   {
      glNormal3f(Cos(k),Sin(k),0);
      glTexCoord2f(0.01*k,0); glVertex3f(Cos(k),Sin(k),+1);
      glTexCoord2f(0.01*k,1); glVertex3f(Cos(k),Sin(k),-1);
   }
   glEnd();
   //  Undo transformations
   glPopMatrix();
   DisableTex();
   glDisable(GL_CULL_FACE);
   //  Undo transofrmations
   glPopMatrix();
}
void Cylinder::setRotationAngle(int nth){nth+=1;}
void Cylinder::setFireAngle(int nph){nph+=1;}
Cylinder::~Cylinder(){}
