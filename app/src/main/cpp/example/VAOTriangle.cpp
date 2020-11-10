//
// Created by haichao.gao on 20-11-9.
//

#include "VAOTriangle.h"

#define VERTEX_POS_SIZE     3
#define VERTEX_COLOR_SIZE   4
#define VERTEX_STRIDE       (sizeof(GLfloat)*(VERTEX_POS_SIZE + \
                                VERTEX_COLOR_SIZE))
#define OFFSET_POS_START    (const void*)(sizeof(GLfloat) * VERTEX_POS_SIZE)

void VAOTriangle::Init() {

    LOGFD("VAOTriangle::Init()");
    //顶点着色器
    char vShaderStr[] =
            "#version 300 es\n"
            "layout(location = 0) in vec4 vPosition; \n"
            "layout(location = 1) in vec4 vColor;\n"
            "smooth out vec4 fColor;\n"
            "void main() \n"
            "{ \n"
            "   gl_Position = vPosition;    \n"
            "   fColor = vColor;\n"
            "} \n";
    //片段着色器
    char fShaderStr[] =
            "#version 300 es    \n"
            "precision mediump float;   \n"
            "smooth in vec4 fColor; \n"
            "out vec4 fragColor;    \n"
            "void main()    \n"
            "{  \n"
            "fragColor = fColor; \n"
            "}  \n";

    //顶点属性 结构数组

    GLfloat vertices [] = {
            -0.5f,   0.5f,   0.0f,      //v0
            1.0f, 0.0f, 0.0f, 1.0f,     //c0
            0.5f,  0.5f,  0.0f,         //v1
            0.0f, 1.0f, 0.0f, 1.0f,     //c1
            -0.5f,   -0.5f,  0.0f,      //v2
            0.0f, 0.0f, 1.0f, 1.0f,     //c2
            0.5f,   -0.5f,  0.0f,       //v3
            1.0f, 1.0f,  0.0f, 1.0f,    //c3
    };
    //根据着色器创建程序对象
    mprogramObject = glHelper::CreateProgram(vShaderStr, fShaderStr);

    //产生VBO，并将数据载入VBOs
    glGenBuffers(1, &mVboids);
    glBindBuffer(GL_ARRAY_BUFFER, mVboids);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //产生VAO，载入数据
    glGenVertexArrays(1, &mVaoid);
    glBindVertexArray(mVaoid);
    glBindBuffer(GL_ARRAY_BUFFER, mVboids);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE,
            VERTEX_STRIDE, (const void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE,
            VERTEX_STRIDE, OFFSET_POS_START);

    glBindVertexArray(GL_NONE);
}


void VAOTriangle::Draw(int screenW, int screenH) {
    LOGFE("VAOTriangle::Draw(),W:%d ,H:%d",screenW, screenH);
    if (mprogramObject == GL_NONE){
        LOGFE(" VAOTriangle: mprogramObject is null ");
        return;
    }
    glViewport( 0, 0, screenW, screenH);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear( GL_COLOR_BUFFER_BIT );

    glUseProgram( mprogramObject );

    glBindVertexArray(mVaoid);
    //用first到first+count-1的顶点去绘制图形，故给定4个顶点，画出4边形
    glDrawArrays(GL_TRIANGLE_STRIP,0 ,4);
}


void VAOTriangle::Destroy() {
    if ( mprogramObject ){
        glDeleteProgram( mprogramObject );
        mprogramObject = GL_NONE;
    }
}


