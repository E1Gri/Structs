#include <stdlib.h>
#include <stdio.h>

/*
    Вспомогательная структкра node
    Хранит в себе значение типа int и указатель на следующий node
*/
struct node{
    int value;
    struct node* next;
};

/*
    Структура list хранит в себе указатель на главный узел списка
*/
struct list{
    struct node* head;
};

/* 
    Функция для инициализации 
    Принимает указатель на list и значение первого элемента типа int 
*/
void listinit(struct list* List, int FirstValue){
    List->head = (struct node*)malloc(sizeof(struct node));
    List->head->next = NULL;
    List->head->value = FirstValue;
}

/* 
    Функция для добавления нового элемента 
    Принимает указатель на list и значение нового элемента типа int 
    Новый элемент всегда добавляется сразу после основного
*/
void NewElementinList(struct list *List, int value){
    if(List->head->next == NULL){
        struct node* new = (struct node*)malloc(sizeof(struct node));
        new->value = value;
        List->head->next = new;
    }
    else{
        struct node *new = (struct node*)malloc(sizeof(struct node*));
        new->next = List->head->next;
        List->head->next = new;
        new->value = value;
    }
}

/* 
    Функция для получения элемента по индексу 
    Принимает указатель на list и индекс типа int 
*/
int GetElementbyIndex(struct list* List, int index){
    struct node* ptr = List->head;
    int i = 0;
    while (i != index)
    {
        if( (i+1 != index && ptr->next->next == NULL) || index < 0){
            printf("\nИндекс выходит за границы списка\n");
            return 0;
        }
        i++;
        ptr = ptr->next;
    }
    return ptr->value;
}

/* 
    Функция для получения индекса последнего элемента
    Принимает указатель на list 
    Возвращает индекс последнего элемента типа int 
*/
int LastElementIndex(struct list* List){
    struct node* ptr = List->head;
    int i = 0;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
        i++;
    }
    return i;
}

/* 
    Функция для поиска максимального значения среди элементов
    Принимает указатель на list
    Возвращает наибольшее значение типа int
*/
int ListMaxValue(struct list* List){
    struct node* ptr = List->head;
    int max = ptr->value;
    while (1){
        if(ptr->value > max)
            max = ptr->value;
        if(ptr->next == NULL)
            break;
        ptr = ptr->next;
    }
    return max;
}

/* 
    Функция для поиска минимального значения среди элементов
    Принимает указатель на list
    Возвращает наименьшее значение типа int
*/
int ListMinValue(struct list* List){
    struct node* ptr = List->head;
    int min = ptr->value;
    while (1){
        if(ptr->value < min)
            min = ptr->value;
        if(ptr->next == NULL)
            break;
        ptr = ptr->next;
    }
    return min;
}

/* 
    Функция для освобождения памяти
*/
void ListFree(struct list* List){
    if(List->head == NULL)
        return;    
    while (List->head != NULL)
    {   
        struct node* ptr = List->head->next;
        free( List->head);
        List->head = ptr;
    }
    
}
/*
    Структура stack хранит в себе указатель на последний добавленный узел
*/
struct stack
{   
    struct node* top;
};

/*
    Функция инициализации stack и добавления первого значения типа int
*/
void stackinit(struct stack* Stack, int FirstValue){
    Stack->top = (struct node*)malloc(sizeof(struct node));
    Stack->top->next = NULL;
    Stack->top->value = FirstValue;
}

/*
    Добавление нового элемента
    Принимает указатель на stack и значение типа int
    Последний добавленный элемент всегда будет первым 
*/
void StackAdd(struct stack* Stack, int NewValue){
    struct node* new = (struct node*)malloc(sizeof(struct node));

    new->value = NewValue;
    new->next = Stack->top;
    Stack->top = new;
}

/*
    Получение первого значения 
    Принимает указатель на stack
    Возвращает значение типа int
    Удаляет первый элемент
*/
int StackPop(struct stack* Stack){
    if (Stack->top == NULL) {
        printf("\nСтэк пуст!\n");
        return 0;
    }
    int value = Stack->top->value;
    struct node* ptr = Stack->top->next;
    free(Stack->top);
    Stack->top = ptr;
    return value;
}

/*
    Функция для освобождения памяти
*/
void StackFree(struct stack* Stack){
    if (Stack->top == NULL) {
        return;
    }
    while(Stack->top != NULL){
        struct node* ptr = Stack->top->next;
        free(Stack->top);
        Stack->top = ptr;
    }
}
