#include <vector>
#include <iostream>

using namespace std;

/*
 1   2  3  4
++  ++  + + 
 +  +  ++ ++

 */
//y, x
//type1

int tile[4][3][2] = 
{ 
	{ {0, 0 }, { 0, 1 }, { 1, 1 }},
	{ {0, 0 }, { 0, 1 }, { 1, 0 }},
	{ {0, 0 }, { 1, -1}, { 1, 0 }},
	{ {0, 0 }, { 1, 0 }, { 1, 1 }}
};

int set(vector<vector<int> > & board, int y, int x, int type, int delta) {
	bool ok = true;
	for (int i = 0; i < 3; ++i) {
		int tile_y = y + tile[type][i][0];
		int tile_x = x + tile[type][i][1];
		if (tile_y < 0 || board.size() <= tile_y ||
			tile_x < 0 || board[0].size() <= tile_x)
			ok = false;
		else if ((board[tile_y][tile_x] += delta) > 1)
			ok = false;
	}
	return ok;
}

void assert(bool a, int line) {
	if (a)
		cout << "test passed at " <<line<<endl;
	else
		cout << "test failed at " <<line<<endl;
}

#define ASSERT(a) assert(a, __LINE__)

void test_set() {
	vector<vector<int> > board(2, vector<int>(2, 0));
	//test same tile twice 
	int ret = set(board, 0, 0, 0, 1);
	ASSERT(ret == true);
	ret = set(board, 0, 0, 0, 1);
	ASSERT(ret == false);
	ret = set(board, 0, 0, 0, -1);
	ret = set(board, 0, 0, 0, -1);

	//test outside
	ret = set(board, 0, 0, 2, 1);
	ASSERT(ret == false);
	ret = set(board, 0, 0, 0, -1);
	
	//test wrong
	board[0][0] = 1;
	ret = set(board, 0, 0, 2, 1);
	ASSERT(ret == false);
	ret = set(board, 0, 0, 0, -1);
	return;
}

int cover(vector<vector<int> > & board) {
	int y = -1, x = -1;
	int result = 0;
	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board[0].size(); ++j) {
			if (0 == board[i][j]) {
				y = i;
				x = j;
				break;
			}
		}
		if (-1 != y)
			break;
	}
		
	if (-1 == y)
		return 1;

	for (int i = 0; i < 4; ++i) {
		int ret = set(board, y, x, i, 1);
		if (ret)
			result += cover(board);
		set(board, y, x, i, -1);
	}
	return result;
}

int main()
{
	int num_of_tc;
	cin >> num_of_tc;
	for (int k = 0; k < num_of_tc; ++k) {
		int height, width;
		char input;
		cin >> height >> width;
		//cout<<"height: "<<height<<" width: "<<width<<endl;

		vector<vector<int> > board(height, vector<int>(width, 0));
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				cin >> input;
				if ('#' == input)
					board[i][j] = 1;
				else
					board[i][j] = 0;
			}
		}
		/*
			for (int i = 0; i < height; ++i) {
				for (int j = 0; j < width; ++j) {
					//cout << board[i][j] << " ";
				}
				//cout << endl;
			}
		*/
		//	test_set();
		int ret = cover(board);
		cout << ret << endl;
	}
    return 0;
}
