MEMORY
{
  /* ARDUINO UNO R3 */
  /*0x0000 - 0x001F：32 x General Purpose Registers
    0x0020 - 0x005F：64 x I/O Registers
    0x0060 - 0x00FF：Extended I/O Registers
    0x0100 - 0x08FF：SRAM（Static RAM）2KB RAM*/

  ram (rwx) : ORIGIN = 0x100, LENGTH = 2048  /* RAM，2KB */
  flash (rx) : ORIGIN = 0x0, LENGTH = 0X7C00  /* FLASH 32KB/ BOOTLOADR 1KB 0x7C00-0X8000 */
  
  /* USED FOR PATCH */
  /*patch_ram (rwx) : ORIGIN = PATCH_RAM_JUMP_TABLE_ADDR, LENGTH = PATCH_JUMP_TABLE_SIZE
  patch_rom (rx) : ORIGIN = PATCH_ROM_JUMP_TABLE_ADDR, LENGTH = PATCH_JUMP_TABLE_SIZE
  patch_flash (rx) : ORIGIN = PATCH_FLASH_JUMP_TABLE_ADDR, LENGTH = PATCH_JUMP_TABLE_SIZE
  patch_code (rx) : ORIGIN = PATCH_FLASH_PATCH_CODE_ADDR, LENGTH = PATCH_FLASH_PATCH_ZONE_SIZE*/
  patch_ram (rwx) : ORIGIN = 0x700, LENGTH = 64
  patch_rom (rx) : ORIGIN = 0x6200, LENGTH = 64
  patch_flash (rx) : ORIGIN = 0x6400, LENGTH = 64
  patch_code (rx) : ORIGIN = 0x6500, LENGTH = 0x400
}

/*SECTIONS {
  .text : { *(.text*) }
  .rom_jmp_table PATCH_ROM_JUMP_TABLE_ADDR : {
    KEEP(*(.rom_jmp_table))
  }
  .bss (NOLOAD) : {
    PATCH_RAM_JUMP_TABLE_ADDR = .;
  }
}*/

SECTIONS
{
  .text : {
    *(.text)
  } > flash
  
  .data : {
    *(.data)
  } > ram
  
  .bss : {
    *(.bss)
  } > ram
  
  .patch_ram : {
    . = 0x700;
    *(.patch_ram)
  } > patch_ram
  
  .patch_rom : {
    . = 0x6200;
    *(.patch_rom)
  } > patch_rom
  
  .patch_flash : {
    . = 0x6400;
    *(.patch_flash)
  } > patch_flash

  .patch_code : {
    . = 0x6500;
    *(.patch_code)
  } > patch_code
}
