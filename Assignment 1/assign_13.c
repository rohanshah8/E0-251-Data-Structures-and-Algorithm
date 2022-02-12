#include<stdio.h>
int main(){
float s1,s2;
float i=1.0;
int n[]={1,3,5,8,100};
int index=0;
do{
s1=0.0;
i=1;
while(i<=n[index]){
s1=s1+1/i;
i=i+1;
}
i=n[index];
s2=0.0;
while(i>0){
s2=s2+1/i;
i=i-1;
}
printf("Sum of  n=%d terms harmonic sequence (forward)  = %.30f\n",n[index],s1);
printf("Sum of  n=%d terms harmonic sequence (backward) = %.30f\n\n",n[index],s2);
index++;
}while(index!=(sizeof(n)/sizeof(int)));


/*

s1=0.0;
s2=0;
i=1;
n=5;
while(i<=n){
s1=s1+1/i;
i=i+1;
}
i=n;
while(i>0){
s2=s2+1/i;
i=i-1;
}
printf("Sum of  n=%d harmonic sequence = %.40f\n",n,s1);
printf("Sum of  n=%d harmonic sequence = %.40f\n",n,s2);

*/
return 0;
}
