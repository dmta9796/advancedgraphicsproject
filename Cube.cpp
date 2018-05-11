//
//  Cube class
//
#include "Cube.h"
#include "CUgl.h"

//
//  Constructor
//
Cube::Cube(const QString tex)
{
   sx = sy = sz = 1;
   //texture for cube
   if (tex.length()>0) setTexture(tex);
   //  Cube vertex buffer object
   //  Copy data to vertex buffer object
   cube_buffer.create();
   cube_buffer.bind();
   cube_buffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
   cube_buffer.allocate(sizeof(cube_data));
   cube_buffer.write(0,cube_data,sizeof(cube_data));
   //  Unbind this buffer
   cube_buffer.release();
}
//
//  Display the cube
//
void Cube::display()
{
	  //  Enable textures and lighting
      glPushMatrix();
      glEnable(GL_LIGHTING);
      //glEnable(GL_CULL_FACE);
      EnableTex();
	  
	  //  Enable arrays
      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_NORMAL_ARRAY);
      glEnableClientState(GL_COLOR_ARRAY);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);

      //  Set pointers
      
      glVertexPointer  (4,GL_FLOAT,18*sizeof(GLfloat),cube_data);
      glNormalPointer  (  GL_FLOAT,18*sizeof(GLfloat),cube_data+4);
      glColorPointer   (3,GL_FLOAT,18*sizeof(GLfloat),cube_data+7);
      glTexCoordPointer(2,GL_FLOAT,18*sizeof(GLfloat),cube_data+10);

      //  Draw the cube slightly offset
      glPushMatrix();
      useTransform();
      glDrawArrays(GL_TRIANGLES,0,cube_size);
      glPopMatrix();

      //  Disable arrays
      glDisableClientState(GL_VERTEX_ARRAY);
      glDisableClientState(GL_NORMAL_ARRAY);
      glDisableClientState(GL_COLOR_ARRAY);
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);

      //  Disable textures and lighting
      DisableTex();
      glDisable(GL_LIGHTING);
      //glDisable(GL_CULL_FACE);
      glPopMatrix();
}
void Cube::setRotationAngle(int nth){nth+=1;}
void Cube::setFireAngle(int nph){nph+=1;}

