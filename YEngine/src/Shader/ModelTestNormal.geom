#version 330 core
layout (triangles) in;
layout (line_strip,max_vertices = 24)out;

uniform bool u_bNormalLine;
uniform bool u_bFaceLine;
uniform bool u_bTangentLine;
uniform bool u_bBittangentLine;
in VS_OUT
{
  vec3 normal;
  vec3 tangent;
  vec3 bittangent;
}gs_in[];
out vec3 LineColor;
const float MAGNITUDE = 0.08;

void GenerateNoramlLine(int index)
{
   LineColor = vec3(1.0,1.0,0.0);
   gl_Position = gl_in[index].gl_Position;
   EmitVertex();
   
   gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal,1.0) * MAGNITUDE;
   EmitVertex();

   EndPrimitive();

}
void GenerateTangentLine(int index)
{
   LineColor = vec3(1.0,0.0,0.0);
   gl_Position = gl_in[index].gl_Position;
   EmitVertex();
   
   gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].tangent,1.0) * MAGNITUDE;
   EmitVertex();

   EndPrimitive();

}
void GenerateBittangentLine(int index)
{
   LineColor = vec3(0.0,1.0,0.0);
   gl_Position = gl_in[index].gl_Position;
   EmitVertex();
   
   gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].bittangent,1.0) * MAGNITUDE;
   EmitVertex();

   EndPrimitive();

}
void GenerateTriangleLine()
{
 LineColor = vec3(0.7,0.7,0.7);
    gl_Position = gl_in[1].gl_Position;
   EmitVertex();
   
   gl_Position = gl_in[2].gl_Position ;
   EmitVertex();

   EndPrimitive();
   gl_Position = gl_in[2].gl_Position;
   EmitVertex();
   
   gl_Position = gl_in[0].gl_Position ;
   EmitVertex();

   EndPrimitive();

}

void main()
{
 if(u_bNormalLine)
 {
    GenerateNoramlLine(0);
   GenerateNoramlLine(1);
   GenerateNoramlLine(2);
 }
 if(u_bTangentLine)
 {
    GenerateTangentLine(0);
   GenerateTangentLine(1);
   GenerateTangentLine(2);
 }
 if(u_bBittangentLine)
 {
    GenerateBittangentLine(0);
   GenerateBittangentLine(1);
   GenerateBittangentLine(2);
 }
  if(u_bFaceLine)
  {
    GenerateTriangleLine();
  }
    
}