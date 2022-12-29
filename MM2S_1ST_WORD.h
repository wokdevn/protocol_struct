//
// Created by shun on 2022/12/26.
//

#ifndef LINKCONTROL_MM2S_1ST_WORD_H
#define LINKCONTROL_MM2S_1ST_WORD_H


#include <iterator>
#include <iostream>
#include "DATA_WORD.h"

#define HEAD_LEN 4
#define MODU_LEN 2
#define ENCODER_MB_MIN 7
#define ENCODER_MB_MAX 46


//enum modulType {BPSK,QPSK,QAM16,QAM64};

class MM2S_1ST_WORD : public DATA_WORD {
private:
    unsigned char head[4];
    unsigned char modulation;
    unsigned int encoderMb;
    unsigned int encoderNum;

    bool checkPayload();
    bool checkHead();
    bool checkModu();
    bool checkEncoderMb();

    /*
 * source: char wait for replace
 * toUpdate: char to replace
 * begin:source begin
 * end:source end
 * 把source中的begin到end替换成相应长度的toUpdate
 * */
    template <class T>
    T updateBits(T source , T toUpdate, int begin , int end){
        T max = ~0;
        T left = max - ((1<<(end+1)) -1);
        T right = (1<<begin) -1;
        T mask = left | right;
        return (source & mask) | ((toUpdate << begin)&(~mask));
    }

//    modulType modulationType;

public:
    MM2S_1ST_WORD(unsigned char payload[8]);

    unsigned char * getHead();
    void setHead(unsigned char * headToSet);

    unsigned char getModulation();
    void setModulation(char modulation);
//    void setModulation(modulType modulation);

    unsigned int getEncoderMb();
    void setEncoderMb(unsigned int encoderMb);

    unsigned int getEncoderNum();
    void setEncoderNum(unsigned int encoderNum);
};

#endif //LINKCONTROL_MM2S_1ST_WORD_H
