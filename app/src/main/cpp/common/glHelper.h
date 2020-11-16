//
// Created by haichao.gao on 20-10-20.
//

#ifndef OPENGLESS1_GLHELPER_H
#define OPENGLESS1_GLHELPER_H

#include <GLES3/gl3.h>

#define PI 3.1415926535897932384626433832795f

struct __MATRIX{
    GLfloat m[4][4];
};
typedef struct __MATRIX GLMatrix;




class glHelper {
private:
    static GLuint LoadShader(GLenum type, const char *shaderSrc);

public:
    static GLuint CreateProgram(const char *, const char *);
    static void   SetIdentityMatrix( GLMatrix *mat );
    static void   SampleScaling(GLMatrix *mat, GLfloat factor);
    static void   SampleRotaeByX(GLMatrix *mat, GLfloat angle );
    static void   SampleRotaeByY(GLMatrix *mat, GLfloat angle );
    static void   SampleRotaeByZ(GLMatrix *mat, GLfloat angle );
    static void   MultiplyMatrix(GLMatrix *res, GLMatrix *sA, GLMatrix *sB);
    static void   Perspective( GLMatrix *res, float fovy, float aspect, float nearZ, float farZ );
    static void   Frustum ( GLMatrix *result, float left, float right, float bottom,
            float top, float nearZ, float farZ );
    static void   Translate( GLMatrix *result, GLfloat tx, GLfloat ty, GLfloat tz );
    static void   Rotate( GLMatrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z );
    static GLMatrix Perspective( float fovy, float  aspect, float nearZ, float farZ);
};


#endif //OPENGLESS1_GLHELPER_H
