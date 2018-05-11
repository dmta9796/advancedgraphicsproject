//
//  Object class
//  Dummy generic object class
//  Location of object is common to all objects
//  Translation is defined for all objects, but must
//  be implemented in the display function of each object
//  The display function is virtual and must be reimplemented
//
#ifndef OBJECT_H
#define OBJECT_H

#include <QtOpenGL>
#include "Type.h"

class Object
{
protected:
   bool  show;          //  Display
   float x0,y0,z0;      //  Location
   float th,rx,ry,rz;   //  Rotation (angle and axis)
   float sx,sy,sz;      //  Scale
   float r0,g0,b0;      //  Color
   QOpenGLTexture* tex; //  Texture
   Object();            //  Constructor
public:
   void setShow(bool on);                               //  Set show
   void setTranslate(float x,float y,float z);          //  Set translation
   void setTexture(QString file);                       //  Set default texture
   void setRotate(float th,float dx,float dy,float dz); //  Set rotation
   void setScale(float dx,float dy,float dz);           //  Set scale
   void setColor(Color rgb);                            //  Set color
   void setColor(float r,float g,float b);              //  Set color
   QMatrix4x4 getModel();                               //  Fetch model matrix
   virtual void display()=0;                            //  Render the object
   virtual void setFireAngle(int nth)=0;
   virtual void setRotationAngle(int nph)=0;
   virtual ~Object() {};                                //  Do nothing destructor
protected:
   void useColor();
   void useColor(Color c);
   void useColor(Color a,Color d,Color s,Color e,float Ns);
   void useTransform();
   void EnableTex();
   void DisableTex();
   int  Increment(int n);
};

#endif
