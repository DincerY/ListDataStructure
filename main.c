#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct list{
    int* arr;
    int index;
    int size;
} List;

List* newList(int size){
    List* list = malloc(sizeof(List));
    list->index = 0;
    if(size != 0){
        list->size = size;
        list->arr = calloc(size, sizeof(int));
    }else{
        list->size = 10;
        list->arr = calloc(10 ,sizeof(int));
    }

    return list;
}
void resizing(List* list){
    int oldSize = list->size;
    list->arr = realloc(list->arr, (list->size * 2) * sizeof(int));
    list->size = list->size * 2;
    for (int i = oldSize; i < list->size; ++i) {
        list->arr[i] = 0;
    }
}

void add(List * list, int value){
    if(list->index == list->size -1){
        resizing(list);
    }

    list->arr[list->index] = value;

    list->index++;
}

int get(List * list,int index){
    if(index >= list->index){
        return -1;
    }else{
        return list->arr[index];
    }
}

int removeAt(List* list, int index){
    if(index >= list->index){
        return -1;
    }
    int temp = list->arr[index];
    for (int i = index; i < list->size; ++i) {
        list->arr[i] = list->arr[i+1];
        list->index--;
    }
    return temp;
}

void printList(List* list){
    printf("List:\n");
    for (int i = 0; i < list->index; ++i) {
        printf("%d", list->arr[i]);
        printf("\n");
    }
}

void freeList(List * list){
    free(list->arr);
    free(list);
}

int main() {
    List* list = newList(1);
    add(list,10);
    add(list,20);
    add(list,30);
    add(list,40);
    add(list,50);
    add(list,60);
    add(list,70);
    add(list,80);
    add(list,90);
    add(list,100);
    add(list,110);

    printList(list);
    int remove = 0;

    printf("Removed Values: \n");
    remove = removeAt(list,2);
    printf("%d\n",remove);
    remove = removeAt(list,3);
    printf("%d\n",remove);
    remove = removeAt(list,4);
    printf("%d\n",remove);

    printList(list);

    /*printf("Get list with index: \n");
    int val = get(list,10);
    printf("%d",val);*/

    freeList(list);

    return 0;
}
