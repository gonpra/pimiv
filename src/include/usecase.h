#pragma once

#define PAGE_USER_REGISTER "user-register"
#define PAGE_USER_LOGIN "user-login"
#define PAGE_HOME "home"
#define PAGE_COMPANY_REGISTER "company-register"
#define PAGE_REPORT "report"
#define HEADER_INDEX "header-index"
#define HEADER_HOME "header-home"

#include "../components/table-company-array.h"

void usecase_create_company(const EntryCompanyRegisterData* data);
void usecase_create_user(const EntryUserRegisterData* data);
void usecase_auth_user(const EntryUserLoginData* data);
void usecase_save_report(const EntryReportSaveData* data, TableCompany* company);
TableCompanyArray* usecase_list_company();
gint* usecase_get_reports_gas_spending(const gchar* company_name);
gint* usecase_get_reports_money_spending(const gchar* company_name);
gboolean usecase_create_report_xls_file(const gchar* output_path);
gboolean usecase_create_report_txt_file(const gchar* output_path);
gboolean usecase_create_report_csv_file(const gchar* output_path);