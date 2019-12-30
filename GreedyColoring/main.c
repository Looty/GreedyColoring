//
//  main.c
//  GreedyColoring
//
//  Created by Erez Mizrahi on 23/04/19.
//  Copyright © 2019 Erez Mizrahi. All rights reserved.
// aa
 
#include <stdio.h>
#include <stdlib.h>
 
typedef struct {
    int begin;
    int end;
    int deg;
    int color;
} Interval;
 
typedef struct {
    Interval* intervals;
    int n;
    int edges;
    int minDeg;
    int maxDeg;
    int chromeNum;
    int compEdges;
    int maxCompDeg;
    int minCompDeg;
} IntArray;
 
void GreedyColoring(void);
int partition(IntArray arr, int low, int high);
void swap(Interval* a, Interval* b);
void quickSort(IntArray arr, int low, int high);
void printIntervalFamily(IntArray);
int getMinColor(int* arr, int n);
void optionalColoring(IntArray);
void InitializeGraph(IntArray*);
 
int main() {
    GreedyColoring();
    system("pause");
    return 0;
}
 
void GreedyColoring(void) {
    int k, b, e;
 
    printf("Please input k\n");
    //scanf_s("%d", &k);
    scanf("%d", &k);
    
    IntArray ints;
    ints.n = k;
    ints.intervals = (Interval*) malloc(ints.n * sizeof(Interval));
    ints.minDeg = ints.maxDeg = ints.edges = ints.compEdges = ints.maxCompDeg = ints.minCompDeg = 0;
    ints.chromeNum = 1;
 
    printf("You will now be asked to insert a family of %d intervals:\n", k);
    for(int i = 0; i < k; i++) {
        printf("%dth Interval: ", i);
 
        scanf("%d", &b); //scanf_s("%d", &b);
        scanf("%d", &e); //scanf_s("%d", &e);
 
        // initialize per interval
        ints.intervals[i].begin = b;
        ints.intervals[i].end = e;
        ints.intervals[i].deg = 0;
        ints.intervals[i].color = -1;
    }
 
    quickSort(ints, 0, ints.n - 1);
    printIntervalFamily(ints);
    InitializeGraph(&ints);
 
    printf("G Edges = %d\n", ints.edges);
    printf("Maximum Degree of G = %d\n", ints.maxDeg);
    printf("Minimum Degree of G = %d\n", ints.minDeg);
    printf("Chromatic Number of G = %d\n", ints.chromeNum);
    printf("G's Complement Edges = %d\n", ints.compEdges);
    printf("Maximum Degree of G's Complmenet = %d\n", ints.maxCompDeg);
    printf("Minimum Degree of G's Complmenet = %d\n", ints.minCompDeg);
    //printf("Optional Coloring: = %d\n", optionalColoring());
}
 
void printIntervalFamily(IntArray a) {
    printf("The Intervals family is:\n");
 
    for(int i = 0; i < a.n; i++) {
        printf("[%d,%d]", a.intervals[i].begin, a.intervals[i].end);
 
        if(i != a.n - 1)
            printf(",");
        else
            printf("\n");
    }
}
 
int partition(IntArray arr, int low, int high) {
    int pivot = arr.intervals[high].begin; // pivot
    int i = (low - 1); // Index of smaller element
 
    for(int j = low; j <= high - 1; j++) {
        if(arr.intervals[j].begin < pivot) {
            i++;
            swap(&arr.intervals[i], &arr.intervals[j]);
        }
    }
    swap(&arr.intervals[i + 1], &arr.intervals[high]);
    return (i + 1);
}
 
void quickSort(IntArray arr, int low, int high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
 
// [0,5],[1,2],[1,3],[3,4],[3,5],[3,9],[3,10],[8,11]
// 0 -> 1
// 1 -> 2
// 3 -> 4
// 8 -> 1
 
void swap(Interval* a, Interval* b) {
    Interval t = *a;
    *a = *b;
    *b = t;
}
 
int getMinColor(int* arr, int n) {
    int min = arr[0];
 
    for(int i = 1; i <= n && !arr[i]; i++) {
        if(arr[i] < min)
            min = arr[i];
    }
 
    return min;
}
 
void InitializeGraph(IntArray* a) {
    int currChrome = 1;
    int minColor = 1;
    int* colorArr = (int*) calloc(a->n, sizeof(int)); // color array of V
 
    for(int i = 0; i < a->n; i++) {
        for(int j = i + 1; j < a->n; j++) {
            if(a->intervals[i].end >= a->intervals[j].begin) {
                a->edges++;
                currChrome++;
 
                if(++a->intervals[i].deg < a->minDeg)
                    a->minDeg = a->intervals[i].deg;
 
                ++a->intervals[j].deg;
 
                if(a->intervals[j].color != -1)
                    colorArr[a->intervals[j].color-1]++;
 
                printf("EDGE: [%d,%d] -> [%d,%d]\n", a->intervals[i].begin, a->intervals[i].end, a->intervals[j].begin, a->intervals[j].end);
            }
        }
 
        a->intervals[i].color = getMinColor(colorArr, a->n)+1;
        for(int i = 0; i < a->n; i++) { colorArr[i] = 0; }
 
        if(currChrome > a->chromeNum)
            a->chromeNum = currChrome;
 
        if(a->maxDeg < a->intervals[i].deg)
            a->maxDeg = a->intervals[i].deg;
 
        currChrome = 0;
    }
 
    a->compEdges = (a->n*(a->n-1)/2) - a->edges;
    a->maxCompDeg = a->n-1 - a->minDeg;
    a->minCompDeg = a->n-1 - a->maxDeg;
 
    free(colorArr);
}
