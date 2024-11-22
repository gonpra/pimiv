#pragma once

#include <gtk/gtk.h>

void ping();

gboolean on_refresh_companies(gpointer data);

void on_save_response(GtkNativeDialog* dialog, int response_id, gpointer user_data);

void on_entry_set_numeric(GtkEditable *editable, const gchar *new_text);

void on_button_user_register_clicked(GtkWidget* widget, gpointer data);
void on_button_user_login_clicked(GtkWidget* button, gpointer data);
void on_button_company_register_clicked(GtkWidget* widget, gpointer data);
void on_button_report_save_clicked(GtkWidget* button, gpointer data);
void on_button_export_txt_clicked(GtkWidget* button, gpointer data);
void on_button_export_xls_clicked(GtkWidget* button, gpointer data);
void on_button_export_csv_clicked(GtkWidget* button, gpointer data);

void on_button_switch_page(GtkWidget* widget, gpointer data);
void on_row_activated(GtkWidget* widget, guint position, gpointer data);
void on_draw_gas_spending(GtkWidget *widget, cairo_t *cr, gpointer user_data);
void on_draw_money_spending(GtkWidget* widget, cairo_t *cr, gpointer user_data);