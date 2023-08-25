#pragma once
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <iomanip>

using namespace std;

//GRADING: INSERTION-SORT
void Insert_Sort(vector<int>& array, int array_size);

void time_tests();

void Merge_Sort(vector<int>& array, int start, int end, int array_min_size);

void Merge(vector<int>& array1, int start, int mid, int end);
