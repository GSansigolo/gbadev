//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// Graphics ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
////// Constants For DISPLAY_CONTROL
/// Video Mode
#define MODE0               0x0 // 0-3 backgrounds are normal
#define MODE1            0x0001 // 0,1 backgrounds are normal 2 is (rotate/scale)able
#define MODE2            0x0002 // 2,3 are (rotate/scale)able
#define MODE3            0x0003 // 240x160 16bpp frame buffer 1 page
#define MODE4            0x0004 // 240x160 8bpp paletted frame buffer 2 pages
#define MODE5            0x0005 // 160x128 16bpp frame buffer 2 pages

/// misc
#define GB_COLOR         0x0008 // set in gb color (readonly) // leave me alone
#define PAGE_FLIP        0x0010 // for page flipping in mode 4 and 5
#define FORCE_HBLANK     0x0020 // processes video during hblank

#define SPRITE_1D        0x0040 // sprite memory mode
#define SPRITE_2D           0x0 

#define SCREEN_OFF       0x0080 // turns off screen! video memory transfers faster?

/// Background Bits
#define BACKGROUND0      0x0100
#define BACKGROUND1      0x0200
#define BACKGROUND2      0x0400
#define BACKGROUND3      0x0800

/// Object Bits (sprites)
#define OBJECTS          0x1000

/// Window Bits
#define WINDOW0          0x2000
#define WINDOW1          0x4000
#define WINDOW_OBJECTS   0x8000

//////////////////////////////////////////////////////////////////////////////////////////
////// Constants For DISPLAY_STATUS
#define VERTICAL_REFRESH     0x01 // set during blank
#define HORIZONTAL_REFRESH   0x02 // set during blank
#define VCOUNT_TRIGGER       0x04 // set to 1 on vcount interrupt?

#define VBLANK_IRQ_ENABLE    0x08 // enable (set in INT_ENABLE also)
#define HBLANK_IRQ_ENABLE    0x10 // enable (set in INT_ENABLE also)
#define VCOUNT_IRQ_ENABLE    0x20 // enable (set in INT_EBABLE also)

/////// VCOUNT upper 8bits set the vcount (used with vcount irq)
#define VCOUNT(x)        ((x)<<8)

//////////////////////////////////////////////////////////////////////////////////////////
////// Constants For Sprite Attributes
/// Sprite Attribute 0
/////// ATTRIB0_Y                        Y // 8bits
#define ATTRIB0_ROTATION             0x100
#define ATTRIB0_DOUBLE               0x200

#define ATTRIB0_MODE_NORMAL            0x0
#define ATTRIB0_MODE_TRANSPERANT     0x400
#define ATTRIB0_MODE_WINDOWED        0x800

#define ATTRIB0_MOSAIC              0x1000

#define ATTRIB0_COLOR_16               0x0
#define ATTRIB0_COLOR_256           0x2000

#define ATTRIB0_SQUARE                 0x0 
#define ATTRIB0_WIDE                0x4000
#define ATTRIB0_TALL                0x8000

/// Sprite Attribute 1
/////// ATTRIB1_X                        X // 9bits
#define ATTRIB1_ROTATE(x)       ((x) << 9) // 5bits // which rotate data to use for this sprite.

#define ATTRIB1_HORIZONTAL_FLIP     0x1000
#define ATTRIB1_VERTICAL_FLIP       0x2000

#define ATTRIB1_SIZE_8                 0x0
#define ATTRIB1_SIZE_16             0x4000
#define ATTRIB1_SIZE_32             0x8000
#define ATTRIB1_SIZE_64             0xC000

/// Sprite Attribute 2
/////// ATTRIB2_TILE                  TILE // 10bits
#define ATTRIB2_PRIORITY(x)    ((x) << 10) // 2bits

#define ATTRIB2_PALETTE(x)     ((x) << 12) // 4bits

/// Sprite Attribute 3
/////// Rotation Data See gba_types.h typedef struct {...} Rotate;

//////////////////////////////////////////////////////////////////////////////////////////
////// Constants For Backgrounds
/////// BACKGROUND_PRIORITY             NUM // 2bits 0 is higher than 1

/////// BACKGROUND_WHICH_CHARACTER      NUM // 2bits (Tile Address = 0x6000000 + (NUM * 0x4000)
#define BACKGROUND_WHICH_CHARACTER(x)   ((x) << 2)

#define BACKGROUND_MOSAIC              0x40

#define BACKGROUND_COLOR_16             0x0
#define BACKGROUND_COLOR_256           0x80

/////// BACKGROUND_WHICH_MAP            NUM // 5bits Address = 0x6000000 + NUM * 0x800
#define BACKGROUND_WHICH_MAP(x)         ((x) << 8)

