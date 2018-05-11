
//
//  Cone class
//

#include "Cone.h"
//
//  Constructor
//
Cone::Cone(const QString tex)
{
   sx = sy = sz = 1;
   if (tex.length()>0) setTexture(tex);
}


//
//  Display Cone
//

void Cone::display()
{
	
   if (!show) return;
   //  Save transformation
   glPushMatrix();
   int i = 15;
   int k;
   //  Offset, scale and rotate
   useTransform();
   //  Texture on
   EnableTex();
   glEnable(GL_CULL_FACE);
   //base
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(1.0,1.0);
   glVertex3f(0.0,0.0,0.0);
   for (k=0;k<=360;k+=i)
   {
	   glNormal3f(0,0,-1);
       glTexCoord2f(0.5*Cos(k)+0.5,0.5*Sin(k)+0.5);
       glVertex3f(Cos(k),0,Sin(k));
   }
   glEnd();
    
   //sides
   glBegin(GL_QUAD_STRIP);
   for (k=0;k<=360;k+=i)
   {
	   glNormal3f(Cos(45)*Cos(k),Sin(45),Cos(45)*Sin(k));
	   glTexCoord2f(0.01*k,1); glVertex3f(Cos(k),-0,Sin(k));
       glTexCoord2f(0.01*k,0); glVertex3f(0,+1,0);
   }
   glEnd();
   //  Texture off
   DisableTex();
   glDisable(GL_CULL_FACE);
   //  Undo transofrmations
   glPopMatrix();
}
void Cone::setRotationAngle(int nth){nth+=1;}
void Cone::setFireAngle(int nph){nph+=1;}
