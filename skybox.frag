#version 120
//  Per-pixel Blinn-Phong lighting
//  Fragment shader

varying vec4 TexCoord;
uniform samplerCube skybox;

void main()
{
   gl_FragColor = textureCube(skybox,TexCoord.xyz);
}


