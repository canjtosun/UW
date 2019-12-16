#include <iostream>
#include "listInterface.h"
#include "ArrayList.h"
#include <iomanip>
#include <sstream>

using namespace std;



template <class TYPE>
void readFile(ArrayList<TYPE> &list ,string fileName)
{
	
	ifstream readFile;
	readFile.open(fileName);

	if (!readFile.is_open()) {
		cout << "file not found" << endl;
		return exit(1);
	}

	string line = "";

	while (getline(readFile, line))
	{
		list.append(stoi(line));
	}

	list.clearStatistics();
	readFile.close();
}


template <class TYPE>
void printOut(ArrayList<TYPE> &list)
{
	for (int i = 0; i < list.getSize(); i++)
		cout << list[i] << " ";

	cout << endl;
}


template <class TYPE>
void insertionSort(ArrayList<TYPE>& list)
{
	for (int i = 1; i < list.getSize(); i++)
	{
		int key = list[i];
		int j = i - 1;

		while (j >= 0 && list[j] > key)
		{
			list[j + 1] = list[j];
			j--;
		}

		list[j + 1] = key;
	}
}


template <class TYPE>
void mergesort(ArrayList<TYPE>& arr, int lo, int hi) {
	// if the segment we need to sort contains <= 1 elements, we don't need to do anything
	if (lo >= hi)
		return;

	// find the middle of the current segment [lo, hi]  
	int mid = (lo + hi) / 2;

	// divide current segment [lo, hi] into two parts [lo, mid] & [mid + 1, hi]
	mergesort(arr, lo, mid);
	mergesort(arr, mid + 1, hi);


	// by the time you get here, segments [lo, mid] & [mid + 1, hi] are two individually sorted
	//  segments e.g. [3, 4, 7, 10] & [1, 20, 21, 40] and all we need to do is merge them
	//  into one sorted segment [lo, hi] e.g. [1, 3, 4, 7, 10, 20, 21, 40]
	// create a temp array which will hold the sorted result [lo, hi] from sorted segments [lo, mid] & [mid + 1, hi]
	ArrayList<TYPE> temp;

	// i iterates in range [lo, mid], and j iterates in range [mid + 1, hi]
	int i = lo, j = mid + 1;
	while (i <= mid && j <= hi) {
		// insert the smaller of the two elements in the back of temp
		if (arr[i] <= arr[j]) {
			temp.append(arr[i++]);
		}
		else {
			temp.append(arr[j++]);
		}
	}
	// if i still hasn't reached mid then insert the rest of elements [i, mid] into temp
	while (i <= mid) {
		temp.append(arr[i++]);
	}
	// if j still hasn't reached hi then insert the rest of the elements [j, hi] into temp
	while (j <= hi) {
		temp.append(arr[j++]);
	}
	// now we need to copy everything from sorted array temp back into segment [lo, hi] of arr
	i = lo;
	for (int k = 0; k < temp.getSize(); ++k) {
		arr[i++] = temp[k];
	}
}

template <class TYPE>
int partition(ArrayList<TYPE>& arr, int low, int high)
{
	int pivot = arr[high]; // pivot  
	int i = (low - 1); // Index of smaller element  

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot  
		if (arr[j] < pivot)
		{
			i++; // increment index of smaller element  
			arr.swap(i, j);
		}
	}
	arr.swap(i+1, high);
	return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
template <class TYPE>
void quickSort(ArrayList<TYPE>& arr, int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before  
		// partition and after partition  
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}
/*

cout << "Insertion Sort Result" << endl;
	printOut(list);
	
	*/

