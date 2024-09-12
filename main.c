#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct list{
    int* arr;
    int index;
    int size;
} List;

typedef enum ResizeType{
    Expand,
    Collapse
} ResizeType;

//Fonksiyon işaretcilerimi tanımladım
typedef bool (*Func) (int);
typedef void (*Action)(int);


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

int insert(List* list,int index, int item){
    if(index > list->index){
        return -1;
    }
    if(list->index == list->size -1){
        resizing(list,Expand);
    }
    for (int i = list->index; i > index; i--) {
        list->arr[i] = list->arr[i-1];
    }
    list->arr[index] = item;
    list->index++;
    return item;
}

int get(List * list,int index){
    if(index >= list->index){
        return -1;
    }else{
        return list->arr[index];
    }
}

int contains(List* list ,int item){
    for (int i = 0; i < list->index; ++i) {
        if(list->arr[i] == item){
            return item;
        }
    }
    return -1;
}

int findIndex(List* list, int val){
    for (int i = 0; i < list->index; ++i) {
        if(list->arr[i] == val){
            return i;
        }
    }
    return -1;
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

int removeVal(List* list,int val){
    int index = -1;
    for (int i = 0; i < list->index; ++i) {
        if(list->arr[i] == val){
            index = i;
        }
    }
    if(index != -1){
        return removeAt(list,index);
    }
    return -1;
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

int removeRange(List* list, int startIndex, int length){
    if(startIndex + length - 1 > list->index){
        return -1;
    }

    int i = startIndex;
    for (int j = startIndex + length; j < list->index; ++j) {
        if(j > list->index){
            break;
        }
        list->arr[i] = list->arr[j];
        i++;
    }
    for (i ; i < list->index; ++i) {
        list->arr[i] = 0;
    }
    list->index -= length;
    if(list->index == (list->size / 2) - 1){
        resizing(list,Collapse);
    }
}

void clear(List* list){
    for (int i = 0; i < list->index; ++i) {
        list->arr[i] = 0;
    }
    list->index = 0;
    resizing(list,Collapse);
}

void copyTo(List* list,int* arr){
    memcpy(arr,list->arr,sizeof(int) * list->index);
}

void reverse(List* list){
    int* tempArr = malloc(list->index * sizeof(int));
    memcpy(tempArr,list->arr,sizeof(int) * list->index);
    for (int i = 0; i < list->index; ++i) {
        int j = (list->index - 1) - i;
        list->arr[i] = tempArr[j];
    }
    free(tempArr);
}

List* slice(List* list, int startIndex,int length){
    if(startIndex + length > list->index){
        return NULL;
    }
    List* slicedList = newList(length + 1);

    for (int i = startIndex; i < startIndex+length; ++i) {
        add(slicedList,list->arr[i]);
    }

    return slicedList;
}

List* toList(List* list){
    List* copyList = malloc(sizeof(List));
    memcpy(copyList, list, sizeof(List));
    copyList->arr = malloc(list->size * sizeof(int));
    memcpy(copyList->arr, list->arr,  sizeof(int) * list->size);
    return copyList;
}
int* toArray(List* list){
    int* arr = malloc(sizeof(int) * list->index);
    memcpy(arr,list->arr, sizeof(int) * list->index);
    return arr;
}
//Küçük sayılar için çalışıyor.
//Büyük sayılar ile kullanmak için her bir sayıya birden fazla bayt düşmeli ve bu işlem biraz karmaşık.
char* toString(List* list){
    char* arr = malloc(sizeof(char) * list->index);
    for (int i = 0; i < list->index; ++i) {
        arr[i] = (char)list->arr[i];
    }
    return arr;
}

//Linq fonksiyonunu yazmaya çalıştım. Çok beceremedim gibi :D
//Burada projeksiyon olarak girilen List yapını kullandım.
List* where(List* list, Func func){
    List *whereList = newList(list->size);

    for (int i = 0; i < list->index; ++i) {
        if(func(list->arr[i])){
            add(whereList,list->arr[i]);
        }
    }
    return whereList;
}

void forEach(List* list, Action action){
    for (int i = 0; i < list->index; ++i) {
        action(list->arr[i]);
    }
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

//Where için delege olarak çalıştırılacak fonksiyonlar
bool greaterThanHundred(int val){
    if(val > 100){
        return true;
    }
    return false;
}

bool lessThanHundred(int val){
    if(val < 100){
        return true;
    }
    return false;
}
bool equalHundred(int val){
    if(val == 100){
        return true;
    }
    return false;
}
//forEach için delege olarak çalıştırılacak fonksiyon
void printOneElement(int element){
    printf("Print : %d\n", element);
}

int main() {
    //List* list = newList(1);

    //Stack tarafında kullanmak istememin sebebi bu yapıya çok fazla erişim var.
    List listStack = newListStack(1);
    List* list = &listStack;

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


    removeRange(list,2,3);
    printf("Remove Range Function:\n");
    printList(list);

    //reverse(list);

    //forEach(list,printOneElement);

    /*List* whereList = where(list,equalHundred);
    printf("Where\n");
    printList(whereList);
    freeList(whereList);*/


    /*insert(list,1,300);
    insert(list,1,400);
    insert(list,1,500);
    insert(list,1,600);
    insert(list,1,700);*/

    //clear(list);

    /*int val = contains(list,9);
    printf("Is contains : %d\n",val);*/

    /*List* slicedList = slice(list,2,3);
    printf("Sliced List : \n");
    printList(slicedList);
    freeList(slicedList);*/

    List* newList = toList(list);
    printf("New List: \n");
    printList(newList);


    /*int* copy = malloc(sizeof(int) * list->index);
    copyTo(list,copy);
    printf("Copy Array: \n");
    for (int i = 0; i < list->index; ++i) {
        printf("%d. element is : %d\n",i+1,copy[i]);
    }
    free(copy);*/

    /*int* arr = toArray(list);
    printf("New Array: \n");
    for (int i = 0; i < list->index; ++i) {
        printf("%d. element is : %d\n",i+1,arr[i]);
    }
    free(arr);*/

    /*char* charArr = toString(list);
    printf("New String: \n");
    for (int i = 0; i < list->index; ++i) {
        printf("%d. element is : %d\n",i+1,charArr[i]);
    }
    free(charArr);*/


    printList(list);
    int remove;

    printf("Removed Values: \n");
    remove = removeAt(list,1);
    printf("%d\n",remove);
    remove = removeAt(list,3);
    printf("%d\n",remove);
    remove = removeAt(list,4);
    printf("%d\n",remove);
    remove = removeAt(list,5);
    printf("%d\n",remove);
    remove = removeAt(list,5);
    printf("%d\n",remove);


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



    //Artık yapım stack üzerinde olduğu için serbest bırakma işlemine gerek kalmadı
    //freeList(list);
    freeList(newList);


    return 0;
}
