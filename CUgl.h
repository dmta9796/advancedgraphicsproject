//
//  CU OpenGL Widget
//

#ifndef CUGL_H
#define CUGL_H

#include <QtOpenGL>
#include <QString>
#include <QVector>
#include <QVector3D>
#include <QMatrix4x4> 
#include "Object.h"

class CUgl : public QOpenGLWidget
{
Q_OBJECT
private:
   float            La,Ld,Ls; // Light intensity
   float            Lr;       // Light radius
   float            zh;       // Light angle
   float            ylight;   // Light elevation
   bool             move;     // Moving light
   int              obj;      // Selected Object
   QTimer           timer;    // Timer for animations
   float            trebth;   //  Trebuchet rotation dialog
   float            trebph;   //  Trebuchet rotation dialog
   bool             firemode; //  Trebuchet fire mode
   int              reltime;  // relative time from button press
   float            deltaph;  // trebuchet angle speed
protected:
   QElapsedTimer    time;     // Track elapsed time
   QVector<Object*> objects;  // Objects
   bool             mouse;    // Mouse pressed
   QPoint           pos;      // Mouse position
   int              fov;      // Field of view
   float            Dim;      // Default size
   float            dim;      // Display size
   int              th,ph;    // Display angles
   int              mode;     // Selected shader
   QVector<QOpenGLShaderProgram*> shader; // Shaders
   QOpenGLFramebufferObject* m_shadowFBO;
public:
   CUgl(QWidget* parent=0,bool fixed=true);        // Constructor
   QSize sizeHint() const {return QSize(400,400);} // Default size of widget
public slots:
   void reset();
   void setDim(float d);                            // Set scene size
   void setPerspective(int on);                     // Set perspective
   void setShader(int sel);                         // Set shader
   void setObject(int type);                        // Set displayed object
   void addObject(Object* obj);                     // Add object
   void doScene();                                  // Draw scene
   void setLightMove(bool on);                      // Set light animation
   void setLightAngle(int th);                      // Set light angle
   void setLightElevation(int pct);                 // Set light elevation (percent)
   void setLightIntensity(float a,float d,float s); // Set light intensity
   void setRotationAngle(int nth);                  // Set angle of rotation
   void setFireAngle(int nph);                      // Set angle of fire arc
   void setFireMode(bool nfire);                    // set fire mode
   float animatearm();                              // animate arm of ter
   void maxFPS(bool);                               // Set max fps
   void addShader(QString vert,QString frag,QString names=""); // Add shader
   void addShader3(QString vert,QString geom,QString frag);    // Add shader
   int getRelativeTime();                           // get the time relative to button press
   float getRotationAngle();                          // Get angle of rotation
   float getFireAngle();                              // Get angle of fire arc
   bool getFireMode();                              // Get fire mode
   QMatrix4x4 getView();                            // get view matrix
   QMatrix4x4 getLightView();                       // get light view matrix
   QMatrix4x4 getProjection(int type);              // get projection matrix
   QMatrix4x4 getView2();                      // cubemap for reflection
   QMatrix4x4 getLightProjection(int type);         // light source projection
   QVector3D getCamera();                           // camera location
protected:
   void initializeGL();                             // Initialization
   void mousePressEvent(QMouseEvent*);              // Mouse pressed
   void mouseReleaseEvent(QMouseEvent*);            // Mouse released
   void mouseMoveEvent(QMouseEvent*);               // Mouse moved
   void wheelEvent(QWheelEvent*);                   // Mouse wheel
   void Fatal(QString message);                     // Error handler
   QVector3D doLight();                             // Enable light
   void doModelViewProjection();                    // Apply projection
   void doModelViewProjectionLight();               // Apply light projection
   void doOrtho(int w,int h,float zoom=1,float dx=0,float dy=0); // Apply orthographic projection with zoom and pan
   float getTime() {return 0.001*time.elapsed();}   // Elapsed time in seconds
   QOpenGLTexture* loadImage(const QString file);   // Method to load texture
   QOpenGLTexture* loadImage(const QImage image);   // load Qimage to texture
   QOpenGLTexture* loadCubemap(const QString bk,const QString dn,const QString ft,const QString lf,const QString rt,const QString up);
   //uint loadShadowMap();

private slots:
   void tick();                                     // Method to capture timer ticks
signals:
   void light(int angle);                           // Signal for light angle
   void angles(QString text);                       // Signal for view angles
};

#endif
