// Per pixel lighting
#version 120

varying vec3 View;
varying vec3 Light;
varying vec3 Normal;
varying vec4 Ambient;
varying vec4 lightclipspace;

uniform sampler2D shadowMap;
uniform float nearplane;
uniform float farplane;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    //projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture2D(shadowMap, projCoords.xy).r; 
    //float closestDepth = textureProj(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;
    return shadow;
}  

void main()
{
   //shadow compute
   float shadow=ShadowCalculation(lightclipspace);
   //  N is the object normal
   vec3 N = normalize(Normal);
   //  L is the light vector
   vec3 L = normalize(Light);
   //  V is the view vector
   vec3 V = normalize(View);

   //  Emission and ambient color
   vec4 color = Ambient;

   //  Diffuse light is cosine of light and normal vectors
   //float Id = dot(L,N);
   //  Add diffuse
   //color += Id*(gl_FrontLightProduct[0].diffuse+(1.0 - shadow))*float(Id>0.0);
   //  The half vectors
   //vec3 H = normalize(V+L);
   //  Specular is cosine of reflected and view vectors
   //float Is = dot(H,N);
   //color += pow(Is,gl_FrontMaterial.shininess)*gl_FrontLightProduct[0].specular*float(Is>0.0);
   vec4 lighting = ((Ambient +(1-shadow)) * (gl_FrontLightProduct[0].diffuse + gl_FrontLightProduct[0].specular)) * gl_Color;    
   gl_FragColor = lighting;//color;// * texture2D(tex,gl_TexCoord[0].xy);
}  
