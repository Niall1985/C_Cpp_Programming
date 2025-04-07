#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void evenparity0(int data_size, int input_arr[]){
  int size = data_size+1;
  int output_arr[size];
  int count = 0;
  for(int i = 0 ; i < data_size ; i++){
    output_arr[i] = input_arr[i];
  }
  
  for(int i = 0 ; i < data_size ; i++){
    if(input_arr[i] == 0){
      count++;
    }
  }
  
  if(count%2 == 0){
    output_arr[data_size] = 1;
  }
  else{
    output_arr[data_size] = 0;
  }
  
  for(int i = 0 ; i < size ; i++){
    printf("%d ", output_arr[i]);
  }
}

void evenparity1(int data_size, int input_arr[]){
  int size = data_size+1;
  int output_arr[size];
  int count = 0;
  for(int i = 0 ; i < data_size ; i++){
    output_arr[i] = input_arr[i];
  }
  
  for(int i = 0 ; i < data_size ; i++){
    if(input_arr[i] == 1){
      count++;
    }
  }
  
  if(count%2 == 0){
    output_arr[data_size] = 0;
  }
  else{
    output_arr[data_size] = 1;
  }
  
  for(int i = 0 ; i < size ; i++){
    printf("%d ", output_arr[i]);
  }
}

 void oddparity0(int data_size, int input_arr[]){
  int size = data_size+1;
  int output_arr[size];
  int count = 0;
  for(int i = 0 ; i < data_size ; i++){
    output_arr[i] = input_arr[i];
  }
  
  for(int i = 0 ; i < data_size ; i++){
    if(input_arr[i] == 0){
      count++;
    }
  }
  
  if(count%2 != 0){
    output_arr[data_size] = 1;
  }
  else{
    output_arr[data_size] = 0;
  }
  
  for(int i = 0 ; i < size ; i++){
    printf("%d ", output_arr[i]);
  }
}

void oddparity1(int data_size, int input_arr[]){
  int size = data_size+1;
  int output_arr[size];
  int count = 0;
  for(int i = 0 ; i < data_size ; i++){
    output_arr[i] = input_arr[i];
  }
  
  for(int i = 0 ; i < data_size ; i++){
    if(input_arr[i] == 1){
      count++;
    }
  }
  
  if(count%2 != 0){
    output_arr[data_size] = 0;
  }
  else{
    output_arr[data_size] = 1;
  }
  
  for(int i = 0 ; i < size ; i++){
    printf("%d ", output_arr[i]);
  }
}

int main(){
  int data_size;
  scanf("%d", &data_size); 
  
  int input_arr[data_size];
  for(int i = 0 ; i < data_size ; i++){
    scanf("%d", &input_arr[i]); 
  }
  
  int bit_choice;
  scanf("%d", &bit_choice); 
  
  char parity_choice[10];
  scanf("%s ", parity_choice); 
  
  if(bit_choice == 0 && strcmp(parity_choice, "even") == 0){
    evenparity0(data_size, input_arr);
  }
  else if(bit_choice == 1 && strcmp(parity_choice, "even") == 0){
    evenparity1(data_size, input_arr);
  }
  else if(bit_choice == 0 && strcmp(parity_choice, "odd") == 0){
    oddparity0(data_size, input_arr);
  }
  else if(bit_choice == 1 && strcmp(parity_choice, "odd") == 0){
    oddparity1(data_size, input_arr);
  }
  else{
    printf("Invalid choice");
  }
  
  char str2[100];
    scanf("%s",str2);

    int ccount=0;

    for(int i=0;i<data_size;i++){
        if(bit_choice==0){
            if(str2[i]=='0'){
                ccount++;
            }
        }else{
            if(str2[i]=='1'){
                ccount++;
            }
        }
    }
    printf("\n");
    if(ccount%2==0 && strcmp(parity_choice,"even")==0){
        printf("No error");
    }else if(ccount%2!=0 && strcmp(parity_choice,"odd")==0){
        printf("No error");
    }else{
        printf("Error!!!");
    }

}