#include "hct_node.h"

HCTNode* createHCTNode(char character, int weight)
{
    HCTNode* pNewHCTNode = (HCTNode*)calloc(1, sizeof(HCTNode));
    if (pNewHCTNode == NULL)
    {
        fprintf(stderr, "ERROR: Creating of Huffman Coding Tree Node Failed!\nCAUSE: Memory Allocation for HCT Node Failed!\n");
        return NULL;
    }

    pNewHCTNode->character = character;
    pNewHCTNode->weight = weight;
    pNewHCTNode->pNextNode = NULL;
    pNewHCTNode->pLeftNode = NULL;
    pNewHCTNode->pRightNode = NULL;

    return pNewHCTNode;
}

void destroyHCTNode(HCTNode* pHCTNode)
{
    if (pHCTNode == NULL)
    {
        fprintf(stderr, "ERROR: Destroying of Huffman Coding Tree Node Failed!\nCAUSE: Pointer to HCT Node in the HCTN Queue is NULL!\n");
        return;
    }

    free(pHCTNode);
}

void destroyHCTNodesInHCTree(HCTNode* pHCTNode)
{
    if (pHCTNode == NULL)
    {
        return;
    }

    destroyHCTNodesInHCTree(pHCTNode->pLeftNode);
    destroyHCTNodesInHCTree(pHCTNode->pRightNode);

    free(pHCTNode);
}

