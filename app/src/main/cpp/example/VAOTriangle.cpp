//
// Created by haichao.gao on 20-11-9.
//

#include "VAOTriangle.h"

VAOTriangle::VAOTriangle() {

}


VAOTriangle::~VAOTriangle() {

}

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
            "fragColor = fColor;"
            "}  \n";

    mprogramObject = glHelper::CreateProgram(vShaderStr, fShaderStr);


}


void VAOTriangle::Draw(int screenW, int screenH) {

}


void VAOTriangle::Destroy() {

}


