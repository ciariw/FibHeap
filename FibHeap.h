//
// Created by Emeka on 8/26/22.
//
#include <iostream>
#include <vector>
using namespace std;

#ifndef FIBHEAP_FIBHEAP_H
#define FIBHEAP_FIBHEAP_H

class FibHeap{
    public:
        FibHeap(vector<int>::iterator begin,vector<int>::iterator end,bool max = 0);
        typedef struct Node{
            int val;
            int degree;
            bool isMarked;
            Node* parent ;
            vector<Node*> children;
            Node(int x, int y, bool z): val{x},degree{y},isMarked{z},parent{NULL}{

            }
        }Node ;
        Node* top;
        void merge(Node* A, Node* B);
        Node* generateNode(int value);
        Node* compareNodes(Node* first, Node* second) const;
        bool Max;
        void addNode(int nodeVal);
        Node peak();
        Node* delMax();
        void updateNode(Node& A,int updatedVal);
        void deleteNode(unsigned long position);
        void cleanup();


    private:
        void cleave(Node* victim);
        void recurTrap(Node* N);
        void addChild(Node* parent, Node* child){
            parent->children.push_back(child);
            parent->degree ++;
        }
        unsigned long maxDegree = 0;

        long int nodeCount = 0;
        vector<Node*> root;
};

#endif //FIBHEAP_FIBHEAP_H
