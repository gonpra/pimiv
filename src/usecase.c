#include "include/structs.h"
#include "include/util.h"
#include "include/db.h"
#include "include/ui.h"
#include "include/usecase.h"

void usecase_create_company(const EntryCompanyRegisterData* data) {
    const AppContext* context = data->context;
    
    const gchar* name_value = gtk_editable_get_text(GTK_EDITABLE(data->name_entry));
    const gchar* company_name_value = gtk_editable_get_text(GTK_EDITABLE(data->company_name_entry));
    const gchar* cnpj_value = gtk_editable_get_text(GTK_EDITABLE(data->cnpj_entry));
    const gchar* legal_name_value = gtk_editable_get_text(GTK_EDITABLE(data->legal_name_entry));
    const gchar* trade_name_value = gtk_editable_get_text(GTK_EDITABLE(data->trade_name_entry));
    const gchar* phone_value = gtk_editable_get_text(GTK_EDITABLE(data->phone_entry));
    const gchar* address_street_value = gtk_editable_get_text(GTK_EDITABLE(data->address_street_entry));
    const gchar* address_number_value = gtk_editable_get_text(GTK_EDITABLE(data->address_number_entry));
    const gchar* address_neighborhood_value = gtk_editable_get_text(GTK_EDITABLE(data->address_neighborhood_entry));
    const gchar* address_city_value = gtk_editable_get_text(GTK_EDITABLE(data->address_city_entry));
    const gchar* address_state_value = gtk_editable_get_text(GTK_EDITABLE(data->address_state_entry));
    const gchar* address_zip_value = gtk_editable_get_text(GTK_EDITABLE(data->address_zip_entry));
    const gchar* email_value = gtk_editable_get_text(GTK_EDITABLE(data->email_entry));
    const gchar* opening_date_value = g_date_time_format_iso8601(gtk_calendar_get_date(GTK_CALENDAR(data->opening_date_entry)));

    if (strlen(name_value) <= 0) {
        run_dialog_error(context->window, "Nome do responsável não preenchido");
        return;
    }

    if (strlen(company_name_value) <= 0) {
        run_dialog_error(context->window, "Nome da empresa não preenchido");
        return;
    }

    if (strlen(cnpj_value) <= 0 && !is_valid_cnpj(cnpj_value)) {
        run_dialog_error(context->window, "CNPJ não preenchido");
        return;
    }
    if(!is_valid_cnpj(cnpj_value)) {
        run_dialog_error(context->window, "CNPJ inválido");
        return;
    }

    if (strlen(legal_name_value) <= 0) {
        run_dialog_error(context->window, "Razão social não preenchida");
        return;
    }

    if (strlen(trade_name_value) <= 0) {
        run_dialog_error(context->window, "Nome fantasia não preenchido");
        return;
    }

    if(strlen(phone_value) <= 0) {
        run_dialog_error(context->window, "Número de telefone não preenchido");
        return;
    }
    if(!is_valid_phone(phone_value)) {
        run_dialog_error(context->window, "Número de telefone inválido");
        return;
    }

    if (strlen(address_street_value) <= 0) {
        run_dialog_error(context->window, "Rua não preenchida");
        return;
    }

    if (strlen(address_number_value) <= 0) {
        run_dialog_error(context->window, "Número não preenchido");
        return;
    }

    if (strlen(address_neighborhood_value) <= 0) {
        run_dialog_error(context->window, "Bairro não preenchido");
        return;
    }

    if (strlen(address_city_value) <= 0) {
        run_dialog_error(context->window, "Cidade não preenchida");
        return;
    }

    if (strlen(address_state_value) <= 0) {
        run_dialog_error(context->window, "Estado não preenchido");
        return;
    }

    if (strlen(address_zip_value) <= 0) {
        run_dialog_error(context->window, "CEP não preenchido");
        return;
    }
    if (!is_valid_cep(address_zip_value)) {
        run_dialog_error(context->window, "CEP inválido");
        return;
    }

    if (strlen(email_value) <= 0) {
        run_dialog_error(context->window, "E-mail não preenchido");
        return;
    }
    if (!is_valid_email(email_value)) {
        run_dialog_error(context->window, "E-mail inválido");
        return;
    }

    if (strlen(opening_date_value) <= 0) {
        run_dialog_error(context->window, "Data de abertura não preenchida");
        return;
    }

    gchar* error_message = db_company_insert(
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

    if (strlen(error_message) == 0) {
        run_dialog(context->window, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Empresa registrada com sucesso!");
    } else {
        run_dialog_error(context->window, error_message);
    }
}
void usecase_create_user(const EntryUserRegisterData* data) {
    const AppContext* context = data->context;
    
    const gchar* username_value = gtk_editable_get_text(GTK_EDITABLE(data->username_entry));
    const gchar* password_value = gtk_editable_get_text(GTK_EDITABLE(data->password_entry));
    const gchar* confirm_password_value = gtk_editable_get_text(GTK_EDITABLE(data->confirm_password_entry));

    if (strlen(username_value) <= 0) {
        run_dialog_error(context->window, "Usuário não preenchido");
        return;
    }

    if (strlen(password_value) <= 0) {
        run_dialog_error(context->window, "Senha não preenchida");
        return;
    }

    if (strlen(confirm_password_value) <= 0) {
        run_dialog_error(context->window, "Confirmação de senha não preenchida");
        return;
    }

    if (strcmp(password_value, confirm_password_value) != 0) {
        run_dialog_error(context->window, "Senha e confirmação de senha estão diferentes");
        return;
    }

    gchar* error_message = db_user_insert(username_value, password_value);
    if (strlen(error_message) == 0) {
        run_dialog(context->window, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Usuário registrado com sucesso!");
    } else {
        run_dialog_error(context->window, error_message);
    }
}

void usecase_auth_user(const EntryUserLoginData* data) {
    const AppContext* context = data->context;

    const gchar* username_value = gtk_editable_get_text(GTK_EDITABLE(data->username_entry));
    const gchar* password_value = gtk_editable_get_text(GTK_EDITABLE(data->password_entry));

    if(db_user_auth(username_value, password_value)) {
        // Clear entry boxes on login
        gtk_editable_set_text(GTK_EDITABLE(data->username_entry), "");
        gtk_editable_set_text(GTK_EDITABLE(data->password_entry), "");

        gtk_stack_set_visible_child_name(GTK_STACK(context->header_stack), HEADER_HOME);
        gtk_stack_set_visible_child_name(GTK_STACK(context->page_stack), PAGE_HOME);
        return;
    };

    run_dialog(context->window, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Usuário e/ou senha inválidos");
}

void usecase_save_report(const EntryReportSaveData* data, TableCompany* report) {
    const AppContext* context = data->context;
    const gchar* gas_spending_value = gtk_editable_get_text(GTK_EDITABLE(data->gas_spending_entry));
    const gchar* money_spending_value = gtk_editable_get_text(GTK_EDITABLE(data->money_spending_entry));
    const gchar* month_value = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(data->month_entry));

    if (strlen(money_spending_value) <= 0) {
        run_dialog_error(context->window, "Valor mensal não preenchido");
        return;
    }

    if (strlen(gas_spending_value) <= 0) {
        run_dialog_error(context->window, "Gastos mensais de gases emitidos não preenchido");
        return;
    }

    if (month_value == NULL || strlen(month_value) <= 0) {
        run_dialog_error(context->window, "Selecione um mês");
        return;
    }

    gchar* company_name;
    g_object_get(report, "company-name", &company_name, NULL);

    if(db_report_save(company_name, month_value, gas_spending_value, money_spending_value)) {
        run_dialog(context->window, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Relatório atualizado com sucesso!");
    }
}

TableCompanyArray* usecase_list_company() {
    return db_company_list();
}

gint* usecase_get_reports_gas_spending(const gchar* company_name) {
    return db_reports_get_gas_spending_by_company_name(company_name);
}

gint* usecase_get_reports_money_spending(const gchar* company_name) {
    return db_reports_get_money_spending_by_company_name(company_name);
}

gboolean usecase_create_report_xls_file(const gchar* output_path) {
      // Create a new workbook
    lxw_workbook  *workbook  = workbook_new(output_path);  // Name for the XLSX file
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);

    FILE *file = fopen(TABLE_REPORTS, "r");
    if (file) {
        char line[256];
        int row = 1;

        while (fgets(line, sizeof(line), file)) {
            gchar *line_company_name = strtok(line, ";");
            gchar *line_month = strtok(NULL, ";");
            gchar *line_gas_spending = strtok(NULL, ";");
            gchar *line_money_spending = strtok(NULL, "\n");

            if (line_company_name) g_strstrip(line_company_name);
            if (line_month) g_strstrip(line_month);
            if (line_gas_spending) g_strstrip(line_gas_spending);
            if (line_money_spending) g_strstrip(line_money_spending);

            // Set headers
            worksheet_write_string(worksheet, 0, 0, "Nome da empresa", NULL);
            worksheet_write_string(worksheet, 0, 1, "Mês", NULL);
            worksheet_write_string(worksheet, 0, 2, "Gastos de gases em toneladas", NULL);
            worksheet_write_string(worksheet, 0, 3, "Valor gasto ao mês", NULL);

            // Write the parsed tokens to the Excel worksheet
            worksheet_write_string(worksheet, row, 0, line_company_name, NULL);
            worksheet_write_string(worksheet, row, 1, line_month, NULL);
            worksheet_write_string(worksheet, row, 2, line_gas_spending, NULL);
            worksheet_write_string(worksheet, row, 3, line_money_spending, NULL);

            row++;  // Move to the next row for the next line of data
        }

        fclose(file);
        workbook_close(workbook);
    } else {
        return FALSE;
    }

    return TRUE;
}

gboolean usecase_create_report_txt_file(const gchar* output_path) {
    FILE* input_file = fopen(TABLE_REPORTS, "r");
    if (!input_file) {
        return FALSE;
    }

    FILE* output_file = fopen(output_path, "w");
    if (output_file) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), input_file)) {
            fputs(buffer, output_file);
        }

        fclose(output_file);
    }

    fclose(input_file);

    return TRUE;
}

gboolean usecase_create_report_csv_file(const gchar* output_path) {
    FILE *source_file = fopen(TABLE_REPORTS, "r");
    if (!source_file) {
        return FALSE;
    }

    FILE *destination_file = fopen(output_path, "w");
    if (!destination_file) {
        fclose(source_file);
        return FALSE;
    }

    fprintf(destination_file, "Nome da empresa,Mês,Gastos de gases em litros,Valor gasto ao mês\n");

    char line[256];
    while (fgets(line, sizeof(line), source_file)) {
        char *token = strtok(line, ";");  // Split by ';'
        int first_token = 1;

        while (token != NULL) {
            if (!first_token) {
                fputc(',', destination_file);  // Add a comma between fields
            }
            first_token = 0;

            // Remove leading/trailing whitespace from the token
            g_strstrip(token);

            fputs(token, destination_file);  // Write the token to the CSV
            token = strtok(NULL, ";");       // Get the next token
        }
        fputc('\n', destination_file);  // End of the CSV row
    }

    fclose(source_file);
    fclose(destination_file);
    return TRUE;
}