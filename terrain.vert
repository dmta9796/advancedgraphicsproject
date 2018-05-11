#version 120

uniform   float time;      //  Time

varying vec3 View;
varying vec3 Light;
varying vec3 Normal;
varying vec4 Ambient;
varying vec4 Vert;

uniform sampler2D tex;
uniform sampler3D Noise3D;
uniform mat4 model;
uniform mat4 trebmodel;
uniform mat4 castlemodel;
uniform mat4 treemodel;

//uniform float width;
//uniform float length;


// 2D Random
float random (in vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898,78.233)))* 43758.5453123);
    //return fract(sin(dot(st.xy, vec2(12.0,78.0)))* 43758.0);
}

// 2D Noise since the Noise texture doesn't work well 
float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    // Smooth Interpolation

    // Cubic Hermine Curve.  Same as SmoothStep()
    vec2 u = f*f*(3.0-2.0*f);
    // u = smoothstep(0.,1.,f);

    // Mix 4 coorners porcentages
    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}
float vertcoord()
{
	vec2 coords=(trebmodel*gl_Vertex).xz;
	vec2 coords2= 5.0*gl_Vertex.xz;
	
	return 0.0;
}

void main()
{
   //define vertex
   vec4 vert= gl_Vertex;
   //vec3 X = 5.0*gl_Vertex.xyz;
   //float e = 0.5*Noise(2.0*X);
   vec2 X = 5.0*gl_Vertex.xz;
   float e = noise(X)+0.5*noise(2.0*X)+0.25*noise(4.0*X)+0.125*noise(4.0*X);
   vert.y+=e-0.65;//pow(e, 0.5)-0.65;
   //
   //  Lighting values needed by fragment shader
   //
   //  Vertex location in modelview coordinates
   vec3 P = vec3(gl_ModelViewMatrix * vert);
   //  Light position
   Light  = vec3(gl_LightSource[0].position) - P;
   //  Normal
   Normal = gl_NormalMatrix * gl_Normal;
   //  Eye position
   View  = -P;
   //  Ambient color
   Ambient = gl_FrontMaterial.emission + gl_FrontLightProduct[0].ambient + gl_LightModel.ambient*gl_FrontMaterial.ambient;

   //  Texture coordinate for fragment shader
   gl_TexCoord[0] = gl_MultiTexCoord0;
   
   //  Set vertex position
   gl_Position = gl_ModelViewProjectionMatrix * vert;
   Vert=gl_Vertex;
}
