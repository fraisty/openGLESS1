//
// Created by haichao.gao on 20-11-20.
//

#include "ImageUtil.h"

ImageUtil::ImageUtil(): mAppdatapath("/data/data/com.fraisty.opengless1/"){

}

ImageUtil::~ImageUtil() {

}

void ImageUtil::transRGBA82RGB10A2() {
    if ( !mImageData.data ){
        LOGFE("Trans8 2 10 failed，data is null");
        return;
    }
    if ( mImageData.bytePerPixel != 4){
        LOGFE("Trans 8210 failed, only support RGB32!");
        return;
    }
    uint32_t isize = mImageData.height * mImageData.width * mImageData.bytePerPixel;
    RGB10A2 tempRGB = {0};
    for(auto i = 0; i < isize; i += 4){
        tempRGB.R = mImageData.data[i] << 2;
        tempRGB.G = mImageData.data[i+1] << 2;
        tempRGB.B = mImageData.data[i+2] << 2;
        tempRGB.A = mImageData.data[i+3] >> 6;
        memcpy(&mImageData.data[i],&tempRGB,sizeof(RGB10A2));
    }
    LOGFD("Trans complete!");
    mImageData.rgbType.internalFormat = GL_RGB10_A2;
    mImageData.rgbType.format = GL_RGBA;
    mImageData.rgbType.type = GL_UNSIGNED_INT_2_10_10_10_REV;
}

void ImageUtil::getTextureId(GLuint& tId) {
    glGenTextures(1, &tId);
    glBindTexture(GL_TEXTURE_2D, tId);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered

    //避免在环绕方式设置为了GL_REPEAT时OpenGL会对边缘的值和纹理下一个重复的值进行插值
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, mImageData.rgbType.internalFormat, mImageData.width,
                 mImageData.height, 0, mImageData.rgbType.format,
                 mImageData.rgbType.type, mImageData.data);
}












