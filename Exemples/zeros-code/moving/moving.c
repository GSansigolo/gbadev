#include"gba_types.h"
#include"gba_mem.h"
#include"gba_const.h"

#ifdef MULTIBOOT
  volatile const u8 __gba_multiboot; // crt0.o const for multiboot mode
#endif

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
  u16 *spriteCharacter=SPRITE_CHARACTER; 
  u16 *spritePalette=SPRITE_PALETTE;
  u16 *backgroundPalette=BACKGROUND_PALETTE;
  u16 *backgroundCharacter=BACKGROUND_CHARACTER(0);
  u16 *backgroundMap=BACKGROUND_MAP(24);

  u8 x,y;
  s16 bx,by;

  u16 vflip=0;
  u16 hflip=0;

  Sprite *realSprites=(Sprite *)OBJECT_ATTRIBUTE;

  u16 i;
  u8 bdelay=0;
  u8 adelay=0;

  DISPLAY_CONTROL=MODE0 | BACKGROUND0 | OBJECTS;

  BACKGROUND0_CONTROL=BACKGROUND_COLOR_256 | BACKGROUND_WHICH_CHARACTER(0) | BACKGROUND_WHICH_MAP(24) | TEXT_SIZE_256x256 | 0; // 0 = priority


  // setup palette
  for(i=0;i<256;i++) {
    spritePalette[i]=0;
    backgroundPalette[i]=0;
  }

  spritePalette[1]=0xFFFF;

  backgroundPalette[1]=0x1F; //0x1F = 31 i hope.... red i would think BGR...

  //clear sprites
  for(i=0;i<128;i++) {
    realSprites[i].attrib0=240; //put the sprite off the screen
    realSprites[i].attrib1=160;
  }
  x=120;
  y=80;

  bx=0;
  by=0;

  for(i=0;i<32;i++) {
    //copy smiley into sprite character ram
    spriteCharacter[i]=smiley[i];
   
    //copy smiley into background character ram
    backgroundCharacter[i]=smiley[i];
  }

  //set background map
  for(i=0;i<(32*32);i++) {
     backgroundMap[i]=0; //tile 0 is the smiley!
  }

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
        adelay=5;
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
        bdelay=5;
      }
    }
    
    bx--; //right
    if(bx<-7) {
      bx=0;
    }

    by--; //down
    if(by<-7) {
      by=0;
    }

    // setup sprite info
    realSprites[0].attrib0=ATTRIB0_COLOR_256 | ATTRIB0_SQUARE | y; //palette typ, size-mod and y
    realSprites[0].attrib1=ATTRIB1_SIZE_8 | vflip | hflip | x; //size and x
    realSprites[0].attrib2=ATTRIB2_PRIORITY(0) | 0; //smiley's tile is 0

    BACKGROUND0_X_SCROLL=bx;
    BACKGROUND0_Y_SCROLL=by;
  }
  return 0; //to what? the bios!
}
