#ifndef M2_HCTN_QUEUE_H
#define M2_HCTN_QUEUE_H

#include <malloc.h>
#include <stdbool.h>

#include "char_info_node.h"
#include "hct_node.h"

#define MAX_CHARACTERS 128

typedef struct HCTNQueue
{
    HCTNode* pFront;
    HCTNode* pBack;
} HCTNQueue;

HCTNQueue* createHCTNQueue();

bool isEmptyHCTNQueue(HCTNQueue* pHCTNQueue);

void enqueueIntoHTCNQueue(HCTNQueue* pHCTNQueue, HCTNode* pHCTNode);

HCTNode* dequeueFromHTCNQueue(HCTNQueue* pHCTNQueue);

void fillUpHCTNQueue(HCTNQueue* pHCTNQueue, CharInfoNode* pCharInfoNodeDictionary);

void destroyHCTNQueue(HCTNQueue* pHCTNQueue);

#endif //M2_HCTN_QUEUE_H
