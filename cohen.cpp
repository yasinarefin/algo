#include <bits/stdc++.h>
using namespace std;
typedef double T;

string format = "TDRL";

T xmin=-217, xmax=63, ymin=-173, ymax=57;

string outCode(T x, T y){
    map<char, int> code;
    code['T'] = code['D'] = code['R'] = code['L'] = '0';
    if(y > ymax) code['T'] = '1';
    if(y < ymin) code['D'] = '1';
    if(x > xmax) code['R'] = '1';
    if(x < xmin) code['L'] = '1';
    string c = "";
    for(auto i : format)
        c += code[i];
    return c;

}
void cohen(T x1, T y1, T x2, T y2){
    string opc = outCode(x1, y1);
    string opc2 = outCode(x2, y2);
    cout<<opc<<" "<<opc2<<endl;

    int ln, pos; cin>>ln>>pos;
    T x, y;

    if(pos == 0){
        x = x1 + (x2 - x1) *  (ymax - y1) / (y2 - y1); // intersection with top boundary
        y = ymax;
    }else if(pos == 1){
        x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);  // intersection with down boundary
        y = ymin;
    }else if(pos == 2){
        y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);  // intersection with right boundary
        x = xmax;
    }else{
        y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);  // intersection with left boundary
        x = xmin;
    }
    if(ln == 0){
        x1 = x;
        y1 = y;
    }else{
        x2 = x;
        y2 = y;
    }
    cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
    cohen(x1, y1, x2, y2);

}

int main()
{
    cohen(-478,-35,297,-541);

}
