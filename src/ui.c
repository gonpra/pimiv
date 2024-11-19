#include "callbacks.h"
#include "structs.h"

GtkWidget* main_box;
GtkWidget* content_box;

void show_header_index() {
    GtkWidget* button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget* btn_show_page_login = gtk_button_new_with_label("Login");
    GtkWidget* btn_show_page_register = gtk_button_new_with_label("Registrar");

    g_signal_connect(btn_show_page_login, "clicked", G_CALLBACK(on_show_page_login_clicked), NULL);
    g_signal_connect(btn_show_page_register, "clicked", G_CALLBACK(on_show_page_register_clicked), NULL);

    gtk_box_append(GTK_BOX(button_box), btn_show_page_login);
    gtk_box_append(GTK_BOX(button_box), btn_show_page_register);
    gtk_box_append(GTK_BOX(main_box), button_box);
}

void show_header_home() {
    GtkWidget* button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget* btn_show_page_register_company = gtk_button_new_with_label("Registrar empresa");

    g_signal_connect(btn_show_page_register_company, "clicked", G_CALLBACK(on_show_page_register_company_clicked), NULL);

    gtk_box_append(GTK_BOX(button_box), btn_show_page_register_company);
    gtk_box_append(GTK_BOX(content_box), button_box);
}

void show_page_home() {
    gtk_box_remove(GTK_BOX(content_box), gtk_widget_get_first_child(content_box));
    gtk_box_remove(GTK_BOX(main_box), gtk_widget_get_first_child(main_box));

    show_header_home();
}

void show_page_register_company() {
    GtkWidget* entry_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    GtkWidget* name = gtk_entry_new();
    gtk_box_append(GTK_BOX(entry_box), name);


    gtk_box_append(GTK_BOX(content_box), entry_box);

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
    EntryLoginData* entries = create_entry_login_data(username_entry, password_entry);
    g_signal_connect(login_button, "clicked", G_CALLBACK(on_button_login_clicked), entries);

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

    EntryRegisterData* entries = create_entry_register_data(username_entry, password_entry, confirm_password_entry);
    g_signal_connect(register_button, "clicked", G_CALLBACK(on_button_register_clicked), entries);

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