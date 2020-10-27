//
// Created by haichao.gao on 20-10-27.
//

#ifndef OPENGLESS1_GLRENDER_H
#define OPENGLESS1_GLRENDER_H

#include <android/native_window.h>
#include "../myegl/eglImpl.h"
#include "../example/Triangle.h"

//#include <EGL/egl.h>

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
    Triangle *mTriangle;
};


#endif //OPENGLESS1_GLRENDER_H
