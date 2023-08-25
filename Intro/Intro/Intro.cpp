#include "IntroHeader.h"
typedef chrono::steady_clock timer;

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
	//vary k with same number of elements = 1000
	//three tests per k
	//min 60 tests
	//20 diff K each ran 3 times
	vector<vector<chrono::duration<float>>> time_table;
	chrono::duration<float> sum_of_times;
	chrono::duration<float> average_of_times;
	time_table.resize(20);
	timer::time_point start, stop;
	chrono::duration<double> time_span;

	for (int k = 1; k <= 39; k += 2) {
		//test with already sorted list
		vector<int> array;
		for (int i = -500; i < 500; i++) {
			array.push_back(i + 1);
		}
		start = timer::now();
		Merge_Sort(array, 0, sizeof(array), k);
		stop = timer::now();

		time_span = chrono::duration_cast<chrono::duration<float>>(stop - start);
		cout << "duration of k = " << k << " sorted forwards = " << setprecision(5) << time_span.count() * 1000000 << " microseconds" << endl;
		sum_of_times = time_span;
		time_table[((k + 1) / 2) - 1].push_back(time_span);

		//test sorted backwards
		array.clear();
		for (int i = 500; i > -500; i--) {
			array.push_back(i);
		}
		start = timer::now();
		Merge_Sort(array, 0, sizeof(array), k);
		stop = timer::now();

		time_span = chrono::duration_cast<chrono::duration<float>>(stop - start);
		cout << "duration of k = " << k << " sorted backwards = " << setprecision(5) << time_span.count() * 1000000 << " microseconds" << endl;
		sum_of_times += time_span;
		time_table[((k + 1) / 2) - 1].push_back(time_span);

		//test with random list -300,000 - 300,000
		array.clear();
		srand(time(NULL));
		for (int i = 0; i < 1000; i++) {
			int rand_num = rand() % 300000;
			if (rand() % 2 == 1)
				rand_num * -1;
			array.push_back(rand_num);
		}
		start = timer::now();
		Merge_Sort(array, 0, sizeof(array), k);
		stop = timer::now();

		time_span = chrono::duration_cast<chrono::duration<float>>(stop - start);
		cout << "duration of k = " << k << " random = " << setprecision(5) << time_span.count() * 1000000 << " microseconds" << endl;
		sum_of_times += time_span;
		time_table[((k + 1) / 2) - 1].push_back(time_span);



		//average the time
		average_of_times = sum_of_times / 3;
		cout << "average of k value " << k << " times = " << setprecision(5) << average_of_times.count() * 1000000 << " microseconds" << endl;
		time_table[((k + 1) / 2) - 1].push_back(average_of_times);

		cout << endl;

	}

	//calculate best K
	chrono::duration<float> best = chrono::duration<float>::max();
	int best_k;
	for (int i = 0; i < 20; i++) {
		if (time_table[i][3] < best) {
			best = time_table[i][3];
			if (i == 0) {
				best_k = 1;
			}
			else {
				best_k = (i * 2) + 1;
			}
		}
	}

	cout << "best k value = " << best_k << endl;

	//calculate k = 1 ordered list time in seconds
	cout << "k = 1 ordered list times: " << endl;
	cout << "sorted forward = " << time_table[0][0].count() << " seconds" << endl;
	cout << "sorted backwards = " << time_table[0][1].count() << " seconds" << endl;
	cout << endl;

	//calculate k = n ordered list time in seconds
	cout << "k = 39 ordered list times: " << endl;
	cout << "sorted forward = " << time_table[19][0].count() << " seconds" << endl;
	cout << "sorted backwards = " << time_table[19][1].count() << " seconds" << endl;
	cout << endl;

	//calculate k = 1 random list time in seconds
	cout << "k = 1 random list time = " << time_table[0][2].count() << " seconds" << endl << endl;

	//calculate k = 39 random list time in seconds
	cout << "k = 39 random list time = " << time_table[19][2].count() << " seconds" << endl << endl;

	return;

}