#include <lib/ClipPlane.glsllib>

#if GL_ES
	precision highp float;
#endif

//uniform sampler2D diffuseMap0;
uniform vec4 textureSize;
uniform vec4 materialAmbient;
uniform int isFloatTex;

varying vec4 mixColor;
varying vec4 texcoordDepth;

vec4 packDepth(float depth)
{
  const vec4 c_bias = vec4(1.0 / 255.0, 1.0 / 255.0, 1.0 / 255.0, 0.0);

  float r = depth;
  float g = fract(r * 255.0);
  float b = fract(g * 255.0);
  float a = fract(b * 255.0);
  vec4 color = vec4(r, g, b, a);

  return color - (color.yzww * c_bias);
}

void main()
{
	// �ж������Ƿ����
	/*if (textureSize.x > 1.0 && textureSize.y > 1.0)
	{
		// ͸�����岻������Ӱ���������ֵ���ñ���
		vec4 texDiffuse = texture2D(diffuseMap0, texcoordDepth.xy);
		if (texDiffuse.a < 0.5)
		{
			discard;
			return;
		}
	}*/
	
	// �жϲ��ʻ򶥵��Ƿ�͸��
	float alpha = mixColor.a * materialAmbient.a;
	if (alpha < 0.5)
	{
		discard;
		return;
	}

	int clipResult = Clip();
	if(clipResult < 0)
	{
		discard;
		return;
	}

	float fDepth = texcoordDepth.z / texcoordDepth.w;
	// fDepth �ķ�ΧΪ(-1, 1)��
	if (isFloatTex == 1)
	{
		// float ��ʽ������Ա��渺ֵ�����Կ��Բ����й�һ��
		gl_FragColor = vec4(fDepth, fDepth, fDepth, 1.0);
	}
	else
	{
		fDepth = fDepth * 0.5 + 0.5;
		gl_FragColor = packDepth(fDepth);
	}
}
