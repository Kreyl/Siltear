/*
 * board.h
 *
 *  Created on: 05 08 2018
 *      Author: Kreyl
 */

#pragma once

// ==== General ====
#define APP_NAME            "Dragon"

// Version of PCB
#define PCB_VER                 1

// MCU type as defined in the ST header.
#define STM32L476xx

// Freq of external crystal if any. Leave it here even if not used.
#define CRYSTAL_FREQ_HZ         12000000

// OS timer settings
#define STM32_ST_IRQ_PRIORITY   2
#define STM32_ST_USE_TIMER      5
#define SYS_TIM_CLK             (Clk.APB1FreqHz)    // Timer 5 is clocked by APB1

//  Periphery
#define I2C1_ENABLED            FALSE
#define I2C2_ENABLED            FALSE
#define I2C3_ENABLED            TRUE

#define ADC_REQUIRED            FALSE
#define STM32_DMA_REQUIRED      TRUE    // Leave this macro name for OS

#if 1 // ========================== GPIO =======================================
// EXTI
#define INDIVIDUAL_EXTI_IRQ_REQUIRED    FALSE

// PWM
#define PWM01_PIN       { GPIOA,  0,  TIM2, 1, invNotInverted, omPushPull, 255 }
#define PWM02_PIN       { GPIOA,  1,  TIM2, 2, invNotInverted, omPushPull, 255 }
#define PWM03_PIN       { GPIOB,  0,  TIM3, 3, invNotInverted, omPushPull, 255 }
#define PWM04_PIN       { GPIOB,  1,  TIM3, 4, invNotInverted, omPushPull, 255 }
#define PWM05_PIN       { GPIOB, 10,  TIM2, 3, invNotInverted, omPushPull, 255 }
#define PWM06_PIN       { GPIOB, 11,  TIM2, 4, invNotInverted, omPushPull, 255 }
#define PWM07_PIN       { GPIOB, 14, TIM15, 1, invNotInverted, omPushPull, 255 }
#define PWM08_PIN       { GPIOB, 15, TIM15, 2, invNotInverted, omPushPull, 255 }
#define PWM09_PIN       { GPIOC,  6,  TIM8, 1, invNotInverted, omPushPull, 255 }
#define PWM10_PIN       { GPIOC,  7,  TIM8, 2, invNotInverted, omPushPull, 255 }
#define PWM11_PIN       { GPIOC,  8,  TIM8, 3, invNotInverted, omPushPull, 255 }
#define PWM12_PIN       { GPIOC,  9,  TIM8, 4, invNotInverted, omPushPull, 255 }
#define PWM13_PIN       { GPIOB,  6,  TIM4, 1, invNotInverted, omPushPull, 255 }
#define PWM14_PIN       { GPIOB,  7,  TIM4, 2, invNotInverted, omPushPull, 255 }
#define PWM15_PIN       { GPIOB,  8,  TIM4, 3, invNotInverted, omPushPull, 255 }
#define PWM16_PIN       { GPIOB,  9,  TIM4, 4, invNotInverted, omPushPull, 255 }

// LCD
#define LCD_SDA         GPIOA, 2 // USART2
#define LCD_XRES        GPIOA, 3
#define LCD_SCLK        GPIOA, 4
#define LCD_AF          AF7
#define LCD_XCS         GPIOB, 13
#define LCD_BCKLT       PWM16_PIN
#define LCD_PWR         GPIOB, 12

// Radio: SPI, PGpio, Sck, Miso, Mosi, Cs, Gdo0
#define CC_Setup0       SPI1, GPIOA, 5,6,7, GPIOC,5, GPIOC,4

// Just pins
#define GPIO_PA8        GPIOA, 8
#define GPIO_PA10       GPIOA, 10
#define GPIO_PC2        GPIOC, 2
#define GPIO_PC3        GPIOC, 3

// Buttons
#define BTN1_PIN        GPIOA, 15, pudPullUp
#define BTN2_PIN        GPIOC, 12, pudPullUp
#define BTN3_PIN        GPIOD,  2, pudPullUp
#define BTN4_PIN        GPIOC, 13, pudPullUp
#define BTN5_PIN        GPIOC, 14, pudPullUp

// Encoder
#define ENC1_PIN        GPIOB, 4, pudPullUp
#define ENC2_PIN        GPIOB, 5, pudPullUp

// UART
#define UART_GPIO       GPIOC
#define UART_TX_PIN     10
#define UART_RX_PIN     11

// I2C
//#define I2C1_GPIO       GPIOB
//#define I2C1_SCL        6
//#define I2C1_SDA        7
//#define I2C2_GPIO       GPIOB
//#define I2C2_SCL        10
//#define I2C2_SDA        11
#define I2C3_GPIO       GPIOC
#define I2C3_SCL        0
#define I2C3_SDA        1
// I2C Alternate Function
#define I2C_AF          AF4

