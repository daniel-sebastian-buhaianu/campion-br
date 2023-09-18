#include <stdio.h>
#include <stdlib.h>

#define NMAX 15000
#define TMAX 10000
#define CMAX 100
#define KMAX 15000
#define XMAX 3000000

int main()
{
	unsigned short N, T, *c, i, k, nr;
	unsigned x, r, *s;

	FILE *fin = fopen("br.in", "r");

	if (!fin) { printf("Eroare br.in\n"); return 1; }

	fscanf(fin, "%hu %hu", &N, &T);

	if (N < 1 || N > NMAX || T < 1 || T > TMAX) { printf("Eroare valoare N sau T\n"); return 2; }

	c = (unsigned short*)calloc(N+1, sizeof(unsigned short));

	s = (unsigned*)calloc(N+1, sizeof(unsigned));

	for (i = 1; i <= N; i++) {
		fscanf(fin, "%hu", &c[i]);

		if (c[i] < 1 || c[i] > CMAX) { printf("Eroare valoare c[%hu]\n", i); return 3; }

		s[i] = s[i-1] + c[i];
	}
	
	FILE *fout = fopen("br.out", "w");

	for (i = 0; i < T; i++) {
		fscanf(fin, "%hu %u", &k, &x);

		if (k < 1 || k > N || x < 1 || x > XMAX) { printf("Eroare valoare k sau x\n"); return 4; }

		if (x >= s[N]) nr = N;
		else {
			r = x, nr = 0;

			while (c[k] <= r && nr < N) {
				nr++;
				
				r -= c[k];
				
				k++;

				if (k > N) k = 1;
			}
		}

		fprintf(fout, "%hu\n", nr);
	}

	fclose(fin);

	fclose(fout);

	free(s);

	free(c);

	return 0;
}
// scor 90 - campion
// scor 100 - pbinfo
