#version 120
varying vec4 pos;
void main()
{             
	float depth = pos.z/pos.w;
	depth=depth*0.5+0.5;
	float v1=depth*255.0;
	float f1=fract(v1);
	float vn1=floor(v1)/255.0;
	
	float v2=f1*255.0;
	float f2=fract(v2);
	float vn2=floor(v2)/255.0;
	
	float v3=f2*255.0;
	float f3=fract(v3);
	float vn3=floor(v3)/255.0;
	
	gl_FragColor=vec4(vn1,vn2,vn3,f3);
	//gl_FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
}  

//void main()
//{             
	//gl_FragDepth = gl_FragCoord.z;
	//gl_FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
//}  

//vec4(1.0,1.0,1.0,1.0);
//LIBS+= -DGL_GLEXT_PROTOTYPES
