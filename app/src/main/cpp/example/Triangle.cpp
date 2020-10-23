//
// Created by haichao.gao on 20-10-20.
//

#include "Triangle.h"
#include "../common/myLog.h"


Triangle::Triangle() : mprogramObject(GL_NONE)
{

}

Triangle::~Triangle() {

}

void Triangle::Init() {
    LOGFE("Triangle::Init()");
    //顶点着色器
    char vShaderStr[] =
            //声明使用的着色器版本3.0
            "#version 300 es \n"
            //声明一个输入属性4分量向量数组，layout(location = 0)表明变量的位置是顶点属性0
            "layout(location = 0) in vec4 vPosition; \n"
            "void main() \n"
            "{ \n"
            //每个顶点着色器必须在gl_Position变量中输出一个位置
            "   gl_Position = vPosition;    \n"
            "} \n";
    //片段着色器
    char fShaderStr[] =
            "#verison 300 es    \n"

            "precision mediump float;   \n"
            "out vec4 fragColor;    \n"
            "void main()    \n"
            "{  \n"
            "   fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );    \n"
            "}  \n";

    mprogramObject = glHelper::CreateProgram(vShaderStr, fShaderStr);
}

void Triangle::Draw( int screenWidth, int screenHeight ) {
    LOGFE("Triangle::Draw(),W:%d ,H:%d",screenWidth, screenHeight);
    //指定几何形状，三角形的三个顶点坐标(x,y,z)
    GLfloat vVertices [] = {
            0.0f,   0.5f,   0.0f,
            -0.5f,  -0.5f,  0.0f,
            0.5f,   -0.5f,  0.0f
    };

    //设置视口，opengles用于绘制的2d渲染表面的原点、宽度、高度
    glViewport( 0, 0, screenWidth, screenHeight);

    //用glClearColor指定的颜色清除缓冲区，此时为白色
    glClearColor(1.0, 1.0, 1.0, 1.0);
    //清除屏幕，每个帧的开始，清除颜色缓冲区
    glClear( GL_COLOR_BUFFER_BIT );

    //使用程序对象
    glUseProgram( mprogramObject );

    //加载几何形状
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
    glEnableVertexAttribArray( 0 );

    //通知绘制图元
    glDrawArrays( GL_TRIANGLES, 0 ,3 );
}


void Triangle::Destroy() {
    if ( mprogramObject ){
        glDeleteProgram( mprogramObject );
        mprogramObject = GL_NONE;
    }
}
