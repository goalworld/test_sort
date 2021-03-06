
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
static void 
printArr(int arr[],int len)
{
	int i=0;
	for(;i<len&&i<20;i++){
		printf("%d ",arr[i]);
	}
	if(len>20) printf("...");
	printf("\n");
}
static inline void SWAP(int *a,int *b){int c = *(a);*(a) = *(b);*(b) = c;}
static void 
insertSort(int arr[],int len)
{
	if(len <= 1)return;
	int i,j;
	for(i=1;i<len;i++){
		int *insert = &arr[i];
		j = i-1;
		while(*insert < arr[j] && j>=0){
			SWAP(insert,(arr+j));
			insert = (arr+j);
			j--;
		}
	}
}

static void 
bumpSort(int arr[],int len)
{
	if(len <= 1)return;
	int i = 0;
	for( ;i<len;i++){
		int j=len-1;
		for(;j>i;j--){
			if(arr[j]<arr[j-1]){
				SWAP(arr+j,arr+j-1);
			}
		}
	}
}
#define LEFT(i)(i*2+1)
#define RIGHT(i)(i*2+2)
static void 
maxHeap(int arr[],int c,int len)
{
	int l=LEFT(c);
	int r=RIGHT(c);
	if(l<len && arr[l]>arr[c]){
		SWAP(arr+l,arr+c);
	}
	if(r<len && arr[r]>arr[c]){
		SWAP(arr+r,arr+c);
	}
}
static void 
buildHeap(int arr[],int len)
{
	if(len <= 1)return;
	int i = len/2;
	for(;i>=0;i--){
		maxHeap(arr,i,len);
	}
}
static void 
heapSort(int arr[],int len)
{
	if(len <= 1)return;
	int sublen=len;
	for(;sublen>1;sublen--){
		buildHeap(arr,sublen);
		SWAP(arr,arr+sublen-1);
	}
}
static void 
randFill(int arr[],int len)
{
	assert(len>=1);
	int i=0;
	for(i;i<len;i++){
		arr[i]= rand()%len;
	}
}

void 
_quickSort(int arr[],int p,int q)
{
	if(p>=q){
		return;
	}
	int x = arr[q];
	int i = p-1,j=p;
	for(;j<q;j++){
		if(arr[j]<x){
			i++;
			SWAP(&arr[j],&arr[i]);
		}
	}
	SWAP(&arr[i+1],&arr[q]);
	_quickSort(arr,p,i);
	_quickSort(arr,i+2,q);
}
static void quickSort(int arr[],int len){
	_quickSort(arr,0,len-1);
}
static clock_t 
sortTime(int arr[],int len,void(*sortfn)(int arr[],int len))
{
	printArr(arr,len);
	clock_t pre = clock(),end;
	sortfn(arr,len);
	end = clock();
	printArr(arr,len);
	return end-pre;
}
int 
main(int argc,char*argv[])
{
	if(argc !=2 ){
		abort();
	}
	int len = atoi(argv[1]);
	int *arr   = malloc(sizeof(int)*len);
	int *arr1 = malloc(sizeof(int)*len);
	int *arr2 = malloc(sizeof(int)*len);;
	int *arr3 = malloc(sizeof(int)*len);
	srand(clock());
	randFill(arr,len);
	memcpy(arr1,arr,(sizeof(int)*len));
	memcpy(arr2,arr,(sizeof(int)*len));
	memcpy(arr3,arr,(sizeof(int)*len));
	printf("[insertSort]-> %d ms\n",  sortTime(arr,len,insertSort));
	printf("[bumpSort  ]-> %d ms\n",  sortTime(arr1,len,bumpSort) );
	printf("[heapSort  ]-> %d ms\n",  sortTime(arr2,len,heapSort));
	printf("[quickSort ]-> %d ms\n",  sortTime(arr3,len,quickSort));
	return 0;
}


