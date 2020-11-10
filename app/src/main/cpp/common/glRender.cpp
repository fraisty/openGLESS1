//
// Created by haichao.gao on 20-10-27.
//

#include "glRender.h"
#include "myLog.h"


enum NATIVE_EXAMPLE NOW_EXAMPLE = ENUM_EXAMPLE_CUBE;

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
    switch ( NOW_EXAMPLE ) {
        case ENUM_EXAMPLE_VAOTRIANGLE:
            mexample = new VAOTriangle();
            break;
        case ENUM_EXAMPLE_CUBE: {
            int width = ANativeWindow_getWidth(window);
            int high = ANativeWindow_getHeight(window);
            mexample = new Cube(width, high);
        }
            break;
        case ENUM_EXAMPLE_CUBEBYINSTANCE:
        default:
            mexample = new Triangle();
            break;
    }
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




