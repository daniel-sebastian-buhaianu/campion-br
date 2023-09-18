#include <stdio.h>
#include <stdlib.h>

#define NMAX 15000
#define TMAX 10000
#define CMAX 100
#define KMAX 15000
#define XMAX 3000000

int main()
{
	unsigned short N, T, c, i, k, j, nr, st, dr, mij;
	unsigned x, *s;

	FILE *fin = fopen("br.in", "r");

	if (!fin) { printf("Eroare br.in\n"); return 1; }

	fscanf(fin, "%hu %hu", &N, &T);

	if (N < 1 || N > NMAX || T < 1 || T > TMAX) { printf("Eroare valoare N sau T\n"); return 2; }

	s = (unsigned*)calloc(N+N+1, sizeof(unsigned));

	if (!s) { printf("Eroare alocare memorie *s\n"); return 3; }

	for (i = 1; i <= N; i++) {
		fscanf(fin, "%hu", &c);

		if (c < 1 || c > CMAX) { printf("Eroare valoare c\n"); return 4; }

		s[i] = s[i-1] + c;
		s[i+N] = c;
	}

	for (i = N+1; i <= N+N; i++) s[i] += s[i-1];	
	
	FILE *fout = fopen("br.out", "w");

	for (i = 0; i < T; i++) {
		fscanf(fin, "%hu %u", &k, &x);

		if (k < 1 || k > N || x < 1 || x > XMAX) { printf("Eroare valoare k sau x\n"); return 5; }

		if (x < s[k]-s[k-1]) nr = 0;
		else {
			st = 0, dr = N+1;

			while (dr-st > 1) {
				mij = st + (dr-st)/2;

				if (s[k+mij-1]-s[k-1] <= x) st = mij;
				else dr = mij;
			}

			nr = st;
		}

		fprintf(fout, "%hu\n", nr);
	}

	fclose(fin);

	fclose(fout);

	free(s);

	return 0;
}
// scor 100 - pbinfo, campion
