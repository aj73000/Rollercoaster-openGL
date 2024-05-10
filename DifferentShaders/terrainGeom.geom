#version 460

layout (triangles) in;

layout (triangle_strip, max_vertices = 3) out;

in vec2 textC[];
out vec2 TextureCoords;
in float height[];
out float Height;

void main()
{
    if(gl_in[0].gl_Position.x > -150 && gl_in[0].gl_Position.x < 150 && gl_in[0].gl_Position.z < 200)
    {
        Height = height[0];
        TextureCoords = textC[0];
        gl_Position = gl_in[0].gl_Position;
        EmitVertex();
        Height = height[1];
        TextureCoords = textC[1];
        gl_Position = gl_in[1].gl_Position;
        EmitVertex();
        Height = height[2];
        TextureCoords = textC[2];
        gl_Position = gl_in[2].gl_Position;
        EmitVertex();
        EndPrimitive();
    }

}