#include <iostream>
#include <math.h>
#include <stdexcept>
using namespace std;

double checkTheVariableA( double a){

    cin >> a;

    if(cin.fail()){
        throw invalid_argument ("Malformed user input"); 
    }
    else if(a == 0){
        throw runtime_error("a must not be zero");
    }
    return a;
}

double checkTheVariableB( double b){

    cin >> b;

    if(cin.fail()){
        throw invalid_argument ("Malformed user input");
    }
    return b;
}

double checkTheVariableC( double c){

    cin >> c;

    if(cin.fail()){
        throw invalid_argument ("Malformed user input");
    }
    return c;
}

double Discriminant (double a, double b, double c){

    return (b * b) - (4 * a * c);
}

void SolveEquation (double Dis, double a, double b, double c, double &x1, double &x2){

    if(Dis > 0){
        x1 = (-b + sqrt(Dis)) / (2 * a);
        x2 = (-b - sqrt(Dis)) / (2 * a);
    }
    else if(Dis == 0){
            x1 = -b / (2 * a);
        }
}

    
int main()
{
    try{

        double a, b, c, x1, x2;
        cout<<"Please enter the values of a, b, and c: "<<endl;

        a = checkTheVariableA(a);
        b = checkTheVariableB(b);
        c = checkTheVariableC(c);

        double D = Discriminant(a, b, c);
        SolveEquation(D, a, b, c, x1, x2);

        if(D > 0){
            cout << "There are 2 solutions." << endl;
            cout << "The solutions are:" << x1 << " and " << x2 << endl;
        }
        else if(D == 0){
            cout << "There is 1 solution." << endl;
            cout << "The solution is:" << x1 << endl;
            }
        else if (D < 0){
            cout << "There is no solution." << endl;
            }
    }

    catch (runtime_error& excpt) {
         cout << "An error occurred: " << excpt.what() << endl;
      }

    catch (invalid_argument& excpt) {
         cout << "An error occurred: " << excpt.what() << endl;
      }

    return 0;
}
