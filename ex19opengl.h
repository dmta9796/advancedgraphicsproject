//
//  OpenGL Ex19opengl Widget
//

#ifndef EX19OPENGL_H
#define EX19OPENGL_H

#include "CUgl.h"
#include <QOpenGLFramebufferObject>

class Ex19opengl : public CUgl
{
Q_OBJECT
private:
   //particle
   int     N;                //  Particle count
   float   zh;               //  Light position
   int     n;                //  Particle count
   float*  Vert;             //  Vertices
   float*  Color;            //  Colors
   float*  Vel;              //  Velocities
   float*  Start;            //  Start time
   QOpenGLTexture* tex1;     //  Texture 
   QOpenGLTexture* tex2;     //  Texture
   QOpenGLTexture* tex3;     //  Texture
   QOpenGLTexture* tex4;     //  Texture 
   QOpenGLTexture* tex5;     //  Texture wood
   QOpenGLTexture* tex6;     //  Texture wood
   QOpenGLTexture* cubemap;  //  Texture skybox
   QOpenGLTexture* shadowmap;//  Texture 
   QOpenGLFramebufferObject* depthMapFBO; //shadow map depth buffer
public:
   int fbow; //framebuffer width 
   int fboh; //framebuffer height
   Ex19opengl(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(400,400);} //  Default size of widget
public slots:
   void setMode(int m);  //  Set mode
protected:
   void initializeGL();  //  Initialize widget
   void paintGL();       //  Draw widget
private:
  void modelCoords();
  void testbuffer();
  void InitPart();
  void DrawPart();
  QImage loadShadowMap();
  //void loadShadowMap();
};

#endif
