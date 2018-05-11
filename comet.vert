#version 120

//  Lame fire

uniform   float time;      //  Time
uniform   float time0;      //  Time
//uniform   vec3  pos;       //  Initial position
attribute float Start;     //  Start time
attribute vec3  Vel;       //  Initial velocity
uniform mat4 model;
uniform mat4 view;
uniform bool firemode;
uniform sampler3D Noise3D;
uniform bool collision;

float noise(vec3 X)
{
   vec4 nv = texture3D(Noise3D,X);
   return nv[0]+nv[1]+nv[2]+nv[3]+0.03135;
}


void main(void)
{
	
   //  Particle life and radius of circle
   float t = mod(time,Start);
   //  Initial conditions
   vec4 vert = (gl_Vertex+vec4(0.0,1.8,-1.5,0.0));                //positions
   vec4 vel=vec4(0.0,0.0,0.0,0.0);
   vec3 color=gl_Color.rgb;                                            //Color
   float start= Start;  
   
   //simulation
   //vel=model*vec4(0.0,0.0,0.0,0.0);
   //vel=vec4(0.0,0.0,2.0*(time-t),0.0);
   //vert+=vel;
   
   if(firemode==true)//&& collision(vert)==false)
   {
   	   vel=vec4(0.0,-0.1*(time-start)*(time-start)+1.5*(time-start)+vert.y,2.0*(time-start)+1.0*time,0.0);
   	   vert+=vel;//+noise(vel.xyz);
   }
   //vert+=noise(vel.xyz);
   //vert+=vel;
   //  Noisy yellow trending to red
   gl_FrontColor = vec4(1,color.r,0,1);
   //  Transform particle location
   gl_Position = gl_ProjectionMatrix*view*model*(vert);//+vec4(0.0,0.5,0.0,0.0));
}
