#include <stdio.h>
#include <stdlib.h>

static int compare(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}

static void two_sum(int *nums, int low, int high, int target, int **results, int *count)
{
    while (low < high) {
        int diff = target - nums[low];
        if (diff > nums[high]) {
            while (++low < high && nums[low] == nums[low - 1]) {}
        } else if (diff < nums[high]) {
            while (--high > low && nums[high] == nums[high + 1]) {}
        } else {
            results[*count] = malloc(3 * sizeof(int));
            results[*count][0] = -target;
            results[*count][1] = nums[low];
            results[*count][2] = nums[high];
            (*count)++;
            while (++low < high && nums[low] == nums[low - 1]) {}
            while (--high > low && nums[high] == nums[high + 1]) {}
        }
    }
}

/**
 ** Return an array of arrays of size *returnSize.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
static int** threeSum(int* nums, int numsSize, int* returnSize)
{
    if (numsSize < 3) {
        return NULL;
    }

    qsort(nums, numsSize, sizeof(*nums), compare);

    *returnSize = 0;
    int i, j, capacity = 50000;
    int **results = malloc(capacity * sizeof(int *));
    for (i = 0; i < numsSize; i++) {
        if (i == 0 || i > 0 && nums[i] != nums[i - 1]) {
            two_sum(nums, i + 1, numsSize - 1, -nums[i], results, returnSize);
        }
    }
    return results;
}

int main(void)
{
    int i, count;
    //int nums[] = { -1, 0, 1, 2, -1, -4 };
    //int nums[] = { 0, 0, 0 };
    //int nums[] = { -1, 0, 1, 0 };
    int nums[] = {-2,0,0,2,2};
    int **triplets = threeSum(nums, sizeof(nums) / sizeof(*nums), &count);
    for (i = 0; i < count; i++) {
        printf("%d %d %d\n", triplets[i][0], triplets[i][1], triplets[i][2]);
    }

    return 0;
}

/*  另一解法 
void quickSort(int* nums,int first,int end){
    int temp,l,r;
    if(first>=end)return;
    temp=nums[first];
    l=first;r=end;
    while(l<r){
        while(l<r && nums[r]>=temp)
		r--;
        if(l<r)
		nums[l]=nums[r];
        while(l<r && nums[l]<=temp)
		l++;
        if(l<r)
		nums[r]=nums[l];
    }
    nums[l]=temp;
    quickSort(nums,first,l-1);
    quickSort(nums,l+1,end);
}
int** threeSum(int* nums, int numsSize, int* returnSize) {
    int i,sum,top=-1,begin,end;
    int** res=(int**)malloc(sizeof(int*)*(numsSize*(numsSize-1)*(numsSize-2))/6);
    if(numsSize<3){
        *returnSize=0;
        return res;
    }
    quickSort(nums,0,numsSize-1);
    for(i=0;i<numsSize;i++){
        if(nums[i]>0)break;
        if(i>0 && nums[i]==nums[i-1])continue;
        begin=i+1;end=numsSize-1;
        while(begin<end){
            sum=nums[i]+nums[begin]+nums[end];
            if(sum==0){
                top++;
	            res[top]=(int*)malloc(sizeof(int)*3);
	            res[top][0]=nums[i];res[top][1]=nums[begin];res[top][2]=nums[end];
	            begin++;end--;
	            while(begin<end && nums[begin]==nums[begin-1])begin++;
	            while(begin<end && nums[end]==nums[end+1])end--;
            }else if(sum>0) end--;
            else begin++;
        }
    }
    *returnSize=top+1;
    return res;
}

*/
