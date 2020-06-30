#include "gbase32.h"
#include <stdio.h>


int
main(
        int argc,
        char** argv)
{
    if (argc <= 1) {
        printf("too less arg\n");
        return -1;
    }

    unsigned char* text2decode = argv[1];

    long unsigned int out_len;

    unsigned char* decoded_text = g_base32_decode(text2decode, &out_len);
    printf("decode text: %s\n", decoded_text);
    printf("decode text len: %d\n", out_len);
}



