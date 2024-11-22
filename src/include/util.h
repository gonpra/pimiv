#pragma once

#include <gtk/gtk.h>
#include <xlsxwriter.h>

void run_dialog(GtkWindow* parent, GtkDialogFlags flags, GtkMessageType type, GtkButtonsType button, const char* message_format);
void run_dialog_error(GtkWindow* parent, const char* message);
gboolean is_valid_cnpj(const gchar* cnpj);
gboolean is_valid_phone(const gchar* phone);
gboolean is_valid_cep(const gchar* cep);
gboolean is_valid_email(const gchar* email);
void clear_box(GtkWidget* box);
void set_box_content(GtkWidget* box, GtkWidget* content);
gchar* format_datetime_string(gchar* datetime);