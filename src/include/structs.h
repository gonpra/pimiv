#pragma once

#include <gtk/gtk.h>

typedef struct {
    GtkWidget* username_entry;
    GtkWidget* password_entry;
    GtkWidget* confirm_password_entry;
} EntryUserRegisterData;

typedef struct {
    GtkWidget* username_entry;
    GtkWidget* password_entry;
} EntryUserLoginData;

typedef struct {
    GtkWidget* name_entry;
    GtkWidget* company_name_entry;
    GtkWidget* cnpj_entry;
    GtkWidget* legal_name_entry;
    GtkWidget* trade_name_entry;
    GtkWidget* phone_entry;
    GtkWidget* address_street_entry;
    GtkWidget* address_number_entry;
    GtkWidget* address_neighborhood_entry;
    GtkWidget* address_city_entry;
    GtkWidget* address_state_entry;
    GtkWidget* address_zip_entry;
    GtkWidget* email_entry;
    GtkWidget* opening_date_entry;
} EntryCompanyRegisterData;

EntryUserRegisterData* create_entry_user_register_data(GtkWidget* username_entry, GtkWidget* password_entry, GtkWidget* confirm_password_entry);
void free_entry_user_register_data(EntryUserRegisterData* data);

EntryUserLoginData* create_entry_user_login_data(GtkWidget* username_entry, GtkWidget* password_entry);
void free_entry_user_login_data(EntryUserLoginData* data);

EntryCompanyRegisterData* create_entry_company_register_data(
    GtkWidget* name_entry,
    GtkWidget* company_name_entry,
    GtkWidget* cnpj_entry,
    GtkWidget* legal_name_entry,
    GtkWidget* trade_name_entry,
    GtkWidget* phone_entry,
    GtkWidget* address_street_entry,
    GtkWidget* address_number_entry,
    GtkWidget* address_neighborhood_entry,
    GtkWidget* address_city_entry,
    GtkWidget* address_state_entry,
    GtkWidget* address_zip_entry,
    GtkWidget* email_entry,
    GtkWidget* opening_date_entry);
void free_entry_company_register_data(EntryCompanyRegisterData* data);