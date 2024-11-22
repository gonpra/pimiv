#pragma once
#include "table-company.h"

G_BEGIN_DECLS

typedef struct {
    TableCompany** content;
    gint size;
} TableCompanyArray;

G_END_DECLS
