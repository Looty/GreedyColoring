//
//  main.c
//  GreedyColoring
//
//  Created by Erez Mizrahi on 23/04/19.
//  Copyright © 2019 Erez Mizrahi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define NIL    -1
#define ZERO    0

typedef struct {
    int begin;
    int end;
    int deg; //NIL
    int color;
    struct Interval* next;
} Interval;

typedef struct {
    Interval* intervals;
    int n;
    int edges; // ZERO
    int minDeg; // ZERO
    int maxDeg; // ZERO
    int chromeNum; // ZERO
} IntArray;

void GreedyColoring(void);
int partition(IntArray arr, int low, int high);
void swap(Interval* a, Interval* b);
void quickSort(IntArray arr, int low, int high);
void printInterval(IntArray a, int i);
void printIntervalFamily(IntArray);
void InitializeGraph(IntArray);
int calculateEdges(IntArray a);

int main() {
    GreedyColoring();
    return 0;
}

void GreedyColoring(void) {
    int k, b, e;
    
    printf("Please input k\n");
    scanf("%d", &k);
    
    // initialize
    IntArray ints;
    ints.n = k;
    ints.intervals = (Interval*) malloc(ints.n * sizeof(Interval));
    ints.minDeg = ints.maxDeg = ints.edges = ints.chromeNum = ZERO;
    
    printf("You will now be asked to insert a family of %d intervals:\n", k);
    for(int i = 0; i < k; i++) {
        scanf("%d", &b);
        scanf("%d", &e);
        
        // initialize per interval
        ints.intervals[i].begin = b;
        ints.intervals[i].end = e;
        ints.intervals[i].deg = ZERO;
        ints.intervals[i].next = (struct Interval*) malloc(sizeof(Interval));
        ints.intervals[i].color = ZERO;
        
        printf("%dth Interval: %d %d\n", i, b, e);
    }

    quickSort(ints, 0, ints.n-1);
    printIntervalFamily(ints);
    
    //printf("G Edges = %d\n", calculateEdges(ints));
}

void printIntervalFamily(IntArray a) {
    printf("The Intervals family is:\n");
    
    for(int i = 0; i < a.n; i++) {
        printf("[%d,%d]", a.intervals[i].begin, a.intervals[i].end);
        
        if(i != a.n-1)
            printf(",");
        else
            printf("\n");
    }
}

int partition(IntArray arr, int low, int high) {
    int pivot = arr.intervals[high].begin; // pivot
    int i = (low - 1); // Index of smaller element
    
    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr.intervals[j].begin < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr.intervals[i], &arr.intervals[j]);
        }
    }
    swap(&arr.intervals[i + 1], &arr.intervals[high]);
    return (i + 1);
}

void quickSort(IntArray arr, int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);
  
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// [0,5],[1,2],[1,3],[3,4],[3,5],[3,9],[3,10],[8,11]
// 0 -> 1
// 1 -> 2
// 3 -> 4
// 8 -> 1

void swap(Interval* a, Interval* b)
{
    Interval t = *a;
    *a = *b;
    *b = t;
}

void InitializeGraph(IntArray a) {
    for(int i = 0; i < a.n; i++) {
        for(int j=i+1; j < a.n; j++) {
            if(a.intervals[i].end >= a.intervals[j].begin) {
                a.intervals[i].deg++;
                a.intervals[i].color++;
                //a.intervals[i].next = a.intervals[j];
                //printf("EDGE: [%d,%d] -> [%d,%d]\n", a.intervals[i].begin, a.intervals[i].end, a.intervals[j].begin, a.intervals[j].end);
            }
        }
    }
}
/*
 typedef struct {
     int begin;
     int end;
     int deg; //NIL
     int color;
     struct Interval* next;
 } Interval;
 
 typedef struct {
     Interval* intervals;
     int n;
     int edges; // ZERO
     int minDeg; // ZERO
     int maxDeg; // ZERO
     int chromeNum; // ZERO
 } IntArray;
 */
