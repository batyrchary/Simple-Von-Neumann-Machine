#include <stdio.h>
#include <string.h>
#define max 100001
int cell[max];

int main()
{
	int r,i,e,n,p,op;
	int vi,wi,hi,ti,pi,si,ai,ni;

	scanf("%d",&r);
	for(i=0;i<=r;i++)
	{
		cell[i]=1;
	}

	scanf("%d",&vi);
	for(op=0;op<vi;op++)
	{
		scanf("%d %d %d %d %d %d %d",&wi,&hi,&ti,&pi,&si,&ai,&ni);
		for(n=0;n<ni;n++)
		{
			for(p=pi;p<pi+wi;p++)
			{
				if((p+wi)<=0 || p>r)
				{
					break;
				}
				if(p>=0 && cell[p]<hi)
				{

						cell[p]=hi;
				}
			}
			pi=pi+si*ai;
		}
	}


	for(e=0;e<=r;e++)
	{
		printf("%d ",cell[e]);
	}

	return 0;
}
