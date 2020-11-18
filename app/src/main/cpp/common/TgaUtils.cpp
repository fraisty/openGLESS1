//
// Created by haichao.gao on 20-11-17.
//

#include "TgaUtils.h"
#include "myLog.h"

TgaUtils::TgaUtils(): mImageHeader(nullptr), mreadCheck(false){
}

TgaUtils::TgaUtils(string filename) : TgaUtils() {
    mImageHeader = new TGAHeader;
    mreadCheck = readTgaFile(filename);
}

bool TgaUtils::readTgaFile(string filename) {
    FILE *fd = fopen(filename.c_str(),"rb");
    if( !fd ){
        LOGFE("File open failed.");
        return false;
    }
    //读取文件头
    if (fread(mImageHeader, sizeof(TGAHeader), 1, fd) != 1){
        LOGFE("File read failed.");
    }
    TgaHeaderDump();
    //CheckHeader();
    //读取图像数据
    if ( !readTgaImageData(fd) ){
        LOGFE("readTgaImageData is failed");
        fclose(fd);
        return false;
    }
    fclose(fd);
    return true;
}

bool TgaUtils::readTgaImageData(FILE *fd) {
    uint32_t imageSize = 0;
    //先只支持读取数据，忽略颜色表数据以及图像信息字段
    if ( mImageHeader->idLength || mImageHeader->colorMapType ){
        LOGFE("imageinfo || colormap is not null");
        return false;
    }
    //ready
    mImageData.width = mImageHeader->igwidth;
    mImageData.height = mImageHeader->igheight;
    mImageData.bytePerPixel = mImageHeader->pixelDepth / 8;
    imageSize = mImageData.bytePerPixel
                * mImageData.width * mImageData.height;
    LOGFD("\nmImageData: width is %d;\n heigth is %d;\n"
                    "imageSize is %d; bpp is %d.", mImageData.width,
                    mImageData.height ,imageSize,mImageData.bytePerPixel);
    //分配空间
    mImageData.data = (uint8_t*)malloc( imageSize );
    if (mImageData.data == nullptr){
        LOGFE("ImageData malloc failed!");
        return false;
    }
    //跳转文件头
    if ( fseek( fd, sizeof(TGAHeader), 0 ) == -1 ){
        free(mImageData.data);
        LOGFE("fseek failed!");
        return false;
    }
    if ( fread(mImageData.data, 1, imageSize, fd) != imageSize){
        LOGFE("fread failed! ImageSize is %d.",imageSize);
        free(mImageData.data);
        return false;
    }
    //tga is BGR(A), need turn to RGB(A)
    for( int i = 0; i < static_cast<int>(imageSize); i+=
            static_cast<int>(mImageData.bytePerPixel) ){
        std::swap<uint8_t>(mImageData.data[i],mImageData.data[i+2]);
    }
    return true;
}

TgaUtils::~TgaUtils() {
    delete mImageHeader;
    if( !mImageData.data ){
        free(mImageData.data);
    }
}


uint8_t* TgaUtils::getImageData() {
    return mImageData.data; //？
}

void TgaUtils::getTextureId(GLuint& tId) {
    GLuint type = GL_RGB;
    if ( mImageData.bytePerPixel == 4 ) type = GL_RGBA;
    glGenTextures(1, &tId);
    glBindTexture(GL_TEXTURE_2D, tId);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered
    glTexImage2D(GL_TEXTURE_2D, 0, type, mImageData.width,
            mImageData.height, 0, type, GL_UNSIGNED_BYTE, mImageData.data);
}

void TgaUtils::TgaHeaderDump() {
    LOGFE("TGAHeader size is : %d",sizeof(*mImageHeader));
    LOGFE("idLength : %d",mImageHeader->idLength);
    LOGFE("colorMapType : %d",mImageHeader->colorMapType);
    LOGFE("imageType : %d",mImageHeader->imageType);
    LOGFE("colorMapFirstAddr : %d",mImageHeader->colorMapFirstAddr);
    LOGFE("colorMapLen : %d",mImageHeader->colorMapLen);
    LOGFE("colorMapPMSize : %d",mImageHeader->colorMapPMSize);
    LOGFE("imageXOrigin : %d",mImageHeader->imageXOrigin);
    LOGFE("imageYOrigin : %d",mImageHeader->imageYOrigin);
    LOGFE("igwidth : %d",mImageHeader->igwidth);
    LOGFE("igheight : %d",mImageHeader->igheight);
    LOGFE("pixelDepth : %d",mImageHeader->pixelDepth);
    LOGFE("imagefd : 0x%x ",mImageHeader->imagefd);
}

void TgaUtils::CheckHeader() {

}