#define BACKGROUND_WRAPAROUND        0x2000 // rotate backgrounds only // text auto wrap always

#define TEXT_SIZE_256x256               0x0 // THATS THE RES NOT THE NUMBER OF TILES MORON!
#define TEXT_SIZE_512x256            0x4000 // 8)
#define TEXT_SIZE_256x512            0x8000
#define TEXT_SIZE_512x512            0xC000

#define ROTATE_SIZE_128x128             0x0
#define ROTATE_SIZE_256x256          0x4000
#define ROTATE_SIZE_512x512          0x8000
#define ROTATE_SIZE_1024x1024        0xC000

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// DMA ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

#define DMA_DESTINATION_INCREMENT       0x0 
#define DMA_DESTINATION_DECREMENT    0x0020
#define DMA_DESTINATION_FIXED        0x0040
#define DMA_DESTINATION_RELOAD       0x0060 //? not sure

#define DMA_SOURCE_INCREMENT            0x0
#define DMA_SOURCE_DECREMENT         0x0080
#define DMA_SOURCE_FIXED             0x0100

#define DMA_REPEAT                   0x0200 //repeat on hblank or vblank or sound fifo

#define DMA_16BITS                      0x0 //16bits at a time
#define DMA_32BITS                   0x0400 //32bits at a time

#define DMA_IMMEDIATE                   0x0
#define DMA_VBLANK                   0x1000 //copy on vblank
#define DMA_HBLANK                   0x2000 //copy on hblank
#define DMA_SOUND_FIFO               0x3000 //copy when sound fifo asks

#define DMA_IRQ_ENABLE               0x4000 //cause interrupt when finished
#define DMA_GO                       0x8000 //START COPYING!

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// Sound //////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//// SOUND_CONTROL_HIGH bits
/////// SOUND_SYNTH_OUTPUT        X // 0=25%,1=50%,2=100%,3=BOOM!? (2 bits)

#define SOUNDA_HALF_OUTPUT      0x0
#define SOUNDA_FULL_OUTPUT   0x0004

#define SOUNDB_HALF_OUTPUT      0x0
#define SOUNDB_FULL_OUTPUT   0x0008

#define SOUNDA_RIGHT         0x0100
#define SOUNDA_LEFT          0x0200

#define SOUNDA_TIMER0           0x0 //enable timer0 overflow signals rate for sound a
#define SOUNDA_TIMER1        0x0400 //enable timer1 overflow signals rate for sound a

#define SOUNDA_FIFO_RESET    0x0800 //reset everytime before playback start

#define SOUNDB_RIGHT         0x1000
#define SOUNDB_LEFT          0x2000

#define SOUNDB_TIMER0           0x0 //enable timer0 overflow signals rate for sound b
#define SOUNDB_TIMER1        0x4000 //enable timer1 overflow signals rate for sound b

#define SOUNDB_FIFO_RESET    0x8000 //reset everytime before playback start

//// SOUND_MASTER bits
#define SOUND_ENABLE         0x0080 //turn on the sound chips

//// SOUND MISC DEFS
#define SOUND_22KHZ           (761) // (16777216/22050)= ~760

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// Timer //////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
#define TIMER_FREQ1        0x00 // 16.78mhz
#define TIMER_FREQ64       0x01 // ~262187.5KHz
#define TIMER_FREQ256      0x02 // ~65546.875KHz
#define TIMER_FREQ1024     0x03 // ~16386.71875KHz

#define TIMER_CASCADE      0x04 // cascade
/////// TIMER_3BIT GAP     !!!! // no idea! (3 unused bits inbetween 0x04 and 0x40)
#define TIMER_IRQ_ENABLE   0x40
#define TIMER_START        0x80

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// Keypad /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
////// Constants For KEYPAD
/// Keys
#define KEY_A        0x1
#define KEY_B        0x2
#define KEY_SELECT   0x4
#define KEY_START    0x8
#define KEY_RIGHT   0x10
#define KEY_LEFT    0x20
#define KEY_UP      0x40
#define KEY_DOWN    0x80
#define KEY_R      0x100
#define KEY_L      0x200

//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// Interrupts ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
#define INT_VBLANK   0x0001
#define INT_HBLANK   0x0002
#define INT_VCOUNT   0x0004 //generate interrupt on vcount

#define INT_TIMER0   0x0008
#define INT_TIMER1   0x0010
#define INT_TIMER2   0x0020
#define INT_TIMER3   0x0040

#define INT_SERIAL   0x0080 //serial communication interupt

#define INT_DMA0     0x0100
#define INT_DMA1     0x0200
#define INT_DMA2     0x0400
#define INT_DMA3     0x0800

#define INT_KEY      0x1000

#define INT_CART     0x2000
