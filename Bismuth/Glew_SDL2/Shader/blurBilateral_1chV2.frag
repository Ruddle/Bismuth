#version 330

in vec2 UV;
out float outColor;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D image;
uniform int h;
uniform vec2 resolution;
uniform float size;
float aspect  =1;
float tanHalfFov=1;

#define SIZE 4.
#define DistE 0.05


 
vec3 decodeNormal(vec2 enc){
	vec3 normal;
	 vec2 fenc = enc.xy*4.0;
    float f = dot(fenc,fenc);
    float g = sqrt(1-f/4);
    normal.xy = fenc*g;
    normal.z = 1-f/2;
	normal = normalize(normal);
	return normal;
}


vec3 getNormal(vec2 uv){
vec3 normal = vec3(texture(gNormal, uv).rg,0);
normal = decodeNormal(normal.xy);
return normal;
}

vec3 getPosition(vec2 uv){


	vec3 position_ViewSpace ;
	position_ViewSpace.z = -texture(gPosition, uv).r ;
	position_ViewSpace.x = -(uv.x*2-1)*position_ViewSpace.z*(aspect) *tanHalfFov ;
	position_ViewSpace.y = -(uv.y*2-1)*position_ViewSpace.z *tanHalfFov ;
	
	return position_ViewSpace;
}


void main()
{





   vec2 sens = vec2(h,1-h);  // horizontal/vertical blur 
    
    float blr = 0;
    float weight = 0; 
    float d0 =  getPosition(UV).z;
    vec3  n0 =  getNormal(UV);
           
    for(float i =-SIZE+1.;i<SIZE;i++){
    	    
      	float signi = min(  max(-1.,i) , 1. ) ;
      	float off = signi *( 1.5 + abs(i)*2.);
     	vec2 offset = ( gl_FragCoord.xy+off*sens)/resolution ;
       
     	float d = getPosition(offset).z;
     	vec3  n = getNormal(offset);
        
        float weightloc = (SIZE- abs(i)) ;  // The closer in screenspace, the heavier
    	weightloc *= 1./(DistE+abs(d-d0)); 	   // The closer in worldSpace (along view vector), the heavier
    	weightloc *= pow(  dot(n,n0) , 2.0 );  // The more the 2 face are opposed, the heavier
     	blr += weightloc * texture(image,    offset).r;
    	weight += weightloc;
        
    }
    blr /= weight; 




outColor =		blr;
}
