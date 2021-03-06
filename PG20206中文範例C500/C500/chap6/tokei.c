/*
 * 在指針式時鐘裡，指針在一天內會重疊幾次呢？
 * 假設時針、分針、秒針都是以1°為單位移動。
 * 另外，時間由00:00:00開始起算，
 * 此時的重疊不列入計算。
 */
#include <stdio.h>

int main(void)
{
	/* 120秒鐘之內，指針移動的角度 */
	int hour_angle = 120 * 30 / 3600;  /* 時針在1小時內移動30° */
	int min_angle = 120 * 6 / 60;      /* 分針在1分鐘內移動6° */
	int sec_angle = 120 * 6;           /* 秒針在1秒鐘內移動6° */ 
	int t, h, m, s;
	int count = 0;

	//printf("%d %d %d\n", hour_angle, min_angle, sec_angle);

	/* 00:00:01�`23:59:59���� */
	for (t = 1 ; t < 24*60*60 ; t++) {
		h = (hour_angle * t/120) % 360;
		m = (min_angle * t/120) % 360 ;
		s = (sec_angle * t/120) % 360;

		if (h == m && m == s) {
			printf("在%d秒(%d小時)後: 時針 %d 分針 %d 秒針 %d\n", t, t/3600, h, m, s);
			count++;
		}
	}

	printf("會重疊 %d 次\n", count);

	return 0;
}

