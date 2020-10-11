#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *net_ByteStuffing(char *pcSrc, int iSrcLen, char cStuffByte, int *piDstLen) {
    char *pcDst = NULL;
    int iLoop, iDstPos = 0;

    pcDst = (char *)calloc(iSrcLen * 2, sizeof(char));
    pcDst[iDstPos] = cStuffByte; /* frame begin */
    iDstPos++;

    for (iLoop = 0 ; iLoop < iSrcLen; iLoop++) {
        if (cStuffByte == pcSrc[iLoop]) {
            pcDst[iDstPos] = cStuffByte; /* byte stuffing */
            iDstPos++;
        }

        pcDst[iDstPos] = pcSrc[iLoop];
        iDstPos++;
    }

    pcDst[iDstPos] = cStuffByte; /* frame end */
    iDstPos++;
    *piDstLen = iDstPos;
    
    return pcDst;
}

int main(int argc, char *argv[]) {
    int iLoop = 0, iAfterStuffLen = 0;
    char cFrameBoundary = 'q';
    char *pcAfterStuff = NULL;

    printf("argc = %d\n", argc);
    for (iLoop = 0; iLoop < argc; iLoop++) {
        printf("argv[%d] = %s\n", iLoop, argv[iLoop]);
        pcAfterStuff = net_ByteStuffing(argv[iLoop],
                                        strlen(argv[iLoop]),
                                        cFrameBoundary,
                                        &iAfterStuffLen);
        printf("After stuffing: %s, %d\n", pcAfterStuff, iAfterStuffLen);
        free(pcAfterStuff);
    }


    return 0;
}
