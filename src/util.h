#pragma once

#include <gtk/gtk.h>

void run_dialog(GtkWindow* parent, GtkDialogFlags flags, GtkMessageType type, GtkButtonsType button, const char* message_format);
void run_dialog_error(GtkWindow* parent, const char* message);
gboolean is_valid_cnpj(const gchar* cnpj);
gboolean is_valid_phone(const gchar* phone);
gboolean is_valid_cep(const gchar* cep);
gboolean is_valid_email(const gchar* email);