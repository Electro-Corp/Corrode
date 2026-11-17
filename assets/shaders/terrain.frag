#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;
in vec4 FragPosLight;

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
uniform sampler2D shadowMap;

float shadowCalculation(vec4 lSpace, vec3 lDir, vec3 norm){
    // Perspective divide
    vec3 proj = lSpace.xyz / lSpace.w;
    proj = proj * 0.5 + 0.5;
    if(proj.z > 1.0) return 0.0;

    float closestDepth = texture(shadowMap, proj.xy).r;
    float currentDepth = proj.z;
    float bias = max(0.005 * (1.0 - dot(norm, lDir)), 0.001);

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x){
        for(int y = -1; y <= 1; ++y){
            float pcD = texture(shadowMap, proj.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > closestDepth ? 1.0 : 0.0;
        }
    }

    return shadow /= 9.0;
}

void main() {
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

    // Shadow
    float shadow = shadowCalculation(FragPosLight, lDir, norm);
    
    vec3 lighting = (amb + (1.0 - shadow) * (diffuse + specular));

    FragColor = vec4(lighting, 1.0);

    //FragColor = texture(material.texture_diffuse1, TexCoords);
}
