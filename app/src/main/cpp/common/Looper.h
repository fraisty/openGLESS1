//
// Created by haichao.gao on 20-10-27.
//

#ifndef OPENGLESS1_LOOPER_H
#define OPENGLESS1_LOOPER_H

#include <pthread.h>
#include <sys/types.h>





struct LooperMessage{
    int what;
    int arg1;
    int arg2;
    void *obj;
    LooperMessage *next;
    bool quit;
};


class Looper {


private:

LooperMessage *head;
pthread_t workthread;

};


#endif //OPENGLESS1_LOOPER_H
