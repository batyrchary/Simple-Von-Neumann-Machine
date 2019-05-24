int main(){
  
unsigned wnumber=2;
int counter=0;
	while(wnumber)
	{	if(wnumber >= 2147483648u)break;
		counter=counter+1;
		wnumber=wnumber<<1;			
	}
		counter=counter+1;
		wnumber=wnumber<<1;
float a=2.0;
printf("%x,%d\n",wnumber,wnumber);
printf("%x,%d\n",counter,counter);
printf("%x\n",a);

}
