#include <stdio.h>
#include <math.h>

int find_redundant_positions(int m){
    int r = 0;
    while ((int)pow(2, r) < m + r + 1) {
        r++;
    }
    return r;
}

int is_power_of_two(int x) {
    return (x != 0) && ((x & (x - 1)) == 0);
}

int main(){
    int size;
    scanf("%d", &size);

    int dataword[size];
    for(int i = 0 ; i < size ; i++){
        scanf("%d", &dataword[i]);
    }

    int redundant = find_redundant_positions(size);
    printf("Number of redundant bits: %d\n", redundant);

    int new_size = size + redundant;
    int hamming[new_size];
    int j = 0;

   
    for(int i = 0; i < new_size; i++){
        if(is_power_of_two(i + 1)){
            hamming[i] = 2; 
        } else {
            hamming[i] = dataword[j++];
        }
    }


    for(int i = 0; i < redundant; i++){
        int position = (int)pow(2, i);
        int parity = 0;

        for(int j = 1; j <= new_size; j++){
            if(j & position){
                if(hamming[j - 1] != 2){ 
                    parity ^= hamming[j - 1];
                }
            }
        }
        hamming[position - 1] = parity; 
    }

    printf("Final Hamming code:\n");
    for(int i = new_size - 1; i >= 0; i--){ 
        printf("%d ", hamming[i]);
    }
    printf("\n");

    return 0;
}