// USB
#define USB_DM          GPIOA, 11
#define USB_DP          GPIOA, 12
#define USB_AF          AF10
// USB detect
#define USB_DETECT_PIN  GPIOA, 9

#endif // GPIO

#if 1 // =========================== I2C =======================================
// i2cclkPCLK1, i2cclkSYSCLK, i2cclkHSI
#define I2C_CLK_SRC     i2cclkHSI
#define I2C_BAUDRATE_HZ 400000
#endif

#if ADC_REQUIRED // ======================= Inner ADC ==========================
// Clock divider: clock is generated from the APB2
#define ADC_CLK_DIVIDER		adcDiv2

// ADC channels
#define ADC_BATTERY_CHNL 	14
// ADC_VREFINT_CHNL
#define ADC_CHANNELS        { ADC_BATTERY_CHNL, ADC_VREFINT_CHNL }
#define ADC_CHANNEL_CNT     2   // Do not use countof(AdcChannels) as preprocessor does not know what is countof => cannot check
#define ADC_SAMPLE_TIME     ast24d5Cycles
#define ADC_OVERSAMPLING_RATIO  64   // 1 (no oversampling), 2, 4, 8, 16, 32, 64, 128, 256
#endif

#if 1 // =========================== DMA =======================================
// ==== Uart ====
// Remap is made automatically if required
#define UART_DMA_TX     STM32_DMA_STREAM_ID(2, 3)
#define UART_DMA_RX     STM32_DMA_STREAM_ID(2, 5)
#define UART_DMA_CHNL   2
#define UART_DMA_TX_MODE(Chnl) (STM32_DMA_CR_CHSEL(Chnl) | DMA_PRIORITY_LOW | STM32_DMA_CR_MSIZE_BYTE | STM32_DMA_CR_PSIZE_BYTE | STM32_DMA_CR_MINC | STM32_DMA_CR_DIR_M2P | STM32_DMA_CR_TCIE)
#define UART_DMA_RX_MODE(Chnl) (STM32_DMA_CR_CHSEL(Chnl) | DMA_PRIORITY_MEDIUM | STM32_DMA_CR_MSIZE_BYTE | STM32_DMA_CR_PSIZE_BYTE | STM32_DMA_CR_MINC | STM32_DMA_CR_DIR_P2M | STM32_DMA_CR_CIRC)

// LCD
#define UARTLCD_DMA_TX          STM32_DMA_STREAM_ID(1, 7)
#define UARTLCD_DMA_CHNL        2
#define UARTLCD_DMA_MODE(Chnl)  (STM32_DMA_CR_CHSEL(Chnl) | DMA_PRIORITY_LOW | STM32_DMA_CR_MSIZE_BYTE | STM32_DMA_CR_PSIZE_BYTE | STM32_DMA_CR_MINC | STM32_DMA_CR_DIR_M2P | STM32_DMA_CR_TCIE)

// ==== I2C ====
#define I2C_USE_DMA     TRUE
//#define I2C1_DMA_TX     STM32_DMA_STREAM_ID(1, 6)
//#define I2C1_DMA_RX     STM32_DMA_STREAM_ID(1, 7)
//#define I2C1_DMA_CHNL   3
//#define I2C2_DMA_TX     STM32_DMA_STREAM_ID(1, 4)
//#define I2C2_DMA_RX     STM32_DMA_STREAM_ID(1, 5)
//#define I2C2_DMA_CHNL   3
#define I2C3_DMA_TX     STM32_DMA_STREAM_ID(1, 2)
#define I2C3_DMA_RX     STM32_DMA_STREAM_ID(1, 3)
#define I2C3_DMA_CHNL   3

#if ADC_REQUIRED
#define ADC_DMA         STM32_DMA1_STREAM1
#define ADC_DMA_MODE    STM32_DMA_CR_CHSEL(0) |   /* DMA1 Stream1 Channel0 */ \
                        DMA_PRIORITY_LOW | \
                        STM32_DMA_CR_MSIZE_HWORD | \
                        STM32_DMA_CR_PSIZE_HWORD | \
                        STM32_DMA_CR_MINC |       /* Memory pointer increase */ \
                        STM32_DMA_CR_DIR_P2M |    /* Direction is peripheral to memory */ \
                        STM32_DMA_CR_TCIE         /* Enable Transmission Complete IRQ */
#endif // ADC

#endif // DMA

#if 1 // ========================== USART ======================================
#define PRINTF_FLOAT_EN FALSE
#define UART_TXBUF_SZ   4096
#define UART_RXBUF_SZ   99
#define CMD_BUF_SZ      256

#define CMD_UART        UART4

#define CMD_UART_PARAMS \
    CMD_UART, UART_GPIO, UART_TX_PIN, UART_GPIO, UART_RX_PIN, \
    UART_DMA_TX, UART_DMA_RX, UART_DMA_TX_MODE(UART_DMA_CHNL), UART_DMA_RX_MODE(UART_DMA_CHNL), \
    uartclkHSI // Use independent clock

#endif
