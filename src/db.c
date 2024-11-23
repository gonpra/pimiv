//
// Created by linpra on 11/19/24.
//

#include "components/table-company.h"
#include "components/table-company-array.h"
#include "include/db.h"
#include "include/util.h"

gboolean db_user_auth(const gchar* username, const gchar* password) {
    gboolean user_authenticated = FALSE;

    FILE* file = fopen(TABLE_USERS, "r");
    if (file == NULL) {
        run_dialog_error(NULL, "Erro ao abrir o banco de dados de usuários.");
        return user_authenticated;
    }

    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        char* stored_username = strtok(line, ";");
        char* stored_password = strtok(NULL, "\n");

        if (stored_username == NULL || stored_password == NULL) {
            continue;
        }

        char* crypted_password = crypt(password, "PIM");
        if (crypted_password == NULL) {
            run_dialog_error(NULL, "Erro ao processar a senha.");
            fclose(file);
            return user_authenticated;
        }

        if (strcmp(stored_username, username) == 0 && strcmp(stored_password, crypted_password) == 0) {
            user_authenticated = TRUE;
            break;
        }
    }

    fclose(file);

    return user_authenticated;
}

gchar* db_user_insert(const gchar* username, const gchar* password) {
    gchar* error_message = "";

    FILE* file = fopen(TABLE_USERS, "a+");
    if (file == NULL) {
        error_message = "Falha em abrir banco de dados";
        return error_message;
    }

    // Get existent users
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        gchar* stored_username = strtok(line, ";");

        if (stored_username != NULL && strcmp(stored_username, username) == 0) {
            error_message = "Usuário já existente";
            return error_message;
        }
    }

    // Insert
    fprintf(file, "%s;%s\n", username, crypt(password, "PIM"));
    fclose(file);

    return "";
}

gchar* db_company_insert(
    const gchar* name,
    const gchar* company_name,
    const gchar* cnpj,
    const gchar* legal_name,
    const gchar* trade_name,
    const gchar* phone,
    const gchar* address_street,
    const gchar* address_number,
    const gchar* address_neighborhood,
    const gchar* address_city,
    const gchar* address_state,
    const gchar* address_zip,
    const gchar* email,
    const gchar* opening_date
    ) {
    gchar* error_message = "";
    gchar line[1024]; // Buffer to read each line of the file

    // Open the file in read mode to check for duplicates
    FILE* file = fopen(TABLE_COMPANIES, "r");
    if (file == NULL) {
        error_message = "Erro ao criar banco de dados";
        return error_message;
    }

    // Check if the company_name already exists
    while (fgets(line, sizeof(line), file) != NULL) {
        gchar* token = strtok(line, ";"); // Tokenize the line
        gint field_index = 0;
        while (token != NULL) {
            if (field_index == 1) { // Field index 1 corresponds to company_name
                if (strcmp(token, company_name) == 0) {
                    error_message = "Empresa já cadastrada";
                    fclose(file);
                    return error_message;
                }
                break;
            }
            token = strtok(NULL, ";");
            field_index++;
        }
    }
    fclose(file);

    // Open the file in append mode to add the new company data
    file = fopen(TABLE_COMPANIES, "a");
    if (file == NULL) {
        error_message = "Erro ao criar banco de dados";
        return error_message;
    }

    // Write the new company data to the file
    fprintf(file, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",
        name,
        company_name,
        cnpj,
        legal_name,
        trade_name,
        phone,
        address_street,
        address_number,
        address_neighborhood,
        address_city,
        address_state,
        address_zip,
        email,
        opening_date
    );
    fclose(file);

    return "";
}

TableCompanyArray* db_company_list() {
    FILE* file = fopen(TABLE_COMPANIES, "r");
    if (file == NULL) {
        g_error("Erro ao abrir o banco de dados");
    }

    TableCompany** companies = NULL; // Pointer to an array of TableReports
    gint company_count = 0; // Initialize the count of reports

    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Tokenize the line using ";" as the delimiter
        gchar* name = strtok(line, ";");
        gchar* company_name = strtok(NULL, ";");
        gchar* cnpj = strtok(NULL, ";");
        gchar* legal_name = strtok(NULL, ";");
        gchar* trade_name = strtok(NULL, ";");
        gchar* phone = strtok(NULL, ";");
        gchar* address_street = strtok(NULL, ";");
        gchar* address_number = strtok(NULL, ";");
        gchar* address_neighborhood = strtok(NULL, ";");
        gchar* address_city = strtok(NULL, ";");
        gchar* address_state = strtok(NULL, ";");
        gchar* address_zip = strtok(NULL, ";");
        gchar* email = strtok(NULL, ";");
        gchar* opening_date = strtok(NULL, ";");

        // Create a new TableReport for the company
        TableCompany* company = table_company_new(name, company_name, cnpj, legal_name,
                                                        trade_name, phone, address_street, address_number,
                                                        address_neighborhood, address_city, address_state,
                                                        address_zip, email, format_datetime_string(opening_date));

        companies = realloc(companies, (company_count + 1) * sizeof(TableCompany*));
        if (companies == NULL) {
            perror("Error reallocating memory for reports");
            fclose(file);
            return NULL; // Memory allocation failed
        }

        companies[company_count] = company;
        company_count++; // Increment the number of reports
    }

    TableCompanyArray* array = malloc(sizeof(TableCompanyArray));
    array->content = companies;
    array->size = company_count;

    fclose(file);

    return array;
}

