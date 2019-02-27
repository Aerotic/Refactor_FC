#ifndef _SBUS_H_
#define _SBUS_H_

#include <stdint.h>

struct _SBUS{

    int16_t CH[6];
    int16_t CH_LAST[6];
    int16_t CH_DIF[6];
    uint16_t NoSignalCnt;//作为失控计数器，在达到一个阈值后强制停转

};
extern struct _SBUS mSBUS;

void SBUS_Init(void);
void SBUS_Check(float T,float OutofControl_ms);
void SBUS_Decode(uint8_t* sbusbuf);
#endif
