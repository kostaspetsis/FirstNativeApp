//
// Created by kostas on 7/10/2019.
//

#ifndef FIRSTNATIVEAPP_MATRIX_H
#define FIRSTNATIVEAPP_MATRIX_H

#include <math.h>

void MatrixIdentity(float *matrix);
void MatrixTranslate(float *matrix, float x, float y, float z);
void MatrixMultiply(float *matrixDst, float *matrix1, float *matrix2);
void MatrixScale(float *matrix, float x, float y, float z);
void MatrixRotateX(float *matrix, float angle);
void MatrixRotateY(float *matrix, float angle);
void MatrixRotateZ(float *matrix, float angle);
void MatrixPerspective(float *matrix, float fov, float aspectRatio, float zNear, float zFar);
void MatrixFrustum(float *matrix, float left, float right, float bottom, float top, float zNear, float zFar);

#endif //FIRSTNATIVEAPP_MATRIX_H
