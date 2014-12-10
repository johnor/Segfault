#version 120

varying vec3 frag_Position;
varying vec3 frag_Normal;
varying vec3 frag_Normal2;
varying vec4 color;

uniform vec3 cameraPosition;

void main()
{
    //v: eye
    //r: reflected
    vec3 r, v, lightDirection;
    vec3 lightPos = vec3(1.0f, 1.0f, 1.0f);
    float diffuseStrength, specularStrength, distance;
    distance = 1.0;
    lightDirection = normalize(lightPos);

    r = normalize(-reflect(lightDirection, frag_Normal));
    diffuseStrength = max(dot(lightDirection, frag_Normal), 0.0f);

    if (diffuseStrength > 0.0f)
    {
        v = normalize(cameraPosition - frag_Position);
        float specularExponent = 5.0f;
        specularStrength = pow(max(dot(r, v), 0.1f), specularExponent);
    }
    else
    {
        diffuseStrength = 0.0f;
        specularStrength = 0.0f;
    }
    gl_FragColor = (diffuseStrength + specularStrength + 0.2f) * color;
}
