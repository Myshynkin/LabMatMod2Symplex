#include "glpk.h"
#include <iostream>

int main() {
    // ������������� ����� ������ ��������� ����������������
    glp_prob* lp = glp_create_prob();
    glp_set_prob_name(lp, "linear_program");

    // ��������� ����������� ����������� (������������)
    glp_set_obj_dir(lp, GLP_MAX);

    // ���������� ����� (�����������)
    glp_add_rows(lp, 3);
    glp_set_row_bnds(lp, 1, GLP_UP, 0.0, 38.0); // 2x1 + 11x2 <= 38
    glp_set_row_bnds(lp, 2, GLP_UP, 0.0, 7.0);  // x1 + x2 <= 7
    glp_set_row_bnds(lp, 3, GLP_UP, 0.0, 5.0);  // 4x1 - 5x2 <= 5

    // ���������� �������� (����������)
    glp_add_cols(lp, 2);
    glp_set_col_bnds(lp, 1, GLP_LO, 0.0, 0.0); // x1 >= 0
    glp_set_col_bnds(lp, 2, GLP_LO, 0.0, 0.0); // x2 >= 0
    glp_set_obj_coef(lp, 1, 1.0); // ����������� ������� ������� ��� x1
    glp_set_obj_coef(lp, 2, 1.0); // ����������� ������� ������� ��� x2

    // ���������� ������� ������������� �����������
    int ia[7], ja[7];
    double ar[7];
    ia[1] = 1, ja[1] = 1, ar[1] = 2.0;  // ����������� ��� x1 � ������ �����������
    ia[2] = 1, ja[2] = 2, ar[2] = 11.0; // ����������� ��� x2 � ������ �����������
    ia[3] = 2, ja[3] = 1, ar[3] = 1.0;  // ����������� ��� x1 �� ������ �����������
    ia[4] = 2, ja[4] = 2, ar[4] = 1.0;  // ����������� ��� x2 �� ������ �����������
    ia[5] = 3, ja[5] = 1, ar[5] = 4.0;  // ����������� ��� x1 � ������� �����������
    ia[6] = 3, ja[6] = 2, ar[6] = -5.0; // ����������� ��� x2 � ������� �����������
    glp_load_matrix(lp, 6, ia, ja, ar);

    // ��������� ��� ��������-������
    glp_smcp params;
    glp_init_smcp(&params);
    params.msg_lev = GLP_MSG_ON; // ����� ������ �������� ��������� � ������ ��������

    // ������ ��������-������
    glp_simplex(lp, &params);

    // ��������� � ����� ����������
    double z = glp_get_obj_val(lp);
    double x1 = glp_get_col_prim(lp, 1);
    double x2 = glp_get_col_prim(lp, 2);

    std::cout << "Z = " << z << "; X1 = " << x1 << "; X2 = " << x2 << ";" << std::endl;

    // ������������ ������
    glp_delete_prob(lp);

    return 0;
}
