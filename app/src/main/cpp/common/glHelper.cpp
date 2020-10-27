//
// Created by haichao.gao on 20-10-20.
//

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



