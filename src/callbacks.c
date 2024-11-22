#include "include/callbacks.h"

#include <ctype.h>

#include "include/structs.h"
#include "include/usecase.h"
#include "include/util.h"
#include <gtk/gtk.h>

TableCompany* current_company;

// Usado para debug de callbacks
void ping() {
    g_print("pong!\n");
}

gboolean on_refresh_companies(gpointer data) {
    if (g_list_model_get_n_items(G_LIST_MODEL(data))) {
        return TRUE;
    }

    g_list_store_remove_all(data);

    TableCompanyArray* reports = usecase_list_company();
    for (int i = 0; i < reports->size; i++) {
        g_list_store_append(data, reports->content[i]);
    }
    return TRUE;
}

void on_draw_gas_spending(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    gchar* company_name;
    g_object_get(current_company, "company-name", &company_name, NULL);

    // Get the spending data (12 months assumed)
    gint* data = usecase_get_reports_gas_spending(company_name);
    if (!data) {
        g_free(company_name);
        return; // No data available
    }

    // Months in Portuguese
    const gchar* months[] = {
        "Jan", "Fev", "Mar", "Abr", "Mai", "Jun",
        "Jul", "Ago", "Set", "Out", "Nov", "Dez"
    };

    int num_bars = 12; // Assuming one value per month
    int width = gtk_widget_get_allocated_width(widget);
    int height = gtk_widget_get_allocated_height(widget);

    int padding = 20;        // Space around the edges
    int bar_spacing = 5;     // Space between bars
    int bar_width = (width - (padding * 2) - ((num_bars - 1) * bar_spacing)) / num_bars;

    // Calculate the maximum data value to normalize bar heights
    gint max_value = 1; // Avoid divide by zero
    for (int i = 0; i < num_bars; i++) {
        if (data[i] > max_value) {
            max_value = data[i];
        }
    }

    // Set bar color
    cairo_set_source_rgb(cr, 0.2, 0.6, 1.0); // Blue color

    // Draw each bar
    for (int i = 0; i < num_bars; i++) {
        double bar_height = (double)data[i] / max_value * (height - 2 * padding);

        // Define the rectangle for the bar
        double x = padding + i * (bar_width + bar_spacing);
        double y = height - padding - bar_height;

        cairo_rectangle(cr, x, y, bar_width, bar_height);
    }

    // Fill the bars
    cairo_fill(cr);

    // Add numbers on top of each bar
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0); // Black color
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 10);

    for (int i = 0; i < num_bars; i++) {
        double bar_height = (double)data[i] / max_value * (height - 2 * padding);
        double x = padding + i * (bar_width + bar_spacing) + bar_width / 2.0;
        double y = height - padding - bar_height - 5; // Position number slightly above the bar

        // Convert the data value to a string
        gchar value_str[10];
        g_snprintf(value_str, sizeof(value_str), "%d", data[i]);

        // Center the number on the bar
        cairo_text_extents_t extents;
        cairo_text_extents(cr, value_str, &extents);
        cairo_move_to(cr, x - extents.width / 2.0, y);
        cairo_show_text(cr, value_str);
    }

    // Add labels for months below the bars
    for (int i = 0; i < num_bars; i++) {
        double x = padding + i * (bar_width + bar_spacing) + bar_width / 2.0;
        double y = height - padding + 15; // Slightly below the bars

        cairo_text_extents_t extents;
        cairo_text_extents(cr, months[i], &extents);
        cairo_move_to(cr, x - extents.width / 2.0, y);
        cairo_show_text(cr, months[i]);
    }

    // Clean up
    g_free(company_name);
    g_free(data);
}

