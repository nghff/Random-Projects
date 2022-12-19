// 4

//#include <iostream>
//#include <vector>
//#include <string>
//using namespace std;
//
//vector<int> order;
//vector<vector<vector<int>>> boards, marked;
//int ii, jj;
//bool found(int board, int curr)
//{
//	for (int i = 0; i < 5; i++)
//	{
//		for (int j = 0; j < 5; j++)
//		{
//			if (boards[board][i][j] == curr)
//			{
//				ii = i; jj = j;
//				marked[board][i][j] = true;
//				return true;
//			}
//		}
//	}
//	return false;
//}
//
//bool checkWin(int boardID, int ii, int jj)
//{
//	bool win = true;
//	for (int j = 0; j < 5; j++)
//	{
//		if (!marked[boardID][ii][j])
//		{
//			win = false;
//			break;
//		}
//	}
//	if (win) return true;
//
//	for (int i = 0; i < 5; i++)
//	{
//		if (!marked[boardID][i][jj])
//		{
//			return false;
//		}
//	}
//	return true;
//}
//
//int getSum(int boardID)
//{
//	int ans = 0;
//	for (int i = 0; i < 5; i++)
//	{
//		for (int j = 0; j < 5; j++)
//		{
//			if (!marked[boardID][i][j])
//			{
//				ans+=boards[boardID][i][j];
//			}
//		}
//	}
//	return ans;
//}
//
//int main()
//{
//	while (1)
//	{
//		string numberS;
//		char in;
//		while (1)
//		{
//			cin >> in;
//			if (in == ',' || in == '.') break;
//			numberS += in;
//		}
//		if (in == '.') break;
//		order.push_back(stoi(numberS));
//	}
//	while (1)
//	{
//		vector<vector<int>> board(5, vector<int>(5));
//		bool stop = false;
//		for (int i = 0; i < 5; i++)
//		{
//			if (stop) break;
//			for (int j = 0; j < 5; j++)
//			{
//				cin >> board[i][j];
//				if (board[i][j] == -1)
//				{
//					stop = true;
//					break;
//				}
//			}
//		}
//		if (stop) break;
//		boards.push_back(board);
//	}
//	marked.resize(boards.size(), vector<vector<int>>(5, vector<int>(5)));
//	vector<bool> won(marked.size());
//	int ans;
//	for (int id = 0; id < order.size(); id++)
//	{
//		int currNum = order[id];
//		for (int boardID = 0; boardID < boards.size(); boardID++)
//		{
//			if (won[boardID]) continue;
//			if (found(boardID, currNum))
//			{
//				if (checkWin(boardID, ii, jj))
//				{
//					won[boardID] = true;
//					int sum = getSum(boardID);
//					ans = sum * currNum;
//				}
//			}
//		}
//	}
//	cout << ans;
//}

//5

//#include <iostream>
//#include <vector>
//#include <string>
//
//using namespace std;
//
//int main()
//{
//	vector<vector<int>> grid(1000, vector<int>(1000));
//	while (1)
//	{
//		int x1, x2, y1, y2; char t;
//		cin >> x1 
//			>> t 
//			>> y1 
//			>> t 
//			>> t 
//			>> x2
//			>> t 
//			>> y2;
//		if (y2 == -1) break;
//		if (x1 != x2 && y1 != y2)
//		{
//			if (x1 <= x2 && y1 <= y2)
//				for (int i = x1; i <= x2; i++)
//				{
//					grid[i][y1 + i - x1]++;
//				}
//			if (x1 > x2 && y1 > y2)
//				for (int i = x2; i <= x1; i++)
//				{
//					grid[i][y2 + i - x2]++;
//				}
//			if (x1 < x2 && y1 > y2)
//				for (int i = x1; i <= x2; i++)
//				{
//					grid[i][y1 - (i - x1)]++;
//				}
//			if (x1 > x2 && y1 < y2)
//				for (int i = x2; i <= x1; i++)
//				{
//					grid[i][y2 - (i - x2)]++;
//				}
//		}
//		if (y1 == y2)
//		{
//			if (x1 <= x2)
//				for (int i = x1; i <= x2; i++)
//					grid[i][y1]++;
//			else
//				for (int i = x2; i <= x1; i++)
//					grid[i][y1]++;
//		}
//		else if (x1 == x2)
//		{
//			if(y1 <= y2)
//				for (int i = y1; i <= y2; i++)
//				grid[x1][i]++;
//			else
//				for (int i = y2; i <= y1; i++)
//				grid[x1][i]++;
//		}
//	}
//	for (int i = 0; i < 10; i++)
//	{
//		for (int j = 0; j < 10; j++)
//		{
//			cout << grid[j][i];
//		}
//		cout << '\n';
//	}
//	int ans = 0;
//	for(int i = 0; i < 1000; i++)
//		for (int j = 0; j < 1000; j++)
//		{
//			if (grid[i][j] > 1) ans++;
//		}
//	cout << ans;
//}
//
//
//

