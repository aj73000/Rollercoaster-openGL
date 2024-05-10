#version 460

layout (triangles) in;

layout (line_strip, max_vertices = 6) out;

in vec2 textC[];
out vec2 TextureCoords;
out float Height;

void main()
{

    if(gl_in[0].gl_Position.x > -150 && gl_in[0].gl_Position.x < 150 && gl_in[0].gl_Position.z < 200)
    {
        Height = 35;
        TextureCoords = textC[0];
        gl_Position = gl_in[0].gl_Position + vec4(0, 0.0f, 0.0, 0.0);
        EmitVertex();
        Height = 35;
        TextureCoords = textC[0];
        gl_Position = gl_in[0].gl_Position + vec4(0, 0.5f, 0.0, 0.0);
        EmitVertex();
        EndPrimitive();

        gl_Position = gl_in[0].gl_Position + vec4(0, 0.0f, 0.0, 0.0);
        EmitVertex();
        Height = 35;
        TextureCoords = textC[0];
        gl_Position = gl_in[0].gl_Position + vec4(0.5f, 0.5f, 0.0, 0.0);
        EmitVertex();
        EndPrimitive();

        gl_Position = gl_in[0].gl_Position + vec4(0, 0.0f, 0.0, 0.0);
        EmitVertex();
        Height = 35;
        TextureCoords = textC[0];
        gl_Position = gl_in[0].gl_Position + vec4(-0.5f, 0.5f, 0.0, 0.0);
        EmitVertex();
        EndPrimitive();
    }

}