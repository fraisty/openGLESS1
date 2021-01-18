//
// Created by haichao.gao on 20-11-16.
//

#ifndef OPENGLESS1_SIMPLETEXTURE_H
#define OPENGLESS1_SIMPLETEXTURE_H

#include "NativeEpBase.h"

class SimpleTexture : public NativeEpBase {

public:
    SimpleTexture();
    virtual ~SimpleTexture();

    virtual void Init();

    virtual void Draw(int screenW, int screenH);

    virtual void Destroy();


private:
    GLuint mTextureId;
    GLint  mSamplerLoc;
    GLuint mVaoid;
    GLuint mVboids[2] = {0};
};


#endif //OPENGLESS1_SIMPLETEXTURE_H
