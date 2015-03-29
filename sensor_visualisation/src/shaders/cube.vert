//#version 120

attribute vec3 vertexPosition;
attribute vec3 vertexColor;
attribute vec3 vertexNormal;

uniform mat4 modelViewMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;
uniform mat4 projectionMatrix;
uniform mat4 mvp;

varying vec3 frag_Position;
varying vec3 frag_Normal;
varying vec3 frag_Normal2;
varying vec4 color;

void main()
{
    frag_Position = vec3(modelMatrix * vec4(vertexPosition, 1.0));
    color = vec4(abs(vertexColor), 1.0);

    frag_Normal = normalize(mat3(modelMatrix) * normalize(vertexNormal));
    frag_Normal2 = normalize(normalize(vertexNormal));

    gl_Position = mvp*vec4(vertexPosition, 1.0);
}
