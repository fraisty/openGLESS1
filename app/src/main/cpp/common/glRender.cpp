//
// Created by haichao.gao on 20-10-27.
//

#include "glRender.h"
#include "myLog.h"




glRender::glRender() {
    meglImpl = new eglImpl(NULL);
    mWindowSurface = EGL_NO_SURFACE;
}

glRender::~glRender() {
    if (meglImpl){
        meglImpl->release();
        meglImpl = nullptr;
    }
}

void glRender::surfaceCreated(ANativeWindow *window) {

    mWindowSurface = meglImpl->createWindowSurface(window);
    meglImpl->makeCurrent(mWindowSurface);
    mexample = new Triangle();
    mexample->Init();
}

void glRender::surfaceChanged(int width, int height) {
    meglImpl->makeCurrent(mWindowSurface);
    mexample->Draw(width, height);
    meglImpl->swapBuffers(mWindowSurface);
}

//void glRender::OnDrawFrame(void) {
//    meglImpl->makeCurrent(mWindowSurface);
//    mTriangle->Draw(width, height);
//    meglImpl->swapBuffers(mWindowSurface);
//}

void glRender::surfaceDestroyed(void) {
    if (mexample){
        mexample->Destroy();
        delete mexample;
        mexample = nullptr;
    }
    if (mWindowSurface){
        mWindowSurface = EGL_NO_SURFACE;
    }
    if (meglImpl){
        meglImpl->release();
        delete meglImpl;
        meglImpl = nullptr;
    }
}




