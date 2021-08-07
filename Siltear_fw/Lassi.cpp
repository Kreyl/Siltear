/*
 * Lassi.cpp
 *
 *  Created on: 1 авг. 2021 г.
 *      Author: layst
 */

#include "lassi.h"
#include "board.h"
#include "led.h"
#include "radio_lvl1.h"

// Lassi
LedRGB_t ILassi[LASSI_CNT] = {
        {PWM01_PIN, PWM02_PIN, PWM03_PIN},
        {PWM04_PIN, PWM05_PIN, PWM06_PIN},
        {PWM07_PIN, PWM08_PIN, PWM09_PIN},
        {PWM10_PIN, PWM11_PIN, PWM12_PIN},
        {PWM13_PIN, PWM14_PIN, PWM15_PIN},
};

// Sequences
LedRGBChunk_t lsq[LASSI_CNT][2] = {
        { {csSetup, SMOOTH_CONST, clRed}, {csEnd} },
        { {csSetup, SMOOTH_CONST, clRed}, {csEnd} },
        { {csSetup, SMOOTH_CONST, clRed}, {csEnd} },
        { {csSetup, SMOOTH_CONST, clRed}, {csEnd} },
        { {csSetup, SMOOTH_CONST, clRed}, {csEnd} },
};


static uint8_t OldChnlID = LASSI_CNT+1; // non-valid value
static const Color_t ClrTbl[CLR_CNT] = { clRed, clGreen, clBlue };

static THD_WORKING_AREA(waLassiThd, 256);
static void LassiThd(void *arg) {
    chRegSetThreadName("LassiThd");
    while(true) {
        // Select new active channel
        uint8_t ActiveChnlID, ActiveClrID = Random::Generate(0, (CLR_CNT-1));
        do {
            ActiveChnlID = Random::Generate(0, (LASSI_CNT-1));
        } while(ActiveChnlID == OldChnlID);
        OldChnlID = ActiveChnlID;
        Printf("Act: %u; Clrs: ", ActiveChnlID);

        // Iterate channels and setup them
        for(uint8_t i=0; i<LASSI_CNT; i++) {
            Color_t Clr;
            // Active chnl
            if(i == ActiveChnlID) {
                Clr = ClrTbl[ActiveClrID];
                Printf("%c; ", (ActiveClrID == 0)? 'R' : (ActiveClrID == 1)? 'G' : 'B');
                Radio.RMsgQ.SendNowOrExit(RMsg_t(Clr));
            }
            // Non-active chnl
            else {
                // Select color not equal to active one
                uint8_t NonActiveClrID;
                do {
                    NonActiveClrID = Random::Generate(0, (CLR_CNT-1));
                } while(NonActiveClrID == ActiveClrID);
                Clr = ClrTbl[NonActiveClrID];
                Printf("%c; ", (NonActiveClrID == 0)? 'R' : (NonActiveClrID == 1)? 'G' : 'B');
            }
            // Set color
            lsq[i][0].Color = Clr;
//            Clr.Print();
            ILassi[i].StartOrRestart(lsq[i]);
        }
        PrintfEOL();
        chThdSleepSeconds(SWITCH_PERIOD_S);
    }
}


namespace Lassi {

void Init() {
    for(auto &Lasse : ILassi) {
        Lasse.Init();
        Lasse.SetColor({36,45,54});
//        Lasse.SetColor(clRed);
//        chThdSleepMilliseconds(63);
//        Lasse.SetColor(clGreen);
//        chThdSleepMilliseconds(63);
//        Lasse.SetColor(clBlue);
//        chThdSleepMilliseconds(63);
//        Lasse.SetColor(clBlack);
    }
    chThdCreateStatic(waLassiThd, sizeof(waLassiThd), NORMALPRIO, (tfunc_t)LassiThd, NULL);
}

} // namespace

