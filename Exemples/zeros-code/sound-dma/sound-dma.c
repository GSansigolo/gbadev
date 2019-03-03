#include"gba_types.h"
#include"gba_mem.h"
#include"gba_const.h"

#include"sound.h"

#ifdef MULTIBOOT
  volatile const u8 __gba_multiboot; // crt0.o const for multiboot mode
#endif

void IRQ() {
  u16 *b = VIDEO_BUFFER;

  DMA1_CONTROL=0;
  DMA1_CONTROL=DMA_DESTINATION_INCREMENT | DMA_SOURCE_INCREMENT | DMA_REPEAT | DMA_32BITS | DMA_SOUND_FIFO | DMA_GO;

  if(b[118+(137*240)]==0xFFFF) {
    b[118+(137*240)]=0;
    b[119+(137*240)]=0;
    b[118+(138*240)]=0;
    b[119+(138*240)]=0;
  } else {
    b[118+(137*240)]=0xFFFF;
    b[119+(137*240)]=0xFFFF;
    b[118+(138*240)]=0xFFFF;
    b[119+(138*240)]=0xFFFF;
  }

  INT_FLAGS|=INT_FLAGS;
}

int AgbMain() {
  u16 *b = VIDEO_BUFFER;
  u32 i=0;
  DISPLAY_CONTROL=MODE3 | BACKGROUND2;

  SOUND_CONTROL_HIGH=SOUNDA_FULL_OUTPUT | SOUNDA_RIGHT | SOUNDA_LEFT | SOUNDA_FIFO_RESET | SOUNDA_TIMER0;
  SOUND_MASTER=SOUND_ENABLE;

  TIMER1_COUNT=(0xFFFF - SOUND_SAMPLES);
  TIMER1_CONTROL=TIMER_CASCADE | TIMER_IRQ_ENABLE | TIMER_START;

  INT_FUNCTION=(u32)IRQ;
  INT_ENABLE=INT_TIMER1;
  INT_MASTER=1;

  TIMER0_COUNT=(0xFFFF-(16777216/22050));
  TIMER0_CONTROL=TIMER_FREQ1 | TIMER_START;

  DMA1_SOURCE=(u32)&sound[0];
  DMA1_DESTINATION=SOUNDA_FIFO_ADDRESS;
  DMA1_CONTROL=DMA_DESTINATION_INCREMENT | DMA_SOURCE_INCREMENT | DMA_REPEAT | DMA_32BITS | DMA_SOUND_FIFO | DMA_GO;

  while(1) {
    if((DISPLAY_STATUS & VERTICAL_REFRESH)==0) {
      //wait during vertical refresh
      while((DISPLAY_STATUS & VERTICAL_REFRESH)==0) {
      }
      while((DISPLAY_STATUS & VERTICAL_REFRESH)==1) {
      }
    }

    i++;
    if(i>0x1F) {
      i=0;
    }

    b[118+(140*240)]=i;
    b[119+(140*240)]=i;
    b[118+(141*240)]=i;
    b[119+(141*240)]=i;

    b[121+(140*240)]=i;
    b[122+(140*240)]=i;
    b[121+(141*240)]=i;
    b[122+(141*240)]=i;
  }

  return 0; //to what? the bios!
}
