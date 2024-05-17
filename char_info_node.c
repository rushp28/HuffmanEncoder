#include "char_info_node.h"

CharInfoNode* createCharInfoNodeDictionary()
{
    CharInfoNode* pCharInfoNodeDictionary = (CharInfoNode*)calloc(MAX_CHARACTERS, sizeof(CharInfoNode));
    if (pCharInfoNodeDictionary == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Create Character Information Dictionary!\nCAUSE: Memory Allocation for pCharInfoNodeDictionary Failed!\n");
        return NULL;
    }

    for (int decimalCharValue = 0; decimalCharValue < MAX_CHARACTERS; decimalCharValue++)
    {
        pCharInfoNodeDictionary[decimalCharValue].character = (char)decimalCharValue;
    }

    return pCharInfoNodeDictionary;
}

void calculateCharFreqs(CharInfoNode* pCharInfoNodeDictionary, const char text[])
{
    if (pCharInfoNodeDictionary == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Calculate Character Frequencies!\nCAUSE: Pointer to pCharInfoNodeDictionary is NULL!\n");
        return;
    }

    for (int textIndex = 0; text[textIndex] != '\0'; textIndex++)
    {
        unsigned char castedTextCharacter = (unsigned char)text[textIndex];

        if (isprint(castedTextCharacter))
        {
            pCharInfoNodeDictionary[castedTextCharacter].frequency++;
        }
    }
}

int compareCharFreqs(const void* pVoidFirstCharInfoNode, const void* pVoidSecondCharInfoNode)
{
    CharInfoNode* pFirstCharInfoNode = (CharInfoNode*)pVoidFirstCharInfoNode;
    CharInfoNode* pSecondCharInfoNode = (CharInfoNode*)pVoidSecondCharInfoNode;

    return (pFirstCharInfoNode->frequency - pSecondCharInfoNode->frequency);
}

void sortCharFreqs(CharInfoNode* pCharInfoNodeDictionary)
{
    if (pCharInfoNodeDictionary == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Sort Character Frequencies!\nCAUSE: Pointer to pCharInfoNodeDictionary is NULL!\n");
        return;
    }

    qsort(pCharInfoNodeDictionary, MAX_CHARACTERS, sizeof(CharInfoNode), compareCharFreqs);
}

void assignHuffmanCodes(HCTNode* pHCTNode, CharInfoNode* pCharInfoNodeDictionary, const char* huffmanCode, int huffmanCodeLength)
{
    if (pHCTNode == NULL) return;

    // Allocate memory for the new huffmanCode string
    char* newHuffmanCode = calloc(1, huffmanCodeLength + 2); // +2 for the new bit and null terminator
    strncpy(newHuffmanCode, huffmanCode, huffmanCodeLength);
    newHuffmanCode[huffmanCodeLength] = '\0';

    // Recursive calls for left and right children
    if (pHCTNode->pLeftNode!= NULL)
    {
        newHuffmanCode[huffmanCodeLength] = '0';
        assignHuffmanCodes(pHCTNode->pLeftNode, pCharInfoNodeDictionary, newHuffmanCode, huffmanCodeLength + 1);
    }
    if (pHCTNode->pRightNode!= NULL)
    {
        newHuffmanCode[huffmanCodeLength] = '1';
        assignHuffmanCodes(pHCTNode->pRightNode, pCharInfoNodeDictionary, newHuffmanCode, huffmanCodeLength + 1);
    }

    // Check if leaf node and assign Huffman code
    if (pHCTNode->pLeftNode == NULL && pHCTNode->pRightNode == NULL) {
        unsigned char charIndex = (unsigned char)pHCTNode->character;
        for (int decimalCharIndex = 0; decimalCharIndex < MAX_CHARACTERS; ++decimalCharIndex)
        {
            if (pCharInfoNodeDictionary[decimalCharIndex].character == charIndex)
            {
                pCharInfoNodeDictionary[decimalCharIndex].huffmanCode = calloc(1, huffmanCodeLength + 1);

                strncpy(pCharInfoNodeDictionary[decimalCharIndex].huffmanCode, newHuffmanCode, huffmanCodeLength);
                pCharInfoNodeDictionary[decimalCharIndex].huffmanCode[huffmanCodeLength] = '\0';

                free(newHuffmanCode);
                break;
            }
        }
    }
    else
    {
        free(newHuffmanCode); // Free the temporary huffmanCode string if not assigned
    }
}

