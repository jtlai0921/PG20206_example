/*
 * magic.c
 */
#include <stdio.h>
#include <stdlib.h>

#define N 3
#define SUM (N*N*N+N)/2
#define MAX N*N
#define CHECK_IN(n) {if (use[n]) continue; use[n] = 1;}
#define CHECK_OUT(n) {use[n] = 0;}
#define CHECK_SUM(a,b,c) {if ((a+b+c) != SUM) continue;}

/* �w�ϥμƦr���X�� */
int use[MAX + 1];

/* �]�k��}�p�U��
�z�w�s�w�s�w�{
�xa �x b�xc �x
�u�w�q�w�q�w�t
�xd �xe �xf �x
�u�w�q�w�q�w�t
�xg �xh �xi  �x
�|�w�r�w�r�w�}
 */

int a, b, c, d, e, f, g, h, i;

/* �Ѫ��Ӽ� */
int count;


void found(void)
{
	count++;

	printf("No. %d\n", count);

	printf("�z�w�s�w�s�w�{\n"
	  	   "�x%2d�x%2d�x%2d�x\n"
           "�u�w�q�w�q�w�t\n"
	  	   "�x%2d�x%2d�x%2d�x\n"
           "�u�w�q�w�q�w�t\n"
	  	   "�x%2d�x%2d�x%2d�x\n"
           "�|�w�r�w�r�w�}\n", 
		   a, b, c, 
		   d, e, f, 
		   g, h, i); 
		   
}

void sub3(void)
{
	for (i = 1 ; i <= MAX ; i++) {  
		CHECK_SUM(a,e,i);
		CHECK_IN(i);

		for (f = 1 ; f <= MAX ; f++) {
			CHECK_SUM(c,f,i);
			CHECK_SUM(d,e,f);
			CHECK_IN(f);

			for (h = 1 ; h <= MAX ; h++) { 
				CHECK_SUM(g,h,i);
				CHECK_SUM(b,e,h);
				CHECK_IN(h);

				found();

				CHECK_OUT(h);
			}

			CHECK_OUT(f);
		}

		CHECK_OUT(i);
	}

}


void sub2(void)
{
	for (d = 1 ; d <= MAX ; d++) {
		CHECK_IN(d);

		for (g = 1 ; g <= MAX ; g++) {  
			CHECK_SUM(a,d,g);
			CHECK_IN(g);

			for (e = 1 ; e <= MAX ; e++) { 
				CHECK_SUM(c,e,g);
				CHECK_IN(e);

				sub3();

				CHECK_OUT(e);
			}

			CHECK_OUT(g);
		}

		CHECK_OUT(d);
	}

}


void sub(void)
{
	for (a = 1 ; a <= MAX ; a++) {
		CHECK_IN(a);

		for (b = 1 ; b <= MAX ; b++) {
			CHECK_IN(b);

			for (c = 1 ; c <= MAX ; c++) { 
				CHECK_SUM(a,b,c);
				CHECK_IN(c);

				sub2();

				CHECK_OUT(c);
			}

			CHECK_OUT(b);
		}

		CHECK_OUT(a);
	}

}

int main(void)
{
	sub();

    return 0;
}

