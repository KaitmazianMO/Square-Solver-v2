#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

/*!
    \brief ����������� ��������� ������ ������� ������,
           ������������ � ������� GetArgs().
*/
const size_t INPUT_STR_SIZE = 1000;
/*!
    \brief ������������ � �������� �������������
           �������� � ������� SolveSquare(),
           ������� � ���, ��� ����� ���������� �����.
*/
const int    INF            = -1;
/*!
    \brief ������������ � ������� isZero(),
           ������������� �����������, ��������
           ������� ����� ��������� ������ 0.
*/
const double PRECISION      = 1E-8;

/*!
   \brief ������� ����� ����������� ���������
          ���� ax^2 + bx + c = 0
          �  ���������� �� �����������.

    \param[in] a        - ��������� ����� x^2;
    \param[in] b        - ��������� ����� x;
    \param[in] �        - ��������� ����;
    \param[in] px1, px2 - ��������� �� ����������
                          ��� ������ ���������;

   \warning x1 � x2 �� ����� ��������������������,
            ���� ��������� �� ����� ������
*/

int SolveSquare        (double a, double b, double c,
                        double *px1, double *px2);

/*!
    \brief ��������� ����� �������� � ������� �
           ���������� �������� ���������� �� ���.

    ����������� ������, ��������� � �������,
    � ����� � ���������� �� �������� � ����������
    �� ����������.

    \param[in] pa, pb, pc - ��������� �� ����������,�
                            ������� ����� �������� ��������;

    \param[in] str_size   - ������������ ������ ������� ������,
                            �� ��������� ��������� ��������
                            INPUT_STR_SIZE;

    \return ���������� ��������� ����������.
*/

int GetArgs            (double *pa, double *pb, double *pc,
                        size_t str_size = INPUT_STR_SIZE);

/*!
    \brief ���������� ����� � 0, �������� �����������.

    \param[in] value     - �����, ������� ������������ � 0;
    \param[in] precision - �����������, �������� �������
                           ����� ������������ � 0, �� ���������
                           ��������� ������ PRECISION;
*/

bool isZero            (double value, double precison = PRECISION);

double GetDiscriminant (double a, double b, double c);

/*!
    \brief ����� ��� ������� SolveSquare().
*/
void TestSolveSquare();

int main()
    {
    //TestSolveSquare();

    int i = 0;

    printf ("\nSquare equation solver\n\n"
            "Equation: ax^2 + bx + c = 0\n"
            "Please, enter a, b, c coefficients: ");

    double a = NAN, b = NAN, c = NAN;
    while (GetArgs (&a, &b, &c) != 3)
        printf ("\nWrong input format!\n"
                "Plese, try again: ");

    double x1 = NAN, x2 = NAN;
    int nRoots = SolveSquare (a, b, c, &x1, &x2);

    switch (nRoots)
        {
        case 0:   printf ("\nNo roots\n");
                  break;

        case 1:   printf ("\nOnly 1 root: %g\n", x1);
                  break;

        case 2:   printf ("\n2 roots: %g %g\n", x1, x2);
                  break;

        case INF: printf ("\nAny number is a root\n");
                  break;

        default:  printf ("\nERROR! WRONG NUMBER OF ROOTS!\n");
                  return 1;
        }

    return 0;
    }


//-----------------------------------------------------------------------------

int GetArgs (double *pa, double *pb, double *pc,
              size_t str_size)
    {
    char input_str[str_size + 1];
    fgets (input_str, str_size, stdin);
    double empty_num; /* check for another nums */

    int nArgs = sscanf(input_str, "%lg%lg%lg%lg", pa, pb, pc, &empty_num);

    return nArgs;
    }

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

int SolveSquare (double a, double b, double c,
                 double *px1, double *px2)
    {

    assert(a != NAN);
    assert(b != NAN);
    assert(c != NAN);

    assert(px1  != px2);
    assert(px1  != NULL);
    assert(px2  != NULL);
    assert(*px1 != NAN);
    assert(*px2 != NAN);

    if (isZero(a))
        if (isZero(b))
            return (isZero(c)) ? INF : 0;

        else /* if(0 != b) */
            {
            *px1 = *px2 = (isZero(c)) ? 0 : -c / b;
            return 1;
            }

    else /* if(0 != a) */
        {
        double  discr = GetDiscriminant(a, b, c);

        if (isZero(discr))
            {

            if (isZero(-b / (2*a)))
                *px1 = *px2 = 0;

            else
                *px1 = *px2 = -b / (2*a);

            return 1;
            }

        if (!isZero(discr) && discr < 0)
            return 0;

        else /* if(!isZero(discr) && discr > 0) */
            {
            double sqrt_discr = sqrt(discr);
            *px1 = (-b + sqrt_discr) / (2*a);
            *px2 = (-b - sqrt_discr) / (2*a);
            return 2;
            }
        }

    }

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

