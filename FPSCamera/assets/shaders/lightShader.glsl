/*
This is the fragment shader, and it's main job is to determine the color for each pixel (fragment)
*/

//specifies the version of the shader (and what features are enabled)
#version 400 core
in vec3 Normal;
in vec3 FragPos;
out vec4 color;






struct Material{
vec3 ambient;
vec3 diffuse;
vec3 specular;
float shininess;
};
uniform Material material;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
//entry point for the fragment shader
void main(void)
{
	
	
	vec3 ambient = material.ambient * lightColor;
	
	//diffuse

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = lightColor * (diff * material.diffuse) ;

	//specular
	

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = lightColor * (material.specular * spec);

	vec3 result = (ambient + diffuse + specular);
	color = vec4(result, 1.0);
	
}