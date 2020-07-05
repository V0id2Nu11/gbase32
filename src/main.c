#include "gbase32.h"
#include "config.h"
#include <stdio.h>
#include <glib.h>


static gboolean verbose = FALSE;
static gchar* text2decode = NULL;
static gboolean show_hex = FALSE;

static GOptionEntry entries[] = {
    {"decode", 'd', 0, G_OPTION_ARG_STRING, &text2decode,
        "Decode <text> to data", NULL},
    {"hex", 'h', 0, G_OPTION_ARG_NONE, &show_hex,
        "Show decode result in hex", NULL},
    {"verbose", 'v', 0, G_OPTION_ARG_NONE, &verbose,
        "Be verbose", NULL},
    {NULL},
};

guchar* 
decode2string(
        guchar* text2decode,
        gsize* out_len)
{
    return g_base32_decode(text2decode, out_len);
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
    GError *error = NULL;
    GOptionContext* context;

    context = g_option_context_new("- base32 encode & decode");
    g_option_context_add_main_entries(context, entries, NULL);
    g_option_context_set_summary(context, "GBase32 encode & decode");

    if (!g_option_context_parse(context, &argc, &argv, &error)) {
        g_print("option parsing failed: %s\n", error->message);
        exit(1);
    }

    if (text2decode != NULL) {
        gsize out_len = 0;
        if (show_hex) {
            g_print("%s\n", decode2hex(text2decode, &out_len));
        } else {
            g_print("%s\n", decode2string(text2decode, &out_len));
        }
        g_free(text2decode);
    }

    g_option_context_free(context);

    return 0;
}

