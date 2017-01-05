//
//  Base64.cpp
//  JHash
//
//  Created by GRC on 2017/1/5.
//  Copyright © 2017年 JimmyTai. All rights reserved.
//

#include "JHash.h"

namespace JHash {
    
    class Base64 Base64;
    
    String Base64::encode(const unsigned char *data, int len){
    /* --- 編碼表 --- */
    const char encodeTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    /* --- 返回值 --- */
    String strEncode;
        unsigned char tmp[4]={0};
        int lineLengh=0;
        for(int i=0;i<(int)(len / 3);i++)
        {
            tmp[1] = *data++;
            tmp[2] = *data++;
            tmp[3] = *data++;
            strEncode+= encodeTable[tmp[1] >> 2];
            strEncode+= encodeTable[((tmp[1] << 4) | (tmp[2] >> 4)) & 0x3F];
            strEncode+= encodeTable[((tmp[2] << 2) | (tmp[3] >> 6)) & 0x3F];
            strEncode+= encodeTable[tmp[3] & 0x3F];
            if(lineLengh+=4,lineLengh==76) {strEncode+="\r\n";lineLengh=0;}
        }
        /* --- 對剩餘數據進行編碼 --- */
        int mod=len % 3;
        if(mod==1)
        {
            tmp[1] = *data++;
            strEncode+= encodeTable[(tmp[1] & 0xFC) >> 2];
            strEncode+= encodeTable[((tmp[1] & 0x03) << 4)];
            strEncode+= "==";
        }
        else if(mod==2)
        {
            tmp[1] = *data++;
            tmp[2] = *data++;
            strEncode+= encodeTable[(tmp[1] & 0xFC) >> 2];
            strEncode+= encodeTable[((tmp[1] & 0x03) << 4) | ((tmp[2] & 0xF0) >> 4)];
            strEncode+= encodeTable[((tmp[2] & 0x0F) << 2)];
            strEncode+= "=";
        }
        return strEncode;
    }
    
    String Base64::decode(const char *data, int len, int outLen){
        /* --- 解碼表 --- */
        const char decodeTable[] =
        {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            /* --- '+' --- */
            0, 0,
            /* --- '/' --- */
            53, 54, 55, 56, 57, 58, 59, 60, 61,
            /* --- '0'-'9' --- */
            0, 0, 0, 0, 0, 0,
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
            14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
            /* --- 'A'-'Z' --- */
            0, 0, 0, 0, 0,
            27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
            40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51
            /* --- 'a'-'z' --- */
        };
        String strDecode;
        int nValue;
        int i= 0;
        while (i < len)
        {
            if (*data != '\r' && *data!='\n')
            {
                nValue = decodeTable[*data++] << 18;
                nValue += decodeTable[*data++] << 12;
                strDecode+=(nValue & 0x00FF0000) >> 16;
                outLen++;
                if (*data != '=')
                {
                    nValue += decodeTable[*data++] << 6;
                    strDecode+=(nValue & 0x0000FF00) >> 8;
                    outLen++;
                    if (*data != '=')
                    {
                        nValue += decodeTable[*data++];
                        strDecode+=nValue & 0x000000FF;
                        outLen++;
                    }
                }
                i += 4;
            }
            else
            {
                data++;
                i++;
            }
        }
        return strDecode;
    }
}
