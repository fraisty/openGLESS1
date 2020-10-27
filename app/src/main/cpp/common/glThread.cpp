//
// Created by haichao.gao on 20-10-27.
//

#include "glThread.h"
#include "myLog.h"
#include <unistd.h>

glThread::glThread():isChange(false), isCreate(false), isExit(false)
                    , isStart(false), window(nullptr) {

}

glThread::~glThread() {

}

void* glthreadloop(void* context){
    glThread *glThread = static_cast<class glThread *>(context);
    glThread->isExit = false;

    while (true){
        if ( glThread->isExit ){
            LOGFD("glTread is exit.");
            if (!glThread->mRender){
                glThread->mRender->surfaceDestroyed();
            }
            break;
        }
        //16ms
        usleep(16000);
        //OnCreate
        if (glThread->isCreate){
            glThread->isCreate = false;
            LOGFD("glThread onCreate.");
            if (glThread->mRender){
                glThread->mRender->surfaceCreated(glThread->window);
            }
        }
        //OnChange
        if (glThread->isChange){
            glThread->isChange = false;
            glThread->isStart = true;
            LOGFD("glThread onChange.");
            if (glThread->mRender){
                glThread->mRender->surfaceChanged(glThread->width,glThread->height);
            }
        }
        //OnDraw
        if (glThread->isStart){
            LOGFD("glThread OnDraw:width is %d,height is %d",glThread->width,glThread->height);
            if (glThread->mRender){
                glThread->mRender->surfaceChanged(glThread->width,glThread->height);
            }
        }
    }
    LOGFD("glThread is run.");
    return nullptr;
}

void glThread::onSurfaceCreate(ANativeWindow *window) {
    this->window = window;
    this->isCreate = true;
    pthread_create(&mThreadImpl, nullptr, glthreadloop, this);
}

void glThread::onSurfaceChange(int w, int h) {
    this->width = w;
    this->height = h;
    this->isChange = true;
}

void glThread::onSurfaceDestroy() {
    this->isStart = false;
    this->isExit = true;
}


void glThread::setglRender(glRender *render) {
    this->mRender = render;
}

void glThread::release() {
    void* return_value;
    pthread_join(mThreadImpl, &return_value);
    LOGFD("glThread release %p",return_value);
    window = nullptr;
}

