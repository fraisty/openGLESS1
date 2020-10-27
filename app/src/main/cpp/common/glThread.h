//
// Created by haichao.gao on 20-10-27.
//

#ifndef OPENGLESS1_GLTHREAD_H
#define OPENGLESS1_GLTHREAD_H

#include <pthread.h>
#include <android/native_window.h>
#include "glRender.h"


class glThread {

public:
    glThread();
    ~glThread();

    void onSurfaceCreate(ANativeWindow *window);
    void onSurfaceChange(int w, int h);
    void onSurfaceDestroy();
    void release();
    void setglRender(glRender *render);

public:
    pthread_t mThreadImpl;
    bool isExit;
    bool isCreate;
    bool isChange;
    bool isStart;
    ANativeWindow  *window;
    int width;
    int height;
    glRender *mRender;
private:
    //阻止编译器自动生成
    glThread(const glThread&);
    void operator=(const glThread&);
};


#endif //OPENGLESS1_GLTHREAD_H
