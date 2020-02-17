/*
 * ¦b«ü°w¦¡®ÉÄÁ¸Ì¡A«ü°w¦b¤@¤Ñ¤º·|­«Å|´X¦¸©O¡H
 * °²³]®É°w¡B¤À°w¡B¬í°w³£¬O¥H1¢X¬°³æ¦ì²¾°Ê¡C
 * ¥t¥~¡A®É¶¡¥Ñ00:00:00¶}©l°_ºâ¡A
 * ¦¹®Éªº­«Å|¤£¦C¤J­pºâ¡C
 */
#include <stdio.h>

int main(void)
{
	/* 120¬íÄÁ¤§¤º¡A«ü°w²¾°Êªº¨¤«× */
	int hour_angle = 120 * 30 / 3600;  /* ®É°w¦b1¤p®É¤º²¾°Ê30¢X */
	int min_angle = 120 * 6 / 60;      /* ¤À°w¦b1¤ÀÄÁ¤º²¾°Ê6¢X */
	int sec_angle = 120 * 6;           /* ¬í°w¦b1¬íÄÁ¤º²¾°Ê6¢X */ 
	int t, h, m, s;
	int count = 0;

	//printf("%d %d %d\n", hour_angle, min_angle, sec_angle);

	/* 00:00:01`23:59:59‚Ü‚Å */
	for (t = 1 ; t < 24*60*60 ; t++) {
		h = (hour_angle * t/120) % 360;
		m = (min_angle * t/120) % 360 ;
		s = (sec_angle * t/120) % 360;

		if (h == m && m == s) {
			printf("¦b%d¬í(%d¤p®É)«á: ®É°w %d ¤À°w %d ¬í°w %d\n", t, t/3600, h, m, s);
			count++;
		}
	}

	printf("·|­«Å| %d ¦¸\n", count);

	return 0;
}

