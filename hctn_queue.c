#include "hctn_queue.h"

HCTNQueue* createHCTNQueue()
{
    HCTNQueue* pNewHCTNQueue = (HCTNQueue*)calloc(1, sizeof(HCTNQueue));
    if (pNewHCTNQueue == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Create Huffman Coding Tree Node Queue!\nCAUSE: Memory Allocation for HCTN Queue Failed!\n");
        return NULL;
    }

    pNewHCTNQueue->pFront = NULL;
    pNewHCTNQueue->pBack = NULL;

    return pNewHCTNQueue;
}

bool isEmptyHCTNQueue(HCTNQueue* pHCTNQueue)
{
    if (pHCTNQueue == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Check if Huffman Coding Tree Node Queue is Empty!\nCAUSE: Pointer to HCTN Queue is NULL!\n");
        return NULL;
    }

    return pHCTNQueue->pFront == NULL;
}

void enqueueIntoHTCNQueue(HCTNQueue* pHCTNQueue, HCTNode* pHCTNode)
{
    if (pHCTNQueue == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Enqueue into Huffman Coding Tree Node Queue!\nCAUSE: Pointer to HCTN Queue is NULL!\n");
        return;
    }
    if (pHCTNode == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Enqueue into Huffman Coding Tree Node Queue!\nCAUSE: Pointer to HCT Node is NULL!\n");
        return;
    }

    if (isEmptyHCTNQueue(pHCTNQueue) == true)
    {
        pHCTNQueue->pFront = pHCTNode;
        pHCTNQueue->pBack = pHCTNode;
    }
    else if (isEmptyHCTNQueue(pHCTNQueue) == false)
    {
        pHCTNQueue->pBack->pNextNode = pHCTNode;
        pHCTNQueue->pBack = pHCTNode;
    }
}

HCTNode* dequeueFromHTCNQueue(HCTNQueue* pHCTNQueue)
{
    if (pHCTNQueue == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Dequeue from Huffman Coding Tree Node Queue!\nCAUSE: Pointer to HCTN Queue is NULL!\n");
        return NULL;
    }

    if (isEmptyHCTNQueue(pHCTNQueue) == true)
    {
        fprintf(stderr, "ERROR: Failed to Dequeue from Huffman Coding Tree Node Queue!\nCAUSE: HCTN Queue is Empty!\n");
        return NULL;
    }

    HCTNode* pHCTNode = pHCTNQueue->pFront;

    pHCTNQueue->pFront = pHCTNQueue->pFront->pNextNode;

    pHCTNode->pNextNode = NULL;

    if (isEmptyHCTNQueue(pHCTNQueue) == true)
    {
        pHCTNQueue->pBack = NULL;
    }

    return pHCTNode;
}

void fillUpHCTNQueue(HCTNQueue* pHCTNQueue, CharInfoNode* pCharInfoNodeDictionary)
{
    if (pHCTNQueue == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Fill Up Huffman Coding Tree Node Queue!\nCAUSE: Pointer to HCTN Queue is NULL!\n");
        return;
    }
    if (pCharInfoNodeDictionary == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Fill Up Huffman Coding Tree Node Queue!\nCAUSE: Pointer to Character Frequencies Array is NULL!\n");
        return;
    }

    for (int decimalCharIndex = 0; decimalCharIndex < MAX_CHARACTERS; decimalCharIndex++)
    {
        if (pCharInfoNodeDictionary[decimalCharIndex].frequency > 0)
        {
            enqueueIntoHTCNQueue(pHCTNQueue,createHCTNode(pCharInfoNodeDictionary[decimalCharIndex].character, pCharInfoNodeDictionary[decimalCharIndex].frequency));
        }
    }
}


void freeHCTNQueue(HCTNQueue* pHCTNQueue)
{
    if (pHCTNQueue == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Destroy Huffman Coding Tree Node Queue!\nCAUSE: Pointer to HCTN Queue is NULL!\n");
        return;
    }

    while (pHCTNQueue->pFront != NULL)
    {
        HCTNode* pNext = pHCTNQueue->pFront->pNextNode;

        freeHCTNode(pHCTNQueue->pFront);

        pHCTNQueue->pFront = pNext;
    }

    free(pHCTNQueue);
}