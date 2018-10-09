#pragma once
#include<iostream>
#include<vector>
using namespace std;

//binary search 
//return the position of the num
template <typename T>
int binary_search(T item, vector<T> &list)
{
	int pos;
	int low = 0;
	int high = list.size()-1;
	T guess = 0;
	bool isFind = false;
	while (low <= high)
	{
		mid = (low + high) / 2;
		guess = list[mid];
		if (guess == item) { isFind = true; break; }
		else if (guess > item) { low = mid + 1; }
		else { high = mid - 1; }
	}
	if (isFind)
	{
		return mid;
	}
	else 
	{
		return -1;
	}
}


//quicksort
template <typename T>
bool quicksort(T *array,T left,T right)
{
	assert(array);							//check the array
	if (left >= right){return;}
	
	T& key = array[right];
	while (left < right)
	{
		while (left < right && array[left] <= key)
		{
			left++;
		}
		while (left < right &&array[right] >= key)
		{
			right--;
		}
		T temp = array[left]; array[left] = array[right]; array[right] = array[left];
	}
	T temp = array[left]; array[left] = key; key = array[left];
	T index = left;
	quicksort(array, left, index - 1);
	quicksort(array, index + 1, right);
	return true;
}