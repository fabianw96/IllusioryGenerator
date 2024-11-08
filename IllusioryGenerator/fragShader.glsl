#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

struct Light{
    vec3 ambient;
    vec3 position;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};

uniform Light lights[10];
uniform Material material;
uniform int numLights;
uniform vec3 viewPos;

vec3 CalcLight(Light light);

void main()
{
    vec3 result = vec3(0.0f);

    for (int i = 0; i < numLights; i++) {
       result += CalcLight(lights[i]);
    }

    FragColor = vec4(result, 1.0);
}

vec3 CalcLight(Light light)
{
    vec4 diffuseMap = texture(material.texture_diffuse1, TexCoord);
    vec3 ambient = light.ambient * diffuseMap.rgb;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * diffuseMap.rgb;

    //specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec4 specularMap = texture(material.texture_specular1, TexCoord);
    vec3 specular = light.specular * spec * light.diffuse * specularMap.rgb;

    //attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (1.0 + 0.1 * distance + 0.01 * distance * distance);

    return (ambient + diffuse + specular) * attenuation;
}