#ifndef SHORTPATH_H_
#define SHORTPATH_H_

#include <queue>
//#include <heap.h>
#include "myHeap.full.h"  
#include <math.h>


#define LARGE1 9999999
#define INT_MAX 2147483647

using namespace std;


struct arc{
  struct arc *next;
  int length;
  int end;
  };

typedef struct node{
   struct arc *first; /* first arc in linked list */
   int id;  // The number of the vertex in this node 
   int key;  /* Distance estimate, named key to reuse heap code*/
   int P;  /* Predecessor node in shortest path */
   int position;  /* Position of node in heap, from 0 to Nm, where 0 is best */
   } nodeitem;

void BellmanFord(nodeitem N[], int Or, int Nm)
{
   // You program this, a  Bellman Ford algorithm that uses a work queue.
    bool inQueue[Nm + 1] = { false };
    struct arc *edge;

    N[Or].key = 0;
  
    queue<int> q;
    q.push(Or);
    inQueue[Or] = true;

    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        inQueue[u] = false;    
        edge = N[u].first; 

        while(edge!=NULL) {
            int v =   edge->end;
            int dv = N[u].key + edge->length;
            //cout << "dv success" << endl;
            if (N[v].key > dv) {
                N[v].key = dv;
                N[v].P = u;
                if (!inQueue[v]) {
                    q.push(v);
                    inQueue[v] = true;
                }
            }
            edge = edge->next;
        }
    }


}/* end Bellman-Ford */
/* ---------------*/


void Dijkstra(nodeitem N[], int Or, int Nm)
{
    int Mark[Nm+1];
    struct arc *edge;
    int v, dv, min_d, min_v, finished;
    for (int i=1; i<=Nm; i++){
        Mark[i]=-1;
    }
    N[Or].key = 0;
    Mark[Or] = 1;
    finished = 1;
    min_v = Or;
    min_d = 0;
    while (finished < Nm){
        edge = N[min_v].first;  //update distances
        while (edge != NULL){ // explore the outgoing arcs of u 
            v = edge->end;
            dv = min_d + edge->length;
            if (N[v].key > dv){
                N[v].key = dv;
                N[v].P = min_v;
            }//if D > dv 
            edge = edge->next;
        }// while edge           
        
        min_d = LARGE1;
        for (int j = 0; j <= Nm; j++){
            if (Mark[j] < 1){
                if (N[j].key < min_d){
                    min_d = N[j].key;
                    min_v = j;
                }
            }
        } 
        Mark[min_v]=1;
        finished++;
    } 
} /* end Dijkstra */


void DijkstraHeap(nodeitem N[], int Or, int Nm)
{
    Heap<nodeitem> *thisHeap;
    struct arc *edge;
    nodeitem *node;
    nodeitem *temp;
    int v, dv, min_d, min_v, finished;

    thisHeap = new Heap<nodeitem>;

    N[Or].key = 0;

    for (int i = 1; i <= Nm; i++)
    {
        thisHeap->insert(&N[i]);
    }

    while(thisHeap->size() != 0)
    {
        node = thisHeap->remove_min();
        min_v = node->position;
        min_d = node->key;
        edge = node->first;
        while (edge != NULL)
        { // explore the outgoing arcs of u 
            v = edge->end;
            dv = node->key + edge->length;
            if (N[v].key > dv)
            {
                N[v].key = dv;
                N[v].P = node->id;
                thisHeap->decreaseKey(N[v].position,N[v].key);
            }
            edge = edge -> next;
        }

    }
    
} /* end DijkstraHeap */ 

#endif
