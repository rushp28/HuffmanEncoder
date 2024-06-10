#include "hc_tree.h"

HCTree* createHCTree()
{
    HCTree* pNewHCTree = (HCTree*)calloc(1, sizeof(HCTree));
    if (pNewHCTree == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Create Huffman Coding Tree!\nCAUSE: Memory Allocation for Huffman Coding Tree Failed!\n");
        return NULL;
    }

    pNewHCTree->pRoot = NULL;

    return pNewHCTree;
}

void generateHCTree(HCTree* pHCTree, HCTNQueue* pCharacterHCTNQueue, HCTNQueue* pInternalHCTNQueue)
{
    if (pHCTree == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Generate Huffman Coding Tree!\nCAUSE: Pointer to Huffman Coding Tree is NULL!\n");
        return;
    }
    if (pCharacterHCTNQueue == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Generate Huffman Coding Tree!\nCAUSE: Pointer to Character Huffman Coding Tree Node Queue is NULL!\n");
        return;
    }
    if (pInternalHCTNQueue == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Generate Huffman Coding Tree!\nCAUSE: Pointer to Internal Huffman Coding Tree Node Queue is NULL!\n");
        return;
    }

    while (pCharacterHCTNQueue->pFront != NULL || !(pCharacterHCTNQueue->pFront == NULL && pInternalHCTNQueue->pFront->pNextNode == NULL))
    {
        HCTNode *pLeftNode = NULL;
        HCTNode *pRightNode = NULL;

        if (pCharacterHCTNQueue->pFront != NULL && (pInternalHCTNQueue->pFront == NULL || pCharacterHCTNQueue->pFront->weight <= pInternalHCTNQueue->pFront->weight))
        {
            pLeftNode = dequeueFromHTCNQueue(pCharacterHCTNQueue);
        }
        else
        {
            pLeftNode = dequeueFromHTCNQueue(pInternalHCTNQueue);
        }

        if (pCharacterHCTNQueue->pFront != NULL && (pInternalHCTNQueue->pFront == NULL || pCharacterHCTNQueue->pFront->weight <= pInternalHCTNQueue->pFront->weight))
        {
            pRightNode = dequeueFromHTCNQueue(pCharacterHCTNQueue);
        }
        else
        {
            pRightNode = dequeueFromHTCNQueue(pInternalHCTNQueue);
        }

        HCTNode *pInternalNode = createHCTNode('$', pLeftNode->weight + pRightNode->weight);
        pInternalNode->pLeftNode = pLeftNode;
        pInternalNode->pRightNode = pRightNode;

        enqueueIntoHTCNQueue(pInternalHCTNQueue, pInternalNode);
    }

    pHCTree->pRoot = dequeueFromHTCNQueue(pInternalHCTNQueue);
}

void destroyHCTree(HCTree* pHCTree)
{
    if (pHCTree == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Destroy Huffman Coding Tree!\nCAUSE: Pointer to Huffman Coding Tree is NULL!\n");
        return;
    }

    destroyHCTNodesInHCTree(pHCTree->pRoot);

    free(pHCTree);
}

void destroyHCTNodesInHCTree(HCTNode* pHCTNode)
{
    if (pHCTNode == NULL) return;

    destroyHCTNodesInHCTree(pHCTNode->pLeftNode);
    destroyHCTNodesInHCTree(pHCTNode->pRightNode);

    free(pHCTNode);
}