//
//  Trees class
//

#include "Trees.h"
//
//  Constructor
//
Trees::Trees(const QString tex)
{
   sx = sy = sz = 1;
   if (tex.length()>0) setTexture(tex);
      //  Copy data to vertex buffer object
   tree_buffer.create();
   tree_buffer.bind();
   tree_buffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
   tree_buffer.allocate(sizeof(tree_data));
   tree_buffer.write(0,tree_data,sizeof(tree_data));
   //  Unbind this buffer
   tree_buffer.release();
}

//
//  Display Trebuchet
//

void Trees::display()
{
	  //  Enable textures and lighting
      glPushMatrix();
      glEnable(GL_LIGHTING);
      EnableTex();
	  
	  //  Enable arrays
      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_NORMAL_ARRAY);
      glEnableClientState(GL_COLOR_ARRAY);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);

      //  Set pointers
      
      glVertexPointer  (4,GL_FLOAT,18*sizeof(GLfloat),tree_data);
      glNormalPointer  (  GL_FLOAT,18*sizeof(GLfloat),tree_data+4);
      glColorPointer   (3,GL_FLOAT,18*sizeof(GLfloat),tree_data+7);
      glTexCoordPointer(2,GL_FLOAT,18*sizeof(GLfloat),tree_data+10);

      //  Draw the cube slightly offset
      glPushMatrix();
      useTransform();
      glDrawArrays(GL_TRIANGLES,0,tree_size);
      glPopMatrix();

      //  Disable arrays
      glDisableClientState(GL_VERTEX_ARRAY);
      glDisableClientState(GL_NORMAL_ARRAY);
      glDisableClientState(GL_COLOR_ARRAY);
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);

      //  Disable textures and lighting
      DisableTex();
      glDisable(GL_LIGHTING);
      glPopMatrix();
}
void Trees::setRotationAngle(int nth){nth+=1;}
void Trees::setFireAngle(int nph){nph+=1;}

