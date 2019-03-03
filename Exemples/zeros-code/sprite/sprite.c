#include"gba_types.h"
#include"gba_mem.h"
#include"gba_const.h"

#ifdef MULTIBOOT
  volatile const u8 __gba_multiboot; // crt0.o const for multiboot mode
#endif

void blit_smiley(u8 x,u8 y);


//it's a smiley trust me.
u16 smiley[]={0,0     ,0     ,0,
	      0,0x0001,0x0100,0,
	      0,0     ,0     ,0,
	      0,0     ,0     ,0,
	      0,0     ,0     ,0,
	      0x0100,0,0,0x0001,
	      0,0x0101,0x0101,0,
	      0,0     ,0    ,0};

int AgbMain() {
  u16 *character=SPRITE_CHARACTER; 
  u16 *spritePalette=SPRITE_PALETTE;
  Sprite *realSprites=(Sprite *)OBJECT_ATTRIBUTE;

  u16 i;

  DISPLAY_CONTROL=MODE0 | OBJECTS;

  // setup palette
  spritePalette[0]=0xFFFF;
  spritePalette[1]=0xFFFF;
  
  // setup sprite info
  realSprites[0].attrib0=ATTRIB0_COLOR_256 | ATTRIB0_SQUARE | 76; //palette typ, size-mod and y
  realSprites[0].attrib1=ATTRIB1_SIZE_8 | 116; //size and x
  realSprites[0].attrib2=0; //tile

  //copy smiley into character ram
  for(i=0;i<32;i++) {
    character[i]=smiley[i];
  }

  return 0; //to what? the bios!
}
