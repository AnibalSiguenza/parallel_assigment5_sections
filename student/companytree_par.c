#include "companytree.h"
#include <omp.h>

void parallelTranverse(tree *node, int n){
    if(node != NULL){
        node->work_hours = compute_workHours(node->data);
        top_work_hours[node->id] = node->work_hours;
        #pragma omp sections
        {
            #pragma omp section 
            {
                parallelTranverse(node->right, n-1);
            }
            #pragma omp section
            {
                parallelTranverse(node->left, n-1);
            } 

        }
    }
}

void traverse(tree *node, int numThreads){
    omp_set_nested(1);
    omp_set_max_active_levels(8);
#pragma omp parallel num_threads(numThreads)
    {
#pragma omp single
        parallelTranverse(node,numThreads);
    }
}

