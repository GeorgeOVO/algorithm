#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list_queue.h"
#include <math.h>

#define TYPE int
#define LEN 20
#define PH "%02d "
#define SWAP(a,b) {typeof(a) t=(a);(a)=(b);(b)=t;}

typedef void (*Sort_FP)(TYPE*,size_t);

void show(TYPE* arr,size_t len)
{
	for(int i=0; i<len; i++)
	{
		printf(PH,arr[i]);
	}
	printf("\n");
}

// 冒泡排序
void bubble_sort(TYPE* arr,size_t len)
{
	printf("%s:\n",__func__);
	show(arr,LEN);
	bool flag = true;
	for(int i=len-1; i>0 && flag; i--)
	{
		flag = false;
		for(int j=0; j<i; j++)
		{
			if(arr[j] > arr[j+1])
			{
				SWAP(arr[j],arr[j+1]);
				flag = true;
			}
		}
	}
}

// 选择排序
void selection_sort(TYPE* arr,size_t len)
{
	printf("%s:\n",__func__);
	show(arr,LEN);
	for(int i=0; i<len-1; i++)
	{
		int min = i;
		for(int j=i+1; j<len; j++)
		{
			if(arr[j] < arr[min]) min = j;
		}
		if(i != min) SWAP(arr[i],arr[min]);
	}
}

// 插入排序
void insertion_sort(TYPE* arr,size_t len)
{
	printf("%s:\n",__func__);
	show(arr,LEN);
	for(int i=1,j=0; i<len; i++)
	{
		int val = arr[i];  // 要插入的数据
		for(j=i; j>0 && arr[j-1] > val; j--) // j表示要插入的位置
		{
			arr[j] = arr[j-1];
		}
		if(j!=i) arr[j] = val;  // j=i意味着j未移动过，不必重新赋值
	}
}

// 希尔排序
void shell_sort(TYPE* arr,size_t len)
{
	printf("%s:\n",__func__);
	show(arr,LEN);
	for(int k=len/2; k>0; k/=2) // k增量
	{
		for(int i=k,j=0; i<len; i++)
		{
			int val = arr[i];
			for(j=i; j-k>=0 && arr[j-k] > val; j-=k)
			{
				arr[j] = arr[j-k];
			}
			if(j != i) arr[j] = val;
		}
	}
}

void _quick(TYPE* arr,int left,int right)
{
	if(left >= right) return;
	int l = left,r = right,p = left;
	// 备份标杆p的值
	int val = arr[p];

	while(l < r)
	{
		// 在p右边找比val小的数
		while(r > p && arr[r] >= val) r--;
		// r在p的右边找到比val小的数
		if(r > p)
		{
			arr[p] = arr[r];
			p = r;
		}
		
		while(l < p && arr[l] <= val) l++;
		if(l < p)
		{
			arr[p] = arr[l];
			p = l;
		}
	}
	arr[p] = val;
	_quick(arr,left,p-1);
	_quick(arr,p+1,right);
}

// 快速排序
void quick_sort(TYPE* arr,size_t len)
{
	printf("%s:\n",__func__);
	show(arr,LEN);
	_quick(arr,0,len-1);
}

// 合并  l左部分最左的下标  p左部分最右  p+1右部分最左  r右部分最右
void __merge(TYPE* arr,TYPE* temp,int l,int p,int r)
{
	// 合并前  左右部分各自有序
	if(arr[p] <= arr[p+1]) return;

	int s = l;
	int i = l,j = p+1;
	while(i <= p && j <= r)
	{
		// 左右部分从开头进行比较
		if(arr[i] <= arr[j])
			temp[s++] = arr[i++];
		else
			temp[s++] = arr[j++];
	}
	// 比完后，把多的部分剩余的数据依次存入temp
	while(i <= p) temp[s++] = arr[i++];
	while(j <= r) temp[s++] = arr[j++];
	// 把temp还原回对应位置的arr
	memcpy(arr+l,temp+l,sizeof(TYPE)*(r-l+1));
}

// 拆分
void _merge(TYPE* arr,TYPE* temp,int l,int r)
{
	if(l >= r) return;
	int p = (l+r)/2;
	_merge(arr,temp,l,p);
	_merge(arr,temp,p+1,r);
	// 合并
	__merge(arr,temp,l,p,r);
}

