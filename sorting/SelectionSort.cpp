//SelectionSort : UnstableSort

#include <algorithm>
#include <vector>

void SelectionSort(vector<int> v) {
    for(int i=0; i<v.size()-1; i++) {
        int temp = i;
        for(int j=i+1; j<v.size(); j++) {
            if(v[temp]>=v[j]) temp = j;
        }
        swap(v[i].v[temp]);
    }
}