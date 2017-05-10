//鼠标位置
uniform float fMousePosX;
uniform float fMousePosY;

uniform float fWidth;
uniform float fHeight;

uniform float fTolerance;

varying vec3 color;

varying float bDiscard;

void main(void)
{
	vec4 pos = gl_ModelViewProjectionMatrix * vec4(gl_Vertex.xyz, 1.0);
	
	//得到顶点屏幕位置 范围0-1
	float fPosX = pos.x / pos.w;
	float fPosY = pos.y / pos.w;
	float fPosZ = pos.z / pos.w;

	bDiscard = 1.0;

	if(fPosZ < 1.0 && fPosZ > 0.0 && fPosX < 1.0 && fPosX > -1.0 && fPosY < 1.0 && fPosY > -1.0)
	{
		fPosX = fPosX * 0.5 + 0.5;
		fPosY = fPosY * 0.5 + 0.5;

		//得到顶点屏幕像素位置
		fPosX = fPosX * fWidth;
		fPosY = fPosY * fHeight;

		//距离
		float fDisY = (fMousePosY - fPosY) * (fMousePosY - fPosY);
		float fDisX = (fMousePosX - fPosX) * (fMousePosX - fPosX);

		float fDis = fDisX + fDisY;
	
		if( fDis < fTolerance * fTolerance )
		{
			bDiscard = 0.0;
		}
	
		pos.x = 0.0;
		pos.y = 0.0;

		color = (gl_ModelViewMatrix * vec4(gl_Vertex.xyz, 1.0)).xyz;
	}

	gl_Position = pos;
}


