#include <iostream>
#include <math.h>
using namespace std;


double Discriminant(double a, double b, double c){
    return (b * b) - (4 * a * c);
}

void SolveEquation(double Dis, double a, double b, double c){

    double x1, x2;

    if (Dis > 0){
        cout << "There are 2 solutions." << endl;
        x1 = (-b + sqrt(Dis)) / (2 * a);
        x2 = (-b - sqrt(Dis)) / (2 * a);
        cout << "The solutions are:" << x1 << " and " << x2 << endl;
    }
    else if (Dis == 0){
        cout << "There is 1 solution." << endl;
        x1 = -b / (2 * a);
        cout << "The solution is:" << x1 << endl;
    }
    else if (Dis < 0){
        cout << "There is no solution." << endl;
    }
}

int main(){

        double a, b, c, x1, x2;
        
        cout << "Please enter the values of a, b, and c: " << endl;
        cin >> a;
        cin >> b;
        cin >> c; 

        double Discr = Discriminant(a, b, c);
        SolveEquation(Discr, a, b, c);

    return 0;
}
