#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define blockSize 540//分块大小
long img[1920][1080];
long ans[1920][1080];
int main() {
	for (int i = 0; i < 1920; i++) {
		for (int j = 0; j < 1080; j++) {
			img[i][j] = rand();
		}
	}
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
					for (; j1 + 8<= j + blockSize - 1; j1 +=8) {
						int j1_0 = img[i1][j1],j1_1=img[i1][j1+1],j1_2=img[i1][j1+2],j1_3=img[i1][j1+3];
						int j1_4 = img[i1][j1+4], j1_5 = img[i1][j1 + 5], j1_6 = img[i1][j1 + 6], j1_7 = img[i1][j1 + 7];
						ans[i1][j1]   = (img[i1 + 1][j1] + img[i1 - 1][j1] + j1_1 + img[i1][j1 - 1]) >> 2;
						ans[i1][j1+1] = (img[i1 + 1][j1] + img[i1 - 1][j1] + j1_2 + j1_0) >> 2;
						ans[i1][j1+2] = (img[i1 + 1][j1] + img[i1 - 1][j1] + j1_3 + j1_1) >> 2;
						ans[i1][j1+3] = (img[i1 + 1][j1] + img[i1 - 1][j1] + j1_4 + j1_2) >> 2;
						ans[i1][j1+4] = (img[i1 + 1][j1] + img[i1 - 1][j1] + j1_5+j1_3) >> 2;
						ans[i1][j1+5] = (img[i1 + 1][j1] + img[i1 - 1][j1] + j1_6+j1_4) >> 2;
						ans[i1][j1+6] = (img[i1 + 1][j1] + img[i1 - 1][j1] + j1_7+j1_5) >> 2;
						ans[i1][j1+7] = (img[i1 + 1][j1] + img[i1 - 1][j1] + img[i1][j1 + 8] + j1_6)>> 2;
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
	printf("cost time :%d (ms)\n", end_t - start_t);
	return 0;
}