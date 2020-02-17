/*
 * 数独（ナンバープレース）を解く
 *
 */
#include <stdio.h>

#define BIT(n) (1 << (n-1))
#define POS(x,y) (x + y*9)
#define BOXPOS(x,y) (x/3 + (y/3)*3)

int width[9], height[9], box[9];

#if 1
int board[9*9] = {
	4,0,0, 0,1,0, 0,0,5,
	0,0,1, 0,0,0, 2,0,0,
	0,2,3, 5,0,8, 1,4,0,

	0,3,0, 1,2,4, 0,7,0,
	1,0,0, 3,5,0, 0,0,6,
	0,5,0, 0,0,0, 0,1,0,

	0,1,7, 6,0,0, 4,5,0,
	0,0,6, 9,0,5, 8,0,0,
	3,0,0, 0,8,0, 0,0,2,
};
#elif 0
int board[9*9] = {
	1,0,0, 0,3,0, 0,0,2,
	0,3,0, 7,1,5, 0,8,0,
	0,0,4, 0,0,0, 6,0,0,
	
	0,0,5, 0,0,2, 3,0,0,
	0,2,6, 0,0,0, 8,7,0,
	0,0,8, 0,4,0, 0,0,0,
	
	0,0,0, 9,0,4, 0,3,0,
	0,6,3, 0,2,0, 0,4,0,
	2,0,0, 0,0,0, 0,0,1,
};
#else
int board[9*9] = {
	0,0,0, 0,0,0, 0,0,0,
	0,1,9, 0,2,8, 0,0,0,
	0,8,4, 0,1,7, 0,0,0,
	
	0,0,8, 6,0,9, 1,0,0,
	0,0,1, 0,0,2, 3,0,0,
	3,6,0, 1,8,0, 0,0,0,
	
	1,7,0, 5,6,0, 0,0,0,
	0,0,0, 0,0,0, 0,2,1,
	0,0,0, 0,0,0, 0,4,6,	
};
#endif

int count;


void found(void)
{
	int x, y, c;

	count++;

	printf("No.%d\n", count);

	for (y = 0 ; y < 9 ; y++) {
		for (x = 0 ; x < 9 ; x++) {
			c = board[POS(x,y)];
			printf("%d ", c);
		}
		printf("\n");
	}
	printf("\n");
}


void sub(void)
{
	int x, y, n, pos;

	for (pos = 0 ; pos < 9*9 ; pos++) {
		if (board[pos] == 0)
			break;
	}
	if (pos >= 9*9) {  /* 解 */
		found();
		return;
	}

	/* 空きコマが見つかった */
	x = pos % 9;
	y = pos / 9;

	for (n = 1 ; n <= 9 ; n++) {  /* 数値を置いてみる */
		if (width[x] & BIT(n))
			continue;
		if (height[y] & BIT(n))
			continue;
		if (box[BOXPOS(x,y)] & BIT(n))
			continue;

		width[x] |= BIT(n);
		height[y] |= BIT(n);
		box[BOXPOS(x,y)] |= BIT(n);
		board[POS(x,y)] = n;

		sub();

		board[POS(x,y)] = 0;
		width[x] &= ~BIT(n);
		height[y] &= ~BIT(n);
		box[BOXPOS(x,y)] &= ~BIT(n);
	}
}

void init(void)
{
	int x, y, c;

	/* 縦方向のフラグを作る */
	for (x = 0 ; x < 9 ; x++) {
		for (y = 0 ; y < 9 ; y++) {
			c = board[POS(x,y)];
			if (c > 0) {
				width[x] |= BIT(c);
			}
		}
	}

	/* 横方向のフラグを作る */
	for (y = 0 ; y < 9 ; y++) {
		for (x = 0 ; x < 9 ; x++) {
			c = board[POS(x,y)];
			if (c > 0) {
				height[y] |= BIT(c);
			}
		}
	}

	/* 3×3領域のフラグを作る */
	for (x = 0 ; x < 9 ; x++) {
		for (y = 0 ; y < 9 ; y++) {
			c = board[POS(x, y)];
			box[BOXPOS(x,y)] |= BIT(c);
		}
	}
}

int main(void)
{
	init();
	sub();

	return 0;
}


