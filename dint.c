#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


void swap(int *a, int *b){
    
    int c = *a;
    *a = *b;
    *b = c;
}

/*
    Структура dint содержит 2 поля:
    int size - размер массива
    int *data - указатель типа int
*/
struct dint
{
    int size;
    int *data;
};

/*
    Функция для инициализации динамического массива.
    Принимает два аргумента:
    указатель переменной типа dint,
    размер массива типа int.

*/
void init_dint(struct dint *a, int size){

    a->size = size;

    if(size <= 0){
        a->data = NULL;
    }
    else{
        a->data = calloc((size_t)size, sizeof(int));
        if(a->data == NULL){

        printf("\nНе удалось выделить память!\n");
        exit(1);
        }
    }
}

/*
    Функция Add to end

    Принимает указатель на dint и целочисленное значение нового элемента

    Добавляет новый элемент в конец массива
*/
void ate(struct dint *a, int new_int){ 

    a->data = realloc(a->data, (size_t)(a->size+1) * sizeof(int));

    if(a->data == NULL){

        printf("\nНе удалось выделить память!\n");
        exit(1);
    }

    a->data[a->size] = new_int; 

    a->size++;
}

/*
    Функция insert

    Принимает указатель на dint, индекс, и целочисленное значение нового элемента

    Добавляет новый элемент на место индекса
    
    Если индекс выходит за пределы массива, то автоматически добавляется в начало
*/
void insert(struct dint *a, int index, int value){

    if(index < 0 || index >= a->size)
    {
        index = 0;
    }

    a->data = realloc(a->data, (size_t)(a->size + 1) * sizeof(int));

    if(a->data == NULL){

        printf("\nНе удалось выделить память!\n");
        exit(1);
    }
    
    for(int i = a->size; i > index; i--){

        a->data[i] = a->data[i-1];
    }

    a->data[index] = value;
    
    a->size++;
}

/*
    Функция delete

    Принимает указатель на dint и индекс

    Удаляет элемент по индексу
*/
void del(struct dint *a, int index){

    if(index < 0 || index >= a->size)
    {
        index = 0;
    }

    for(int i=index; i < a->size-1; i++)
        a->data[i] = a->data[i+1];
    
    a->data = realloc(a->data, (size_t)(a->size - 1) * sizeof(int));

    a->size--;
}

/*
    Функция copy_dint

    Принимает указатели dint на источник и назначение

    Перезаписывает массив назначения, копируя в него элементы массива источника
*/
void copy_dint(struct dint *source, struct dint *dest){

    if(source->size != dest->size)
    {   
        free(dest->data);

        dest->data = malloc((size_t)source->size * sizeof(int));
        dest->size = source->size;
    }

    for(int i = 0; i < dest->size; i++)
    {
        dest->data[i] = source->data[i];
    }
    
}

/*
    Функция dint sum

    Принимает указатель типа dint

    Возвращает целочисленное значение суммы всех элементов массива или возвращает INT_MIN если массив пустой
*/
int dsum(struct dint *a){

    if(a->size < 1 || a->data == NULL)
    {   
        printf("\ndint -> data ничего не содержит\n");
        return INT_MIN;
    }
        

    int sum = 0;

    for(int i = 0; i < a->size; i++)
        sum = sum + a->data[i];
    
    return sum;
}

/*
    Функция quicksort

    Принимает указатель типа dint

    Сортирует массив по возрастанию
*/
void quicksort(struct dint *a){

    if(a->size <= 1)
        return;

    int mid = a->size / 2 ;

    struct dint left;
    init_dint(&left, 0);
    struct dint right;
    init_dint(&right, 0);

    for(int i = 0; i < a->size; i++){
        
        if(i == mid)
            continue;
        else{
            if(a->data[i] <= a->data[mid])
                ate(&left, a->data[i]);
            else
                ate(&right, a->data[i]);
        }
    }

    quicksort(&left);
    quicksort(&right);

    mid = a->data[mid];

    for(int i = 0; i<left.size; i++ )
        a->data[i] = left.data[i];

    a->data[left.size] = mid;

    for(int i = 0; i<right.size; i++ )
        a->data[left.size + 1 + i] = right.data[i];

    free(left.data);
    free(right.data);
}

/*
    Функция MaxValue

    Принимает указатель типа dint

    Возвращает самое больше значение среди элементов массива или INT_MAX если массив пустой
*/
int MaxValue(struct dint *a){

    if (a->data == NULL)
    {
        return INT_MAX;
    }
    
    int mv = a->data[0]; //max value

    for(int i=0; i<a->size; i++)
         if(a->data[i] > mv)
            mv = a->data[i];

    return mv;
}

