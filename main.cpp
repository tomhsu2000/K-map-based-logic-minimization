#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Node
{
	int val;
	int num;
	Node* right;
	Node* down;

	struct CircleInfo
	{
		Node* node;
		int row;
		int col;
	};

	vector<CircleInfo> circleInfo;
};

void loadFile(ifstream& inFile, vector<Node*>& headerList);

void input(vector<Node*>& headerList);

void checkAll(Node* header);

void check(Node* node, int row, int col);

void circle(Node* node, int row, int col);

void select(Node* node);

int* transform(int row, int col);

void print(Node::CircleInfo circleInfo);

int main(int argc, char* argv[])
{
	vector<Node*> headerList;

	ifstream readFile;
	readFile.open(argv[1]);
	loadFile(readFile, headerList);

	for (int i = 0; i < headerList.size(); i++)
		checkAll(headerList[i]);

	for (int i = 0; i < headerList.size(); i++) {
		cout << "#" << i + 1 << endl;
		select(headerList[i]);
	}
}

void loadFile(ifstream& inFile, vector<Node*>& headerList)
{
	if (!inFile) {
		cout << "File could not be opened" << endl;
		return;
	}

	Node* header, * pretemp = nullptr, * temp;
	vector<Node*> tempHeader;
	char numericString[40];
	int dataNum, pos;
	inFile.getline(numericString, 40, '\n');
	dataNum = (int)atoi(numericString);
	for (int i = 0; i < dataNum; i++) {
		inFile.getline(numericString, 40, '\n');
		pos = 0;
		while (pos < 31) {
			temp = new Node;
			temp->val = numericString[pos] - '0';
			temp->num = pos / 2;
			if ((pos / 2) % 4 == 0) {
				header = pretemp = new Node;
				temp->right = temp;
				header = pretemp = temp;
				tempHeader.push_back(header);
			}
			else {
				temp->right = pretemp->right;
				pretemp->right = temp;
				pretemp = temp;
			}
			pos += 2;
		}
		headerList.push_back(tempHeader[0]);
		for (int i = 0; i < tempHeader.size(); i++) {
			pretemp = tempHeader[i];
			temp = tempHeader[(i + 1) % 4];
			for (int j = 0; j < 4; j++, pretemp = pretemp->right, temp = temp->right)
				pretemp->down = temp;
		}
		tempHeader.clear();
	}
}

void input(vector<Node*>& headerList)
{
	Node* header, * pretemp = nullptr, * temp;
	vector<Node*> tempHeader;
	int dataNum, pos;
	cout << "How many questions ?" << endl;
	cin >> dataNum;
	for (int i = 0; i < dataNum; i++) {
		pos = 0;
		cout << "#" << i + 1 << " K-MAP format ?" << endl;
		while (pos < 31) {
			temp = new Node;
			cin >> temp->val;
			if ((pos / 2) % 4 == 0) {
				header = pretemp = new Node;
				temp->right = temp;
				header = pretemp = temp;
				tempHeader.push_back(header);
			}
			else {
				temp->right = pretemp->right;
				pretemp->right = temp;
				pretemp = temp;
			}
			pos += 2;
		}
		headerList.push_back(tempHeader[0]);
		for (int i = 0; i < tempHeader.size(); i++) {
			pretemp = tempHeader[i];
			temp = tempHeader[(i + 1) % 4];
			for (int j = 0; j < 4; j++, pretemp = pretemp->right, temp = temp->right)
				pretemp->down = temp;
		}
		tempHeader.clear();
	}
}

void checkAll(Node* header)
{
	Node* temp = header;
	check(temp, 4, 4);
	temp = header;
	for (int i = 0; i < 4; i++) {
		check(temp, 4, 2);
		temp = temp->right;
	}
	temp = header;
	for (int i = 0; i < 4; i++) {
		check(temp, 2, 4);
		temp = temp->down;
	}
	temp = header;
	for (int i = 0; i < 4; i++) {
		check(temp, 4, 1);
		temp = temp->right;
	}
	temp = header;
	for (int i = 0; i < 4; i++) {
		check(temp, 1, 4);
		temp = temp->down;
	}
	temp = header;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			check(temp, 2, 2);
			temp = temp->right;
		}
		temp = temp->down;
	}
	temp = header;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			check(temp, 2, 1);
			temp = temp->right;
		}
		temp = temp->down;
	}
	temp = header;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			check(temp, 1, 2);
			temp = temp->right;
		}
		temp = temp->down;
	}
	temp = header;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			check(temp, 1, 1);
			temp = temp->right;
		}
		temp = temp->down;
	}
}

