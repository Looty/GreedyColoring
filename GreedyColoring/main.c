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

void GreedyColoring();
void printIntervalFamily(IntArray);
void calculateEdges(Interval);

int main() {
    GreedyColoring();
    return 0;
}

void GreedyColoring() {
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
        
        printf("%dth Interval: %d %d", i, b, e);
    }
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

void calculateEdges(IntArray a) {
    int c = 0;
    
    for(int i = 0; i < a.n; i++) {
        for(int j = 0; j < i; j++) {
            
        }
    }
}
