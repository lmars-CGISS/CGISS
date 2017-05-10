#if GL_ES
	precision mediump float;
#endif

uniform sampler3D VolTexture;
uniform sampler2D ColorsTexture;
uniform float minValue;
uniform float maxValue;
// 可以从外面传入;这个值直接影响最终效果,值越小精度越高,效果越好,性能也越慢。
//uniform float texSampleDist;
uniform mat4 viewToTextureMatrix;
uniform mat4 projection_matrix;
uniform mat4 inverse_projection_matrix;
uniform mat4 worldview_matrix;
uniform int bShade;
uniform int bHasColorTable;

varying vec4 viewPos;
varying vec4 texCoord;

vec3 getNormal(vec3 pos)
{
	// 计算法线的时候注意纹理边界的问题，可以在着色器中进行边界值判断或者通过设置边界颜色解决。
	// textureSize3D 可能存在兼容性问题，可以替换为通过变量传入。
    vec3 r=1.0/textureSize3D(VolTexture,0);
    vec3 sample1,sample2;
    sample1.x=texture3D(VolTexture, pos+vec3(-r.x,0.0,0.0)).x;
    sample2.x=texture3D(VolTexture, pos+vec3(r.x,0.0,0.0)).x;
    sample1.y=texture3D(VolTexture, pos+vec3(0.0,-r.y,0.0)).x;
    sample2.y=texture3D(VolTexture, pos+vec3(0.0,r.y,0.0)).x;
    sample1.z=texture3D(VolTexture, pos+vec3(0.0,0.0,-r.z)).x;
    sample2.z=texture3D(VolTexture, pos+vec3(0.0,0.0,r.z)).x;
	
	if (bHasColorTable)
	{
		sample1 = (sample1 - minValue) / (maxValue - minValue);
		sample1 = clamp(sample1, 0.0, 1.0);
		sample2 = (sample2 - minValue) / (maxValue - minValue);
		sample2 = clamp(sample2, 0.0, 1.0);
	}
	
    return normalize(sample2-sample1);
}

vec4 shade(vec3 pos, vec3 cameraDir, vec4 baseColor)
{
	// 视觉坐标系下的一个固定方向
	const vec3 lightDir = vec3(0.0, 0.0, -1.0);
	const float spec_threshold = 0.549280286;
	const float specular_power = 10.0000000;
	const vec3 ambient = vec3(0.3);
	const vec3 diffuse = vec3(0.5);
	const vec3 specular = vec3(0.5);

	float n_dot_l;
	float n_dot_c;
	float n_dot_h;
	vec3 normal=getNormal(pos);
	// 把 normal 变换到视觉坐标系下
	normal = vec3(worldview_matrix*vec4(normal, 0.0));
	vec3 k=ambient;	vec3 b=vec3(0.0);
	n_dot_l=dot(normal,lightDir);
	n_dot_c=dot(normal,cameraDir);
	if ((n_dot_l>0.0 && n_dot_c>0.0) || (n_dot_l<0.0 && n_dot_c<0.0))
    {
		n_dot_l=n_dot_l>0?n_dot_l:-n_dot_l;
        k+=diffuse*n_dot_l;
		vec3 halfwayVector=normalize(lightDir+cameraDir);
        n_dot_h=dot(normal,halfwayVector);
		if (n_dot_h<0) n_dot_h=-n_dot_h;
        if (n_dot_h > spec_threshold)
        {
            b=specular*pow(n_dot_h,specular_power);
        }
	}
	return vec4(vec3(baseColor)*k+b*baseColor.w,baseColor.w);
}

vec4 getSampleValue(vec3 pos, vec3 cameraDir)
{
	float value = texture3D(VolTexture, pos).x;
	vec4 color = vec4(1.0,1.0,1.0,value);
	if (bHasColorTable)
	{
		if (value < minValue || value > maxValue)
		{
			return vec4(0.0);
		}
		value = (value - minValue) / (maxValue - minValue);
		value = clamp(value, 0.0, 1.0);
		color = texture2D(ColorsTexture, vec2(0.0, value));
	}
	if (bShade>0)
		color = shade(pos, cameraDir, color);
		
	//float opacity=AlphaTransfer(color.w);
	//color.w=1;
	//color=color*opacity;
	
	color.rgb *= color.a;
	return color;
}

