
#version 120
//  Per-pixel Blinn-Phong lighting
//  Vertex shader

uniform mat4 view;
uniform mat4 model;

varying vec4 TexCoord;

void main()
{
   //  Texture coordinate for cubemap
   TexCoord=gl_Vertex;
   //  Set vertex position
   gl_Position = (gl_ProjectionMatrix*view*model*gl_Vertex);
}
