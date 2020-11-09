//
// Created by haichao.gao on 20-11-6.
//

#ifndef OPENGLESS1_NATIVEEPBASE_H
#define OPENGLESS1_NATIVEEPBASE_H

#include "../common/glHelper.h"
//#include "Triangle.h"
#include "../common/myLog.h"



class NativeEpBase {
public:
    NativeEpBase():mprogramObject(GL_NONE){}

    virtual void Init() = 0;

    virtual void Draw(int screenW, int screenH) = 0;

    virtual void Destroy() = 0;

    virtual ~NativeEpBase() {  }

protected:
    GLuint mprogramObject;
};







#endif //OPENGLESS1_NATIVEEPBASE_H
