#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
#include<thread>
using namespace std;const int N=1e2+1;
int n,m,difficult=1,score=0;unsigned char Map[N][N];bool flag=true;string s,facing;int dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}};char ch,now_dir;
struct Point{int x,y;};
vector<Point> snack;
Point apple;
int get_sleep_time(){
    return 500-(difficult-1)*20;
}
void Init(){
    for(int i=0;i<N;i++)for(int j=0;j<N;j++){Map[i][j]='0';}
    Point a,b;
    a.x=a.y=2;b.x=3;b.y=2;
    snack.push_back(a);snack.push_back(b);
    facing[0]='d';s[0]='d';
    srand((unsigned)time(NULL));
    apple.y=rand()%n;apple.x=rand()%m;
}
void map_print(){
    system("cls");
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<m;j++){
    //         if(Map[i][j]=='1')cout<<" ";
    //         else if(Map[i][j]=='2')cout<<"$";
    //         else cout<<"#";
    //     }
    //     cout<<endl;
    // }
    for(int i=0;i<m+1;i++){cout<<"-";}cout<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(Map[i][j]=='1')cout<<"*";
            else if(Map[i][j]=='2')cout<<"+";
            else cout<<" ";
        }
        cout<<"|"<<endl;
    }
    for(int i=0;i<m+1;i++){cout<<"-";}
    cout<<endl;
    cout<<"Score: "<<score<<endl;
}
void map_updata(){
    for(int i=0;i<n;i++)for(int j=0;j<m;j++){Map[i][j]='0';}
    for(int i=0;i<snack.size();i++){
        Map[snack[i].y][snack[i].x]='1';
    }
    Map[apple.y][apple.x]='2';
}
bool hit_wall(Point nn){
    if(nn.x<0||nn.x>=m||nn.y<0||nn.y>=n)return true;
    return false;
}
void set_apple(){
    apple.y=rand()%n;apple.x=rand()%m;
    for(int i=0;i<snack.size();i++){
        if(apple.x==snack[i].x&&apple.y==snack[i].y){set_apple();break;}
    }
}
bool eat_apple(Point nn){
    if(nn.y==apple.y&&nn.x==apple.x){difficult++;score++;return true;}
    return false;
}
void end_game_title(){
    cout<<"\nYou Failed The Game!\nPlease input Esc to exit!"<<endl;
    flag=false;
    Sleep(1000);
}
void begin_game_title(){
    cout<<"Enter 'w' 'a' 's' 'd' to contorl the snack\nEnter 'Enter' to confirmed your choice!"<<endl;
}
bool eat_myself(Point nn){
    for(int i=0;i<snack.size();i++){
        if(snack[i].x==nn.x&&snack[i].y==nn.y)return true;
    }
    return false;
}
void get_key(){
    while(now_dir=getch()){
        if(!flag&&now_dir==27){break;}
        if((now_dir=='w'&&facing[0]!='s')||(now_dir=='a'&&facing[0]!='d')||(now_dir=='s'&&facing[0]!='w')||(now_dir=='d'&&facing[0]!='a')){s[0]=now_dir;}
        Sleep(10);
    }
}
void main_game(){
    while(1){
        if(s[0]=='w'&&facing[0]!='s'){
                Point next_body;
                next_body.x=(*(--snack.end())).x+dir[0][0];next_body.y=(*(--snack.end())).y+dir[0][1];
                if(hit_wall(next_body)){
                    end_game_title();
                    break;
                }else if(eat_myself(next_body)){
                    end_game_title();
                    break;
                }
                else{
                    snack.push_back(next_body);
                    if(eat_apple(next_body)){
                        set_apple();
                    }else{
                        snack.erase(snack.begin());
                    }
                    facing[0]='w';
                }
        }else if(s[0]=='a'&&facing[0]!='d'){
                Point next_body;
                next_body.x=(*(--snack.end())).x+dir[1][0];next_body.y=(*(--snack.end())).y+dir[1][1];
                if(hit_wall(next_body)){
                    end_game_title();
                    break;
                }else if(eat_myself(next_body)){
                    end_game_title();
                    break;
                }else{
                    snack.push_back(next_body);
                    if(eat_apple(next_body)){
                        set_apple();
                    }else{
                        snack.erase(snack.begin());
                    }
                    facing[0]='a';
                }
        }else if(s[0]=='s'&&facing[0]!='w'){
                Point next_body;
                next_body.x=(*(--snack.end())).x+dir[2][0];next_body.y=(*(--snack.end())).y+dir[2][1];
                if(hit_wall(next_body)){
                    end_game_title();
                    break;
                }else if(eat_myself(next_body)){
                    end_game_title();
                    break;
                }else{
                    snack.push_back(next_body);
                    if(eat_apple(next_body)){
                        set_apple();
                    }else{
                        snack.erase(snack.begin());
                    }
                    facing[0]='s';
                }
        }else if(s[0]=='d'&&facing[0]!='a'){
                Point next_body;
                next_body.x=(*(--snack.end())).x+dir[3][0];next_body.y=(*(--snack.end())).y+dir[3][1];
                if(hit_wall(next_body)){
                    end_game_title();
                    break;
                }else if(eat_myself(next_body)){
                    end_game_title();
                    break;
                }else{
                    snack.push_back(next_body);
                    if(eat_apple(next_body)){
                        set_apple();
                    }else{
                        snack.erase(snack.begin());
                    }
                    facing[0]='d';
                }
            }
        map_updata();map_print();
        Sleep(get_sleep_time());
    }
}
int main(){
    cout<<"Please Input Map Size And Difficult!"<<endl;
    cin>>n>>m>>difficult;
    Init();
    map_updata();
    map_print();
    begin_game_title();
    thread T1(get_key);
    thread T2(main_game);
    T1.join();
    T2.join();
    // while(ch=getch()){
    //     s[0]=ch;
    //     if(s[0]=='w'&&facing[0]!='s'){
    //         Point next_body;
    //         next_body.x=(*(--snack.end())).x+dir[0][0];next_body.y=(*(--snack.end())).y+dir[0][1];
    //         if(hit_wall(next_body)){
    //             end_game_title();
    //             break;
    //         }else if(eat_myself(next_body)){
    //             end_game_title();
    //             break;
    //         }
    //         else{
    //             snack.push_back(next_body);
    //             if(eat_apple(next_body)){
    //                 set_apple();
    //             }else{
    //                 snack.erase(snack.begin());
    //             }
    //             facing[0]='w';
    //         }
    //     }else if(s[0]=='a'&&facing[0]!='d'){
    //         Point next_body;
    //         next_body.x=(*(--snack.end())).x+dir[1][0];next_body.y=(*(--snack.end())).y+dir[1][1];
    //         if(hit_wall(next_body)){
    //             end_game_title();
    //             break;
    //         }else if(eat_myself(next_body)){
    //             end_game_title();
    //             break;
    //         }else{
    //             snack.push_back(next_body);
    //             if(eat_apple(next_body)){
    //                 set_apple();
    //             }else{
    //                 snack.erase(snack.begin());
    //             }
    //             facing[0]='a';
    //         }
    //     }else if(s[0]=='s'&&facing[0]!='w'){
    //         Point next_body;
    //         next_body.x=(*(--snack.end())).x+dir[2][0];next_body.y=(*(--snack.end())).y+dir[2][1];
    //         if(hit_wall(next_body)){
    //             end_game_title();
    //             break;
    //         }else if(eat_myself(next_body)){
    //             end_game_title();
    //             break;
    //         }else{
    //             snack.push_back(next_body);
    //             if(eat_apple(next_body)){
    //                 set_apple();
    //             }else{
    //                 snack.erase(snack.begin());
    //             }
    //             facing[0]='s';
    //         }
    //     }else if(s[0]=='d'&&facing[0]!='a'){
    //         Point next_body;
    //         next_body.x=(*(--snack.end())).x+dir[3][0];next_body.y=(*(--snack.end())).y+dir[3][1];
    //         if(hit_wall(next_body)){
    //             end_game_title();
    //             break;
    //         }else if(eat_myself(next_body)){
    //             end_game_title();
    //             break;
    //         }else{
    //             snack.push_back(next_body);
    //             if(eat_apple(next_body)){
    //                 set_apple();
    //             }else{
    //                 snack.erase(snack.begin());
    //             }
    //             facing[0]='d';
    //         }
    //     }
    //     map_updata();map_print();
    // }
}