#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pq;
  for (size_t i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      pq.push(new Node(i, counts[i]));
    }
  }
  while (pq.size() > 1) {
    Node * n1 = pq.top();
    pq.pop();
    Node * n2 = pq.top();
    pq.pop();
    pq.push(new Node(n1, n2));
  }
  return pq.top();
}
