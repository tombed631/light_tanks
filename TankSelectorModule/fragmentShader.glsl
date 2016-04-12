#version 130

struct Light{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


varying vec3 normal;
varying vec2 textureCoord;	//texture coordinate
varying vec3 fragWorldPos;	//fragment world coords

uniform vec3 viewPos; //camera world coords


//lighting texture maps
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_specular3;
uniform Light light;

void main()
{

	//ambient light
	vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, textureCoord));

	//diffuse light
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragWorldPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, textureCoord));

	//specular light
	vec3 viewDir = normalize(viewPos - fragWorldPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir),0.0), 32);
	vec3 specular = light.specular * spec * vec3(texture(texture_specular1, textureCoord));

	//gl_FragColor = vec4(1.0,1.0,1.0,0.0); //set white color


	gl_FragColor = vec4(ambient + diffuse + specular, 1.0);
	
}