/*
This is a generic program that randomly generates arrays between 1-10,
and sorts them using various common sorting algorithms, including 
Selection Sort, Bubble Sort, Insertion Sort, Merge Sort, and Quick Sort.

Completed on 05/19/2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Function that takes in an array, and creates an array of unique values
//between 1-10
void shuffle(int * arr)
{
    int i = 0;
    
    //declare used array of flags
    int * used = calloc(10, sizeof(int));
    while (i < 10)
    {
        //generate our random value
        int r = rand() % 10 + 1;

        //if this value has already been used, try something else
        if (used[r - 1])
            continue;
        
        //after using a variable, flag the corresponding index in the used
        //array as 1, so that we don't use it again
        used[r - 1] = 1;
        arr[i] = r;
        i++;
    }

    printf("\nUNSORTED RANDOMLY GENERATED ARRAY: \n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void selectionSort(int * arr)
{
    //Declare our temp variable used in swapping mechanism
    int temp;

    //loop until size - 1, in our case, hard coded 9 because our array is of size 10
    for (int i = 0; i < 9; i++)
    {
        //create a new variable to use as an index in swap, updates as we go
        int n = i;
        
        //starting at the index following i, traverse the rest of the array, looking for elements smaller than
        //the current minimum. 
        
        //For example, in the array: 4 5 2 6 7 1 7, when i = 0, we start at the 5 (index 1), and traverse the array
        //updating n to the current j index if we find something less than the current min. This will keep updating
        //throughout the array. When we reach the one, arr[n] = 2, but because 1 < 2, n is now = index of "1", which
        //is 5 in this little example. So now, arr[n] = 1. Once we're done traversing the array, we know that arr[n]
        //is the minimum element, so we should swap it with arr[i] (arr[0] right now). We then go to i = 1, and do
        //the same thing. That's the essence of the selection sort. 
        for (int j = i + 1; j < 10; j++)
        {
            if (arr[j] < arr[n])
                n = j; //update the index to the new minimum
        }

        //Basic and traditional swap mechanism using a temp variable
        temp = arr[i];
        arr[i] = arr[n];
        arr[n] = temp;
    }

    //print the resulting sorted array
    printf("\nAFTER SELECTION SORT: \n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


void bubbleSort(int * arr)
{
    //temp variable to be used in swap
    int temp;

    //Loop through the entire array
    for (int i = 0; i < 9; i++)
    {
        //Loop from the beginning only up to size - 2, because we use 
        //j + 1, and j + 1 on the last element would result in a seg fault

        //In a bubble sort, we traverse the whole array, and each time we encounter
        //a situation where the current value is greater than the value to its right
        //we swap them. Once we reach the end of the array, we repeat the process
        //until we finally end up with a sorted array. 
        for (int j = 0; j < 10 - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                //basic, traditional swap
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    //print the resulting sorted array
    printf("\nAFTER BUBBLE SORT: \n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insertionSort(int * arr)
{
    //initialize variables
    int val, ind;

    //To perform the insertion sort, we are essentially splittng the array
    //into a sorted and an unsorted section. We start from index 1, and we
    //move that element left until it's in the correct sorted position.

    //example: 4 1 3 5 2
    //We start on the 1, and we shift it left until it's in the correct spot
        //1 4 3 5 2
    //Next, we move to index 2, which is the 3, and we move that left until
    //it's in the right spot
        //1 3 4 5 2
    //We move to index 3, which is the 5. The 5 doesn't need to move at all
    //in this case, because it isn't < 4

    //Lastly, we move to index 4, which is the 2, and we shift it left until
    //it's in the right spot
        //1 3 4 2 5
        //1 3 2 4 5
        //1 2 3 4 5
    //And that's our sorted array! Insertion sort can be very fast for small arrays
    //even faster than quick and merge sorts, with an average runtime of O(n^2)
    for (int i = 1; i < 10; i++)
    {
        val = arr[i];
        ind = i;
        while (ind > 0 && arr[ind - 1] > val)
        {
            arr[ind] = arr[ind - 1];
            ind = ind - 1;
        }
        arr[ind] = val;
    }
    
    printf("\nAFTER INSERTION SORT....\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/*
The merge sort is a powerful sorting algorithm with a worst
case runtime of O(nlogn), making it much faster than any of 
the previous sorts in this program for large arrays. The merge
sort relies heavily on recursion to divide the problem into
subproblems using a divide and conquer style technique. 

To do a merge sort, we first must split the array all the way
down into single elements. We can do this easily with recursion.
This will allow us to sort the array in it's simplest form, then
run a loop to merge everything into a temp array. 

To merge the arrays, there are a few possible scenarios. 
    1) the left array has a lower value than the right array
    2) the right is lower than the left
    3) there are no more values in the left array
    4) there are no more values in the right array

The merge mechanism is best explained with an example, so lets take
the following 2 arrays as an example: 
    Left = {2, 5, 7, 9}, Right = {1, 4, 6, 8}

We first must use an indexing variable for the left and the right
to traverse them. We first need to check if that index has surpassed
the length of the sub array. If it hasn't, then we compare the values
in the corresponding indices in the sub arrays. 

In this case, we will compare Left[0] and Right[0], 2 vs 1. 
1 < 2, therefore, we will copy the value from Right[0] into 
the new temp array at index 0, and increment the index for the right array. 
Temp: {1, ....}, Left = {2, 5, 7, 9}, Right = {1, 4, 6, 8}
                         ^                        ^
                         L                        R

Next, we compare Left[0] to Right[1], 2 vs 4, 2 < 4, so we copy Left[0] into
the new temp array at index 1, then increment the left index. We repeat this
process until the array is sorted and merged into the temp array.
Temp: {1, 2 ...}, Left = {2, 5, 7, 9}, Right = {1, 4, 6, 8}
                             ^                     ^
                             L                     R

If we exhaust all the elements in one of the subarrays, we simply fill in
the rest of the remaining sub array into the temp, and we're done. 
*/

