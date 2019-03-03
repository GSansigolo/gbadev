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

u16 box0[]={0x0101,0x0101,0x0101,0x0101,
	    0x0001,0,0,0,
	    0x0001,0,0,0,
	    0x0001,0,0,0,
	    0x0001,0,0,0,
	    0x0001,0,0,0,
	    0x0001,0,0,0,
	    0x0001,0,0,0};
u16 box1[]={0x0202,0x0202,0x0202,0x0202,
	    0x0002,0,0,0,
	    0x0002,0,0,0,
	    0x0002,0,0,0,
	    0x0002,0,0,0,
	    0x0002,0,0,0,
	    0x0002,0,0,0,
	    0x0002,0,0,0};
u16 box2[]={0x0303,0x0303,0x0303,0x0303,
	    0x0003,0,0,0,
	    0x0003,0,0,0,
	    0x0003,0,0,0,
	    0x0003,0,0,0,
	    0x0003,0,0,0,
	    0x0003,0,0,0,
	    0x0003,0,0,0};
u16 box3[]={0x0404,0x0404,0x0404,0x0404,
	    0x0004,0,0,0,
	    0x0004,0,0,0,
	    0x0004,0,0,0,
	    0x0004,0,0,0,
	    0x0004,0,0,0,
	    0x0004,0,0,0,
	    0x0004,0,0,0};

int AgbMain() {
  u16 *spriteCharacter=SPRITE_CHARACTER; 
  u16 *spritePalette=SPRITE_PALETTE;
  u16 *backgroundPalette=BACKGROUND_PALETTE;

  u16 *background0Character=BACKGROUND_CHARACTER(0);
  u16 *background1Character=BACKGROUND_CHARACTER(1);
  u16 *background2Character=BACKGROUND_CHARACTER(2);
  u16 *background3Character=BACKGROUND_CHARACTER(3);

  u16 *background0Map=BACKGROUND_MAP(28);
  u16 *background1Map=BACKGROUND_MAP(29);
  u16 *background2Map=BACKGROUND_MAP(30);
  u16 *background3Map=BACKGROUND_MAP(31);

  u16 b0=BACKGROUND0;
  u16 b1=BACKGROUND1;
  u16 b2=BACKGROUND2;
  u16 b3=BACKGROUND3;

  u8 x,y;
  s16 bx,by;
  s16 nx,ny;

  u16 vflip=0;
  u16 hflip=0;

  Sprite *realSprites=(Sprite *)OBJECT_ATTRIBUTE;

  u16 i;
  u8 bdelay=0;
  u8 adelay=0;

  DISPLAY_CONTROL=MODE0 | BACKGROUND0 | BACKGROUND1 | BACKGROUND2 | BACKGROUND3 | OBJECTS;

  BACKGROUND0_CONTROL=BACKGROUND_COLOR_256 | BACKGROUND_WHICH_CHARACTER(0) | BACKGROUND_WHICH_MAP(28) | TEXT_SIZE_256x256 | 0; // 0 = priority
  BACKGROUND1_CONTROL=BACKGROUND_COLOR_256 | BACKGROUND_WHICH_CHARACTER(1) | BACKGROUND_WHICH_MAP(29) | TEXT_SIZE_256x256 | 1; // 1 = priority
  BACKGROUND2_CONTROL=BACKGROUND_COLOR_256 | BACKGROUND_WHICH_CHARACTER(2) | BACKGROUND_WHICH_MAP(30) | TEXT_SIZE_256x256 | 2; // 2 = priority
  BACKGROUND3_CONTROL=BACKGROUND_COLOR_256 | BACKGROUND_WHICH_CHARACTER(3) | BACKGROUND_WHICH_MAP(31) | TEXT_SIZE_256x256 | 3; // 3 = priority

  // setup palette
  for(i=0;i<256;i++) {
    spritePalette[i]=0;
    backgroundPalette[i]=0;
  }

  spritePalette[1]=0xFFFF;

  backgroundPalette[1]=0x1F;
  backgroundPalette[2]=0x1F << 5;
  backgroundPalette[3]=0x1F << 10;
  backgroundPalette[4]=(0x1F<<5) | 0x1F;    

  //clear sprites
  for(i=0;i<128;i++) {
    realSprites[i].attrib0=160; //put the sprite off the screen
    realSprites[i].attrib1=240;
  }
  x=120;
  y=80;

  bx=0;
  by=0;
  nx=0;
  ny=0;

  for(i=0;i<32;i++) {
    //copy smiley into sprite character ram
    spriteCharacter[i]=smiley[i];
   
    //copy smiley into background character ram
    background0Character[i]=box0[i];
    background1Character[i]=box1[i];
    background2Character[i]=box2[i];
    background3Character[i]=box3[i];
  }

  //set background map
  for(i=0;i<(32*32);i++) {
     background0Map[i]=0;
     background1Map[i]=0;
     background2Map[i]=0;
     background3Map[i]=0;
  }

  i=0;
  while(1) {
    i++;
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
    if(bx< -7) {
      bx=0;
    }
    
    by--; //down
    if(by< -7) {
      by=0;
    }
    
    nx++; //left
    if(nx> 7) {
      nx=0;
    }
    
    ny++; //up
    if(ny> 7) {
      ny=0;
    }
    
    if(i>=10) {
      if(!(KEYPAD & KEY_L)) {
	if(b0==BACKGROUND0) {
	  b0=0;
	} else {
	  b0=BACKGROUND0;
	}
	DISPLAY_CONTROL=MODE0 | b0 | b1 | b2 | b3 | OBJECTS;
      }
      
      if(!(KEYPAD & KEY_R)) {
	if(b1==BACKGROUND1) {
	  b1=0;
	} else {
	  b1=BACKGROUND1;
	}
	DISPLAY_CONTROL=MODE0 | b0 | b1 | b2 | b3 | OBJECTS;
      }
      
      if(!(KEYPAD & KEY_SELECT)) {
	if(b2==BACKGROUND2) {
	  b2=0;
	} else {
	  b2=BACKGROUND2;
	}
	DISPLAY_CONTROL=MODE0 | b0 | b1 | b2 | b3 | OBJECTS;
      }

      if(!(KEYPAD & KEY_START)) {
        if(b3==BACKGROUND3) {
          b3=0;
        } else {
          b3=BACKGROUND3;
        }
        DISPLAY_CONTROL=MODE0 | b0 | b1 | b2 | b3 | OBJECTS;
      }
      
      i=0;
    }

    // setup sprite info
    realSprites[0].attrib0=ATTRIB0_COLOR_256 | ATTRIB0_SQUARE | y; //palette typ, size-mod and y
    realSprites[0].attrib1=ATTRIB1_SIZE_8 | vflip | hflip | x; //size and x
    realSprites[0].attrib2=ATTRIB2_PRIORITY(0) | 0; //smiley's tile is 0

    BACKGROUND0_X_SCROLL=bx;
    BACKGROUND0_Y_SCROLL=by;

    BACKGROUND1_X_SCROLL=bx;
    BACKGROUND1_Y_SCROLL=ny;

    BACKGROUND2_X_SCROLL=nx;
    BACKGROUND2_Y_SCROLL=by;

    BACKGROUND3_X_SCROLL=nx;
    BACKGROUND3_Y_SCROLL=ny;
  }
  return 0; //to what? the bios!
}
