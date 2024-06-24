#ifndef M2_CHAR_INFO_NODE_H
#define M2_CHAR_INFO_NODE_H

#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>

#include "hct_node.h"

#define MAX_CHARACTERS 128

typedef struct CharInfoNode {
    char character;
    int frequency;
    char* huffmanCode;
} CharInfoNode;

CharInfoNode* createCharInfoNodeDictionary();

void calculateCharFreqs(const char text[], CharInfoNode* pCharInfoNodeDictionary);

int compareCharFreqs(const void* pVoidFirstCharInfoNode, const void* pVoidSecondCharInfoNode);

void sortCharFreqs(CharInfoNode* pCharInfoNodeDictionary);

void assignHuffmanCodes(HCTNode* pHCTNode, CharInfoNode* pCharInfoNodeDictionary, char* huffmanCodeBuffer, int huffmanCodeLength);

void encodeText(const char text[], CharInfoNode* pCharInfoNodeDictionary);

void destroyCharInfoDictionary(CharInfoNode* pCharInfoNodeDictionary);

void printCharInfoDictionary(CharInfoNode* pCharInfoNodeDictionary);

#endif //M2_CHAR_INFO_NODE_H
