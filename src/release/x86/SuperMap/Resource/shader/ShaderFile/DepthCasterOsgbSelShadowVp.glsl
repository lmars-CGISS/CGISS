attribute vec4 vertex;
attribute vec4 uv0;

uniform mat4 worldviewproj_matrix;
uniform mat4 texture0_matrix;
#if !GL_ES
uniform mat4 worldview_matrix;
#endif

uniform int shadowType;
uniform int hasSelShadow;
uniform sampler2D selShadowTex;
uniform vec4 v4SelShadowRect;

varying vec4 mixColor;
varying vec4 texcoordDepth;
varying float fHeight;
varying vec4 clip_vertex;

void main()
{
	bool needDiscard = false;
	if (shadowType == 1)
	{
		if (hasSelShadow == 1)
		{
			vec2 vecRatio = vec2(v4SelShadowRect.z - v4SelShadowRect.x, v4SelShadowRect.w - v4SelShadowRect.y);
			vec2 texCoord = vec2(vertex.x - v4SelShadowRect.x, vertex.y - v4SelShadowRect.y);
			
			texCoord.x = texCoord.x / vecRatio.x;
			texCoord.y = 1.0 - texCoord.y / vecRatio.y;
			
			if(texCoord.x > 1.0 || texCoord.x < 0.0 || texCoord.y > 1.0 || texCoord.y < 0.0)
			{
				needDiscard = true;
			}
			else
			{
				vec4 texColor = texture2DLod(selShadowTex, texCoord, 0.0);
				if (texColor.r < 0.5)
				{
					needDiscard = true;
				}
			}
		}
		else
		{
			needDiscard = true;
		}
	}
	
	if (needDiscard)
	{
		mixColor = vec4(0.0);
	}
	else
	{
		mixColor = vec4(1.0);
	}
	
	texcoordDepth.xy = vec2(texture0_matrix * uv0);

	// 投影到屏幕上的位置
	gl_Position = worldviewproj_matrix * vec4(vertex.xyz, 1.0);
#if !GL_ES
	gl_ClipVertex = worldview_matrix * vec4(vertex.xyz, 1.0);
	clip_vertex = gl_ClipVertex;
#endif

    fHeight = gl_Position.z/gl_Position.w;
	texcoordDepth.zw = gl_Position.zw;
}
