//
// Created by haichao.gao on 20-10-27.
//

#ifndef OPENGLESS1_GLRENDER_H
#define OPENGLESS1_GLRENDER_H

#include <android/native_window.h>
#include "../myegl/eglImpl.h"
#include "../example/NativeEpBase.h"
#include "Triangle.h"
#include "VAOTriangle.h"
#include "Cube.h"


class glRender {

public:
    glRender();

    ~glRender();

    void surfaceCreated(ANativeWindow *window);
    void surfaceChanged(int width, int height);
    void surfaceDestroyed(void);
    //void OnDrawFrame(void);

private:
    eglImpl *meglImpl;
    EGLSurface mWindowSurface;
    NativeEpBase *mexample;
};


#endif //OPENGLESS1_GLRENDER_H
