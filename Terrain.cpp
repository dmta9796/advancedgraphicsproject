//
//  Terrain class
//

#include "Terrain.h"
//
//  Constructor
//
Terrain::Terrain(const QString tex)
{
   sx = sy = sz = 1;
   x0 = y0 = z0 = 0;
   th = rx = ry = rz = 0;
   if (tex.length()>0) setTexture(tex);
}

//
//  Display Trebuchet
//

void Terrain::display()
{
   if (!show) return;
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   useTransform();
   // Ennable lighting 
   glEnable(GL_LIGHTING);
   glEnable(GL_CULL_FACE);
   //  Texture on
   EnableTex();
   glTranslated(0, 0, -31.4);
   //glRotatef(45, -1, 0, 0);

   const float offX = -25;
   const float offY = 0;
   const float lato = 2.0;
   const int limit = 25;
   const int limsx = 0;

   glBegin(GL_TRIANGLES);
   glColor3f(1,1,1);
   glNormal3f(0.0,1.0,0.0);
   for (float i = limsx; i < limit-1; ++i) {
       for (float j = limsx; j < limit-1; ++j) {           
           glVertex3f(offX+lato*(j+1),-0.2, offY+lato*i);
           glVertex3f(offX + lato*(j + 1),-0.2, offY + lato*(i + 1));
           glVertex3f(offX + lato*j,-0.2, offY + lato*(i + 1));
           
           glVertex3f(offX + lato*(j),-0.2, offY + lato*(i + 1));
           glVertex3f(offX + lato*(j),-0.2, offY + lato*(i));
           glVertex3f(offX+lato*(j+1),-0.2, offY+lato*i);
           
           glVertex3f(offX + lato*(j + 1),-0.21, offY + lato*(i + 1));
           glVertex3f(offX+lato*(j+1),-0.21, offY+lato*i);
           glVertex3f(offX + lato*j,-0.21, offY + lato*(i + 1));
           
           glVertex3f(offX + lato*(j),-0.21, offY + lato*(i));
           glVertex3f(offX + lato*(j),-0.21, offY + lato*(i + 1));
           glVertex3f(offX+lato*(j+1),-0.21, offY+lato*i);
       }
   }
   glEnd();
   //Disable lighting
   glDisable(GL_LIGHTING);  
   glDisable(GL_CULL_FACE); 
   //  Texture off
   DisableTex();
   //  Undo transofrmations
   glPopMatrix();
}
void Terrain::setRotationAngle(int nth){nth+=1;}
void Terrain::setFireAngle(int nph){nph+=1;}

