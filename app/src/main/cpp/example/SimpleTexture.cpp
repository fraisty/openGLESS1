//
// Created by haichao.gao on 20-11-16.
//

#include "SimpleTexture.h"


SimpleTexture::SimpleTexture() {

}

SimpleTexture::~SimpleTexture() {

}

void SimpleTexture::Init() {
    LOGFD("SimpleTexture::Init()");
    //顶点着色器
    char vShaderStr[] =
            "#version 300 es\n"
            "layout(location = 0) in vec4 iPosition; \n"
            "layout(location = 1) in vec2 iTexCoord;\n"
            "out vec2 oTexCoord;\n"
            "void main() \n"
            "{ \n"
            "   gl_Position = iPosition;    \n"
            "   oTexCoord = iTexCoord;\n"
            "} \n";
    //片段着色器
    char fShaderStr[] =
            "#version 300 es    \n"
            "precision mediump float;   \n"
            "in vec2 oTexCoord; \n"
            "layout(location = 0) out vec4 outColor;    \n"
            "uniform sampler2D s_Texture;    \n"
            "void main()    \n"
            "{  \n"
            "   outColor = texture( s_Texture, oTexCoord);   \n"
            "}  \n";

    mprogramObject = glHelper::CreateProgram(vShaderStr, fShaderStr);
    //生成简单纹理2×2
    mTextureId = glHelper::CreateSimpleTexture2D();
    //获取纹理采样器的location
    mSamplerLoc = glGetUniformLocation( mprogramObject, "s_Texture");
}

void SimpleTexture::Draw(int screenW, int screenH) {
    //顶点 纹理  3+2
    GLfloat vVertices[] = {
            -0.5f,  0.5f,  0.0f,  0.0f,  0.0f, //左上角
            -0.5f,  -0.5f,  0.0f,  0.0f,  1.0f,  //左下角
             0.5f,  -0.5f,  0.0f,  1.0f,  1.0f,  //右下角
             0.5f,  0.5f,  0.0f,  1.0f,  0.0f, //右上角
    };
    GLushort indices[] = {
            0,  1,  2,
            0,  2,  3,
    };

    glViewport( 0, 0, screenW, screenH);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear( GL_COLOR_BUFFER_BIT );
    glUseProgram( mprogramObject );

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), vVertices);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), &vVertices[3]);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    //bind the texture
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, mTextureId );
    //设置纹理采样器读取0
    glUniform1i( mSamplerLoc, 0 );

    glDrawElements( GL_TRIANGLES, sizeof(indices)/sizeof(GLushort), GL_UNSIGNED_SHORT, indices );
}


void SimpleTexture::Destroy() {
    glDeleteTextures( 1, &mTextureId );
    NativeEpBase::Destroy();
}


