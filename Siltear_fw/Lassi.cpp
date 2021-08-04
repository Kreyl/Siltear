/*
 * Lassi.cpp
 *
 *  Created on: 1 авг. 2021 г.
 *      Author: layst
 */

#include "lassi.h"
#include "board.h"
#include "led.h"

// Lassi
LedRGB_t ILassi[LASSI_CNT] = {
        {PWM01_PIN, PWM02_PIN, PWM03_PIN},
        {PWM04_PIN, PWM05_PIN, PWM06_PIN},
        {PWM07_PIN, PWM08_PIN, PWM09_PIN},
        {PWM10_PIN, PWM11_PIN, PWM12_PIN},
        {PWM13_PIN, PWM14_PIN, PWM15_PIN},
};


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
}

}

