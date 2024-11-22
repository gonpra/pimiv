#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

#define TABLE_COMPANY_TYPE (table_company_get_type())
G_DECLARE_FINAL_TYPE(TableCompany, table_company, TABLE, COMPANY, GObject)
TableCompany* table_company_new(const gchar *name,
                              const gchar *company_name,
                              const gchar *cnpj,
                              const gchar *legal_name,
                              const gchar *trade_name,
                              const gchar *phone,
                              const gchar *address_street,
                              const gchar *address_number,
                              const gchar *address_neighborhood,
                              const gchar *address_city,
                              const gchar *address_state,
                              const gchar *address_zip,
                              const gchar *email,
                              const gchar *opening_date);

G_END_DECLS