// 归并排序
void merge_sort(TYPE* arr,size_t len)
{
	printf("%s:\n",__func__);
	show(arr,LEN);
	
	// 申请临时存储空间
	TYPE* temp = malloc(sizeof(TYPE)*len);
	_merge(arr,temp,0,len-1);
	free(temp);
}

// 计数排序
void count_sort(TYPE* arr,size_t len)
{
	printf("%s:\n",__func__);
	show(arr,LEN);
	
	TYPE max = arr[0],min = arr[0];
	for(int i=1; i<len; i++)
	{
		if(arr[i] > max) max = arr[i];
		if(arr[i] < min) min = arr[i];
	}

	TYPE* temp = calloc(sizeof(TYPE),max-min+1);
	for(int i=0; i<len; i++)
	{
		temp[arr[i]-min]++;
	}
	for(int i=0,j=0; i<max-min+1; i++)
	{
		while(temp[i]--) arr[j++] = i+min; 
	}
	free(temp);
}

// cnt桶数 range桶中数据的差值
void _bucket(TYPE* arr,size_t len,int cnt,TYPE range)
{
	// 申请桶内存
	// bucket_s指向桶的开头位置
	// bucket_e指向桶的末尾  接下去要入桶的位置
	TYPE* bucket_s[cnt],*bucket_e[cnt];
	for(int i=0; i<cnt; i++)
	{
		// 数据有可能全在一个桶内
		bucket_s[i] = malloc(sizeof(TYPE)*len);
		bucket_e[i] = bucket_s[i];
	}

	// 把数据按照对应的范围放入对应的桶中
	for(int i=0; i<len; i++)
	{
		for(int j=0; j<cnt; j++)
		{
			if(j*range <= arr[i] && arr[i] < (j+1)*range)
			{
				*(bucket_e[j]) = arr[i];
				bucket_e[j] += 1;
				break;
			}
		}
	}

	// 通过其他排序对各个桶中的数据排序
	for(int i=0; i<cnt; i++)
	{
		// 计算桶中元素的数量
		int size = bucket_e[i] - bucket_s[i];
		// 其他排序
		if(size > 1) 
			bubble_sort(bucket_s[i],size);
		// 按照先后顺序 放入原内存中
		memcpy(arr,bucket_s[i],size*sizeof(TYPE));
		arr += size;
		free(bucket_s[i]);
	}
}

// 桶排序
void bucket_sort(TYPE* arr,size_t len)
{
	printf("%s:\n",__func__);
	show(arr,LEN);
	_bucket(arr,len,4,25);	
}	

// 基数排序
void radix_sort(TYPE* arr,size_t len)
{
	printf("%s:\n",__func__);
	show(arr,LEN);
	
	ListQueue* queue[10] = {};
	for(int i=0; i<10; i++)
	{
		queue[i] = create_list_queue();
	}

	// 循环次数由最大值的位数决定
	TYPE max = arr[0];
	for(int i=1; i<len; i++)
	{
		if(arr[i] > max) max = arr[i];
	}

	// i是1表示处理个位，2表示处理十位...
	for(int i=1,k=1; max/k>0; k*=10,i++)
	{
		int mod = pow(10,i);
		int div = mod/10;
		for(int j=0; j<len; j++)
		{
			// 获取arr[j] 某位的数
			int index = arr[j]%mod/div;
			push_list_queue(queue[index],arr[j]);
		}
		// 对所有队列依次出队回原内存中
		for(int j=0,i=0; j<10; j++)
		{
			while(!empty_list_queue(queue[j]))
			{
				arr[i++] = front_list_queue(queue[j]);
				pop_list_queue(queue[j]);
			}
		}
	}
	for(int i=0; i<10; i++)
		destroy_list_queue(queue[i]);
}

int main(int argc,const char* argv[])
{
	Sort_FP fp[] = {bubble_sort,selection_sort,insertion_sort,shell_sort,quick_sort,
		merge_sort,count_sort,bucket_sort,radix_sort};
	TYPE arr[LEN] = {};
	for(int i=0; i<sizeof(fp)/sizeof(fp[0]); i++)
	{
		for(int j=0; j<LEN; j++)
		{
			printf("---");
			arr[j] = rand()%100;
		}
		printf("\n");
		fp[i](arr,LEN);
		show(arr,LEN);
	}
	return 0;
}
