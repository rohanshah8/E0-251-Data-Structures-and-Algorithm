#include<stdio.h>
#include<stdlib.h>
void out_float(float f,char *bin)
{
  size_t size = sizeof(f);
  unsigned char * p = (unsigned char *) &f;
  p += size-1;
  int i=0;
  while (size--)
  {
    for (int n=0; n<8; n++)
    {
      bin[i]= ('0' + (*p & 128 ? 1 : 0));
      i++;
      *p <<= 1;
    }
    p--;
  }
  bin[32]='\0';
}

int main(){

float pie=22/7.0f;
int hex=0x40490FDB;
float pie_hex=*((float*)&hex);
char *buffer1,*buffer2;
out_float(pie,buffer1);
out_float(pie_hex,buffer2);

printf("Binary of 22/7 = %s \nBinary of  hex = %s \n",buffer1,buffer2);
int differ=1;
while(buffer1){
  if(*buffer1!=*buffer2)
    break;
  else  
    differ++;
  buffer1++,buffer2++;
}
printf("Differ at %d binary position \n------------------------------------",differ);

//decimal representation of both
printf("\npie dec = %.30f \npie hex = %.30f\n",pie,pie_hex);
differ=1;
while(1){
  if((int)pie!=(int)pie_hex)
    break;
  else  
    differ++;
  pie*=10,pie_hex*=10;
}

printf("Differ at %d decimal position after point\n",differ-1);
return 0;
}
