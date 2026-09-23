#version 330 core

in vec3 v_WorldPos;
in vec3 v_Normal;
in vec2 v_TexCoord;

out vec4 FragColor;

uniform sampler2D u_Texture;
uniform bool u_UseTexture;
uniform vec4 u_Color;

uniform vec3 u_LightDirection;
uniform vec3 u_LightColor;

void main()
{
    vec4 baseColor = u_UseTexture ? texture(u_Texture, v_TexCoord)
                                  : vec4(1.0);

    if (baseColor.a * u_Color.a < 0.01)
        discard;

    vec3 normal = normalize(v_Normal);
    vec3 lightDir = normalize(-u_LightDirection);

    // Ambient
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * u_LightColor;

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * u_LightColor;

    vec3 lighting = ambient + diffuse;

    FragColor = vec4(
        baseColor.rgb * u_Color.rgb * lighting,
        baseColor.a * u_Color.a
    );
}