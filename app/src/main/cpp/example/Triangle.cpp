//
// Created by haichao.gao on 20-10-20.
//

/*
 * 简单三角形，采用VBO改进，采用数组结构，将顶点属性颜色和坐标分开
 * */




#include "Triangle.h"


Triangle::Triangle()
{

}

Triangle::~Triangle() {

}


void Triangle::Init() {
    LOGFD("Triangle::Init()");
    //顶点着色器
    char vShaderStr[] =
            //声明使用的着色器版本3.0
            "#version 300 es\n"
            //声明一个输入属性 4分量向量数组，layout(location = 0)表明变量的位置是顶点属性0
            "layout(location = 0) in vec4 vPosition; \n"
            "layout(location = 1) in vec4 vColor;\n"
            "smooth out vec4 fColor;\n"
            "void main() \n"
            "{ \n"
            //每个顶点着色器必须在gl_Position变量中输出一个位置
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
//            "   fragColor = vec4 ( 0.0, 1.0, 1.0, 1.0 );    \n"
                "fragColor = fColor;"
            "}  \n";

    mprogramObject = glHelper::CreateProgram(vShaderStr, fShaderStr);
}

void Triangle::Draw( int screenWidth, int screenHeight ) {
    LOGFE("Triangle::Draw(),W:%d ,H:%d",screenWidth, screenHeight);
    GLuint vboids[] = {0, 0};  //用来保存申请的缓冲区对象返回的位置
    //指定几何形状，三角形的三个顶点坐标(x,y,z)
    GLfloat vVertices [] = {
            -0.5f,   0.5f,   0.0f,
            0.5f,  0.5f,  0.0f,
            -0.5f,   -0.5f,  0.0f,
            0.5f,   -0.5f,  0.0f,
    };
    GLfloat inColor[] = {
            1.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 1.0f,  0.0f, 1.0f,
    };

    //设置视口，opengles用于绘制的2d渲染表面的原点、宽度、高度
    glViewport( 0, 0, screenWidth, screenHeight);

    //用glClearColor指定的颜色清除缓冲区，此时为白色
    glClearColor(1.0, 1.0, 1.0, 1.0);
    //清除屏幕，每个帧的开始，清除颜色缓冲区
    glClear( GL_COLOR_BUFFER_BIT );

    //使用程序对象
    glUseProgram( mprogramObject );

    //使用顶点缓冲区对象
    if ( vboids[0] == 0 &&  vboids[1] == 0 ){
        glGenBuffers(2,vboids);
        glBindBuffer( GL_ARRAY_BUFFER,vboids[0] );
        glBufferData( GL_ARRAY_BUFFER, sizeof(vVertices), vVertices, GL_STATIC_DRAW);

        glBindBuffer( GL_ARRAY_BUFFER, vboids[1] );
        glBufferData( GL_ARRAY_BUFFER, sizeof(inColor), inColor, GL_STATIC_DRAW );
    }

    glBindBuffer( GL_ARRAY_BUFFER,vboids[0] );   //表示启用id0表示的buffer
    glEnableVertexAttribArray(0);
    glVertexAttribPointer( 0, 3, GL_FLOAT,GL_FALSE, 0, 0 );

    glBindBuffer( GL_ARRAY_BUFFER, vboids[1] );
    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, 0, 0 );

    glDrawArrays(  GL_TRIANGLE_STRIP , 0 ,4 );

}


void Triangle::Destroy() {
    if ( mprogramObject ){
        glDeleteProgram( mprogramObject );
        mprogramObject = GL_NONE;
    }
}



