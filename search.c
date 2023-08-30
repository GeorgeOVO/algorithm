#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 顺序查找
int order_search(int* arr,int len,int key)
{
	for(int i=0; i<len; i++)
	{
		if(key == arr[i]) return i;
	}
	return -1;
}

void sort(int* arr,int len)
{
	for(int i=0; i<len-1; i++)
	{
		for(int j=i+1; j<len;j++)
		{
			if(arr[i] > arr[j])
			{
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

// 循环二分查找
int binary_search_for(int* arr,int len,int key)
{
	int l = 0,r = len-1;
	while(l <= r)
	{
		int m = (l+r)/2;
		if(arr[m] == key) return m;
		if(arr[m] > key) r = m-1;
		else l = m+1;
	}
	return -1;
}

int _binary(int* arr,int l,int r,int key)
{
	if(l > r) return -1;
	int m = (l+r)/2;
	if(key == arr[m]) return m;
	if(key < arr[m])
		return _binary(arr,l,m-1,key);
	else
		return _binary(arr,m+1,r,key);
}

// 递归二分查找
int binary_search_recusion(int* arr,int len,int key)
{
	return _binary(arr,0,len-1,key);
}

// 哈希查找
int hash_search(int* arr,int len,int key)
{
	// 直接定址法
	// 创建哈希表
	int hash[100000] = {};
	// 根据数据做标记
	for(int i=0; i<len; i++)
	{
		hash[arr[i]]++; 
	}
	// 查找
	return hash[key];
}

int hash_search_data(int* arr,int len,int key)
{
	// 数据分析法
	int max = arr[0],min = arr[0];
	for(int i=0; i<len; i++)
	{
		if(arr[i] > max) max = arr[i];
		if(arr[i] < min) min = arr[i];
	}
	if(key<min || key>max) return -1;
	// 创建哈希表
	int hash[max-min+1];
	memset(hash,0,sizeof(int)*(max-min+1));

	// 经过哈希函数来标记
	for(int i=0; i<len; i++)
	{
		hash[arr[i]-min]++;
	}
	return hash[key-min];
}

int main(int argc,const char* argv[])
{
	int arr[10] = {};
	for(int i=0; i<10; i++)
	{
		arr[i] = rand()%100;
		printf("%d ",arr[i]);
	}
	printf("\norder_search:%d\n",order_search(arr,10,77));
	printf("hash_search:%d\n",hash_search(arr,10,77));
	printf("hash_search_data:%d\n",hash_search_data(arr,10,77));
	sort(arr,10);
	for(int i=0; i<10; i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\nbinary_search_for:%d\n",binary_search_for(arr,10,49));
	printf("binary_search_recusion:%d\n",binary_search_recusion(arr,10,49));
	return 0;
}
