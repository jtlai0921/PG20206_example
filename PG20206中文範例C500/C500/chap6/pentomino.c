/*
 * pentomino.c - ¡u¤­¤è¶ôªºÅ]³N¤è¶ô¡v
 *
 * [how to compile]
 * >cl /O2 /nologo /W3 pentomino.c && pentomino
 *
 * Copyright (C)2003 YUTAKA
 * All rights reserved.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* ¦b6¡Ñ10ªº½L­±¤W©ñ¸m¦UºØ¹s¥ó(¦U¤@­Ó)¡C
 * ¦b¥kÃä©M¤U­±°µ¥XÀð¾À
 
	¡¼¡¼¡¼¡¼¡¼¡¼¡½
	¡¼¡¼¡¼¡¼¡¼¡¼¡½
	¡¼¡¼¡¼¡¼¡¼¡¼¡½
	¡¼¡¼¡¼¡¼¡¼¡¼¡½
	¡¼¡¼¡¼¡¼¡¼¡¼¡½
	¡¼¡¼¡¼¡¼¡¼¡¼¡½
	¡¼¡¼¡¼¡¼¡¼¡¼¡½
	¡¼¡¼¡¼¡¼¡¼¡¼¡½
	¡¼¡¼¡¼¡¼¡¼¡¼¡½
	¡¼¡¼¡¼¡¼¡¼¡¼¡½
	¡½¡½¡½¡½¡½¡½¡½
 */
#define WIDTH (6+1)        /* ½L­±ªº¾î¦V¼e«×+Àð¾À */
#define HEIGHT (10+1)      /* ½L­±ªºÁa¦V°ª«×+Àð¾À */
#define POS(x,y) ((x) + (y)*WIDTH)
#define WALL -1

#define BITS_PIECES 5   /* ¹s¥óªº²Õ¦¨­n¯À¼Æ */
#define PIECES 12       /* ¹s¥óªººØÃþ */

char pieces[PIECES][5*5] = {
	{  /* I«¬¤è¶ô */
	"*----"
	"*----"
	"*----"
	"*----"
	"*----"
	},
	{  /* Y«¬¤è¶ô */
	"*----"
	"**---"
	"*----"
	"*----"
	"-----"
	},
	{  /* P«¬¤è¶ô */
	"**---"
	"**---"
	"*----"
	"-----"
	"-----"
	},
	{  /* V«¬¤è¶ô */
	"*----"
	"*----"
	"***--"
	"-----"
	"-----"
	},
	{  /* W«¬¤è¶ô */
	"*----"
	"**---"
	"-**--"
	"-----"
	"-----"
	},
	{  /* L«¬¤è¶ô */
	"**---"
	"*----"
	"*----"
	"*----"
	"-----"
	},
	{  /* U«¬¤è¶ô */
	"**---"
	"*----"
	"**---"
	"-----"
	"-----"
	},
	{  /* N«¬¤è¶ô */
	"*----"
	"*----"
	"**---"
	"-*---"
	"-----"
	},
	{  /* F«¬¤è¶ô */
	"-*---"
	"-**--"
	"**---"
	"-----"
	"-----"
	},
	{  /* X«¬¤è¶ô */
	"-*---"
	"***--"
	"-*---"
	"-----"
	"-----"
	},
	{  /* T«¬¤è¶ô */
	"*----"
	"***--"
	"*----"
	"-----"
	"-----"
	},
	{  /* Z«¬¤è¶ô */
	"**---"
	"-*---"
	"-**--"
	"-----"
	"-----"
	},
};

int count_pieces[PIECES] = { 
	1, 1, 1, 1, 1,
	1, 1, 1, 1, 1,
	1, 1,
};
char face_pieces[PIECES] = { 'I', 'Y', 'P', 'V', 'W', 'L', 'U', 'N', 'F', 'X', 'T', 'Z' };

typedef struct {
	int x;
	int y;
}point_t;
point_t Point[PIECES][BITS_PIECES]; /* ¥ÎXY®y¼Ð­Èªí¥Üªº¹s¥ó¸ê®Æ */

typedef struct {
	int shape[8][BITS_PIECES];
	int n_shape;
}shape_t;
shape_t Shape[PIECES];    /* ¥Ñ°¾²¾¶q¨Óªí¥Üªº¹s¥ó¸ê®Æ(³Ì¦h8ºØ) */


int board[WIDTH*HEIGHT];
int put_count = 0;
int ans_cnt = 0;


void display_board(int *board)
{
	int x, y;
	char c;

	for (y = 0 ; y < HEIGHT-1 ; y++) {
		for (x = 0 ; x < WIDTH-1 ; x++) {
			c = board[POS(x,y)];
			printf("%c", c);
		}
		printf("\n");
	}
	printf("\n");
}

