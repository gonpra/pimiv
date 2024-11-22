#pragma once

#include <gtk/gtk.h>

typedef struct {
    GtkWindow* window;
    GtkStack* header_stack;
    GtkStack* page_stack;
} AppContext;

typedef struct {
    AppContext* context;
    GtkSingleSelection* selection;
} RowContext;

typedef struct {
    char** lines;
    int num_lines;
    char* format;
} SaveFileData;

typedef struct {
    AppContext* context;

    GtkWidget* username_entry;
    GtkWidget* password_entry;
    GtkWidget* confirm_password_entry;
} EntryUserRegisterData;

typedef struct {
    AppContext* context;

    GtkWidget* username_entry;
    GtkWidget* password_entry;
} EntryUserLoginData;

typedef struct {
    GtkWidget* gas_spending_drawing_area;
    GtkWidget* money_spending_drawing_area;

    AppContext* context;

    GtkWidget* gas_spending_entry;
    GtkWidget* money_spending_entry;
    GtkWidget* month_entry;
} EntryReportSaveData;

typedef struct {
    AppContext* context;

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

EntryUserRegisterData* create_entry_user_register_data(AppContext* context, GtkWidget* username_entry, GtkWidget* password_entry, GtkWidget* confirm_password_entry);
EntryUserLoginData* create_entry_user_login_data(AppContext* context, GtkWidget* username_entry, GtkWidget* password_entry);
EntryReportSaveData* create_entry_report_save_data(AppContext* context, GtkWidget* gas_spending_drawing_area, GtkWidget* money_spending_drawing_area, GtkWidget* gas_spending_entry, GtkWidget* money_spending_entry, GtkWidget* month_entry);

EntryCompanyRegisterData* create_entry_company_register_data(
    AppContext* context,
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