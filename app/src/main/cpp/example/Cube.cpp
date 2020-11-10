//
// Created by haichao.gao on 20-11-9.
//

#include "Cube.h"

#define VERTEX_POS_SIZE     3
#define VERTEX_COLOR_SIZE   4
#define VERTEX_STRIDE       (sizeof(GLfloat)*(VERTEX_POS_SIZE + \
                                VERTEX_COLOR_SIZE))
#define OFFSET_POS_START    (const void*)(sizeof(GLfloat) * VERTEX_POS_SIZE)

Cube::Cube(int width, int height): mWidth(width), mHeight(height) {
    LOGFD("Cube constructor: width is %d, height is %d.",mWidth , mHeight);
    if ( mHeight != 0 ){
        mAspect = (GLfloat)width / (GLfloat)height;
        LOGFD("Cube constructor: mAspect is %f.",mAspect);
    }else{
        LOGFD("Cube constructor: heigth is null");
    }
    glHelper::SetIdentityMatrix(&mMvpMat);
}

void Cube::Init() {
    LOGFD("Cube::Init() ");
    //顶点着色器
    char vShaderStr[] =
            "#version 300 es\n"
            "uniform mat4 MvpMatrix;\n"
            "layout(location = 0) in vec4 vPosition; \n"
            "layout(location = 1) in vec4 vColor;\n"
            "smooth centroid out vec4 fColor;\n"
            "void main() \n"
            "{ \n"
            "   gl_Position = MvpMatrix * vPosition;    \n"
            "   fColor = vColor;\n"
            "} \n";
    //片段着色器
    char fShaderStr[] =
            "#version 300 es    \n"
            "precision mediump float;   \n"
            "smooth centroid in vec4 fColor; \n"
            "out vec4 fragColor;    \n"
            "void main()    \n"
            "{  \n"
            "fragColor = fColor; \n"
            "}  \n";
    GLfloat vertices [] = {
            //v0,c0 + + +
            mRadius,mRadius,mRadius,1.0f,1.0f,0.0f,1.0f,
            //1，   - + +
            -mRadius,mRadius,mRadius,1.0f,1.0f,0.0f,1.0f,
            //2,    - - +
            -mRadius,-mRadius,mRadius,1.0f,1.0f,0.0f,1.0f,
            //3,    + - +
            mRadius,-mRadius,mRadius,1.0f,1.0f,0.0f,1.0f,
            //4,    + - -
            mRadius,-mRadius,-mRadius,0.0f,1.0f,0.0f,1.0f,
            //5,    + + -
            mRadius,mRadius,-mRadius,0.0f,1.0f,0.0f,1.0f,
            //6,    - + -
            -mRadius,mRadius,-mRadius,0.0f,1.0f,0.0f,1.0f,
            //7,    - - -
            -mRadius,-mRadius,-mRadius,0.0f,1.0f,0.0f,1.0f,
    };
    GLushort indices[] = {
            0, 1, 2, 0, 2, 3,   //front
            5, 6, 7, 5, 7, 4,   //back
            6, 1, 2, 6, 2, 7,   //left
            5, 0, 3, 5, 3, 4,   //right
            5, 6, 7, 5, 7, 4,   //top
            4, 7, 2, 4, 2, 3,   //bottom
    };
    mIndiceCount = sizeof(indices)/sizeof(GLushort);
    LOGFD("Cube::mIndiceCount is %d",mIndiceCount);
    //创建程序对象
    mprogramObject = glHelper::CreateProgram(vShaderStr, fShaderStr);
    mMvploc = glGetUniformLocation(mprogramObject, "MvpMatrix");
    //产生VBO，存入顶点数据，索引数据
    glGenBuffers(2, mVboId);
    glBindBuffer(GL_ARRAY_BUFFER, mVboId[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVboId[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //产生VAO，载入数据
    glGenVertexArrays(1, &mVaoId);
    glBindVertexArray(mVaoId);
    glBindBuffer(GL_ARRAY_BUFFER, mVboId[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVboId[1]);

    //设置顶点属性
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE,
                          VERTEX_STRIDE, (const void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE,
                          VERTEX_STRIDE, OFFSET_POS_START);

    //设置默认的vao
    glBindVertexArray(GL_NONE);

    //生成一个默认的透视矩阵
    glHelper::SetIdentityMatrix(&mPerspective);
    glHelper::Perspective(&mPerspective, 90.0f, mAspect,1.0f ,30.0f);
    //生成一个默认的变换矩阵
    glHelper::SetIdentityMatrix(&mModelView);
    glHelper::Translate (&mModelView, 0.0f, 0.0f, -2.0f );
    glHelper::Rotate(&mModelView, 45, 0.0f, 1.0f, 0.0f);
    //glHelper::Rotate(&mModelView, 15, 1.0f, 0.0f, 0.0f);
    //生成默认的mvp矩阵
    glHelper::MultiplyMatrix(&mMvpMat, &mModelView, &mPerspective);
}

void Cube::Draw(int screenW, int screenH) {
    LOGFD("Cube::Draw(),W:%d ,H:%d",screenW, screenH);
    if (mprogramObject == GL_NONE){
        LOGFE(" Cube: mprogramObject is null ");
        return;
    }
    glViewport( 0, 0, screenW, screenH);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);//
    glEnable(GL_DEPTH_TEST);

    glUseProgram( mprogramObject );

    glBindVertexArray(mVaoId);

    glUniformMatrix4fv(mMvploc, 1, GL_FALSE, (GLfloat*)&mMvpMat.m[0][0]);

    glDrawElements(GL_TRIANGLES, mIndiceCount, GL_UNSIGNED_SHORT, (const void* )0);
}


void Cube::Destroy() {
    if ( mprogramObject ){
        glDeleteProgram( mprogramObject );
        mprogramObject = GL_NONE;
    }
}


