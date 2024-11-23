#include "include/util.h"
#include <xlsxwriter.h>

void run_dialog(GtkWindow *parent, GtkDialogFlags flags, GtkMessageType type, GtkButtonsType button,
                const char *message_format) {
    GtkWidget *dialog = gtk_message_dialog_new(parent, flags, type, button, message_format);
    gtk_widget_show(dialog);
    g_signal_connect(dialog, "response", G_CALLBACK(gtk_window_destroy), NULL);
}

void run_dialog_error(GtkWindow *parent, const gchar *message) {
    run_dialog(parent, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, message);
}

gboolean is_valid_cnpj(const gchar *cnpj) {
    if (strlen(cnpj) != 14) {
        return FALSE;
    }

    for (gsize i = 0; i < 14; i++) {
        if (!g_ascii_isdigit(cnpj[i])) {
            return FALSE;
        }
    }

    gint first_digit_weights[12] = {5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};
    gint second_digit_weights[13] = {6, 5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};

    gint sum = 0;
    for (gsize i = 0; i < 12; i++) {
        sum += (cnpj[i] - '0') * first_digit_weights[i];
    }
    gint first_digit = 11 - (sum % 11);
    if (first_digit >= 10) first_digit = 0;

    if ((cnpj[12] - '0') != first_digit) {
        return FALSE;
    }

    sum = 0;
    for (gsize i = 0; i < 13; i++) {
        sum += (cnpj[i] - '0') * second_digit_weights[i];
    }
    gint second_digit = 11 - (sum % 11);
    if (second_digit >= 10) second_digit = 0;

    if ((cnpj[13] - '0') != second_digit) {
        return FALSE;
    }

    return TRUE; // CNPJ is valid
}

gboolean is_valid_phone(const gchar *telephone) {
    // This regex will allow a format like +1234567890, 123-456-7890, or 1234567890.
    GRegex *regex = g_regex_new("^\\+?\\d{1,4}[-\\s]?\\(?\\d{1,4}\\)?[-\\s]?\\d{6,10}$", 0, 0, NULL);
    gboolean isMatch = g_regex_match(regex, telephone, 0, NULL);

    g_regex_unref(regex); // Free regex object

    return isMatch;
}

gboolean is_valid_cep(const gchar *cep) {
    const gchar *pattern = "^[0-9]{5}[0-9]{3}$";

    GRegex *regex = g_regex_new(pattern, 0, 0, NULL);

    if (regex == NULL) {
        g_print("Could not compile regex.\n");
        return FALSE;
    }

    gboolean isMatch = g_regex_match(regex, cep, 0, NULL);

    g_regex_unref(regex);

    return isMatch;
}

gboolean is_valid_email(const gchar *email) {
    GRegex *regex;
    gboolean result;

    const gchar *email_regex = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";

    regex = g_regex_new(email_regex, 0, 0, NULL);

    result = g_regex_match(regex, email, 0, NULL);

    g_regex_unref(regex);

    return result;
}

void clear_box(GtkWidget *box) {
    GtkWidget *child = gtk_widget_get_first_child(box);

    while (child != NULL && gtk_widget_get_parent(child) == box) {
        GtkWidget *first_child = gtk_widget_get_first_child(child);

        if (GTK_IS_WIDGET(first_child)) {
            gtk_box_remove(GTK_BOX(box), child);
        }

        child = first_child;
    }
}

void set_box_content(GtkWidget *box, GtkWidget *content) {
    clear_box(box);
    gtk_box_append(GTK_BOX(box), content);
}

gchar *format_datetime_string(gchar *datetime_str) {
    // Find the period (.) in the string that starts the microseconds
    // gchar* period_pos = g_strstr_len(datetime_str, -1, ".");
    //
    // gchar* trimmed_str;
    // if (period_pos != NULL) {
    //     // Trim the string to exclude the microseconds part
    //     trimmed_str = g_strndup(datetime_str, period_pos - datetime_str);
    // } else {
    //     // If there's no period, use the original string
    //     trimmed_str = g_strdup(datetime_str);
    // }
    //
    // gchar *dash_pos = strrchr(trimmed_str, '-');
    //
    // if (dash_pos != NULL) {
    //     // Truncate the string up to the '-' character
    //     *dash_pos = '\0';  // Replace the '-' with a null terminator, effectively trimming everything after it
    // }
    //
    // gchar *datetime_str_with_timezone = g_strconcat(trimmed_str, "-03:00", NULL);
    //
    // // Convert the trimmed gchar* to GDateTime
    // GDateTime *datetime = g_date_time_new_from_iso8601(datetime_str_with_timezone, NULL);
    //
    // // Format the GDateTime as day/month/year
    // gchar *formatted_datetime = g_date_time_format(datetime, "%d/%m/%Y");
    //
    // return formatted_datetime;
    if (datetime_str == NULL) {
        return datetime_str;
    }
    return g_strchomp(datetime_str);
}