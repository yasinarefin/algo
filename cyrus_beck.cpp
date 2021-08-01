#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double T;
struct Point{
    T x, y;
    Point(T x = 0, T y = 0){
        this->x = x;
        this->y = y;
    }
    Point operator+(Point p){ return Point(x+p.x, y+p.y); }

    Point operator-(Point p){ return Point(x-p.x, y-p.y); }

    Point operator*(T a){ return Point(x*a, y*a); }

    Point operator/(T a){ return Point(x/a, y/a); }

    T len(){ return sqrt(x*x+y*y); }
};

Point nVec(Point v){
    return {-v.y, v.x};
}

struct Line{
    double x1, y1, x2, y2;
    Point para(double t){
        Point ret;
        ret.x = x1 + t * (x2 -x1);
        ret.y = y1 + t * (y2 - y1);
        return ret;
    }
    Point pl(){
        return Point(x1, y1);
    }
    Point pr(){
        return Point(x2, y2);
    }
    Point lineV(){
        return Point(x2, y2) - Point(x1, y1);
    }
};

double dot(Point a, Point b){
    return a.x * b.x + a.y * b.y;
}

double tval(Point norm, Point pe, Point p0, Point p1){
    T nu = dot(norm, (p0 - pe));
    T de = dot(norm * -1, (p1 - p0));
    return nu / de;
}


void trivialAlgo(){

    double xmin, xmax, ymin, ymax; cin>>xmin>>xmax>>ymin>>ymax;
    double x1, y1, x2, y2; cin>>x1>>y1>>x2>>y2; // line endpoints
    Line l{x1, y1, x2, y2};
    Point le{x1 ,y1}; // left end point of line
    Point re{x2, y2}; // right end point of line
    Point lv =l.lineV(); // line vector

    vector<double> ts; // l, r, b, u
    ts.push_back((xmin - x1) / (x2 - x1));
    ts.push_back((xmax - x1) / (x2 - x1));
    ts.push_back((ymin - y1) / (y2 - y1));
    ts.push_back((ymax - y1) / (y2 - y1));


    vector<Point> norms; // l, r, b, u
    norms.push_back({-1, 0});
    norms.push_back({1, 0});
    norms.push_back({0, -1});
    norms.push_back({0, 1});

    double te = 0, tl = 1;
    int idx = 0;
    for(auto i : norms){
        double d = dot(lv, i);
        if(d < 0){

            te = max(te, ts[idx]);
            cout<<"Entering "<<ts[idx]<<" "<<te<<" "<<tl<<endl;
        }else{

            tl = min(tl, ts[idx]);
            cout<<"Leaving "<<ts[idx]<<" "<<te<<" "<<tl<<endl;
        }
        idx++;
    }
    if(te > tl){
        cout<<"Outside clipping window\n";
    }else{
        Point a = l.para(te);
        Point b = l.para(tl);
        cout<<a.x<<" "<<a.y<<endl;
        cout<<b.x<<" "<<b.y<<endl;
    }

}

void completeAlgo(){
    int n; cin>>n; // number of vectors //polygon stuffs
    vector<Point> points; // enter points counterclockwise
    for(int x=0;x<n;x++){
        double a, b; cin>>a>>b;
        points.push_back({a, b});
    }
    vector<Point> vecs;
    for(int x=0;x<n;x++){
        vecs.push_back(points[(x+1) % n] - points[x]);
    }

    double x1, y1, x2, y2; cin>>x1>>y1>>x2>>y2; //endpoints of points
    Line l{x1, y1, x2, y2};
    Point lv =l.lineV(); // line vector

    vector<Point> norms;

    for(auto i : vecs){ // for polygons
        norms.push_back(nVec(i));
       // cout<<nVec(i).x<<" "<<nVec(i).y<<endl;
    }



    double te = 0, tl = 1;
    int idx = 0;
    for(auto i : norms){
        double d = dot(lv, i); // Ni * D
        T t = tval(i, points[idx], l.pl(), l.pr());

        if(d == 0) {cout<<"Parallel to line\n"; continue;}
        if(d > 0){
            te = max(te, t);
            cout<<"Entering "<<t<<" "<<te<<" "<<tl<<endl;
        }else{
            tl = min(tl, t);
            cout<<"Leaving "<<t<<" "<<te<<" "<<tl<<endl;
        }
        idx++;

    }
    if(te > tl){
        cout<<"Outside clipping window\n";
    }else{
        Point a = l.para(te);
        Point b = l.para(tl);
        cout<<a.x<<" "<<a.y<<endl;
        cout<<b.x<<" "<<b.y<<endl;
    }
}
int main(){
    trivialAlgo();


}
