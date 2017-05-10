attribute vec4 vertex;
attribute vec3 normal;
attribute vec4 colour;
attribute vec4 uv0;

varying vec3 noiseCoord;
varying vec4 projectionCoord;
varying vec3 oEyeDir;
varying vec3 oNormal;
varying vec4 mixColor;

uniform mat4 worldviewproj_matrix;
uniform vec3 camera_position_object_space; // object space
uniform float waterTimeVal;
uniform float scale;  // the amount to scale the noise texture by
uniform float scroll; // the amount by which to scroll the noise
uniform float noise;  // the noise perturb as a factor of the  time
uniform vec3 bumpSpeed;

void main(void)
{
	vec4 oPos = worldviewproj_matrix * vec4(vertex.xyz, 1.0);


	mat4 scalemat = mat4(0.5, 0.0, 0.0, 0.0,
					0.0, -0.5, 0.0, 0.0,
					0.0, 0.0, 0.5, 0.0,
					0.5, 0.5, 0.5, 1.0);
	projectionCoord = scalemat * oPos;
	noiseCoord.xy = uv0.xy * scale + bumpSpeed.xy * waterTimeVal;
	noiseCoord.z = noise * waterTimeVal;

	oEyeDir = vertex.xyz - camera_position_object_space; 
	oNormal = normal.rgb;

	mixColor = colour;

	gl_Position = oPos;
}