/*
    Функция MinValue

    Принимает указатель типа dint

    Возвращает самое маленькое значение среди элементов массива или INT_MIN если массив пустой
*/
int MinValue(struct dint *a){

    if (a->data == NULL)
    {
        return INT_MIN;
    }
    
    int mv = a->data[0]; //min value

    for(int i=0; i<a->size; i++)
         if(a->data[i] < mv)
            mv = a->data[i];

    return mv;
}

/*
    Функция AverageValue

    Принимает указатель типа dint

    Возвращает среднее значение среди элементов или 0.0 если массив пустой
*/
float AverageValue(struct dint *a){

    if (a->data == NULL || a->size == 0)
    {
        return 0;
    }

    float avrg = 0;

    for(int i=0; i<a->size; i++)    
        avrg += a->data[i];
    
    return avrg / a->size;

}

/*
    Функция median

    Принимает указатель типа dint

    Возвращает медиану среди элементов или 0.0 если массив пустой
*/
float median(struct dint *a){

     if (a->data == NULL || a->size == 0)
    {
        return 0;
    }

    struct dint a_copy;
    init_dint(&a_copy, 0);

    for(int i = 0; i< a->size; i++)
        ate(&a_copy, a->data[i]);
    
    quicksort(&a_copy);

    float median;

    if(a->size % 2 != 0 ){
        median = a_copy.data[a_copy.size/2];
        free(a_copy.data);
        return median;
        
    }
    else{
        median = (float)(a_copy.data[a_copy.size/2] + a_copy.data[a_copy.size/2 - 1] )/ 2;
        free(a_copy.data);
        return  median;
        
    }
}

/*
    Функция reverse

    Принимает указатель типа dint

    Меняет реверсирует массив
*/
void reverse(struct dint *a)
{

    for (int i = 0; i < a->size/2; i++)
    {
        swap(&a->data[i], &a->data[a->size - 1 - i]);
    }
    
}

/*  
    Функция dint free

    Очищает динамический массив и меняет размер на 0
*/
void dfree(struct dint *a)
{
    a->size = 0;
    free(a->data);
}

/*
    Matrix of dynamic int
    Содержит два поля:
    int size - кол-во строк матрицы
    struct dint **data - указатель на массив указателей типа dint
*/
struct mdint
{
    int size;
    struct dint **data;
};

/*
    Функция init_mdint инициализирует матрицу для dint

    Принимает указатель типа *mdint, кол-во строк и столбцов матрицы
*/
void init_mdint(struct mdint *m, int rows, int columns)
{    

    if(rows < 1)
    {
        m->size = 0;
        m->data = NULL;
    }
    else
    {
        m->size = rows;
        m->data = malloc((size_t)rows * sizeof(struct dint*));

        if(m->data == NULL)
        {
        printf("\nНе удалось выделить память!\n");
        exit(1);
        }

        for(int i = 0; i < rows; i++)
        {   
            m->data[i] = malloc(sizeof(struct dint));
            struct dint a;
            init_dint(&a, columns);
            *m->data[i] = a;
        }
    }

}

/*
    Функция mprint

    Принимает указатель типа mdint

    Выводит матрицу
*/
void mprint(struct mdint* m)
{

    if(m->data == NULL)
    {
        printf("\nМатрица пустая\n");
        return;
    }

    for(int i = 0; i < m->size; i++)
    {
        for(int j = 0; j < m->data[i]->size; j++)
            printf("%d ", m->data[i]->data[j]);
        
        printf("\n");
    }
}

/* 
    Функция mfree

    Принимает указатель типа mdint

    Освобождает память для mdint
*/
void mfree(struct mdint *m)
{

    for(int i = 0; i < m->size; i++)
    {   
        free(m->data[i]->data);
        free(m->data[i]);
    }

    free(m->data);
}

/*
    Функция add_row_to_end

    Принимает указатель типа mdint и указатель типа dint

    Добавляет новую строку в конец матрицы
*/
void add_row_to_end(struct mdint *m, struct dint *a)
{

    m->size++;
    m->data = realloc(m->data, (size_t)(m->size) * sizeof(struct dint*));

    if(m->data == NULL)
    {
        printf("\nНеудалось выделить память\n");
        exit(1);
    }
    
    m->data[m->size-1] = a;

}
