#version 120
uniform mat4 lightMatrix;
uniform mat4 modelMatrix;
uniform mat4 projectionLightMatrix;

varying vec4 pos;

void main()
{
    //gl_Position = lightMatrix * modelMatrix * gl_Vertex;
    //gl_Position = gl_ModelViewProjectionMatrix* gl_Vertex;
    //gl_Position = gl_ProjectionMatrix*view*model*gl_Vertex;
    //pos = projectionLightMatrix*lightMatrix*modelMatrix* gl_Vertex;
    
    
    pos = gl_ModelViewProjectionMatrix* gl_Vertex;
    gl_Position=pos;
}  
