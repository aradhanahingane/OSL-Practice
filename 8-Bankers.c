#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(){
  int n,m;
  printf("Enter the no. of processes :");
  scanf("%d",&n);
  printf("Enter no. of resources :");
  scanf("%d",&m);

  int max[n][m],alloc[n][m],need[n][m],avail[m],finished[n],safe[n];


  printf("Enter the max matrix : (%d *  %d)",n,m);
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      scanf("%d",&max[i][j]);
    }
  }

  printf("Enter the alloc matrix : (%d *  %d)",n,m);
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      scanf("%d",&alloc[i][j]);
    }
  }

  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      need[i][j]=max[i][j]-alloc[i][j];
    }
  }

  printf("Enter the available resources : (%d)",m);
  for(int i=0;i<m;i++){
    scanf("%d",&avail[i]);
  }

  for(int i=0;i<n;i++){
    finished[i]=0;
  }

  int count=0;
  while(count<n){
    int found=0;
    for(int i=0;i<n;i++){
      if(finished[i]==0){
        int isSafe=1;
        for(int j=0;j<m;j++){
          if(need[i][j]>avail[j]){
            isSafe=0;
            break;
          }
        }
        if(isSafe){
          for(int j=0;j<m;j++){
            avail[j]+=alloc[i][j];
           
          }
          found=1;
          safe[count]=i;
          count++;
          finished[i]=1;
        }
      }
    }
    if(found==0){
      printf("System is in unsafe state !");
      return 0;
    }
  }

    for(int i=0;i<n;i++){
      printf("p%d ->",safe[i]);
    }

  return 0;
}