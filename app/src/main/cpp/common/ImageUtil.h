//
// Created by haichao.gao on 20-11-20.
//

#ifndef OPENGLESS1_IMAGEUTIL_H
#define OPENGLESS1_IMAGEUTIL_H

#include <string>
#include "myLog.h"
#include "GLES3/gl3.h"

class ImageUtil {
public:
#pragma pack(push)   //阻止对齐
#pragma pack(1)
    struct GLType{
        GLenum internalFormat = GL_RGBA8;
        GLenum format = GL_RGBA;
        GLenum type = GL_UNSIGNED_BYTE;
    };
    struct ImageData{
        uint16_t width;
        uint16_t height;
        GLType    rgbType;
        uint16_t     bytePerPixel;
        uint8_t *data;
    };
    struct RGB10A2{
        uint16_t R:10;
        uint16_t G:10;
        uint16_t B:10;
        uint16_t A:2;
    };
#pragma pack(pop)
    ImageUtil();
    virtual ~ImageUtil();
    void transRGBA82RGB10A2();
    void getTextureId( GLuint& tId );
protected:
    ImageData mImageData;
    std::string mAppdatapath;
private:

};


#endif //OPENGLESS1_IMAGEUTIL_H
