//
// Created by kostas on 7/10/2019.
//
#include "Matrix.h"
#include <assert.h>
#include "Maths.h"

void MatrixIdentity(float *matrix){
    assert (matrix!= nullptr);
//    matrix[0]=1.0f;
//    matrix[1]=0.0f;
//    matrix[2]=0.0f;
//    matrix[3]=0.0f;
//    matrix[4]=0.0f;
//    matrix[5]=1.0f;
//    matrix[6]=0.0f;
//    matrix[7]=0.0f;
//    matrix[8]=0.0f;
//    matrix[9]=0.0f;
//    matrix[10]=1.0f;
//    matrix[11]=0.0f;
//    matrix[12]=0.0f;
//    matrix[13]=0.0f;
//    matrix[14]=0.0f;
//    matrix[15]=1.0f;

    matrix[0]=1.0f; matrix[4]=0.0f; matrix[8]=0.0f; matrix[12]=0.0f;
    matrix[1]=0.0f; matrix[5]=1.0f; matrix[9]=0.0f; matrix[13]=0.0f;
    matrix[2]=0.0f; matrix[6]=0.0f; matrix[10]=1.0f;matrix[14]=0.0f;
    matrix[3]=0.0f; matrix[7]=0.0f; matrix[11]=0.0f;matrix[15]=1.0f;
}

void MatrixTranslate(float *matrix, float x, float y, float z){
    float tempMatrix[16];
    MatrixIdentity(tempMatrix);
    tempMatrix[12]=x;
    tempMatrix[13]=y;
    tempMatrix[14]=z;
    MatrixMultiply(matrix, tempMatrix, matrix);
}

void MatrixMultiply(float *matrixDst, float *matrix1, float *matrix2){
    float tempMatrix[16];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            tempMatrix[i*4+j] =  matrix1[j] * matrix2[4 * i] + matrix1[4 + j] * matrix2[4 * i + 1] +
                    matrix1[8 + j] * matrix2[4 * i + 2] + matrix1[12 + j] * matrix2[4 * i + 3];
        }
    }
    for (int i = 0; i < 16; ++i) {
        matrixDst[i] = tempMatrix[i];
    }
}

void MatrixScale(float *matrix, float x, float y, float z){
    float tempMatrix[16];
    MatrixIdentity(tempMatrix);
    tempMatrix[0]=x;
    tempMatrix[5]=y;
    tempMatrix[10]=z;
    MatrixMultiply(matrix, tempMatrix, matrix);
}

void MatrixRotateX(float *matrix, float angle){
    float tempMatrix[16];
    MatrixIdentity(tempMatrix);

    tempMatrix[5] = cos(DegreesToRadians(angle));
    tempMatrix[6] = sin(DegreesToRadians(angle));
    tempMatrix[9] = -sin(DegreesToRadians(angle));
    tempMatrix[10] = cos(DegreesToRadians(angle));
    MatrixMultiply(matrix, tempMatrix, matrix);
}

void MatrixRotateY(float *matrix, float angle){
    float tempMatrix[16];
    MatrixIdentity(tempMatrix);

    tempMatrix[0] = cos(DegreesToRadians(angle));
    tempMatrix[2] = -sin(DegreesToRadians(angle));
    tempMatrix[8] = sin(DegreesToRadians(angle));
    tempMatrix[10] = cos(DegreesToRadians(angle));
    MatrixMultiply(matrix, tempMatrix, matrix);
}

void MatrixRotateZ(float *matrix, float angle){
    float tempMatrix[16];
    MatrixIdentity(tempMatrix);

    tempMatrix[0] = cos(DegreesToRadians(angle));
    tempMatrix[1] = sin(DegreesToRadians(angle));
    tempMatrix[4] = -sin(DegreesToRadians(angle));
    tempMatrix[5] = cos(DegreesToRadians(angle));
    MatrixMultiply(matrix, tempMatrix, matrix);
}

void MatrixPerspective(float *matrix, float fov, float aspectRatio, float zNear, float zFar){
    float yMax, xMax;
    yMax = zNear * tanf(fov*PI/360.0f);
    xMax = yMax * aspectRatio;
    MatrixFrustum(matrix, -xMax, xMax, -yMax, yMax, zNear, zFar);
}

void MatrixFrustum(float *matrix, float left, float right, float bottom, float top, float zNear, float zFar){
    float temp, xDistance, yDistance, zDistance;
    temp = 2.0 * zNear;
    xDistance = right - left;
    yDistance = top - bottom;
    zDistance = zFar - zNear;
    MatrixIdentity(matrix);
    matrix[0] = temp / xDistance;
    matrix[5] = temp / yDistance;
    matrix[8] = (right + left) / xDistance;
    matrix[9] = (top + bottom) / yDistance;
    matrix[10] = (-zFar - zNear) / zDistance;
    matrix[11] = -1.0f;
    matrix[14] = (-temp * zFar) / zDistance;
    matrix[15] = 0.0f;
}