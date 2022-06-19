#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main() {
	//声明一个1920行1080列矩阵
	auto img=new long[1920][1080];
	auto ans = new long[1920][1080];
	for (int i = 0; i < 1920; i++) {
		for (int j = 0; j < 1080; j++) {
			img[i][j] = rand();
		}
	}
	clock_t start_t = clock();
	for (int t = 0; t < 1000; t++) {
		for (int i=1; i <= 1918; i ++){
			int j = 1;
				for (; j+8<= 1078; j += 8) {//factor是展开因子
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
				for (; j<= 1078; j++) {
						ans[i][j] = (img[i + 1][j] + img[i - 1][j] + img[i][j + 1] + img[i][j - 1]) >> 2;
				}
		}
	}
	clock_t end_t = clock();
	printf("cost time :%d (ms)\n", end_t - start_t);
	return 0;
}