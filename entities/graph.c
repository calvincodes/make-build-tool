//
// Created by Arpit Jain on 11/1/18.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "graph.h"

graph_node* createGraphNode(char *element, linked_list_node* dependencies, linked_list_node* commands) {

    graph_node* graphNode = (graph_node *) malloc(sizeof(graph_node));

    if(!graphNode){
        fprintf(stderr, "Could not allocate memory for LinkedList data");
        exit(1);
    }
    graphNode->element = element;
    graphNode->dependencies = dependencies;
    graphNode->commands = commands;
    graphNode->children = (graph_node**) malloc(MAX_SIZE * sizeof(graphNode));
    return graphNode;
}

graph_node* createConnections(graph_node* graphArray[], unsigned int size){
    graph_node *root = NULL;

    for(int i = 0;i<size;i++){
        graphArray[i]->nodeNo = i;
    }
    for(int i = 0;i<size;i++){
        if(!root){
            root = graphArray[i];
        }
        linked_list_node *llNode = graphArray[i]->dependencies;
        int currChildCount = 0;
        while(llNode){

            for(int j =0;j<size;j++){
                if(strcmp(llNode->element, graphArray[j]->element) == 0){
                    graphArray[i]->children[currChildCount++] = graphArray[j];
                    break;
                }
            }
            llNode = llNode->next;
        }
    }
    return root;
}

int cyclic_util(int nodeNo, int visited[], int stack[], graph_node *graphNodeArray[], graph_node* node ){
    if(!visited[nodeNo]){
        visited[nodeNo] = 1;
        stack[nodeNo] = 1;
    }
    for(int i=0;i<MAX_SIZE && node->children[i] != NULL;i++){
        if (!visited[node->children[i]->nodeNo] && cyclic_util(node->children[i]->nodeNo, visited, stack, graphNodeArray, graphNodeArray[nodeNo]->children[i]))
            return 1;
        else if (stack[node->children[i]->nodeNo])
            return 1;
    }
    stack[node->nodeNo] = 0;
    return 0;
}

int is_cycle_found(unsigned int graphSize, graph_node *graphNodeArray[]){

    int visited[graphSize];
    int stack[graphSize];

    for(int i=0;i<graphSize;i++ ){
        visited[i] = 0;
        stack[i] = 0;
    }

    for(int i=0;i<graphSize;i++){
        if(cyclic_util(graphNodeArray[i]->nodeNo, visited, stack, graphNodeArray, graphNodeArray[i])){
            return 1;
        }
    }
    return 0;
}
