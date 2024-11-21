#pragma once

#include <gtk/gtk.h>

#include "../components/table-report-array.h"

gboolean db_user_auth(const gchar* username, const gchar* password);
gboolean db_user_insert(const gchar* username, const gchar* password);
gboolean db_company_insert(const gchar* name, const gchar* company_name, const gchar* cnpj, const gchar* legal_name, const gchar* trade_name, const gchar* phone, const gchar* address_street, const gchar* address_number, const gchar* address_neighborhood, const gchar* address_city, const gchar* address_state, const gchar* address_zip, const gchar* email, const gchar* opening_date);
TableReportArray* db_company_list();