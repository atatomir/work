#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>

using namespace std;

#define PI pair<double,double>
#define x first
#define y second
#define T 3.1415

#define N 1000 //! nr de pct
#define alfa 0.000001 //! precizia
#define lim 1000 //! ca sa generezi nr

PI P[N+11];
long i,n;
double cosAlfa,sinAlfa;
double xMin,xMax,yMin,yMax;
double last=0;

vector<char> sgn;
vector<double> diff;

double genCord(){
    return 1.00*(rand()%lim)*0.001*(rand()%lim);
}
void rotate(PI &point){
    PI tmp = point;
    point.x = tmp.x*cosAlfa - tmp.y*sinAlfa;
    point.y = tmp.x*sinAlfa + tmp.y*cosAlfa;
}

int main()
{
    srand(time(NULL));
    cosAlfa = cos(alfa);
    sinAlfa = sin(alfa);
    sgn.clear(); sgn.push_back('0');
    diff.clear(); diff.push_back(0);

    n = N;
    for(i=1;i<=n;i++){
        P[i].x = genCord();
        P[i].y = genCord();
    }

    for(double aa=0.00;2.00*aa<=T;aa+=alfa){
        xMin = yMin =  100000.00;
        xMax = yMax = -100000.00;

        for(i=1;i<=n;i++){
            xMin = min(xMin,P[i].x);
            xMax = max(xMax,P[i].x);

            yMin = min(yMin,P[i].y);
            yMax = max(yMax,P[i].y);
        }

        double Ans = 1.00*(xMax-xMin)*(yMax-yMin);
        printf("New area :  %.3lf %c\n",Ans,(last<Ans?'+':'-'));

        char cc = (last<Ans?'+':'-');
        if(cc!=sgn[sgn.size()-1]) {
            sgn.push_back(cc);
            diff.push_back(0);
        } else {
            diff[diff.size()-1] += Ans-last;
        }

        last = Ans;
        for(i=1;i<=n;i++) rotate(P[i]);
    }

    printf("-------\n The results are :\n");
    for(i=1;i<sgn.size();i++) printf("%c %.4lf\n",sgn[i],diff[i]);

    return 0;
}
