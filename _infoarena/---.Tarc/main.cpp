#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

class Buffer{
    public:
        long maxBuf,pos,sign;
        vector<char> Buff;

        Buffer(char fileName[],long buffSize){
            freopen(fileName,"r",stdin);
            maxBuf = buffSize; Buff.resize(maxBuf);
            reFill();
        }

        Buffer& operator>>(long &dest){
            while(!isDigit(Buff[pos]) && Buff[pos] != '-'){
                pos++;
                if(pos == maxBuf) reFill();
            }
            dest = 0;
            if(Buff[pos]=='-'){
                sign = -1;
                if(++pos == maxBuf) reFill();
            } else sign = 1;
            while(isDigit(Buff[pos])){
                dest = dest*10 + Buff[pos++] - '0';
                if(pos == maxBuf) reFill();
            }
            dest *= sign;
            return *this;
        }

    private:
        bool isDigit(char c){
            return c >= '0' && c <= '9' ;
        }
        void reFill(){
            fread(&Buff[0],1,maxBuf,stdin); pos = 0;
        }
};

#define maxN 100011
#define eps 0.001

const double PI  =3.141592653589793238463;

long t,n,i;
long pct[maxN][2];
double xMin,yMin,xMax,yMax;
bool up;

double coss,sinn;

bool eq(double x){
    return x>=-eps && x<=eps;
}

inline double rotateX(double x,double y){
    return 1.00*x*coss-1.00*y*sinn;
}
inline double rotateY(double x,double y){
    return 1.00*x*sinn+1.00*y*coss;
}

double getVal(double alfa){
    xMin = yMin = 1000000000.00;
    xMax = yMax = -1000000000.00;

    coss = cos(alfa); sinn = sin(alfa);

    double xx,yy;
    for(long i=1;i<=n;i++){
        xx = rotateX(pct[i][0],pct[i][1]);
        yy = rotateY(pct[i][0],pct[i][1]);

        xMin = min(xMin,xx); xMax = max(xMax,xx);
        yMin = min(yMin,yy); yMax = max(yMax,yy);
    }

    return (xMax-xMin)-(yMax-yMin);
}

void writeSol(double alfa,double x1,double y1,double x2,double y2){
    alfa = -alfa;
    coss = cos(alfa); sinn = sin(alfa);
    printf("%.6lf %.6lf\n",rotateX(x1,y1),rotateY(x1,y1));
    printf("%.6lf %.6lf\n",rotateX(x1,y2),rotateY(x1,y2));
    printf("%.6lf %.6lf\n",rotateX(x2,y1),rotateY(x2,y1));
    printf("%.6lf %.6lf\n",rotateX(x2,y2),rotateY(x2,y2));
}


int main()
{
    Buffer cin("tarc.in",1024*1024);
    freopen("tarc.out","w",stdout);

    for(cin>>t;t;t--){
        cin >> n;
        for(i=1;i<=n;i++) cin >> pct[i][0] >> pct[i][1];

        double v2 = getVal(PI/2);
        double v1 = getVal(0);
        up = (v1 < v2);

        if(eq(v1)){
            writeSol(0,xMin,yMin,xMax,yMax);
            continue;
        }

        double boI=0,boJ=PI/2,m;
        bool found = false;
        while(!found){
            m = (boI+boJ)/2;
            v1 = getVal(m);
            if(eq(v1)){
                found = true;
                writeSol(m,xMin,yMin,xMax,yMax);
                break;
            }
            if((v1>0&&up)||(v1<0&&!up))
                boJ = m;
            else
                boI = m;
        }
    }

    return 0;
}
