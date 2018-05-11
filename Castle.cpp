//
//  Castle class
//

#include "Castle.h"
//
//  Constructor
//
Castle::Castle(const QString tex)
{
   sx = sy = sz = 1;
   if (tex.length()>0) setTexture(tex);
}
//
//  Display Castle
//

void Castle::display()
{
	
   if (!show) return;
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   useTransform();
   //  Texture on
   EnableTex();
   //base
   Cube *base1=new Cube();
   //base1->Object::setTranslate(-1.0,0.0,0.0); 
   //base1->Object::setScale(0.1,0.1,2.0);
   base1->display();
   delete base1;
   //towers
   Cylinder *tower1=new Cylinder();
   tower1->Object::setTranslate(1.0,0.0,1.0);
   tower1->Object::setRotate(90,1.0,0.0,0.0); 
   tower1->Object::setScale(0.5,0.5,2.0);
   tower1->display();
   delete tower1;
   
   Cylinder *tower2=new Cylinder();
   tower2->Object::setTranslate(-1.0,0.0,1.0);
   tower2->Object::setRotate(90,1.0,0.0,0.0); 
   tower2->Object::setScale(0.5,0.5,2.0);
   tower2->display();
   delete tower2;
   
   Cylinder *tower3=new Cylinder();
   tower3->Object::setTranslate(-1.0,0.0,-1.0); 
   tower3->Object::setRotate(90,1.0,0.0,0.0);
   tower3->Object::setScale(0.5,0.5,2.0);
   tower3->display();
   delete tower3;
   
   Cylinder *tower4=new Cylinder();
   tower4->Object::setTranslate(1.0,0.0,-1.0); 
   tower4->Object::setRotate(90,1.0,0.0,0.0);
   tower4->Object::setScale(0.5,0.5,2.0);
   tower4->display();
   delete tower4;
   
   //tower tops
   Cone *top1=new Cone();
   top1->Object::setTranslate(1.0,2.0,1.0); 
   top1->Object::setRotate(90,0.0,1.0,0.0);
   top1->Object::setScale(0.5,2.0,0.5);
   top1->display();
   delete top1;
   
   Cone *top2=new Cone();
   top2->Object::setTranslate(1.0,2.0,-1.0); 
   top2->Object::setRotate(90,0.0,1.0,0.0);
   top2->Object::setScale(0.5,2.0,0.5);
   top2->display();
   delete top2;

   
   Cone *top3=new Cone();
   top3->Object::setTranslate(-1.0,2.0,-1.0); 
   top3->Object::setRotate(90,0.0,1.0,0.0);
   top3->Object::setScale(0.5,2.0,0.5);
   top3->display();
   delete top3;
   
   Cone *top4=new Cone();
   top4->Object::setTranslate(-1.0,2.0,1.0); 
   top4->Object::setRotate(90,0.0,1.0,0.0);
   top4->Object::setScale(0.5,2.0,0.5);
   top4->display();
   delete top4;
   //  Texture off
   DisableTex();
   //  Undo transofrmations
   glPopMatrix();
}
void Castle::setRotationAngle(int nth){nth+=1;}
void Castle::setFireAngle(int nph){nph+=1;}

