#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec4 FragPosLight;

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
    //vec3 norm = normalize(cross(dFdx(FragPos), dFdy(FragPos)));

    vec3 norm = normalize(Normal);

    vec3 lDir = normalize(light.position - FragPos);
    vec3 vDir = normalize(viewPosition - FragPos);
    vec3 rDir = reflect(-lDir, norm);
    vec3 hDir = normalize(lDir + vDir);

    vec3 lColor = vec3(1.0, 1.0, 1.0);

    // Ambient
    float aS = 0.1;
    vec3 amb = aS * lColor;
    // Diffuse
    float d = max(dot(norm, lDir), 0.0);
    vec3 diff = d * lColor;

    // Specular
    float sS = 0.5;
    float s = pow(max(dot(vDir, rDir), 0.0), 32);
    vec3 spec = sS * s * lColor;

    // Shadow
    float shadow = shadowCalculation(FragPosLight, lDir, norm);
    
    vec3 lighting = (amb + (1.0 - shadow) * (diff + spec)) * vec3(1.0, 0.1, 0.1);

    FragColor = vec4(lighting, 1.0);
}
