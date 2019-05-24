#include "lab3.h"
char* encode(char* message)
{
    int len=(int)strlen(message);
    char* res=(char*)malloc(sizeof(char)*(len+len/8));
    int i=0;
    int j=0;
    int counter=0;
    for(i=0;i<=len;)
    {
        if(*(message+i)=='1')counter++;
        *(res+j)=*(message+i);
        j++;
        i++;
        if(i%8==0)
        {
            *(res+j)='0'+(counter%2);
            counter=0;
            j++;
        }
    }
    *(res+j)=0;
    return res;
}
char* decode(char* message)
{
    int len=(int)strlen(message);
    char* res=malloc(sizeof(char)*8);
    int counter=0;
    int i;
    int j=0;
    for(i=0;i<len;)
    {
        if(*(message+i)=='1')counter++;
        *(res+j)=*(message+i);
        j++;
        i++;
        if((i+1)%9==0)
        {
            if(counter%2 != (*(message+i)-'0'))
            {
                free(res);
                return "error";
            }
            counter=0;
            res=(char*)realloc(res,sizeof(char)*(j+8));
            i++;
        }
    }
    *(res+j)=0;
    return res;
}
int power(int a,int b)
{
    int res=1;
    while(b--)
        res*=a;
    return res;
}
char* convert(char* message)
{
    int i;
    int len=(int)strlen(message);
    int pow=7;
    char* res=(char*)malloc(sizeof(char)*len/8);
    int j=0;
    int acc=0;
    for(i=0;i<len;i++)
    {
        acc+=(*(message+i)-'0')*power(2,pow);
        pow--;
        if(pow==-1)
        {
            *(res+j)=acc;
            acc=0;
            j++;
            pow=7;
        }
    }
    return res;
}
int count(char* message)
{
    int len=(int)strlen(message);
    char *converted=malloc((sizeof(char)*len/8)-2);
    int curCount=0;
    int maxCount=0;
    char curChar;
    int i;
    int j;
    converted=convert(message)+1;
    for(i=0;i<((len/8)-2);i++)
    {
        curChar=converted[i];
        curCount=1;
        for(j=(i+1);j<len;j++)
        {
            if(converted[j]==curChar) 
                curCount++;
        }
        if(curCount>maxCount)
            maxCount=curCount;
    }
    return maxCount;
}
char** slide(char** messageBox)
{
    int rowCount;
    int columnCount=(int)strlen(messageBox[0]);
    int i,j,z,p;
    int kaydirmaSayisi=0;
    for(rowCount=0;*(messageBox+rowCount)!=NULL;rowCount++);
    for(i=1;i<rowCount;i++)
    {
        for(j=kaydirmaSayisi;j<columnCount;j++)
        {
            if(messageBox[i-1][j]=='1')break;
            kaydirmaSayisi++;
            for(z=0;z<rowCount;z++)
            {
                *(messageBox+z)=(char*)realloc(*(messageBox+z),sizeof(char)*(columnCount+1));
            }
            columnCount++;
            for(z=0;z<i;z++)
            {           
                messageBox[z][columnCount-1]='0';
                messageBox[z][columnCount]=0;
            }
            for(;z<rowCount;z++)
            {
                messageBox[z][columnCount]=0;
                for(p=(columnCount-2);p>=0;p--)
                    messageBox[z][p+1]=messageBox[z][p];
                messageBox[z][0]='0';
            }
        }
    }
    return messageBox;
}
char** intersect(char* message1, char* message2, int number)
{
    char** res=(char**)malloc(sizeof(char*));
    char* temp=(char*)malloc(sizeof(char)*number);
    int i;
    int j;
    int k;
    int kacKereDogru=0;
    int message1Len=strlen(message1);
    int message2Len=strlen(message2);
    int exists=0;
    static int rowCount=1;
    int columnCount=number;
    int p,l;
    *res=(char*)malloc(sizeof(char)*(number+1));
    for(i=0;i<(message1Len-number);i++)
    {
        for(j=0;j<(message2Len-number);j++)
        {
            while(*(message1+i+kacKereDogru)==*(message2+j+kacKereDogru))
            {
                kacKereDogru++;
                if(kacKereDogru==number)break;
            }
            if(kacKereDogru==number)
            {
                for(k=0;k<number;k++)
                {
                    *(temp+k)=*(message1+i+k);
                }
 
                for(p=0;p<(rowCount-1);p++)
                {
                    if(exists==1) break;
                    for(l=0;l<columnCount;l++)
                    {
                        if(*(*(res+p)+l)!=*(temp+l))
                        {
                            break;
                        }
                        if(l==(columnCount-1))
                            exists=1;
                    }
                }
                if(!exists)
                {
                    res=(char**)realloc(res,sizeof(char*)*(rowCount+1));
                    *(res+rowCount)=(char*)malloc(sizeof(char)*(number+1));                 
                    for(i=0;i<columnCount;i++)
                    {
                        *(*(res+rowCount-1)+i)=*(temp+i);
                    }
                    *(*(res+rowCount-1)+i)=0;
                    rowCount++;
                }
            }
            exists=0;
            kacKereDogru=0;
        }
    }
    *(res+rowCount)=NULL;
    return res;
}
char** split(char* message)
{
    char** res=(char**)malloc(sizeof(char*));
    int i=8;
    int k=0;
    int row=1;
    int p;
    int l=0;
    char* beof=(char*)malloc(sizeof(char)*9);
    beof="01111110";
    *res=(char*)malloc(sizeof(char)*1);
    while(*(message+i)!=0)
    {
        p=i;
        while(*(message+p)==*(beof+k))
        {
            p++;
            k++;
            if(k==8)break;
        }
        if(k==8)
        {
            row++;
            res=(char**)realloc(res,row);
            *(res+row-1)=(char*)malloc(sizeof(char)*1);
            l=0;
            i+=8;
        }
        else
        {
            *(*(res+row-1)+l)=*(message+i);         
            l++;
            i++;
            *(res+row-1)=(char*)realloc(*(res+row-1),l+1);
            *(*(res+row-1)+l)=0;
        }
        k=0;
    }
    *(res+row)=NULL;
    return res;
}
void execute()
{
    /*printf("%s",encode("011111101111010001111110"));*/
 
    /*printf("%s",decode("011111100111101001011111100"));
    printf("%s",decode("011111110111101001011111100"));*/
 
    /*printf("%s",convert("011111100100011101001111010011110100010000100000010011000101010101000011010010110010000101111110"));*/
 
    /*printf("%d\n",count("0111111001001000010011110100110001001100010110010101011101001111010011110100010001111110"));*/ /*~HOLLYWOOD~*/
    /*printf("%d\n",count("011111100100011101001111010011110100010000100000010011000101010101000011010010110010000101111110"));*/ /*~GOOD LUCK~*/
     
    /******************************************/
    /**********slide deneme*********/
    /*char** asd=malloc(sizeof(char*)*4);
    asd[0]=(char*)malloc(sizeof(char)*6);
    asd[1]=(char*)malloc(sizeof(char)*6);
    asd[2]=(char*)malloc(sizeof(char)*6);
    asd[3]=(char*)malloc(sizeof(char)*6);
    strcpy(asd[0],"001011");
    strcpy(asd[1],"110111");
    strcpy(asd[2],"010101");
    strcpy(asd[3],"110001");
    asd=slide(asd);
    int rowCount;
    int columnCount=strlen(asd[0]);
    for(rowCount=0;*(asd+rowCount)!=NULL;rowCount++);
    int i,j;
    for(i=0;i<rowCount;i++)
    {
        for(j=0;j<columnCount;j++)
        {
            printf("%c",asd[i][j]);
        }
        printf("\n");
    }*/
 
    /**************intersect DENEMEE************/
    /*
    int i,j;
    char** inter=(char**)malloc(sizeof(char*)*4);
    for(i=0;i<4;i++)
    {
        *(inter+i)=(char*)malloc(sizeof(char)*5);
    }
    inter=intersect("10001101111010000000100", "11000101", 4);
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            printf("%c",inter[i][j]);
        }
        printf("\n");
    }
    */
 
    /*************************************************/
    /*************split DENEME*************************/
    
    char **asd=(char**)malloc(sizeof(char*)*4);
    int i;
    int count;
    asd=split("0111111010001101111010000000100011111101100010101111110111000101001111110");
    for(count=0;asd[count]!=NULL;count++);
    for(i=0;i<count;i++)
    {
        printf("%s\n",asd[i]);
    }
}
int main()
{
    execute();
    return 0;
}
