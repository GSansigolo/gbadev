#include"gba_types.h"
#include"gba_mem.h"
#include"gba_const.h"

#ifdef MULTIBOOT
  volatile const u8 __gba_multiboot; // crt0.o const for multiboot mode
#endif

void blit_smiley(u8 x,u8 y);


//it's a smiley trust me.
u16 smiley[]={0,0     ,0     ,0,
	      0,0,0x0001,0x0100,
	      0,0     ,0     ,0,
	      0,0     ,0     ,0,
	      0,0     ,0     ,0,
	      0x0100,0,0,0x0001,
	      0,0x0101,0x0101,0,
	      0,0     ,0    ,0};

int AgbMain() {
  u16 *character=SPRITE_CHARACTER; 
  u16 *spritePalette=SPRITE_PALETTE;
  u8 x,y;
  u16 vflip=0;
  u16 hflip=0;

  Sprite *realSprites=(Sprite *)OBJECT_ATTRIBUTE;

  u16 i;
  u8 bdelay=0;
  u8 adelay=0;

  DISPLAY_CONTROL=MODE0 | OBJECTS;

  // setup palette
  spritePalette[0]=0xFFFF;
  spritePalette[1]=0xFFFF;

  x=116;
  y=76;
  
  //copy smiley into character ram
  for(i=0;i<32;i++) {
    character[i]=smiley[i];
  }
  
  i=0;
  while(1) {

    if((DISPLAY_STATUS & VERTICAL_REFRESH)==0) {
      //wait during vertical refresh
      while((DISPLAY_STATUS & VERTICAL_REFRESH)==0) {
      }
      while((DISPLAY_STATUS & VERTICAL_REFRESH)==1) {
      }
    }

    if(!(KEYPAD & KEY_LEFT)) {
      if(x>0) {
	x--;
      }
    }
    if(!(KEYPAD & KEY_RIGHT)) {
      if(x<232) {
	x++;
      }
    }
    if(!(KEYPAD & KEY_UP)) {
      if(y>0) {
	y--;
      }
    }
    if(!(KEYPAD & KEY_DOWN)) {
      if(y<152) {
	y++;
      }
    }
    
    if(adelay != 0) {
      adelay--;
    } else {
      if(!(KEYPAD & KEY_A)) {
        if(vflip==0) {
	  vflip=ATTRIB1_VERTICAL_FLIP;
	} else {
	  vflip=0;
	}
        adelay=10;
      }
    }

    if(bdelay != 0) {
      bdelay--;
    } else {
      if(!(KEYPAD & KEY_B)) {
	if(hflip==0) {
	  hflip=ATTRIB1_HORIZONTAL_FLIP;
	} else {
	  hflip=0;
	}
        bdelay=10;
      }
    }

    // setup sprite info
    realSprites[0].attrib0=ATTRIB0_COLOR_256 | ATTRIB0_SQUARE | y; //palette typ, size-mod and y
    realSprites[0].attrib1=ATTRIB1_SIZE_8 | vflip | hflip | x; //size and x
    realSprites[0].attrib2=0; //tile
  }
  return 0; //to what? the bios!
}