template <class TYPE>
void outputSortedList(ArrayList<TYPE> list, string fileName)
{

	readFile(list, fileName);

	cout << "Filename: " << fileName << endl;
	cout << "Number of items: " << list.getSize() << endl;

	list.clearStatistics();
	insertionSort(list);
	cout << "Insertion Sort Result" << endl;
	printOut(list);


	int isgna = list.getNumAccess();
	int isgns = list.getNumSwap();
	int isgnr = list.getNumRemove();
	int isgnia = list.getNumInsertAt();
	int isgnap = list.getNumAppends();

	list.clearAll();
	list.clearStatistics();
	readFile(list, fileName);
	list.clearStatistics();
	mergesort(list, 0, list.getSize() - 1);
	cout << "Merge Sort Result" << endl;
	printOut(list);



	int msgna = list.getNumAccess();
	int msgns = list.getNumSwap();
	int msgnr = list.getNumRemove();
	int msgnia = list.getNumInsertAt();
	int msgnap = list.getNumAppends();


	list.clearAll();
	list.clearStatistics();
	readFile(list, fileName);
	list.clearStatistics();
	quickSort(list, 0, list.getSize() - 1);
	cout << "Quick Sort Result" << endl;
	printOut(list);


	int qsgna = list.getNumAccess();
	int qsgns = list.getNumSwap();
	int qsgnr = list.getNumRemove();
	int qsgnia = list.getNumInsertAt();
	int qsgnap = list.getNumAppends();


	cout << endl;
	cout << endl;

	cout << "Number of" << setw(15) << "Access" << setw(10) << "Swap"
		<< setw(10) << "Remove"
		<< setw(10) << "InserAt" << setw(10) << "Append" << endl;


	cout << "InsertionSort" << setw(10) << isgna << setw(10) << isgns << setw(10)
		<< isgnr << setw(10) << isgnia << setw(10) << isgnap << endl;

	cout << "MergeSort" << setw(14) << msgna << setw(10) << msgns << setw(10)
		<< msgnr << setw(10) << msgnia << setw(10) << msgnap << endl;

	cout << "QuickSort" << setw(14) << qsgna << setw(10) << qsgns << setw(10)
		<< qsgnr << setw(10) << qsgnia << setw(10) << qsgnap << endl;

	list.clearStatistics();

}



template<class TYPE>
void report(ArrayList<TYPE>& list, string fileName) {


	readFile(list, fileName);

	cout << "Filename: " << fileName << endl;
	cout << "Number of items: " << list.getSize() << endl;

	list.clearStatistics();
	insertionSort(list);
	

	int isgna = list.getNumAccess();
	int isgns = list.getNumSwap();
	int isgnr = list.getNumRemove();
	int isgnia = list.getNumInsertAt();
	int isgnap = list.getNumAppends();

	list.clearAll();
	list.clearStatistics();
	readFile(list, fileName);
	list.clearStatistics();
	mergesort(list, 0, list.getSize() - 1);
	


	int msgna = list.getNumAccess();
	int msgns = list.getNumSwap();
	int msgnr = list.getNumRemove();
	int msgnia = list.getNumInsertAt();
	int msgnap = list.getNumAppends();


	list.clearAll();
	list.clearStatistics();
	readFile(list, fileName);
	list.clearStatistics();
	quickSort(list, 0, list.getSize() - 1);
	

	int qsgna = list.getNumAccess();
	int qsgns = list.getNumSwap();
	int qsgnr = list.getNumRemove();
	int qsgnia = list.getNumInsertAt();
	int qsgnap = list.getNumAppends();


	cout << endl;
	cout << endl;

	cout << "Number of" << setw(15) << "Access" << setw(10) << "Swap"
		<< setw(10) << "Remove"
		<< setw(10) << "InserAt" << setw(10) << "Append" << endl;


	cout << "InsertionSort" << setw(10) << isgna << setw(10) << isgns << setw(10)
		<< isgnr << setw(10) << isgnia << setw(10) << isgnap << endl;

	cout << "MergeSort" << setw(14) << msgna << setw(10) << msgns << setw(10)
		<< msgnr << setw(10) << msgnia << setw(10) << msgnap << endl;

	cout << "QuickSort" << setw(14) << qsgna << setw(10) << qsgns << setw(10)
		<< qsgnr << setw(10) << qsgnia << setw(10) << qsgnap << endl;

	list.clearStatistics();

}




int main(int argc, char* argv[])
{
	ArrayList<int> list;

	if (argc == 1){
		cout << "no file name written" << endl;
		exit(1);
	}

	else if (argc == 2) {

		stringstream readIt(argv[1]);
		string convertedFile = readIt.str();
		report(list, convertedFile);

	}

	
	else if(argc == 3)
	{
		stringstream readIt2(argv[1]);
		stringstream readIt3(argv[2]);
		string convertedFile2 = readIt2.str();
		string convertedFile3 = readIt3.str();

		if(convertedFile2 == "-d"){
		
			outputSortedList(list,convertedFile3);
		}
	
		else {
			cout << "you did not add right command " << endl;
			exit(1);
		}
		
	}

	else
	{
		cout << "too many argument " << endl;
		exit(1);
	}


	return 0;
}
