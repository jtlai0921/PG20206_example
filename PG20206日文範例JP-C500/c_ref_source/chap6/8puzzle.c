/*
 * 8�p�Y��������
 *
 * [how to compile]
 *  >cl /nologo /W3 /O2 8puzzle.c
 */
#include <stdio.h>
#include <stdlib.h>

/* �C���f�b�N�X�}�N�� */
#define POS(x,y) ((x) + (y)*3)

/* �J�n�Ֆ� */
int start_board[9] = {
	4,1,3,
	7,2,6,
	0,5,8
};

/* �I���Ֆ� */
int goal_board[9] = {
	1,2,3,
	4,5,6,
	7,8,0
};


/* �n�b�V���e�[�u���Ǘ��\���� */
#define HASH_SIZE 8192   /* �n�b�V���T�C�Y */
typedef struct hash {
	int board[9];   /* �Ֆ� */
	int step;       /* �萔 */
	struct hash *next;  /* ���ׂ̔Ֆ� */
	struct hash *prev_board;  /* 1��O�̔Ֆ� */
} hash_t;

hash_t *hash[HASH_SIZE];  /* �n�b�V���e�[�u���i�`�F�C���@�j*/


/* �Ֆʂ̕\�� */
void display_board(int *board)
{
	printf("��������������\n"
		   "��%2d��%2d��%2d��\n"
		   "��������������\n"
		   "��%2d��%2d��%2d��\n"
		   "��������������\n"
		   "��%2d��%2d��%2d��\n"
		   "��������������\n",
		   board[0], board[1], board[2],
		   board[3], board[4], board[5],
		   board[6], board[7], board[8]);
}


void sub_show(hash_t *hash)
{
	hash_t *prev = hash->prev_board;

	if (prev == NULL)
		return;

	sub_show(prev);
	display_board(prev->board);
}

/* �菇�������̂ڂ��āA���肩��Ֆʂ�\�����Ă��� */
void show_answer(hash_t *hash)
{
	sub_show(hash);

	display_board(hash->board);
}


/* �n�b�V���e�[�u���̏����� */
void init_hash(void)
{
	int i;

	for (i = 0 ; i < HASH_SIZE ; i++) {
		hash[i] = NULL;
	}
}

/* �n�b�V���C���f�b�N�X���v�Z���� */
int get_hash_index(int *board)
{
	int i, val;
	int offset[] = {40320, 5040, 720, 120, 24, 6, 2, 1};  /* 8! 7! 6! 5! 4! 3! 2! 1! */

	val = 0;
	for (i = 0 ; i < 9 ; i++) {
		val += (board[i] * offset[i]);
	}
	val &= (HASH_SIZE - 1);
	return (val);
}

/* �Ֆ�(board)��step��ڂƂ��ăn�b�V���e�[�u���֓o�^����B
 * prev��1��O�̔Ֆʂ��w���B
 */
hash_t *hash_board(int *board, int step, hash_t *prev)
{
	int i, key;
	hash_t *ptr;

	ptr = malloc(sizeof(hash_t));
	if (ptr == NULL)
		exit(1);
	for (i = 0 ; i < 9 ; i++) {
		ptr->board[i] = board[i];
	}
	ptr->next = NULL;
	ptr->prev_board = prev;
	ptr->step = step;

	key = get_hash_index(board);
	ptr->next = hash[key];
	hash[key] = ptr;

	return (ptr);
}

/* �n�b�V���e�[�u������Ֆʂ�T�� */
hash_t *find_board_from_hash(int *board)
{
	int key, i;
	hash_t *ptr;

	key = get_hash_index(board);
	for (ptr = hash[key]; ptr ; ptr = ptr->next) {
		for (i = 0 ; i < 9 ; i++) 
			if (board[i] != ptr->board[i])
				break;
		if (i == 9)
			return (ptr);
	}
	return (NULL);
}

