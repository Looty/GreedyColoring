//
//  main.c
//  GreedyColoring
//
//  Created by Erez Mizrahi on 23/04/19.
//  Copyright © 2019 Erez Mizrahi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Intervals {
    int begin;
    int end;
} Interval;

typedef struct IntervalArray {
    Interval* intervals;
    int n;
} IntArray;

void GreedyColoring(void);
int partition(IntArray arr, int low, int high);
void swap(Interval* a, Interval* b);
void quickSort(IntArray arr, int low, int high);
void printInterval(IntArray a, int i);
void printIntervalFamily(IntArray);
int calculateEdges(IntArray a);
int maxDegree(IntArray a);
int maxDegree(IntArray a);

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
    ints.intervals = (Interval*) malloc(ints.n * sizeof(int));
    
    printf("You will now be asked to insert a family of %d intervals:\n", k);
    for(int i = 0; i < k; i++) {
        scanf("%d", &b);
        scanf("%d", &e);
        
        // initialize per interval
        ints.intervals[i].begin = b;
        ints.intervals[i].end = e;
        
        printf("%dth Interval: %d %d\n", i, b, e);
    }
    
    printf("Sorting...\n");
    quickSort(ints, 0, ints.n-1);
    printf("After sort...\n");
    printIntervalFamily(ints);
    
    printf("G Edges = %d\n", calculateEdges(ints));
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

void swap(Interval* a, Interval* b)
{
    Interval t = *a;
    *a = *b;
    *b = t;
}

int calculateEdges(IntArray a) {
    int c = 0;
    
    for(int i = 0; i < a.n; i++) {
        for(int j=i+1; j < a.n; j++) {
            if(a.intervals[i].end >= a.intervals[j].begin) {
                c++;
                //printf("EDGE: [%d,%d] -> [%d,%d]\n", a.intervals[i].begin, a.intervals[i].end, a.intervals[j].begin, a.intervals[j].end);
            }
        }
    }

    return c;
}
