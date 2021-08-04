#if 1 // ============================ Includes =================================
#include "hal.h"
#include "MsgQ.h"
#include "shell.h"
#include "led.h"
//#include "buttons.h"
#include "Sequences.h"
#include "kl_i2c.h"
#include "lassi.h"
#endif
#if 1 // ======================== Variables & prototypes =======================
// Forever
bool OsIsInitialized = false;
EvtMsgQ_t<EvtMsg_t, MAIN_EVT_Q_LEN> EvtQMain;
static const UartParams_t CmdUartParams(115200, CMD_UART_PARAMS);
CmdUart_t Uart{CmdUartParams};
void OnCmd(Shell_t *PShell);
void ITask();

PinInput_t PinUsbDetect(USB_DETECT_PIN, pudPullDown);

LedSmooth_t Led{PWM16_PIN};

static TmrKL_t TmrOneSecond {TIME_MS2I(999), evtIdEverySecond, tktPeriodic}; // Measure battery periodically
#endif

int main(void) {
#if 1 // ==== Iwdg, Clk, Os, EvtQ, Uart ====
    // Start Watchdog. Will reset in main thread by periodic 1 sec events.
//    Iwdg::InitAndStart(4500);
//    Iwdg::DisableInDebug();
    // Setup clock frequency
//    Clk.SetCoreClk(cclk48MHz);
//    // 48MHz clock
//    Clk.SetupSai1Qas48MhzSrc();
    Clk.UpdateFreqValues();
    // Init OS
    halInit();
    chSysInit();
    OsIsInitialized = true;

    // ==== Init hardware ====
    EvtQMain.Init();
    Uart.Init();
    Printf("\r%S %S\r", APP_NAME, XSTRINGIFY(BUILD_TIME));
    Clk.PrintFreqs();
#endif

    Led.Init();

    const LedSmoothChunk_t *p = lsqOk;
    Led.StartOrRestart(p);
    Lassi::Init();
//    PinUsbDetect.Init();

    TmrOneSecond.StartOrRestart();

    // Main cycle
    ITask();
}

__noreturn
void ITask() {
    while(true) {
        EvtMsg_t Msg = EvtQMain.Fetch(TIME_INFINITE);
        switch(Msg.ID) {
            case evtIdShellCmdRcvd:
                while(((CmdUart_t*)Msg.Ptr)->TryParseRxBuff() == retvOk) OnCmd((Shell_t*)((CmdUart_t*)Msg.Ptr));
                break;

            case evtIdEverySecond:
//                Printf("Second\r");
                Iwdg::Reload();
                // Check USB
//                if(PinUsbDetect.IsHi() and !PinUsbIsHigh) {
//                    if(AuPlayer.IsPlayingNow()) {
//                        AuPlayer.Stop();
//                        chThdSleepMilliseconds(4);
//                    }
//                    PinUsbIsHigh = true;
//                    EvtQMain.SendNowOrExit(EvtMsg_t(evtIdUsbConnect));
//                }
//                else if(!PinUsbDetect.IsHi() and PinUsbIsHigh) {
//                    PinUsbIsHigh = false;
//                    EvtQMain.SendNowOrExit(EvtMsg_t(evtIdUsbDisconnect));
//                    Led.StartOrContinue(lsqOk);
//                }
                break;

#if 0 // ======= USB =======
            case evtIdUsbConnect:
                Printf("USB connect\r");
                Resume();
                UsbConnected = true;
                UsbMsd.Connect();
                Charger.Enable();
                break;
            case evtIdUsbDisconnect:
                Standby();
                Printf("USB disconnect\r");
                UsbConnected = false;
                UsbMsd.Disconnect();
                break;
            case evtIdUsbReady:
                Printf("USB ready\r");
                break;
#endif
            default: break;
        } // switch
    } // while true
}

#if 1 // ======================= Command processing ============================
void OnCmd(Shell_t *PShell) {
	Cmd_t *PCmd = &PShell->Cmd;
    // Handle command
    if(PCmd->NameIs("Ping")) PShell->Ok();
    else if(PCmd->NameIs("Version")) PShell->Print("%S %S\r", APP_NAME, XSTRINGIFY(BUILD_TIME));
    else if(PCmd->NameIs("mem")) PrintMemoryInfo();

    else PShell->CmdUnknown();
}
#endif
