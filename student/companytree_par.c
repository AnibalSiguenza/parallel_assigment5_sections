#include "companytree.h"
#include <omp.h>
#define T 4

void traverse(tree *node, int numThreads){
    omp_set_nested(1);
    omp_set_max_active_levels(T);
    omp_set_num_threads(numThreads);
    if(node != NULL){
        node->work_hours = compute_workHours(node->data);
        top_work_hours[node->id] = node->work_hours;
        #pragma omp parallel sections
        {
            #pragma omp section 
            {
                traverse(node->right, numThreads);
            }
            #pragma omp section
            {
                traverse(node->left, numThreads);
            } 

        }
    }
}

