#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <string>
#define f(_t, _x, _y) (_y)
#define g(_t, _x, _y) (-4.0 * (_x))

const double _t0 = 0;
const double _x0 = 1;
const double _y0 = 2;
const double a = _t0;
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

// Return t_i
vector<double> get_ti(int n)
{
    double h = (b - a) / (n - 1);

    vector<double> ti(n);
    for (int i = 0; i < n; i++)
        ti[i] = _t0 + (double)i * h;

    return ti;
}

// Euler's solution
void task_1(int n)
{
    double h = (b - a) / (n - 1);

    vector<double> ti = get_ti(n), xi(n), yi(n);

    xi[0] = _x0;
    yi[0] = _y0;
    for (int i = 1; i < n; i++)
    {
        xi[i] = xi[i - 1] + h * f(ti[i - 1], xi[i - 1], yi[i - 1]);
        yi[i] = yi[i - 1] + h * g(ti[i - 1], xi[i - 1], yi[i - 1]);
    }

    print_array("ti", ti);
    print_array("Euler_xi", xi);
    print_array("Euler_yi", yi);
}

// Improved Euler's solution
void task_2(int n)
{
    double h = (b - a) / (n - 1);

    vector<double> ti = get_ti(n), xi(n), yi(n);

    xi[0] = _x0;
    yi[0] = _y0;
    for (int i = 1; i < n; i++)
    {
        double K_1xi = f(ti[i - 1], xi[i - 1], yi[i - 1]);
        double K_1yi = g(ti[i - 1], xi[i - 1], yi[i - 1]);
        double K_2xi = f(ti[i], xi[i - 1] + h * K_1xi, yi[i - 1] + h * K_1yi);
        double K_2yi = g(ti[i], xi[i - 1] + h * K_1xi, yi[i - 1] + h * K_1yi);
        xi[i] = xi[i - 1] + h / 2 * (K_1xi + K_2xi);
        yi[i] = yi[i - 1] + h / 2 * (K_1yi + K_2yi);
    }

    print_array("ti", ti);
    print_array("iEuler_xi", xi);
    print_array("iEuler_yi", yi);
}

// Runge-Kutta solution
void task_3(int n)
{
    double h = (b - a) / (n - 1);

    vector<double> ti = get_ti(n), xi(n), yi(n);

    xi[0] = _x0;
    yi[0] = _y0;
    for (int i = 1; i < n; i++)
    {
        double K_1xi = f(ti[i - 1], xi[i - 1], yi[i - 1]);
        double K_1yi = g(ti[i - 1], xi[i - 1], yi[i - 1]);
        double K_2xi = f(ti[i - 1] + h / 2, xi[i - 1] + h / 2 * K_1xi, yi[i - 1] + h / 2 * K_1yi);
        double K_2yi = g(ti[i - 1] + h / 2, xi[i - 1] + h / 2 * K_1xi, yi[i - 1] + h / 2 * K_1yi);
        double K_3xi = f(ti[i - 1] + h / 2, xi[i - 1] + h / 2 * K_2xi, yi[i - 1] + h / 2 * K_2yi);
        double K_3yi = g(ti[i - 1] + h / 2, xi[i - 1] + h / 2 * K_2xi, yi[i - 1] + h / 2 * K_2yi);
        double K_4xi = f(ti[i - 1] + h, xi[i - 1] + h * K_3xi, yi[i - 1] + h * K_3yi);
        double K_4yi = g(ti[i - 1] + h, xi[i - 1] + h * K_3xi, yi[i - 1] + h * K_3yi);
        xi[i] = xi[i - 1] + h / 6 * (K_1xi + 2 * K_2xi + 2 * K_3xi + K_4xi);
        yi[i] = yi[i - 1] + h / 6 * (K_1yi + 2 * K_2yi + 2 * K_3yi + K_4yi);
    }

    print_array("ti", ti);
    print_array("RK4_xi", xi);
    print_array("RK4_yi", yi);
}

int main()
{
    cout << fixed << setprecision(5);

    int n;
    cin >> n;

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

    default:
        break;
    }

    return 0;
}