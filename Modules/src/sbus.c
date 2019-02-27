/**
 * @author Aero <neuhutao@gmail.com>
 * @file Description
 * @desc Created on 2019-02-27 11:07:49 am
 * @copyright APPI SASU
 */
#include "sbus.h"
struct _SBUS mSBUS;
uint16_t sbus_decode_buffer[6];

void SBUS_Decode(uint8_t* sbusbuf){

//		sbus_decode_buffer[0] = (sbusbuf[1] | (sbusbuf[2] << 8)) & 0x07ff; //!< Channel 0
//		mSBUS.CH[2] = (my_deathzoom(sbus_decode_buffer[0]-1024, 5));
//		//?????   ??+-660
//		sbus_decode_buffer[1] = ((sbusbuf[2] >> 3) | (sbusbuf[3] << 5)) & 0x07ff; //!< Channel 1
//		mSBUS.CH[1] = -(my_deathzoom(sbus_decode_buffer[1]-1024, 5));
//		//?????   ??+-660
//		sbus_decode_buffer[2]= ((sbusbuf[3] >> 6) | (sbusbuf[4] << 2) | (sbusbuf[5] << 10)) & 0x07ff; //!< Channel 2
//		mSBUS.CH[3] = my_deathzoom(sbus_decode_buffer[2]-1024, 5);
//		//?????   ??+-660
//		sbus_decode_buffer[3] = ((sbusbuf[5] >> 1) | (sbusbuf[6] << 7)) & 0x07ff; //!< Channel 3
//		mSBUS.CH[0] = -(my_deathzoom(sbus_decode_buffer[3]-1024, 5));
//		//????  132 ???
//		mSBUS.CH[4] = ((sbusbuf[6] >> 4)& 0x000C) >> 2; //!< Switch left
//		//????  132 ???
//		mSBUS.CH[5] = ((sbusbuf[6] >> 4)& 0x0003); //!< Switch right9 / 9  
}