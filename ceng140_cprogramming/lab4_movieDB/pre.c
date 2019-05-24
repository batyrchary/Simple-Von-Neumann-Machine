#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct movie
{
    char name[100];
    float rating;
    int year;
    int duration;
    struct movie *next;
};
int main()
{
    int year;
    float rating;
    char input[20];
    struct movie *first=malloc(sizeof(struct movie));
    while(1)
    {
        scanf("%s",input);
        if(strcmp(input,"FINISH")==0)
        {
            break;
        }
        if(strcmp(input,"ADD")==0)
        {
            struct movie *new=malloc(sizeof(struct movie)),*trial;
            scanf("%s %f %d %d",new->name,&new->rating,&new->year,&new->duration);
            for(trial=first;trial->next!=NULL;trial=trial->next);
            trial->next=new;
        }
        if(strcmp(input,"GETALL")==0)
        {  
            struct movie *trial;
            for(trial=first->next;trial!=NULL;trial=trial->next)
            {
                printf("%s %.1f %d %d\n",trial->name,trial->rating,trial->year,trial->duration);
            }
        }
        if(strcmp(input,"DELETEYEAR")==0)
        {
            struct movie *trial;
            scanf("%d",&year);
            for(trial=first;trial!=NULL;trial=trial->next)
            {
                while(trial->next!=NULL && trial->next->year==year)
                {
                    trial->next=trial->next->next;
                }
            }
        }
        if(strcmp(input,"CHANGERATING")==0)
        {
            struct movie *trial;
            scanf("%s %f",input,&rating);
            for(trial=first->next;trial!=NULL;trial=trial->next)
            {
                if(strcmp(input,trial->name)==0)
                {
                    trial->rating=rating;
                }
            }
        }
    }
    return 0;
}
