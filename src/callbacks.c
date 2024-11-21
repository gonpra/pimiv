#include "include/callbacks.h"

#include <ctype.h>

#include "include/structs.h"
#include "include/usecase.h"
#include <gtk/gtk.h>

void on_entry_set_numeric(GtkEditable *editable, const gchar* new_text) {
    if(!isdigit(new_text[0])) {
        gtk_editable_delete_text(editable, 0, -1);
    }
}

void on_switch_page(GtkWidget* widget, gpointer data) {
    AppContext* context = (AppContext*) data;

    const gchar* target_page = g_object_get_data(G_OBJECT(GTK_BUTTON(widget)), "target-page");
    if (target_page) {
        gtk_stack_set_visible_child_name(GTK_STACK(context->page_stack), target_page);
        if (g_strcmp0(target_page, PAGE_HOME) == 0 || g_strcmp0(target_page, PAGE_COMPANY_REGISTER) == 0) {
            gtk_stack_set_visible_child_name(GTK_STACK(context->header_stack), HEADER_HOME);
        } else {
            gtk_stack_set_visible_child_name(GTK_STACK(context->header_stack), HEADER_INDEX);
        }
    }
}

void on_button_company_register_clicked(GtkWidget* widget, gpointer data) {
    const EntryCompanyRegisterData* entries = data;
    usecase_create_company(entries);
}

void on_button_user_login_clicked(GtkWidget* widget, gpointer data) {
    const EntryUserLoginData* entries = data;
    usecase_auth_user(data);
}

void on_button_user_register_clicked(GtkWidget* widget, gpointer data) {
    const EntryUserRegisterData* entries = data;
    usecase_create_user(data);
}