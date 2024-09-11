#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct list{
    int* arr;
    int index;
    int size;
} List;

typedef enum ResizeType{
    Expand,
    Collapse
} ResizeType;

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

List newListStack(int size){
    List list;
    list.index = 0;
    if(size != 0){
        list.size = size;
        list.arr = calloc(size, sizeof(int));
    }else{
        list.size = 10;
        list.arr = calloc(10 ,sizeof(int));
    }
    return list;
}

void resizing(List* list, ResizeType resizeType){
    int oldSize = list->size;
    if(resizeType == Expand){
        list->arr = realloc(list->arr, (list->size * 2) * sizeof(int));
        list->size = list->size * 2;
        for (int i = oldSize; i < list->size; ++i) {
            list->arr[i] = 0;
        }
    }
    else{
        list->arr = realloc(list->arr, (list->size / 2) * sizeof(int));
        list->size /= 2;
    }
}

void add(List * list, int value){
    if(list->index == list->size -1){
        resizing(list,Expand);
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
    if(list->index == (list->size / 2) - 1){
        resizing(list,Collapse);
    }
    int temp = list->arr[index];
    for (int i = index; i < list->index; ++i) {
        list->arr[i] = list->arr[i+1];
    }
    list->index--;
    return temp;
}


int removeFirst(List* list){
    if(list->index == 0){
        return -1;
    }
    if(list->index == (list->size / 2) - 1){
        resizing(list,Collapse);
    }
    int temp = list->arr[0];
    for (int i = 0; i < list->index; ++i) {
        list->arr[i] = list->arr[i+1];
    }
    list->index--;
    return temp;
}
int removeLast(List* list){
    if(list->index == 0){
        return -1;
    }
    if(list->index == (list->size / 2) - 1){
        resizing(list,Collapse);
    }
    int temp = list->arr[list->index-1];
    list->index--;
    list->arr[list->index] = 0;
    return temp;
}


void clear(List* list){
    for (int i = 0; i < list->index; ++i) {
        list->arr[i] = 0;
    }
    list->index = 0;
    resizing(list,Collapse);
}

List* toList(List* list){
    List* copyList = malloc(sizeof(List));
    memcpy(copyList, list, sizeof(List));
    copyList->arr = malloc(list->size * sizeof(int));
    memcpy(copyList->arr, list->arr,  sizeof(int) * list->size);
    return copyList;
}
int* toArray(){

}
void toString(){

}


void printList(List* list){
    printf("List:\n");
    //TODO: list->size olan kısımı daha sonra list->index yapıcam
    for (int i = 0; i < list->size; ++i) {
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
    /*List listStack = newListStack(1);
    List* list = &listStack;*/

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

    //clear(list);

    List* newList = toList(list);
    printf("New Array: \n");
    printList(newList);

    printList(list);
    int remove;

    /*printf("Removed Values: \n");
    remove = removeAt(list,1);
    printf("%d\n",remove);
    remove = removeAt(list,3);
    printf("%d\n",remove);
    remove = removeAt(list,4);
    printf("%d\n",remove);
    remove = removeAt(list,5);
    printf("%d\n",remove);
    remove = removeAt(list,5);
    printf("%d\n",remove);*/


    /*printf("Removed Values: \n");
    remove = removeLast(list);
    printf("%d\n",remove);
    remove = removeLast(list);
    printf("%d\n",remove);
    remove = removeLast(list);
    printf("%d\n",remove);*/


    printList(list);


    /*printf("Get list with index: \n");
    int val = get(list,10);
    printf("%d",val);*/

    freeList(list);
    freeList(newList);


    return 0;
}
