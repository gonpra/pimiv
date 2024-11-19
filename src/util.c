#include "util.h"

void run_dialog(GtkWindow* parent, GtkDialogFlags flags, GtkMessageType type, GtkButtonsType button, const char* message_format) {
    GtkWidget *dialog = gtk_message_dialog_new(parent, flags, type, button, message_format);
    gtk_widget_show(dialog);
    g_signal_connect(dialog, "response", G_CALLBACK(gtk_window_destroy), NULL);
}

gboolean must_be_not_empty(const gchar* value, gchar* error_message) {
    if (value != NULL && strlen(value) < 0) {
        run_dialog(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, 0, error_message);
        return 0;
    }

    return 1;
}

gboolean must_be_different(const gchar* value1, const gchar* value2, gchar* error_message) {
    if (value1 != NULL && value2 != NULL && strcmp(value1, value2) != 0) {
        run_dialog(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, 0, error_message);
        return 0;
    }

    return 1;
}