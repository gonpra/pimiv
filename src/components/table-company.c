//
// Created by linpra on 11/20/24.
//

#include "table-company.h"
#include <glib-object.h>

enum {
    PROP_NAME = 1,
    PROP_COMPANY_NAME,
    PROP_CNPJ,
    PROP_LEGAL_NAME,
    PROP_TRADE_NAME,
    PROP_PHONE,
    PROP_ADDRESS_STREET,
    PROP_ADDRESS_NUMBER,
    PROP_ADDRESS_NEIGHBORHOOD,
    PROP_ADDRESS_CITY,
    PROP_ADDRESS_STATE,
    PROP_ADDRESS_ZIP,
    PROP_EMAIL,
    PROP_OPENING_DATE,
    N_PROPERTIES
};

static GParamSpec *properties[N_PROPERTIES];

struct _TableCompany {
    GObject parent_instance;

    gchar *name;
    gchar *company_name;
    gchar *cnpj;
    gchar *legal_name;
    gchar *trade_name;
    gchar *phone;
    gchar *address_street;
    gchar *address_number;
    gchar *address_neighborhood;
    gchar *address_city;
    gchar *address_state;
    gchar *address_zip;
    gchar *email;
    gchar *opening_date;
};

G_DEFINE_TYPE(TableCompany, table_company, G_TYPE_OBJECT)

