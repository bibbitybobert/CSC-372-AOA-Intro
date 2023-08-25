#include "IntroHeader.h"

int main(int argc, char* argv[]) {
	int ary_min_size = 0;
	vector<int> array;
	if (argv[1][0] == 't') {
		time_tests();
		return 0;
	}

	//get set min array size value
	ary_min_size = atoi(argv[1]);

	//get all the data from command line arg into and arry
	for (int i = 2; i < argc; i++) {
		array.push_back(atoi(argv[i]));
	}

	Merge_Sort(array, 0, (array.size() - 1), ary_min_size);

	cout << "SUCCESS!" << endl << "Sorted Array: ";
	for (int i = 0; i < array.size(); i++) {
		cout << array[i] << " ";
	}

	return 0;

}


void Merge_Sort(vector<int>& array, int start, int end, int ary_min_size) {
	if ((end - start) < ary_min_size) {
		Insert_Sort(array, end);
		return;
	}
	if (start >= end)
		return;

	int mid = ((start + end) / 2); //find midpoint
	Merge_Sort(array, start, mid, ary_min_size); //recursively sort first half of the array
	Merge_Sort(array, mid + 1, end, ary_min_size); //recursively sort back half of the array

	Merge(array, start, mid, end);
	return;
}

void Merge(vector<int>& array, int start, int mid, int end) {
	int len_top = mid - start + 1;
	int len_back = end - mid;
	vector<int> top_array;
	vector<int> back_array;
	top_array.resize(len_top);
	back_array.resize(len_back);

	for (int i = 0; i < len_top; i++) {
		top_array[i] = array[start + i];
	}
	for (int j = 0; j < len_back; j++) {
		back_array[j] = array[mid + j + 1];
	}

	int i = 0, j = 0, k = start;

	while (i < len_top && j < len_back) {
		if (top_array[i] <= back_array[j]) {
			array[k] = top_array[i];
			i++;
		}
		else {
			array[k] = back_array[j];
			j++;
		}
		k++;

	}

	while (i < len_top) {
		array[k] = top_array[i];
		i++;
		k++;
	}
	while (j < len_back) {
		array[k] = back_array[j];
		j++;
		k++;
	}

	return;
}

void Insert_Sort(vector<int>& array, int array_size) {
	for (int i = 1; i <= array_size; i++) {
		int key = array[i];
		int j = i - 1;
		while (j >= 0 && array[j] > key) {
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = key;
	}
	return;
}

void time_tests() {
	//vary k with same number of elements
	//three tests per k
	//min 60 tests
	//20 diff K each ran 3 times
	vector<vector<float>> time_table;
	time_table.resize(20);

	for (int k = 0; k < 20; k++) {

	}
}