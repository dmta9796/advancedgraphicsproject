//
//  Ex19viewer Widget
//
#include "Trebuchet.h"
#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include "ex19viewer.h"

//
//  Constructor
//
Ex19viewer::Ex19viewer()
{
   //  Set window title
   setWindowTitle(tr("Project"));

   //  Create new OpenGL widget
   ogl = new Ex19opengl;

   //  Select shader
   //QComboBox* shader = new QComboBox();
   //shader->addItem("Scene");

   //  Select projection
  // QComboBox* projection = new QComboBox();
   //projection->addItem("Orthogonal");
   //projection->addItem("Perspective");

   //  Center position
   trebangle = new QSlider(Qt::Horizontal);
   trebangle->setRange(0,360);
   trebarc = new QSlider(Qt::Horizontal);
   trebarc->setRange(0,100);
   Lpos = new QSlider(Qt::Horizontal);
   Zpos = new QSlider(Qt::Horizontal);
   Lpos->setRange(0,360);
   Zpos->setRange(-100,100);
   
   // fire
   fire = new QPushButton("Fire");
   
   
   //random stuff not to be used
   //random = new QPushButton("Random");
   
   //  View angle and zoom
   QLabel* angles = new QLabel();
   
   //Reset
   QPushButton* rst = new QPushButton("Reset");
   //  Quit
   QPushButton* quit = new QPushButton("Quit");

   //  Set layout of child widgets
   QGridLayout* layout = new QGridLayout;
   layout->addWidget(ogl,0,0,5,1);
   //layout->addWidget(new QLabel("Shader"),0,1);
   //layout->addWidget(shader,0,2);
   //layout->addWidget(new QLabel("Projection"),1,1);
   //layout->addWidget(projection,1,2);
   layout->addWidget(new QLabel("Trebuchet Angle"),0,1);
   layout->addWidget(trebangle,0,2);
   layout->addWidget(new QLabel("Trebuchet Arc"),1,1);
   layout->addWidget(trebarc,1,2);
   //layout->addWidget(new QLabel("Light Position"),4,1);
   //layout->addWidget(Lpos,4,2);
   layout->addWidget(fire,2,1);
   //layout->addWidget(random,5,2);
   layout->addWidget(new QLabel("Angles"),3,1);
   layout->addWidget(angles,3,2);
   layout->addWidget(rst,4,1);
   layout->addWidget(quit,4,2);
   //  Manage resizing
   layout->setColumnStretch(0,100);
   layout->setColumnMinimumWidth(0,100);
   layout->setRowStretch(3,100);
   setLayout(layout);

   //  Connect valueChanged() signals to ogl
   //connect(shader,SIGNAL(currentIndexChanged(int))     , ogl,SLOT(setMode(int)));
   //connect(projection,SIGNAL(currentIndexChanged(int)) , ogl,SLOT(setPerspective(int)));
   //connect(Lpos,SIGNAL(valueChanged(int)) , ogl,SLOT(setAngle(int)));
   connect(trebangle,SIGNAL(valueChanged(int)) , ogl,SLOT(setRotationAngle(int)));
   connect(trebarc,SIGNAL(valueChanged(int)) , ogl,SLOT(setFireAngle(int)));
   //  Connect angles() and zoom() signal to labels
   connect(ogl,SIGNAL(angles(QString)) , angles,SLOT(setText(QString)));
   //  Connect reset() and lmove() signals
   connect(fire ,SIGNAL(pressed()),this,SLOT(fireMode()));
   connect(rst  ,SIGNAL(pressed()),ogl,SLOT(reset()));
   //  Connect quit() signal to qApp::quit()
   connect(quit,SIGNAL(pressed()) , qApp,SLOT(quit()));
}
void Ex19viewer::lmove()
{
   bool pause = (light->text()=="Pause");
   if (pause)
      light->setText("Animate");
   else
      light->setText("Pause");
   ogl->setLightMove(!pause);
}
void Ex19viewer::fireMode()
{
   bool stop = (fire->text()=="Stop");
   if (stop)
      fire->setText("Fire");
   else
      fire->setText("Stop");
   ogl->setFireMode(!stop);
}
void Ex19viewer::rotationAngle()
{
	//(Trebuchet)(ogl->CUgl::getobjects()[1])->setRotationAngle(trebangle->value());
	ogl->setRotationAngle(trebangle->value());
}
void Ex19viewer::fireAngle()
{
	//(Trebuchet)(ogl->CUgl::getobjects()[1])->setFireAngle(trebarc->value());
	ogl->setFireAngle(trebarc->value());
}
