#include "callbacks.h"

#include <ctype.h>

#include "ui.h"
#include "structs.h"
#include "util.h"
#include "db.h"
#include <gtk/gtk.h>

void on_entry_set_numeric(GtkEditable *editable, const gchar* new_text) {
    if(!isdigit(new_text[0])) {
        gtk_editable_delete_text(editable, 0, -1);
    }
}

void on_show_page_user_login_clicked(GtkWidget* widget, gpointer data) {
    show_page_login();
}

void on_show_page_user_register_clicked(GtkWidget* widget, gpointer data) {
    show_page_register();
}

void on_show_page_home_clicked(GtkWidget* widget, gpointer data) {
    show_page_home();
}

void on_show_page_user_register_company_clicked(GtkWidget* widget, gpointer data) {
    show_page_register_company();
}

void on_button_company_register_clicked(GtkWidget* widget, gpointer data) {
    const EntryCompanyRegisterData* entries = data;

    const gchar* name_value = gtk_editable_get_text(GTK_EDITABLE(entries->name_entry));
    const gchar* company_name_value = gtk_editable_get_text(GTK_EDITABLE(entries->company_name_entry));
    const gchar* cnpj_value = gtk_editable_get_text(GTK_EDITABLE(entries->cnpj_entry));
    const gchar* legal_name_value = gtk_editable_get_text(GTK_EDITABLE(entries->legal_name_entry));
    const gchar* trade_name_value = gtk_editable_get_text(GTK_EDITABLE(entries->trade_name_entry));
    const gchar* phone_value = gtk_editable_get_text(GTK_EDITABLE(entries->phone_entry));
    const gchar* address_street_value = gtk_editable_get_text(GTK_EDITABLE(entries->address_street_entry));
    const gchar* address_number_value = gtk_editable_get_text(GTK_EDITABLE(entries->address_number_entry));
    const gchar* address_neighborhood_value = gtk_editable_get_text(GTK_EDITABLE(entries->address_neighborhood_entry));
    const gchar* address_city_value = gtk_editable_get_text(GTK_EDITABLE(entries->address_city_entry));
    const gchar* address_state_value = gtk_editable_get_text(GTK_EDITABLE(entries->address_state_entry));
    const gchar* address_zip_value = gtk_editable_get_text(GTK_EDITABLE(entries->address_zip_entry));
    const gchar* email_value = gtk_editable_get_text(GTK_EDITABLE(entries->email_entry));
    const gchar* opening_date_value = g_date_time_format_iso8601(gtk_calendar_get_date(GTK_CALENDAR(entries->opening_date_entry)));


    if (strlen(name_value) <= 0) {
        run_dialog_error(NULL, "Nome do responsável não preenchido");
        return;
    }

    if (strlen(company_name_value) <= 0) {
        run_dialog_error(NULL, "Nome da empresa não preenchido");
        return;
    }

    if (strlen(cnpj_value) <= 0 && !is_valid_cnpj(cnpj_value)) {
        run_dialog_error(NULL, "CNPJ não preenchido");
        return;
    }
    if(!is_valid_cnpj(cnpj_value)) {
        run_dialog_error(NULL, "CNPJ inválido");
        return;
    }

    if (strlen(legal_name_value) <= 0) {
        run_dialog_error(NULL, "Razão social não preenchida");
        return;
    }

    if (strlen(trade_name_value) <= 0) {
        run_dialog_error(NULL, "Nome fantasia não preenchido");
        return;
    }

    if(strlen(phone_value) <= 0) {
        run_dialog_error(NULL, "Número de telefone não preenchido");
        return;
    }
    if(!is_valid_phone(phone_value)) {
        run_dialog_error(NULL, "Número de telefone inválido");
        return;
    }

    if (strlen(address_street_value) <= 0) {
        run_dialog_error(NULL, "Rua não preenchida");
        return;
    }

    if (strlen(address_number_value) <= 0) {
        run_dialog_error(NULL, "Número não preenchido");
        return;
    }

    if (strlen(address_neighborhood_value) <= 0) {
        run_dialog_error(NULL, "Bairro não preenchido");
        return;
    }

    if (strlen(address_city_value) <= 0) {
        run_dialog_error(NULL, "Cidade não preenchida");
        return;
    }

    if (strlen(address_state_value) <= 0) {
        run_dialog_error(NULL, "Estado não preenchido");
        return;
    }

    if (strlen(address_zip_value) <= 0) {
        run_dialog_error(NULL, "CEP não preenchido");
        return;
    }
    if (!is_valid_cep(address_zip_value)) {
        run_dialog_error(NULL, "CEP inválido");
        return;
    }

    if (strlen(email_value) <= 0) {
        run_dialog_error(NULL, "E-mail não preenchido");
        return;
    }
    if (!is_valid_email(email_value)) {
        run_dialog_error(NULL, "E-mail inválido");
        return;
    }

    if (strlen(opening_date_value) <= 0) {
        run_dialog_error(NULL, "Data de abertura não preenchida");
        return;
    }

    gboolean success = db_company_insert(
        name_value,
        company_name_value,
        cnpj_value,
        legal_name_value,
        trade_name_value,
        phone_value,
        address_street_value,
        address_number_value,
        address_neighborhood_value,
        address_city_value,
        address_state_value,
        address_zip_value,
        email_value,
        opening_date_value
    );

    if (success) {
        show_page_home();
    }
}

void on_button_user_login_clicked(GtkWidget* widget, gpointer data) {
    const EntryUserLoginData* entries = data;

    const gchar* usernameValue = gtk_editable_get_text(GTK_EDITABLE(entries->username_entry));
    const gchar* passwordValue = gtk_editable_get_text(GTK_EDITABLE(entries->password_entry));

    if(db_user_auth(usernameValue, passwordValue)) {
        show_page_home();
        return;
    };

    run_dialog(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Usuário e/ou senha inválidos");
}

void on_button_user_register_clicked(GtkWidget* widget, gpointer data) {
    const EntryUserRegisterData* entries = data;

    const gchar* username_value = gtk_editable_get_text(GTK_EDITABLE(entries->username_entry));
    const gchar* password_value = gtk_editable_get_text(GTK_EDITABLE(entries->password_entry));
    const gchar* confirm_password_value = gtk_editable_get_text(GTK_EDITABLE(entries->confirm_password_entry));

    if (strlen(username_value) <= 0) {
        run_dialog_error(NULL, "Usuário não preenchido");
        return;
    }

    if (strlen(password_value) <= 0) {
        run_dialog_error(NULL, "Senha não preenchida");
        return;
    }

    if (strlen(confirm_password_value) <= 0) {
        run_dialog_error(NULL, "Confirmação de senha não preenchida");
        return;
    }

    if (strcmp(password_value, confirm_password_value) != 0) {
        run_dialog_error(NULL, "Senha e confirmação de senha estão diferentes");
        return;
    }

    db_user_insert(username_value, password_value);
}