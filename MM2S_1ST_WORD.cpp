//
// Created by shun on 2022/12/26.
//


#include "MM2S_1ST_WORD.h"

MM2S_1ST_WORD::MM2S_1ST_WORD(std::array<unsigned char,8> payload):DATA_WORD(payload){
    this->payload = payload;
    checkPayload();
}

bool MM2S_1ST_WORD::checkHead(){
    try {
        std::array<unsigned char,4> head= getHead();
//        int res = strcmp(reinterpret_cast<const char *>(head), "1234");
//上面这里错了，数据应该不是字符串的形式
        int flag = 1;

        for(int i = 0; i < HEAD_LEN; ++i){
            if(head[i] != (i+1)){
                flag = 0;
                break;
            }
        }

        if(!flag){
            throw std::invalid_argument("head is not 1234");
        }
    } catch (std::invalid_argument &ia){
        std::cerr << "head check failed" << ia.what() << std::endl;
    }
}

bool MM2S_1ST_WORD::checkModu(){
    try {
        unsigned char modu = getModulation();

        int flag = 1;

        if(modu > 3){
            flag = 0;
        }

        if(!flag){
            throw std::invalid_argument("modu is not in the range from 0 to 3");
        }
    } catch (std::invalid_argument &ia){
        std::cerr << "modulation check failed" << ia.what() << std::endl;
    }
}

bool MM2S_1ST_WORD::checkEncoderMb(){
    try {
        unsigned int encoderMb = getEncoderMb();

        int flag = 1;

        if(encoderMb > ENCODER_MB_MAX || encoderMb < ENCODER_MB_MIN){
            flag = 0;
        }

        if(!flag){
            throw std::invalid_argument("encoder mb is not in the range from 7 to 46");
        }
    } catch (std::invalid_argument &ia){
        std::cerr << "encoder Mb check failed" << ia.what() << std::endl;
    }
}

bool MM2S_1ST_WORD::checkPayload() {
    checkHead();
    checkModu();
    checkEncoderMb();
}

std::array<unsigned char,4> MM2S_1ST_WORD::getHead(){
//    memcpy(head,payload,sizeof(head));
    std::copy(std::begin(this->payload),std::begin(this->payload)+head.size(),head.begin());
    return head;
}

void MM2S_1ST_WORD::setHead(std::array<unsigned char, 4> headToSet){
//    memcpy(payload,headToSet,HEAD_LEN);
    std::copy(std::begin(headToSet),std::end(headToSet),std::begin(head));
    checkHead();
}

unsigned char MM2S_1ST_WORD::getModulation(){
    char inter;
//    memcpy(&inter, reinterpret_cast<const void *>(payload[4]), sizeof(inter));
    inter = payload[4];
    this->modulation = (inter & 12) >> 2; //00001100,取出来27:26
    return modulation;
}

void MM2S_1ST_WORD::setModulation(char modulation) {
    char inter;
//    memcpy(&inter, reinterpret_cast<const void *>(payload[4]), sizeof(inter));
    inter = payload[4];

    inter = updateBits<char>(inter, modulation, 2,3);

//    memcpy(reinterpret_cast<void *>(payload[4]), &inter, sizeof(inter));
    payload[4] = inter;

    checkModu();
}

unsigned int MM2S_1ST_WORD::getEncoderMb(){
    unsigned int inter;//之后直接用的int赋值给encoderMb
//    memcpy(&inter, reinterpret_cast<const void *>(payload[4]), sizeof(char));
    inter = payload[4];

    inter = inter & 3;//提取出来25:24
    inter = inter << 4;

    unsigned int secondHalfInte;
//    memcpy(&secondHalfInte, reinterpret_cast<const void *>(payload[5]), sizeof(char));
    secondHalfInte = payload[5];

    secondHalfInte = secondHalfInte >> 4;
    secondHalfInte = secondHalfInte & 15;

    inter = inter | secondHalfInte;

    this->encoderMb = inter;

    return this->encoderMb;
}


void MM2S_1ST_WORD::setEncoderMb(unsigned int encoderMb){
    unsigned int inter;//这里用char更好,但是截断也无所谓了
//    memcpy(&inter, reinterpret_cast<const void *>(payload[4]), sizeof(char));
    inter = payload[4];

    unsigned int halfEncoderMb = encoderMb >> 4;
    inter = updateBits(inter, halfEncoderMb,0,1);

//    memcpy(reinterpret_cast<void *>(payload[4]), &inter, sizeof(char));
    payload[4] = inter;

    unsigned int secondInter;
//    memcpy(&secondInter, reinterpret_cast<const void *>(payload[5]), sizeof(char));
    secondInter = payload[5];

    unsigned int secondHalfEncoderMb = encoderMb & 15;
    secondInter = updateBits(secondInter, secondHalfEncoderMb, 4,7);

//    memcpy(reinterpret_cast<void *>(payload[5]), &secondInter, sizeof(char));
    payload[5] = secondInter;

    checkEncoderMb();
}

unsigned int MM2S_1ST_WORD::getEncoderNum(){
    unsigned int inter;//后面直接用的int赋值给encoderNum
//    memcpy(&inter, reinterpret_cast<const void *>(payload[5]), sizeof(char));
    inter = payload[5];
    inter = inter & 15;//提取出来19:16
    inter = inter << 5;

    unsigned int secondHalfInte;
//    memcpy(&secondHalfInte, reinterpret_cast<const void *>(payload[6]), sizeof(char));
    secondHalfInte = payload[6];
    secondHalfInte = secondHalfInte >> 3;
    secondHalfInte = secondHalfInte & 31;

    inter = inter | secondHalfInte;

    this->encoderNum = inter;

    return this->encoderNum;
}


void MM2S_1ST_WORD::setEncoderNum(unsigned int encoderNum){
    unsigned int inter;//这里用char更好,但是截断赋值也可以
//    memcpy(&inter, reinterpret_cast<const void *>(payload[5]), sizeof(char));
    inter = payload[5];

    unsigned int halfEncoderNum = encoderNum >> 5;
    inter = updateBits(inter, halfEncoderNum,0,3);

//    memcpy(reinterpret_cast<void *>(payload[5]), &inter, sizeof(char));
    payload[5] = inter;

    unsigned int secondInter;
//    memcpy(&secondInter, reinterpret_cast<const void *>(payload[6]), sizeof(char));
    secondInter = payload[6];

    unsigned int secondHalfEncoderNum = encoderNum & 31;
    secondInter = updateBits(secondInter, secondHalfEncoderNum, 3,7);

//    memcpy(reinterpret_cast<void *>(payload[6]), &secondInter, sizeof(char));
    payload[6] = secondInter;
}