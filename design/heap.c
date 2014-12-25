#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;
const int HEAP_SIZE = 13; //堆積樹大小
 
int parent(int);
int left(int);
int right(int);
void Max_Heapify(int [], int, int);
void Build_Max_Heap(int []);
void print(int []);
void HeapSort(int [], int);
 
/*父結點*/
int parent(int i)
{
    return (int)floor((i - 1) / 2);
}
 
/*左子結點*/
int left(int i)
{
    return (2 * i + 1);
}
 
/*右子結點*/
int right(int i)
{
    return (2 * i + 2);
}
 
/*單一子結點最大堆積樹調整*/
void Max_Heapify(int A[], int i, int heap_size)
{
	print(A);
    int l = left(i);
    int r = right(i);
    int largest;
    int temp;
    if(l < heap_size && A[l] > A[i])
    {
        largest = l;
    }
    else
    {
        largest = i;
    }
    if(r < heap_size && A[r] > A[largest])
    {
        largest = r;
    }
    if(largest != i)
    {
        temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        Max_Heapify(A, largest, heap_size);
    }
}
 
/*建立最大堆積樹*/
void Build_Max_Heap(int A[])
{
    for(int i = (HEAP_SIZE-1)/2; i >= 0; i--)
    {
        Max_Heapify(A, i, HEAP_SIZE);
    }
}
 
/*印出樹狀結構*/
void print(int A[])
{
    for(int i = 0; i < HEAP_SIZE;i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}
 
/*堆積排序程序碼*/
void HeapSort(int A[], int heap_size)
{
    Build_Max_Heap(A);
    int temp;
    for(int i = heap_size - 1; i >= 0; i--)
    {
        temp = A[0];
        A[0] = A[i];
        A[i] = temp;
        Max_Heapify(A, 0, i);
    }
    print(A);
}
 
/*輸入資料並做堆積排序*/
int main(int argc, char* argv[])
{
    int A[HEAP_SIZE] = {19, 1, 10, 14, 16, 4, 7, 9, 3, 2, 8, 5, 11};
    HeapSort(A, HEAP_SIZE);
    system("pause");
    return 0;
}
