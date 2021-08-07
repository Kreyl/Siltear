/*
 * radio_lvl1.h
 *
 *  Created on: Nov 17, 2013
 *      Author: kreyl
 */

#pragma once

#include "kl_lib.h"
#include "ch.h"
#include "cc1101.h"
#include "shell.h"
#include "MsgQ.h"
#include "color.h"

#define CC_TX_PWR   CC_PwrPlus5dBm

#if 1 // =========================== Pkt_t =====================================
struct rPkt_t  {
    Color_t Clr;
    rPkt_t& operator = (const rPkt_t &Right) {
        Clr = Right.Clr;
        return *this;
    }
//    void Print() { Printf("%d %d %d %d %d %d; %X\r", Ch[0],Ch[1],Ch[2],Ch[3],R1, R2, Btns); }
} __packed;

#define RPKT_LEN    sizeof(rPkt_t)

#endif

#define RMSG_Q_LEN      18

struct RMsg_t {
    Color_t Clr;
    uint32_t ID;
    RMsg_t& operator = (const RMsg_t &Right) {
        Clr = Right.Clr;
        ID = Right.ID;
        return *this;
    }
    RMsg_t() {
        Clr = clBlack;
        ID = 0;
    }
    RMsg_t(Color_t &AClr)  {
        Clr = AClr;
        ID = 1;
    }
} __attribute__((__packed__));


class rLevel1_t {
private:
public:
    int8_t Rssi;
    rPkt_t rPkt;
    EvtMsgQ_t<RMsg_t, RMSG_Q_LEN> RMsgQ;
    uint8_t Init();
    void SetChannel(uint8_t NewChannel);
    // Inner use
    void ITask();
};

extern rLevel1_t Radio;
