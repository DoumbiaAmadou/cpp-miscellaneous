#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
string player_1(15, '.'), player_2(15, '.');
string name1, name2;
bool finish = false;
bool tieBreak = false;
string winners;
int score1, score2,
    point1, point2;
int n;
vector<int> valiateSetP1;
vector<int> valiateSetP2;
void checkWin(int isP1score);

void checkIfWinSet(bool isP1score)
{
  if (tieBreak || (score1 >= 6 || score2 >= 6) && (abs(score1 - score2) > 1))
  {
    valiateSetP1.push_back(score1);
    valiateSetP2.push_back(score2);
    score1 = score2 = 0;
    if (tieBreak)
      tieBreak = false;
    checkWin(isP1score);
  }
}
string displayValidateSet(const vector<int> validsp)
{
  string s = "";
  for_each(validsp.begin(), validsp.end(), [&s](const int i)
           { s += " " + to_string(i); });
  return s;
}
string displayPoint(int p1, int p2)
{
  if (tieBreak)
    return to_string(p1);

  switch (p1)
  {
  case 0:

    return "0";
  case 1:
    return "15";
  case 2:
    return "30";
  case 3:
    return "40";
  default:
    if (p1 > p2)
      return "AV";
    else
      return "-";
  }
}
void score(bool isP1score)
{
  cerr << "   ===> isP1score " << !isP1score << endl;
  /*
      reel display  0,15, 30, 40. WIN?ADV
      point         0, 1,  2,  3. 4.
  */
  int *pscore, *ppoint, *pAdversScore, *pAdversPoint;
  if (isP1score)
  {
    pscore = &score1;
    ppoint = &point1;

    pAdversScore = &score2;
    pAdversPoint = &point2;
  }
  else
  {
    pscore = &score2;
    ppoint = &point2;

    pAdversScore = &score1;
    pAdversPoint = &point1;
  }

  int limit = 4;
  // handle TIE break
  if (score1 == score2 & score1 == 6)
  {
    limit = 7;
    if (!tieBreak)
      tieBreak = true;
    if (valiateSetP1.size() == n - 1)
      limit = 10;
  }
  // add point =>
  if (*ppoint < (limit - 1) || *ppoint <= *pAdversPoint)
    (*ppoint)++;

  else
  {
    // win game
    (*pscore)++;
    *ppoint = 0;
    *pAdversPoint = 0;
    checkIfWinSet(isP1score);
  }

  cerr << player_1 << displayValidateSet(valiateSetP1) << " " << score1 << " | " << displayPoint(point1, point2) << endl;
  cerr << player_2 << displayValidateSet(valiateSetP2) << " " << score2 << " | " << displayPoint(point2, point1) << endl;
  cerr << endl;
}
void checkWin(int isP1score)
{
  int p1nbSet = 0;
  int p2nbSet = 0;

  for (int i = 0; i < valiateSetP1.size(); i++)
  {
    valiateSetP1[i] > valiateSetP2[i] ? p1nbSet++ : p2nbSet++;
  }
  if (p1nbSet > (n / 2.0))
  {
    finish = true;
    winners = name1;
  }
  if (p2nbSet > (n / 2.0))
  {
    finish = true;
    winners = name2;
  }
};

int main()
{
  string names;
  score1 = score2 = point1 = point2 = 0;

  getline(cin, names);

  cin >> n;
  cin.ignore();
  string points;
  getline(cin, points);

  int delimererPos = names.find(' ');
  name1 = names.substr(0, delimererPos);
  player_1 = name1 + string(15 - delimererPos, '.');
  int len = names.length();
  if ((len - delimererPos) < 16)
  {
    name2 = names.substr(delimererPos + 1, names.length());
    player_2 = name2 + string(15 - (names.length() - delimererPos - 1), '.');
  }
  else
  {
    player_2 = name2.substr(0, 15);
  }
  stringstream sStream;
  sStream << hex << points;
  int nPoints;
  cerr << " point  " << points << endl
       << "nombre de set " << n << endl;
  cerr << player_1 << " " << score1 << " | " << point1 << endl;
  cerr << player_2 << " " << score2 << " | " << point2 << endl
       << endl;

  cerr << "<==== STRAT ITERATION ===> " << endl;
  while (sStream >> nPoints && !finish)
  {
    // cerr<<" tour "<<" " <<nPoints<<" ";
    for (int i = 7; i >= 0 && !finish; i--)
    {
      if ((nPoints >> i) & 1)
      {
        cerr << " ==>  1" << endl;
        score(false);
      }
      else
      {
        cerr << " ==> 0" << endl;
        ;
        score(true);
      }
    }
  }
  cerr << "resultat final" << endl;

  // Write an answer using cout. DON'T FORGET THE "<< endl"
  // To debug: cerr << "Debug messages..." << endl;
  // cerr << player_1<<" "<<score1<<" | "<<point1<< endl;
  // cerr << player_2<<" "<<score2<<" | "<<point2<< endl;
  cout << player_1 << displayValidateSet(valiateSetP1);

  if (!finish)
    cout << " " << score1 << " | " << displayPoint(point1, point2);

  cout << endl;
  cout << player_2 << displayValidateSet(valiateSetP2);
  if (!finish)
    cout << " " << score2 << " | " << displayPoint(point2, point1);

  cout << endl;

  if (!finish)
    cout << "Game in progress" << endl;
  else
    cout << winners << " "
         << "wins" << endl;
}