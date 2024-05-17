#ifndef M2_HCT_NODE_H
#define M2_HCT_NODE_H

#include <stdio.h>
#include <malloc.h>

typedef struct HCTNode
{
    char character;
    int weight;
    struct HCTNode* pNextNode;
    struct HCTNode* pLeftNode;
    struct HCTNode* pRightNode;
} HCTNode;

HCTNode* createHCTNode(char character, int weight);

void freeHCTNode(HCTNode* pHCTNode);

#endif //M2_HCT_NODE_H