//6

//#include <iostream>
//#include <vector>
//using namespace std;
//
//#define ll long long
//
//int main()
//{
//	vector<ll> count(9); char c;
//	while (1)
//	{
//		cin >> c;
//		int curr; cin >> curr;
//		if (curr == -1) break;
//		count[curr]++;
//	}
//
//	for (int t = 0; t < 256; t++)
//	{
//		ll births = count[0];
//		vector<ll> next(9);
//
//		for (int i = 0; i < 8; i++)
//		{
//			next[i] = count[i + 1];
//		}
//		next[8] += births;
//		next[6] += births;
//		count = next;
//	}
//	ll sum = 0;
//	for (int i = 0; i < 9; i++)
//	{
//		sum += count[i];
//	}
//	cout << sum;
//}

//7

//#include <iostream>
//#include <vector>
//using namespace std;
//
//#define ll long long
//
//int main()
//{
//	ll max = LLONG_MIN, min = LLONG_MAX;
//	vector<ll> loc;
//	while (1)
//	{
//		ll currX; cin >> currX;
//		if (currX == -1000) break;
//		loc.push_back(currX);
//		if (currX > max) max = currX;
//		if (currX < min) min = currX;
//		char t; cin >> t;
//	}
//	ll minF = LLONG_MAX;
//	for (ll x = min; x <= max; x++)
//	{
//		ll total = 0;
//		for (int i = 0; i < loc.size(); i++)
//		{
//			ll d = abs(loc[i] - x);
//			total += d*(d+1)/2;
//		}
//		if (total < minF) minF = total;
//	}
//	cout << minF;
//}

//8

//#include <iostream>
//#include <algorithm>
//#include <vector>
//#include <set>
//#include <map>
//using namespace std;
//// 2, 4, 3, 7
//int main()
//{
//	int sum = 0;
//	while (1)
//	{
//		vector<vector<char>> iv, ov;
//		iv.clear();
//		while(1)
//		{
//			string in; cin >> in;
//			vector<char> inS;
//			for (int i = 0; i < in.size(); i++)
//				inS.push_back(in[i]);      
//			if (in == "|") break;
//			sort(inS.begin(), inS.end());
//			iv.push_back(inS);
//		}
//		if (iv.size() == 1) break;
//		ov.resize(4);
//		for (int i = 0; i < 4; i++)
//		{
//			string in; cin >> in;
//			vector<char> inS;
//			for (int i = 0; i < in.size(); i++)
//				inS.push_back(in[i]);
//			sort(inS.begin(), inS.end());
//			ov[i] = inS;
//		}
//		vector<int> letter = { 0, 1, 2, 3, 4, 5, 6 };
//		map<char, int> convert = { {'a', 0},{'b', 1},{'c', 2},{'d', 3},{'e', 4},{'f', 5},{'g', 6} };
//		vector<char> display = { 'a', 'b', 'c', 'd', 'e', 'f', 'g' };
//		map<set<char>, int> seq2numb =
//		{
//			{{'a','b','c','e','f','g'},1},
//			{{'c','f'},2},
//			{{'a','c','d','e','g'},3},
//			{{'a','c','d','f','g'},4},
//			{{'b','c','d','f'},5},
//			{{'a','b','d','f','g'},6},
//			{{'a','b','d','f','e','g'},7},
//			{{'a','c','f'},8},
//			{{'a','b','c','d','e','f','g'},9},
//			{{'a','b','c','d','f','g'},10}
//		};
//		int ans = 0;
//		do
//		{
//			bool bad = false;
//			for (int i = 0; i < 10; i++)
//			{
//				set<char> pred;
//				for (int j = 0; j < iv[i].size(); j++)
//				{
//					pred.insert(display[letter[convert[iv[i][j]]]]);
//				}
//				if (seq2numb[pred] == 0) 
//				{
//					bad = true;
//					break;
//				}
//			}
//			if (bad) continue;
//			for (int i = 0; i < 4; i++)
//			{
//				set<char> pred;
//				for (int j = 0; j < ov[i].size(); j++)
//				{
//					pred.insert(display[letter[convert[ov[i][j]]]]);
//				}
//				ans = ans * 10 + seq2numb[pred] - 1;
//			}
//			break;
//		} while (next_permutation(display.begin(), display.end()));
//		sum += ans;
//	}
//	cout << sum;
//}

