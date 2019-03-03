#include"gba_types.h"
#include"gba_mem.h"
#include"gba_const.h"

#ifdef MULTIBOOT
  volatile const u8 __gba_multiboot; // crt0.o const for multiboot mode
#endif

void blit_smiley(u8 x,u8 y);

u16 *b;

//it's a smiley trust me.
u16 smiley[]={0,0,0,0,0,0,0,0,
	      0,0,0xFFFF,0,0xFFFF,0,0,0,
	      0,0,0,0,0,0,0,0,
	      0,0,0,0,0,0,0,0,
	      0,0,0,0,0,0,0,0,
	      0,0xFFFF,0,0,0,0,0xFFFF,0,
	      0,0,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0,0,
	      0,0,0,0,0,0,0,0};

int AgbMain() {
  b = VIDEO_BUFFER;
  
  DISPLAY_CONTROL=MODE3 | BACKGROUND2;

  blit_smiley(116,76);
  
  return 0; //to what? the bios!
}

// blit_smiley is not meant to be fast.. just to work!
// it really is worthless don't use it
void blit_smiley(u8 x,u8 y) {
  u8 sx;
  u8 sy;

  for(sx=0;sx<8;sx++) {
    for(sy=0;sy<8;sy++) {
      b[(x+sx)+((y+sy)*240)]=smiley[sx+(sy*8)];
    }
  }
}  

