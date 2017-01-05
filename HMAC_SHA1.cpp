//
//  HMAC_SHA1.cpp
//  JHash
//
//  Created by GRC on 2017/1/5.
//  Copyright © 2017年 JimmyTai. All rights reserved.
//

#include "JHash.h"

namespace JHash {
    
    class HMAC_SHA1 HMAC_SHA1;
    
    void HMAC_SHA1::encode(unsigned char *text, int textLen, unsigned char *key, int keyLen, unsigned char *digest){
        
        memset(SHA1_Key, 0, SHA1_BLOCK_SIZE);
        
        /* repeated 64 times for values in ipad and opad */
        memset(m_ipad, 0x36, sizeof(m_ipad));
        memset(m_opad, 0x5c, sizeof(m_opad));
        
        /* STEP 1 */
        if (keyLen > SHA1_BLOCK_SIZE)  //大于64位
        {
            SHA1::encode((uint8_t *)key, keyLen, (uint8_t *)SHA1_Key);
        }
        else
            memcpy(SHA1_Key, key, keyLen);
        
        /* STEP 2 */
        for (int i=0; i<sizeof(m_ipad); i++)
        {
            m_ipad[i] ^= SHA1_Key[i];
        }
        
        /* STEP 3 */
        memcpy(AppendBuf1, m_ipad, sizeof(m_ipad));
        memcpy(AppendBuf1 + sizeof(m_ipad), text, textLen);
        
        /* STEP 4 */
        SHA1::encode((uint8_t *)AppendBuf1, sizeof(m_ipad) + textLen, (uint8_t *)szReport);
        
        /* STEP 5 */
        for (int j=0; j<sizeof(m_opad); j++)
        {
            m_opad[j] ^= SHA1_Key[j];
        }
        
        /* STEP 6 */
        memcpy(AppendBuf2, m_opad, sizeof(m_opad));
        memcpy(AppendBuf2 + sizeof(m_opad), szReport, SHA1_DIGEST_LENGTH);
        
        /*STEP 7 */
        SHA1::encode((uint8_t *)AppendBuf2, sizeof(m_opad) + SHA1_DIGEST_LENGTH, (uint8_t *)digest);
    }
    
}
