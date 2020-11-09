//
// Created by haichao.gao on 20-11-9.
//

#ifndef OPENGLESS1_VAOTRIANGLE_H
#define OPENGLESS1_VAOTRIANGLE_H

#include "NativeEpBase.h"


class VAOTriangle : public NativeEpBase {

public:
    VAOTriangle();

    void Init();

    void Draw(int screenW, int screenH);

    void Destroy();

    virtual ~VAOTriangle();

};


#endif //OPENGLESS1_VAOTRIANGLE_H
