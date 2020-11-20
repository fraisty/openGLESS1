//
// Created by haichao.gao on 20-11-17.
//

#include "TgaUtils.h"


TgaUtils::TgaUtils():mImageHeader(std::make_unique<TGAHeader>()), mreadCheck(false)
{
}

TgaUtils::TgaUtils(std::string filename) : TgaUtils() {
    mreadCheck = readTgaFile(mAppdatapath + filename);
}

bool TgaUtils::readTgaFile(std::string filename) {
    FILE *fd = fopen(filename.c_str(),"rb");
    if( !fd ){
        LOGFE("File open failed.");
        return false;
    }
    //读取文件头
    if (fread(mImageHeader.get(), sizeof(TGAHeader), 1, fd) != 1){
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
    int32_t imageSize = 0;
    //先只支持读取数据，忽略颜色表数据以及图像信息字段
    if ( mImageHeader->idLength || mImageHeader->colorMapType ){
        LOGFE("imageinfo || colormap is not supported");
        return false;
    }
    //ready
    mImageData.width = mImageHeader->igwidth;
    mImageData.height = mImageHeader->igheight;
    mImageData.bytePerPixel = mImageHeader->pixelDepth / 8;
    imageSize = mImageData.bytePerPixel
                * mImageData.width * mImageData.height;
    int32_t imageSizeDQ = (((mImageData.width*mImageHeader->pixelDepth) + 31)>>5)<<2;

    LOGFE("\nmImageData: width is %d;\n heigth is %d;\n"
                    "imageSize is %d;\n bpp is %d;\n DQ is %d.", mImageData.width,

                    mImageData.height ,imageSize,mImageData.bytePerPixel,
                    imageSizeDQ == mImageData.width * mImageData.bytePerPixel ? 1:0 );

    //分配空间
    mImageData.data = (uint8_t*)malloc( imageSize );
    if (mImageData.data == nullptr){
        LOGFE("ImageData malloc failed!");
        return false;
    }
    //跳转文件头
    if ( fseek( fd, sizeof(TGAHeader), SEEK_SET ) == -1 ){
        free(mImageData.data);
        LOGFE("fseek failed!");
        return false;
    }

    if ( fread(mImageData.data, 1, imageSize, fd) != imageSize ){
        LOGFE("fread failed! bit5 is 1, ImageSize is %d.",imageSize);
        free(mImageData.data);
        return false;
    }

    //tga  imagefd bit5-0 屏幕起始位置标志，0-原点在左下角，读取从下到上，1-原点在左上角，读取从上到下
    //1 正常，当为0时读取后翻转
    if ( !(mImageHeader->imagefd & 0x20) ){
         transImageData2vertic();
    }

    //tga is BGR(A), need turn to RGB(A)
    for( auto i = 0; i < static_cast<int>(imageSize); i+=
            static_cast<int>(mImageData.bytePerPixel) ){
        std::swap<uint8_t>(mImageData.data[i],mImageData.data[i+2]);
    }
    if (mImageData.bytePerPixel == 3){
        mImageData.rgbType.internalFormat = GL_RGB8;
        mImageData.rgbType.format = GL_RGB;
    }
    return true;
}

TgaUtils::~TgaUtils() {
    if( !mImageData.data ){
        free(mImageData.data);
    }
}

uint8_t* TgaUtils::getImageData() {
    return mImageData.data; //？
}

void TgaUtils::dumpImageData(std::string fn, int32_t isize) {
    FILE *fd = fopen( (mAppdatapath + fn).c_str(), "wb+" );
    if( !fd ){
        LOGFE("File open to write failed.");
        return;
    }
    fwrite( mImageData.data, isize, 1, fd);
    fclose(fd);
}


void TgaUtils::TgaHeaderDump() {
    LOGFE("TGAHeader size is : %d", static_cast<int>(sizeof((*mImageHeader))));
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

void TgaUtils::transImageData2vertic() {
    uint32_t imagePerLineBytes = mImageData.width * mImageData.bytePerPixel;
    uint8_t*  temp_line = new uint8_t[imagePerLineBytes];
    uint16_t height_half = mImageData.height >> 1;
    for (uint16_t i = 0; i < height_half ;i++ ){
        unsigned long l1 = i*imagePerLineBytes;
        unsigned long l2 = (mImageData.height-1-i)*imagePerLineBytes;
        memmove((void *)temp_line,      (void *)(mImageData.data+l1), imagePerLineBytes);
        memmove((void *)(mImageData.data+l1), (void *)(mImageData.data+l2), imagePerLineBytes);
        memmove((void *)(mImageData.data+l2), (void *)temp_line,      imagePerLineBytes);
    }
    delete [] temp_line;
}


