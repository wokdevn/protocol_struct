//
// Created by shun on 2022/12/28.
//

#include <stdexcept>
#include "S2MM_1ST_WORD.h"

S2MM_1ST_WORD::S2MM_1ST_WORD(){}

S2MM_1ST_WORD::S2MM_1ST_WORD(unsigned char payload[8]) : DATA_WORD(payload){
    checkPayload();
}

bool S2MM_1ST_WORD::checkPayload(){
    checkHead();
    checkVerfyRslt();
    checkModu();
    checkEncoderMb();
}
bool checkHead(){
    try{

    }catch (std::invalid_argument &ia){
        std::cerr << "head check failed" << ia.what() << std::endl;
    }
}
bool checkVerfyRslt(){

}
bool checkModu(){

}
bool checkEncoderMb(){

}

unsigned char * S2MM_1ST_WORD::getHead(){
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

void setHead(unsigned char * headToSet){

}

unsigned char getCrcVrRs(){

}

void setCrcVrRs(char crcVrRs){

}

unsigned char getEvm(){

}

void setEvm(char evm){

}

unsigned int getDecoderAccuNum(){

}

void setDecoderAccuNum(unsigned int decoderAccuNum){

}

unsigned char getAmp(){

}
void setAmp(unsigned char amp){

}

unsigned char getModulation(){

}
void setModulation(char modulation){

}

unsigned int getEncoderMb(){

}
void setEncoderMb(unsigned int encoderMb){

}

unsigned int getEncoderNum(){

}
void setEncoderNum(unsigned int encoderNum){

}
