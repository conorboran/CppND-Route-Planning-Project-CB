#include "node_comparer.h"

bool CompareNodeFVal(const RouteModel::Node *n1, const RouteModel::Node *n2)
{
    float f1 = n1->g_value + n1->h_value;
    float f2 = n2->g_value + n2->h_value;

    return f1 > f2;
}
