#ifndef EX19V_H
#define EX19V_H

#include "CUgl.h"
#include <QWidget>
#include <QSlider>
#include <QDoubleSpinBox>
#include "ex19opengl.h"

class Ex19viewer : public QWidget
{
Q_OBJECT
private:
   QSlider*     Lpos;
   QSlider*     Zpos;
   QSlider*     trebangle;
   QSlider*     trebarc;
   QPushButton* light;
   QPushButton* fire;
   Ex19opengl*  ogl;
private slots:
    void lmove();             //Trebuchet movement
    void fireMode();              //start/stop simulation
    void fireAngle();         //Trebuchet movement
    void rotationAngle();     //Trebuchet movement
public:
    Ex19viewer();
};

#endif
