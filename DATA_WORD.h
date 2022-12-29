//
// Created by shun on 2022/12/26.
//

#ifndef LINKCONTROL_DATA_WORD_H
#define LINKCONTROL_DATA_WORD_H


#include <cstring>
#include <array>

#define PAYLOAD_LEN_BIT 64

class DATA_WORD {
protected:
    std::array<unsigned char,8> payload;
    std::array<unsigned char,64> payloadInBit;

public:
    DATA_WORD();
//    DATA_WORD(unsigned char payload[8]);
    DATA_WORD(std::array<unsigned char,8>);

//    unsigned char * getPayLoad();
    std::array<unsigned char, 8> getPayload();

    void setPayLoad(unsigned char * payloadToSet);

    unsigned char * getPayloadInBit();

    void setPayloadInBit();
    void setPayloadInBit(unsigned char * payloadInBitToSet);

    //下面两个函数的begin和end之间的数据是连续的,并且是按bit来定的位置
    //下面两个函数写一半,换了种实现方案,没有写完
    unsigned char * getPayloadBitData(int begin, int end);

    void setPayloadBitData(unsigned char * toSet, int begin, int end);
};


#endif //LINKCONTROL_DATA_WORD_H
