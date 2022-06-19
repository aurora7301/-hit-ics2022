#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define blockSize 160
auto img = new long[19200][10800];
auto ans = new long[19200][10800];
void original();
void original_shift();
void only_loopUnroll();
void only_partition();
void loopUnroll_partition();
int main() {
	for (int i = 0; i < 1920; i++) {
		for (int j = 0; j < 1080; j++) {
			img[i][j] = rand();
		}
	}
	original();
	original_shift();
	only_loopUnroll();
	only_partition();
	loopUnroll_partition();
	return 0;
}
void original() {
	clock_t start_t = clock();
	for (int t = 0; t < 1000; t++) {//计算1000次
		for (int i = 1; i <= 1918; i++) {
			;
			for (int j = 1; j <= 1078; j++) {
				ans[i][j] = (img[i - 1][j] + img[i + 1][j] + img[i][j + 1] + img[i][j - 1]) /2;
			}
		}
	}
	clock_t end_t = clock();
	printf("original  cost time :%d (ms)\n", end_t - start_t);
}

void original_shift() {
	clock_t start_t = clock();
	for (int t = 0; t < 1000; t++) {//计算1000次
		for (int i = 1; i <= 1918; i++) {
			;
			for (int j = 1; j <= 1078; j++) {
				ans[i][j] = (img[i - 1][j] + img[i + 1][j] + img[i][j + 1] + img[i][j - 1]) >> 1;
			}
		}
	}
	clock_t end_t = clock();
	printf("original +shift(>>)  cost time :%d (ms)\n", end_t - start_t);
}
void only_loopUnroll() {
	clock_t start_t = clock();
	for (int t = 0; t < 1000; t++) {
		for (int i = 1; i <= 1918; i++) {
			int j = 1;
			for (; j + 8 <= 1078; j += 8) {
				int j_0 = img[i][j], j_1 = img[i][j + 1], j_2 = img[i][j + 2], j_3 = img[i][j + 3];
				int j_4 = img[i][j + 4], j_5 = img[i][j + 5], j_6 = img[i][j + 6], j_7 = img[i][j + 7];
				ans[i][j] = (img[i + 1][j] + img[i - 1][j] + j_1 + img[i][j - 1]) >> 2;
				ans[i][j + 1] = (img[i + 1][j] + img[i - 1][j] + j_2 + j_0) >> 2;
				ans[i][j + 2] = (img[i + 1][j] + img[i - 1][j] + j_3 + j_1) >> 2;
				ans[i][j + 3] = (img[i + 1][j] + img[i - 1][j] + j_4 + j_2) >> 2;
				ans[i][j + 4] = (img[i + 1][j] + img[i - 1][j] + j_5 + j_3) >> 2;
				ans[i][j + 5] = (img[i + 1][j] + img[i - 1][j] + j_6 + j_4) >> 2;
				ans[i][j + 6] = (img[i + 1][j] + img[i - 1][j] + j_7 + j_5) >> 2;
				ans[i][j + 7] = (img[i + 1][j] + img[i - 1][j] + img[i][j + 8] + j_6) >> 2;
			}
			for (; j <= 1078; j++) {
				ans[i][j] = (img[i + 1][j] + img[i - 1][j] + img[i][j + 1] + img[i][j - 1]) >> 2;
			}
		}
	}
	clock_t end_t = clock();
	printf("only_loopUnroll cost time :%d (ms)\n", end_t - start_t);
}
void loopUnroll_partition() {
	clock_t start_t = clock();
	for (int t = 0; t < 1000; t++) {
		int i = 1;
		int j = 1;
		for (; i + blockSize <= 1918; i += blockSize) {
			j = 1;
			for (; j + blockSize <= 1078; j += blockSize) {
				//处理小块
				for (int i1 = i; i1 < i + blockSize; i1++) {
					//循环展开 ，先算整对
					int j1 = j;
					for (; j1 + 8 <= j + blockSize - 1; j1 += 8) {
						int j1_0 = img[i1][j1], j1_1 = img[i1][j1 + 1], j1_2 = img[i1][j1 + 2], j1_3 = img[i1][j1 + 3];
						int j1_4 = img[i1][j1 + 4], j1_5 = img[i1][j1 + 5], j1_6 = img[i1][j1 + 6], j1_7 = img[i1][j1 + 7];
						ans[i1][j1] = (img[i1 + 1][j1] + img[i1 - 1][j1] + j1_1 + img[i1][j1 - 1]) >> 2;
						ans[i1][j1 + 1] = (img[i1 + 1][j1] + img[i1 - 1][j1] + j1_2 + j1_0) >> 2;
						ans[i1][j1 + 2] = (img[i1 + 1][j1] + img[i1 - 1][j1] + j1_3 + j1_1) >> 2;
						ans[i1][j1 + 3] = (img[i1 + 1][j1] + img[i1 - 1][j1] + j1_4 + j1_2) >> 2;
						ans[i1][j1 + 4] = (img[i1 + 1][j1] + img[i1 - 1][j1] + j1_5 + j1_3) >> 2;
						ans[i1][j1 + 5] = (img[i1 + 1][j1] + img[i1 - 1][j1] + j1_6 + j1_4) >> 2;
						ans[i1][j1 + 6] = (img[i1 + 1][j1] + img[i1 - 1][j1] + j1_7 + j1_5) >> 2;
						ans[i1][j1 + 7] = (img[i1 + 1][j1] + img[i1 - 1][j1] + img[i1][j1 + 8] + j1_6) >> 2;
					}
					for (; j1 <= j + blockSize - 1; j1++) {
						ans[i1][j1] = (img[i1 + 1][j1] + img[i1 - 1][j1] + img[i1][j1 + 1] + img[i1][j1 - 1]) >> 2;
					}
				}
			}
		}
		int i_store = i, j_store = j;
		//计算剩余边缘部分,先算下方
		for (int i = i_store; i <= 1917; i++) {//第i行
			for (int k = 1; k <= 1078; k++) {//第k列
				ans[i][k] = (img[i][k + 1] + img[i][k - 1] + img[i + 1][k] + img[i - 1][k]) >> 2;
			}
		}
		for (int k = 1; k <= i_store - 1; k++) {//行
			for (int z = j_store; z <= 1078; z++) {//列
				ans[k][z] = (img[k][z + 1] + img[k][z - 1] + img[k - 1][z] + img[k + 1][z]) >> 2;
			}
		}
	}
	clock_t end_t = clock();
	printf(" loopUnroll_partition   cost time :%d (ms)\n", end_t - start_t);
}
void only_partition(){
	clock_t start_t = clock();
	for (int t = 0; t < 1000; t++) {
		int i = 1;
		int j = 1;
		for (; i + blockSize <= 1918; i += blockSize) {
			j = 1;
			for (; j + blockSize <= 1078; j += blockSize) {
				//处理小块
				for (int i1 = i; i1 < i + blockSize; i1++) {
					//循环展开 ，先算整对
					for (int j1=1; j1 <= j + blockSize - 1; j1 ++) {
						ans[i1][j1] = (img[i1 + 1][j1] + img[i1 - 1][j1] + img[i1][j1+1] + img[i1][j1 - 1]) >> 2;
						
					}
				}
			}
		}
		int i_store = i, j_store = j;
		//计算剩余边缘部分,先算下方
		for (int i = i_store; i <= 1917; i++) {//第i行
			for (int k = 1; k <= 1078; k++) {//第k列
				ans[i][k] = (img[i][k + 1] + img[i][k - 1] + img[i + 1][k] + img[i - 1][k]) >> 2;
			}
		}
		for (int k = 1; k <= i_store - 1; k++) {//行
			for (int z = j_store; z <= 1078; z++) {//列
				ans[k][z] = (img[k][z + 1] + img[k][z - 1] + img[k - 1][z] + img[k + 1][z]) >> 2;
			}
		}
	}
	clock_t end_t = clock();
	printf(" only_partition   cost time :%d (ms)\n", end_t - start_t);
}