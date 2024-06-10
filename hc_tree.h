#ifndef M2_HC_TREE_H
#define M2_HC_TREE_H

#include <malloc.h>

#include "hct_node.h"
#include "hctn_queue.h"

typedef struct HCTree
{
    HCTNode* pRoot;
} HCTree;

HCTree* createHCTree();

void generateHCTree(HCTree* pHCTree, HCTNQueue* pCharacterHCTNQueue, HCTNQueue* pInternalHCTNQueue);

void destroyHCTree(HCTree* pHCTree);

void destroyHCTNodesInHCTree(HCTNode* pHCTNode);

#endif //M2_HC_TREE_H