//9

//#include <iostream>
//#include <vector>
//#include <string>
//using namespace std;
//
//vector<vector<int>> grid;
//
//void setLowestCoords(vector<vector<int>>& ans)
//{
//	for (int i = 1; i < grid.size() - 1; i++)
//	{
//		for (int j = 1; j < grid[0].size() - 1; j++)
//		{
//			if (grid[i][j] < grid[i + 1][j] && grid[i][j] < grid[i][j + 1] &&
//				grid[i][j] < grid[i - 1][j] && grid[i][j] < grid[i][j - 1])
//			{
//				ans.push_back({ i, j });
//			}
//		}
//	}
//	for (int j = 1; j < grid[0].size() - 1; j++)
//	{
//		if (grid[0][j] < grid[1][j] && grid[0][j] < grid[0][j + 1] &&
//			grid[0][j] < grid[0][j - 1])
//		{
//			ans.push_back({ 0, j });
//		}
//		if (grid[grid.size() - 1][j] < grid[grid.size() - 2][j] && grid[grid.size() - 1][j] < grid[grid.size() - 1][j + 1] &&
//			grid[grid.size() - 1][j] < grid[grid.size() - 1][j - 1])
//		{
//			ans.push_back({ (int)grid.size() - 1, j });
//		}
//	}
//	for (int i = 1; i < grid.size() - 1; i++)
//	{
//		if (grid[i][0] < grid[i][1] &&
//			grid[i][0] < grid[i + 1][0] &&
//			grid[i][0] < grid[i - 1][0])
//		{
//			ans.push_back({ i, 0 });
//		}
//		if (grid[i][grid[0].size() - 1] < grid[i][grid[0].size() - 2] &&
//			grid[i][grid[0].size() - 1] < grid[i + 1][grid[0].size() - 1] &&
//			grid[i][grid[0].size() - 1] < grid[i - 1][grid[0].size() - 1])
//		{
//			ans.push_back({ i, (int)grid[0].size() - 1 });
//		}
//	}
//
//	if (grid[0][0] < grid[0][1] &&
//		grid[0][0] < grid[1][0])
//		ans.push_back({ 0,0 });
//
//	if (grid[grid.size() - 1][0] < grid[grid.size() - 1][1] &&
//		grid[grid.size() - 1][0] < grid[grid.size() - 2][0])
//		ans.push_back({ (int)grid.size() - 1, 0});
//
//	if (grid[0][grid[0].size() - 1] < grid[1][grid[0].size() - 1] &&
//		grid[0][grid[0].size() - 1] < grid[0][grid[0].size() - 2])
//		ans.push_back({ 0, (int)grid[0].size() - 1 });
//
//	if (grid[grid.size() - 1][grid[0].size() - 1] < grid[grid.size() - 2][grid[0].size() - 1] &&
//		grid[grid.size() - 1][grid[0].size() - 1] < grid[grid.size() - 1][grid[0].size() - 2])
//		ans.push_back({ (int)grid.size() - 1, (int)grid[0].size() - 1 });
//}
//
//int d[4][2] = { {0, 1},{0, -1},{1, 0},{-1, 0} };
//vector<vector<bool>> visited;
//void ff(int i, int j, int& size)
//{
//	size++;
//	visited[i][j] = true;
//	for (int k = 0; k < 4; k++)
//	{
//		int newI = i + d[k][0], newJ = j + d[k][1];
//		if (newI == -1 || newI == grid.size() || newJ == -1 || newJ == grid[0].size() || visited[newI][newJ] || grid[newI][newJ] == 9) continue;
//		ff(newI, newJ, size);
//	}
//}
//
//int main()
//{
//	while (1)
//	{
//		string line;
//		cin >> line;
//		if (line.size() == 1) break;
//		vector<int> gl;
//		for (int i = 0; i < line.size(); i++)
//		{
//			gl.push_back(line[i] - '0');
//		}
//		grid.push_back(gl);
//	}
//	vector<vector<int>> lowest;
//	visited.resize(grid.size(), vector<bool>(grid[0].size()));
//	setLowestCoords(lowest);
//	int max1 = 0, max2 = 0, max3 = 0;
//	for (int i = 0; i < lowest.size(); i++)
//	{
//		int size = 0;
//		ff(lowest[i][0], lowest[i][1], size);
//		vector<bool> t(grid[0].size());
//		fill(visited.begin(), visited.end(), t);
//		if (size > max1)
//		{
//			max3 = max2;
//			max2 = max1;
//			max1 = size;
//		}
//		else if (size > max2)
//		{
//			max3 = max2;
//			max2 = size;
//		}
//		else if (size > max3)
//		{
//			max3 = size;
//		}
//	}
//	cout << max1 * max2 * max3;
//}

