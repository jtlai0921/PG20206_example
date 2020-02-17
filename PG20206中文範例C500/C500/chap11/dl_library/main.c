/*
 * main.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

/* function proto-type declaration */
typedef int (*func_ptr)(int);

int main(void)
{
	int i;
	void *module;
	func_ptr isprime;
	const char *error;

	/* dynamic loading 
	 * search path: LD_LIBRARY_PATH -> /etc/ld.so.cache -> /lib -> /usr/lib
	 */
	module = dlopen("libisprime.so.1", RTLD_LAZY);
	if (module == NULL) {
		printf("Can't load library: %s\n", dlerror());
		exit(1);
	}

	/* symbol searching */
	isprime = dlsym(module, "isprime");
	if ((error = dlerror()) != NULL) {
		printf("Can't find symbol: %s\n", error);
		dlclose(module);
		exit(1);
	}

	for (i = 0 ; i < 100 ; i++) {
		if (isprime(i))
			printf("%d\n", i);
	}

	dlclose(module);

	return 0;
}


