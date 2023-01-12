//
// Created by shun on 2022/12/28.
//

#include "S2MM_1ST_WORD.h"

#define HEAD_LEN 4
#define ENCODER_MB_MIN 7
#define ENCODER_MB_MAX 46

S2MM_1ST_WORD::S2MM_1ST_WORD(){}

S2MM_1ST_WORD::S2MM_1ST_WORD(std::array<unsigned char,8> payload) : DATA_WORD(payload){
    checkPayload();
}

bool S2MM_1ST_WORD::checkPayload(){
    checkHead();
    checkVerfyRslt();
    checkModu();
    checkEncoderMb();
}
bool S2MM_1ST_WORD::checkHead(){
    try{
        std::array<unsigned char,4> headToCheck = getHead();
        int flag = 1;

        for(int i = 0; i < HEAD_LEN; ++i){
            if(headToCheck[i] != (i+1)){
                flag = 0;
                break;
            }
        }

        if(!flag){
            throw std::invalid_argument("head is not 1234");
        }
    }catch (std::invalid_argument &ia){
        std::cerr << "head check failed " << ia.what() << std::endl;
    }
}
bool S2MM_1ST_WORD::checkVerfyRslt(){
    try{
        char crcResult = getCrcVrRs();

        if(crcResult>1 || crcResult <0){
            throw std::invalid_argument("crc invalid");
        }
    }catch (std::invalid_argument &ia){
        std::cerr<<"crc check failed " << ia.what()<<std::endl;
    }

}
bool S2MM_1ST_WORD::checkModu(){
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
bool S2MM_1ST_WORD::checkEncoderMb(){
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

std::array<unsigned char,4> S2MM_1ST_WORD::getHead(){
//    unsigned char * inter = new unsigned char[4];
    for(int i = 0; i < 4 ;++i){
        unsigned char num = 0;
        for(int j = 0;j<4;++j){
            num = num <<1;
            num= num + (payloadInBit[i*4+j]&1);
        }
        this->head[i] = num;
    }
    return this->head;
}

void S2MM_1ST_WORD::setHead(std::array<unsigned char,4> headToSet){
    this->head = headToSet;
    checkHead();

    for(int i = 0; i<4; ++i){
        char inter = head[i];
        for(int j = 0; j<4;++j){
            this->payloadInBit[i*4+j] = inter & 8;
            inter = inter <<1;
        }
    }
}

unsigned char S2MM_1ST_WORD::getCrcVrRs(){
    this->crcVerfyReslt = payloadInBit[16];
    return this->crcVerfyReslt;
}

void S2MM_1ST_WORD::setCrcVrRs(char crcVrRs){
    this->crcVerfyReslt = crcVrRs;
    checkVerfyRslt();

    this->payloadInBit[16] = crcVrRs & 1;
}

unsigned char S2MM_1ST_WORD::getEvm(){
    //TODO:evm数据格式暂时不知道.先空着
}

void S2MM_1ST_WORD::setEvm(char evm){
    this->evm = evm;
    //TODO:format not known
}

unsigned int S2MM_1ST_WORD::getDecoderAccuNum(){
    unsigned int inter = 0;
    for(int i = 25;i<34;++i){
        inter = inter <<1;
        inter = inter + (this->payloadInBit[i]&1);
    }

    this->decoderAccuNum = inter;

    return this->decoderAccuNum;
}

void S2MM_1ST_WORD::setDecoderAccuNum(unsigned int decoderAccuNum){
    this->decoderAccuNum = decoderAccuNum;

    for(int i = 33;i>24;--i){
        this->payloadInBit[i] = decoderAccuNum &1;
        decoderAccuNum = decoderAccuNum >>1;
    }
}

unsigned char getAmp(){
    //TODO:信号幅度判定数据格式暂时不知道,先空着
}
void S2MM_1ST_WORD::setAmp(unsigned char amp){
    this->amp = amp;
    //TODO:format not known
}

unsigned char S2MM_1ST_WORD::getModulation(){
    unsigned char inter = 0;
    for(int i =36; i<38; ++i){
        inter = inter <<1;
        inter = inter + (this->payloadInBit[i]&1);
    }
    this->modulation = inter;
    return this->modulation;
}
void S2MM_1ST_WORD::setModulation(char modulation){
    this->modulation = modulation;
    checkModu();

    for(int i = 37;i>35;--i){
        this->payloadInBit[i] = modulation & 1;
        modulation = modulation >>1;
    }
}

unsigned int S2MM_1ST_WORD::getEncoderMb(){
    unsigned int inter = 0;
    for(int i = 38; i< 44;++i){
        inter = inter <<1;
        inter = inter+(this->payloadInBit[i]&1);
    }
    this->encoderMb = inter;
    return this->encoderMb;
}
void S2MM_1ST_WORD::setEncoderMb(unsigned int encoderMb){
    this->encoderMb = encoderMb;
    checkEncoderMb();

    for(int i = 43; i>37;--i){
        this->payloadInBit[i] = encoderMb &1;
        encoderMb = encoderMb >>1;
    }
}

unsigned int S2MM_1ST_WORD::getEncoderNum(){
    unsigned int inter = 0;
    for(int i = 44; i<53;++i){
        inter = inter <<1;
        inter = inter +(this->payloadInBit[i]&1);
    }
    this->encoderNum = inter;
    return this->encoderNum;
}
void S2MM_1ST_WORD::setEncoderNum(unsigned int encoderNum){
    this->encoderNum = encoderNum;

    for(int i = 52;i>43;--i){
        this->payloadInBit[i] = encoderNum&1;
        encoderNum = encoderNum >> 1;
    }
}
