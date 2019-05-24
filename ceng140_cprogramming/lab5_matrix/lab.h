#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#define N 10
#define EVALUATE 0

int matrix[N][N];

void readRowByRow(void);
void printColumnByColumn(void);
void printSnakelike(void);
int rowSum(int rowNumber);
void printEachSum(void);
void transpose(void);

int execute(void);

/* helper functions */
void __clear__(void){
	int i,j;
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			matrix[i][j] = 0;
}

void __printmatrix__(void){
	int i,j;
	for(i=0; i<N; i++){
		for(j=0; j<N; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
}

void __readmatrix__(void){
	int i,j;
	for( i=0; i<N; i++ ){
		for(j=0; j<N; j++)
			scanf("%d", &matrix[i][j]);
	}
}

/* entry point */
int main(void) {
	if (EVALUATE) {
		/*
		 * 0: exit
		 * 1: readRowByRow
		 * 2: printColumnByColumn
		 * 3: printSnakeline
		 * 4: rowSum
		 * 5: printEachSum
		 * 6: transpose
		 */
		int menu, index;
		scanf("%d" ,&menu);
		while (menu){
			if (menu == 0) {
				break;
			} else if (menu == 1){
				readRowByRow();
				__printmatrix__();
				__clear__();
			} else if (menu == 2){
				__readmatrix__();
				printColumnByColumn();
				__clear__();
			} else if (menu == 3) {
				__readmatrix__();
				printSnakelike();
				__clear__();
			} else if (menu == 4) {
				scanf("%d", &index);
				__readmatrix__();
				printf("%d\n", rowSum(index));
				__clear__();
			} else if (menu == 5) {
				__readmatrix__();
				printEachSum();
				__clear__();
			} else if (menu == 6) {
				__readmatrix__();
				transpose();
				__printmatrix__();
				__clear__();
			}
			scanf("%d", &menu);
		}
	} else {
		execute();
	}
	
	return 0;
}

