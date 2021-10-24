// Connor Taylor
// Assignment 4: Has user choose if which sorting method to use on a array of their choosing
// and if it is random or sorted

#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <chrono>

// Precondition: int, int
// Gets the input within a certain range
// Postcondition: int
int getChoice(int, int);

// Precondition: none
// Gets the size of the of the array the user wants
// Postcondition: int
int getSize();

// Precondition: vector<int>&, vector<int>&, vector<int>&, int
// Implements and checks if the array is impplemented correctly
// Postcondition: boolean
bool isImplemented(std::vector<int>&, std::vector<int>&, std::vector<int>&, int size);

// Precondition: vector<int>&
// Has user choose which sort method to use
// Postcondition: none
void sort(std::vector<int>&);

// Precondition: int&, int&
// Swaps to values in the array
// Postcondition: none
void swap(int&, int&);

// Precondition: int, int
// Compares two values, if the first number is smaller, returns true
// Postcondition: boolean
bool compare(int, int);

// Precondition: vector<int>&
// Sorts an array using bubble sort
// Postcondition: none
void bubbleSort(std::vector<int>&);

// Precondition: vector<int>&
// Sorts array using insertion sort
// Postcondition: none
void insertionSort(std::vector<int>&);

// Precondition: vector<int>&
// Sorts array using selection sort
// Postcondition: none
void selectionSort(std::vector<int>&);

// Precondition: vector<int>&
// Sorts array using merge sort
// Postcondition: none
void mergeSort(std::vector<int>&);

// Precondition: vector<int>, vector<int>
// Merges two arrays together
// Postcondition: vector<int>
std::vector<int> merge(std::vector<int>, std::vector<int>);

// Precondition: vector<int>&, int, int
// Sorts array using quick sort with pivot at beginning value
// Postcondition: none
void quickSortFirst(std::vector<int>&, int, int);

// Precondition: vector<int>&, int, int
// Sorts array using quick sort with pivot at the mid point
// Postcondition: none
void quickSortMiddle(std::vector<int>&, int, int);

int main()
{
    int size = 0;
    std::vector<int> sortedArray, randomArray, array;
    // seeds random
    srand(time(nullptr));

    // implements both sorted and random arrays with 500,000 values
    for (int i = 0; i < 500000; ++i)
    {
        sortedArray.push_back(i);
        randomArray.push_back(rand());
    }
    
    while (size != -1)
    {
        // gets user input for inputs 
        size = getSize();
        if (size != -1 && isImplemented(array, sortedArray, randomArray, size))
        {
            sort(array);
        }
        // empties array of all values
        array.clear();
    }
    
    return 0;
}

// Precondition: int, int
// Gets the input within a certain range
// Postcondition: int
int getChoice(int first, int last)
{
    std::string strChoice;
    int intChoice;
    while (true)
    {
        // gets user input as string
        std::cout << "Enter your choice here: ";
        std::cin >> strChoice;
        if (strChoice.size() == 1)
        {
            // converts input to int then checks it is within valid range
            intChoice = std::stoi(strChoice);
            if (intChoice >= first && intChoice <= last)
            {
                return intChoice;
            }
        }

        // error message
        std::cout << "Enter a number between " << first << " and " << last << "." << std::endl;
    }
}

// Precondition: none
// Gets the size of the of the array the user wants
// Postcondition: int
int getSize()
{
    int size;
    // displays menu of sizes
    std::cout << "1. 1,000\n";
    std::cout << "2. 5,000\n";
    std::cout << "3. 10,000\n";
    std::cout << "4. 50,000\n";
    std::cout << "5. 75,000\n";
    std::cout << "6. 100,000\n";
    std::cout << "7. 500,000\n";
    std::cout << "8. Quit\n";
    int choice = getChoice(1, 8);
    // sets size to appropiate value
    switch (choice)
    {
    case 1:
        size = 1000;
        break;
    case 2:
        size = 5000;
        break;
    case 3:
        size = 10000;
        break;
    case 4:
        size = 50000;
        break;
    case 5:
        size = 75000;
        break;
    case 6:
        size = 100000;
        break;
    case 7:
        size = 500000;
        break;
    case 8:
        size = -1;
        break;
    default:
        size = -1;
        std::cout << "Unexpected error." << std::endl;
    }

    return size;
}

// Precondition: vector<int>&, vector<int>&, vector<int>&, int
// Implements and checks if the array is impplemented correctly
// Postcondition: boolean
bool isImplemented(std::vector<int>& array, std::vector<int>& sortedArray, std::vector<int>& randomArray, int size)
{
    // displays menu and gets input
    std::cout << "1. Sorted\n";
    std::cout << "2. Random\n";
    std::cout << "3. Restart\n";
    int choice = getChoice(1, 3);
    // implements array based on user input for size and if it is sorted or not
    switch (choice)
    {
    case 1:
        for (int i = 0; i < size; ++i)
        {
            array.push_back(sortedArray[i]);
        }
        break;
    case 2:
        for (int i = 0; i < size; ++i)
        {
            array.push_back(randomArray[i]);
        }
        break;
    case 3:
        return false;
        break;
    default:
        std::cout << "Unexpected error." << std::endl;
        return false;
        break;
    }

    return true;
}

