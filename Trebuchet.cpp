//
//  Trebuchet class
//

#include "Trebuchet.h"
//
//  Constructor
//
Trebuchet::Trebuchet(const QString tex)
{
   sx = sy = sz = 1;
   if (tex.length()>0) setTexture(tex);
}
//
//  Display Trebuchet
//
void Trebuchet::arm()
{
   //arm
   Cylinder *arm1= new Cylinder();
   QVector3D vec=setCenteredRotation(0.0,0.0,0.0);
   arm1->Object::setTranslate(vec.x(),vec.y(),vec.z());
   arm1->Object::setScale(0.1,0.1,1.0);
   arm1->Object::setRotate(90.0,0.0,1.0,0.0);
   //arm1->Object::setTranslate(0.0,1.5,0.0);
   arm1->display();
   delete arm1;
   
   Cylinder *arm2= new Cylinder();
   vec=setCenteredRotation(0.0,0.0,0.0);
   arm2->Object::setTranslate(vec.x(),vec.y(),vec.z());
   arm2->Object::setRotate(ph,1.0,0.0,0.0);
   arm2->Object::setScale(0.1,0.1,1.0);
   //arm2->Object::setTranslate(0.0,1.5,0.0);
   arm2->display();
   delete arm2;
   
   //weight
   Cube *weight=new Cube();
   vec=setCenteredRotation(0.0,0.0,1.25);
   weight->Object::setTranslate(vec.x(),vec.y(),vec.z()); 
   //weight->Object::setTranslate(0.0,1.5,1.25); 
   weight->Object::setRotate(ph,1.0,0.0,0.0); 
   weight->Object::setScale(0.25,0.5,0.25);
   weight->display();
   delete weight;
   
   //platform
   Cube *platform1=new Cube();
   vec=setCenteredRotation(0.0,0.05,-1.0);
   platform1->Object::setTranslate(vec.x(),vec.y(),vec.z()); 
   //platform1->Object::setTranslate(0.0,1.55,-1.0); 
   platform1->Object::setScale(0.25,0.15,0.01);
   platform1->Object::setRotate(ph,1.0,0.0,0.0); 
   platform1->display();
   delete platform1;
   
   Cube *platform2=new Cube();
   vec=setCenteredRotation(0.0,-0.1,-1.25);
   platform2->Object::setTranslate(vec.x(),vec.y(),vec.z()); 
   //platform2->Object::setTranslate(0.0,1.4,-1.25);
   platform2->Object::setRotate(ph,1.0,0.0,0.0);  
   platform2->Object::setScale(0.25,0.01,0.25);
   platform2->display();
   delete platform2;
   
   Cube *platform3=new Cube();
   vec=setCenteredRotation(0.25,0.025,-1.25);
   platform3->Object::setTranslate(vec.x(),vec.y(),vec.z()); 
   //platform3->Object::setTranslate(0.25,1.4+0.125,-1.25); 
   platform3->Object::setRotate(ph,1.0,0.0,0.0); 
   platform3->Object::setScale(0.01,0.125,0.25);
   platform3->display();
   delete platform3;

   
   Cube *platform4=new Cube();
   vec=setCenteredRotation(-0.25,0.025,-1.25);
   platform4->Object::setTranslate(vec.x(),vec.y(),vec.z());
   //platform4->Object::setTranslate(-0.25,1.4+0.125,-1.25); 
   platform4->Object::setRotate(ph,1.0,0.0,0.0); 
   platform4->Object::setScale(0.01,0.125,0.25);
   platform4->display();
   delete platform4;

}
void Trebuchet::display()
{
	
   if (!show) return;
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   useTransform();
   //  Texture on
   EnableTex();
   setRotate(th,0.0,1.0,0.0);
   //base
   Cube *base1=new Cube();
   base1->Object::setTranslate(-1.0,0.0,0.0); 
   base1->Object::setScale(0.1,0.1,2.0);
   base1->display();
   delete base1;
   
   Cube *base2= new Cube(); 
   base2->Object::setTranslate(1.0,0.0,0.0); 
   base2->Object::setScale(0.1,0.1,2.0);
   base2->display();
   delete base2;
   
   Cube *base3= new Cube(); 
   base3->Object::setTranslate(0.0,0.0,1.5); 
   base3->Object::setScale(1.0,0.1,0.1);
   base3->display();
   delete base3;
   
   Cube *base4= new Cube(); 
   base4->Object::setTranslate(0.0,0.0,-1.5); 
   base4->Object::setScale(1.0,0.1,0.1);
   base4->display();
   delete base4;
   
   //supports
   Cube *support1=new Cube();
   support1->Object::setTranslate(1.0,1.0,0.0); 
   support1->Object::setScale(0.1,1.0,0.1);
   support1->display();
   delete support1;
   
   Cube *support2=new Cube();
   support2->Object::setTranslate(-1.0,1.0,0.0); 
   support2->Object::setScale(0.1,1.0,0.1);
   support2->display();
   delete support2;
   
   //arm render
   arm();
   //  Texture off
   DisableTex();
   //  Undo transofrmations
   glPopMatrix();
}
void Trebuchet::setRotationAngle(int nth)
{
	th=nth;
}
void Trebuchet::setFireAngle(int nph)
{
	ph=nph;
}
QVector3D Trebuchet::setCenteredRotation(float x, float y, float z) // translate around a center
{
	QVector4D vec=QVector4D(x,y,z,1.0); 
	QMatrix4x4 mat;
    //mat.translate(x,y,z);
    mat.translate(0.0,1.5,0.0);
    mat.rotate(ph,1,0,0);
	
	QVector3D coord=(mat*vec).toVector3D();
	return coord;
	
}
