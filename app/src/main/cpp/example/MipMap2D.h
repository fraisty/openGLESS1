//
// Created by haichao.gao on 20-11-16.
//

#ifndef OPENGLESS1_MIPMAP2D_H
#define OPENGLESS1_MIPMAP2D_H

#include "NativeEpBase.h"

class MipMap2D : NativeEpBase {

public:
    MipMap2D();

    void Init() ;

    void Draw(int screenW, int screenH) ;

    void Destroy() ;

    virtual  ~MipMap2D();

private:




};


#endif //OPENGLESS1_MIPMAP2D_H
