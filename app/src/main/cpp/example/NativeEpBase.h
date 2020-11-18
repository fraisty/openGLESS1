//
// Created by haichao.gao on 20-11-6.
//

#ifndef OPENGLESS1_NATIVEEPBASE_H
#define OPENGLESS1_NATIVEEPBASE_H

#include "../common/glHelper.h"
//#include "Triangle.h"
#include "../common/myLog.h"

enum NATIVE_EXAMPLE {
    ENUM_EXAMPLE_TRIANGLE,
    ENUM_EXAMPLE_VAOTRIANGLE,
    ENUM_EXAMPLE_CUBE,
    ENUM_EXAMPLE_CUBEBYINSTANCE,
    ENUM_EXAMPLE_SIMPLETEXTURE,
    ENUM_EXAMPLE_MIPMAP2D,
    ENUM_EXAMPLE_SIMPLEMAPTEXTURE,

    ENUM_EXAMPLE_NUM
};

class NativeEpBase {
public:
    NativeEpBase():mprogramObject(GL_NONE),mTextureId(GL_NONE){}

    virtual void Init() = 0;

    virtual void Draw(int screenW, int screenH) = 0;

    virtual void Destroy() {
        if ( mprogramObject ){
            glDeleteProgram( mprogramObject );
            mprogramObject = GL_NONE;
        }};

    virtual ~NativeEpBase() {  }

protected:
    GLuint mprogramObject;
    GLuint mTextureId;
};







#endif //OPENGLESS1_NATIVEEPBASE_H
