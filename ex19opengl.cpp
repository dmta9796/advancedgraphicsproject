//
//  OpenGL widget
//
#include "ex19opengl.h"
#include "Object.h"
#include <QStringList>
#include <QVector>
#include <QMatrix4x4>
#include "Noise.h"
#include "Sphere.h"
#include "Cube.h"
#include "Cubemap.h"
#include "Cylinder.h"
#include "Trebuchet.h"
#include "Terrain.h"
#include "Cone.h"
#include "Water.h"
#include "Castle.h"
#include "Particle.h"
#include "Trees.h"
#include <math.h>
//  Set up array indexes for program
const int VELOCITY_ARRAY=4;
const int START_ARRAY=5;
const char* Name = ",,,,Vel,Start";

/*
 *  Random numbers with range and offset
 */
static float frand(float rng,float off)
{
   return rand()*rng/RAND_MAX+off;
}

/*
 *  Initialize particles
 */
void Ex19opengl::InitPart(void)
{
   //  Array Pointers
   float* vert  = Vert;
   float* color = Color;
   float* vel   = Vel;
   float* start = Start;
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
         *color++ = frand(0.5,0.5);
         *color++ = frand(0.5,0.5);
         *color++ = frand(0.5,0.5);
         //  Velocity
         *vel++ = 0;//frand( 1.0,3.0);
         *vel++ = 0;//frand(10.0,0.0);
         *vel++ = 0;//frand( 1.0,3.0);
         //  Launch time
         *start++ = frand(2.0,0.0);
      }
}

/*
 *  Draw particles
 */
void Ex19opengl::DrawPart(void)
{
   QOpenGLFunctions glf(QOpenGLContext::currentContext());
   //  Set particle size
   glPointSize(15);
   //  Point vertex location to local array Vert
   glVertexPointer(3,GL_FLOAT,0,Vert);
   //  Point color array to local array Color
   glColorPointer(3,GL_FLOAT,0,Color);
   //  Point attribute arrays to local arrays
   glf.glVertexAttribPointer(VELOCITY_ARRAY,3,GL_FLOAT,GL_FALSE,0,Vel);
   glf.glVertexAttribPointer(START_ARRAY,1,GL_FLOAT,GL_FALSE,0,Start);
   //  Enable arrays used by DrawArrays
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
   glf.glEnableVertexAttribArray(VELOCITY_ARRAY);
   glf.glEnableVertexAttribArray(START_ARRAY);
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
   glf.glDisableVertexAttribArray(VELOCITY_ARRAY);
   glf.glDisableVertexAttribArray(START_ARRAY);
}

//
//  Constructor
//
Ex19opengl::Ex19opengl(QWidget* parent)
    : CUgl(parent,false)
{
   N = 50;
   Vert  = new float[3*N*N];
   Color = new float[3*N*N];
   Vel   = new float[3*N*N];
   Start = new float[N*N];
   InitPart();
}

//
//  Initialize
//
void Ex19opengl::setMode(int m)
{
   setShader(m);
   InitPart();
}

