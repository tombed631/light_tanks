#version 130

struct Light{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Material{
	vec3 color_ambient;
	vec3 color_diffuse;
	vec3 color_specular;
	float shininess;
};

varying vec3 normal;
varying vec2 textureCoord;	//texture coordinate
varying vec3 fragWorldPos;	//fragment world coords

uniform vec3 viewPos; //camera world coords
uniform vec3 color;

//lighting texture maps
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform Light light;
uniform Material material;
uniform int isTextured;

void main()
{
	vec3 ambient, diffuse, specular;

	if(isTextured == 1){
		//ambient light
		ambient = light.ambient * vec3(texture(texture_diffuse1, textureCoord));

		//diffuse light
		vec3 norm = normalize(normal);
		vec3 lightDir = normalize(light.position - fragWorldPos);
		float diff = max(dot(norm, lightDir), 0.0);
		diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, textureCoord));
	
		//specular light
		vec3 viewDir = normalize(viewPos - fragWorldPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir),0.0), material.shininess);
		specular = light.specular * spec * vec3(texture(texture_specular1, textureCoord));

	}else{
		//ambient light
		ambient = light.ambient * material.color_ambient;
		
		//diffuse light
		vec3 norm = normalize(normal);
		vec3 lightDir = normalize(light.position - fragWorldPos);
		float diff = max(dot(norm, lightDir), 0.0);
		diffuse = light.diffuse * diff * material.color_diffuse;
		
	
		//specular light
		vec3 viewDir = normalize(viewPos - fragWorldPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir),0.0), material.shininess);
		specular = light.specular * spec * material.color_specular;
		

	}

	gl_FragColor = vec4((ambient + diffuse + specular) * color, 1.0);
}