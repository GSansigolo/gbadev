typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;

typedef unsigned char byte;
typedef unsigned short hword;
typedef unsigned long word;

typedef struct {
  u16 attrib0;
  u16 attrib1;
  u16 attrib2;
  u16 attrib3;
} Sprite;

typedef struct {
  u16 empty0[3];
  u16 pa; //change these gay names
  u16 empty1[3];
  u16 pb;
  u16 empty2[3];
  u16 pc;
  u16 empty3[3];
  u16 pd;
} Rotate;
