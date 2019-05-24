#include<stdio.h>
#include<string.h>
#define max 128

char dna1[max],dna2[max],dna3[max];
char op1,op4;
int op2,op3,op5;
int fun(char op1);

int main()
{
    int i;
    scanf("%s",dna1);
    scanf("%s",dna2);

    for(i=0;i<4;i++)
    {
        scanf(" %c",&op1);
        fun(op1);
    }

    printf("%s\n",dna1);
    printf("%s\n",dna2);
    printf("%s\n",dna3);
    return 0;
}

int fun(char op1)
{
    int l,c;
    char R,C;

    if(op1=='M')
    {
        scanf("%d %d",&op2,&op3);
        scanf(" %c",&op4);
        if(op2==1)
        {
            dna1[op3]=op4;
        }
        else if(op2==2)
        {
            dna2[op3]=op4;
        }
        else if(op2==3)
        {
            dna3[op3]=op4;
        }
    }

    if(op1=='J')
    {
        scanf("%d",&op2);
        for(l=0;l<strlen(dna2);l++)
        {
            if(l<op2)
            {
                dna3[l]=dna1[l];
            }
                
            if(l>=op2)
            {
                dna3[l]=dna2[l];
            }
        }
    }

    if(op1=='R')
    {
        scanf("%d %d %d",&op2,&op3,&op5);
        if(op2==1)
        {
            R=dna1[op3];
            dna1[op3]=dna1[op5];
            dna1[op5]=R;
        }
        if(op2==2)
        {
            R=dna2[op3];
            dna2[op3]=dna2[op5];
            dna2[op5]=R;
        }
        if(op2==3)
        {
            R=dna3[op3];
            dna3[op3]=dna3[op5];
            dna3[op5]=R;
        }
    }

    if(op1=='C')
    {
        scanf("%d",&op2);
        if(op2==1)
        {
            for(c=0;c<strlen(dna1);c++)
            {
                if(dna1[c]=='A')
                {
                    dna3[c]='T';
                }
                if(dna1[c]=='T')
                {
                    dna3[c]='A';
                }
                if(dna1[c]=='C')
                {
                    dna3[c]='G';
                }
                if(dna1[c]=='G')
                {
                    dna3[c]='C';
                }
            }
        }

        if(op2==2)
        {
            for(c=0;c<strlen(dna2);c++)
            {
                if(dna2[c]=='A')
                {
                    dna3[c]='T';
                }
                if(dna2[c]=='T')
                {
                    dna3[c]='A';
                }
                if(dna2[c]=='C')
                {
                    dna3[c]='G';
                }
                if(dna2[c]=='G')
                {
                    dna3[c]='C';
                }
            }
        }
    }
}



















