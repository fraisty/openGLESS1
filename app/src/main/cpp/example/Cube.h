//
// Created by haichao.gao on 20-11-9.
//

#ifndef OPENGLESS1_CUBE_H
#define OPENGLESS1_CUBE_H
#include "NativeEpBase.h"

class Cube : public NativeEpBase {

public:
    //Cube() = default;
    Cube(int width, int height);
    virtual ~Cube() = default;

    void Init();

    void Draw(int screenW, int screenH);

    void Destroy();

private:

    GLuint mVaoId = 0;
    GLuint mVboId[2] = {0};
    GLfloat mRadius = 0.5f;

    GLMatrix mMvpMat;
    GLMatrix mPerspective;
    GLMatrix mModelView;
    GLint mMvploc = 0;

    int mWidth = 0;
    int mHeight = 0;
    GLfloat mAspect = 0.0f;

    GLint mIndiceCount = 0;
};


#endif //OPENGLESS1_CUBE_H
