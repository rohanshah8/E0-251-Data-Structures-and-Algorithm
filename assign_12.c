#include<stdio.h>
int main(){
//For float single precision
int count=0;
float f=1.0;
while(f!=0.0){
f=f/2.0;
count+=1;
}
printf("No. of times loop iterate = %d ",count);
//For Double precision
count=0;
double d=1.0;
while(d!=0.0){
d=d/2.0;
count+=1;
}
printf("No. of times loop iterate = %d ",count);
return 0;
}