//10

//#include <iostream>
//#include <stack>
//#include <vector>
//#include <string>
//#include <algorithm>
//using namespace std;
//
//#define ll long long
//
//int main()
//{
//	vector<string> lines;
//	while (1)
//	{
//		string line; cin >> line;
//		if (line == "-") break;
//		lines.push_back(line);
//	}
//	vector<bool> corrupted(lines.size());
//	for (int i = 0; i < lines.size(); i++)
//	{
//		stack<char> sc;
//		int points = 0;
//		for (int j = 0; j < lines[i].size(); j++)
//		{
//			char curr = lines[i][j];
//			switch (curr)
//			{
//			case '{':
//				sc.push('{'); break;
//			case '[':
//				sc.push('['); break;
//			case '(':
//				sc.push('('); break;
//			case '<':
//				sc.push('<'); break;
//
//			case '}':
//				if (sc.top() != '{') points = 1197;
//				sc.pop();
//				break;
//			case ']':
//				if (sc.top() != '[') points = 57;
//				sc.pop();
//				break;
//			case ')':
//				if (sc.top() != '(') points = 3;
//				sc.pop();
//				break;
//			case '>':
//				if (sc.top() != '<') points = 25137;
//				sc.pop();
//				break;
//			}
//			if (points > 0) break;
//		}
//		if (points > 0)
//		{
//			corrupted[i] = true;
//		}
//	}
//	vector<ll> ansV;
//	for (int i = 0; i < lines.size(); i++)
//	{
//		if (corrupted[i]) continue;
//		stack<char> sc;
//		string remaining = "";
//		for (int j = 0; j < lines[i].size(); j++)
//		{
//			char curr = lines[i][j];
//			switch (curr)
//			{
//			case '{':
//				sc.push('{'); break;
//			case '[':
//				sc.push('['); break;
//			case '(':
//				sc.push('('); break;
//			case '<':
//				sc.push('<'); break;
//
//			case '}':
//				sc.pop();
//				break;
//			case ']':
//				sc.pop();
//				break;
//			case ')':
//				sc.pop();
//				break;
//			case '>':
//				sc.pop();
//				break;
//			}
//		}
//		ll points = 0;
//		while (sc.size() != 0)
//		{
//			points *= 5;
//			char curr = sc.top();
//			sc.pop();
//			switch (curr)
//			{
//			case '{':
//				points += 3; break;
//			case '[':
//				points += 2; break;
//			case '(':
//				points += 1; break;
//			case '<':
//				points += 4; break;
//			}
//		}
//		ansV.push_back(points);
//	}
//	sort(ansV.begin(), ansV.end());
//	cout << ansV[ansV.size() / 2];
//}