void on_draw_money_spending(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    gchar* company_name;
    g_object_get(current_company, "company-name", &company_name, NULL);

    // Get the spending data (12 months assumed)
    gint* data = usecase_get_reports_money_spending(company_name);
    if (!data) {
        g_free(company_name);
        return; // No data available
    }

    // Months in Portuguese
    const gchar* months[] = {
        "Jan", "Fev", "Mar", "Abr", "Mai", "Jun",
        "Jul", "Ago", "Set", "Out", "Nov", "Dez"
    };

    int num_bars = 12; // Assuming one value per month
    int width = gtk_widget_get_allocated_width(widget);
    int height = gtk_widget_get_allocated_height(widget);

    int padding = 20;        // Space around the edges
    int bar_spacing = 5;     // Space between bars
    int bar_width = (width - (padding * 2) - ((num_bars - 1) * bar_spacing)) / num_bars;

    // Calculate the maximum data value to normalize bar heights
    gint max_value = 1; // Avoid divide by zero
    for (int i = 0; i < num_bars; i++) {
        if (data[i] > max_value) {
            max_value = data[i];
        }
    }

    // Set bar color
    cairo_set_source_rgb(cr, 0.2, 0.6, 1.0); // Blue color

    // Draw each bar
    for (int i = 0; i < num_bars; i++) {
        double bar_height = (double)data[i] / max_value * (height - 2 * padding);

        // Define the rectangle for the bar
        double x = padding + i * (bar_width + bar_spacing);
        double y = height - padding - bar_height;

        cairo_rectangle(cr, x, y, bar_width, bar_height);
    }

    // Fill the bars
    cairo_fill(cr);

    // Add numbers on top of each bar
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0); // Black color
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 10);

    for (int i = 0; i < num_bars; i++) {
        double bar_height = (double)data[i] / max_value * (height - 2 * padding);
        double x = padding + i * (bar_width + bar_spacing) + bar_width / 2.0;
        double y = height - padding - bar_height - 5; // Position number slightly above the bar

        // Convert the data value to a string
        gchar value_str[10];
        g_snprintf(value_str, sizeof(value_str), "%d", data[i]);

        // Center the number on the bar
        cairo_text_extents_t extents;
        cairo_text_extents(cr, value_str, &extents);
        cairo_move_to(cr, x - extents.width / 2.0, y);
        cairo_show_text(cr, value_str);
    }

    // Add labels for months below the bars
    for (int i = 0; i < num_bars; i++) {
        double x = padding + i * (bar_width + bar_spacing) + bar_width / 2.0;
        double y = height - padding + 15; // Slightly below the bars

        cairo_text_extents_t extents;
        cairo_text_extents(cr, months[i], &extents);
        cairo_move_to(cr, x - extents.width / 2.0, y);
        cairo_show_text(cr, months[i]);
    }

    // Clean up
    g_free(company_name);
    g_free(data);
}

void on_entry_set_numeric(GtkEditable *editable, const gchar* new_text) {
    if(!isdigit(new_text[0])) {
        gtk_editable_delete_text(editable, 0, -1);
    }
}

void on_file_chooser_response(GtkDialog *dialog, gint response_id, gpointer user_data) {
    const gchar* extension = g_object_get_data(G_OBJECT(dialog), "extension");

    if (response_id == GTK_RESPONSE_ACCEPT) {
        GFile* file = gtk_file_chooser_get_file(GTK_FILE_CHOOSER(dialog));
        gchar* file_path = g_file_get_path(file);


        if (extension == "xls") {
            if (!usecase_create_report_xls_file(file_path)) {
                run_dialog_error(GTK_WINDOW(dialog), "Failed to create report file");
            }
        } else if (extension == "txt") {
            if (!usecase_create_report_txt_file(file_path)) {
                run_dialog_error(GTK_WINDOW(dialog), "Failed to create report file");
            }
        } else if (extension == "csv") {
            if (!usecase_create_report_csv_file(file_path)) {
                run_dialog_error(GTK_WINDOW(dialog), "Failed to create report file");
            }
        }

        // After saving, free the file path
        g_free(file_path);
    }

    gtk_window_destroy(GTK_WINDOW(dialog));
}

