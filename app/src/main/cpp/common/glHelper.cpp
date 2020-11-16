//
// Created by haichao.gao on 20-10-20.
//

#include <cstring>
#include "glHelper.h"
#include "myLog.h"
#include "stdio.h"
#include "stdlib.h"


/**
 * description: 编译和加载着色器
 *
 * type: 着色器类型，分为顶点着色器：GL_VERTEX_SHADER
 *       片段着色器：GL_FRAGMENT_SHADER
 * shaderSrc:着色器源代码
*/
GLuint glHelper::LoadShader(GLenum type, const char *shaderSrc) {
    GLuint shader;
    GLint compiledStatus;

    //创建指定类型的新着色器对象
    shader = glCreateShader( type );
    if ( shader == 0 ) {
        LOGFE("glCreateShader is null!");
        return 0;
    }
    //将着色器源代码加载到着色器对象
    glShaderSource(shader, 1, &shaderSrc, NULL);
    //编译
    glCompileShader(shader);

    //编译完成后进行检查
    glGetShaderiv( shader, GL_COMPILE_STATUS, &compiledStatus);
    if ( !compiledStatus ){
        GLint infoLen = 0;

        glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &infoLen );

        if ( infoLen > 1 ){
            char *infoLog = (char*)malloc ( sizeof(char) * infoLen );
            glGetShaderInfoLog( shader, infoLen, NULL, infoLog);
            LOGFE("glHelper LoadShader compile shader error: \n%s\n", infoLog);
            if ( infoLog ) {free( infoLog );}
        }
        LOGFE("glHelper LoadShader error, type is: %x \n", type);
        glDeleteShader( shader );
        return  0;
    }
    return shader;
}

/**
 * description: 创建程序对象链接着色器
 *
 * vertexShaderSrc: 顶点着色器源代码
 * fragmentShaderSrc: 片段着色器源代码
*/
GLuint glHelper::CreateProgram( const char *vertexShaderSrc, const char *fragmentShaderSrc ) {
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linkStatus;

    vertexShader = LoadShader( GL_VERTEX_SHADER, vertexShaderSrc );
    if ( !vertexShader ) return 0;
    fragmentShader = LoadShader( GL_FRAGMENT_SHADER, fragmentShaderSrc );
    if ( !fragmentShader ) {
        glDeleteShader( vertexShader );
        return 0;
    }

    //创建程序对象并连接
    programObject = glCreateProgram();
    if( !programObject ){
        LOGFE("glCreateProgram error! programObject is null!\n");
    }

    glAttachShader( programObject, vertexShader );
    glAttachShader( programObject, fragmentShader);

    //链接程序对象
    glLinkProgram( programObject );

    //检查链接错误
    glGetProgramiv( programObject, GL_LINK_STATUS, &linkStatus );
    if ( !linkStatus ){
        GLint infoLen = 0;
        glGetProgramiv( programObject, GL_INFO_LOG_LENGTH, &infoLen );
        if ( infoLen > 1 ){
            char *infoLog = (char*)malloc (sizeof(char) * infoLen );
            glGetProgramInfoLog( programObject, infoLen, NULL, infoLog);
            LOGFE("glCreateProgram error! link program error:\n%s\n",infoLog);
            if( infoLog ) { free(infoLog); }
        }

        glDeleteProgram( programObject );
        return  0;
    }

    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );

    return programObject;
}

/* @Description: 产生一个对角线矩阵
 * @param  GLMATRIX
 * @return
*/
void glHelper::SetIdentityMatrix(GLMatrix *mat) {
    memset( mat, 0x0, sizeof(GLMatrix) );
    mat->m[0][0] = 1.0f;
    mat->m[1][1] = 1.0f;
    mat->m[2][2] = 1.0f;
    mat->m[3][3] = 1.0f;
}


/* @Description:  简单缩放整体
 * @param
 * @return
*/
void glHelper::SampleScaling(GLMatrix *mat, GLfloat factor) {
    mat->m[0][0] *= factor;
    mat->m[1][1] *= factor;
    mat->m[2][2] *= factor;
}

/* @Description:  简单旋转
 * @param
 * @return
*/
void glHelper::SampleRotaeByZ(GLMatrix *mat, GLfloat angle) {
    GLfloat sintheta = sinf( angle * PI / 180.0f );
    GLfloat costheta = cosf( angle * PI / 180.0f );
    mat->m[0][0] *= costheta;
    mat->m[0][1] *= -sintheta;
    mat->m[1][0] *= sintheta;
    mat->m[1][1] *= costheta;
}

void glHelper::SampleRotaeByX(GLMatrix *mat, GLfloat angle) {
    GLfloat sintheta = sinf( angle * PI / 180.0f );
    GLfloat costheta = cosf( angle * PI / 180.0f );
    mat->m[1][1] *= costheta;
    mat->m[1][2] *= -sintheta;
    mat->m[2][1] *= sintheta;
    mat->m[2][2] *= costheta;
}

void glHelper::SampleRotaeByY(GLMatrix *mat, GLfloat angle) {
    GLfloat sintheta = sinf( angle * PI / 180.0f );
    GLfloat costheta = cosf( angle * PI / 180.0f );
    mat->m[0][0] *= costheta;
    mat->m[0][2] *= sintheta;
    mat->m[2][0] *= -sintheta;
    mat->m[2][2] *= costheta;
}

