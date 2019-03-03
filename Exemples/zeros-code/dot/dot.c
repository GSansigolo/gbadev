#include"gba_types.h"
#include"gba_mem.h"
#include"gba_const.h"

#ifdef MULTIBOOT
  volatile const u8 __gba_multiboot; // crt0.o const for multiboot mode
#endif



int AgbMain() {
  u16 *b = VIDEO_BUFFER;
  
  DISPLAY_CONTROL=MODE3 | BACKGROUND2;
  
  b[120+(80*240)]=0xFFFF;

  return 0; //to what? the bios!
}
