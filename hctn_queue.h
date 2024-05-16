#ifndef M2_HCTN_QUEUE_H
#define M2_HCTN_QUEUE_H

#include <malloc.h>
#include <stdbool.h>

#include "char_freq.h"
#include "hct_node.h"

typedef struct HCTNQueue
{
    HCTNode* pFront;
    HCTNode* pBack;
} HCTNQueue;

HCTNQueue* createHCTNQueue();

bool isEmptyHCTNQueue(HCTNQueue* pHCTNQueue);

void enqueueIntoHTCNQueue(HCTNQueue* pHCTNQueue, HCTNode* pHCTNode);

HCTNode* dequeueFromHTCNQueue(HCTNQueue* pHCTNQueue);

void fillUpHCTNQueue(HCTNQueue* pHCTNQueue, CharFreq* pCharFreqs);

void destroyHCTNQueue(HCTNQueue* pHCTNQueue);

#endif //M2_HCTN_QUEUE_H
