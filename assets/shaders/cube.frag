#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quad;
};

uniform Light light;
uniform vec3 viewPosition;

void main()
{
    vec3 norm = normalize(cross(dFdx(FragPos), dFdy(FragPos)));

    vec3 lDir = normalize(light.position - FragPos);
    vec3 vDir = normalize(viewPosition - FragPos);
    vec3 rDir = reflect(-lDir, norm);
    vec3 hDir = normalize(lDir + vDir);

    // Attenuation and distance
    float distance = length(light.position  - FragPos);
    //float atten = 1.0 / ((distance * distance) * (1.0 + 0.35 * distance * 0.44));
    float atten = (1.0 / distance) * 50;

    vec3 ambientAtten = light.ambient * atten;
    vec3 specularAtten = light.specular * atten;
    vec3 diffuseAtten = light.diffuse * atten;

    vec3 allTex = vec3(100.0, 255.0, 120.0);
    vec3 amb = ambientAtten * allTex;

    // Diffuse
    float diff = max(dot(norm, lDir), 0.0); 
    vec3 diffuse = diffuseAtten * (diff * allTex);

    // Specular
    float spec = pow(max(dot(viewPosition, hDir), 0.0), 32);
    vec3 specular = vec3(0.5 * spec, 0.5 * spec, 0.5 * spec);

    FragColor = vec4(diffuse + amb + specular, 1.0);
}