void on_button_export_txt_clicked(GtkWidget* widget, gpointer user_data) {
    const AppContext* context = user_data;
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Save As", context->window,
                                                    GTK_FILE_CHOOSER_ACTION_SAVE,
                                                    "_Cancel", GTK_RESPONSE_CANCEL,
                                                    "_Save", GTK_RESPONSE_ACCEPT,
                                                    NULL);

    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), "relatório.txt");

    gtk_widget_show(dialog);

    g_object_set_data(G_OBJECT(dialog), "extension", "txt");
    g_signal_connect(dialog, "response", G_CALLBACK(on_file_chooser_response), NULL);
}

void on_button_export_csv_clicked(GtkWidget* widget, gpointer user_data) {
    const AppContext* context = user_data;
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Save As", context->window,
                                                    GTK_FILE_CHOOSER_ACTION_SAVE,
                                                    "_Cancel", GTK_RESPONSE_CANCEL,
                                                    "_Save", GTK_RESPONSE_ACCEPT,
                                                    NULL);

    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), "relatório.csv");

    gtk_widget_show(dialog);

    g_object_set_data(G_OBJECT(dialog), "extension", "csv");
    g_signal_connect(dialog, "response", G_CALLBACK(on_file_chooser_response), NULL);
}

void on_button_export_xls_clicked(GtkWidget* widget, gpointer user_data) {
    const AppContext* context = user_data;
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Save As", context->window,
                                                    GTK_FILE_CHOOSER_ACTION_SAVE,
                                                    "_Cancel", GTK_RESPONSE_CANCEL,
                                                    "_Save", GTK_RESPONSE_ACCEPT,
                                                    NULL);

    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), "relatório.xls");

    gtk_widget_show(dialog);

    g_object_set_data(G_OBJECT(dialog), "extension", "xls");
    g_signal_connect(dialog, "response", G_CALLBACK(on_file_chooser_response), NULL);
}

void on_button_switch_page(GtkWidget* widget, gpointer data) {
    AppContext* context = (AppContext*) data;

    const gchar* target_page = g_object_get_data(G_OBJECT(GTK_BUTTON(widget)), "target-page");
    if (target_page) {
        gtk_stack_set_visible_child_name(GTK_STACK(context->page_stack), target_page);
        if (g_strcmp0(target_page, PAGE_HOME) == 0 || g_strcmp0(target_page, PAGE_COMPANY_REGISTER) == 0) {
            gtk_stack_set_visible_child_name(GTK_STACK(context->header_stack), HEADER_HOME);
        } else {
            gtk_stack_set_visible_child_name(GTK_STACK(context->header_stack), HEADER_INDEX);
        }
    }
}

void on_button_report_save_clicked(GtkWidget* widget, gpointer data) {
    if (current_company == NULL) {
        return;
    }

    EntryReportSaveData* report_data = data;
    usecase_save_report(report_data, current_company);
    gtk_widget_queue_draw(report_data->gas_spending_drawing_area);
    gtk_widget_queue_draw(report_data->money_spending_drawing_area);
}

void on_row_activated(GtkWidget* widget, guint position, gpointer data) {
    const RowContext* row_context = (RowContext*) data;
    const AppContext* context = (AppContext*) row_context->context;

    current_company = gtk_single_selection_get_selected_item(row_context->selection);
    gtk_stack_set_visible_child_name(GTK_STACK(context->page_stack), PAGE_REPORT);
}

void on_button_company_register_clicked(GtkWidget* widget, gpointer data) {
    const EntryCompanyRegisterData* entries = data;
    usecase_create_company(entries);
}

void on_button_user_login_clicked(GtkWidget* widget, gpointer data) {
    const EntryUserLoginData* entries = data;
    usecase_auth_user(entries);
}

void on_button_user_register_clicked(GtkWidget* widget, gpointer data) {
    const EntryUserRegisterData* entries = data;
    usecase_create_user(entries);
}