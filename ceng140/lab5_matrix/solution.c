#include <stdio.h>
#include "lab.h"

/* 1 */
void readRowByRow(void){
	int i,row,j;
	for( i=0; i<N; i++ ){
		scanf("%d",&row);
		for(j=0; j<N; j++)
			scanf("%d", &matrix[row][j]);
	}
}

/* 2 */
void printColumnByColumn(void){
	int i,j;
	for(i=0; i<N; i++){
		for(j=0; j<N; j++)
			printf("%d ",matrix[j][i]);
		printf("\n");
	}
}

/* 3 */
void printSnakelike(void){
	int i,j;
	for(i=0; i<N; i++){
		if( i%2 ){
			for(j=N-1; j>=0; j--)
				printf("%d ", matrix[i][j]);
		}else{
			for(j=0; j<N; j++)
				printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

/* 4 */
int rowSum(int rowNumber) {
	int i, sum=0;
	for (i=0; i<N; i++) {
		sum += matrix[rowNumber][i];
	}
	return sum;
}

/* 5 */
void printEachSum(void) {
	int i;
	for (i=0; i<N; i++) {
		printf("%d\n", rowSum(i));
	}
}

/* 6 */
void transpose(void) {
	int i, j, tmp;
	for (i=0; i<N; i++) {
		for (j=0; j<i; j++) {
			tmp = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = tmp;
		}
	}
}

int execute(){
	printf("Extra Lab-1 Section-1\n");
	return 0;
}

