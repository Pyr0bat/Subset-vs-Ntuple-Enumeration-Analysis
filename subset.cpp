#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
typedef struct {
    int type;
    int value;
    int weight;
} item;

int *knapsack (item *items, const int numitems, int bagsize) {
    //initialize arrays
    int* array = new int[(numitems + 1) * (bagsize + 1)];
    int** arrays = new int*[numitems+1];
    for(int index = 0; index < numitems+1; index++){
        arrays[index] = new int[numitems+1];
    }
    //find optimal bag
    arrays[0] = array;
    for (int index = 1; index <= numitems; index++) {
        arrays[index] = &array[index * (bagsize + 1)];
        for (int inner = 0; inner <= bagsize; inner++) {
            if (items[index - 1].weight > inner) {
                arrays[index][inner] = arrays[index - 1][inner];
            } else {
                int temp1 = arrays[index - 1][inner];
                int temp2 = arrays[index - 1][inner - items[index - 1].weight] + items[index - 1].value;
                arrays[index][inner] = temp1 > temp2 ? temp1 : temp2;
            }
        }
    }
    //store optimal bag in result to return
    int *result = new int[numitems];
    int inner = bagsize;
    for (int index = numitems; index > 0; index--) {
        if (arrays[index][inner] > arrays[index - 1][inner]) {
            result[index - 1] = 1;
            inner -= items[index - 1].weight;
        }
    }
    return result;
}
 
int main(){
    int *result;
    FILE * filefd;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    filefd = fopen("tester.txt", "r");
    if (filefd == NULL)
        exit(EXIT_FAILURE);
    getline(&line, &len, filefd);
    int numitems = atoi(line);
    item items[numitems];
    getline(&line, &len, filefd);
    int totalweight = atoi(line);
    int count = 0;
    int counter = 0;
    while ((read = getline(&line, &len, filefd)) != -1) {
        char *val = strtok(line, ",");
        int copies = atoi(val);
        int value = atoi(strtok(NULL, ","));
        int weight = atoi(strtok(NULL, ","));
        for(int index = 0; index < copies;index++){
            items[counter].type = count;
            items[counter].weight = weight;
            items[counter++].value = value;
        }
        count++;
    }
    fclose(filefd);
    result = knapsack(items, sizeof (items) / sizeof (item), totalweight);
    int totalvalue = 0;
    int totalw = 0;
    
    for(int index = 0; index < sizeof (items) / sizeof (item); index++){
        if(result[index]){
            if(totalweight < items[index].weight){
                continue;
            }
            printf("%d,%d,%d\n", items[index].type, items[index].value, items[index].weight);
            totalw += items[index].weight;
            totalvalue += items[index].value;
        }
    }
    printf("%d,%d", totalvalue, totalw);
    return 0;
}