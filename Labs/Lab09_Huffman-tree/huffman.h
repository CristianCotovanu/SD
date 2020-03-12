#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <string.h>

typedef struct {
    unsigned char value;
    int left, right;
} HuffmanNode;

#define Item int

// Including below so `Item` is defined.
#include "heap.h"

void computeFreqs(char *text, int size, int freqs[256]) {
    for(int i = 0; i < 256; i++){
        freqs[i] = 0;
    }
    for (int i = 0; i < size; i++) {
        freqs[(int) text[i]]++;
    }
}

HuffmanNode *makeTree(int freqs[256], int *size) {
    HuffmanNode *huffman = calloc(256, sizeof(HuffmanNode));
    PriQueue* queue = makeQueue(256);
    int i;
    *size = 0;
    for (i = 0; i < 256; i++){
        if (freqs[i] > 0){
            ItemType x;
            x.content = *size;
            x.prior = freqs[i];

            insert(queue, x);
            huffman[*size].value = i;
            huffman[*size].left = huffman[*size].right = -1;
            (*size)++;
        }
    }
    while (queue->size > 1){
        ItemType l, r, node;
        l = getMin(queue);
        removeMin(queue);
        r = getMin(queue);
        removeMin(queue);
        huffman[*size].left = l.content;
        huffman[*size].right = r.content;
        huffman[*size].value = '\0';
        
        node.content = *size;
        node.prior = l.prior + r.prior;
        insert(queue, node);
        (*size)++;
    }
    ItemType node;
    node = getMin(queue);
    huffman[*size].left = node.content;
    huffman[*size].right = -1;
    huffman[*size].value = '\0';
    (*size)++;
    free(queue->elem);
    free(queue);
    return huffman;
}

void makeCodes(int index, HuffmanNode *nodes, char **codes, char *code) {
    if (nodes[index].value != '\0'){
        codes[index] = calloc(strlen(code) + 1, sizeof(char));
        strcpy(codes[index], code);
    }
    else{
        strcat(code, "0");
        makeCodes(nodes[index].left, nodes, codes, code);
        code[strlen(code) - 1] = '\0';
        strcat(code, "1");
        makeCodes(nodes[index].right, nodes, codes, code);
        code[strlen(code) - 1] = '\0';
    }
}

char *compress(char *text, int textSize, HuffmanNode *nodes, int numNodes) {
   int letters[256], i, count = 0;

    if (textSize == 0){
        char *r = calloc(2, sizeof(char));
        r[0] = 'e';
        return r;
    }

    for (i = 0; i < numNodes; i++){
        if (nodes[i].value == '\0') break;
        letters[(int)nodes[i].value] = count;
        count++;
    }
    
    char **codes = (char**) calloc(count, sizeof(char*));

    char *code = (char*) calloc(256,sizeof(char));
    code[0] = '\0';
    makeCodes(numNodes - 1, nodes, codes, code);
    
    char *compressed = (char*) calloc(256,sizeof(char));
    compressed[0] = '\0';
    for (i = 0; i < textSize; i++){
        int index = letters[(int)text[i]];
        strcat(compressed, codes[index]);
    }

    free(code);
    for(int i = 0; i < count; i++)
        free(codes[i]);
    free(codes);
    return compressed;
}

char *decompress(char *text, int textSize, HuffmanNode *nodes, int numNodes) {
    char* decomp =  calloc(256,sizeof(char));
    decomp[0] = '\0';

    if (textSize == 0){
        return decomp;
    }

    int index = numNodes - 1, size = 0;
    for(int i = 0; i < textSize; i++){
        if( text[i] == '0' ){
            index = nodes[index].left;
        }
        else if (text[i] == '1'){
            index = nodes[index].right;
        }

        if( nodes[index].value != '\0' ){
            decomp[size++] = nodes[index].value;
            index = numNodes - 1;
        }
    }
    decomp[size] = '\0';
    return decomp;
}

#endif