//
//  Initialize
//
void Ex19opengl::initializeGL()
{
   //  Load shaders
   addShader(":/ex19b.vert",":/ex19b.frag",Name);  //nothing shader
   addShader(":/skybox.vert",":/skybox.frag",Name);  //skybox shader
   addShader(":/models.vert",":/models.frag",Name);  //models shader
   addShader(":/terrain.vert",":/terrain.frag",Name); //terrain shader
   addShader(":/water.vert",":/water.frag",Name);    //water shader
   addShader(":/comet.vert",":/ex19b.frag",Name);    //particle system
   addShader(":/trees.vert",":/trees.frag",Name);    //shadows
   
   
   //Load Objects
   addObject((new Cubemap("")));    //Skybox
   addObject((new Trebuchet("")));  //
   addObject((new Terrain("")));    //
   addObject((new Water("")));      //
   addObject((new Castle("")));     //
   addObject((new Trees("")));      //make trees
   addObject((new Trees("")));      //make trees
   addObject((new Trees("")));      //make trees

   
   //init framebuffer
   //fbow = fmin(width()*devicePixelRatio(),1024);
   //fboh = fmin(height()*devicePixelRatio(),1024);
   //makeCurrent();
   //depthMapFBO = new QOpenGLFramebufferObject(fbow,fboh, QOpenGLFramebufferObject::Depth);//,GL_TEXTURE_2D, GL_RGBA8);

   //  Load smoke particle
   tex1 = loadImage(":/crate.png");
   tex2 = loadImage(":/grass.bmp");
   tex3 = loadImage(":/particle.png");
   tex4 = loadImage(":/Wall.jpg");
   tex5 = loadImage(":/wood2.bmp");
   tex6 = loadImage(":/tree1.bmp");
   cubemap=loadCubemap(":/nevada_bk.png",":/nevada_dn.png",":/nevada_ft.png",":/nevada_lf.png",":/nevada_rt.png",":/nevada_up.png");

}
void Ex19opengl::modelCoords()
{
   //skybox
   CUgl::objects[0]->setRotate(180,1.0,0.0,0.0); //skybox upside down
   //trebuchet
   CUgl::objects[1]->setTranslate(1.0,1.6,-1.0);
   CUgl::objects[1]->setScale(0.25,0.25,0.25);
   //water
   CUgl::objects[3]->setTranslate(0, 0, -31.4);

   //castle
   CUgl::objects[4]->setTranslate(4.5,1.25,-6.0);
   CUgl::objects[4]->setScale(0.5,0.5,0.5);
}
//void Ex19opengl::testbuffer()
//{
   //QMatrix4x4 model;
   //QMatrix4x4 lightViewMatrix=CUgl::getLightView();
   //QMatrix4x4 lightProjectionMatrix=CUgl::getLightProjection(0);
   //QMatrix4x4 lightSpaceMatrix=lightViewMatrix*lightProjectionMatrix;
   //shadowmap->bind();
   //shader[2]->bind();
   //shader[2]->setUniformValue("lightSpaceMatrix",lightSpaceMatrix);
   //shader[2]->setUniformValue("shadowmap",4)
   //model=CUgl::objects[5]->getModel();
   //shader[2]->setUniformValue("model",model);
   //float near=dim/16.0;
   //float far=dim*16.0;
   //shader[2]->setUniformValue("nearplane",near);
   //shader[2]->setUniformValue("farplane",far);
   //setObject(5);
   //doScene();
   //shader[2]->release();
   //delete shadowmap; // free shadow map memory;
