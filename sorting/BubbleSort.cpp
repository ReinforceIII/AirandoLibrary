//BubbleSort : StableSort

#include <vector>

void bubbleSort(vector<int> v) {
    for(int i=0; i<v.size()-1; i++) {
        for(int j=1; j<v.size()-i; j++) {
            if(v[j-1] > v[j]) swap(v[j-1],v[j]);
        }
    }
}