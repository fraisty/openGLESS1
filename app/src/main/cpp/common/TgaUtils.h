//
// Created by haichao.gao on 20-11-17.
//

#ifndef OPENGLESS1_TGAUTILS_H
#define OPENGLESS1_TGAUTILS_H



#include "ImageUtil.h"

class TgaUtils : public ImageUtil {
public:
#pragma pack(push)   //阻止对齐
#pragma pack(1)
    struct TGAHeader{
        uint8_t idLength = 0;           //图像信息字段长度      1byte
        uint8_t colorMapType = 0;       //颜色表类型           1byte
        uint8_t imageType = 0;          //图像类型             1byte
        uint16_t colorMapFirstAddr = 0; //颜色表首地址          2byte
        uint16_t colorMapLen = 0;       //颜色表长度            2byte
        uint8_t colorMapPMSize = 0;     //颜色表表项大小        1byte
        uint16_t imageXOrigin= 0;      //图像左下角的水平坐标   2byte
        uint16_t imageYOrigin= 0;      //图像左下角的垂直坐标   2byte
        uint16_t igwidth= 0;            //图像宽度             2byte
        uint16_t igheight= 0;           //图像高度             2byte
        uint8_t pixelDepth= 0;          //像素深度             1byte
        uint8_t imagefd= 0;             //图像描述符            1byte
    };
    struct TGAImageInfo{
        uint8_t *imageInfo;           //图像信息字段
        uint8_t *colormapData;        //颜色表数据
        uint8_t *devData;             //开发者区域数据
        uint8_t *extData;             //拓展区域数据
    };
#pragma pack(pop)

    TgaUtils();
    TgaUtils(std::string filename);
    uint8_t* getImageData();
    ~TgaUtils();
    void TgaHeaderDump();
    void CheckHeader();

    void dumpImageData(std::string,int32_t);

private:
    bool readTgaFile(std::string filename);
    bool readTgaImageData(FILE *fd);
    void transImageData2vertic();
    std::unique_ptr<TGAHeader> mImageHeader;
    TGAImageInfo mImageInfo;
    bool mreadCheck;
};


#endif //OPENGLESS1_TGAUTILS_H
