#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[])
{
    if (argc < 2)
    
    
    return 0;
}












int my_ascending_order(void) {
    int initial_array[] = {1, 5, 2, 3, 4};
    int size = 5;
    
    
    
    for(int i = 0; i < size - 1; i++) {
        int min_index = i;
        
        for(int j = i + 1; j < size; j++) {
            if(initial_array[j] < initial_array[min_index]) {
                min_index = j;
            }
        }
        
        
        if(min_index != i) {
            int temp = initial_array[i];
            initial_array[i] = initial_array[min_index];
            initial_array[min_index] = temp;
        }
    }
    
    for(int i = 0; i < size; i++) {
        printf("%d ", initial_array[i]);
    }
    printf("\n");
    
    return 0;
}


// favours code on ascending order

int favours_ascending(void)
{
    int v[] = {1, 5, 2, 3, 4};
    int p[5], i, k;
    for (i = 0,k = 0; i < 4; i++)
    {
        if (v[i+1]< v[k])
        {
            p[i] = v[i+1];

        }
        else 
        {
            p[i] = v[i];
            k++;
        }
    }
    p[i] = v[k];
    printf ("v is now [");
    for (int i = 0; i < 5; i++)
        printf ("%i, ", p[i]);
    printf("]\n");
    
} 





// reverse

int reverse(void) {
    int list_reverse[] = {1, 2, 3, 4, 5};
    // int size = 5;
    
    for(int i = 5 - 1; i >= 0; i--) {
        printf("%d ", list_reverse[i]);
    }
    printf("\n");
    
    return 0;
}




// get the highest value
int highestValue(void)
{
    int list[] = {3, 7, 1, 9, 5};
    int highestAge = list[0];  

    int length = sizeof(list) / sizeof(list[0]); 

    for(int i = 1; i < length; i++)
    {
        if(list[i] > highestAge)
        {
            highestAge = list[i];
        }
    }

    printf("The highest value is: %d\n", highestAge);

    return 0;
}