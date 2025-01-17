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
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  783


void singPlayer(void);



#endif // _PWM_DEMO_H_


#endif // (INCLUDE_MODULE_PWM == TEST_YES) 