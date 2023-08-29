#include "IntroHeader.h"
typedef chrono::high_resolution_clock timer;

int main(int argc, char* argv[]) {
	int ary_min_size = 0;
	vector<int> array;
	//error checking
	if (argv[1] == NULL) {
		cout << "Error: must have command at [1]" << endl;
		return 0;
	}
	else if (argv[1][0] == 't') { //if you want to run automated testing, use argument 't' when running the program
		time_tests();
		return 0;
	}
	else if (isalpha(argv[1][0])) {
		cout << "Error: Unknown command at [1]." << endl << "All arguments must either be /'t/' for test cases or a number for k" << endl;
		return 0;
	}

	//get set min array size value
	ary_min_size = atoi(argv[1]);

	//get all the data from command line arg into and arry
	for (int i = 2; i < argc; i++) {
		array.push_back(atoi(argv[i]));
	}

	//sort the given list
	Merge_Sort(array, 0, (array.size() - 1), ary_min_size);


	cout << "SUCCESS!" << endl << "Sorted Array: ";
	for (int i = 0; i < array.size(); i++) {
		cout << array[i] << " ";
	}

	return 0;

}

//GRADING: MERGE
//from Introduction to Algorithms" by Thomas H. Cormen, Charles E. Leiserson page 37
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

////from Introduction to Algorithms" by Thomas H. Cormen, Charles E. Leiserson page 35
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

//GRADING: INSERTION
//from Introduction to Algorithms" by Thomas H. Cormen, Charles E. Leiserson page 19
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

//automated test cases
void time_tests() {
	vector<vector<chrono::duration<float>>> time_table;
	chrono::duration<float> sum_of_times;
	chrono::duration<float> average_of_times;
	time_table.resize(300);
	timer::time_point start, stop;
	chrono::duration<double> time_span;

	srand(time(NULL));
	int t = 0; //used for incrementing the time table vector
	int k = 1;

	//testing k = 1 -> 300 with randomized arrays
	for (int l = 0; l < 300; l++) {
		vector<int> array;
		//cout << "K = " << k << "(k # = " << l << ") " << endl; //used for data confirmation
		for (int i = 0; i < 3; i++) {
			for (int x = 0; x < 1000; x++) {
				array.push_back(rand());
			}

			start = timer::now();
			Merge_Sort(array, 0, sizeof(array), k);
			stop = timer::now();

			time_span = chrono::duration_cast<chrono::duration<float>>(stop - start);
			time_table[k - 1].push_back(time_span);

			if (i == 0) {
				sum_of_times = time_span;
			}
			else {
				sum_of_times += time_span;
			}

			//cout << "	Duration of test " << i + 1 << ": " << setprecision(10) << time_span.count() << " seconds" << endl; //used for data confirmation
			array.clear();

		}
		average_of_times = sum_of_times / 3;
		//cout << "average: " << average_of_times.count() << endl; //used for data confirmation
		time_table[k - 1].push_back(average_of_times);
		k++;
		cout << endl;
	}

	//find best K from previous tests
	chrono::duration<float> best = timer::duration::max();
	int best_k = 0;
	for (int i = 0; i < time_table.size(); i++) {
		if (time_table[i][3] <= best) {
			best = time_table[i][3];
			best_k = i;
		}
	}

	cout << "best K = " << best_k + 1 << " at: " << time_table[best_k][3].count() << endl;

	//last 4 test cases
	vector<chrono::duration<float>> edge_cases;
	vector<int> array;
	for (int i = 0; i < 300; i++) {
		array.push_back(i + 1);
	}

	//test case with k = 1 ordered list
	start = timer::now();
	Merge_Sort(array, 0, sizeof(array), 1);
	stop = timer::now();

	edge_cases.push_back(chrono::duration_cast<chrono::duration<float>>(stop - start));

	//test case with k = n ordered list
	start = timer::now();
	Merge_Sort(array, 0, sizeof(array), sizeof(array));
	stop = timer::now();

	edge_cases.push_back(chrono::duration_cast<chrono::duration<float>>(stop - start));

	//randomly sorted array tests
	array.clear();
	srand(time(NULL));
	for (int i = 0; i < 300; i++) {
		array.push_back(rand());
	}
	vector<int> array2 = array; //so we have the same randomly ordered list for both k = 1 and k = n

	//test case with k = 1 random list
	start = timer::now();
	Merge_Sort(array, 0, sizeof(array), 1);
	stop = timer::now();
	edge_cases.push_back(chrono::duration_cast<chrono::duration<float>>(stop - start));

	//test case with k = n random list
	start = timer::now();
	Merge_Sort(array2, 0, sizeof(array2), sizeof(array2));
	stop = timer::now();
	edge_cases.push_back(chrono::duration_cast<chrono::duration<float>>(stop - start));

	cout << "K = 1 ordered list time: " << setprecision(10) << edge_cases[0].count() << endl;
	cout << "K = n ordered list time: " << setprecision(10) << edge_cases[1].count() << endl;
	cout << "K = 1 random list time: " << setprecision(10) << edge_cases[2].count() << endl;
	cout << "K = n random list time: " << setprecision(10) << edge_cases[3].count() << endl;

	//output to a csv file
	ofstream outFile;
	outFile.open("outData.csv");

	for (int i = 0; i < time_table.size(); i++) {
		outFile << i + 1 << ", " << time_table[i][0].count() << ", ";
		outFile << time_table[i][1].count() << ", ";
		outFile << time_table[i][2].count() << ", ";
		outFile << time_table[i][3].count() << endl;
	}


	return;

}