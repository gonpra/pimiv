#include "include/callbacks.h"
#include "include/structs.h"
#include "include/util.h"

#define LAYOUT_USER_LOGIN "../src/layout/login-user.ui"
#define LAYOUT_USER_REGISTER "../src/layout/register-user.ui"
#define LAYOUT_COMPANY_REGISTER "../src/layout/register-company.ui"

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

    set_box_content(main_box, button_box);
    gtk_box_append(GTK_BOX(button_box), btn_show_page_register_company);
}

void on_item_activated() {
    g_print("ativo!!");
}

void show_page_home() {
    show_header_home();

    GtkWidget* list_box = gtk_list_box_new();
    gtk_box_append(GTK_BOX(content_box), list_box);

    GtkWidget* item1 = gtk_button_new_with_label("Empresa");
    GtkWidget* item2 = gtk_button_new_with_label("Registrar");

    gtk_list_box_append(list_box, item1);
    gtk_list_box_append(list_box, item2);

    g_signal_connect(list_box, "row-activated", G_CALLBACK(on_item_activated), NULL);
    set_box_content(content_box, list_box);
}

void show_page_register_company() {
    GtkBuilder* builder = gtk_builder_new_from_file(LAYOUT_COMPANY_REGISTER);

    GtkWidget* entry_box = GTK_WIDGET(gtk_builder_get_object(builder, "entry_box"));
    GtkWidget* button_box = GTK_WIDGET(gtk_builder_get_object(builder, "button_box"));

    GtkWidget* responsible_name_entry = GTK_WIDGET(gtk_builder_get_object(builder, "responsible_name_entry"));
    GtkWidget* company_name_entry = GTK_WIDGET(gtk_builder_get_object(builder, "company_name_entry"));
    GtkWidget* cnpj_entry = GTK_WIDGET(gtk_builder_get_object(builder, "cnpj_entry"));
    GtkWidget* legal_name_entry = GTK_WIDGET(gtk_builder_get_object(builder, "legal_name_entry"));
    GtkWidget* trade_name_entry = GTK_WIDGET(gtk_builder_get_object(builder, "trade_name_entry"));
    GtkWidget* phone_entry = GTK_WIDGET(gtk_builder_get_object(builder, "phone_entry"));
    GtkWidget* address_street_entry = GTK_WIDGET(gtk_builder_get_object(builder, "address_street_entry"));
    GtkWidget* address_number_entry = GTK_WIDGET(gtk_builder_get_object(builder, "address_number_entry"));
    GtkWidget* address_neighborhood_entry = GTK_WIDGET(gtk_builder_get_object(builder, "address_neighborhood_entry"));
    GtkWidget* address_city_entry = GTK_WIDGET(gtk_builder_get_object(builder, "address_city_entry"));
    GtkWidget* address_state_entry = GTK_WIDGET(gtk_builder_get_object(builder, "address_state_entry"));
    GtkWidget* address_zip_entry = GTK_WIDGET(gtk_builder_get_object(builder, "address_zip_entry"));
    GtkWidget* email_entry = GTK_WIDGET(gtk_builder_get_object(builder, "email_entry"));
    GtkWidget* opening_date_entry = GTK_WIDGET(gtk_builder_get_object(builder, "opening_date_entry"));

    GtkWidget* btn_register_company = GTK_WIDGET(gtk_builder_get_object(builder, "btn_register_company"));

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

    set_box_content(content_box, entry_box);
    gtk_box_append(GTK_BOX(entry_box), button_box);
}

void show_page_login() {
    GtkBuilder* builder = gtk_builder_new_from_file(LAYOUT_USER_LOGIN);

    GtkWidget *entry_box = GTK_WIDGET(gtk_builder_get_object(builder, "entry_box"));
    GtkWidget *entry_username = GTK_WIDGET(gtk_builder_get_object(builder, "username_entry"));
    GtkWidget *entry_password = GTK_WIDGET(gtk_builder_get_object(builder, "password_entry"));
    GtkWidget *btn_login = GTK_WIDGET(gtk_builder_get_object(builder, "login_button"));

    EntryUserLoginData* entries = create_entry_user_login_data(entry_username, entry_password);

    g_signal_connect(btn_login, "clicked", G_CALLBACK(on_button_user_login_clicked), entries);
    set_box_content(content_box, entry_box);
}

void show_page_register() {
    GtkBuilder* builder = gtk_builder_new_from_file(LAYOUT_USER_REGISTER);

    GtkWidget *entry_box = GTK_WIDGET(gtk_builder_get_object(builder, "entry_box"));
    GtkWidget *username_entry = GTK_WIDGET(gtk_builder_get_object(builder, "username_entry"));
    GtkWidget *password_entry = GTK_WIDGET(gtk_builder_get_object(builder, "password_entry"));
    GtkWidget *confirm_password_entry = GTK_WIDGET(gtk_builder_get_object(builder, "confirm_password_entry"));
    GtkWidget *btn_register = GTK_WIDGET(gtk_builder_get_object(builder, "register_button"));

    EntryUserRegisterData* entries = create_entry_user_register_data(username_entry, password_entry, confirm_password_entry);

    g_signal_connect(btn_register, "clicked", G_CALLBACK(on_button_user_register_clicked), entries);
    set_box_content(content_box, entry_box);
}

void on_activate(GtkApplication *app, gpointer user_data) {
    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "PIM IV");
    gtk_window_set_default_size(GTK_WINDOW(window), 840, 620);

    main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    show_header_index();

    content_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    // gtk_widget_set_halign(content_box, GTK_ALIGN_CENTER);
    // gtk_widget_set_valign(content_box, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(main_box), content_box);

    gtk_window_set_child(GTK_WINDOW(window), main_box);
    gtk_window_present(GTK_WINDOW(window));
}