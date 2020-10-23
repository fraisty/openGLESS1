//
// Created by haichao.gao on 20-10-20.
//

#ifndef OPENGLESS1_TRIANGLE_H
#define OPENGLESS1_TRIANGLE_H

#include "../common/glHelper.h"

class Triangle {

public:
    Triangle();

    void Init();

    void Draw(int screenW, int screenH);

    void Destroy();

    virtual ~Triangle();

private:
    GLuint mprogramObject;
};


#endif //OPENGLESS1_TRIANGLE_H
