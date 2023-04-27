#include <iostream>
#include <regex>
#include <vector>

using namespace std;

int main()
{
  pair<string, string> names;
  cin >> names.first >> names.second;

  int S;
  cin >> S;
  cin.ignore();

  string hexpoints;
  getline(cin, hexpoints);

  string totpoints;
  for (auto c : hexpoints)
  {
    switch (c)
    {
    case '0':
      totpoints += "0000";
      break;
    case '1':
      totpoints += "0001";
      break;
    case '2':
      totpoints += "0010";
      break;
    case '3':
      totpoints += "0011";
      break;
    case '4':
      totpoints += "0100";
      break;
    case '5':
      totpoints += "0101";
      break;
    case '6':
      totpoints += "0110";
      break;
    case '7':
      totpoints += "0111";
      break;
    case '8':
      totpoints += "1000";
      break;
    case '9':
      totpoints += "1001";
      break;
    case 'A':
      totpoints += "1010";
      break;
    case 'B':
      totpoints += "1011";
      break;
    case 'C':
      totpoints += "1100";
      break;
    case 'D':
      totpoints += "1101";
      break;
    case 'E':
      totpoints += "1110";
      break;
    case 'F':
      totpoints += "1111";
      break;
    }
  }

  reverse(begin(totpoints), end(totpoints));

  pair<vector<short>, vector<short>> games = {{0}, {0}};
  pair<short, short> points, sets;
  auto gain = 4;
  auto tie = false;
  string win;

  while (totpoints.length())
  {
    auto point = totpoints.back() - '0';
    totpoints.pop_back();
    if (point)
      ++points.second;
    else
      ++points.first;

    if (max(points.first, points.second) < gain)
      continue;

    if (abs(points.first - points.second) >= 2)
    {
      short *game = (points.first > points.second) ? &games.first.back() : &games.second.back();
      short *set = (points.first > points.second) ? &sets.first : &sets.second;
      string name = (points.first > points.second) ? names.first : names.second;

      points = {0, 0};

      if (++*game >= 6)
      {
        if ((games.first.back() == 6) && (games.second.back() == 6))
        {
          gain = (sets.first + sets.second < S - 1) ? 7 : 10, tie = true;
          continue;
        }

        if ((abs(games.first.back() - games.second.back()) >= 2) || (*game == 7))
        {
          ++*set;

          gain = 4, tie = false;

          if (max(sets.first, sets.second) == (S + 1) / 2)
          {
            win = name;
            break;
          }

          games.first.push_back(0);
          games.second.push_back(0);
          continue;
        }
      }

      continue;
    }

    if ((points.first == gain) && (points.second == gain))
      --points.first, --points.second;
  }

  for (size_t i = 0; i < 2; ++i)
  {
    auto name = i ? names.second : names.first;
    cout << name << string(15 - name.length(), '.');
    for (auto game : i ? games.second : games.first)
      cout << " " << game;
    auto point = i ? points.second : points.first;
    auto point_adv = i ? points.first : points.second;
    if (!win.length())
      cout << string(" | ") << (tie ? to_string(point) : ((max(points.first, points.second) == 4) ? string((point > point_adv) ? "AV" : "-") : to_string(vector<int>{0, 15, 30, 40}[point])));
    cout << endl;
  }

  cout << (win.length() ? (win + string(" wins")) : "Game in progress") << endl;
}
