//
//  JHash.h
//  JHash
//
//  Created by JimmyTai on 2017/1/5.
//  Copyright © 2017年 JimmyTai. All rights reserved.
//

#ifndef JHash_h
#define JHash_h

#include <string.h>
#include "WString.h"

#if !defined(SHA1_LITTLE_ENDIAN) && !defined(SHA1_BIG_ENDIAN)
#define SHA1_LITTLE_ENDIAN
#endif

#if !defined(SHA1_WIPE_VARIABLES) && !defined(SHA1_NO_WIPE_VARIABLES)
#define SHA1_WIPE_VARIABLES
#endif

//#ifndef uint32_t
//
//#define uint8_t unsigned char
//#if (ULONG_MAX == 0xFFFFFFFF)
//#define uint32_t unsigned long
//#else
//#define uint32_t unsigned int
//#endif
//
//#endif

namespace JHash {
    
    typedef union{
        uint8_t c[64];
        uint32_t l[16];
    } SHA1_WORKSPACE_BLOCK;
    
    class SHA1{
        
    public:
        /* --- Cunstructor and Destructor --- */
        SHA1();
        ~SHA1();
        
        void encode(uint8_t* data, uint32_t len, uint8_t* outBuf);
        
    private:
        
        uint32_t m_state[5];
        uint32_t m_count[2];
        uint32_t __reserved1[1];
        uint8_t  m_buffer[64];
        uint8_t  m_digest[20];
        uint32_t __reserved2[3];
        
        void reset();
        
        void update(uint8_t* data, uint32_t len);
        
        void finalize();
        
        void getHash(uint8_t* outBuf);
        
        /* --- Private SHA-1 transformation --- */
        void transform(uint32_t* state, uint8_t* buufer);
        
        /* --- Member variables --- */
        uint8_t m_workspace[64];
        /* --- SHA1 pointer to the byte array above --- */
        SHA1_WORKSPACE_BLOCK *m_block;
    };
    
    extern SHA1 SHA1;
    
    class HMAC_SHA1 : public SHA1{
        
    public:
        
        enum{
            SHA1_DIGEST_LENGTH = 20,
            SHA1_BLOCK_SIZE = 64,
            HMAC_BUF_LEN = 4096
        };
        
        HMAC_SHA1():
        szReport(new char[HMAC_BUF_LEN]),
        AppendBuf1(new char[HMAC_BUF_LEN]),
        AppendBuf2(new char[HMAC_BUF_LEN]),
        SHA1_Key(new char[HMAC_BUF_LEN])
        {}
        
        ~HMAC_SHA1(){
            delete[] szReport ;
            delete[] AppendBuf1 ;
            delete[] AppendBuf2 ;
            delete[] SHA1_Key ;
        }
        
        void encode(unsigned char* text, int textLen, unsigned char* key, int keyLen, unsigned char* digest);
        
    private:
        
        unsigned char m_ipad[64];
        unsigned char m_opad[64];
        
        char * szReport ;
        char * SHA1_Key ;
        char * AppendBuf1 ;
        char * AppendBuf2 ;
    };
    
    extern HMAC_SHA1 HMAC_SHA1;
    
    class Base64{
    
    public:
        
        String encode(const unsigned char* data, int len);
        
        String decode(const char* data, int len, int outLen);
        
    };
    
    extern Base64 Base64;
}

#endif /* JHash_h */