void check(Node* node, int row, int col)
{
	Node* temp = node, * pretemp = node;
	Node::CircleInfo circle;
	int existOne = -1;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++, temp = temp->right) {
			if (temp->val == 0) {
				existOne = 0;
				break;
			}
			else if (temp->val == 1)
				existOne = 1;
		}
		if (existOne == 0)
			break;
		temp = pretemp->down;
		pretemp = temp;
	}
	if (existOne == 1) {
		temp = pretemp = node;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++, temp = temp->right) {
				if (temp->val == 1) {
					temp->val = 3;
					circle.node = node;
					circle.row = row;
					circle.col = col;
					temp->circleInfo.push_back(circle);
				}
				else if (temp->val >= 3) {
					temp->val++;
					circle.node = node;
					circle.row = row;
					circle.col = col;
					temp->circleInfo.push_back(circle);
				}
			}
			temp = pretemp->down;
			pretemp = temp;
		}
	}
}

void circle(Node* node, int row, int col)
{
	Node* temp, * pretemp;
	Node::CircleInfo circle;
	temp = pretemp = node;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++, temp = temp->right) {
			if (temp->val == 1) {
				temp->val = 3;
				circle.node = temp;
				circle.row = row;
				circle.col = col;
				temp->circleInfo.push_back(circle);
			}
			else if (temp->val >= 3) {
				temp->val++;
				circle.node = temp;
				circle.row = row;
				circle.col = col;
				temp->circleInfo.push_back(circle);
			}
		}
		temp = pretemp->down;
		pretemp = temp;
	}
}

void select(Node* node)
{
	Node* temp = node;
	vector<Node::CircleInfo> circleList;
	bool exist = false;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (temp->val == 3) {
				circleList.push_back(temp->circleInfo[0]);
				print(temp->circleInfo[0]);
			}
			temp = temp->right;
		}
		temp = temp->down;
	}
	temp = node;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (temp->val > 3) {
				for (int l = 0; l < temp->circleInfo.size(); l++) {
					for (int k = 0; k < circleList.size(); k++) {
						if (circleList[k].node != temp->circleInfo[l].node &&
							circleList[k].row != temp->circleInfo[l].row &&
							circleList[k].col != temp->circleInfo[l].col &&
							k == circleList.size() - 1) {
							circleList.push_back(temp->circleInfo[l]);
							print(temp->circleInfo[l]);
							exist = true;
							break;
						}
					}
					if (exist)
						break;
				}
			}
			temp = temp->right;
		}
		temp = temp->down;
	}
}

int* transform(int row, int col)
{
	int* result = new int[4];
	if (row == 0) {
		result[0] = 0;
		result[1] = 0;
	}
	else if (row == 1) {
		result[0] = 0;
		result[1] = 1;
	}
	else if (row == 2) {
		result[0] = 1;
		result[1] = 1;
	}
	else if (row == 3) {
		result[0] = 1;
		result[1] = 0;
	}
	if (col == 0) {
		result[2] = 0;
		result[3] = 0;
	}
	else if (col == 1) {
		result[2] = 0;
		result[3] = 1;
	}
	else if (col == 2) {
		result[2] = 1;
		result[3] = 1;
	}
	else if (col == 3) {
		result[2] = 1;
		result[3] = 0;
	}
	return result;
}

void print(Node::CircleInfo circleList)
{
	Node* pretemp, * ppretemp;
	Node::CircleInfo circle;
	int row, col, * check = nullptr, * result = nullptr;
	pretemp = ppretemp = circleList.node;
	for (int i = 0; i < circleList.row; i++) {
		for (int j = 0; j < circleList.col; j++, pretemp = pretemp->right) {
			if (pretemp->val >= 3) {
				pretemp->val = 1;
			}
			row = pretemp->num / 4;
			col = pretemp->num % 4;
			if (i == 0 && j == 0) {
				result = transform(row, col);
			}
			check = transform(row, col);
			for (int i = 0; i < 4; i++) {
				if (check[i] != result[i])
					result[i] = 2;
			}
		}
		pretemp = ppretemp->down;
		ppretemp = pretemp;
	}
	for (int k = 0; k < 4; k++)
		cout << result[k] << " ";
	cout << endl;
}
