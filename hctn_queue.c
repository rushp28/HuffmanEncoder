#include "hctn_queue.h"

HCTNQueue* createHCTNQueue()
{
    HCTNQueue* pNewHCTNQueue = (HCTNQueue*)calloc(1, sizeof(HCTNQueue));
    if (pNewHCTNQueue == NULL)
    {
        fprintf(stderr, "ERROR: Creating of Huffman Coding Tree Node Queue Failed!\nCAUSE: Memory Allocation for HCTN Queue Failed!\n");
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
        fprintf(stderr, "ERROR: Checking if Huffman Coding Tree Node Queue is Empty Failed!\nCAUSE: Pointer to HCTN Queue is NULL!\n");
        return NULL;
    }

    return pHCTNQueue->pFront == NULL;
}

void enqueueIntoHTCNQueue(HCTNQueue* pHCTNQueue, HCTNode* pHCTNode)
{
    if (pHCTNQueue == NULL)
    {
        fprintf(stderr, "ERROR: Enqueuing into Huffman Coding Tree Node Queue Failed!\nCAUSE: Pointer to HCTN Queue is NULL!\n");
        return;
    }
    if (pHCTNode == NULL)
    {
        fprintf(stderr, "ERROR: Enqueuing into Huffman Coding Tree Node Queue Failed!\nCAUSE: Pointer to HCT Node is NULL!\n");
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
        fprintf(stderr, "ERROR: Dequeuing from Huffman Coding Tree Node Queue Failed!\nCAUSE: Pointer to HCTN Queue is NULL!\n");
        return NULL;
    }

    if (isEmptyHCTNQueue(pHCTNQueue) == true)
    {
        fprintf(stderr, "ERROR: Dequeuing from Huffman Coding Tree Node Queue Failed!\nCAUSE: HCTN Queue is Empty!\n");
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

void fillUpHCTNQueue(HCTNQueue* pHCTNQueue, CharFreq* pCharFreqs)
{
    if (pHCTNQueue == NULL)
    {
        fprintf(stderr, "ERROR: Filling up of Huffman Coding Tree Node Queue Failed!\nCAUSE: Pointer to HCTN Queue is NULL!\n");
        return;
    }
    if (pCharFreqs == NULL)
    {
        fprintf(stderr, "ERROR: Filling up of Huffman Coding Tree Node Queue Failed!\nCAUSE: Pointer to Character Frequencies Array is NULL!\n");
        return;
    }

    for (int charFreqIndex = 0; charFreqIndex < MAX_CHARACTERS; charFreqIndex++)
    {
        if (pCharFreqs[charFreqIndex].frequency > 0)
        {
            enqueueIntoHTCNQueue(pHCTNQueue,createHCTNode(pCharFreqs[charFreqIndex].character, pCharFreqs[charFreqIndex].frequency));
        }
    }
}


void destroyHCTNQueue(HCTNQueue* pHCTNQueue)
{
    if (pHCTNQueue == NULL)
    {
        fprintf(stderr, "ERROR: Destroying of Huffman Coding Tree Node Queue Failed!\nCAUSE: Pointer to HCTN Queue is NULL!\n");
        return;
    }

    while (pHCTNQueue->pFront != NULL)
    {
        HCTNode* pNext = pHCTNQueue->pFront->pNextNode;

        destroyHCTNode(pHCTNQueue->pFront);

        pHCTNQueue->pFront = pNext;
    }

    free(pHCTNQueue);
}