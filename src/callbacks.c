#include "callbacks.h"
#include "ui.h"
#include "structs.h"
#include "util.h"
#include <gtk/gtk.h>

void on_show_page_login_clicked(GtkWidget* widget, gpointer data) {
    show_page_login();
}

void on_show_page_register_clicked(GtkWidget* widget, gpointer data) {
    show_page_register();
}

void on_show_page_home_clicked(GtkWidget* widget, gpointer data) {
    show_page_home();
}

void on_show_page_register_company_clicked(GtkWidget* widget, gpointer data) {
    show_page_register_company();
}

void on_button_login_clicked(GtkWidget* widget, gpointer data) {
    const EntryLoginData* entries = data;

    const gchar* usernameValue = gtk_editable_get_text(GTK_EDITABLE(entries->username_entry));
    const gchar* passwordValue = gtk_editable_get_text(GTK_EDITABLE(entries->password_entry));

    FILE* file = fopen("users.txt", "a+");
    if (file == NULL) {
        run_dialog(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Erro ao criar banco de dados");
        return;
    }

    // Get existent users
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        gchar* stored_username = strtok(line, ";");
        gchar* stored_password = strtok(NULL, "\n");

        gchar* crypted_password = crypt(passwordValue, "PIM");
        if (stored_username != NULL && strcmp(stored_username, usernameValue) == 0 && stored_password != NULL && strcmp(stored_password, crypted_password) == 0) {
            on_show_page_home_clicked(widget, data);
            return;
        }
        break;
    }

    run_dialog(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Usuário e/ou senha inválidos");
}

void on_button_register_clicked(GtkWidget* widget, gpointer data) {
    const EntryRegisterData* entries = data;

    const gchar* usernameValue = gtk_editable_get_text(GTK_EDITABLE(entries->username_entry));
    const gchar* password_value = gtk_editable_get_text(GTK_EDITABLE(entries->password_entry));
    const gchar* confirm_password_value = gtk_editable_get_text(GTK_EDITABLE(entries->confirm_password_entry));

    if (strlen(usernameValue) <= 0) {
        run_dialog(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Usuário não preenchido");
        return;
    }

    if (strlen(password_value) <= 0) {
        run_dialog(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Senha não preenchida");
        return;
    }

    if (strlen(confirm_password_value) <= 0) {
        run_dialog(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Confirmação de senha não preenchida");
        return;
    }

    if (strcmp(password_value, confirm_password_value) != 0) {
        run_dialog(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Senha e confirmação de senha estão diferentes");
        return;
    }

    // register db code

    FILE* file = fopen("users.txt", "a+");
    if (file == NULL) {
        run_dialog(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Erro ao criar banco de dados");
        return;
    }

    // Get existent users
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        gchar* stored_username = strtok(line, ";");

        if (stored_username != NULL && strcmp(stored_username, usernameValue) == 0) {
            run_dialog(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Usuário já existente");
            return;
        }
    }

    fprintf(file, "%s;%s\n", usernameValue, crypt(password_value, "PIM"));
    fclose(file);

    g_print("success");
}