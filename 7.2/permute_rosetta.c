#include <stdio.h>
#include <stdlib.h>

#include "include.h"

/* next lexicographical permutation */
int next_lex_perm(int *a, int n)
{
#	define swap(i, j) {t = a[i]; a[i] = a[j]; a[j] = t;}
	int k, l, t;
 
	/* 1. Find the largest index k such that a[k] < a[k + 1]. If no such
	      index exists, the permutation is the last permutation. */
	for (k = n - 1; k && a[k - 1] >= a[k]; k--);
	if (!k--) return 0;
 
	/* 2. Find the largest index l such that a[k] < a[l]. Since k + 1 is
	   such an index, l is well defined */
	for (l = n - 1; a[l] <= a[k]; l--);
 
	/* 3. Swap a[k] with a[l] */
	swap(k, l);
 
	/* 4. Reverse the sequence from a[k + 1] to the end */
	for (k++, l = n - 1; l > k; l--, k++)
		swap(k, l);
	return 1;
#	undef swap
}
 
int permute(int *x, int n, int callback(int*, DATA*[]), DATA* amplifier[] )
{
    int best_output = 0;
    int current_output;
	do
	{
        current_output = callback(x, amplifier);
        if (current_output > best_output)
        {
            best_output = current_output;
        }

	} while (next_lex_perm(x, n));

    return best_output;
}
