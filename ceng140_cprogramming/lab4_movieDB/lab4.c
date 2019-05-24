#include <stdio.h>
#include <string.h>


struct movie {
	char name[20];
	float rating;
	int year;
	int duration;
	struct movie* next;
};

void getName(struct movie* mv) {
	char c;
	int i=0;
	c = getchar();		
	while(1) {
		c = getchar();
		if(c==' ') break;		
		mv->name[i] = c;
		i++;
	}
}

float pwr (int base, float n) {
	float i, result = 1;
	for(i=0; i<n; i++) result*= base;
	return result;
}

void getRating(struct movie* mv) {
	char c;	
	float f = 0;
	float stage = 0;
	while(1) {
		c = getchar();
		if(c==' ') break;
		if(c=='.') {stage++; continue;}
		if(stage==0) {f*=10; f=f+c-48;}
		if(stage>0) {f=f+ (c-48)/pwr(10,stage);}		
	}
	mv->rating = f;
}


void getYear(struct movie* mv) {
	char c;	
	int y = 0;
	while(1) {
		c = getchar();
		if(c==' ') break;
		y*=10; y=y+c-48;
	}
	mv->year = y;
}

void getDuration(struct movie* mv) {
	char c;	
	int d = 0;
	while(1) {
		c = getchar();
		if(c=='\n') break;
		d*=10; d=d+c-48;
	}
	mv->duration = d;
}

int getDeleteYear() {
	char c;	
	int y = 0;
		c = getchar();
	while(1) {
		c = getchar();
		if(c =='\n') break;
		y*=10; y=y+c-48;
	}
	return y;
}


char* getChangeRatingName() {
	char c;
	char* name = (char*) malloc (21 * sizeof(char));
	int i=0;
		c = getchar();		

	while(1) {
		c = getchar();	
		if(c==' ') break;	
		name[i] = c;
		i++;
	}
	return name;
}


float getChangeRatingRating() {
	char c;	
	float f = 0;
	float stage = 0;	
	while(1) {
		c = getchar();
		if(c=='\n') break;
		if(c=='.') {stage++; continue;}
		if(stage==0) {f*=10; f=f+c-48;}
		if(stage>0) {f=f+ (c-48)/pwr(10,stage);}		
	}
	return f;
}


int main() {
	
	struct movie* first;
	struct movie* last;	
	int size = 0;	
	
	while(1){
		char operation[20];
		scanf("%s", operation);
		
		if(strcmp(operation,"FINISH\0") == 0) {
			break;
		} else
		if(strcmp(operation,"ADD\0") == 0) {
			struct movie* newMovie = (struct movie*) malloc (sizeof(struct movie));
			
			getName(newMovie);
//			printf("%s\n", newMovie->name);				
			
			getRating(newMovie);
//			printf("%1f\n", newMovie->rating);			
	
			getYear(newMovie);
//			printf("%d\n", newMovie->year);			

			getDuration(newMovie);
//			printf("%d\n", newMovie->duration);			

			if(size==0) {
				first = newMovie;
			} else {
				last->next = newMovie;
			}
			last = newMovie;
			size++;
			
		} else
		if(strcmp(operation,"GETALL\0") == 0) {
			int i;
			struct movie* temp = first;
			for(i=0; i<size; i++) {
				printf ("%s %.1f %d %d\n", temp->name, temp->rating,temp->year,temp->duration);
				temp = temp->next;  
			}
		} else
		if(strcmp(operation,"DELETEYEAR\0") == 0) {
			int dYear = getDeleteYear();
		//	printf("%d\n", dYear);		
		
			while(1) {
				struct movie* temp = first;
				if(temp->year == dYear) {
					first = first->next;
					size--;
					if(size==0) {
						first = NULL;
						break;					
					}
				} else { break; }
			}			
			
			if(size>1) {
				struct movie* temp1 = first;
				struct movie* temp2 = first->next;
				int i, firstSize = size;

				for(i=1; i<firstSize; i++) {
					if(temp2->year == dYear) {
						temp1->next = temp2->next;
						temp2 = temp2->next;
						size--;
						if(size==0) {
							first = NULL;
							break;					
						}
					} else {
						temp2 = temp2->next;
						temp1 = temp2;
					}
				}
			}	
		} else
		if(strcmp(operation,"CHANGERATING\0") == 0) {
			char * name = getChangeRatingName();
		//	printf("%s\n", name);			
			float f = getChangeRatingRating();
		//	printf("%.1f\n", f);			
			struct movie* temp = first;
			int i;			
			for(i=0; i<size; i++) {
				if(strcmp(temp->name,name) == 0) {
					temp->rating = f;
				}
				temp = temp->next;
			}
		}
	}
		
	
	
	return 50;

}


