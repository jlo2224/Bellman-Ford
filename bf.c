#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define INVALID -1
#define RANGE 100000

long long successful_relaxations = 0;
long long attempted_relaxations = 0;
long long e = 0;
double weight_sum = 0;

double exponential() {
	double lambda = 1 / (exp(1) - 1);
	//printf("lambda: %f\n", lambda);
    double u = ((double) rand() / (RAND_MAX));  // Uniform random variable in [0, 1]
	//printf("u: %f\n", u);
	//printf("%f\n", u/lambda + 1);
    double x = log(u/lambda + 1); // Inverse CDF of the custom PDF
	weight_sum += x;
	//printf("%f\n", x);
    return x;
}

double bernoulli() {
	if ((double) rand() / (RAND_MAX) < 0.5) {
		return 0.0001;
	}
	return 1.0;
}

double uniform() {
	return (double) rand() / (RAND_MAX);
}

void initialize_depths(double* tentative_depths, int v) {
	tentative_depths[0] = 0;
	for (int i=1; i<v; i++) {
		tentative_depths[i] = 10000;
	}
}

void populate_matrix(double* matrix, int v, float p) {
	for (int i=0; i<v; i++) {
		for (int j=0; j<v; j++) {
			if (i != j && rand() * 1.0 / RAND_MAX < p) {
				matrix[i * v + j] =	uniform(); // 1 + rand() % 100000;
				e++;
			} else {
				matrix[i * v + j] = INVALID;
			}
		}
	}
}

void populate_pi(double* pi, int v) {
	for (int i=1; i<v; i++) {
		pi[i] = 10000;
	}
	pi[0] = 0;
}


int relax(double * matrix, double * tentative_depths, double * pi, int i, int j, int v) {
	if (matrix[i * v + j] < 0 ) {
		return 0;
	}
	attempted_relaxations++;
	double update = tentative_depths[i] + matrix[i * v + j];
	if (update < tentative_depths[j]) {
		tentative_depths[j] = update;
		successful_relaxations++;
		pi[j] = pi[i] + 1;
		return 1;
	}
	return 0;
}

void print_matrix(double * matrix, int v) {

	printf("-----------------------------------------------------------------\n");
	printf("MATRIX: \n");
	for (int i=0; i<v; i++) {
		for (int j=0; j<v; j++) {
			if (matrix[i * v + j] >= 0) printf("%f ", matrix[i * v + j]); else printf("N ");
		}
		printf("\n");
	}
	printf("-----------------------------------------------------------------\n");
}

int main(int argc, char * argv[]) {
	if (argc < 3) {
		printf("Usage: ./bf <# of vertices> <p>\n");
		printf("Alternate Usage: ./bf <# of vertices> <a> <b>\n(p=a/b in this alternate usage)\n");
	} else if (argc > 4) {
		printf("Usage: ./bf <# of vertices> <p>\n");
		printf("Alternate Usage: ./bf <# of vertices> <a> <b>\n(p=a/b in this alternate usage)\n");
	}
	int v = atoi(argv[1]);
	float p = atof(argv[2]);
	if (argc == 4) p = atof(argv[2]) / atof(argv[3]);
	double * matrix = (double *) malloc(v * v * sizeof(double));
	double * tentative_depths = (double *) malloc(v * sizeof(double));
	double * pi = (double *) malloc(v * sizeof(double));

	srand(time(NULL));
	
	populate_matrix(matrix, v, p);
	populate_pi(pi, v);
	initialize_depths(tentative_depths, v);
	// print_matrix(matrix, v);

#ifdef LONG
	print_matrix(matrix, v);
#endif

	int active = 0;
	int iterations = 0;

	while (1) {
		iterations++;
		for (int i=0; i<v; i++) {
			for (int j=0; j<v; j++) {
				active += relax(matrix, tentative_depths, pi, i, j, v);
			}
		}
		if (!active) break;
		active = 0;
	}
	int tree_depth = 0;
	for (int i=0; i<v; i++) {
		if (pi[i] > tree_depth && pi[i] != 10000) {
			tree_depth = pi[i];
		}
		// printf("%f ", tentative_depths[i]);
	}
	//printf("\n");
	//printf("%f\n", weight_sum / e);
#ifdef LONG
	printf("%d successful relaxations.\n", successful_relaxations);
#else
	printf("%d %lld %d %lld %lld %d\n", v, e, iterations, attempted_relaxations, successful_relaxations, tree_depth);
#endif
}
	
		
	
