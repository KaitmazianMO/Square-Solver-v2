#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

/*!
    \brief Максимально возможный размер входной строки,
           используется в функции GetArgs().
*/
const size_t INPUT_STR_SIZE = 1000;
/*!
    \brief Используется в качестве возвращаемого
           значения в функции SolveSquare(),
           говорит о том, что коней бесконечно много.
*/
const int    INF            = -1;
/*!
    \brief Используется в функции isZero(),
           устанавливает погрешность, согласно
           которой число считается равным 0.
*/
const double PRECISION      = 1E-8;

/*!
   \brief Находит корни квадратного уравнения
          вида ax^2 + bx + c = 0
          и  возвращает их количествою.

    \param[in] a        - коэфицент перед x^2;
    \param[in] b        - коэфицент перед x;
    \param[in] с        - свободный член;
    \param[in] px1, px2 - указатели на переменные
                          для корней уравнения;

   \warning x1 и x2 не будут проинициализированны,
            если уравнение не имеет корней
*/

int SolveSquare        (double a, double b, double c,
                        double *px1, double *px2);

/*!
    \brief Записыает числа введеные в консоль в
           переменные согласно указателям на них.

    Преобразует строку, введенную в консоль,
    в числа и записывает их значения в переменные
    по указателям.

    \param[in] pa, pb, pc - указатели на переменные,в
                            которые нужно записать занчения;

    \param[in] str_size   - маскимальный размер входной строки,
                            по умолчанию принимает значение
                            INPUT_STR_SIZE;

    \return Количество считанных аргументов.
*/

int GetArgs            (double *pa, double *pb, double *pc,
                        size_t str_size = INPUT_STR_SIZE);

/*!
    \brief Сравнивает число с 0, согласно погрешности.

    \param[in] value     - число, которое сравнивается с 0;
    \param[in] precision - погрешность, согласно которой
                           число сравнивается с 0, по умолчанию
                           считается равной PRECISION;
*/

bool isZero            (double value, double precison = PRECISION);

double GetDiscriminant (double a, double b, double c);

/*!
    \brief Тесты для функции SolveSquare().
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
    int nRoots = SolveSquare (1e-20, 2*1e-20, 1e-20, &x1, &x2);

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

    int nArgs = sscanf (input_str, "%lg%lg%lg%lg", pa, pb, pc,
                                                   &empty_num);

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
    
        {
        double x1, x2;
        int nRoots = SolveSquare(PRECISION, 2*PRECISION, PRECISION,
                                 &x1, &x2);
        if(!isZero(nRoots - 1))
            printf("Test 9 BAD! isZero(nRoots - 1) = false\n");
        if(!isZero(x1 + 1))
            printf("Test 9 BAD! !isZero(x1 + 1) = false\n");
        else
            printf("Test 9 OK\n");
        }

    }

//-----------------------------------------------------------------------------

