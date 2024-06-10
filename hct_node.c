#include "hct_node.h"

HCTNode* createHCTNode(char character, int weight)
{
    HCTNode* pNewHCTNode = (HCTNode*)calloc(1, sizeof(HCTNode));
    if (pNewHCTNode == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Create Huffman Coding Tree Node!\nCAUSE: Memory Allocation for HCT Node Failed!\n");
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
        fprintf(stderr, "ERROR: Failed to Destroy to Huffman Coding Tree Node!\nCAUSE: Pointer to HCT Node in the HCTN Queue is NULL!\n");
        return;
    }

    free(pHCTNode);
}