//}
//
//  Draw the window
//
void Ex19opengl::paintGL()
{	
	//clear and enable depth
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	
	//matrix transforms
    QMatrix4x4 model;
    QMatrix4x4 lightViewMatrix=CUgl::getLightView();
    QMatrix4x4 lightProjectionMatrix=CUgl::getLightProjection(0);
    QMatrix4x4 lightSpaceMatrix=lightViewMatrix*lightProjectionMatrix;
    
    //load model coords
    modelCoords();
	
	////shadow pass
    ////setup depth buffer
    	
	//doModelViewProjectionLight();
	//depthMapFBO->bind();
	//glDrawBuffer(GL_NONE);
    //glReadBuffer(GL_NONE);
	//depthMapFBO->release();
	//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	////glClear(GL_COLOR_BUFFER_BIT);
    //glViewport(0, 0, depthMapFBO->width(), depthMapFBO->height());
    //glEnable(GL_DEPTH_TEST);
    ////glEnable(GL_POLYGON_OFFSET_FILL);
    ////glDisable(GL_LIGHTING);    
    
    ////draw scene
    //depthMapFBO->bind();
    //shader[6]->bind();
    //shader[6]->setUniformValue("lightSpaceMatrix",lightSpaceMatrix);
    //shader[6]->setUniformValue("view",getView());
    //shader[6]->setUniformValue("projection",getProjection(1));
    //for(int i =0;i<6;i++)
    //{
		//model=CUgl::objects[i]->getModel();
        //shader[6]->setUniformValue("model",model);
		//setObject(i);
		//doScene();
    //}
    //shader[6]->release();
    
    ////fetch texture
    //int shadowmapindex=depthMapFBO->texture();
    //glActiveTexture(GL_TEXTURE4);
    //glBindTexture(GL_TEXTURE4,shadowmapindex);
    
	////shadowmap=loadImage(depthMapFBO->toImage(QImage::Format_RGB32));//.toImageFormat(QImage::Format_RGB32)));

	////QImage img=depthMapFBO->toImage();
	////QImage test=QGLWidget::grabFrameBuffer(false);
    //depthMapFBO->release();
    ////test.save("fbo2.jpg");
    ////img.save("fbo.jpg");   // test image	
	
	
   //render scene	
   //  Wall time (seconds)
   float t = 0.001*time.elapsed();
   zh = fmod(90*t,360);

   //  Clear screen and Z-buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);
   
   //  Apply projection
   doModelViewProjection();
   
   
   ////shadow map frame buffer debug
   //shader[2]->bind();
   ////shadowmap->bind();
   //shader[2]->setUniformValue("lightSpaceMatrix",lightSpaceMatrix);
   //CUgl::objects[5]->setTranslate(0.0,1.0,0.0);
   //model=CUgl::objects[5]->getModel();
   //shader[2]->setUniformValue("model",model);
   //shader[2]->setUniformValue("view",getView());
   //shader[2]->setUniformValue("projection",getProjection(1));
   ////loadImage(img)->bind();
   //setObject(5);
   //doScene();
   //shader[2]->release();
   
   
   //skybox
   cubemap->bind();   
   shader[1]->bind();
   shader[1]->setUniformValue("time",t);
   shader[1]->setUniformValue("skybox",0);
   shader[1]->setUniformValue("view",getView2());
   CUgl::objects[0]->setRotate(180,1.0,0.0,0.0); //skybox upside down
   QMatrix4x4 skyboxmodel=CUgl::objects[0]->getModel(); //get skybox world coords 
   shader[1]->setUniformValue("model",skyboxmodel);
   // Draw skybox
   setObject(0);
   doScene();
   //  Release shader
   shader[1]->release();
   
   //  Apply lighting
   doLight();
   //  light
   
   //  Bind texture and shader
   tex5->bind();   
   shader[2]->bind();
   shader[2]->setUniformValue("time",t);
   shader[2]->setUniformValue("img",0);
   CUgl::objects[1]->setFireAngle(animatearm()); //CUgl::getFireAngle()+
   CUgl::objects[1]->setRotationAngle(CUgl::getRotationAngle());
   CUgl::objects[1]->setTranslate(1.0,0.35,-1.0);
   CUgl::objects[1]->setScale(0.25,0.25,0.25);
   QMatrix4x4 trebmodel=CUgl::objects[1]->getModel(); //get trebuchet world coords 
   shader[2]->setUniformValue("model",trebmodel);
   shader[2]->setUniformValue("lightSpaceMatrix",lightSpaceMatrix);
   // Draw trebuchet
   setObject(1);
   doScene();
   //tex5->release();
   
   //draw castle
   tex4->bind();
   setObject(4);
   CUgl::objects[4]->setTranslate(4.5,0.25,-6.0);
   CUgl::objects[4]->setScale(0.5,0.5,0.5);
   doScene();
   //  Release shader
   shader[2]->release();
   //tex4->release();
   
   //  Bind texture and shader
   tex2->bind();   
   shader[3]->bind();
   shader[3]->setUniformValue("time",t);
   shader[3]->setUniformValue("img",0);
   shader[3]->setUniformValue("Noise3D",1);
   model=CUgl::objects[2]->getModel();
   shader[3]->setUniformValue("model",model);
   shader[3]->setUniformValue("lightSpaceMatrix",lightSpaceMatrix);
   // Draw terrain
   setObject(2);
   doScene();
   //  Release shader
   shader[3]->release();
   //tex2->release(); 
   
   //  Bind texture and shader
   cubemap->bind();   
   shader[4]->bind();
   shader[4]->setUniformValue("time",t);
   shader[4]->setUniformValue("skybox",0);
   model=CUgl::objects[3]->getModel();
   shader[4]->setUniformValue("model",model);
   shader[4]->setUniformValue("invmodel",model.transposed().inverted());
   shader[4]->setUniformValue("view",getView());
   shader[4]->setUniformValue("projection",getProjection(1));
   //QMatrix4x4 modelsky=CUgl::objects[0]->getModel();
   //shader[4]->setUniformValue("modelsky",modelsky);
   shader[4]->setUniformValue("invview",getView().inverted());
   QVector3D CameraPos=getCamera();
   shader[4]->setUniformValue("CameraPos",CameraPos);
   shader[4]->setUniformValue("lightSpaceMatrix",lightSpaceMatrix);
   // Draw water
   setObject(3);
   doScene();
   //  Release shader
   shader[4]->release();
   //cubemap->release();  
   
   //  Bind texture
   tex6->bind();  
   //  Apply shader
   shader[6]->bind();
   shader[6]->setUniformValue("time",t-getRelativeTime());
   shader[6]->setUniformValue("img",0);
   shader[6]->setUniformValue("view",getView());
   shader[6]->setUniformValue("projection",getProjection(1));
   shader[6]->setUniformValue("lightSpaceMatrix",lightSpaceMatrix);
   shader[6]->setUniformValue("firemode",getFireMode());
   // Draw tree  
   CUgl::objects[5]->setTranslate(-2.0,0.35,2.7);
   model=CUgl::objects[5]->getModel();
   shader[6]->setUniformValue("model",model);
   setObject(5);
   doScene();
   setObject(7);
   doScene();
   //  Release shader
   shader[6]->release();
      //  Bind texture
   tex6->bind();  
   //  Apply shader
   shader[6]->bind();
   shader[6]->setUniformValue("time",t-getRelativeTime());
   shader[6]->setUniformValue("img",0);
   shader[6]->setUniformValue("view",getView());
   shader[6]->setUniformValue("projection",getProjection(1));
   shader[6]->setUniformValue("lightSpaceMatrix",lightSpaceMatrix);
   shader[6]->setUniformValue("firemode",getFireMode());
   // Draw tree  
   CUgl::objects[6]->setTranslate(-2.1,0.275,3.0);
   model=CUgl::objects[6]->getModel();
   shader[6]->setUniformValue("model",model);
   setObject(6);
   doScene();
   //  Release shader
   shader[6]->release();
      //  Bind texture
   tex6->bind();  
   //  Apply shader
   shader[6]->bind();
   shader[6]->setUniformValue("time",t-getRelativeTime());
   shader[6]->setUniformValue("img",0);
   shader[6]->setUniformValue("view",getView());
   shader[6]->setUniformValue("projection",getProjection(1));
   shader[6]->setUniformValue("lightSpaceMatrix",lightSpaceMatrix);
   shader[6]->setUniformValue("firemode",getFireMode());
   // Draw tree  
   CUgl::objects[7]->setTranslate(-2.3,0.45,2.75);
   model=CUgl::objects[7]->getModel();
   shader[6]->setUniformValue("model",model);
   setObject(7);
   doScene();
   //  Release shader
   shader[6]->release();
   
     
   //  Bind texture
   tex3->bind();  
   //  Apply shader
   shader[5]->bind();
   shader[5]->setUniformValue("time",t-getRelativeTime());
   shader[5]->setUniformValue("img",0);
   //CUgl::objects[1]->setTranslate(1.0,1.0,1.0);
   trebmodel=CUgl::objects[1]->getModel(); //get trebuchet world coords 
   shader[5]->setUniformValue("model",trebmodel);
   shader[5]->setUniformValue("view",getView());
   shader[5]->setUniformValue("lightSpaceMatrix",lightSpaceMatrix);
   shader[5]->setUniformValue("firemode",getFireMode());
   // Draw particles
   DrawPart();
   //  Release shader
   shader[5]->release();
   //tex3->release(); 
   
   
   
   //  Draw axes
   glBegin(GL_LINES);
   glVertex3d(0,0,0);
   glVertex3d(1,0,0);
   glVertex3d(0,0,0);
   glVertex3d(0,1,0);
   glVertex3d(0,0,0);
   glVertex3d(0,0,1);
   glEnd();
   
   //shadows pass
   //loadShadowMap();
   
   ////shadow first pass
   //loadShadowMap();
   
   //shadow map frame buffer debug
   //shader[2]->bind();
   //shadowmap->bind();
   //shader[2]->setUniformValue("lightSpaceMatrix",lightSpaceMatrix);
   //CUgl::objects[5]->setTranslate(0.0,1.0,0.0);
   //model=CUgl::objects[5]->getModel();
   //shader[2]->setUniformValue("model",model);
   //shader[2]->setUniformValue("view",getView());
   //shader[2]->setUniformValue("projection",getProjection(1));
   ////loadImage(img)->bind();
   //setObject(5);
   //doScene();
   //shader[2]->release();
     
   ////shadow second pass
   //shadowmap->bind();
   //shader[7]->bind();
   //shader[7]->setUniformValue("lightSpaceMatrix",lightSpaceMatrix);
   //model=CUgl::objects[1]->getModel();
   //shader[7]->setUniformValue("model",model);
   //float near=dim/16.0;
   //float far=dim*16.0;
   //shader[7]->setUniformValue("nearplane",near);
   //shader[7]->setUniformValue("farplane",far);
   //setObject(-1);
   //doScene();
   //shader[7]->release();
   //delete shadowmap; // free shadow map memory;
   
   
}
//QImage Ex19opengl::loadShadowMap()
//{
	////matrix transforms
    //QMatrix4x4 model;
    //QMatrix4x4 lightViewMatrix=CUgl::getLightView();
    //QMatrix4x4 lightProjectionMatrix=CUgl::getLightProjection(0);
    //QMatrix4x4 lightSpaceMatrix=lightViewMatrix*lightProjectionMatrix;
    ////setup depth buffer
    	
	//doModelViewProjectionLight();
	//depthMapFBO->bind();
	//glDrawBuffer(GL_NONE);
    //glReadBuffer(GL_NONE);
	//depthMapFBO->release();
	//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	////glClear(GL_COLOR_BUFFER_BIT);
    
    ////glMatrixMode(GL_MODELVIEW);
    ////glLoadIdentity();
    //glViewport(0, 0, depthMapFBO->width(), depthMapFBO->height());
    //glEnable(GL_DEPTH_TEST);
    ////glEnable(GL_POLYGON_OFFSET_FILL);
    ////glDisable(GL_LIGHTING);    
    
    ////draw scene
    ////depthMapFBO->bind();
    //shader[6]->bind();
    ////glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //shader[6]->setUniformValue("lightSpaceMatrix",lightSpaceMatrix);
    //shader[6]->setUniformValue("view",getView());
    //shader[6]->setUniformValue("projection",getProjection(1));
    //for(int i =0;i<6;i++)
    //{
		//model=CUgl::objects[i]->getModel();
        //shader[6]->setUniformValue("model",model);
		//setObject(i);
		//doScene();
    //}
    //shader[6]->release();
    
	//shadowmap=loadImage(depthMapFBO->toImage(QImage::Format_RGB32));//.toImageFormat(QImage::Format_RGB32)));
	//QImage img=depthMapFBO->toImage(QImage::Format_RGB32);
    //depthMapFBO->release();
    //delete depthMapFBO;
    //return img;
    
    
    //glDisable(GL_POLYGON_OFFSET_FILL);
    //glColorMask(1,1,1,1);
    //shadow second pass
    //shadowmap->bind();
    //shader[7]->bind();
    //shader[7]->setUniformValue("lightSpaceMatrix",lightSpaceMatrix);
    ////float near=dim/16.0;
    ////float far=dim*16.0;
    //shader[7]->setUniformValue("nearplane",near);
    //shader[7]->setUniformValue("farplane",far);
    //for(int i=0;i<6;i++)
    //{
		//model=CUgl::objects[i]->getModel();
		//shader[7]->setUniformValue("model",model);
		//setObject(i);
		//doScene();
	//}
	////model=CUgl::objects[2]->getModel();
    ////shader[7]->setUniformValue("model",model);
	////setObject(2);
	////doScene();
    //shader[7]->release();
    //delete shadowmap; // free shadow map memory; 
    //doModelViewProjection();
    //glEnable(GL_LIGHTING);
    //glActiveTexture(GL_TEXTURE0);
	
//}
//void Ex19opengl::loadShadowMap()
//{
	//unsigned int shadowMap;
	//unsigned int depthFBO;
	//int w = fmin(width()*devicePixelRatio(),1024);
    //int h = fmin(height()*devicePixelRatio(),1024);
	//glGenTextures(1, &shadowMap);
	//glBindTexture(GL_TEXTURE_2D, shadowMap);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,w,h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	
	//glGenFramebuffers(1,&depthFBO);
	//glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthFBO, 0);
	//glDrawBuffer(GL_NONE);
	//glReadBuffer(GL_NONE);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);  
	
	//glViewport(0, 0, w, h);
	//glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
    //glClear(GL_DEPTH_BUFFER_BIT);
    ////ConfigureShaderAndMatrices();
    //doScene();
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//// 2. then render scene as normal with shadow mapping (using depth map)
	//glViewport(0, 0, w, h);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	////ConfigureShaderAndMatrices();
	//glBindTexture(GL_TEXTURE_2D, shadowMap);
	////doScene();
//}
