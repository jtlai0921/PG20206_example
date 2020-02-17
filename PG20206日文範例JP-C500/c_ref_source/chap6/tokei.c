/*
 * �A�i���O���v�ɂ�����1���̂������v�̐j�͉���d�Ȃ邩�B
 * �������A���j�E���j�E�b�j��1�����݂œ������̂Ƃ���B
 * �܂��A����J�n��00:00:00�Ƃ��A���Y�����ɂ�����d�Ȃ��
 * �����Ȃ����̂Ƃ���B
 */
#include <stdio.h>

int main(void)
{
	/* 120�b�Ԃ�����ɐj�̓����p�x */
	int hour_angle = 120 * 30 / 3600;  /* ���j��1���Ԃ�30������ */ 
	int min_angle = 120 * 6 / 60;      /* ���j��1���Ԃ�6������ */ 
	int sec_angle = 120 * 6;           /* �b�j��1�b�Ԃ�6������ */ 
	int t, h, m, s;
	int count = 0;

	//printf("%d %d %d\n", hour_angle, min_angle, sec_angle);

	/* 00:00:01�`23:59:59�܂� */
	for (t = 1 ; t < 24*60*60 ; t++) {
		h = (hour_angle * t/120) % 360;
		m = (min_angle * t/120) % 360 ;
		s = (sec_angle * t/120) % 360;

		if (h == m && m == s) {
			printf("%d�b(%d����)��F ���j %d ���j %d �b�j %d\n", t, t/3600, h, m, s);
			count++;
		}
	}

	printf("%d ��d�Ȃ�\n", count);

	return 0;
}

