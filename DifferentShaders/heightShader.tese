#version 460 core
layout(quads, fractional_odd_spacing, ccw) in;

uniform sampler2D heightMap;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec2 TextureCoord[];
out vec2 TextureCoords;

out float Height;


float random(in vec2 _st)
{
    return fract(sin(dot(_st.xy,vec2(12.9898,78.233)))*43758.5453123);
}
float noise(in vec2 st)
{
    vec2 i = floor(st);
    vec2 f = fract(st);

    float a =  random(i);
    float b = random(i+vec2(1,0));
    float c = random(i+vec2(0,1));
    float d = random(i+vec2(1,1));
    vec2 u = f*f*(3-2*f);
    return mix(a,b,u.x)+(c-a)*u.y*(1-u.x)+(d-b)*u.x*u.y;
}

void main()
{
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;



    vec2 t00 = TextureCoord[0];
    vec2 t01 = TextureCoord[1];
    vec2 t10 = TextureCoord[2];
    vec2 t11 = TextureCoord[3];

    vec2 t0 = (t01 - t00) * u + t00;
    vec2 t1 = (t11 - t10) * u + t10;
    vec2 texCoord = (t1 - t0) * v + t0;

    TextureCoords = texCoord;

    Height = 120*noise(texCoord*50);

    vec4 p00 = gl_in[0].gl_Position;
    vec4 p01 = gl_in[1].gl_Position;
    vec4 p10 = gl_in[2].gl_Position;
    vec4 p11 = gl_in[3].gl_Position;

    vec4 p0 = (p01 - p00) * u + p00;
    vec4 p1 = (p11 - p10) * u + p10;
    vec4 p = (p1 - p0) * v + p0 + normalize(vec4(0,-1,0,0)) * Height;

    gl_Position = projection * view * model * p;
}