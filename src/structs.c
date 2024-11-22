#include "include/structs.h"
#include <gtk/gtk.h>

EntryUserRegisterData* create_entry_user_register_data(AppContext* context, GtkWidget* usernameEntry, GtkWidget* passwordEntry, GtkWidget* confirm_password_entry) {
    EntryUserRegisterData* data = g_malloc(sizeof(EntryUserRegisterData));
    data->context = context;
    data->username_entry = usernameEntry;
    data->password_entry = passwordEntry;
    data->confirm_password_entry = confirm_password_entry;
    return data;
}

EntryUserLoginData* create_entry_user_login_data(AppContext* context, GtkWidget* username_entry, GtkWidget* password_entry) {
    EntryUserLoginData* data = g_malloc(sizeof(EntryUserLoginData));
    data->context = context;
    data->username_entry = username_entry;
    data->password_entry = password_entry;
    return data;
}

EntryReportSaveData* create_entry_report_save_data(AppContext* context, GtkWidget* gas_spending_drawing_area, GtkWidget* money_spending_drawing_area, GtkWidget* gas_spending_entry, GtkWidget* money_spending_entry, GtkWidget* month_entry) {
    EntryReportSaveData* data = g_malloc(sizeof(EntryReportSaveData));
    data->context = context;
    data->gas_spending_drawing_area = gas_spending_drawing_area;
    data->money_spending_drawing_area = money_spending_drawing_area;
    data->gas_spending_entry = gas_spending_entry;
    data->money_spending_entry = money_spending_entry;
    data->month_entry = month_entry;
    return data;
}

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
    GtkWidget* opening_date_entry) {

    EntryCompanyRegisterData* data = g_malloc(sizeof(EntryCompanyRegisterData));
    data->context = context;
    data->name_entry = name_entry;
    data->company_name_entry = company_name_entry;
    data->cnpj_entry = cnpj_entry;
    data->legal_name_entry = legal_name_entry;
    data->trade_name_entry = trade_name_entry;
    data->phone_entry = phone_entry;
    data->address_street_entry = address_street_entry;
    data->address_number_entry = address_number_entry;
    data->address_neighborhood_entry = address_neighborhood_entry;
    data->address_city_entry = address_city_entry;
    data->address_state_entry = address_state_entry;
    data->address_zip_entry = address_zip_entry;
    data->email_entry = email_entry;
    data->opening_date_entry = opening_date_entry;

    return data;
}