#if 0
void hash_display(void)
{
	int i, c;
	hash_t *ptr;

	for (i = 0 ; i < HASH_SIZE ; i++) {
		c = 0;
		for (ptr = hash[i]; ptr ; ptr = ptr->next) {
			if (c == 0)
				printf("%d ", i);
			c++;
			printf("*--");
#if 0
			printf("%d ���\n", ptr->step);
			for (n = 0 ; n < 9 ; n++) {
				if (n && n % 3 == 0)
					printf("\n");
				printf("%d ", ptr->board[n]);
			}
			printf("\n");
#endif
		}

		if (c)
			printf("\n");
	}

}
#endif


/* �Ֆ�(org_board)���菇(dir)�ɂ��������ăR�}�̈ړ����s���A
 * �ړ�������������A�V�K�Ֆ�(new_board)�Ƃ��Ċi�[����B
 */
int move_board(int dir, int *org_board, int *new_board)
{
	int i, found, zx, zy, t;

	found = 0;
	for (i = 0 ; i < 9 ; i++) {
		new_board[i] = org_board[i];
		if (org_board[i] == 0) {
			found = 1;
			t = i;
		}
	}
	if (found == 0) {
		printf("��}�X��������Ȃ�");
		exit(1);
	}
	zx = t % 3;   /* 0�`2 */
	zy = t / 3;   /* 0�`2 */
	//printf("(%d,%d)\n", zx, zy);

	switch (dir) {
	case 0:  /* �E�ֈړ��is/(\d)0/0$1/�j*/
		if (zx >= 1) {
			/* (zx-1,zy)<->(zx,zy) */
			new_board[POS(zx,zy)] = new_board[POS(zx-1,zy)];
			new_board[POS(zx-1,zy)] = 0;
			return 1;
		}
		break;

	case 1: /* ���ֈړ��is/0(\d)/${1}0/�j*/
		if (zx <= 1) {
			/* (zx,zy)<->(zx+1,zy) */
			new_board[POS(zx,zy)] = new_board[POS(zx+1,zy)];
			new_board[POS(zx+1,zy)] = 0;
			return 1;
		}
		break;

	case 2:  /* ���ֈړ��is/(.)(.)(.)(.)0/0$2$3$4$1/�j*/
		if (zy >= 1) {
			/* (zx,zy)<->(zx,zy-1) */
			new_board[POS(zx,zy)] = new_board[POS(zx,zy-1)];
			new_board[POS(zx,zy-1)] = 0;
			return 1;
		}
		break;

	case 3:  // ��ֈړ��is/0(.)(.)(.)(.)/$4$1$2${3}0/�j
	default:
		if (zy <= 1) {
			/* (zx,zy)<->(zx,zy+1) */
			new_board[POS(zx,zy)] = new_board[POS(zx,zy+1)];
			new_board[POS(zx,zy+1)] = 0;
			return 1;
		}
		break;
	}

	return 0;  /* �ړ����s */
}

/* ���D��T�� */
void sub(void)
{
	int i, j, k, step;
	int new_board[9];
	hash_t *ptr, *newhash;

	/* 1��ڂ��珇�ԂɎ萔�𑝂₵�Ă��� */
	for (step = 1 ; step < 100 ; step++) {
		//printf("searching.. %d step\n", step);

		/* (step-1)��ڂ̔Ֆʂ����o�� */
		for (i = 0 ; i < HASH_SIZE ; i++) {
			for (ptr = hash[i]; ptr ; ptr = ptr->next) {
				if (ptr->step != step - 1)
					continue;

				//display_board(ptr->board);

				/* �R�}��4�����ɓ������Ă݂� */
				for (j = 0 ; j < 4 ; j++) {
					if (move_board(j, ptr->board, new_board)) { /* �ړ����� */
						if (find_board_from_hash(new_board) == NULL) { /* �V�K�ՖʂȂ� */ 
							newhash = hash_board(new_board, step, ptr);
							//display_board(new_board);

							for (k = 0 ; k < 9 ; k++) {
								if (new_board[k] != goal_board[k])
									break;
							}
							if (k == 9) {
								printf("���� %d ��ڂŔ������܂���\n", step);
								show_answer(newhash);
								return;
							}
						}
					}
				}

			}
		}
	}
}

/* ���C���֐� */
int main(void)
{
	init_hash();
	/* �J�n�Ֆʂ�0��ڂƂ��ēo�^���Ă��� */
	hash_board(start_board, 0, NULL);

	sub();

	return 0;
}

