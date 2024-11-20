#include "callbacks.h"
#include "structs.h"

GtkWidget* main_box;
GtkWidget* content_box;

void show_header_index() {
    GtkWidget* button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget* btn_show_page_login = gtk_button_new_with_label("Login");
    GtkWidget* btn_show_page_register = gtk_button_new_with_label("Registrar");

    g_signal_connect(btn_show_page_login, "clicked", G_CALLBACK(on_show_page_user_login_clicked), NULL);
    g_signal_connect(btn_show_page_register, "clicked", G_CALLBACK(on_show_page_user_register_clicked), NULL);

    gtk_box_append(GTK_BOX(button_box), btn_show_page_login);
    gtk_box_append(GTK_BOX(button_box), btn_show_page_register);
    gtk_box_append(GTK_BOX(main_box), button_box);
}

void show_header_home() {
    GtkWidget* button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget* btn_show_page_register_company = gtk_button_new_with_label("Registrar empresa");

    g_signal_connect(btn_show_page_register_company, "clicked", G_CALLBACK(on_show_page_user_register_company_clicked), NULL);

    gtk_box_append(GTK_BOX(button_box), btn_show_page_register_company);
    gtk_box_append(GTK_BOX(main_box), button_box);
}

void show_page_home() {
    gtk_box_remove(GTK_BOX(content_box), gtk_widget_get_first_child(content_box));
    gtk_box_remove(GTK_BOX(main_box), gtk_widget_get_first_child(main_box));

    show_header_home();
}

void show_page_register_company() {

    GtkWidget* entry_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // Create entry for "Nome e dados do responsável"
    GtkWidget* responsible_name_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(responsible_name_entry), "Nome do responsável");
    gtk_box_append(GTK_BOX(entry_box), responsible_name_entry);

    // Create entry for "Nome da empresa"
    GtkWidget* company_name_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(company_name_entry), "Nome da empresa");
    gtk_box_append(GTK_BOX(entry_box), company_name_entry);

    // Create entry for "CNPJ"
    GtkWidget* cnpj_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(cnpj_entry), "CNPJ");
    g_signal_connect_after(gtk_editable_get_delegate(GTK_EDITABLE(cnpj_entry)), "insert-text", G_CALLBACK(on_entry_set_numeric), NULL);
    gtk_box_append(GTK_BOX(entry_box), cnpj_entry);

    // Create entry for "Razão social"
    GtkWidget* legal_name_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(legal_name_entry), "Razão social");
    gtk_box_append(GTK_BOX(entry_box), legal_name_entry);

    // Create entry for "Nome fantasia"
    GtkWidget* trade_name_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(trade_name_entry), "Nome fantasia");
    gtk_box_append(GTK_BOX(entry_box), trade_name_entry);

    // Create entry for "Telefone"
    GtkWidget* phone_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(phone_entry), "Telefone");
    g_signal_connect_after(gtk_editable_get_delegate(GTK_EDITABLE(phone_entry)), "insert-text", G_CALLBACK(on_entry_set_numeric), NULL);
    gtk_box_append(GTK_BOX(entry_box), phone_entry);

    // Create entry for "Rua" (Address - Street)
    GtkWidget* address_street_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(address_street_entry), "Rua");
    gtk_box_append(GTK_BOX(entry_box), address_street_entry);

    // Create entry for "Número" (Address - Number)
    GtkWidget* address_number_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(address_number_entry), "Número");
    g_signal_connect_after(gtk_editable_get_delegate(GTK_EDITABLE(address_number_entry)), "insert-text", G_CALLBACK(on_entry_set_numeric), NULL);
    gtk_box_append(GTK_BOX(entry_box), address_number_entry);

    // Create entry for "Bairro" (Address - Neighborhood)
    GtkWidget* address_neighborhood_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(address_neighborhood_entry), "Bairro");
    gtk_box_append(GTK_BOX(entry_box), address_neighborhood_entry);

    // Create entry for "Cidade" (Address - City)
    GtkWidget* address_city_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(address_city_entry), "Cidade");
    gtk_box_append(GTK_BOX(entry_box), address_city_entry);

    // Create entry for "Estado" (Address - State)
    GtkWidget* address_state_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(address_state_entry), "Estado");
    gtk_box_append(GTK_BOX(entry_box), address_state_entry);

    // Create entry for "CEP" (Postal Code)
    GtkWidget* address_zip_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(address_zip_entry), "CEP");
    gtk_box_append(GTK_BOX(entry_box), address_zip_entry);

    // Create entry for "E-mail"
    GtkWidget* email_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(email_entry), "E-mail");
    gtk_box_append(GTK_BOX(entry_box), email_entry);

    // Create entry for "Data de abertura" (Opening Date)
    GtkWidget* opening_date_entry = gtk_calendar_new();
    gtk_box_append(GTK_BOX(entry_box), opening_date_entry);

    GtkWidget* button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    GtkWidget* btn_register_company = gtk_button_new_with_label("Registrar empresa");
    gtk_box_append(GTK_BOX(button_box), btn_register_company);

    EntryCompanyRegisterData* entries = create_entry_company_register_data(
        responsible_name_entry,
        company_name_entry,
        cnpj_entry,
        legal_name_entry,
        trade_name_entry,
        phone_entry,
        address_street_entry,
        address_number_entry,
        address_neighborhood_entry,
        address_city_entry,
        address_state_entry,
        address_zip_entry,
        email_entry,
        opening_date_entry
    );
    g_signal_connect(btn_register_company, "clicked", G_CALLBACK(on_button_company_register_clicked), entries);

    gtk_box_append(GTK_BOX(content_box), entry_box);
    gtk_box_append(GTK_BOX(content_box), button_box);
}

