//==========================================================================
//
//      text_disp.h
//
//      LCD text display code for Game Boy Advance
//
//==========================================================================
#ifndef _TEXT_DISP_H
#define _TEXT_DISP_H

#define TD_SCREEN_WIDTH		30
#define TD_SCREEN_VWIDTH	32
#define TD_SCREEN_HEIGHT	20
#define TD_SCREEN_VHEIGHT	64

int putchar(int c);

void TD_Init(void);
void TD_PrintChar(char c);
void TD_Print(char *string);
void TD_Clear(void);
void TD_SetPosition(unsigned short x, unsigned short y);
void TD_GetPosition(unsigned short *x, unsigned short *y);

#endif
