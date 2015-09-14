#include <stdio.h>
#include "../util.h"

int main(void)
{
	int cntns;

	cntns = contains("03/04/05", "/");
	printf("contains(03/04/05, /) = %d\t\t%s\n", cntns, (cntns == 2) ? "PASSED" : "FAILED");
	cntns = contains("03/-04/-05", "/-");
	printf("contains(03/-04/-05, /-) = %d\t\t%s\n", cntns, (cntns == 2) ? "PASSED" : "FAILED");
	cntns = contains("03/-04/04", "/-");
	printf("contains(03/-04/05, /-) = %d\t\t%s\n", cntns, (cntns == 1) ? "PASSED" : "FAILED");
	cntns = contains("030404", "/");
	printf("contains(030405, /) = %d\t\t\t%s\n", cntns, (cntns == 0) ? "PASSED" : "FAILED");

	return 0;
}
