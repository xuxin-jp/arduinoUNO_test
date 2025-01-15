#include "config.h"
#if (INCLUDE_MODULE_PATCH == TEST_YES) 
#include "patch_demo.h"
#endif

void setup() {
    pinMode(LED_PIN, OUTPUT);
    // Serial.begin(9600);
    #if (INCLUDE_MODULE_PATCH == TEST_YES) 
    patch_loadJumpTable();


    // int result1 = func1(3, 1.0f);

    // float result2 = func2(45.67);

    // int result3 = func3(3, 1.0f);

    CALL_FUNCTION(func1, 10, 5.5f);
    CALL_FUNCTION(func2, 3.14);    
    CALL_FUNCTION(func3, 20, 4.5f);
    
    #endif

    /* memory size test
    // フラッシュメモリのサイズ プログラム用
    Serial.print("Flash Memory Size: "); //16000 KB
    Serial.print(F_CPU / 1000); // フラッシュサイズの参考値
    Serial.println(" KB");

    // SRAMのサイズ 変数やスタック用
    extern int __heap_start, *__brkval;
    int v;
    Serial.print("SRAM Free Size: "); //1796
    Serial.println((int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval));

    // EEPROMのサイズ 不揮発性メモリ
    Serial.print("EEPROM Size: "); //1024
    Serial.println(EEPROM.length());

    */
}

void loop() {
  // put your main code here, to run repeatedly:
}