gboolean db_report_save(const gchar* company_name, const gchar* month, const gchar* gas_spending, const gchar* money_spending) {
    FILE *file = fopen(TABLE_REPORTS, "r+");
    if (file == NULL) {
        // If the file doesn't exist, create a new one
        file = fopen(TABLE_REPORTS, "w+");
        if (file == NULL) {
            return FALSE;  // Failed to open the file
        }
    }

    gchar line[256];
    gboolean entry_found = FALSE;
    GString *file_content = g_string_new("");  // To store the entire file content
    gchar *company_name_trimmed = g_strstrip(g_strdup(company_name));
    gchar *month_trimmed = g_strstrip(g_strdup(month));
    gchar *gas_spending_trimmed = g_strstrip(g_strdup(gas_spending));
    gchar *money_spending_trimmed = g_strstrip(g_strdup(money_spending));

    // Read the file content and check if the entry exists
    while (fgets(line, sizeof(line), file)) {
        // Ensure to separate the fields properly by the semicolon
        gchar *line_company_name = strtok(line, ";");
        gchar *line_month = strtok(NULL, ";");
        gchar *line_gas_spending = strtok(NULL, ";");
        gchar *line_money_spending = strtok(NULL, "\n");

        // Strip whitespace from fields in the file
        if (line_company_name) g_strstrip(line_company_name);
        if (line_month) g_strstrip(line_month);
        if (line_gas_spending) g_strstrip(line_gas_spending);
        if (line_money_spending) g_strstrip(line_money_spending);

        // Check if both company and month match
        if (line_company_name && line_month && strcmp(line_company_name, company_name_trimmed) == 0 && strcmp(line_month, month_trimmed) == 0) {
            // Set the entry found flag and update the spending if both match
            entry_found = TRUE;
            // Update the gas and money spending in the line
            g_string_append_printf(file_content, "%s;%s;%s;%s\n", company_name_trimmed, month_trimmed, gas_spending_trimmed, money_spending_trimmed);
        } else {
            // Append the unchanged line to file content with proper line break
            g_string_append_printf(file_content, "%s;%s;%s;%s\n", line_company_name, line_month, line_gas_spending, line_money_spending);
        }
    }

    // If the entry wasn't found, append a new entry
    if (!entry_found) {
        g_string_append_printf(file_content, "%s;%s;%s;%s\n", company_name_trimmed, month_trimmed, gas_spending_trimmed, money_spending_trimmed);
    }

    // Write the updated content back to the file
    fclose(file);  // Close the file after reading
    file = fopen(TABLE_REPORTS, "w+");  // Reopen the file in write mode to overwrite it
    if (file == NULL) {
        return FALSE;  // Failed to open the file for writing
    }

    fputs(file_content->str, file);  // Write the entire updated content to the file

    fclose(file);
    g_string_free(file_content, TRUE);  // Free the GString

    // Free allocated memory for trimmed strings
    g_free(company_name_trimmed);
    g_free(month_trimmed);
    g_free(gas_spending_trimmed);
    g_free(money_spending_trimmed);

    return TRUE;
}

gint* db_reports_get_gas_spending_by_company_name(const gchar* company_name) {
    FILE* file = fopen(TABLE_REPORTS, "r");
    if (!file) {
        return NULL;  // File doesn't exist or cannot be opened
    }

    // Initialize an array for 12 months, default value is 0
    gint* gas_spending = g_new0(gint, 12);

    gchar line[256];
    gchar* company_name_trimmed = g_strstrip(g_strdup(company_name));

    const gchar* months[] = {
        "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho",
        "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"
    };

    while (fgets(line, sizeof(line), file)) {
        // Split the line into fields
        gchar* line_company_name = strtok(line, ";");
        gchar* line_month = strtok(NULL, ";");
        gchar* line_gas_spending = strtok(NULL, ";");

        // Strip whitespace from fields
        if (line_company_name) g_strstrip(line_company_name);
        if (line_month) g_strstrip(line_month);

        // Check if this line belongs to the given company
        if (line_company_name && strcmp(line_company_name, company_name_trimmed) == 0) {
            for (int i = 0; i < 12; i++) {
                if (line_month && strcmp(line_month, months[i]) == 0) {
                    // Parse gas spending and assign to the respective month
                    gas_spending[i] = line_gas_spending ? atoi(g_strstrip(line_gas_spending)) : 0;
                    break;
                }
            }
        }
    }

    fclose(file);
    g_free(company_name_trimmed);
    return gas_spending;  // Caller must free the returned array
}

gint* db_reports_get_money_spending_by_company_name(const gchar* company_name) {
    FILE* file = fopen(TABLE_REPORTS, "r");
    if (!file) {
        return NULL;  // File doesn't exist or cannot be opened
    }

    // Initialize an array for 12 months, default value is 0
    gint* money_spending = g_new0(gint, 12);

    gchar line[256];
    gchar* company_name_trimmed = g_strstrip(g_strdup(company_name));

    const gchar* months[] = {
        "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho",
        "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"
    };

    while (fgets(line, sizeof(line), file)) {
        // Split the line into fields
        gchar* line_company_name = strtok(line, ";");
        gchar* line_month = strtok(NULL, ";");
        strtok(NULL, ";");  // Skip gas spending
        gchar* line_money_spending = strtok(NULL, "\n");

        // Strip whitespace from fields
        if (line_company_name) g_strstrip(line_company_name);
        if (line_month) g_strstrip(line_month);

        // Check if this line belongs to the given company
        if (line_company_name && strcmp(line_company_name, company_name_trimmed) == 0) {
            for (int i = 0; i < 12; i++) {
                if (line_month && strcmp(line_month, months[i]) == 0) {
                    // Parse money spending and assign to the respective month
                    money_spending[i] = line_money_spending ? atoi(g_strstrip(line_money_spending)) : 0;
                    break;
                }
            }
        }
    }

    fclose(file);
    g_free(company_name_trimmed);
    return money_spending;  // Caller must free the returned array
}