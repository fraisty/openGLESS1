//
// Created by haichao.gao on 20-10-23.
//

#ifndef OPENGLESS1_EGLIMPL_H
#define OPENGLESS1_EGLIMPL_H


#include <EGL/egl.h>
//#include <EGL/eglplatform.h>
#include <EGL/eglext.h>


class eglImpl {

public:
    eglImpl();
    eglImpl(EGLContext sharedContext);
    ~eglImpl();

    EGLBoolean Initialize(EGLContext sharedContext);
    void release();
    EGLContext getEGLContext();
    void releaseSurface(EGLSurface eglSurface);
    EGLSurface createWindowSurface(ANativeWindow *surface);
    EGLSurface createOffscreenSurface(int width, int height);
    void makeCurrent(EGLSurface eglSurface);
    void makeCurrent(EGLSurface drawSurface, EGLSurface readSurface);
    void makeNothingCurrent();
    bool swapBuffers(EGLSurface eglSurface);
    void setPresentationTime(EGLSurface eglSurface, long nsecs);
    bool isCurrent(EGLSurface eglSurface);
    int querySurface(EGLSurface eglSurface, int what);
    const char *queryString(int what);
    void checkEglError(const char *msg);

private:
    EGLDisplay mDisplay;
    EGLConfig mConfig;
    EGLContext mContext;
    PFNEGLPRESENTATIONTIMEANDROIDPROC  eglPresentationTimeANDROID;

};


#endif //OPENGLESS1_EGLIMPL_H
