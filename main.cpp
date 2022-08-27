#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include "FibHeap.h"
#include <assert.h>



FibHeap::FibHeap(std::vector<int>::iterator begin, std::vector<int>::iterator end, bool max) {
    std::vector<FibHeap::Node*> tempRoot;
    if(max){
        // Sets the order of the heap. Max will push maximums to the top
        this->Max = true;
    }else{
        this->Max = false;
    }
    for(auto nodeElement = begin; nodeElement != end; nodeElement++){
        this->root.push_back(this->generateNode(*nodeElement));
    }
    this->top = *(this->root.begin());
    bool hadFoundFirst = false;

    for(auto x = this->root.begin(); x != this->root.end(); x++){
        if(!hadFoundFirst){
            if (*x != NULL){
                hadFoundFirst = true;
                this->top = *x;
            }
        }else{
            FibHeap::Node* comp = this->compareNodes(this->top,*x);
            if (this->top != comp){
                this->top = comp;
            }
        }
    }
    this->cleanup();

}


FibHeap::Node FibHeap::peak(){
    if (this->top != NULL){
        return *(this->top);
    }
}


FibHeap::Node* FibHeap::generateNode(int value){
    FibHeap::Node* n = new FibHeap::Node{value,0};
    this->nodeCount++;
    this->maxDegree = log2(nodeCount);
    return n;
}

void FibHeap::addNode(int nodeVal) {
    FibHeap::Node* newNode = this->generateNode(nodeVal);
    // Create new node reference
    this->root.push_back(newNode);
    // Add node to the root.
    // Add to the root
    this->top = this->compareNodes(this->top,newNode);
    // Compare the new one to the top node, set the top node to the new node
}

FibHeap::Node* FibHeap::delMax() {

    for(FibHeap::Node* child:this->top->children){
        this->root.push_back(child);
    }
    FibHeap::Node* tmpPtr = (this->top);
    this->top = NULL;
    bool hadFoundFirst = false;

    for(auto x = this->root.begin(); x != this->root.end(); x++){
        if(!hadFoundFirst){
            if (*x != NULL){
                hadFoundFirst = true;
                this->top = *x;
            }
        }else{
            FibHeap::Node* comp = this->compareNodes(this->top,*x);
            if (this->top != comp){
                this->top = comp;
            }
        }
    }
    return tmpPtr;


}

void FibHeap::cleanup() {
    // Only called on delete top and on init
    std::cout << (this->maxDegree)+1 << std::endl;
    FibHeap::Node* field [(this->maxDegree)+1];
    for(unsigned long int x = 0; x < (this->maxDegree)+1; x++){
        field[x] = NULL;
    }
    // Pull from this->root, get the degree
    for(FibHeap::Node* node:this->root){
        // While loop
        // Take this node, check if Null if null pass
        // if not null, combine, set node to new parent node
        bool ready = true;
        long unsigned int offset = 0;
        while(ready)
        {
            if (field[node->degree] == NULL) {
                field[node->degree] = node;
                ready = false;

            } else {
                // Change to while the node is not empty
                FibHeap::Node *tNode = this->compareNodes(field[node->degree], node);

                if (tNode == field[node->degree]) {
                    tNode->children.push_back(node);
                } else {
                    node->children.push_back(field[node->degree]);
                }

                field[node->degree] = NULL;

                tNode->degree++;
                node = tNode;
                std::cout << tNode->degree << std::endl;
            }

        }
        ready = true;
    }

    for(auto x:field){
        if (x != NULL){
            std::cout << x->degree << std::endl;
        }

    }




}

FibHeap::Node* FibHeap::compareNodes(FibHeap::Node *first, FibHeap::Node *second) const {
    // Function for comparing nodes
    // Dont change if equal. the second has to be explicitly greater than or less than the first
    if (this->Max){
        if(first->val < second->val){
            // If the first node is smaller  than the current max, return the second node ref
            return second;
        }else {
            return first;
        }
    }else{
        if(second->val < first->val){
            // If the second node is smaller than the current min, return the second node.
            // If it is equal or greater, return the first
            return second;
        }else{
            return first;
        }
    }
    return NULL;
}

int main(){
    // By using vectors i can just fill in the empty spots with NULL, preserving the
    std::vector<int> n{2,3,56,2,1,0,6,4,1,8,-59,2,2,3,4,3,3,3,-100};
    FibHeap h(n.begin(),n.end(),0);

    return 1;
}
