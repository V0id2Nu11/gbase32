#include "gbase32.h"
#include <stdio.h>
#include <glib.h>


guchar* 
decode2string(
        guchar* text2decode,
        gsize* out_len)
{
    return g_base32_decode(text2decode, out_len);
}

void
printdecode2hex(
        guchar* text2decode,
        gsize* out_len)
{
    guchar* str_data = g_base32_decode(text2decode, out_len);
    gsize str_len = strlen(str_data);

    guchar* str_start;
    str_start = str_data;
    guchar* str_end = str_data + str_len;

    int i = 0;

    while (str_start < str_end) {
        g_print("[%d: %#x]", i++, *str_start++);
    }
    g_print("\n");
}

guchar*
decode2hex(
        guchar* text2decode,
        gsize* out_len)
{
    guchar* str_data = g_base32_decode(text2decode, out_len);
    gsize str_len = strlen(str_data);

    guchar* str_start;
    str_start = str_data;
    guchar* str_end = str_data + str_len;

    guchar* hex;
    hex = (guchar*) g_malloc0(2 * (str_len) + 1);
    guchar buff[3];
    int i = 0;
    guchar* hex_ptr = hex;
    
    while (str_start < str_end) {
        sprintf(buff, "%02x", *str_start++);
        *hex_ptr++ = buff[0];
        *hex_ptr++ = buff[1];
    }
    return hex;
}

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

    unsigned char* decoded_text = decode2string(text2decode, &out_len);
    printf("decode text: %s\n", decoded_text);
    printf("decode text len: %d\n", out_len);

    printf("====>\n");
    printdecode2hex(text2decode, &out_len);

    printf("====>\n");
    unsigned char* decoded_hex = decode2hex(text2decode, &out_len);
    printf("hex: %s\n", decoded_hex);
}

