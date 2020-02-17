/*
 * �b���w�������̡A���w�b�@�Ѥ��|���|�X���O�H
 * ���]�ɰw�B���w�B��w���O�H1�X����첾�ʡC
 * �t�~�A�ɶ���00:00:00�}�l�_��A
 * ���ɪ����|���C�J�p��C
 */
#include <stdio.h>

int main(void)
{
	/* 120���������A���w���ʪ����� */
	int hour_angle = 120 * 30 / 3600;  /* �ɰw�b1�p�ɤ�����30�X */
	int min_angle = 120 * 6 / 60;      /* ���w�b1����������6�X */
	int sec_angle = 120 * 6;           /* ��w�b1����������6�X */ 
	int t, h, m, s;
	int count = 0;

	//printf("%d %d %d\n", hour_angle, min_angle, sec_angle);

	/* 00:00:01�`23:59:59�܂� */
	for (t = 1 ; t < 24*60*60 ; t++) {
		h = (hour_angle * t/120) % 360;
		m = (min_angle * t/120) % 360 ;
		s = (sec_angle * t/120) % 360;

		if (h == m && m == s) {
			printf("�b%d��(%d�p��)��: �ɰw %d ���w %d ��w %d\n", t, t/3600, h, m, s);
			count++;
		}
	}

	printf("�|���| %d ��\n", count);

	return 0;
}

