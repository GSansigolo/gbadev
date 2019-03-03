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

  DISPLAY_CONTROL=MODE0 | OBJECTS;

  // setup palette
  spritePalette[0]=0xFFFF;
  spritePalette[1]=0xFFFF;
  
  // setup sprite info
  realSprites[0].attrib0=ATTRIB0_COLOR_256 | ATTRIB0_SQUARE | 76; //palette typ, size-mod and y
  realSprites[0].attrib1=ATTRIB1_SIZE_8 | 116; //size and x
  realSprites[0].attrib2=0; //tile

  //old copy smiley into character ram
  //for(i=0;i<32;i++) {
  //  character[i]=smiley[i];
  // }

  //new dma copy!
  DMA3_SOURCE=(u32)smiley; //same as &smiley[0] i think (it worked when i ran it on hardware!?
  DMA3_DESTINATION=(u32)&character[0];
  DMA3_COUNT=16; // 16 32bits to copy! (32 16bits or 64 8bits (dma doesn't do 8bits though))
  DMA3_CONTROL=DMA_DESTINATION_INCREMENT | DMA_SOURCE_INCREMENT | DMA_32BITS | DMA_GO;

  return 0; //to what? the bios!
}
