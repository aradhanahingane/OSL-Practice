#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
void bubbleSort(int n,int nums[]){
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
int main(){
    int n;
    printf("Enter the no. of elements :");
    scanf("%d",&n);
    int nums[n];
    printf("Enter the array elements :");
    for(int i=0;i<n;i++){
        scanf("%d",&nums[i]);
    }
    bubbleSort(n,nums);

    pid_t pid=fork();

    if(pid<0){
        printf("error occured !");
    }
    else if(pid==0){
        char* argv[n+2];
        argv[0]="./execexample";
        for(int i=0;i<n;i++){
            char* strnum=malloc(10);
            sprintf(strnum,"%d",nums[i]);
            argv[i+1]=strnum;
        }
        argv[n+1]=NULL;

        execve(argv[0],argv,NULL);

        perror("exec failed");
        exit(0);
    }
    else{
        wait(NULL);
        printf("Inside parent process ! waiting for child to finish");
    }
    return 0;
}