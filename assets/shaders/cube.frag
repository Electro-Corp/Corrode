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

    vec3 res = (amb + diff + spec) * vec3(1.0, 0.1, 0.1);
    FragColor = vec4(res, 1.0);
}
