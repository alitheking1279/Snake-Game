#include<iostream>
#include<cstdlib>
#include<ctime>
#include<conio.h>
#include<windows.h>
#include<unistd.h>
#include<vector>
using namespace std;
enum Direction{up,down,Left,Right};
enum Difficulty{Easy=80,Medium=50,Hard=30};
const int X=20;
const int Y=20;
int px=5,py=5;
int score=0;
class Snake{
	private: 
	char box[X][Y];
	char player='O';
	char food='x';
	char trail='o';
	Direction direction;
	vector<pair<int,int>> tail;
	public:
	void create()
	{
		for(int i=0;i<20;i++)
			{for(int k=0;k<20;k++)
				{if(i==0||i==19)
				box[i][k]='#';
				else if(k==0||k==19)
				box[i][k]='#';
				else
				box[i][k]=' ';}
				}
				
	}
	void display()
	{
		for(int i=0;i<20;i++)
			{for(int k=0;k<20;k++)
				cout<<box[i][k];
				cout<<endl;}
	}
	void Player()
	{
			box[px][py]=player;
	}	
	void Food()
	{
		srand(time(NULL));
		int start,temp;
		bool free=false;
		while(!free)
		{
			temp=rand()%19+1;
			start=rand()%19+1;
			if(box[temp][start]==' ')
			{box[temp][start]=food;
			free=true;}
		}
	}
	void ChangeDirection(char input)
	{
	if (input == 'w') 
	{ direction = up;}
	else if (input == 's') 
	{direction = down;}
	else if (input == 'a') 
	{direction = Left;}
	 else 
	 {direction = Right;}

	}
    void movement() {
        int oldx = px, oldy = py;
        switch (direction) {
            case Left: if (box[px][py - 1] != '#' && box[px][py - 1] != trail) py--; break;
            case Right: if (box[px][py + 1] != '#' && box[px][py + 1] != trail) py++; break;
            case up: if (box[px - 1][py] != '#' && box[px - 1][py] != trail) px--; break;
            case down: if (box[px + 1][py] != '#' && box[px + 1][py] != trail) px++; break;
        }

        if (box[px][py] == food) {
            score += 10;
            tail.push_back({oldx, oldy});
            Food(); 
        } else {
            tail.push_back({oldx, oldy});
            if (tail.size() > score / 10) {  
                pair<int, int> old = tail.front();
                box[old.first][old.second] = ' ';
                tail.erase(tail.begin());
            }
        }

        box[px][py] = player;

        for (auto t : tail) {
            box[t.first][t.second] = trail;
        }
    }
	bool GameOver()
	{
	        if (px == 0||px==19||py==0||py==19)
			 return true;

        for (auto t : tail) {
            if (t.first == px && t.second == py) return true;
        }

        return false;
    }
	int chose()
	{
		cout<<"\nChose your difficulty:\n[1]Easy\n[2]Medium\n[3]Hard";
		char c;
		c=getch();
		Difficulty d;
		switch(c){
			case '1':d=Easy;return d;break;
			case '2':d=Medium;return d;break;
			case '3':d=Hard;return d;break;
		}
	}

};
int main()
{
	Snake b;
	b.create();
	b.Player();
	b.Food();
	int c=b.chose();
	while(!b.GameOver())
	{b.display();
	cout<<"\nSCORE ["<<score<<"]";
		if(_kbhit()){
		char input=_getch();
		b.ChangeDirection(input);
	}
	b.movement();
	Sleep(c);
	system("cls");
	}
	b.display();
	cout<<"\nGAME OVER\nYOUR SCORE WAS:"<<score;
	return 0;
}