//-----------------------------------------------------------------------------
// file name: pwm_demo.h
// author: xuxin
// DATE:2025-01-16
//-----------------------------------------------------------------------------
   
#if (INCLUDE_MODULE_PWM == TEST_YES) 

#ifndef _PWM_DEMO_H_
#define _PWM_DEMO_H_

#define SINGER_PIN  9 // スピーカーを接続するピン

// 音階の周波数 (C, D, E, F, G, A, B)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

void singPlayer(void);



#endif // _PWM_DEMO_H_


#endif // (INCLUDE_MODULE_PWM == TEST_YES) 