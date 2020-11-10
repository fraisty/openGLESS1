//
// Created by haichao.gao on 20-11-9.
//

#ifndef OPENGLESS1_VAOTRIANGLE_H
#define OPENGLESS1_VAOTRIANGLE_H

#include "NativeEpBase.h"


class VAOTriangle : public NativeEpBase {

public:
    VAOTriangle() = default;

    void Init();

    void Draw(int screenW, int screenH);

    void Destroy();

    virtual ~VAOTriangle()= default;

private:
    GLuint mVboids = 0;
    GLuint mVaoid = 0;
};


#endif //OPENGLESS1_VAOTRIANGLE_H
