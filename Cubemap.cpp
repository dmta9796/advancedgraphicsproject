//
//  Cubemap class
//
#include "Cubemap.h"
#include "CUgl.h"

//
//  Constructor
//
Cubemap::Cubemap(const QString tex)
{
   sx = sy = sz = 1;
   //texture for cube
   if (tex.length()>0) setTexture(tex);
   //  Cube vertex buffer object
   //  Copy data to vertex buffer object
   cube_buffer.create();
   cube_buffer.bind();
   cube_buffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
   cube_buffer.allocate(sizeof(skyboxVertices));
   cube_buffer.write(0,skyboxVertices,sizeof(skyboxVertices));
   //  Unbind this buffer
   cube_buffer.release();
}


//
//  Display the cube
//
void Cubemap::display()
{
	  //  Enable textures and lighting
      glPushMatrix();
      glEnable(GL_LIGHTING);
      EnableTex();
	  
	  //  Enable arrays
      glEnableClientState(GL_VERTEX_ARRAY);


      //  Set pointers
      
      glVertexPointer  (3,GL_FLOAT,3*sizeof(GLfloat),skyboxVertices);

      //draw cubemap
      glPushMatrix();
      useTransform();
      glDepthMask(GL_FALSE);
      glDrawArrays(GL_TRIANGLES,0,cube_size);
      glDepthMask(GL_TRUE);
      glPopMatrix();

      //  Disable arrays
      glDisableClientState(GL_VERTEX_ARRAY);

      //  Disable textures and lighting
      DisableTex();
      glDisable(GL_LIGHTING);
      glPopMatrix();
}
void Cubemap::setRotationAngle(int nth){nth+=1;}
void Cubemap::setFireAngle(int nph){nph+=1;}
Cubemap::~Cubemap(){}
