#version 120
//layout (location = 0) in vec3 aPos;
uniform   float time;      //  Time

varying vec3 Normal;
varying vec4 Position;
varying vec3 Camera;

uniform mat4 model;
uniform mat4 modelsky;
uniform mat4 invview;
uniform mat4 view;
uniform vec3 CameraPos;
uniform mat4 projection;
uniform sampler3D Noise3D;

float Noise(vec3 X)
{
   vec4 nv = texture3D(Noise3D,X);
   return nv[0]+nv[1]+nv[2]+nv[3]+0.03135;
}

void main()
{
	//vec4 vert=vec4(gl_Vertex.x,7.5*sin(0.1*Noise(gl_Vertex.xyz-vec3(0.01*time,0.01*time,0.0)))-1.0*cos(0.25*Noise(gl_Vertex.xyz-vec3(0.01*time,0.01*time,0.0))),gl_Vertex.z,1.0); this looks ugly 
	
	
	
	//  Texture coordinate for fragment shader
    gl_TexCoord[0] = gl_MultiTexCoord0;
	//
    Normal = normalize(gl_NormalMatrix * gl_Normal);
    Camera = (view*model*vec4(gl_Normal,0.0)).xyz;//CameraPos;
    Position=view*model *gl_Vertex;        // world space
    gl_Position = projection*view*model*gl_Vertex;
}  
