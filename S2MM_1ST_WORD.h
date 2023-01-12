//
// Created by shun on 2022/12/28.
//

#ifndef LINKCONTROL_S2MM_1ST_WORD_H
#define LINKCONTROL_S2MM_1ST_WORD_H


#include "DATA_WORD.h"
#include <iostream>
#include <stdexcept>

class S2MM_1ST_WORD : public DATA_WORD{
private:
    std::array<unsigned char,4> head;
    unsigned char crcVerfyReslt;
    unsigned char evm;
    unsigned int decoderAccuNum;
    unsigned char amp;
    unsigned char modulation;
    unsigned int encoderMb;
    unsigned int encoderNum;

    bool checkPayload();
    bool checkHead();
    bool checkVerfyRslt();
    bool checkModu();
    bool checkEncoderMb();

public:
    S2MM_1ST_WORD();
    S2MM_1ST_WORD(std::array<unsigned char,8> payload);

    std::array<unsigned char, 4> getHead();
    void setHead(std::array<unsigned char, 4> headToSet);

    unsigned char getCrcVrRs();
    void setCrcVrRs(char crcVrRs);

    unsigned char getEvm();
    void setEvm(char evm);

    unsigned int getDecoderAccuNum();
    void setDecoderAccuNum(unsigned int decoderAccuNum);

    unsigned char getAmp();
    void setAmp(unsigned char amp);

    unsigned char getModulation();
    void setModulation(char modulation);

    unsigned int getEncoderMb();
    void setEncoderMb(unsigned int encoderMb);

    unsigned int getEncoderNum();
    void setEncoderNum(unsigned int encoderNum);
};


#endif //LINKCONTROL_S2MM_1ST_WORD_H
