#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int getvalue(string a ){
    string tab[8] =  {"U", "UR","R", "DR", "D", "DL", "L", "UL"} ; 
    for (int i =0 ; i<8 ; i++) {
        if(tab[i] == a )
            return i;
    }
    return -10000 ; 
}

int main()
{
    int w; // width of the building.
    int h; // height of the building.
    cin >> w >> h; cin.ignore();
    int n; // maximum number of turns before game over.
    cin >> n; cin.ignore();
    int x0;
    int y0;
    cin >> x0 >> y0; cin.ignore();
    int startx =0 ; 
    int starty = 0  ;
    // game loop
    while (1) {
        cerr<<"tour => "<<x0<<' ' <<y0 << endl; 
        string bomb_dir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> bomb_dir; cin.ignore();        
        switch (getvalue(bomb_dir)) {
        case 0: //U
            h=y0; 
            y0= starty+(h-starty)/2 ; 
        break ; 

        case 1 : //UR
         
            h=y0; 
            startx= x0; 
            y0= starty+(h-starty)/2; 
            x0= startx+(w-startx)/2; 
        break ; 

        case 2:  // R
            startx=x0;
            x0= startx+(w-startx)/2; 
        break ; 

        case 3:  //DR 
            starty=y0; 
            startx=x0;
            x0=(startx+ (w-startx)/2); 
            y0=(starty+ (h-starty)/2) ; 
        break ;

        case 4:  //D
            starty=y0; 
            y0=starty+(h-starty)/2 ; 
        break;

        case 5:  //DL
            starty=y0; 
            w = x0 ;
            y0=starty+ (h-starty)/2 ; 
            x0=startx+ (w-startx)/2; 
        break; 

        case 6 : //L
            w = x0 ;
            x0= startx+(w-startx)/2; 
        break; 

        case 7 : //UL
            
            h=y0; 
            w=x0; 
            y0= starty+(h-starty)/2; 
            x0= startx+(w-startx)/2;
        break ;  
        
        default: 
            cerr<<"error"<<endl;
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;


        // the location of the next window Batman should jump to.
        cerr<<" choice => "<<x0<<' ' <<y0 << endl; 
        cout << x0<<' '<<y0 << endl;
    }
}