// Precondition: vector<int>&
// Has user choose which sort method to use
// Postcondition: none
void sort(std::vector<int>& array)
{
    // Displays menu and gets user input 
    std::cout << "1. Bubble Sort\n";
    std::cout << "2. Insertion Sort\n";
    std::cout << "3. Selection Sort\n";
    std::cout << "4. Merge Sort\n";
    std::cout << "5. Quick Sort - Pivot is on first element\n";
    std::cout << "6. Quick Sort - Pivot is on middle element\n";
    std::cout << "7. Restart\n";
    int choice = getChoice(1, 7);

    // Starts clock and then sorts array based on user input
    auto start = std::chrono::high_resolution_clock::now();
    switch (choice)
    {
    case 1:
        bubbleSort(array);
        break;
    case 2:
        insertionSort(array);
        break;
    case 3:
        selectionSort(array);
        break;
    case 4:
        mergeSort(array);
        break;
    case 5:
        quickSortFirst(array, 0, (int)array.size() - 1);
        break;
    case 6:
        quickSortMiddle(array, 0, (int)array.size() - 1);
        break;
    case 7:
        break;
    default:
        std::cout << "Unexpected error." << std::endl;
        break;
    }
    // stops clock and outputs time
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    // alerts that the sorting is done for larger sort methods, windows specific
    std::cout << "\a";
    std::cout << "It took " << duration.count() / 1000 << "." << duration.count() % 1000 << " seconds.\n" << std::endl;
}

// Precondition: int&, int&
// Swaps to values in the array
// Postcondition: none
void swap(int& i, int& j)
{
    int temp = i;
    i = j;
    j = temp;
}

// Precondition: int, int
// Compares two values, if the first number is smaller, returns true
// Postcondition: boolean
bool compare(int i, int j)
{
    if (i < j)
    {
        return true;
    }

    return false;
}

// Precondition: vector<int>&
// Sorts an array using bubble sort
// Postcondition: none
void bubbleSort(std::vector<int>& array)
{
    size_t size = array.size();
    for (size_t i = 0; i < size - 1; ++i)
    {
        for (size_t j = size - 1; j > i; --j)
        {
            if (compare(array[j], array[j - 1]))
            {
                swap(array[j], array[j - 1]);
            }
        }
    }
    
}

// Precondition: vector<int>&
// Sorts array using insertion sort
// Postcondition: none
void insertionSort(std::vector<int>& array)
{
    size_t size = array.size();
    for (size_t i = 1; i < size; ++i)
    {
        for (size_t j = i; j > 0 && compare(array[j], array[j - 1]); --j)
        {
            swap(array[j], array[j - 1]);
        }
    }   
}

// Precondition: vector<int>&
// Sorts array using selection sort
// Postcondition: none
void selectionSort(std::vector<int>& array)
{
    size_t size = array.size();
    for (size_t i = 0; i < size - 1; ++i)
    {
        size_t lowIndex = i;
        for (size_t j = size - 1; j > i; --j)
        {
            if (compare(array[j], array[lowIndex]))
            {
                lowIndex = j;
            }
        }
        swap(array[i], array[lowIndex]);
    }
}

// Precondition: vector<int>&
// Sorts array using merge sort
// Postcondition: none
void mergeSort(std::vector<int>& array)
{
    if (array.size() <= 1)
    {
        return;
    }
    size_t length = array.size() / (size_t)2;
    std::vector<int> leftArray(array.begin(), array.begin() + length);
    std::vector<int> rightArray(array.begin() + length, array.end());
    mergeSort(leftArray);
    mergeSort(rightArray);

    array = merge(leftArray, rightArray);
}

// Precondition: vector<int>, vector<int>
// Merges two arrays together
// Postcondition: vector<int>
std::vector<int> merge(std::vector<int> leftArray, std::vector<int> rightArray) 
{
    size_t leftIndexndex = 0, rightIndexndex = 0;
    std::vector<int> finalArray;
    while (leftIndexndex < leftArray.size() && rightIndexndex < rightArray.size())
    {
        if (leftArray[leftIndexndex] < rightArray[rightIndexndex])
        {
            finalArray.push_back(leftArray[leftIndexndex]);
            ++leftIndexndex;
        }
        else
        {
            finalArray.push_back(rightArray[rightIndexndex]);
            ++rightIndexndex;
        }
    }

    while (leftIndexndex < leftArray.size())
    {
        finalArray.push_back(leftArray[leftIndexndex]);
        ++leftIndexndex;
    }

    while (rightIndexndex < rightArray.size())
    {
        finalArray.push_back(rightArray[rightIndexndex]);
        ++rightIndexndex;
    }

    return finalArray;
}

// Precondition: vector<int>&, int, int
// Sorts array using quick sort with pivot at beginning value
// Postcondition: none
void quickSortFirst(std::vector<int>& array, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int pivot = array[left];
    int leftIndex = left - 1;
    int rightIndex = right + 1;
    while (true)
    {
        while (array[++leftIndex] < pivot);
        while (array[--rightIndex] > pivot);
        if (leftIndex >= rightIndex)
        {
            break;
        }
        swap(array[leftIndex], array[rightIndex]);
    }
    quickSortFirst(array, left, rightIndex);
    quickSortFirst(array, rightIndex + 1, right);
}

// Precondition: vector<int>&, int, int
// Sorts array using quick sort with pivot at the mid point
// Postcondition: none
void quickSortMiddle(std::vector<int>& array, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int pivot = array[left + (right - left) / 2];
    int leftIndex = left - 1;
    int rightIndex = right + 1;
    while (true)
    {
        while (array[++leftIndex] < pivot);
        while (array[--rightIndex] > pivot);
        if (leftIndex >= rightIndex)
        {
            break;
        }
        swap(array[leftIndex], array[rightIndex]);
    }
    quickSortMiddle(array, left, rightIndex);
    quickSortMiddle(array, rightIndex + 1, right);
}
