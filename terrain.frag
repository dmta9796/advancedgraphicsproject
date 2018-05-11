//  Per-pixel Blinn-Phong lighting
//  Fragment shader

varying vec3 View;
varying vec3 Light;
varying vec3 Normal;
varying vec4 Ambient;
varying vec4 Vert;
uniform sampler2D tex;

void main()
{
   //  N is the object normal
   vec3 N = normalize(Normal);
   //  L is the light vector
   vec3 L = normalize(Light);
   //  V is the view vector
   vec3 V = normalize(View);

   //  Emission and ambient color
   vec4 color = Ambient;

   //  Diffuse light is cosine of light and normal vectors
   float Id = dot(L,N);
   //  Add diffuse
   color += Id*gl_FrontLightProduct[0].diffuse*float(Id>0.0);
   //  The half vectors
   vec3 H = normalize(V+L);
   //  Specular is cosine of reflected and view vectors
   float Is = dot(H,N);
   color += pow(Is,gl_FrontMaterial.shininess)*gl_FrontLightProduct[0].specular*float(Is>0.0);
   gl_FragColor = color * texture2D(tex,Vert.xz);//gl_TexCoord[0].xy);
}

