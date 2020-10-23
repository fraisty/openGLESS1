//
// Created by haichao.gao on 20-10-23.
//

#include "eglImpl.h"
#include "../common/myLog.h"

EGLBoolean eglImpl::Initialize(EGLContext sharedContext) {

    EGLDisplay display = eglGetDisplay( EGL_DEFAULT_DISPLAY );
    if ( display == EGL_NO_DISPLAY ){
        LOGFE("eglImpl::Initialize: EGL_NO_DISPLAY!");
        return EGL_FALSE;
    }

    if ( !eglInitialize( display, NULL, NULL ) ){
        LOGFE("eglImpl::Initialize: eglInitialize error!");
        return EGL_FALSE;
    }

    {


    }







    return EGL_FALSE;
}
