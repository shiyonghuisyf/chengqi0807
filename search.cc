#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
using std::cout;
using std::endl;

int binarySearch(double * array, int N, double target)
{
    if(array == NULL || N <= 0)
    {
        return -1;
    }
    int low = 0, high = N - 1, mid;
    while(low <= high)
    {
        mid = (low + high)/2;
        if(fabs(array[mid] - target) < 0.000001)
        {
            return mid;
        }else if(array[mid] > target )
        {
            high = mid - 1;
        }else {
            low = mid + 1;
        }
    }
    return -1;
}

int linearSearch(double * array, int N, double target)
{
    if(array == NULL || N <= 0)
    {
        return -1;
    }
    for(int i = 0; i != N; ++i)
    {
        if(fabs(array[i] - target) < 0.000001)
        {
            return i;
        }
    }
    return -1;
}

void getRandomArray(int n, int left, int right, double * array)//生成随机数组
{
    right *= 3;
    srand(time(NULL));
    for(int i = 0; i != n; ++i)
    {
        array[i] = (double)((rand() % (right - left))/3.333 + left);
    }
}

void swap(double & a, double & b)
{
    double temp = a;
    a = b;
    b = temp;
}

int partiton(double * arr, int left, int right)
{
    int k = left;
    for(int i = left; i != right; ++i)
    {
        if(arr[i] < arr[right])
        {
            swap(arr[k], arr[i]);
            ++k;
        }
    }
    swap(arr[right], arr[k]);
    return k;
}

void arrQuick(double * arr, int left, int right)
{
    int pivot;
    if(left < right)
    {
        pivot = partiton(arr, left, right);
        arrQuick(arr, left, pivot - 1);
        arrQuick(arr, pivot + 1, right);
    }
}

void test()
{
    for(int i = 50; i != 100; ++i)
    {
        double * array = new double[i];
        memset(array, 0, sizeof(double) * i);
        getRandomArray(i, 0, 1000, array);
        //for(int j = 0; j != i; ++j)
        //{
        //    cout << array[j] << "   ";
        //}
        //cout << endl;
        srand(time(NULL));
        int num = rand() % i;
        int findNum = 0;
        arrQuick(array, 0, i - 1);
        //for(int j = 0; j != i; ++j)
        //{
        //    cout << array[j] << " ";
        //}
        //cout << endl;
        struct timeval start, end;
        gettimeofday(& start, NULL);
        findNum = binarySearch(array, i, array[num]);
        gettimeofday(& end, NULL);
        printf("count: %d binarySearch cost time : %ld\n", i, (end.tv_sec - start.tv_sec)*1000000 + end.tv_usec - start.tv_usec);
        printf("num %d, find %d \n", num, findNum);
        
        struct timeval start1, end1;
        gettimeofday(& start1, NULL);
        findNum = linearSearch(array, i, array[num]);
        gettimeofday(& end1, NULL);
        printf("count: %d linearSearch cost time : %ld\n", i, (end1.tv_sec - start1.tv_sec)*1000000 + end1.tv_usec - start1.tv_usec);
        printf("num %d, find %d \n", num, findNum);
        delete [] array;
        sleep(1); 
    }
}

int main()
{
    test();
    return 0;
}
