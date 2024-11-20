#pragma once

#include <gtk/gtk.h>

#define PAGE_USER_REGISTER "user-register"
#define PAGE_USER_LOGIN "user-login"
#define PAGE_HOME "home"
#define PAGE_COMPANY_REGISTER "company-register"
#define HEADER_INDEX "header-index"
#define HEADER_HOME "header-home"

void on_entry_set_numeric(GtkEditable *editable, const gchar *new_text);
void on_entry_set_date(GtkEntry* entry, gpointer data);

void on_button_user_register_clicked(GtkWidget* widget, gpointer data);
void on_button_user_login_clicked(GtkWidget* button, gpointer data);
void on_button_company_register_clicked(GtkWidget* widget, gpointer data);

void on_switch_page(GtkWidget* widget, gpointer data);