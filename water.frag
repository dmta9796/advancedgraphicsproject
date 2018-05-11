#version 120

varying vec3 Normal;
varying vec4 Position;
varying vec3 Camera;

//uniform vec3 cameraPos;
uniform float time;
uniform samplerCube skybox;
uniform mat4 invview;

vec3 mod289(vec3 x) { return x - floor(x * (1.0 / 289.0)) * 289.0; }
vec2 mod289(vec2 x) { return x - floor(x * (1.0 / 289.0)) * 289.0; }
vec3 permute(vec3 x) { return mod289(((x*34.0)+1.0)*x); }

float snoise(vec2 v) {
    const vec4 C = vec4(0.211324865405187,  // (3.0-sqrt(3.0))/6.0
                        0.366025403784439,  // 0.5*(sqrt(3.0)-1.0)
                        -0.577350269189626,  // -1.0 + 2.0 * C.x
                        0.024390243902439); // 1.0 / 41.0
    vec2 i  = floor(v + dot(v, C.yy) );
    vec2 x0 = v -   i + dot(i, C.xx);
    vec2 i1;
    i1 = (x0.x > x0.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
    vec4 x12 = x0.xyxy + C.xxzz;
    x12.xy -= i1;
    i = mod289(i); // Avoid truncation effects in permutation
    vec3 p = permute( permute( i.y + vec3(0.0, i1.y, 1.0 ))
        + i.x + vec3(0.0, i1.x, 1.0 ));

    vec3 m = max(0.5 - vec3(dot(x0,x0), dot(x12.xy,x12.xy), dot(x12.zw,x12.zw)), 0.0);
    m = m*m ;
    m = m*m ;
    vec3 x = 2.0 * fract(p * C.www) - 1.0;
    vec3 h = abs(x) - 0.5;
    vec3 ox = floor(x + 0.5);
    vec3 a0 = x - ox;
    m *= 1.79284291400159 - 0.85373472095314 * ( a0*a0 + h*h );
    vec3 g;
    g.x  = a0.x  * x0.x  + h.x  * x0.y;
    g.yz = a0.yz * x12.xz + h.yz * x12.yw;
    return 130.0 * dot(m, g);
}

void main()
{
	//water generated texture
    vec2 st = Position.xz;
    //st.x *= u_resolution.x/u_resolution.y;
    vec3 color = vec3(0.0);
    vec2 pos = vec2(st*3.);

    float DF = 0.0;

    // Add a random position
    float a = 0.0;
    vec2 vel = vec2(time*.1);
    DF += snoise(pos+vel)*.25+.25;
    
    a = snoise(pos*vec2(cos(time*0.25-st.x)+sin(time*0.3-st.y),cos(time*0.2-st.y)+cos(time*0.1-st.y))*0.1)*3.1415;
    vel = vec2(cos(a),sin(a));
    DF += snoise(pos+vel)*.5-.25;

    color = vec3(clamp(.7,.5,fract(DF))-0.4,clamp(.7,.5,fract(DF))-0.4,1.0);
	
	//reflection and refraction
    float ratio = 1.00 / 1.52;
    vec3 incident_eye=normalize(Position.xyz);
    vec3 normal=normalize(Camera);
    vec3 Reflect=reflect(incident_eye,normal);
    vec3 Refrace=refract(incident_eye,normal,ratio);
    Reflect=vec3(invview*vec4(Reflect,0.0));
    gl_FragColor = mix(vec4(textureCube(skybox, Reflect).rgb, 1.0),vec4(color,1.0),0.5);

}
