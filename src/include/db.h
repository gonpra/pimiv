#pragma once

#include <gtk/gtk.h>

#include "../components/table-company-array.h"

#define TABLE_USERS "db/users.txt"
#define TABLE_COMPANIES "db/companies.txt"
#define TABLE_REPORTS "db/reports.txt"

gboolean db_user_auth(const gchar* username, const gchar* password);
gchar* db_user_insert(const gchar* username, const gchar* password);
gchar* db_company_insert(const gchar* name, const gchar* company_name, const gchar* cnpj, const gchar* legal_name, const gchar* trade_name, const gchar* phone, const gchar* address_street, const gchar* address_number, const gchar* address_neighborhood, const gchar* address_city, const gchar* address_state, const gchar* address_zip, const gchar* email, const gchar* opening_date);
TableCompanyArray* db_company_list();
gboolean db_report_save(const gchar* company_name, const gchar* month, const gchar* gas_spending, const gchar* money_spending);
gint* db_reports_get_money_spending_by_company_name(const gchar* company_name);
gint* db_reports_get_gas_spending_by_company_name(const gchar* company_name);