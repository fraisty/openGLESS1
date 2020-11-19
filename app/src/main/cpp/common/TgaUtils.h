//
// Created by haichao.gao on 20-11-17.
//

#ifndef OPENGLESS1_TGAUTILS_H
#define OPENGLESS1_TGAUTILS_H

#include <string>
#include "GLES3/gl3.h"

using namespace std;


class TgaUtils {
public:
#pragma pack(push)   //阻止对齐
#pragma pack(1)
    struct TGAImageData{
        uint16_t width;
        uint16_t height;
        //uint16_t     rgbType;
        uint16_t     bytePerPixel;
        uint8_t *data;
    };
    struct TGAHeader{
        uint8_t idLength;           //图像信息字段长度      1byte
        uint8_t colorMapType;       //颜色表类型           1byte
        uint8_t imageType;          //图像类型             1byte
        uint16_t colorMapFirstAddr; //颜色表首地址          2byte
        uint16_t colorMapLen;       //颜色表长度            2byte
        uint8_t colorMapPMSize;     //颜色表表项大小        1byte
        uint16_t imageXOrigin;      //图像左下角的水平坐标   2byte
        uint16_t imageYOrigin;      //图像左下角的垂直坐标   2byte
        uint16_t igwidth;            //图像宽度             2byte
        uint16_t igheight;           //图像高度             2byte
        uint8_t pixelDepth;          //像素深度             1byte
        uint8_t imagefd;             //图像描述符            1byte
    };
    struct TGAImageInfo{
        uint8_t *imageInfo;           //图像信息字段
        uint8_t *colormapData;        //颜色表数据
        uint8_t *devData;             //开发者区域数据
        uint8_t *extData;             //拓展区域数据
    };
#pragma pack(pop)

    TgaUtils();
    TgaUtils(string filename);
    uint8_t* getImageData();
    ~TgaUtils();
    void TgaHeaderDump();
    void CheckHeader();
    void getTextureId( GLuint& tId );
    void dumpImageData(string,int32_t);
private:
    bool readTgaFile(string filename);
    bool readTgaImageData(FILE *fd);
    void transImageData2vertic();
    TGAHeader *mImageHeader;
    TGAImageData mImageData;
    TGAImageInfo mImageInfo;
    bool mreadCheck;
    string appdatapath;
};


#endif //OPENGLESS1_TGAUTILS_H
