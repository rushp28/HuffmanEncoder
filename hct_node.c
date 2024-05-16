#include "hct_node.h"

HCTNode* createHCTNode(char character, int weight)
{
    HCTNode* pNewHCTNode = (HCTNode*)malloc(sizeof(HCTNode));
    if (pNewHCTNode == NULL)
    {
        fprintf(stderr, "ERROR: Creating of Huffman Coding Tree Node Failed!\nCAUSE: Memory Allocation for HCT Node Failed!\n");
        return NULL;
    }

    pNewHCTNode->character = character;
    pNewHCTNode->weight = weight;
    pNewHCTNode->pLeft = NULL;
    pNewHCTNode->pRight = NULL;

    return pNewHCTNode;
}

void destroyHCTNode(HCTNode* pHCTNode)
{
    if (pHCTNode == NULL)
    {
        fprintf(stderr, "ERROR: Destroying of Huffman Coding Tree Node Failed!\nCAUSE: Pointer to HCT Node is NULL!\n");
        return;
    }

    free(pHCTNode);
}

