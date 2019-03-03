//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// Buffers ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//// Palettes
#define BACKGROUND_PALETTE        ((u16*)0x5000000)
#define SPRITE_PALETTE            ((u16*)0x5000200)

//// Framebuffer Background // overlaps with BACKGROUND_CHARACTER() and BACKGROUND_MAP()
#define VIDEO_BUFFER              ((u16*)0x6000000)

//// Text Background Tile Data // overlaps with VIDEO_BUFFER and BACKGROUND_MAP()
#define BACKGROUND_CHARACTER(x)   ((u16*)(0x6000000+((x)*0x4000))) //parens... killing... me....

//// Text Background Map Data // overlaps with VIDEO_BUFFER and BACKGROUND_CHARACTER()
#define BACKGROUND_MAP(x)         ((u16*)(0x6000000+((x)*0x800)))

//// Sprite
#define SPRITE_CHARACTER          ((u16*)0x6010000)

//// Sprite Information
#define OBJECT_ATTRIBUTE          ((u16*)0x7000000)


//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// Registers /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//// Display Stuff
#define DISPLAY_CONTROL        (*(u32*)0x4000000)
#define DISPLAY_STATUS         (*(u32*)0x4000004)

//// Backgrounds
#define BACKGROUND0_CONTROL    (*(u16*)0x4000008)
#define BACKGROUND1_CONTROL    (*(u16*)0x400000A)
#define BACKGROUND2_CONTROL    (*(u16*)0x400000C)
#define BACKGROUND3_CONTROL    (*(u16*)0x400000E)

//// Backgrounds Scrollers
#define BACKGROUND0_X_SCROLL   (*(u16*)0x4000010)
#define BACKGROUND0_Y_SCROLL   (*(u16*)0x4000012)

#define BACKGROUND1_X_SCROLL   (*(u16*)0x4000014)
#define BACKGROUND1_Y_SCROLL   (*(u16*)0x4000016)

#define BACKGROUND2_X_SCROLL   (*(u16*)0x4000018)
#define BACKGROUND2_Y_SCROLL   (*(u16*)0x400001A)

#define BACKGROUND3_X_SCROLL   (*(u16*)0x400001C)
#define BACKGROUND3_Y_SCROLL   (*(u16*)0x400001E)

//////////////////////////////////////////////////////////////////////////////////////////
//// DMA
#define DMA0_SOURCE            (*(u32*)0x40000B0)
#define DMA0_DESTINATION       (*(u32*)0x40000B4)
#define DMA0_COUNT             (*(u16*)0x40000B8)
#define DMA0_CONTROL           (*(u16*)0x40000BA)

#define DMA1_SOURCE            (*(u32*)0x40000BC)
#define DMA1_DESTINATION       (*(u32*)0x40000C0)
#define DMA1_COUNT             (*(u16*)0x40000C4)
#define DMA1_CONTROL           (*(u16*)0x40000C6)

#define DMA2_SOURCE            (*(u32*)0x40000C8)
#define DMA2_DESTINATION       (*(u32*)0x40000CC)
#define DMA2_COUNT             (*(u16*)0x40000D0)
#define DMA2_CONTROL           (*(u16*)0x40000D2)

#define DMA3_SOURCE            (*(u32*)0x40000D4)
#define DMA3_DESTINATION       (*(u32*)0x40000D8)
#define DMA3_COUNT             (*(u16*)0x40000DC)
#define DMA3_CONTROL           (*(u16*)0x40000DE)

//////////////////////////////////////////////////////////////////////////////////////////
//// Sound
#define SOUND_CONTROL_LOW      (*(u16*)0x4000080)
#define SOUND_CONTROL_HIGH     (*(u16*)0x4000082)
#define SOUND_MASTER           (*(u16*)0x4000084)

#define SOUNDA_FIFO            (*(u32*)0x40000A0)
#define SOUNDA_FIFO_ADDRESS           (0x40000A0) //for setting dma1
#define SOUNDB_FIFO            (*(u32*)0x40000A4)
#define SOUNDB_FIFO_ADDRESS           (0x40000A4) //for setting dma2

//////////////////////////////////////////////////////////////////////////////////////////
//// Timers
#define TIMER0_COUNT           (*(u16*)0x4000100)
#define TIMER0_CONTROL         (*(u16*)0x4000102)

#define TIMER1_COUNT           (*(u16*)0x4000104)
#define TIMER1_CONTROL         (*(u16*)0x4000106)

#define TIMER2_COUNT           (*(u16*)0x4000108)
#define TIMER2_CONTROL         (*(u16*)0x400010A)

#define TIMER3_COUNT           (*(u16*)0x400010C)
#define TIMER3_CONTROL         (*(u16*)0x400010E)

//////////////////////////////////////////////////////////////////////////////////////////
//// Keypad
#define KEYPAD                 (*(u32*)0x4000130)

//////////////////////////////////////////////////////////////////////////////////////////
//// Interrupt
#define INT_ENABLE             (*(u16*)0x4000200) //individual interrupts enable
#define INT_FLAGS              (*(u16*)0x4000202)
#define INT_MASTER              (*(u8*)0x4000208) //set to 1 to enable all interrupts
#define INT_FUNCTION           (*(u32*)0x3007FFC) //int handler here (function pointer)

//#define REG_BIOSIF (*(unsigned short *)0x03fffff8) //use with bios interrupts???

