#include<stdio.h>
#include<stdlib.h>
#define numpage 5
#define psize 6
char book[numpage][psize]={{'a', 'b', ' ', 'd', 'e','q'}, {'A', ' ', 'C', 'D', 'E','q'}, {'a', 'b', 'c', 'd', 'e','q'}, {'A', 'B', 'C', 'D', 'E','q'}, {'a', 'b', 'c', 'd', 'e','q'}};

void print_book()
{
    int i,j,k;
    for(i=0;i<numpage;i++)
    {
       /* for(k=0;k<i;k++)
        {
            printf(".");
        }
        */
        for(j=0;j<psize;j++)
        {
            printf("%c",book[i][j]);
        }
        printf("\n");
    }
}

int count_char(char* c)
{
    int i,j, ret=0;
    for(i=0;i<numpage;i++)
    {
        for(j=0;j<psize;j++)
        {
            if(book[i][j]==*c)
                ret++;
        }
    }
    return ret;
}

void compact()
{
   char* res=(char*)malloc(sizeof(char)*psize*numpage);
    int n,p,k=0,l=0;
    for(n=0;n<numpage;n++)
        for(p=0;p<psize;p++)
            if(book[n][p]!=*" ")
            {
                *(res+k)=book[n][p];
                k++;
            } 
    
    *(res+k)='\0';
    k=0;

    for(n=0;n<numpage;n++)
    {
        for(p=0;p<psize;p++)
        {
            book[n][p]=*(res+k);
            k++;
        }
        book[n][p]='\0';
    }
    free(res);
    
}

int word_count()
{
    int i;
	int j=1;
	int wc=0;
	for(i=0;i<numpage;i++)
	{
		while(j!=psize)
		{
			if(book[i][j]==' ' && book[i][j-1]!=' ')
				wc++;
			j++;
		}
		if(book[i][j-1]!=' ')
			wc++;
		j=1;
	}
	return wc;
}


void find_str(char* word, int* result)
{
    int i;
	int j;
	int flag=0;
	for(i=0;i<numpage;i++)
	{
		if(flag==1)break;
		for(j=0;j<psize;j++)
		{
			if(book[i][j]==word[0])
			{
				int k=1;
				int l=j+1;
				if(word[k]=='\0')
				{
					*result=i*psize+j;
					flag=1;
					break;
				}
				while(word[k]==book[i][l])
				{
					k++;
					l++;
					if(word[k]=='\0')
					{
						*result=i*psize+j;
						flag=1;
						break;
					}
				}
			}
		}
	}
}


void erase_uppercase()
{
    char* res=(char*)malloc(sizeof(char)*psize*numpage);
    int n,p,k=0,l=0;
    for(n=0;n<numpage;n++)
        for(p=0;p<psize;p++)
            if(book[n][p]<65 || book[n][p]>90)
            {
                *(res+k)=book[n][p];
                k++;
            }

    while(k%(numpage*psize)!=0)
    {
    
        *(res+k)=' ';
        k++;
    }
    *(res+k)='\0';
    k=0;

    for(n=0;n<numpage;n++)
    {
        for(p=0;p<psize;p++)
        {
            book[n][p]=*(res+k);
            k++;
        }
        book[n][p]='\0';
    }
    free(res);
}


void execute()
{

printf("%s\n","--------------PRINT---------------");
    print_book();
printf("%s\n","----------------------------------");
printf("%s\n","-------------COUNT----------------");
    char chr = 'c';
    char* chrp = &chr;
    int count=count_char(chrp);
    printf("%d\n",count);
printf("%s\n","----------------------------------");
printf("%s\n","----------WORDCOUNT---------------");
    count=word_count();
    printf("%d\n",count);

printf("%s\n","----------------------------------");
printf("%s\n","----------FINDWORD---------------");
    int result;
    find_str("DE", &result);
    printf("%d\n",result);


printf("%s\n","----------------------------------");
printf("%s\n","----------COMPACT-------------");
    print_book();
    printf("%s\n","------------");  
    compact();
    print_book();

printf("%s\n","----------------------------------");
printf("%s\n","----------ERASEUPPER-------------");
    print_book();
    printf("%s\n","------------");  
    erase_uppercase();
    print_book();
}



int main()
{
    execute();
}
