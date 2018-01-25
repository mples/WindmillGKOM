#version 330 core
in vec3 ourColor;
in vec2 TexCoord;
in vec3 normalVec;
in vec3 fragPoss;

out vec4 color;


uniform sampler2D Texture0;
uniform vec3 lightPos; 
uniform vec3 lightColor;

void main()
{
	float ambientStr = 0.5f;
	vec3 ambient = ambientStr * lightColor;

	//diffuse
	vec3 norm = normalize(normalVec);
	vec3 lightDir = normalize(lightPos - fragPoss);
	float diff = max(dot(norm,lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;
	vec3 res = (ambient + diffuse) * ourColor;
	color = texture(Texture0, TexCoord) * vec4(res, 1.0);

}
