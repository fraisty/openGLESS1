//
// Created by haichao.gao on 20-11-17.
//

#ifndef OPENGLESS1_SIMPLEMAPTEXTURE_H
#define OPENGLESS1_SIMPLEMAPTEXTURE_H

#include "NativeEpBase.h"

class SimpleMapTexture : public NativeEpBase{

public:
    SimpleMapTexture();
    virtual ~SimpleMapTexture();

    virtual void Init();

    virtual void Draw(int screenW, int screenH);

    virtual void Destroy();

private:
    GLuint mTextureId;
    GLint  mSamplerLoc;
};


#endif //OPENGLESS1_SIMPLEMAPTEXTURE_H
