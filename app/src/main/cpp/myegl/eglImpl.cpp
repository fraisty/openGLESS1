//
// Created by haichao.gao on 20-10-23.
//

#include "eglImpl.h"
#include "../common/myLog.h"


eglImpl::eglImpl():mConfig(nullptr), mContext(EGL_NO_CONTEXT),mDisplay(EGL_NO_DISPLAY),
                   eglPresentationTimeANDROID(NULL){
    Initialize(nullptr);
}

eglImpl::eglImpl(EGLContext sharedContext):mConfig(nullptr), mContext(EGL_NO_CONTEXT),
                                            mDisplay(EGL_NO_DISPLAY),
                                           eglPresentationTimeANDROID(NULL){
    Initialize( sharedContext );
}

eglImpl::~eglImpl() {
    release();
}

/**
 * @description： 初始化egl
 * @sharedContext: egl上下文
*/
EGLBoolean eglImpl::Initialize(EGLContext sharedContext) {
    LOGFE("exec: eglImpl::Initialize.");
    EGLConfig config;
    EGLContext context;
    //创建和初始化与本地EGL显示的连接
    EGLDisplay display = eglGetDisplay( EGL_DEFAULT_DISPLAY );
    if ( display == EGL_NO_DISPLAY ){
        LOGFE("eglImpl::Initialize: EGL_NO_DISPLAY!");
        return EGL_FALSE;
    }

    //初始化EGL
    if ( !eglInitialize( display, NULL, NULL ) ){
        LOGFE("eglImpl::Initialize: eglInitialize error!");
        return EGL_FALSE;
    }

    //确定可用表面配置
    {
        EGLint numConfigs = 0;

        EGLint configAttribs[] = {
                EGL_RED_SIZE,       8,
                EGL_GREEN_SIZE,     8,
                EGL_BLUE_SIZE,      8,
                EGL_ALPHA_SIZE,     8,
                EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
                EGL_NONE
        };

        if ( !eglChooseConfig( display,configAttribs, &config, 1,&numConfigs ) ){
            LOGFE("eglImpl: can not find RGB8888! numConfigs:%d ",numConfigs);
            return EGL_FALSE;
        }

    }

    //创建上下文
    {
        EGLint contextAttribs[] = {
                EGL_CONTEXT_CLIENT_VERSION, 3,
                EGL_NONE
        };
        context = eglCreateContext(display, mConfig, sharedContext, contextAttribs);

        if ( context ==  EGL_NO_CONTEXT ) {
            LOGFE("eglImpl::Initialize:eglCreateContext error!");
            return EGL_FALSE;
        }
    }

    mConfig = config;
    mContext = context;
    mDisplay = display;

    return EGL_TRUE;
}


void eglImpl::checkEglError(const char *msg) {
    int error;
    if ((error = eglGetError()) != EGL_SUCCESS) {
        LOGFE("%s: EGL error: %x", msg, error);
    }
}

void eglImpl::release() {
    if (mDisplay != EGL_NO_DISPLAY ){
        eglMakeCurrent( mDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        eglDestroyContext( mDisplay, mContext );
        eglReleaseThread();
        eglTerminate( mDisplay );
    }
    mDisplay = EGL_NO_DISPLAY;
    mContext = EGL_NO_CONTEXT;
    mConfig = nullptr;
}

EGLContext eglImpl::getEGLContext() {
    return mContext;
}

void eglImpl::releaseSurface(EGLSurface eglSurface) {
    eglDestroySurface( mDisplay, eglSurface);
}

/**
 * @description： 释放egl资源
 * @para none
*/
void release(){


}

EGLSurface eglImpl::createWindowSurface(ANativeWindow *surface) {
    if ( surface == nullptr ){
        LOGFE("eglImpl::createWindowSurface error : surface is null");
        return nullptr;
    }
    EGLSurface window = eglCreateWindowSurface( mDisplay, mConfig, surface, nullptr );
    if (window == EGL_NO_SURFACE ){
        switch ( eglGetError() ) {
            case EGL_BAD_MATCH:
                LOGFE("eglImpl::createWindowSurface error:EGL_BAD_MATCH");
                break;
            case EGL_BAD_CONFIG:
                LOGFE("eglImpl::createWindowSurface error:EGL_BAD_CONFIG");
                break;
            case EGL_BAD_NATIVE_WINDOW:
                LOGFE("eglImpl::createWindowSurface error:EGL_BAD_NATIVE_WINDOW");
                break;
            case EGL_BAD_ALLOC:
                LOGFE("eglImpl::createWindowSurface error:ALLOC");
                break;
            default:
                LOGFE("eglImpl::createWindowSurface error!");
                break;
        }
    }
    return window;
}

EGLSurface eglImpl::createOffscreenSurface(int width, int height) {

    EGLint surfaceAtrrib[] = {
            EGL_WIDTH, width,
            EGL_HEIGHT, height,
            EGL_NONE,
    };

    EGLSurface pbuffer = eglCreatePbufferSurface(mDisplay, mConfig, surfaceAtrrib);

    if (pbuffer == nullptr){
        LOGFE("eglImpl::createOffscreenSurface: pbuffer is null");
        return nullptr;
    }
    return pbuffer;
}

void eglImpl::makeCurrent(EGLSurface drawSurface, EGLSurface readSurface) {
    if (mDisplay == EGL_NO_DISPLAY){
        LOGFE("eglImpl::makeCurrent: no display");
    }
    if (!eglMakeCurrent(mDisplay, drawSurface, readSurface, mContext)){
        LOGFE("eglImpl::makeCurrent: error");
    }
}

void eglImpl::makeCurrent(EGLSurface eglSurface) {
    if (mDisplay == EGL_NO_DISPLAY){
        LOGFE("eglImpl::makeCurrent: no display");
    }
    if (!eglMakeCurrent(mDisplay, eglSurface, eglSurface, mContext)){
        LOGFE("eglImpl::makeCurrent: error");
    }
}

void eglImpl::makeNothingCurrent() {
    if (!eglMakeCurrent(mDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, mContext)){
        LOGFE("eglImpl::makeNothingCurrent: error");
    }
}

bool eglImpl::swapBuffers(EGLSurface eglSurface) {
    return eglSwapBuffers(mDisplay, eglSurface);
}

void eglImpl::setPresentationTime(EGLSurface eglSurface, long nsecs) {
    eglPresentationTimeANDROID(mDisplay, eglSurface, nsecs);
}

bool eglImpl::isCurrent(EGLSurface eglSurface) {
    return mContext == eglGetCurrentContext()
    && eglSurface == eglGetCurrentSurface(EGL_DRAW);
}

int eglImpl::querySurface(EGLSurface eglSurface, int what) {
    EGLint value;
    eglQuerySurface(mContext, eglSurface, what, &value);
    return value;
}

const char *eglImpl::queryString(int what) {
    return eglQueryString(mDisplay, what);
}







