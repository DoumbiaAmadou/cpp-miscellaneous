#include <iostream>
#include <algorithm>
#include <sstream>
#include <bitset>
using namespace std;
void play(string &s, vector<int> &P, int m = 4)
{
  P[0] = 0;
  P[1] = 0;
  while (size(s) > 0)
  {
    int p = s[0] - '0';
    s.erase(0, 1);
    P[p]++;
    if (P[p] >= m)
    {
      if (abs(P[0] - P[1]) > 1)
        break;
      else if (P[0] == m && P[1] == m)
      {
        P[0]--;
        P[1]--;
      }
    }
  }
}
int main()
{
  string s, x, PP[2], a[] = {"0", "15", "30", "40", "AV", "-"};
  int N, tt = 0, t = 0, m = 4, w = -1;
  vector<int> P(2, 0), S(2, 0);
  vector<vector<int>> G(2, vector<int>(1, 0));
  cin >> PP[0] >> PP[1] >> N;
  while (cin >> x)
  {
    stringstream ss;
    ss << hex << x;
    ss >> tt;
    bitset<8> b(tt);
    s += b.to_string();
  }
  while (size(s))
  {
    play(s, P, m);
    if ((P[0] >= m || P[1] >= m) && abs(P[0] - P[1]) > 1)
    {
      bool ind = P[1] > P[0];
      G[ind].back()++;
      P[0] = 0;
      P[1] = 0;
      if (G[ind].back() >= 6)
      {
        if (abs(G[1].back() - G[0].back()) > 1 || G[ind].back() == 7)
        {
          S[ind]++;
          t = 0;
          m = 4;
          int ms = max(S[0], S[1]);
          if (ms == (N + 1) / 2)
            w = ind, s = "";
          else
          {
            G[0].push_back(0);
            G[1].push_back(0);
          }
        }
        else if (G[0].back() == 6 && G[1].back() == 6)
        {
          t = 1;
          if (S[0] + S[1] == N - 1)
            m = 10;
          else
            m = 7;
        }
      }
    }
  }
  for (int i = 0; i < 2; i++)
  {
    string q = PP[i];
    while (size(q) < 15)
      q += ".";
    cout << q;
    for (int x : G[i])
      cout << " " << x;
    if (w < 0)
    {
      if (t)
        cout << " | " << P[i] << endl;
      else
        cout << " | " << a[P[i] + 2 * (P[1 - i] == 4)] << endl;
    }
    else
      cout << endl;
  }
  if (w == -1)
    cout << "Game in progress";
  else
    cout << PP[w] << " wins";
}