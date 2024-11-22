#include "components/table-company-array.h"
#include "components/table-company.h"
#include "include/callbacks.h"
#include "include/db.h"
#include "include/structs.h"
#include "include/usecase.h"
#include "include/util.h"

#define LAYOUT_USER_LOGIN "layout/login-user.ui"
#define LAYOUT_USER_REGISTER "layout/register-user.ui"
#define LAYOUT_COMPANY_REGISTER "layout/register-company.ui"
#define LAYOUT_HOME "layout/home.ui"
#define LAYOUT_REPORT "layout/report.ui"

GtkWidget* main_window;

GtkWidget* create_header_index(gpointer data) {
    AppContext* context = data;

    GtkWidget* header = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    GtkWidget* btn_show_page_login = gtk_button_new_with_label("Login");
    GtkWidget* btn_show_page_register = gtk_button_new_with_label("Registrar");

    g_object_set_data(G_OBJECT(btn_show_page_login), "target-page", PAGE_USER_LOGIN);
    g_signal_connect(btn_show_page_login, "clicked", G_CALLBACK(on_button_switch_page), context);

    g_object_set_data(G_OBJECT(btn_show_page_register), "target-page", PAGE_USER_REGISTER);
    g_signal_connect(btn_show_page_register, "clicked", G_CALLBACK(on_button_switch_page), context);

    gtk_box_append(GTK_BOX(header), btn_show_page_login);
    gtk_box_append(GTK_BOX(header), btn_show_page_register);

    return header;
}

GtkWidget* create_header_home(gpointer data) {
    AppContext* context = data;

    GtkWidget* header = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    GtkWidget* btn_show_page_home = gtk_button_new_with_label("Home");
    g_object_set_data(G_OBJECT(btn_show_page_home), "target-page", PAGE_HOME);
    g_signal_connect(btn_show_page_home, "clicked", G_CALLBACK(on_button_switch_page), context);

    GtkWidget* btn_logout = gtk_button_new_with_label("Logout");
    g_object_set_data(G_OBJECT(btn_logout), "target-page", PAGE_USER_LOGIN);
    g_signal_connect(btn_logout, "clicked", G_CALLBACK(on_button_switch_page), context);

    GtkWidget* btn_show_page_register_company = gtk_button_new_with_label("Registrar empresa");
    g_object_set_data(G_OBJECT(btn_show_page_register_company), "target-page", PAGE_COMPANY_REGISTER);
    g_signal_connect(btn_show_page_register_company, "clicked", G_CALLBACK(on_button_switch_page), context);

    gtk_box_append(GTK_BOX(header), btn_logout);
    gtk_box_append(GTK_BOX(header), btn_show_page_home);
    gtk_box_append(GTK_BOX(header), btn_show_page_register_company);

    return header;
}

GtkWidget* create_page_report(gpointer data) {
    AppContext* context = data;

    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    GtkBuilder* builder = gtk_builder_new_from_file(LAYOUT_REPORT);
    GtkWidget* main_box = GTK_WIDGET(gtk_builder_get_object(builder, "main_box"));
    GtkWidget* horizontal_box = GTK_WIDGET(gtk_builder_get_object(builder, "horizontal_box"));
    gtk_widget_set_halign(horizontal_box, GTK_ALIGN_CENTER);

    GtkWidget* month_selector = GTK_WIDGET(gtk_builder_get_object(builder, "month_selector"));

    GtkWidget* gas_spending_entry = GTK_WIDGET(gtk_builder_get_object(builder, "gas_spending_entry"));
    GtkWidget* money_spending_entry = GTK_WIDGET(gtk_builder_get_object(builder, "money_spending_entry"));
    GtkWidget* btn_save_report = GTK_WIDGET(gtk_builder_get_object(builder, "save_button"));

    GtkWidget* gas_spending_drawing_area = GTK_WIDGET(gtk_builder_get_object(builder, "gas_spending_drawing_area"));
    g_object_set_data(G_OBJECT(gas_spending_drawing_area), "draw-type", "gas");
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(gas_spending_drawing_area), on_draw_gas_spending, NULL, NULL);

    GtkWidget* money_spending_drawing_area = GTK_WIDGET(gtk_builder_get_object(builder, "money_spending_drawing_area"));
    g_object_set_data(G_OBJECT(money_spending_drawing_area), "draw-type", "money");
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(money_spending_drawing_area), on_draw_money_spending, NULL, NULL);

    EntryReportSaveData* report_data = create_entry_report_save_data(context, gas_spending_drawing_area, money_spending_drawing_area, gas_spending_entry, money_spending_entry, month_selector);
    g_signal_connect(btn_save_report, "clicked", G_CALLBACK(on_button_report_save_clicked), report_data);

    GtkWidget* btn_export_txt = GTK_WIDGET(gtk_builder_get_object(builder, "export_txt"));
    g_signal_connect(btn_export_txt, "clicked", G_CALLBACK(on_button_export_txt_clicked), context);

    GtkWidget* btn_export_xls = GTK_WIDGET(gtk_builder_get_object(builder, "export_xls"));
    g_signal_connect(btn_export_xls, "clicked", G_CALLBACK(on_button_export_xls_clicked), context);

    GtkWidget* btn_export_csv = GTK_WIDGET(gtk_builder_get_object(builder, "export_csv"));
    g_signal_connect(btn_export_csv, "clicked", G_CALLBACK(on_button_export_csv_clicked), context);

    gtk_box_append(GTK_BOX(box), main_box);

    return box;
}

