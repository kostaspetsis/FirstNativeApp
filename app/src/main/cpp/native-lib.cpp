#include "native-lib.h"


JNIEXPORT void JNICALL Java_com_example_kostas_firstnativeapp_NativeLibrary_init(
        JNIEnv *env, jobject obj, jint width, jint height) {
    LOGI("Hello world from the Native-Side(C++);");
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL Java_com_example_kostas_firstnativeapp_NativeLibrary_step(JNIEnv *env, jobject obj){
//    sleep(5);
    LOGI("New Frame Ready to be drawn!!!");
    renderFrame();
}

GLuint loadShader(GLenum shaderType, const char* shaderSource)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader)
    {
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);

        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        if (!compiled)
        {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

            if (infoLen)
            {
                char * buf = (char*) malloc(infoLen);

                if (buf)
                {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not Compile Shader %d:\n%s\n", shaderType, buf);
                    free(buf);
                }

                glDeleteShader(shader);
                shader = 0;
            }
        }
    }

    return shader;
}

GLuint createProgram(const char* vertexSource, const char * fragmentSource)
{
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
    if (!vertexShader)
    {
        return 0;
    }

    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (!fragmentShader)
    {
        return 0;
    }

    GLuint _program = glCreateProgram();

    if (_program)
    {
        glAttachShader(_program , vertexShader);
        glAttachShader(_program, fragmentShader);

        glLinkProgram(_program);
        GLint linkStatus = GL_FALSE;

        glGetProgramiv(_program , GL_LINK_STATUS, &linkStatus);

        if( linkStatus != GL_TRUE)
        {
            GLint bufLength = 0;

            glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &bufLength);

            if (bufLength)
            {
                char* buf = (char*) malloc(bufLength);

                if (buf)
                {
                    glGetProgramInfoLog(_program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(_program);
            _program = 0;
        }
    }

    return _program;
}

bool setupGraphics(int w, int h){
    program = createProgram(glVertexShader, glFragmentShader);
    if (!program){
        LOGE ("Could not create program");
        return false;
    }
    Position = glGetAttribLocation(program, "Position");
    Color = glGetAttribLocation(program, "Color");
    TextureCoord = glGetAttribLocation(program, "TextureCoord");
    projectionLocation = glGetUniformLocation(program, "projection");
    modelViewLocation = glGetUniformLocation(program, "modelView");
    sampler = glGetUniformLocation(program, "Texture");
    vertexNormalLocation = glGetAttribLocation(program, "VertexNormal");

    MatrixPerspective(projectionMatrix, 45, (float)w/(float)h, 0.1f, 1000);
    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, w, h);


    if(texture.id == 0) {
        return false;
    }
    else {
        return true;
    }
    return true;
}

//TODO Test
void renderFrame(){
    glClearColor(0.33f,0.33f,0.33f,1.0f);
    glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    MatrixIdentity(modelViewMatrix);
    MatrixRotateX(modelViewMatrix, angle);
    MatrixRotateY(modelViewMatrix, angle);

    MatrixTranslate(modelViewMatrix, 0.0f, 0.0f, -10.0f);


    glUseProgram(program);

//    unsigned int VBO;
//    glGenBuffers(1,&VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


//    glVertexAttribPointer(Position, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float) ,(void*)0);
//    glEnableVertexAttribArray(Position);
//    glVertexAttribPointer(Color, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));
//    glEnableVertexAttribArray(Color);

    glVertexAttribPointer(Position, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(Position);
    glVertexAttribPointer(Color, 3, GL_FLOAT, GL_FALSE, 0, colour);
    glEnableVertexAttribArray(Color);
    glVertexAttribPointer(TextureCoord, 2, GL_FLOAT, GL_FALSE, 0, textureCoords);
    glEnableVertexAttribArray(TextureCoord);
    glVertexAttribPointer(vertexNormalLocation, 3, GL_FLOAT, GL_FALSE, 0, normals);
    glEnableVertexAttribArray(vertexNormalLocation);

//    glDrawArrays(GL_TRIANGLES, 0, 6);
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, projectionMatrix);
    glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, modelViewMatrix);
    glUniform1f(sampler, 0);
    glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_SHORT, indices);

    angle+=1;
    if(angle>360){
        angle=-360;
    }

//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof (float), (void*)(3*sizeof(float)));

}
