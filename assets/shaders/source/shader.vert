#version 450

layout(set = 0, binding = 0) uniform Transform
{
	mat4 MODEL;
	mat4 VIEW;
	mat4 PROJECTION;
} tf;

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;

layout(location = 0) out vec3 FragColor;

void main()
{
	gl_Position = tf.PROJECTION * tf.VIEW * tf.MODEL * vec4(aPos, 0.0, 1.0);
	FragColor = aColor;
}