/* ·j´M³B²z */
void sub(int site)
{
	int recsite[BITS_PIECES];
	int i, j, k, tmp;
	
	if (put_count == PIECES) {  /* ¸Ñ */
		ans_cnt++;
		//display_board(board);
		return;
	}

	/* ¹Á¸Õsite¦ì¸m¬O§_¥i¥H©ñ¸m */
	for (k = 0 ; k < PIECES ; k++) {
		if (count_pieces[k] == 0)
			continue;

		count_pieces[k]--;

		for (i = 0; i < Shape[k].n_shape ; i++) {  /* ¹s¥óªºÃþ«¬ */
			for (j = 0 ; j < BITS_PIECES ; j++) {
				recsite[j] = site + Shape[k].shape[i][j];
				if (board[recsite[j]])  /* ªÅ®æ¤w³Q¨Ï¥Î */
					break;
			}
			if (j != BITS_PIECES) 
				continue;
			
			/* ©ñ¸m¹s¥ó */
			put_count++;
			for (j = 0 ; j < BITS_PIECES ; j++) {
				board[recsite[j]] = face_pieces[k];
			}
			tmp = site;
			while (board[++tmp] != 0)  /* §äªÅ®æ */
				;

			sub( tmp );  /* ¨ì¤U¤@­Ó·j´M¨BÆJ */

			/* §â¹s¥ó®³°_¨Ó */
			for (j = 0 ; j < BITS_PIECES ; j++) {
				board[recsite[j]] = 0;
			}
			put_count--;
		}

		count_pieces[k]++;
	}
}

void init_board(void)
{
	int x, y;
	
	for (y = 0 ; y < HEIGHT ; y++) {
		for (x = 0 ; x < WIDTH ; x++) {
			if (x == WIDTH - 1 || y == HEIGHT - 1) 
				board[POS(x,y)] = WALL;
			else
				board[POS(x,y)] = 0;
		}
	}
	board[POS(WIDTH-1,HEIGHT-1)] = 0;  /* ½Ã§L */
}

void shape_disp(shape_t s)
{
	int i, j;
	
	printf("%d pattern(s)\n", s.n_shape);
	for (i = 0 ; i < s.n_shape; i++) {
		for (j = 0 ; j < BITS_PIECES ; j++) 
			printf("%2d, ", s.shape[i][j]);
		printf("\n");
	}
}

/* ¥ª¥kÂ½Âà */
void reverse(point_t *p)
{
	int i;

	for (i = 0 ; i < BITS_PIECES ; i++) {
		p[i].x = -p[i].x;
	}
}

/* ±ÛÂà90¢X */
void rotate(point_t *p)
{
	int i, t;

	/*
	 * x' = cosƒÆx - sinƒÆy
	 * y' = sinƒÆx + cosƒÆy
	 * (ƒÆ=90?)
	 */
	for (i = 0 ; i < BITS_PIECES ; i++) {
		t = p[i].x;
		p[i].x = -p[i].y;
		p[i].y = t;
	}
}

/* »¼¼W±Æ§Ç */
void sort(int s[], int n)
{
	int i, j;
	int a;
	
	for (i = 0 ; i < n ; i++) {
		for (j = n - 1 ; j > i ; j--) {
			if (s[j] < s[j-1]) {
				a = s[j];
				s[j] = s[j-1];
				s[j-1] = a;
			}
        }
    }
}

/* ±N«ù¦³XY®y¼Ðªº¸ê®Æ¡AÂà´«¦¨¤@ºû°}¦C¥Îªº½s¸¹ */
void convert_shape_to_index(shape_t *shape, point_t *point)
{
	int i, j, n;
	int tmp[BITS_PIECES];
	
	n = shape->n_shape;
	for (i = 0 ; i < BITS_PIECES ; i++) {
		tmp[i] = POS(point[i].x, point[i].y);
    }
    
    sort(tmp, BITS_PIECES);
    
	for (i = 0 ; i < BITS_PIECES ; i++) {
		shape->shape[n][i] = tmp[i] - tmp[0];
	}
	for (i = 0 ; i < n ; i++) {   /* ÀË¬d¬O§_¤w¦³¦P«¬ªÌ */
		for (j = 0 ; j < BITS_PIECES ; j++)
			if (shape->shape[n][j] != shape->shape[i][j])
				break;
		if (j == BITS_PIECES) 
			return;
	}
	shape->n_shape++;
}

/* ±q¤­¤è¶ôÂI°}¹Ï¨ú±o¹s¥ó¸ê°T */
void init(void)
{
	int x, y, n, i, k;

	for (k = 0 ; k < PIECES ; k++) {
		/* ±qÂI°}¹Ï¨ú±oXY®y¼Ð­È */
		n = 0;
		for (y = 0 ; y < 5 ; y++) {
			for (x = 0 ; x < 5 ; x++) {
				if (pieces[k][x + y*5] == '*') {
					assert(n < BITS_PIECES);
					Point[k][n].x = x;
					Point[k][n].y = y;
					n++;
				}
			}
		}

		/* ±qXY®y¼Ð­ÈÂà´«¦¨8ºØÃþ«¬ªº¬Û¹ï¦ì¸m */
		Shape[k].n_shape = 0;
		for (i = 0 ; i < 4; i++) {
			convert_shape_to_index(&Shape[k] ,Point[k]);
			rotate(Point[k]);
		}
		reverse(Point[k]);
		for (i = 0 ; i < 4; i++) {
			convert_shape_to_index(&Shape[k] ,Point[k]);
			rotate(Point[k]);
		}
		//shape_disp(Shape[k]);
	}
}


int main(void)
{
	init();
	init_board();
	sub(0);

	printf("¦@ %d ºØ¸Ñ\n", ans_cnt);

	return 0;
}


