#pragma once

#include <gtk/gtk.h>

typedef struct {
    GtkWidget* username_entry;
    GtkWidget* password_entry;
    GtkWidget* confirm_password_entry;
} EntryRegisterData;

typedef struct {
    GtkWidget* username_entry;
    GtkWidget* password_entry;
} EntryLoginData;

EntryRegisterData* create_entry_register_data(GtkWidget* username_entry, GtkWidget* password_entry, GtkWidget* confirm_password_entry);
void free_entry_register_data(EntryRegisterData* data);

EntryLoginData* create_entry_login_data(GtkWidget* username_entry, GtkWidget* password_entry);
void free_entry_login_data(EntryLoginData* data);