bool isZero (double value, double precison)
    {
    return fabs(value) < precison;
    }

//-----------------------------------------------------------------------------

double GetDiscriminant (double a, double b, double c)
    {
    double discr = NAN;

    if (a < sqrt(PRECISION) ||
        b < sqrt(PRECISION) ||
        c < sqrt(PRECISION)   )
        {
        a /= PRECISION;
        b /= PRECISION;
        c /= PRECISION;

        discr = (b*b - 4*a*c) * PRECISION * PRECISION;
        }
    else
        discr = (b*b - 4*a*c);

    return discr;
    }

//-----------------------------------------------------------------------------

void TestSolveSquare()
    {

        {
        double x1, x2;
        int nRoots = SolveSquare(0, 0, 0, &x1, &x2);
        if(!isZero(nRoots - INF))
            printf("Test 1 BAD! isZero(nRoots - INF) = false\n");
        else
            printf("Test 1 OK\n");
        }

        {
        double x1, x2;
        int nRoots = SolveSquare(0, 0, 1, &x1, &x2);
        if(!isZero(nRoots - 0))
            printf("Test 2 BAD! isZero(nRoots - 0) = false\n");
        else
            printf("Test 2 OK\n");
        }

        {
        double x1, x2;
        int nRoots = SolveSquare(0, 1, 0, &x1, &x2);
        if(!isZero(nRoots - 1)) printf("Test 3 Bad! isZero(nRoots - 1)) = false\n");
        if(!isZero(x1))         printf("Test 3 Bad! isZero(x1) = false\n");
        if(!isZero(x2))         printf("Test 3 Bad! isZero(x2) = false\n");
        else
            printf("Test 3 OK\n");
        }

        {
        double x1, x2;
        int nRoots = SolveSquare(0, 1, 2, &x1, &x2);
        if(!isZero(nRoots - 1)) printf("Test 4 BAD! isZero(nRoots - 1) = false\n");
        if(!isZero(x1 + 2))     printf("Test 4 BAD! isZero(x1 + 2) = false\n");
        if(!isZero(x2 + 2))     printf("Test 4 BAD! isZero(x2 + 2) = false\n");
        else
            printf("Test 4 OK\n");
        }

        {
        double x1, x2;
        int nRoots = SolveSquare(1, 0, 0, &x1, &x2);
        if(!isZero(nRoots - 1)) printf("Test 5 BAD! isZero(nRoots - 1) = false\n");
        if(!isZero(x1))         printf("Test 5 BAD! isZero(x1) = false\n");
        if(!isZero(x2))         printf("Test 5 BAD! isZero(x2) = false\n");
        else
            printf("Test 5 OK\n");
        }

        {
        double x1, x2;
        int nRoots = SolveSquare(1, 2, 1, &x1, &x2);
        if(!isZero(nRoots - 1)) printf("Test 6 BAD! isZero(nRoots - 1) = false\n");
        if(!isZero(x1 + 1))     printf("Test 6 BAD! isZero(x1 + 1) = false\n");
        if(!isZero(x2 + 1))     printf("Test 6 BAD! isZero(x2 + 1) = false\n");
        else
            printf("Test 6 OK\n");
        }

        {
        double x1, x2;
        int nRoots = SolveSquare(1, 2, -1, &x1, &x2);
        if(!isZero(nRoots - 2))  printf("Test 7 BAD! isZero(nRoots - 2) = fasle\n");
        if(!isZero(x1 * x2 + 1)) printf("Test 7 BAD! isZero(x1 * x2 + 1) = fasle\n");
        if(!isZero(x1 + x2 + 2)) printf("Test 7 BAD! isZero(x1 + x2 + 2) = fasle\n");
        else
            printf("Test 7 OK\n");
        }

        {
        double x1, x2;
        int nRoots = SolveSquare(0.01, 2, -0.001, &x1, &x2);
        if(!isZero(nRoots - 2))
            printf("Test 8 BAD! isZero(nRoots - 2) = false\n");
        if(!isZero(x1 * x2 + 0.001 / 0.01))
            printf("Test 8 BAD! isZero(x1 * x2 + 0.001 / 0.01) = false\n");
        if(!isZero(x1 + x2 + 2 / 0.01))
            printf("Test 8 BAD! isZero(x1 + x2 + 2 / 0.01) = false\n");
        else
            printf("Test 8 OK\n");
        }

    }

//-----------------------------------------------------------------------------

