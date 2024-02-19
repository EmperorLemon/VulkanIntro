#version 450

//layout(set = 0, binding = 0) uniform Transform
//{
//	mat4 MODEL;
//	mat4 VIEW;
//	mat4 PROJECTION;
//} tf;

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;

void main()
{
	gl_Position = vec4(aPos, 0.0, 1.0);
}