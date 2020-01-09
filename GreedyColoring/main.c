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
void optionalColoring(IntArray*);
void printColors(IntArray*);
void InitializeGraph(IntArray*);
 
int main() {
    GreedyColoring();
    //system("pause");
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
    ints.maxDeg = ints.edges = ints.compEdges = ints.maxCompDeg = ints.minCompDeg = ints.chromeNum = 0;
    ints.minDeg = -1;
 
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

    printIntervalFamily(ints);
    quickSort(ints, 0, ints.n - 1);
    InitializeGraph(&ints);
    optionalColoring(&ints);
    
    printf("G Edges = %d\n", ints.edges);
    printf("Maximum Degree of G = %d\n", ints.maxDeg);
    printf("Minimum Degree of G = %d\n", ints.minDeg);
    printf("Chromatic Number of G = %d\n", ints.chromeNum);
    printf("G's Complement Edges = %d\n", ints.compEdges);
    printf("Maximum Degree of G's Complmenet = %d\n", ints.maxCompDeg);
    printf("Minimum Degree of G's Complmenet = %d\n", ints.minCompDeg);
    printColors(&ints);
    
    free(ints.intervals);
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
    int pivot = arr.intervals[high].begin;
    int i = (low - 1);
 
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

void swap(Interval* a, Interval* b) {
    Interval t = *a;
    *a = *b;
    *b = t;
}

void InitializeGraph(IntArray* a) {
    for(int i = 0; i < a->n; i++) {
        for(int j = i + 1; j < a->n; j++) {
            if(a->intervals[i].end >= a->intervals[j].begin) {
                a->edges++;
                
                if(a->minDeg == -1)
                    a->minDeg = ++a->intervals[i].deg;

                if(a->intervals[i].deg < a->minDeg)
                    a->minDeg = a->intervals[i].deg;

                ++a->intervals[j].deg;
            }
        }
    }
 
    a->compEdges = (a->n*(a->n-1)/2) - a->edges;
    a->maxCompDeg = a->n-1 - a->minDeg;
    a->minCompDeg = a->n-1 - a->maxDeg;
}

void optionalColoring(IntArray* a) {
      a->intervals[0].color = 0;

      int ready[a->n];
      int maxConnections = 0;
      for (int cr = 0; cr < a->n; cr++)
          ready[cr] = 0;

      for (int u = 1; u < a->n; u++)
      {
          for (int i = 0; i < a->n; i++) {
            if(a->intervals[u].end >= a->intervals[i].begin && a->intervals[i].end >= a->intervals[u].begin) {
              if (a->intervals[i].color != -1)
                  ready[a->intervals[i].color] = 1;
                  
              if(a->intervals[u].begin != a->intervals[i].begin && a->intervals[u].end != a->intervals[i].end)
                maxConnections++;

              if(a->maxDeg < maxConnections)
                  a->maxDeg = maxConnections;
            }
          }

          maxConnections = 0;
          
          int cr;
          for (cr = 0; cr < a->n; cr++)
              if (!ready[cr])
                  break;
    
          a->intervals[u].color = cr;
          
          if(cr > a->chromeNum)
            a->chromeNum = cr;

          for (int i = 0; i < a->n; i++)
            if(a->intervals[u].end >= a->intervals[i].begin)
                if (a->intervals[i].color != -1)
                    ready[a->intervals[i].color] = 0;
      }

      if(a->chromeNum != 0)
        a->chromeNum++;
      else
        a->chromeNum = 1;
        
      if(a->minDeg == -1) a->minDeg = 0;
}

void printColors(IntArray* a) {
    printf("Optional Coloring: ");
    
    if(a->chromeNum > 0) {
        int colorArr[a->chromeNum];
        int currSize = 0;

        for(int i = 0; i < a->chromeNum; i++)
            colorArr[i] = 0;

        for(int i = 0; i < a->n; i++)
            colorArr[a->intervals[i].color]++;

        for(int i = 0; i < a->chromeNum; i++) {
            printf("{");
            
            for(int j = 0; j < a->n; j++) {
                if(a->intervals[j].color == i) {
                    currSize++;
                    printf("[%d, %d]", a->intervals[j].begin, a->intervals[j].end);
                    if(currSize < colorArr[i]) printf(",");
                }
            }

            currSize = 0;
            printf("} = %d", i+1);
            if(i+1 < a->chromeNum) printf(", ");
        }
    }
    else {
        printf("{");
        
        for(int j = 0; j < a->n; j++) {
            printf("[%d, %d]", a->intervals[j].begin, a->intervals[j].end);
            if(j+1 < a->n) printf(",");
        }

        printf("} = 0");
    }
    
    printf("\n");
}
