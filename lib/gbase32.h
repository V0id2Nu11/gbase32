#pragma once
#ifndef __G_BASE32_H
#define __G_BASE32_H

#include <glib.h>


G_BEGIN_DECLS
gsize g_base32_decode_step(
        const gchar *in,
        gsize len,
        guchar *out,
        gint *state,
        guint64 *save);

guchar* g_base32_decode(
        const gchar *text,
        gsize *out_len);

G_END_DECLS
#endif // __G_BASE32_H