// Funções para setar as propriedades
static void table_company_set_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pspec) {
    TableCompany* self = TABLE_COMPANY(object);

    switch (property_id) {
        case PROP_NAME:
            g_free(self->name);
            self->name = g_value_dup_string(value);
            break;
        case PROP_COMPANY_NAME:
            g_free(self->company_name);
            self->company_name = g_value_dup_string(value);
            break;
        case PROP_CNPJ:
            g_free(self->cnpj);
            self->cnpj = g_value_dup_string(value);
            break;
        case PROP_LEGAL_NAME:
            g_free(self->legal_name);
            self->legal_name = g_value_dup_string(value);
            break;
        case PROP_TRADE_NAME:
            g_free(self->trade_name);
            self->trade_name = g_value_dup_string(value);
            break;
        case PROP_PHONE:
            g_free(self->phone);
            self->phone = g_value_dup_string(value);
            break;
        case PROP_ADDRESS_STREET:
            g_free(self->address_street);
            self->address_street = g_value_dup_string(value);
            break;
        case PROP_ADDRESS_NUMBER:
            g_free(self->address_number);
            self->address_number = g_value_dup_string(value);
            break;
        case PROP_ADDRESS_NEIGHBORHOOD:
            g_free(self->address_neighborhood);
            self->address_neighborhood = g_value_dup_string(value);
            break;
        case PROP_ADDRESS_CITY:
            g_free(self->address_city);
            self->address_city = g_value_dup_string(value);
            break;
        case PROP_ADDRESS_STATE:
            g_free(self->address_state);
            self->address_state = g_value_dup_string(value);
            break;
        case PROP_ADDRESS_ZIP:
            g_free(self->address_zip);
            self->address_zip = g_value_dup_string(value);
            break;
        case PROP_EMAIL:
            g_free(self->email);
            self->email = g_value_dup_string(value);
            break;
        case PROP_OPENING_DATE:
            g_free(self->opening_date);
            self->opening_date = g_value_dup_string(value);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

// Funções para obter as propriedades
static void table_company_get_property(GObject *object, guint property_id, GValue *value, GParamSpec *pspec) {
    TableCompany* self = TABLE_COMPANY(object);

    switch (property_id) {
        case PROP_NAME:
            g_value_set_string(value, self->name);
            break;
        case PROP_COMPANY_NAME:
            g_value_set_string(value, self->company_name);
            break;
        case PROP_CNPJ:
            g_value_set_string(value, self->cnpj);
            break;
        case PROP_LEGAL_NAME:
            g_value_set_string(value, self->legal_name);
            break;
        case PROP_TRADE_NAME:
            g_value_set_string(value, self->trade_name);
            break;
        case PROP_PHONE:
            g_value_set_string(value, self->phone);
            break;
        case PROP_ADDRESS_STREET:
            g_value_set_string(value, self->address_street);
            break;
        case PROP_ADDRESS_NUMBER:
            g_value_set_string(value, self->address_number);
            break;
        case PROP_ADDRESS_NEIGHBORHOOD:
            g_value_set_string(value, self->address_neighborhood);
            break;
        case PROP_ADDRESS_CITY:
            g_value_set_string(value, self->address_city);
            break;
        case PROP_ADDRESS_STATE:
            g_value_set_string(value, self->address_state);
            break;
        case PROP_ADDRESS_ZIP:
            g_value_set_string(value, self->address_zip);
            break;
        case PROP_EMAIL:
            g_value_set_string(value, self->email);
            break;
        case PROP_OPENING_DATE:
            g_value_set_string(value, self->opening_date);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

// Inicializa as propriedades do objeto
static void table_company_finalize(GObject *object) {
    TableCompany* self = TABLE_COMPANY(object);

    g_free(self->name);
    g_free(self->company_name);
    g_free(self->cnpj);
    g_free(self->legal_name);
    g_free(self->trade_name);
    g_free(self->phone);
    g_free(self->address_street);
    g_free(self->address_number);
    g_free(self->address_neighborhood);
    g_free(self->address_city);
    g_free(self->address_state);
    g_free(self->address_zip);
    g_free(self->email);
    g_free(self->opening_date);

    G_OBJECT_CLASS(table_company_parent_class)->finalize(object);
}

// Inicializa o objeto
static void table_company_init(TableCompany* self) {}

// Inicializa a classe
static void table_company_class_init(TableCompanyClass *klass) {
    GObjectClass *object_class = G_OBJECT_CLASS(klass);

    object_class->set_property = table_company_set_property;
    object_class->get_property = table_company_get_property;
    object_class->finalize = table_company_finalize;

    GParamFlags flags = G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS;

    properties[PROP_NAME] = g_param_spec_string("name", "Name", "Name of the responsible person", NULL, flags);
    properties[PROP_COMPANY_NAME] = g_param_spec_string("company-name", "Company Name", "Name of the company", NULL, flags);
    properties[PROP_CNPJ] = g_param_spec_string("cnpj", "CNPJ", "Company CNPJ", NULL, flags);
    properties[PROP_LEGAL_NAME] = g_param_spec_string("legal-name", "Legal Name", "Legal name of the company", NULL, flags);
    properties[PROP_TRADE_NAME] = g_param_spec_string("trade-name", "Trade Name", "Trade name of the company", NULL, flags);
    properties[PROP_PHONE] = g_param_spec_string("phone", "Phone", "Phone number", NULL, flags);
    properties[PROP_ADDRESS_STREET] = g_param_spec_string("address-street", "Address Street", "Street address", NULL, flags);
    properties[PROP_ADDRESS_NUMBER] = g_param_spec_string("address-number", "Address Number", "Number of the address", NULL, flags);
    properties[PROP_ADDRESS_NEIGHBORHOOD] = g_param_spec_string("address-neighborhood", "Neighborhood", "Neighborhood of the address", NULL, flags);
    properties[PROP_ADDRESS_CITY] = g_param_spec_string("address-city", "City", "City of the address", NULL, flags);
    properties[PROP_ADDRESS_STATE] = g_param_spec_string("address-state", "State", "State of the address", NULL, flags);
    properties[PROP_ADDRESS_ZIP] = g_param_spec_string("address-zip", "ZIP Code", "ZIP code of the address", NULL, flags);
    properties[PROP_EMAIL] = g_param_spec_string("email", "Email", "Email address", NULL, flags);
    properties[PROP_OPENING_DATE] = g_param_spec_string("opening-date", "Opening Date", "Opening date of the company", NULL, flags);

    g_object_class_install_properties(object_class, N_PROPERTIES, properties);
}

// Cria um novo objeto Tablecompany
TableCompany* table_company_new(const gchar *name,
                              const gchar *company_name,
                              const gchar *cnpj,
                              const gchar *legal_name,
                              const gchar *trade_name,
                              const gchar *phone,
                              const gchar *address_street,
                              const gchar *address_number,
                              const gchar *address_neighborhood,
                              const gchar *address_city,
                              const gchar *address_state,
                              const gchar *address_zip,
                              const gchar *email,
                              const gchar *opening_date) {
    return g_object_new(TABLE_COMPANY_TYPE,
                        "name", name,
                        "company-name", company_name,
                        "cnpj", cnpj,
                        "legal-name", legal_name,
                        "trade-name", trade_name,
                        "phone", phone,
                        "address-street", address_street,
                        "address-number", address_number,
                        "address-neighborhood", address_neighborhood,
                        "address-city", address_city,
                        "address-state", address_state,
                        "address-zip", address_zip,
                        "email", email,
                        "opening-date", opening_date,
                        NULL
    );
}
