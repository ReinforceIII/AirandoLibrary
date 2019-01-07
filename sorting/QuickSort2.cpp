//QuickSort2 : UnstableSort

#include <algorithm>
#include <vector>

void quickSort2(vector<int> &v, int left, int right) {
	int low = left, high = right;
	int pivot = v[left];
	do {
		while (v[low] < pivot) low++;
		while (v[high] > pivot) high--;
		if (low <= high) {
			swap(v[low], v[high]);
			low++;
			high--;
		}
	} while (low <= high);
//	print_vector(v);
	if (left < high) quickSort2(v, left, high);
	if (low < right) quickSort2(v, low, right);
}