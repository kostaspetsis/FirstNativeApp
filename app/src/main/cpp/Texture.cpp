//
// Created by kostas on 9/10/2019.
//
#include "Texture.h"
#include <GLES2/gl2.h>
#include <GLES/gl.h>
#include <GLES2/gl2ext.h>
Texture::Texture(){

    GLubyte pixels[9*4]={
            18,  140, 171, 255, /* Some Colour Bottom Left. */
            143, 143, 143, 255, /* Some Colour Bottom Middle. */
            255, 255, 255, 255, /* Some Colour Bottom Right. */
            255, 255, 0,   255, /* Yellow Middle Left. */
            0,   255, 255, 255, /* Some Colour Middle. */
            255, 0,   255, 255, /* Some Colour Middle Right. */
            255, 0,   0,   255, /* Red Top Left. */
            0,   255, 0,   255, /* Green Top Middle. */
            0,   0,   255, 255, /* Blue Top Right. */
    };
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 3, 3, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
