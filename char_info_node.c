#include "char_info_node.h"

CharInfoNode* createCharInfoNodeDictionary() {
    CharInfoNode* pCharInfoNodeDictionary = (CharInfoNode*)calloc(MAX_CHARACTERS, sizeof(CharInfoNode));
    if (pCharInfoNodeDictionary == NULL) {
        fprintf(stderr, "ERROR: Failed to Create Character Information Dictionary!\nCAUSE: Memory Allocation for pCharInfoNodeDictionary Failed!\n");
        return NULL;
    }

    for (int decimalCharValue = 0; decimalCharValue < MAX_CHARACTERS; decimalCharValue++) {
        pCharInfoNodeDictionary[decimalCharValue].character = (char)decimalCharValue;
        pCharInfoNodeDictionary[decimalCharValue].frequency = 0;
        pCharInfoNodeDictionary[decimalCharValue].huffmanCode = NULL;
    }

    return pCharInfoNodeDictionary;
}

void calculateCharFreqs(const char text[], CharInfoNode* pCharInfoNodeDictionary) {
    if (pCharInfoNodeDictionary == NULL) {
        fprintf(stderr, "ERROR: Failed to Calculate Character Frequencies!\nCAUSE: Pointer to pCharInfoNodeDictionary is NULL!\n");
        return;
    }
    if (text == NULL) {
        fprintf(stderr, "ERROR: Failed to Encode Text!\nCAUSE: text is NULL!\n");
        return;
    }

    for (int textIndex = 0; text[textIndex] != '\0'; textIndex++) {
        unsigned char castedTextCharacter = (unsigned char)text[textIndex];

        if (isprint(castedTextCharacter)) {
            pCharInfoNodeDictionary[castedTextCharacter].frequency++;
        }
    }
}

int compareCharFreqs(const void* pVoidFirstCharInfoNode, const void* pVoidSecondCharInfoNode) {
    CharInfoNode* pFirstCharInfoNode = (CharInfoNode*)pVoidFirstCharInfoNode;
    CharInfoNode* pSecondCharInfoNode = (CharInfoNode*)pVoidSecondCharInfoNode;

    return (pFirstCharInfoNode->frequency - pSecondCharInfoNode->frequency);
}

void sortCharFreqs(CharInfoNode* pCharInfoNodeDictionary) {
    if (pCharInfoNodeDictionary == NULL) {
        fprintf(stderr, "ERROR: Failed to Sort Character Frequencies!\nCAUSE: Pointer to pCharInfoNodeDictionary is NULL!\n");
        return;
    }

    qsort(pCharInfoNodeDictionary, MAX_CHARACTERS, sizeof(CharInfoNode), compareCharFreqs);
}

void assignHuffmanCodes(HCTNode* pHCTNode, CharInfoNode* pCharInfoNodeDictionary, char* huffmanCodeBuffer, int huffmanCodeLength) {
    if (pHCTNode == NULL) return;
    if (pCharInfoNodeDictionary == NULL) {
        fprintf(stderr, "ERROR: Failed to Assign Huffman Codes!\nCAUSE: Pointer to pCharInfoNodeDictionary is NULL!\n");
        return;
    }
    if (huffmanCodeBuffer == NULL) {
        fprintf(stderr, "ERROR: Failed to Assign Huffman Codes!\nCAUSE: Pointer to huffmanCodeBuffer is NULL!\n");
        return;
    }
    if (huffmanCodeLength < 0) {
        fprintf(stderr, "ERROR: Failed to Assign Huffman Codes!\nCAUSE: huffmanCodeLength is Negative!\n");
        return;
    }

    // Check if leaf node and assign Huffman code
    if (pHCTNode->pLeftNode == NULL && pHCTNode->pRightNode == NULL) {
        unsigned char charIndex = (unsigned char)pHCTNode->character;

        for (int decimalCharIndex = 0; decimalCharIndex < MAX_CHARACTERS; ++decimalCharIndex) {
            if (pCharInfoNodeDictionary[decimalCharIndex].character == charIndex) {
                pCharInfoNodeDictionary[decimalCharIndex].huffmanCode = (char*)calloc(huffmanCodeLength + 1, sizeof(char));

                strncpy(pCharInfoNodeDictionary[decimalCharIndex].huffmanCode, huffmanCodeBuffer, huffmanCodeLength);
                pCharInfoNodeDictionary[decimalCharIndex].huffmanCode[huffmanCodeLength] = '\0';

                return;
            }
        }
        return;
    }

    // Recurse on left child with '0' appended
    if (pHCTNode->pLeftNode != NULL) {
        huffmanCodeBuffer[huffmanCodeLength] = '0';
        assignHuffmanCodes(pHCTNode->pLeftNode, pCharInfoNodeDictionary, huffmanCodeBuffer, huffmanCodeLength + 1);
    }

    // Recurse on right child with '1' appended
    if (pHCTNode->pRightNode != NULL) {
        huffmanCodeBuffer[huffmanCodeLength] = '1';
        assignHuffmanCodes(pHCTNode->pRightNode, pCharInfoNodeDictionary, huffmanCodeBuffer, huffmanCodeLength + 1);
    }
}

