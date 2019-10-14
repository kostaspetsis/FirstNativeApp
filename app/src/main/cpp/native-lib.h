//
// Created by kostas on 6/10/2019.
//

#ifndef FIRSTNATIVEAPP_NATIVE_LIB_H
#define FIRSTNATIVEAPP_NATIVE_LIB_H

#include <jni.h>
#include <string>
#include <android/log.h>
#include <unistd.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "Matrix.h"
#include "Texture.h"

#define LOG_TAG "libNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

extern "C"{
JNIEXPORT void JNICALL Java_com_example_kostas_firstnativeapp_NativeLibrary_init(JNIEnv *env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_com_example_kostas_firstnativeapp_NativeLibrary_step(JNIEnv *env, jobject obj);
};
static const char glVertexShader[] =
        "attribute vec4 Position;\n"
        "attribute vec3 Color;\n"
        /* [Add a vertex normal attribute.] */
        "attribute vec3 VertexNormal;\n"
        /* [Add a vertex normal attribute.] */
        "varying vec3 _Color;\n"
        "uniform mat4 projection;\n"
        "uniform mat4 modelView;\n"
        "void main()\n"
        "{\n"
        /* [Setup scene vectors.] */
        "    vec3 transformedVertexNormal = normalize((modelView * vec4(VertexNormal, 0.0)).xyz);"
        "    vec3 inverseLightDirection = normalize(vec3(0.0, 1.0, 1.0));\n"
        "    _Color = vec3(0.0);\n"
        /* [Setup scene vectors.] */
        "\n"
        /* [Calculate the diffuse component.] */
        "    vec3 diffuseLightIntensity = vec3(1.0, 1.0, 1.0);\n"
        "    vec3 vertexDiffuseReflectionConstant = Color;\n"
        "    float normalDotLight = max(0.0, dot(transformedVertexNormal, inverseLightDirection));\n"
        "    _Color += normalDotLight * vertexDiffuseReflectionConstant * diffuseLightIntensity;\n"
        /* [Calculate the diffuse component.] */
        "\n"
        /* [Calculate the ambient component.] */
        "    vec3 ambientLightIntensity = vec3(0.1, 0.1, 0.1);\n"
        "    vec3 vertexAmbientReflectionConstant = Color;\n"
        "    _Color += vertexAmbientReflectionConstant * ambientLightIntensity;\n"
        /* [Calculate the ambient component.] */
        "\n"
        /* [Calculate the specular component.] */
        "    vec3 inverseEyeDirection = normalize(vec3(0.0, 0.0, 1.0));\n"
        "    vec3 specularLightIntensity = vec3(1.0, 1.0, 1.0);\n"
        "    vec3 vertexSpecularReflectionConstant = vec3(1.0, 1.0, 1.0);\n"
        "    float shininess = 2.0;\n"
        "    vec3 lightReflectionDirection = reflect(vec3(0) - inverseLightDirection, transformedVertexNormal);\n"
        "    float normalDotReflection = max(0.0, dot(inverseEyeDirection, lightReflectionDirection));\n"
        "    _Color += pow(normalDotReflection, shininess) * vertexSpecularReflectionConstant * specularLightIntensity;\n"
        /* [Calculate the specular component.] */
        "\n"
        "    /* Make sure the fragment colour is between 0 and 1. */"
        "    clamp(_Color, 0.0, 1.0);\n"
        "\n"
        "    gl_Position = projection * modelView * Position;\n"
        "}\n";
//        "attribute vec4 Position;\n"
//        "attribute vec3 Color;\n"//vertecColour
//        "attribute vec2 TextureCoord;\n"
//        "attribute vec3 VertexNormal;\n"
//        "varying vec2 _TextureCoord;\n"
//        "varying vec3 _Color;\n"
//        "uniform mat4 projection;\n"
//        "uniform mat4 modelView;\n"
//        "void main()\n"
//        "{\n"
//        "   vec3 transformedVertexNormal = normalize((modelView * vec4(VertexNormal,0.0)).xyz);\n"
//        "   vec3 inverseLightDir = normalize(vec3(0.0f,1.0,1.0));\n"
//        "   _Color = vec3(0.0);\n"
//        "   vec3 diffuseLightIntensity = vec3(1.0,1.0,1.0);\n"
//        "   vec3 vertexDiffuseReflectionConstant = Color;\n"
//        "   float normalDotLight = max(0.0, dot(transformedVertexNormal, inverseLightDir));\n"
//        "   _Color += normalDotLight * vertexDiffuseReflectionConstant * diffuseLightIntensity;\n"
//        /* [Calculate the ambient component.] */
//        "    vec3 ambientLightIntensity = vec3(0.1, 0.1, 0.1);\n"
//        "    vec3 vertexAmbientReflectionConstant = Color;\n"
//        "    _Color += vertexAmbientReflectionConstant * ambientLightIntensity;\n"
//        /* [Calculate the ambient component.] */
//        "\n"
//        /* [Calculate the specular component.] */
//        "    vec3 inverseEyeDirection = normalize(vec3(0.0, 0.0, 1.0));\n"
//        "    vec3 specularLightIntensity = vec3(1.0, 1.0, 1.0);\n"
//        "    vec3 vertexSpecularReflectionConstant = vec3(1.0, 1.0, 1.0);\n"
//        "    float shininess = 2.0;\n"
//        "    vec3 lightReflectionDirection = reflect(vec3(0) - inverseLightDir, transformedVertexNormal);\n"
//        "    float normalDotReflection = max(0.0, dot(inverseEyeDirection, lightReflectionDirection));\n"
//        "    _Color += pow(normalDotReflection, shininess) * vertexSpecularReflectionConstant * specularLightIntensity;\n"
//        /* [Calculate the specular component.] */
//        "   clamp(_Color, 0.0, 1.0);\n"
//        "   gl_Position = projection * modelView * Position;\n"
//        "   //_Color = Color;\n"
//        "   _TextureCoord = TextureCoord;\n"
//        "}\n";

static const char glFragmentShader[] =
        "precision mediump float;\n"
        "varying vec3 _Color;\n"
        "varying vec2 _TextureCoord;\n"
        "uniform sampler2D Texture;\n"
        "void main()\n"
        "{\n"
        //"  gl_FragColor = vec4(_Color, 1.0);\n"
        "   gl_FragColor = vec4(_Color,1.0);\n//  texture2D(Texture, _TextureCoord);\n"
        "}\n";

/* [loadShader] */
GLuint loadShader(GLenum shaderType, const char* shaderSource);
/* [loadShader] */

/* [createProgram] */
GLuint createProgram(const char* vertexSource, const char * fragmentSource);
/* [createProgram] */

/* [setupGraphics] */
GLuint program;
GLuint Position;
GLuint Color;
GLuint TextureCoord;
GLuint projectionLocation;
GLuint modelViewLocation;
GLuint vertexNormalLocation;
GLuint sampler;
float projectionMatrix[16];
float modelViewMatrix[16];
float angle=0;
Texture texture;

bool setupGraphics(int w, int h);

//const GLfloat vertices[] = {
//        -1.0f,1.0f,  1.0f,0.0f,0.0f,
//        -1.0f,-1.0f, 0.0f,1.0f,0.0f,
//        1.0f,-1.0f,  0.0f,0.0f,1.0f,
//
//        1.0f,-1.0f,  0.0f,0.0f,1.0f,
//        1.0f,1.0f,  1.0f,1.0f,0.0f,
//        -1.0f,1.0f,  1.0f,0.0f,0.0f,
//};
/* [cubeVertices] */
GLfloat vertices[] = {1.0f,  1.0f, -1.0f, /* Back. */
                      -1.0f,  1.0f, -1.0f,
                      1.0f, -1.0f, -1.0f,
                      -1.0f, -1.0f, -1.0f,
                      0.0f,  0.0f, -2.0f,
                      -1.0f,  1.0f,  1.0f, /* Front. */
                      1.0f,  1.0f,  1.0f,
                      -1.0f, -1.0f,  1.0f,
                      1.0f, -1.0f,  1.0f,
                      0.0f,  0.0f,  2.0f,
                      -1.0f,  1.0f, -1.0f, /* Left. */
                      -1.0f,  1.0f,  1.0f,
                      -1.0f, -1.0f, -1.0f,
                      -1.0f, -1.0f,  1.0f,
                      -2.0f,  0.0f,  0.0f,
                      1.0f,  1.0f,  1.0f, /* Right. */
                      1.0f,  1.0f, -1.0f,
                      1.0f, -1.0f,  1.0f,
                      1.0f, -1.0f, -1.0f,
                      2.0f,  0.0f,  0.0f,
                      -1.0f, -1.0f,  1.0f, /* Bottom. */
                      1.0f, -1.0f,  1.0f,
                      -1.0f, -1.0f, -1.0f,
                      1.0f, -1.0f, -1.0f,
                      0.0f, -2.0f,  0.0f,
                      -1.0f,  1.0f, -1.0f, /* Top. */
                      1.0f,  1.0f, -1.0f,
                      -1.0f,  1.0f,  1.0f,
                      1.0f,  1.0f,  1.0f,
                      0.0f,  2.0f,  0.0f
};
/* [cubeVertices] */
/* [colourComponents] */
GLfloat colour[] = {1.0f, 0.0f, 0.0f, /* Back. */
                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, /* Front. */
                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, /* Left. */
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,
                    1.0f, 1.0f, 0.0f, /* Right. */
                    1.0f, 1.0f, 0.0f,
                    1.0f, 1.0f, 0.0f,
                    1.0f, 1.0f, 0.0f,
                    1.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 1.0f, /* Bottom. */
                    0.0f, 1.0f, 1.0f,
                    0.0f, 1.0f, 1.0f,
                    0.0f, 1.0f, 1.0f,
                    0.0f, 1.0f, 1.0f,
                    1.0f, 0.0f, 1.0f, /* Top. */
                    1.0f, 0.0f, 1.0f,
                    1.0f, 0.0f, 1.0f,
                    1.0f, 0.0f, 1.0f,
                    1.0f, 0.0f, 1.0f
};
/* [colourComponents] */
GLfloat textureCoords[] = {
        1.0f, 1.0f, /* Back. */
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f, /* Front. */
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f, /* Left. */
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f, /* Right. */
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 1.0f, /* Top. */
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f, /* Bottom. */
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
};

/* [indices] */
GLushort indices[] = {0,  2,  4,  0,  4,  1,  1,  4,  3,  2,  3,  4,  /* Back. */
                      5,  7,  9,  5,  9,  6,  6,  9,  8,  7,  8,  9,  /* Front. */
                      10, 12, 14, 10, 14, 11, 11, 14, 13, 12, 13, 14, /* Left. */
                      15, 17, 19, 15, 19, 16, 16, 19, 18, 17, 18, 19, /* Right. */
                      20, 22, 24, 20, 24, 21, 21, 24, 23, 22, 23, 24, /* Bottom. */
                      25, 27, 29, 25, 29, 26, 26, 29, 28, 27, 28, 29  /* Top. */};

GLfloat normals[] = { 1.0f,  1.0f, -1.0f, /* Back. */
                      -1.0f,  1.0f, -1.0f,
                      1.0f, -1.0f, -1.0f,
                      -1.0f, -1.0f, -1.0f,
                      0.0f,  0.0f, -1.0f,
                      -1.0f,  1.0f,  1.0f, /* Front. */
                      1.0f,  1.0f,  1.0f,
                      -1.0f, -1.0f,  1.0f,
                      1.0f, -1.0f,  1.0f,
                      0.0f,  0.0f,  1.0f,
                      -1.0f,  1.0f, -1.0f, /* Left. */
                      -1.0f,  1.0f,  1.0f,
                      -1.0f, -1.0f, -1.0f,
                      -1.0f, -1.0f,  1.0f,
                      -1.0f,  0.0f,  0.0f,
                      1.0f,  1.0f,  1.0f, /* Right. */
                      1.0f,  1.0f, -1.0f,
                      1.0f, -1.0f,  1.0f,
                      1.0f, -1.0f, -1.0f,
                      1.0f,  0.0f,  0.0f,
                      -1.0f, -1.0f,  1.0f, /* Bottom. */
                      1.0f, -1.0f,  1.0f,
                      -1.0f, -1.0f, -1.0f,
                      1.0f, -1.0f, -1.0f,
                      0.0f, -1.0f,  0.0f,
                      -1.0f,  1.0f, -1.0f, /* Top. */
                      1.0f,  1.0f, -1.0f,
                      -1.0f,  1.0f,  1.0f,
                      1.0f,  1.0f,  1.0f,
                      0.0f,  1.0f,  0.0f
};

/* [indices] */
void renderFrame();
#endif //FIRSTNATIVEAPP_NATIVE_LIB_H
