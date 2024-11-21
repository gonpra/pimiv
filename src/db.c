//
// Created by linpra on 11/19/24.
//

#include "components/table-report.h"
#include "components/table-report-array.h"
#include "include/db.h"
#include "include/util.h"

gboolean db_user_auth(const gchar* username, const gchar* password) {
    gboolean user_authenticated = FALSE;

    FILE* file = fopen("users.txt", "r");
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

gboolean db_user_insert(const gchar* username, const gchar* password) {
    gboolean user_registered = FALSE;

    FILE* file = fopen("users.txt", "a+");
    if (file == NULL) {
        run_dialog_error(NULL, "Erro ao criar banco de dados");
        return user_registered;
    }

    // Get existent users
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        gchar* stored_username = strtok(line, ";");

        if (stored_username != NULL && strcmp(stored_username, username) == 0) {
            run_dialog(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Usuário já existente");
            return user_registered;
        }
    }

    // Insert
    fprintf(file, "%s;%s\n", username, crypt(password, "PIM"));
    fclose(file);
    user_registered = TRUE;

    return user_registered;
}

gboolean db_company_insert(
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
    gboolean company_registered = FALSE;

    FILE* file = fopen("companies.txt", "a+");
    if (file == NULL) {
        run_dialog_error(NULL, "Erro ao criar banco de dados");
        return company_registered;
    }
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
        ),
    fclose(file);
    company_registered = TRUE;

    return company_registered;
}

TableReportArray* db_company_list() {
        FILE* file = fopen("companies.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    TableReport** reports = NULL; // Pointer to an array of TableReports
    gint report_count = 0; // Initialize the count of reports

    char line[256];
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
        TableReport* company_report = table_report_new(name, company_name, cnpj, legal_name,
                                                        trade_name, phone, address_street, address_number,
                                                        address_neighborhood, address_city, address_state,
                                                        address_zip, email, format_datetime_string(opening_date));

        reports = realloc(reports, (report_count + 1) * sizeof(TableReport*));
        if (reports == NULL) {
            perror("Error reallocating memory for reports");
            fclose(file);
            return NULL; // Memory allocation failed
        }

        reports[report_count] = company_report;
        report_count++; // Increment the number of reports
    }

    TableReportArray* array = malloc(sizeof(TableReportArray));
    array->content = reports;
    array->size = report_count;

    fclose(file);

    return array;
}