void show_page_login() {
    gtk_box_remove(GTK_BOX(content_box), gtk_widget_get_first_child(content_box));

    GtkWidget* entry_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    GtkWidget* username_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(username_entry), "Nome de usuário");
    gtk_box_append(GTK_BOX(entry_box), username_entry);

    GtkWidget* password_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_entry), "Senha");
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_box_append(GTK_BOX(entry_box), password_entry);

    GtkWidget* button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
    gtk_box_append(GTK_BOX(entry_box), button_box);

    GtkWidget* login_button = gtk_button_new_with_label("Login");
    gtk_box_append(GTK_BOX(button_box), login_button);
    EntryUserLoginData* entries = create_entry_user_login_data(username_entry, password_entry);
    g_signal_connect(login_button, "clicked", G_CALLBACK(on_button_user_login_clicked), entries);

    gtk_box_append(GTK_BOX(content_box), entry_box);
    gtk_box_append(GTK_BOX(content_box), button_box);
}

void show_page_register() {
    gtk_box_remove(GTK_BOX(content_box), gtk_widget_get_first_child(content_box));

    GtkWidget* entry_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    GtkWidget* username_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(username_entry), "Nome de usuário");
    gtk_box_append(GTK_BOX(entry_box), username_entry);

    GtkWidget* password_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_entry), "Senha");
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_box_append(GTK_BOX(entry_box), password_entry);

    GtkWidget* confirm_password_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(confirm_password_entry), "Confirmar senha");
    gtk_entry_set_visibility(GTK_ENTRY(confirm_password_entry), FALSE);
    gtk_box_append(GTK_BOX(entry_box), confirm_password_entry);

    GtkWidget* button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
    gtk_box_append(GTK_BOX(entry_box), button_box);

    GtkWidget* register_button = gtk_button_new_with_label("Registrar");
    gtk_box_append(GTK_BOX(button_box), register_button);

    EntryUserRegisterData* entries = create_entry_user_register_data(username_entry, password_entry, confirm_password_entry);
    g_signal_connect(register_button, "clicked", G_CALLBACK(on_button_user_register_clicked), entries);

    gtk_box_append(GTK_BOX(content_box), entry_box);
    gtk_box_append(GTK_BOX(content_box), button_box);
}

void on_activate(GtkApplication *app, gpointer user_data) {
    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Title");
    gtk_window_set_default_size(GTK_WINDOW(window), 840, 620);

    main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    show_header_index();

    content_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    //gtk_widget_set_halign(content_box, GTK_ALIGN_CENTER);
    //gtk_widget_set_valign(content_box, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(main_box), content_box);


    gtk_window_set_child(GTK_WINDOW(window), main_box);
    gtk_window_present(GTK_WINDOW(window));
}