/*
 * アナログ時計において1日のうち時計の針は何回重なるか。
 * ただし、時針・分針・秒針は1°刻みで動くものとする。
 * また、測定開始は00:00:00とし、当該時刻における重なりは
 * 数えないものとする。
 */
#include <stdio.h>

int main(void)
{
	/* 120秒間あたりに針の動く角度 */
	int hour_angle = 120 * 30 / 3600;  /* 時針は1時間に30°動く */ 
	int min_angle = 120 * 6 / 60;      /* 分針は1分間に6°動く */ 
	int sec_angle = 120 * 6;           /* 秒針は1秒間に6°動く */ 
	int t, h, m, s;
	int count = 0;

	//printf("%d %d %d\n", hour_angle, min_angle, sec_angle);

	/* 00:00:01～23:59:59まで */
	for (t = 1 ; t < 24*60*60 ; t++) {
		h = (hour_angle * t/120) % 360;
		m = (min_angle * t/120) % 360 ;
		s = (sec_angle * t/120) % 360;

		if (h == m && m == s) {
			printf("%d秒(%d時間)後： 時針 %d 分針 %d 秒針 %d\n", t, t/3600, h, m, s);
			count++;
		}
	}

	printf("%d 回重なる\n", count);

	return 0;
}

