//
// Created by haichao.gao on 20-10-20.
//

#ifndef OPENGLESS1_TRIANGLE_H
#define OPENGLESS1_TRIANGLE_H

#include "NativeEpBase.h"

class Triangle : public NativeEpBase {

public:
    Triangle();

    void Init();

    void Draw(int screenW, int screenH);

    void Destroy();

    virtual ~Triangle();
};


#endif //OPENGLESS1_TRIANGLE_H
