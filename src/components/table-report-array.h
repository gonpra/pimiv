#pragma once
#include "table-report.h"

G_BEGIN_DECLS

typedef struct {
    TableReport** content;
    gint size;
} TableReportArray;

G_END_DECLS