void mergeSort(int * arr, int n)
{
    if (n <= 1)
        return;

    //Recursively split the array
    int mid = n / 2;
    mergeSort(arr, mid);
    mergeSort(arr + mid, n - mid);

    //declare temp array to store final array
    int * temp = calloc(n, sizeof(int));
    int leftIndex = 0;
    int rightIndex = mid;

    for (int i = 0; i < n; i++)
    {
        //We have values remaining in both sub arrays
        if (leftIndex < mid && rightIndex < n)
        {
            //left array had the lower value
            if (arr[leftIndex] < arr[rightIndex])
            {
                temp[i] = arr[leftIndex];
                leftIndex++;
            }
            //right array had the lower value
            else
            {
                temp[i] = arr[rightIndex];
                rightIndex++;
            }
        }
        //Right array is empty, but left array still has items in it
        else if (leftIndex < mid)
        {
            temp[i] = arr[leftIndex];
            leftIndex++;
        }
        //Left array is empty, but right array still has items in it
        else
        {
            temp[i] = arr[rightIndex];
            rightIndex++;
        }
    }
    //copy temp over to arr and free temp
    for (int i = 0; i < n; i++)
    {
        arr[i] = temp[i];
    }
    free(temp);
}

// The quick sort is an extremely popular sorting algorithm that uses
// recursion, similarly to merge sort, to produce an average of O(nlogn)
// runtime to sort an array. The Quick Sort also uses a divide and conquer
// recursive technique, in which we partition the array to position our
// pivot value correctly. 

// The properties of a pivot value are:
//     1) All values to its right are greater than it
//     2) All values to its left are less than it
// To obtain and position a valid pivot, we have a couple of options. 
// Some people will choose the first element, and partitition based on that,
// others will start on the last element. In this code, I started with the first
// element of the array. 

// To partition the array, we start by initializing a front and back index to track
// our location. We then loop throughout the array, comparing our pivot value to 
// frontIndex position in the array. For example, if we had the following array:
//     {3, 5, 6, 1, 2, 4}
// We would compare the pivot (3) to arr[1] (5). If the frontIndex value is greater
// than our pivot, then we need to adjust the array by swapping that frontIndex value
// with the next index from the back of the array. If the frontIndex value is less
// than the pivot, then we simply increment the front index. Partitioning the above
// array would go as follows
//     {3, 5, 6, 1, 2, 4}  frontIndex = 1, n - backIndex = 5
//     {3, 4, 6, 1, 2, 5}  frontIndex = 1, n - backIndex = 4
//     {3, 2, 6, 1, 4, 5}  frontIndex = 1, n - backIndex = 3
//     {3, 2, 6, 1, 4, 5}  frontIndex = 2, n - backIndex = 3
//     {3, 2, 1, 6, 4, 5}  frontIndex = 2, n - backIndex = 3

// This should take n - 1 steps. Once this is all completed, we will finally swap
// the pivot with arr[frontIndex]. In this case, we would swap 3 and 1
//     {1, 2, 3, 6, 4, 5}
// As you can see, now 3 is a valid pivot, where all the elements to its left are
// less than it, and all the values to its right are greater than it. From here, 
// we simply do a couple of recursive calls on the sub arrays to finish the sort.

void quickSort(int * arr, int n)
{
    if (n <= 1) return;

    //initialize the pivot to the first element in the array
    int pivot = arr[0];
    int frontIndex = 0;
    int backIndex = 0;

    //starting from the element to the right of the pivot
    for (int i = 1; i < n; i++)
    {
        //the next value from the front is greater than the pivot, swap it
        //with the current value from the back
        if (pivot < arr[frontIndex+1])
        {
            backIndex++;
            int tmp = arr[frontIndex+1];
            arr[frontIndex+1] = arr[n - backIndex];
            arr[n - backIndex] = tmp;
        }
        //the next value from the front is less than the pivot, simply increment
        //the current front index
        else
        {
            frontIndex++;
        }
    }

    //All we have to do now is place the pivot in the correct spot, which should be
    //indicated by the frontIndex. Simple swap arr[0] with the frontIndex position
    int tmp = arr[frontIndex];
    arr[frontIndex] = arr[0];
    arr[0] = tmp;

    //recursive calls
    quickSort(arr, frontIndex);

    //pointer math to recursively pass a sub array
    quickSort(arr + frontIndex + 1, backIndex);
}

//Driver main to test out the sorts
int main()
{
    //Start with a blank array so our shuffle function can create unique ones
    int * arr = calloc(10, sizeof(int));
    shuffle(arr);
    selectionSort(arr);
    shuffle(arr);
    bubbleSort(arr);
    shuffle(arr);
    insertionSort(arr);
    shuffle(arr);
    mergeSort(arr, 10);

    //Printing in main because Merge Sort is recursive
    printf("\nAFTER MERGE SORT...\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    shuffle(arr);
    quickSort(arr, 10);

    //Printing in main because Quick Sort is recursive, would be scuffed
    printf("\nAFTER QUICK SORT...\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\nI want to die\n");

    return 0;
}