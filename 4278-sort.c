#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int*array;
void*sort(void*args);
void merge(int low,int middle, int high);
struct index{
int l;
int h;
};


void*sort(void*args){
struct index*info = args;//create pointer to struct with the passed parameters from pthread main
int l1=info->l; //assign l1 with the value of the struct member l(0)
int h1=info->h;//assign  h2 with the value of the struct member h(size-1)
int middle = l1+(h1-l1)/2 ;//to avoid overflow
pthread_t leftThread,rightThread;// create 2 threads
struct index left,right;// create 2 struct variables
left.l=l1;
left.h=middle;
right.l=middle+1;
right.h=h1;
if(l1 < h1){
//create thread for the left array,call sort function,pass parameters
pthread_create(&leftThread,NULL,sort,&left);
//create thread for the right array, call sort function,pass parameters
pthread_create(&rightThread,NULL,sort,&right);
pthread_join(leftThread,NULL);
pthread_join(rightThread,NULL);
merge(l1,middle,h1);
}}


void merge(int low, int middle,int high){
int count = high-low;//element count
int leftend=middle;//left end index no
int rightbeg = middle+1;//right begining index no
int k=low;//left begining index
int*temp =malloc(100*sizeof(int));//dynamically allocate memory for temporary array
while( (low<=leftend) && (rightbeg<=high))
{
  if (array[low]<=array[rightbeg]){
      temp[k] = array[low];
       k++;
       low++;
     }
  else {
    temp[k] = array[rightbeg];
    k++;
    rightbeg++;
    }
}


while(low<=leftend){
  temp[k] = array[low];
   low++;
   k++;
}
while(rightbeg <= high){
temp[k] = array[rightbeg];
rightbeg++;
k++;
}
for(int i=0; i<=count;i++){
array[high] = temp[high];
high--;
}
}

int main(){
int length;
// construct a pointer for struct index
struct index*info = (struct index*)malloc(sizeof(struct index));
pthread_t thread;// define new thread
FILE*input = fopen("merge.txt","r");
FILE*output = fopen("output.txt","w");
fscanf(input,"%d",&length);//scan the length of array
array =malloc(length*sizeof(int));//dynamically allocate memory for the array
for(int i=0; i<length; i++){
fscanf(input,"%d",&array[i]);
printf("%d",array[i]);
printf("\t");
}
printf("\n");
printf("The length is: %d \n",length);
int size = length;
//create a variable from the struct "index" called main
struct index main;
// assign members l and h of the struct variable "main" with values
main.l = 0; 
main.h = size-1;
//create a thread that calls the sort function and passes the info in "main" as input parameter to it
pthread_create(&thread,NULL,sort,&main);
//waits for thread to terminate and once it terminates it returns immediately
pthread_join(thread,NULL);

for(int i=0; i<size;i++){
fprintf(output,"%d",array[i]);
fprintf(output,"\t");
}
fprintf(output,"\n");
fclose(input);
fclose(output);
return 0;
}
