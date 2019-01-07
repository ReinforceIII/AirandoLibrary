//QuickSort : UnstableSort

#include <algorithm>
#include <vector>

int partition(vector<int> &v, int left, int right) {
	int pivot, temp;
	int low, high;

	low = left;
	high = right+1;
	pivot = v[left];

	do {
		do {
			low++;
		} while (low <= right && v[low] < pivot);
		do {
			high--;
		} while (high >= left && v[high] > pivot);

		if (low < high) {
			swap(v[low], v[high]);
		}
	} while (low < high);

	swap(v[left], v[high]);
//	print_vector(v);
	return high;

}

void quickSort(vector<int> &v, int left, int right) {
	if (left < right) {
		int pivot = partition(v, left, right);

		quickSort(v, left, pivot - 1);
		quickSort(v, pivot + 1, right);
	}
}