#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


void swap(int* el1, int* el2) {
	int tmp = *el2;
	*el2 = *el1;
	*el1 = tmp;
}

void select(int* a, int p, int n) {
	for (int i = 0; i < n; i++) {
		int minIn = i;
		for (int j = i; j < n; j++) {
			if (a[j] < a[minIn])
				minIn = j;
		}
		swap(&a[i], &a[minIn]);
	}
}

void insert(int* a, int p, int n) {
	for (int i = 0; i < n - 1; i++) {
		double key = a[i + 1];
		for (int j = i; j >= 0; j--) {
			if (key < a[j]) {
				swap(&a[j], &a[j + 1]);
			}
			else break;
		}
	}
}

void poop(int* a, int p, int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (a[j] > a[j + 1]) {
				swap(&a[j], &a[j + 1]);
			}
		}
	}
}

void poop_optimiz(int* a, int p, int n) {
	for (int i = 0; i < n - 1; i++) {
		bool flag = true;
		for (int j = 0; j < n - 1 - i; j++) {
			if (a[j] > a[j + 1]) {
				swap(&a[j], &a[j + 1]);
				flag = false;
			}
		}
		if (flag) break;
	}
}


int partition(int* arr, int left, int right) {
	double pivot = arr[right];
	int i = left - 1;

	for (int j = left; j <= right - 1; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[right]);
	return i + 1;
}

void quicksort(int* arr, int left, int right) {
	if (left < right) {
		int p = partition(arr, left, right);
		quicksort(arr, left, p - 1);
		quicksort(arr, p + 1, right);
	}
}


void merge(int* arr, int l, int m, int r) {
	int n1 = m - l + 1;
	int n2 = r - m;

	int* L = (int*)malloc(n1 * sizeof(int));
	int* R = (int*)malloc(n2 * sizeof(int));

	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	int i = 0;
	int j = 0;
	int k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergesort(int* arr, int left, int right) {
	if (left < right) {
		int m = left + (right - left) / 2;
		mergesort(arr, left, m);
		mergesort(arr, m + 1, right);
		merge(arr, left, m, right);
	}
}


int check_1(int* x, int n) {
	for (int i = 0; i < n - 1; i++) {
		if (x[i + 1] < x[i]) {
			return 0;
		}
	}
	return 1;
}


int check_2(int* x, int n, long long int s) {
	long long int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += x[i];
	}
	if (sum == s) return 1;
	return 0;
}


void debug_test(bool rev, int n, int* x, int q,
	double* time, void (*Fp)(int*, int, int)) {
	for (int p = 0; p < 3; p++) {
		long long int sss = 0;
		srand(66);
		for (int i = 0; i != n; i++) {
			x[i] = rand();
			sss += x[i];
		}
		clock_t time_start = clock();
		if (q == 4 || q == 5) {
			Fp(x, 0, n - 1);
		}
		else {
			Fp(x, 0, n);
		}
		clock_t time_end = clock() - time_start;
		double t = (double)time_end / CLOCKS_PER_SEC;
		if (check_1(x, n) && check_2(x, n, sss)) {
			if (t < time[q]) time[q] = t;
		}
		else {
			time[q] = -1;
		}
	}
	if (rev) {
		for (int i = 0; i < (n / 2); i++) {
			int g = x[i];
			x[i] = x[n - i - 1];
			x[n - i - 1] = g;
		}
	}
}


void counting_sort(int* arr, int p, int n) {
	int max = arr[0], min = arr[0];
	int* count_arr, * sorted_arr;

	for (int i = 1; i < n; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
		if (arr[i] < min) {
			min = arr[i];
		}
	}

	count_arr = (int*)calloc(max - min + 1, sizeof(int));

	for (int i = 0; i < n; i++) {
		count_arr[arr[i] - min]++;
	}

	for (int i = 1; i < max - min + 1; i++) {
		count_arr[i] += count_arr[i - 1];
	}

	sorted_arr = (int*)calloc(n, sizeof(int));
	for (int i = n - 1; i >= 0; i--) {
		sorted_arr[count_arr[arr[i] - min] - 1] = arr[i];
		count_arr[arr[i] - min]--;
	}

	for (int i = 0; i < n; i++) {
		arr[i] = sorted_arr[i];
	}

	free(count_arr);
	free(sorted_arr);
}
// 512 - 1_000_000 (1_000_000_000)
// проверка на сортиртировку
// проверть что всё не "1"

void radix_sort(int* arr, int p, int n) {
	int i, bucket[10] = { 0 }, max_val = 0, digit_place = 1;
	int* output = (int*)malloc(n * sizeof(int));

	for (i = 0; i < n; i++) {
		if (arr[i] > max_val) {
			max_val = arr[i];
		}
	}

	while (max_val / digit_place > 0) {
		for (i = 0; i < 10; i++) {
			bucket[i] = 0;
		}

		for (i = 0; i < n; i++) {
			bucket[(arr[i] / digit_place) % 10]++;
		}

		for (i = 1; i < 10; i++) {
			bucket[i] += bucket[i - 1];
		}

		for (i = n - 1; i >= 0; i--) {
			output[bucket[(arr[i] / digit_place) % 10] - 1] = arr[i];
			bucket[(arr[i] / digit_place) % 10]--;
		}

		for (i = 0; i < n; i++) {
			arr[i] = output[i];
		}

		digit_place *= 10;
	}
}

int main() {
	int t = -1;
	while (t != 0 && t != 1) {
		printf("0 - revers false\n1 - revers true\nInput: ");
		scanf_s("%d", &t);
		system("cls");
	}
	bool revers = false;
	if (t == 1) revers = true;
	FILE* file;
	fopen_s(&file, "output.txt", "w");
	fprintf(file, "select\t\tinsert\t\tpop\t\tpop_optimiz\tquick\t\tmerge\t\tcounting\tradix\n");
	fclose(file);
	printf("\tselect\t\tinsert\t\tpop\t\tpop_optimiz\tquick\t\tmerge\t\tcounting\tradix\n");
	double time[8];
	int n;
	int* x;
	for (int j = 10; j <= 40; j++) {
		for (int i = 0; i < 8; i++) {
			time[i] = 10000;
		}
		n = 2;
		for (int i = 0; i < j; i++) n *= 2;
		x = (int*)malloc(n * sizeof(int));
		debug_test(revers, n, x, 0, time, select);
		debug_test(revers, n, x, 1, time, insert);
		debug_test(revers, n, x, 2, time, poop);
		debug_test(revers, n, x, 3, time, poop_optimiz);
		debug_test(revers, n, x, 4, time, quicksort);
		debug_test(revers, n, x, 5, time, mergesort);
		debug_test(revers, n, x, 6, time, counting_sort);
		debug_test(revers, n, x, 7, time, radix_sort);
		printf("2**%d	", j + 1);
		FILE* file;
		fopen_s(&file, "output.txt", "a+");
		for (int i = 0; i < 8; i++) {
			printf("%.3lf\t\t", time[i]);
			fprintf(file, "%.3lf\t\t", time[i]);
		}
		printf("\n");
		fprintf(file, "\n");
		fclose(file);
		free(x);
		memset(time, 0, sizeof(time));
	}
}