void encodeText(const char text[], CharInfoNode* pCharInfoNodeDictionary) {
    if (text == NULL) {
        fprintf(stderr, "ERROR: Failed to Encode Text!\nCAUSE: text is NULL!\n");
        return;
    }
    if (pCharInfoNodeDictionary == NULL) {
        fprintf(stderr, "ERROR: Failed to Encode Text!\nCAUSE: Pointer to pCharInfoNodeDictionary is NULL!\n");
        return;
    }

    int textLength = (int)strlen(text);
    char* encodedText = (char*)calloc(textLength * 8 + 1, sizeof(char)); // 8 bits per character

    if (encodedText == NULL) {
        fprintf(stderr, "ERROR: Failed to Encode Text!\nCAUSE: Memory Allocation for Encoded Text Failed!\n");
        return;
    }

    int encodedTextIndex = 0;

    for (int textIndex = 0; textIndex < textLength - 1; textIndex++) {
        unsigned char castedTextCharacter = (unsigned char)text[textIndex];

        for (int decimalCharIndex = 0; decimalCharIndex < MAX_CHARACTERS; decimalCharIndex++) {
            if (pCharInfoNodeDictionary[decimalCharIndex].character == castedTextCharacter) {
                int huffmanCodeLength = (int)strlen(pCharInfoNodeDictionary[decimalCharIndex].huffmanCode);
                strncpy(&encodedText[encodedTextIndex], pCharInfoNodeDictionary[decimalCharIndex].huffmanCode, huffmanCodeLength);
                encodedTextIndex += huffmanCodeLength;
                break;
            }
        }
    }

    encodedText[encodedTextIndex] = '\0';

    fprintf(stdout, "\nHere's your Encoded Text:\n%s\n", encodedText);
    fflush(stdout);

    free(encodedText);
}

void destroyCharInfoDictionary(CharInfoNode* pCharInfoNodeDictionary)
{
    if (pCharInfoNodeDictionary == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Destroy Character Information Dictionary!\nCAUSE: Pointer to pCharInfoNodeDictionary is NULL!\n");
        return;
    }

    for (int decimalCharIndex = 0; decimalCharIndex < MAX_CHARACTERS; decimalCharIndex++)
    {
        if (pCharInfoNodeDictionary[decimalCharIndex].huffmanCode != NULL)
        {
            free(pCharInfoNodeDictionary[decimalCharIndex].huffmanCode);
        }
    }

    free(pCharInfoNodeDictionary);
}

void printCharInfoDictionary(CharInfoNode* pCharInfoNodeDictionary) {
    if (pCharInfoNodeDictionary == NULL) {
        fprintf(stderr, "ERROR: Failed to Print Character Information Dictionary!\nCAUSE: Pointer to pCharInfoNodeDictionary is NULL!\n");
        return;
    }

    fprintf(stdout, "| %s | %s | %s |\n",
           "Characters",
           "Frequencies",
           "Huffman Code");
    fflush(stdout);
    for (int decimalCharIndex = 0; decimalCharIndex < MAX_CHARACTERS; decimalCharIndex++) {
        if (pCharInfoNodeDictionary[decimalCharIndex].frequency > 0) {
            fprintf(stdout, "| %-10c | %04d        | %-12s |\n",
                   pCharInfoNodeDictionary[decimalCharIndex].character,
                   pCharInfoNodeDictionary[decimalCharIndex].frequency,
                   pCharInfoNodeDictionary[decimalCharIndex].huffmanCode);
            fflush(stdout);
        }
    }
}