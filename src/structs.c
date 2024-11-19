#include "structs.h"
#include <gtk/gtk.h>

EntryRegisterData* create_entry_register_data(GtkWidget* usernameEntry, GtkWidget* passwordEntry, GtkWidget* confirm_password_entry) {
    EntryRegisterData* data = g_malloc(sizeof(EntryRegisterData));
    data->username_entry = usernameEntry;
    data->password_entry = passwordEntry;
    data->confirm_password_entry = confirm_password_entry;
    return data;
}

void free_entry_register_data(EntryRegisterData* data) {
    g_free(data);
}

EntryLoginData* create_entry_login_data(GtkWidget* username_entry, GtkWidget* password_entry) {
    EntryLoginData* data = g_malloc(sizeof(EntryLoginData));
    data->username_entry = username_entry;
    data->password_entry = password_entry;
    return data;
}

void free_entry_login_data(EntryLoginData* data) {
    g_free(data);
}