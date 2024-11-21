#pragma once

#define PAGE_USER_REGISTER "user-register"
#define PAGE_USER_LOGIN "user-login"
#define PAGE_HOME "home"
#define PAGE_COMPANY_REGISTER "company-register"
#define HEADER_INDEX "header-index"
#define HEADER_HOME "header-home"

#include "../components/table-report-array.h"

void usecase_create_company(const EntryCompanyRegisterData* data);
void usecase_create_user(const EntryUserRegisterData* data);
void usecase_auth_user(const EntryUserLoginData* data);
TableReportArray* usecase_list_company();