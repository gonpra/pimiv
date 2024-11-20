#pragma once

#include <gtk/gtk.h>

void on_entry_set_numeric(GtkEditable *editable, const gchar *new_text);
void on_entry_set_date(GtkEntry* entry, gpointer data);
void on_show_page_user_login_clicked(GtkWidget* widget, gpointer data);
void on_show_page_user_register_clicked(GtkWidget* widget, gpointer data);
void on_show_page_user_register_company_clicked(GtkWidget* widget, gpointer data);
void on_button_user_register_clicked(GtkWidget* widget, gpointer data);
void on_button_user_login_clicked(GtkWidget* widget, gpointer data);
void on_button_company_register_clicked(GtkWidget* widget, gpointer data);