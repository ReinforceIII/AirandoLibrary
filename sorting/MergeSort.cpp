//MergeSort : StableSort

#include <vector>

void merge(vector<int> &v, int left, int mid, int right) {
	int i = left;
	int j = mid + 1;
	int k = left;
	vector<int> sorted(v.size());

	while (i <= mid && j <= right) {
		if (v[i] <= v[j]) sorted[k++] = v[i++];
		else sorted[k++] = v[j++];
	}
	while (i <= mid) sorted[k++] = v[i++];
	while (j <= right) sorted[k++] = v[j++];

	for (int l = left; l <= right; l++) {
		v[l] = sorted[l];
	}
}

void mergeSort(vector<int> &v, int left, int right) {
	int mid;
	if (left<right) {
		mid = (left + right) / 2;
		mergeSort(v, left, mid);
		mergeSort(v, mid + 1, right);
		merge(v, left, mid, right);
	}
}