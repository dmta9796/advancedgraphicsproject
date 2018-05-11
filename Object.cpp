//
//  Generic Object class
//
#include "Object.h"

#define Cos(th) cos(M_PI/180*(th))
#define Sin(th) sin(M_PI/180*(th))
//
//  Constructor
//
Object::Object()
{
   show = true;
   //  Location
   x0 = y0 = z0 = 0;
   //  Rotation
   th = ry = rz = 0;
   //Scale
   sx=sy=sz=1;
   rx = 1;
   //  Color
   r0 = g0 = b0 = 1;
   //  Texture
   tex = NULL;
}

//
//  Show object
//
void Object::setShow(bool on)
{
   show = on;
}

//
//  Object position
//
void Object::setTranslate(float x,float y,float z)
{
   x0 = x;
   y0 = y;
   z0 = z;
}

//
//  Object rotation
//
void Object::setRotate(float t,float dx,float dy,float dz)
{
   th = t;
   rx = dx;
   ry = dy;
   rz = dz;
}
//
//  Set scaling
//
void Object::setScale(float dx,float dy,float dz)
{
   sx = dx;
   sy = dy;
   sz = dz;
}


//
//  Object color
//
void Object::setColor(Color rgb)
{
   r0 = rgb.r;
   g0 = rgb.g;
   b0 = rgb.b;
}

//
//  Object color
//
void Object::setColor(float r,float g,float b)
{
   r0 = r;
   g0 = g;
   b0 = b;
}

//
//  Apply transformation
//
void Object::useTransform()
{
   glTranslated(x0,y0,z0);
   glRotated(th,rx,ry,rz);
   glScaled(sx,sy,sz);
}

//
//  Apply default color
//
void Object::useColor()
{
   useColor(Color(r0,g0,b0));
}

//
//  Apply ambient and diffuse color
//  Specular is set to white
//  Emission is set to black
//
void Object::useColor(Color c)
{
   useColor(c,c,Color(1,1,1),Color(0,0,0),16);
}

//
//  Apply colors
//
void Object::useColor(Color a,Color d,Color s,Color e,float Ns)
{
   glColor4fv(d.fv());
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT ,a.fv());
   glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE ,d.fv());
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,s.fv());
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,e.fv());
   glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,&Ns);
}

//
//  Set texture
//
void Object::setTexture(QString file)
{
   tex = new QOpenGLTexture(QImage(file).mirrored());
   tex->setMinificationFilter(QOpenGLTexture::Linear);
   tex->setMagnificationFilter(QOpenGLTexture::Linear);
}

//
//  Enable texture
//
void Object::EnableTex()
{
   if (tex)
   {
      tex->bind();
      glEnable(GL_TEXTURE_2D);
   }
}

//
//  Disable texture
//
void Object::DisableTex()
{
   if (tex) glDisable(GL_TEXTURE_2D);
}
QMatrix4x4 Object::getModel()
{
	QMatrix4x4 model;//=new QMatrix4x4();
	model.translate(x0,y0,z0);
	model.rotate(th,rx,ry,rz);
	model.scale(sx,sy,sz);
	return model;
}
