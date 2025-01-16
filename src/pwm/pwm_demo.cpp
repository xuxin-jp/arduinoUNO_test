//-----------------------------------------------------------------------------
// file name: pwm_demo.C
// author: xuxin
// DATE:2025-01-16
//-----------------------------------------------------------------------------
#include "config.h"

#if (INCLUDE_MODULE_PWM == TEST_YES) 
#include "pwm_demo.h"
#define _PWM_DEMO_C_

// 曲の音階と長さ
int melody[] = {
  NOTE_E4, NOTE_E4, NOTE_E4, // ジングルベル ジングルベル
  NOTE_E4, NOTE_E4, NOTE_E4, // 鈴が鳴る
  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4, // 今日も楽しい
  NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4,         // 日のように
  NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, // 明るく進もう
  NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_G4 // 鈴が鳴る
};

// 音の長さ
int noteDurations[] = {
  4, 4, 4, 
  4, 4, 4,
  4, 4, 4, 4, 2, // 最初のフレーズ
  4, 4, 4, 4, 
  4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 2     // 次のフレーズ
};

void playNote(int pin, int frequency, unsigned long duration)
{
  int period = 1000000 / frequency; // 周期 (microseconds)
  int pulseWidth = period / 2;      // 占空比 50%

  unsigned long startTime = millis();
  while ((millis() - startTime) < duration) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(pulseWidth);
    digitalWrite(pin, LOW);
    delayMicroseconds(pulseWidth);
  }
}

void singPlayer(void) 
{
    // 曲を1音ずつ再生
  int durationSize = sizeof(noteDurations) / sizeof(noteDurations[0]);
  int melodySize = sizeof(melody) / sizeof(melody[0]);
  int minSize = (durationSize < melodySize) ? durationSize : melodySize;
      
  for (int i = 0; i < minSize; i++) {
    if (noteDurations[i] != 0) {
        int noteDuration = 1000 / noteDurations[i]; // 音の長さを計算
        playNote(SINGER_PIN, melody[i], noteDuration);  // 音を再生
        delay(noteDuration * 0.30);                // 音と音の間に少し間をあける
        analogWrite(SINGER_PIN, 0);                        // Stop sound
    } else {
        Serial.println("Warning: noteDuration is zero!");
        break;
    }
  }
  delay(2000); // 曲が終わった後、2秒間の休止
}

#endif