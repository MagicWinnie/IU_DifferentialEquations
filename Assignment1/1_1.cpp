#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <string>
#define y(_x, _x0, _y0) (sin(_x))
#define f(_x, _y) (cos(_x))

const double _x0 = 0;
const double _y0 = 0;
const double a = _x0;
const double b = M_PI;

using namespace std;

// Print given vector in specified format
void print_array(string name, vector<double> vec)
{
    cout << name << "=\n";
    for (size_t i = 0; i < vec.size(); i++)
    {
        cout << vec[i];
        if (i != vec.size() - 1)
            cout << " ";
    }
    cout << "\n";
}

// Return X_i
vector<double> get_xi(int n)
{
    double h = (b - a) / (n - 1);

    vector<double> xi(n);
    for (int i = 0; i < n; i++)
        xi[i] = _x0 + (double)i * h;

    return xi;
}

// Exact solution
void task_1(int n, bool print_solution = true)
{
    vector<double> xi = get_xi(n), yi(n);

    for (int i = 0; i < n; i++)
        yi[i] = y(xi[i], _x0, _y0);

    if (print_solution)
    {
        print_array("xi", xi);
        print_array("y(xi)", yi);
    }
}

// Euler's solution
vector<double> task_2(int n, bool print_solution = true)
{
    double h = (b - a) / (n - 1);

    vector<double> xi = get_xi(n), yi(n);

    yi[0] = _y0;
    for (int i = 1; i < n; i++)
        yi[i] = yi[i - 1] + h * f(xi[i - 1], yi[i - 1]);

    if (print_solution)
    {
        print_array("xi", xi);
        print_array("Euler_yi", yi);
    }

    return yi;
}

// Improved Euler's solution
vector<double> task_3(int n, bool print_solution = true)
{
    double h = (b - a) / (n - 1);

    vector<double> xi = get_xi(n), yi(n);

    yi[0] = _y0;
    for (int i = 1; i < n; i++)
    {
        double K_1i = f(xi[i - 1], yi[i - 1]);
        double K_2i = f(xi[i - 1] + h, y[i - 1] + h * K_1i);
        yi[i] = yi[i - 1] + h / 2 * (K_1i + K_2i);
    }

    if (print_solution)
    {
        print_array("xi", xi);
        print_array("iEuler_yi", yi);
    }

    return yi;
}

// Runge-Kutta solution
vector<double> task_4(int n, bool print_solution = true)
{
    double h = (b - a) / (n - 1);

    vector<double> xi = get_xi(n), yi(n);

    yi[0] = _y0;
    for (int i = 1; i < n; i++)
    {
        double K_1i = f(xi[i - 1], yi[i - 1]);
        double K_2i = f(xi[i - 1] + h / 2, y[i - 1] + h / 2 * K_1i);
        double K_3i = f(xi[i - 1] + h / 2, y[i - 1] + h / 2 * K_2i);
        double K_4i = f(xi[i - 1] + h, y[i - 1] + h * K_3i);
        yi[i] = yi[i - 1] + h / 6 * (K_1i + 2 * K_2i + 2 * K_3i + K_4i);
    }

    if (print_solution)
    {
        print_array("xi", xi);
        print_array("RK4_yi", yi);
    }

    return yi;
}

// Local errors of the Euler's solution
vector<double> task_5(int n, bool print_solution = true)
{
    vector<double> LE(n);
    vector<double> xi = get_xi(n), yi = task_2(n, false);
    for (int i = 0; i < n; i++)
        LE[i] = abs(yi[i] - y(xi[i], _x0, _y0));

    if (print_solution)
    {
        print_array("xi", xi);
        print_array("Euler_LE(xi)", LE);
    }

    return LE;
}

// Local errors of the improved Euler's solution
void task_6(int n, bool print_solution = true)
{
    vector<double> LE(n);
    vector<double> xi = get_xi(n), yi = task_3(n, false);
    for (int i = 0; i < n; i++)
        LE[i] = abs(yi[i] - y(xi[i], _x0, _y0));

    if (print_solution)
    {
        print_array("xi", xi);
        print_array("iEuler_LE(xi)", LE);
    }
}

// Local errors of the Runge-Kutta solution
void task_7(int n, bool print_solution = true)
{
    vector<double> LE(n);
    vector<double> xi = get_xi(n), yi = task_4(n, false);
    for (int i = 0; i < n; i++)
        LE[i] = abs(yi[i] - y(xi[i], _x0, _y0));

    if (print_solution)
    {
        print_array("xi", xi);
        print_array("RK4_LE(xi)", LE);
    }
}

// Blobal errors of the Euler's solution
void task_8(int n1, int n2)
{
    vector<double> GE(n2 - n1 + 1);
    vector<double> ni(n2 - n1 + 1);

    for (int n = n1; n <= n2; n++)
    {
        ni[n - n1] = n;

        vector<double> xi = get_xi(n);
        vector<double> yi = task_2(n, false);
        for (int i = 0; i <= n - 1; i++)
        {
            GE[n - n1] = max(GE[n - n1], abs(yi[i] - y(xi[i], _x0, _y0)));
        }
    }

    cout << defaultfloat;
    print_array("ni", ni);
    cout << fixed;
    print_array("Euler_GE(n)", GE);
}

// Blobal errors of the improved Euler's solution
void task_9(int n1, int n2)
{
    vector<double> GE(n2 - n1 + 1);
    vector<double> ni(n2 - n1 + 1);

    for (int n = n1; n <= n2; n++)
    {
        ni[n - n1] = n;

        vector<double> xi = get_xi(n);
        vector<double> yi = task_3(n, false);
        for (int i = 0; i <= n - 1; i++)
        {
            GE[n - n1] = max(GE[n - n1], abs(yi[i] - y(xi[i], _x0, _y0)));
        }
    }

    cout << defaultfloat;
    print_array("ni", ni);
    cout << fixed;
    print_array("iEuler_GE(n)", GE);
}

// Blobal errors of the Runge-Kutta solution
void task_10(int n1, int n2)
{
    vector<double> GE(n2 - n1 + 1);
    vector<double> ni(n2 - n1 + 1);

    for (int n = n1; n <= n2; n++)
    {
        ni[n - n1] = n;

        vector<double> xi = get_xi(n);
        vector<double> yi = task_4(n, false);
        for (int i = 0; i <= n - 1; i++)
        {
            GE[n - n1] = max(GE[n - n1], abs(yi[i] - y(xi[i], _x0, _y0)));
        }
    }

    cout << defaultfloat;
    print_array("ni", ni);
    cout << fixed;
    print_array("RK4_GE(n)", GE);
}

int main()
{
    cout << fixed << setprecision(5);

    int n, n1, n2;
    cin >> n >> n1 >> n2;

    int task;
    cin >> task;

    switch (task)
    {
    case 1:
        task_1(n);
        break;
    case 2:
        task_2(n);
        break;
    case 3:
        task_3(n);
        break;
    case 4:
        task_4(n);
        break;
    case 5:
        task_5(n);
        break;
    case 6:
        task_6(n);
        break;
    case 7:
        task_7(n);
        break;
    case 8:
        task_8(n1, n2);
        break;
    case 9:
        task_9(n1, n2);
        break;
    case 10:
        task_10(n1, n2);
        break;

    default:
        break;
    }

    return 0;
}