void encodeText(const char text[], CharInfoNode* pCharInfoNodeDictionary)
{
    if (pCharInfoNodeDictionary == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Encode Text!\nCAUSE: Pointer to pCharInfoNodeDictionary is NULL!\n");
        return;
    }

    int textLength = strlen(text);
    char* encodedText = (char*)calloc(textLength * 8 + 1, sizeof(char)); // 8 bits per character
    if (encodedText == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Encode Text!\nCAUSE: Memory Allocation for Encoded Text Failed!\n");
        return;
    }

    int encodedTextIndex = 0;
    for (int textIndex = 0; textIndex < textLength; textIndex++)
    {
        unsigned char castedTextCharacter = (unsigned char)text[textIndex];
        for (int decimalCharIndex = 0; decimalCharIndex < MAX_CHARACTERS; decimalCharIndex++)
        {
            if (pCharInfoNodeDictionary[decimalCharIndex].character == castedTextCharacter)
            {
                int huffmanCodeLength = strlen(pCharInfoNodeDictionary[decimalCharIndex].huffmanCode);
                strncpy(&encodedText[encodedTextIndex], pCharInfoNodeDictionary[decimalCharIndex].huffmanCode, huffmanCodeLength);
                encodedTextIndex += huffmanCodeLength;
                break;
            }
        }
    }

    encodedText[encodedTextIndex] = '\0';

    printf("Encoded Text: %s\n", encodedText);

    free(encodedText);
}

void decodeText(const char encodedText[], CharInfoNode* pCharInfoNodeDictionary)
{
    if (pCharInfoNodeDictionary == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Decode Text!\nCAUSE: Pointer to pCharInfoNodeDictionary is NULL!\n");
        return;
    }

    int encodedTextLength = strlen(encodedText);
    int decodedTextLength = 0;

    char* decodedText = (char*)calloc(encodedTextLength + 1, sizeof(char));
    if (decodedText == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Decode Text!\nCAUSE: Memory Allocation for Decoded Text Failed!\n");
        return;
    }

    int encodedTextIndex = 0;

    while (encodedTextIndex < encodedTextLength)
    {
        HCTNode* pHCTNode = NULL;
        for (int decimalCharIndex = 0; decimalCharIndex < MAX_CHARACTERS; decimalCharIndex++)
        {
            if (pCharInfoNodeDictionary[decimalCharIndex].huffmanCode != NULL)
            {
                int huffmanCodeLength = strlen(pCharInfoNodeDictionary[decimalCharIndex].huffmanCode);

                if (strncmp(&encodedText[encodedTextIndex], pCharInfoNodeDictionary[decimalCharIndex].huffmanCode, huffmanCodeLength) == 0)
                {
                    decodedText[decodedTextLength++] = pCharInfoNodeDictionary[decimalCharIndex].character;
                    encodedTextIndex += huffmanCodeLength;

                    break;
                }
            }
        }
    }

    decodedText[decodedTextLength] = '\0';

    printf("Decoded Text: %s\n", decodedText);

    free(decodedText);
}

void freeCharInfoDictionary(CharInfoNode* pCharInfoNodeDictionary)
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

void printCharInfoDictionary(CharInfoNode* pCharInfoNodeDictionary)
{
    if (pCharInfoNodeDictionary == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Print Character Information Dictionary!\nCAUSE: Pointer to pCharInfoNodeDictionary is NULL!\n");
        return;
    }

    for (int decimalCharIndex = 0; decimalCharIndex < MAX_CHARACTERS; decimalCharIndex++)
    {
        if (pCharInfoNodeDictionary[decimalCharIndex].frequency > 0)
        {
            printf("Character: %c %d, Frequency: %d, Huffman Code: %s\n", pCharInfoNodeDictionary[decimalCharIndex].character, pCharInfoNodeDictionary[decimalCharIndex].character, pCharInfoNodeDictionary[decimalCharIndex].frequency, pCharInfoNodeDictionary[decimalCharIndex].huffmanCode);
        }
    }
}