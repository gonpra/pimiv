#pragma once

#include <gtk/gtk.h>

void run_dialog(GtkWindow* parent, GtkDialogFlags flags, GtkMessageType type, GtkButtonsType button, const char* message_format);
gboolean must_be_not_empty(const gchar* value, gchar* error_message);
gboolean must_be_different(const gchar* value1, const gchar* value2, gchar* error_message);