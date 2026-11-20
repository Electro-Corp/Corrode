#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
}; 

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
uniform Material material;
uniform vec3 viewPosition;
uniform bool rawNoiseUnlit;

void main()
{
    if(rawNoiseUnlit) {
        FragColor = vec4(texture(material.texture_diffuse1, TexCoords).rgb, 1.0);
        return;
    }

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

    vec3 allTex = texture(material.texture_diffuse1, TexCoords).rgb;
    vec3 amb = ambientAtten * allTex;

    // Diffuse
    float diff = max(dot(norm, lDir), 0.0); 
    vec3 diffuse = diffuseAtten * (diff * allTex);

    // Specular
    float spec = pow(max(dot(norm, hDir), 0.0), 15.0f);
    vec3 specular = specularAtten * texture(material.texture_specular1, TexCoords).rgb * spec * 2;

    FragColor = vec4(diffuse + amb + specular, 1.0);

    //FragColor = texture(material.texture_diffuse1, TexCoords);
}
