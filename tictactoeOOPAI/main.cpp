#include <bits/stdc++.h>
#define ipair pair<int, int>


using namespace std;

const int INF = 100000;

int a[4][4];

void dataOutput(){
	for (int i=1; i<=3; i++){
		for (int j=1; j<=3; j++){
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int checkWin(int player, int b[][4]){
    int a[10];
    for (int i=1; i<=3; i++)
    for (int j=1; j<=3; j++){
        a[(i - 1) * 3 + j] = b[i][j];
    }
    if (a[1] == player && a[2] == player && a[3] == player) return 1;
    if (a[4] == player && a[5] == player && a[6] == player) return 1;
    if (a[7] == player && a[8] == player && a[9] == player) return 1;
    if (a[1] == player && a[5] == player && a[9] == player) return 1;
    if (a[3] == player && a[5] == player && a[7] == player) return 1;
    if (a[1] == player && a[4] == player && a[7] == player) return 1;
    if (a[2] == player && a[5] == player && a[8] == player) return 1;
    if (a[3] == player && a[6] == player && a[9] == player) return 1;
    return 0;
}

int winning(int b[][4]){
    if (checkWin(2, b)) return 1;
    else if (checkWin(1, b)) return -1;
    else return 0;
}

int minimax(int b[][4], int maximizingPlayer, int depth){
    if (winning(b) == 1) return 10 - depth;
    if (winning(b) == -1) return -10 + depth;

    if (maximizingPlayer){
        int best = -INF;
        for (int i=1; i<4; i++)
            for (int j=1; j<4; j++)
                if (b[i][j] == 0){
                    b[i][j] = 2;
                    int val = minimax(b, 1, depth + 1);
                    best = max(best, val);
                    b[i][j] = 0;
                }
        return best;
    }
    else{
        int best = INF;
        for (int i=1; i<4; i++)
            for (int j=1; j<4; j++)
                if (b[i][j] == 0){
                    b[i][j] = 1;
                    int val = minimax(b, 0, depth + 1);
                    best = min(best, val);
                    b[i][j] = 0;
                }
        return best;
    }
    return 0;
}

int dataInput(int type, int x, int y){
	if (a[x][y] != 0){
		return 1;
	}
	a[x][y] = type;
	ofstream f1("tictactoe.dat",ios::app);
	f1 << type << " " << x << " " << y << endl;
	return 0;
}

ipair createMove(int b[][4], int player){
    int res = -INF;
    ipair p_res;
    for (int i=1; i< 4; i++)
    for (int j=1; j<4; j++){
        if (a[i][j] == 0){
            a[i][j] = 2;
            int tmp = minimax(b, 0, 0);
            if (tmp > res){
                res = tmp;
                p_res = make_pair(i, j);
            }
            a[i][j] = 0;
        }
    }
    return p_res;
}

int checkTie(){
    int flag = 0;
    for (int i=1; i<=3; i++)
    for (int j=1; j<=3; j++){
        if (a[i][j] == 0) flag = 1;
    }
    if (flag == 0) return 1;
    return 0;
}

int main(){
    cout << "Do you want to move first? (1/ yes, 2/ no)";
    int c;
    cin >> c;
    int flag = c == 1? 0: 1;
    while (1){
        if (flag == 1){
            ipair p = createMove(a, 1);
            a[p.first][p.second] = 2;
            cout << "Com:" << endl;
            dataOutput();
            if (checkWin(2, a)){
                cout << "You Lose!!, ofcourse, cuz i'm undefeatable" << endl;
                return 0;
            }
            else if (checkWin(1, a)){
                cout << "You Win!!!" << endl;
                return 0;
            }
            if (checkTie()){
                cout << "Match tie!! Good job, cuz you can't win this game, the retard!!";
                return 0;
            }
            flag = !flag;
        }
        else{
            ipair p;
            cin >> p.first >> p.second;
            a[p.first][p.second] = 1;
            cout << "You:" << endl;
            dataOutput();
            if (checkWin(2, a)){
                cout << "You Lose!!" << endl;
                return 0;
            }
            else if (checkWin(1, a)){
                cout << "You Win!!!" << endl;
                return 0;
            }
            if (checkTie()){
                cout << "Match tie!! Good job, cuz you can't win this game, the retard!!";
            }
            flag = !flag;
        }
    }
}
