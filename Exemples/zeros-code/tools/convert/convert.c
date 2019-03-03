#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main() {
  FILE *outfile;
  //int outrawfile;
  int infile;
  int ok;
  unsigned int data;
  int i=0;

  if(sizeof(unsigned int)!=4) {
    printf("sizeof(unsign int) != 4 is true!\n");
    return -1;
  }

  infile=open("sound.raw",O_RDONLY);

  outfile=fopen("sound.h","w");
  //outrawfile=open("sound_converted.raw",O_WRONLY | O_CREAT);

  fprintf(outfile,"const u32 sound[]={");

  ok=read(infile,&data,4);
  while(1) {
    fprintf(outfile,"0x%X",data);
    //write(outrawfile,&data,4);    
    i++;

    ok=read(infile,&data,4);
    if(ok==0) {
      break;
    }
    fprintf(outfile,",");
  }
  fprintf(outfile,"};\n");
  fprintf(outfile,"#define SOUND_MEMBERS   %d\n",i);
  fprintf(outfile,"#define SOUND_SAMPLES   %d\n",i*4);

  close(infile);
  fclose(outfile);
  //close(outrawfile);

  printf("Sample has [%d] samples\n",i);

  return 0;
}