GtkWidget* create_page_home(gpointer data) {
    AppContext* context = data;

    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    g_autoptr(GtkBuilder) builder = NULL;
    g_type_ensure(TABLE_COMPANY_TYPE);

    builder = gtk_builder_new_from_file(LAYOUT_HOME);

    GtkWidget* scrolled_window = GTK_WIDGET(gtk_builder_get_object(builder, "scrolled_window"));
    GtkWidget* column_view = GTK_WIDGET(gtk_builder_get_object(builder, "column_view"));
    GObject* selection = gtk_builder_get_object(builder, "selection");

    GListStore* store = G_LIST_STORE(gtk_builder_get_object(builder, "store"));

    TableCompanyArray* reports = usecase_list_company();
    for (int i = 0; i < reports->size; i++) {
        g_list_store_append(store, reports->content[i]);
    }

    g_timeout_add(1000, on_refresh_companies, store);

    RowContext* row_context = g_new0(RowContext, 1);
    row_context->context = context;
    row_context->selection = GTK_SINGLE_SELECTION(selection);

    g_signal_connect(column_view, "activate", G_CALLBACK(on_row_activated), row_context);

    gtk_box_append(GTK_BOX(box), scrolled_window);
    return box;
}

GtkWidget* create_page_register_company(gpointer data) {
    AppContext* context = data;

    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

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

    // Set fields to NUMERIC
    g_signal_connect_after(gtk_editable_get_delegate(GTK_EDITABLE(cnpj_entry)), "insert-text", G_CALLBACK(on_entry_set_numeric), NULL);
    g_signal_connect_after(gtk_editable_get_delegate(GTK_EDITABLE(phone_entry)), "insert-text", G_CALLBACK(on_entry_set_numeric), NULL);
    g_signal_connect_after(gtk_editable_get_delegate(GTK_EDITABLE(address_number_entry)), "insert-text", G_CALLBACK(on_entry_set_numeric), NULL);
    g_signal_connect_after(gtk_editable_get_delegate(GTK_EDITABLE(address_zip_entry)), "insert-text", G_CALLBACK(on_entry_set_numeric), NULL);

    EntryCompanyRegisterData* entries = create_entry_company_register_data(
        context,
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

    gtk_box_append(GTK_BOX(box), entry_box);
    gtk_box_append(GTK_BOX(entry_box), button_box);

    return box;
}

GtkWidget* create_page_login_user(gpointer data) {
    AppContext* context = data;

    GtkBuilder* builder = gtk_builder_new_from_file(LAYOUT_USER_LOGIN);

    GtkWidget *entry_box = GTK_WIDGET(gtk_builder_get_object(builder, "entry_box"));
    GtkWidget *entry_username = GTK_WIDGET(gtk_builder_get_object(builder, "username_entry"));
    GtkWidget *entry_password = GTK_WIDGET(gtk_builder_get_object(builder, "password_entry"));
    GtkWidget *btn_login = GTK_WIDGET(gtk_builder_get_object(builder, "login_button"));

    EntryUserLoginData* entries = create_entry_user_login_data(context, entry_username, entry_password);

    g_signal_connect(btn_login, "clicked", G_CALLBACK(on_button_user_login_clicked), entries);

    return entry_box;
}

GtkWidget* create_page_register_user(gpointer data) {
    AppContext* context = data;

    GtkBuilder* builder = gtk_builder_new_from_file(LAYOUT_USER_REGISTER);

    GtkWidget *entry_box = GTK_WIDGET(gtk_builder_get_object(builder, "entry_box"));
    GtkWidget *username_entry = GTK_WIDGET(gtk_builder_get_object(builder, "username_entry"));
    GtkWidget *password_entry = GTK_WIDGET(gtk_builder_get_object(builder, "password_entry"));
    GtkWidget *confirm_password_entry = GTK_WIDGET(gtk_builder_get_object(builder, "confirm_password_entry"));
    GtkWidget *btn_register = GTK_WIDGET(gtk_builder_get_object(builder, "register_button"));

    EntryUserRegisterData* entries = create_entry_user_register_data(context, username_entry, password_entry, confirm_password_entry);

    g_signal_connect(btn_register, "clicked", G_CALLBACK(on_button_user_register_clicked), entries);

    return entry_box;
}

void load_css() {
    GtkCssProvider *css_provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();

    gtk_css_provider_load_from_path(css_provider, "style.css");
    gtk_style_context_add_provider_for_display(display,
                                               GTK_STYLE_PROVIDER(css_provider),
                                               GTK_STYLE_PROVIDER_PRIORITY_USER);

    g_object_unref(css_provider);
}

void on_home_reload(gpointer user_data) {
    AppContext* context = user_data;
    gtk_stack_remove(context->page_stack, PAGE_HOME);
    gtk_stack_add_named(context->page_stack, create_page_home(context), PAGE_HOME);
}

void on_activate(GtkApplication *app, gpointer user_data) {
    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "PIM IV");
    gtk_window_set_default_size(GTK_WINDOW(window), 1080, 620);

    load_css();

    AppContext* context = g_malloc(sizeof(AppContext));
    context->window = GTK_WINDOW(window);
    context->header_stack = GTK_STACK(gtk_stack_new());
    context->page_stack = GTK_STACK(gtk_stack_new());

    gtk_stack_set_transition_type(GTK_STACK(context->header_stack), GTK_STACK_TRANSITION_TYPE_CROSSFADE);
    gtk_stack_add_named(GTK_STACK(context->header_stack), create_header_index(context), HEADER_INDEX);
    gtk_stack_add_named(GTK_STACK(context->header_stack), create_header_home(context), HEADER_HOME);

    gtk_stack_set_transition_type(GTK_STACK(context->page_stack), GTK_STACK_TRANSITION_TYPE_CROSSFADE);
    gtk_stack_add_named(GTK_STACK(context->page_stack), create_page_home(context), PAGE_HOME);
    gtk_stack_add_named(GTK_STACK(context->page_stack), create_page_register_company(context), PAGE_COMPANY_REGISTER);
    gtk_stack_add_named(GTK_STACK(context->page_stack), create_page_login_user(context), PAGE_USER_LOGIN);
    gtk_stack_add_named(GTK_STACK(context->page_stack), create_page_register_user(context), PAGE_USER_REGISTER);
    gtk_stack_add_named(GTK_STACK(context->page_stack), create_page_report(context), PAGE_REPORT);


    gtk_stack_set_visible_child_name(GTK_STACK(context->header_stack), HEADER_INDEX);
    gtk_stack_set_visible_child_name(GTK_STACK(context->page_stack), PAGE_USER_LOGIN);

    GtkWidget* main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_append(GTK_BOX(main_box), GTK_WIDGET(context->header_stack));
    gtk_box_append(GTK_BOX(main_box), GTK_WIDGET(context->page_stack));

    gtk_window_set_child(GTK_WINDOW(window), main_box);
    gtk_window_present(GTK_WINDOW(window));
}