vec4 castRay(vec3 pos,vec3 texel_step,float t,float tfar,float tstep,vec3 cameraDir)
{
    vec4 result=vec4(0.0);
	while(t<tfar && result.w<0.98)
    {
		result+=(1.0-result.w)*getSampleValue(pos,cameraDir);
		t += tstep;
		pos += texel_step;
    }
	
	if (result.w>0.0)
	{
		result.x*=1.0/result.w;
		result.y*=1.0/result.w;
		result.z*=1.0/result.w;
	}
	
    return result;
}

vec2 intersectBox(vec3 texel_zero, vec3 texel_dir_norm)
{
	float t1,t2;
	t1=(0.0-texel_zero.x)/texel_dir_norm.x;
	t2=(1.0-texel_zero.x)/texel_dir_norm.x;
	float tminX=min(t1,t2);
	float tmaxX=max(t1,t2);
	t1=(0.0-texel_zero.y)/texel_dir_norm.y;
	t2=(1.0-texel_zero.y)/texel_dir_norm.y;
	float tminY=min(t1,t2);
	float tmaxY=max(t1,t2);
	t1=(0.0-texel_zero.z)/texel_dir_norm.z;
	t2=(1.0-texel_zero.z)/texel_dir_norm.z;
	float tminZ=min(t1,t2);
	float tmaxZ=max(t1,t2);
	float largest_tmin = max(max(tminX, tminY), max(tminX, tminZ));
	float smallest_tmax = min(min(tmaxX, tmaxY), min(tmaxX, tmaxZ));
	vec2 result=vec2(largest_tmin,smallest_tmax);
	return result;
}

void main()
{
	// 视觉坐标系下眼睛方向
	vec3 cameraDir = normalize(viewPos.xyz);	// 视觉坐标系下相机位置为原点

	// 获取投影后的最近点和最远点
	vec4 projPos = projection_matrix * viewPos;
	projPos /= projPos.w;
	vec4 projZero = projPos;	projZero.z = -1.0;
	vec4 projOne = projPos;		projOne.z = 1.0;
	// 从投影坐标系变换到视觉坐标系
	vec4 viewZero = inverse_projection_matrix * projZero;
	vec4 viewOne = inverse_projection_matrix * projOne;
	// 从视觉坐标系变换到本地坐标系(即纹理坐标系，因为模型坐标和纹理坐标相同)
	vec4 localZero = viewToTextureMatrix * viewZero;
	vec4 localOne = viewToTextureMatrix * viewOne;
	localZero /= localZero.w, localOne /= localOne.w;
	// 计算纹理坐标系下的视线方向
	vec3 texel_dir_norm = normalize(localOne.xyz - localZero.xyz);
	
	// 光线投射算法(Ray-casting)
	vec3 texel_zero = localZero.xyz;
	vec2 nearFar = intersectBox(texel_zero, texel_dir_norm);
	// 采样间隔受相机与物体之间的距离控制
	//float texSampleDist = clamp(nearFar.x*0.01, 0.002, 0.2);
	float texSampleDist = 0.01;
	vec3 texel_step = texSampleDist * texel_dir_norm;
	float tstep = length(texel_step);
	float tnear = max(nearFar.x, 0.0) + tstep;
	float tfar = nearFar.y - tstep;
	vec3 coord = texel_zero + texel_dir_norm * tnear;
	// 相机在体外时背面不绘制，确保透明叠加效果正确
	if (nearFar.x > 0.0 && length(texCoord.xyz-coord) > (tfar-tnear)*0.5)
	{
		discard;
		return;
	}
	gl_FragColor = castRay(coord, texel_step.xyz, tnear, tfar, tstep, cameraDir);
}
