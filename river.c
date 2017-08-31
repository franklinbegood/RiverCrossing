#include "river.h"

Pole** loadFile(char* filename, int *n, int *m) {
	FILE *fp;
	int r, c;
	if(!(fp = fopen(filename, "r"))) {
		fprintf(stderr, "\nFile could not be opened.\n");
		return NULL;
	}

	// Read n
	if(fscanf(fp, "%d", n) == EOF) {
		fprintf(stderr, "\nShort read error.\n");
		return NULL;
	}

	// Read m
	if(fscanf(fp, "%d", m) == EOF) {
		fprintf(stderr, "\nShort read error.\n");
		return NULL;
	}

	// Malloc for poleArray
	Pole** poleArray = malloc(sizeof(*poleArray) * (*n - 1));
	for(r = 0; r < *n - 1; r++) {
		poleArray[r] = malloc(sizeof(**poleArray) * (*m));
	}

	// Read array
	fseek(fp, sizeof(char), SEEK_CUR);
	char temp;
	for(r = 0; r < *n - 1; r++) {
		for(c = 0; c < *m; c++) {
			if(fscanf(fp, "%c", &temp) == EOF) {
				fprintf(stderr, "\nShort read error.\n");
			}
			if(temp == '0')
				poleArray[r][c].val = 2;
			else
				poleArray[r][c].val = 1;

			if(c == 0 && temp == '0')
				poleArray[r][c].w = 1;
			else if(c == 0 && temp == '1')
				poleArray[r][c].w = 0;
			else
				poleArray[r][c].w = poleArray[r][c-1].w + poleArray[r][c].val;
		}

		fseek(fp, sizeof(char), SEEK_CUR);
	}
	fclose(fp);
	return poleArray;
}

void crossRiver(Pole** p, int r, int c, int n, int m) {
	Pole curr = p[r][c];
	
	// attempt quick up
	if((r + 1 < n - 1) && p[r+1][c].val == 1 && curr.w < p[r+1][c].w) {
		p[r+1][c].w = curr.w;
		crossRiver(p, r+1, c, n, m);
	} 	
	// attempt qucik down
	if((r - 1 >= 0) && p[r-1][c].val == 1 && curr.w < p[r-1][c].w) {
		p[r-1][c].w = curr.w;
		crossRiver(p, r-1, c, n, m);
	}
	
	// attempt right + up
	if((r + 1 < n - 1) && (c + 1 < m) && curr.w + p[r+1][c+1].val < p[r+1][c+1].w) {
		p[r+1][c+1].w = curr.w + p[r+1][c+1].val;
		crossRiver(p, r+1, c+1, n, m);
	}
	// attempt right
	if((c + 1 < m) && curr.w + p[r][c+1].val < p[r][c+1].w) {
		p[r][c+1].w = curr.w + p[r][c+1].val;
		crossRiver(p, r, c+1, n, m);
	}
	// attempt right + down
	if((r - 1 >= 0) && (c + 1 < m) && curr.w + p[r-1][c+1].val < p[r-1][c+1].w) {
		p[r-1][c+1].w = curr.w + p[r-1][c+1].val;
		crossRiver(p, r-1, c+1, n, m);
	}
	
	// attempt up
	if((r + 1 < n - 1) && p[r+1][c].val == 2 && curr.w + 2 < p[r+1][c].w) {
		p[r+1][c].w = curr.w + 2;
		crossRiver(p, r+1, c, n, m);
	}

	// attempt down
	if((r - 1 >= 0) && p[r-1][c].val == 2 && curr.w + 2 < p[r-1][c].w) {
		p[r-1][c].w = curr.w + 2;
		crossRiver(p, r-1, c, n, m);
	}

	// attempt left + up
	if((r + 1 < n - 1) && (c - 1 >= 0) && curr.w + p[r+1][c-1].val < p[r+1][c-1].w) {
		p[r+1][c-1].w = curr.w + p[r+1][c-1].val;
		crossRiver(p, r+1, c-1, n, m);
	}
	// attempt left
	if((c - 1 >= 0) && curr.w + p[r][c-1].val < p[r][c-1].w) {
		p[r][c-1].w = curr.w + p[r][c-1].val;
		crossRiver(p, r, c-1, n, m);
	}
	// attempt left + down
	if((r - 1 >= 0) && (c - 1 >= 0) && curr.w + p[r-1][c-1].val < p[r-1][c-1].w) {
		p[r-1][c-1].w = curr.w + p[r-1][c-1].val;
		crossRiver(p, r-1, c-1, n, m);
	}
	
}

int fewestRotations(char *filename) {
	int n, m, i, j; 
	Pole** poleArray = loadFile(filename, &n, &m);

	if(poleArray == NULL) {
		return -1;
	}
	for(j = 0; j < m - 1; j++) {
		for(i = 0; i < n - 1; i++) {
			crossRiver(poleArray, i, j, n, m);
		}
	}

	int min = INT_MAX;
	for(i = 0; i < n - 1; i++) {
		if(poleArray[i][m-1].w < min) {
			min = poleArray[i][m-1].w;
		}	
		free(poleArray[i]);
	}
	free(poleArray);
	
	return min + 1;
}
