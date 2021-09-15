#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
using namespace std;

void setResult(double score)
{
	printf("%0.1lf\n", score);
	exit(0);
}
const double EPS = 1e-9;

bool isEqual(double a, double b)
{
	return abs(a - b) <= EPS * max(abs(a), 1.0);
}

int main(int argc, const char *argv[])
{
	//const char *inputFileName = argv[1];
	const char *outputFileName = argv[2];
	const char *standardFileName = argv[3];
	const char *logFileName = argv[4];
	freopen(logFileName, "w", stdout);

	double vu, vs;
	FILE *fout = fopen(outputFileName, "r");
	if (!fout)
		setResult(0.0);
	if (fscanf(fout, "%lf", &vu) != 1)
		setResult(0.0);
	fclose(fout);
	FILE *fstd = fopen(standardFileName, "r");
	if (!fstd)
		setResult(0.0);
	if (fscanf(fstd, "%lf", &vs) != 1)
		setResult(0.0);
	fclose(fstd);
	if (isEqual(vs, vu))
		setResult(1.0);
	else
		setResult(0.0);
	return 0;
}