void glHelper::Rotate(GLMatrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
    GLfloat sinAngle, cosAngle;
    GLfloat mag = sqrtf ( x * x + y * y + z * z );

    sinAngle = sinf ( angle * PI / 180.0f );
    cosAngle = cosf ( angle * PI / 180.0f );

    if ( mag > 0.0f )
    {
        GLfloat xx, yy, zz, xy, yz, zx, xs, ys, zs;
        GLfloat oneMinusCos;
        GLMatrix rotMat;

        x /= mag;
        y /= mag;
        z /= mag;

        xx = x * x;
        yy = y * y;
        zz = z * z;
        xy = x * y;
        yz = y * z;
        zx = z * x;
        xs = x * sinAngle;
        ys = y * sinAngle;
        zs = z * sinAngle;
        oneMinusCos = 1.0f - cosAngle;

        rotMat.m[0][0] = ( oneMinusCos * xx ) + cosAngle;
        rotMat.m[0][1] = ( oneMinusCos * xy ) - zs;
        rotMat.m[0][2] = ( oneMinusCos * zx ) + ys;
        rotMat.m[0][3] = 0.0F;

        rotMat.m[1][0] = ( oneMinusCos * xy ) + zs;
        rotMat.m[1][1] = ( oneMinusCos * yy ) + cosAngle;
        rotMat.m[1][2] = ( oneMinusCos * yz ) - xs;
        rotMat.m[1][3] = 0.0F;

        rotMat.m[2][0] = ( oneMinusCos * zx ) - ys;
        rotMat.m[2][1] = ( oneMinusCos * yz ) + xs;
        rotMat.m[2][2] = ( oneMinusCos * zz ) + cosAngle;
        rotMat.m[2][3] = 0.0F;

        rotMat.m[3][0] = 0.0F;
        rotMat.m[3][1] = 0.0F;
        rotMat.m[3][2] = 0.0F;
        rotMat.m[3][3] = 1.0F;

        MultiplyMatrix( result, &rotMat, result );
    }
}

/* @Description: 矩阵乘法
 * @param
 * @return
*/
void glHelper::MultiplyMatrix(GLMatrix *res, GLMatrix *sA, GLMatrix *sB) {
    GLMatrix tmp;
    memset(&tmp, 0x0, sizeof(GLMatrix));
    for( int i = 0; i < 4; i++){
        for( int j = 0; j < 4; j++){
            GLfloat sum = 0;
            for(int k = 0; k < 4; k++){
                sum += sA->m[i][k] * sB->m[k][j];
            }
            tmp.m[i][j] = sum;
        }
    }
    memcpy(res, &tmp, sizeof(GLMatrix));
}

/* @Description: es透视矩阵
 * @param
 * @return
*/
void glHelper::Frustum(GLMatrix *result, float left, float right, float bottom,
        float top, float nearZ, float farZ) {

    float       deltaX = right - left;
    float       deltaY = top - bottom;
    float       deltaZ = farZ - nearZ;
    GLMatrix    frust;

    if ( ( nearZ <= 0.0f ) || ( farZ <= 0.0f ) ||
         ( deltaX <= 0.0f ) || ( deltaY <= 0.0f ) || ( deltaZ <= 0.0f ) )
    {
        LOGFE("glHelper::Frustum data is wrong!");
        return;
    }

    frust.m[0][0] = 2.0f * nearZ / deltaX;
    frust.m[0][1] = frust.m[0][2] = frust.m[0][3] = 0.0f;

    frust.m[1][1] = 2.0f * nearZ / deltaY;
    frust.m[1][0] = frust.m[1][2] = frust.m[1][3] = 0.0f;

    frust.m[2][0] = ( right + left ) / deltaX;
    frust.m[2][1] = ( top + bottom ) / deltaY;
    frust.m[2][2] = - ( nearZ + farZ ) / deltaZ;
    frust.m[2][3] = -1.0f;

    frust.m[3][2] = -2.0f * nearZ * farZ / deltaZ;
    frust.m[3][0] = frust.m[3][1] = frust.m[3][3] = 0.0f;

    MultiplyMatrix ( result, &frust, result );
}

/* @Description:  es透视矩阵
 * @param
 * @return
*/
void glHelper::Perspective(GLMatrix *res, float fovy, float aspect, float nearZ, float farZ) {
    GLfloat frustumW, frustumH;

    frustumH = tanf ( fovy / 360.0f * PI ) * nearZ;
    frustumW = frustumH * aspect;

    Frustum ( res, -frustumW, frustumW, -frustumH, frustumH, nearZ, farZ );
}
/* @Description: 模型矩阵
 * @param
 * @return
*/
void glHelper::Translate(GLMatrix *result, GLfloat tx, GLfloat ty, GLfloat tz) {
    result->m[3][0] += ( result->m[0][0] * tx + result->m[1][0] * ty + result->m[2][0] * tz );
    result->m[3][1] += ( result->m[0][1] * tx + result->m[1][1] * ty + result->m[2][1] * tz );
    result->m[3][2] += ( result->m[0][2] * tx + result->m[1][2] * ty + result->m[2][2] * tz );
    result->m[3][3] += ( result->m[0][3] * tx + result->m[1][3] * ty + result->m[2][3] * tz );
}

GLMatrix glHelper::Perspective(float fovy, float aspect, float nearZ, float farZ) {

    GLMatrix result;
    memset(&result, 0x0, sizeof(GLMatrix));

    float const tanFovy = tan(fovy / static_cast<float>(2));

    result.m[0][0] = static_cast<float>(1) / (aspect * tanFovy);
    result.m[1][1] = static_cast<float>(1) / (tanFovy);
    result.m[2][2] = - (farZ + nearZ) / (farZ - nearZ);
    result.m[2][3] = - static_cast<float>(1);
    result.m[3][2] = - (static_cast<float>(2) * farZ * nearZ) / (farZ - nearZ);
    return result;
}


