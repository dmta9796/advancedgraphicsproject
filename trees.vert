
#version 130
//  Per-pixel Blinn-Phong lighting
//  Vertex shader

varying vec3 View;
varying vec3 Light;
varying vec3 Normal;
varying vec4 Ambient;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// 2D Random
float random (in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))
                 * 43758.5453123);
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

void main()
{
   //
   //  Lighting values needed by fragment shader
   //
   //change verticies upward
   //define vertex
   
   //  Vertex location in modelview coordinates
   vec3 P = vec3(gl_ModelViewMatrix * gl_Vertex);
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
   gl_Position = projection*view*model*gl_Vertex;//gl_ModelViewProjectionMatrix * gl_Vertex;
}
