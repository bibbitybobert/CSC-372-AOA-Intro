#pragma once
#include <vector> //for vectors
#include <iostream> //for cmd access
#include <cstdlib> //standard library for c functions
#include <cmath> //for math
#include <chrono> //for timing
#include <iomanip> //for cmd manipulation
#include <fstream> //for file modification

using namespace std;

//GRADING: INSERTION-SORT
void Insert_Sort(vector<int>& array, int array_size);

void time_tests();

//GRADING: MERGE
void Merge_Sort(vector<int>& array, int start, int end, int array_min_size);

void Merge(vector<int>& array1, int start, int mid, int end);
