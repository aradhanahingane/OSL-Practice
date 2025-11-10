#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

void bubbleSort(int nums[],int n){
  for(int i=0;i<n-1;i++){
    for(int j=0;j<n-i-1;j++){
      if(nums[j]>nums[j+1]){
        int temp=nums[j];
        nums[j]=nums[j+1];
        nums[j+1]=temp;
      }
    }
  }
}

void selectionSort(int nums[], int n){
  for(int i=0;i<n-1;i++){
    int min_idx = i;
    for(int j=i+1;j<n;j++){
      if(nums[j] < nums[min_idx]){
        min_idx = j;
      }
    }
    if(min_idx != i){
      int tmp = nums[i];
      nums[i] = nums[min_idx];
      nums[min_idx] = tmp;
    }
  }
}

void printNums(int nums[],int n){
  printf("Sorted array :");
  for(int i=0;i<n;i++){
    printf("%d ",nums[i]);
  }
  printf("\n");
}

int main(){
  int n;
  printf("Enter no. of elements in array : ");
  scanf("%d",&n);
  printf("Enter the array elements : ");
  int nums[n];
  for(int i=0;i<n;i++){
    scanf("%d",&nums[i]);
  }

  pid_t pid=fork();
  
  if(pid<0){
    printf("Something went wrong !");
  }
  else if(pid==0){
    printf("Inside the child process pid:%d\n",getpid());
    bubbleSort(nums,n);
    printNums(nums,n);
  }
  else{
    printf("Inside the parent process process id :%d\n",getpid());
    printf("Waiting for child to execute! ");
    wait(NULL);
    selectionSort(nums,n);
    printNums(nums,n);
    
  }
  return 0;
}