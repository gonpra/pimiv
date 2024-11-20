//
// Created by linpra on 11/19/24.
//

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