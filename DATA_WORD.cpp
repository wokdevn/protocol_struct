//
// Created by shun on 2022/12/26.
//

#include <stdexcept>
#include <iostream>
#include "DATA_WORD.h"

//TODO:重构一下,两个payload还有成员变量之间的关系有点乱

DATA_WORD::DATA_WORD() {}

//DATA_WORD::DATA_WORD(unsigned char payload[8]){
DATA_WORD::DATA_WORD(std::array<unsigned char,8> payload){
//    memcpy(this->payload,payload, sizeof(this->payload));
    this->payload = payload;
    setPayloadInBit();
}

//unsigned char * DATA_WORD::getPayLoad(){
std::array<unsigned char, 8> DATA_WORD::getPayload(){
    syncBitPayload();
    return this->payload;
}

//void DATA_WORD::setPayLoad(unsigned char * payloadToSet){
void DATA_WORD::setPayload(std::array<unsigned char, 8> payload){
//    memcpy(this->payload,payloadToSet,sizeof(payload));
    this->payload = payload;
    setPayloadInBit();
}

//unsigned char * DATA_WORD::getPayloadInBit(){
std::array<unsigned char, 64> DATA_WORD::getPayloadInBit(){
    return this->payloadInBit;
}

void DATA_WORD::setPayloadInBit(){
    int itPayBit = 0;
    for(int i = 0; i<(PAYLOAD_LEN_BIT/8); ++i){
        unsigned char itPay = payload[i];
        for(int j = 0; j<sizeof(char);j++){
            unsigned char inter = itPay & 0x01;
            payloadInBit[itPayBit] = inter;
            itPay = itPay >> 1;
        }
    }
}

void DATA_WORD::syncBitPayload(){
    for(int i = 0; i<8;++i){
        unsigned char inter = 0;
        for(int j = 0; j<8;++j){
            inter = inter << 1;
            inter = inter +(this->payloadInBit[i*8+j]);
        }
        this->payload[i] = inter;
    }
}

void DATA_WORD::setPayloadInBit(std::array<unsigned char, 64> payload){
    //64转到一个8byte中赋值给payload变量,然后调用setPayloadInBit()
    for(int i = 0; i<(PAYLOAD_LEN_BIT/8);++i){
        unsigned char inter = 0;

        for(int j = 0; j<sizeof(char); ++j){
            inter = inter << 1;
            inter = inter+(payload[i*8 + j]&1);
        }

        this->payload[i] = inter;
    }

    setPayloadInBit();
}

unsigned char * DATA_WORD::getPayloadBitData(int begin, int end){
    try {
        if( (begin - end < 0) || begin > 63 || end < 0){
            throw std::invalid_argument(R"(location wrong, "begin" is supposed to be larger than "end" AND both in range from 63 to 0,  63:48 for instance)");
        }
        if(begin - end >= 7 ){//满一个byte，例如63:56
            int diff = begin - end +1;
            int ans = diff / 8;
            int remain = diff - ans;
            int len = ans;
            if(remain){
                len ++;
            }

            unsigned char * inter = new unsigned char[len];

            //TODO:拷贝,头尾操作,类似于<8bit的情况

//            if(end+len*8 <= 64){
//                memcpy(inter, reinterpret_cast<const void *>(payload[8 - (end+len*8) / 8]), sizeof(char)*len);
//                *inter = *inter & (2^(begin-end+1)-1);
//                return inter;
//            }

        }
        if(begin - end < 7){//不够一个字节

            //这里还有两种特殊情况，如果不够一个字节且在两端，直接复制有可能溢出，如果是右端（x-0）这种和一般情况是一样的处理
            //主要考虑左端
            if(end>56){
                unsigned char * inter = new unsigned char;
                memcpy(inter, reinterpret_cast<const void *>(payload[7 - 56 / 8]), sizeof(char));
                *inter = *inter >> (end - 56);
                return inter;
            }
            if(end <= 56){//这里有问题,没考虑跨两个字节的复制,跨两个字节得复制两次,两头作运算
                if((begin/8) == (end / 8)){
                    unsigned char * inter = new unsigned char;
                    memcpy(inter, reinterpret_cast<const void *>(payload[7 - end / 8]), sizeof(char));
                    *inter = *inter & (2^(begin-end+1)-1);
                    return inter;
                }
                if((begin/8) > (end / 8)){
                    unsigned char * inter = new unsigned char[2];
                    memcpy(inter, reinterpret_cast<const void *>(payload[7 - begin / 8]), sizeof(char));
                    memcpy(reinterpret_cast<void *>(inter[1]), reinterpret_cast<const void *>(payload[7 - end / 8]), sizeof(char));

                    *inter = *inter & (2^((begin-(begin/8)*8)+1)-1);
                    //TODO:移位操作也有点东西要做,移位到一个byte之中去
                }
            }
        }
    }catch (std::invalid_argument &ia){
        std::cerr << "invalid argument: " << ia.what() << std::endl;
    }
}

void DATA_WORD::setPayloadBitData(unsigned char * toSet, int begin, int end){

}