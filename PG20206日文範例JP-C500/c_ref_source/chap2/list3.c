/* list3 */
#include <stdio.h>
#include <conio.h>

int main(int argc, char **argv)
{
	int i;

	for (i = 0 ; i < argc ; i++) {
		printf("argv[%d] = %s\n", i, argv[i]);
	}

	_getch();  /* ƒL[“ü—Í‘Ò‚¿ */
	return 0;
}
