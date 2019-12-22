#include "test.h"

int push_box_map [MAX][MAX];
int row, col;
int now = 0;

void Count::StepCount(){
    step+=1;
    attron(COLOR_PAIR(9));
    mvprintw(3,15,"step : %d",step);
}

void Count::PushCount(){
    push+=1;
    attron(COLOR_PAIR(9));
    mvprintw(5,15,"move box : %d",push);
}

    void gameManager::DrawMap(){
        h_count = 0;
        initscr();
        curs_set(0);
        //색 관련
        start_color();
        init_pair(1,COLOR_GREEN,COLOR_WHITE);//벽
        init_pair(2,COLOR_YELLOW,COLOR_BLACK);//상자
        init_pair(3,COLOR_RED,COLOR_RED);//목적지
        init_pair(4,COLOR_BLUE,COLOR_BLUE);//바깥
        init_pair(5,COLOR_BLACK,COLOR_BLACK);//바닥
        init_pair(6,COLOR_CYAN,COLOR_BLACK);//캐릭터
        init_pair(7,COLOR_CYAN,COLOR_RED); //목적지 위에 캐릭터
        init_pair(8,COLOR_YELLOW,COLOR_RED);//목적지 위에 상자
        init_pair(9,COLOR_WHITE,COLOR_BLACK);

        attron(COLOR_PAIR(9));
        mvprintw(3,15,"step : %d",step);

        attron(COLOR_PAIR(9));
        mvprintw(5,15,"move box : %d",push);

        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
            //바닥
                if(push_box_map[i][j]==0){
                    attron(COLOR_PAIR(5));
                    mvprintw(i,j," ");
                }
                //벽
                else if(push_box_map[i][j]==1){
                    attron(COLOR_PAIR(1));
                    mvprintw(i,j,"*");
                }
                //상자
                else if(push_box_map[i][j]==2){
                    attron(COLOR_PAIR(2));
                    mvprintw(i,j,"X");
                }
                //목적지
                else if(push_box_map[i][j]==3){
                    attron(COLOR_PAIR(3));
                    mvprintw(i,j," ");
                    h_count+=1;
                }
                //배경
                else if(push_box_map[i][j]==4){
                    attron(COLOR_PAIR(4));
                    mvprintw(i,j," ");
                }
                //캐릭터
                else{//(push_box_map[i][j]==5)
                    attron(COLOR_PAIR(6));
                    mvprintw(i,j,"o");
                    a=i;
                    b=j; //캐릭터의 좌표 저장
                }
            }
            cout << endl;
        }
    }

    void gameManager::moveGame(){

        while(count!=h_count){
            keypad(stdscr, TRUE);
            int ch = getch();
            noecho();

            if(ch==KEY_LEFT){
            if(what==0){
                if(push_box_map[a][b-1]==3){//바닥에서 목적지로 가려고 할 때
                    what=3;
                    attron(COLOR_PAIR(7));
                    mvprintw(a,b-1,"o");
                    attron(COLOR_PAIR(5));
                    mvprintw(a,b," ");
                    push_box_map[a][b-1]=5;
                    push_box_map[a][b]=0;
                    b-=1;
                    StepCount();
                }
                else if(push_box_map[a][b-1]==2)//상자 밀려고 할 때
                {
                    if(push_box_map[a][b-2]==2)//상자 연속해서 있을 때
                    {
                        continue;
                    }
                    else if(push_box_map[a][b-2]==1)//상자 뒤에 벽일 때
                    {
                        continue;
                    }
                    else if(push_box_map[a][b-2]==0)//상자 뒤에 바닥일 때
                    {
                        what=0;
                        attron(COLOR_PAIR(2));
                        mvprintw(a,b-2,"X");
                        attron(COLOR_PAIR(6));
                        mvprintw(a,b-1,"o");
                        attron(COLOR_PAIR(5));
                        mvprintw(a,b," ");
                        push_box_map[a][b-2]=2;
                        push_box_map[a][b-1]=5;
                        push_box_map[a][b]=0;
                        b-=1;
                        StepCount();
                        PushCount();
                    }
                    else if(push_box_map[a][b-2]==3) //상자 목적지에 넣을 때
                    {
                        what=0;
                        attron(COLOR_PAIR(8));
                        mvprintw(a,b-2,"X");
                        attron(COLOR_PAIR(6));
                        mvprintw(a,b-1,"o");
                        attron(COLOR_PAIR(5));
                        mvprintw(a,b," ");
                        push_box_map[a][b-2]=2;
                        push_box_map[a][b-1]=5;
                        push_box_map[a][b]=0;
                        b-=1;
                        count+=1;
                        StepCount();
                        PushCount();
                    }
                }
                else if(push_box_map[a][b-1]==0)//바닥에서 바닥으로 가려고 할 때
                {
                    what=0;
                    attron(COLOR_PAIR(6));
                    mvprintw(a,b-1,"o");
                    attron(COLOR_PAIR(5));
                    mvprintw(a,b," ");
                    push_box_map[a][b-1]=5;
                    push_box_map[a][b]=0;
                    b-=1;
                    StepCount();
                }
                else if(push_box_map[a][b-1]==1)//바닥에서 벽으로 가려고 할 때
                {
                continue;
                }
            }


            else if(what==3)
            {
                if(push_box_map[a][b-1]==3)//목적지에서 목적지로 가려고 할 때
                {
                what=3;
                attron(COLOR_PAIR(7));
                mvprintw(a,b-1,"o");
                attron(COLOR_PAIR(3));
                mvprintw(a,b," ");
                push_box_map[a][b-1]=5;
                push_box_map[a][b]=3;
                b-=1;
                StepCount();
                }
                else if(push_box_map[a][b-1]==2)//상자 밀려고 할 때
                {
                if(push_box_map[a][b-2]==2)//상자 연속해서 있을 때
                {
                    continue;
                }
                else if(push_box_map[a][b-2]==1)//상자 뒤에 벽일 때
                {
                    continue;
                }
                else if(push_box_map[a][b-2]==0)//상자 뒤에 바닥일 때
                {
                    what=3;
                    attron(COLOR_PAIR(2));
                    mvprintw(a,b-2,"X");
                    attron(COLOR_PAIR(6));
                    mvprintw(a,b-1,"o");
                    attron(COLOR_PAIR(5));
                    mvprintw(a,b," ");
                    push_box_map[a][b-2]=2;
                    push_box_map[a][b-1]=5;
                    push_box_map[a][b]=3;
                    b-=1;
                    count-=1;
                    StepCount();
                    PushCount();
                }
                else if(push_box_map[a][b-2]==3) //상자 목적지에 넣을 때
                {
                    what=3;
                    attron(COLOR_PAIR(8));
                    mvprintw(a,b-2,"X");
                    attron(COLOR_PAIR(7));
                    mvprintw(a,b-1,"o");
                    attron(COLOR_PAIR(3));
                    mvprintw(a,b," ");
                    push_box_map[a][b-2]=2;
                    push_box_map[a][b-1]=5;
                    push_box_map[a][b]=3;
                    b-=1;
                    StepCount();
                    PushCount();
                }
                }
                else if(push_box_map[a][b-1]==0)//목적지에서 바닥으로 가려고 할 때
                {
                what=0;
                attron(COLOR_PAIR(6));
                mvprintw(a,b-1,"o");
                attron(COLOR_PAIR(3));
                mvprintw(a,b," ");
                push_box_map[a][b-1]=3;
                push_box_map[a][b]=0;
                b-=1;
                StepCount();
                }
                else if(push_box_map[a][b-1]==1)//목적지에서 벽으로 가려고 할 때
                {
                continue;
                }
            }
            }


            else if(ch==KEY_RIGHT)
            {
            if(what==3)
            {
                if(push_box_map[a][b+1]==0)//목적지에서 바닥으로 가려고 할 때
                {
                what=0;
                attron(COLOR_PAIR(6));
                mvprintw(a,b+1,"o");
                attron(COLOR_PAIR(3));
                mvprintw(a,b," ");
                push_box_map[a][b+1]=5;
                push_box_map[a][b]=3;
                b+=1;
                StepCount();
                }
                else if(push_box_map[a][b+1]==3)//목적지에서 목적지로 가려고 할 때
                {
                what=3;
                attron(COLOR_PAIR(7));
                mvprintw(a,b+1,"o");
                attron(COLOR_PAIR(3));
                mvprintw(a,b," ");
                push_box_map[a][b+1]=5;
                push_box_map[a][b]=3;
                b+=1;
                StepCount();
                }
                else if(push_box_map[a][b+1]==2)//상자 밀려고 할 때
                {
                if(push_box_map[a][b+2]==2)//상자 연속해서 있을 때
                {
                    continue;
                }
                else if(push_box_map[a][b+2]==1)//상자 뒤에 벽일 때
                {
                    continue;
                }
                else if(push_box_map[a][b+2]==0)//상자 뒤에 바닥일 때
                {
                    what=3;
                    attron(COLOR_PAIR(2));
                    mvprintw(a,b+2,"X");
                    attron(COLOR_PAIR(6));
                    mvprintw(a,b+1,"o");
                    attron(COLOR_PAIR(5));
                    mvprintw(a,b," ");
                    push_box_map[a][b+2]=2;
                    push_box_map[a][b+1]=5;
                    push_box_map[a][b]=3;
                    b+=1;
                    count-=1;
                    StepCount();
                    PushCount();
                }
                else if(push_box_map[a][b+2]==3) //상자 목적지에 넣을 때
                {
                    what=3;
                    attron(COLOR_PAIR(8));
                    mvprintw(a,b+2,"X");
                    attron(COLOR_PAIR(7));
                    mvprintw(a,b+1,"o");
                    attron(COLOR_PAIR(3));
                    mvprintw(a,b," ");
                    push_box_map[a][b+2]=2;
                    push_box_map[a][b+1]=5;
                    push_box_map[a][b]=3;
                    b+=1;
                    StepCount();
                    PushCount();
                }
                }
                else if(push_box_map[a][b+1]==1)//목적지에서 벽으로 가려고 할 때
                {
                continue;
                }
            }

            else if(what==0)
            {
                if(push_box_map[a][b+1]==0)//바닥에서 바닥으로 가려고 할 때
                {
                    what=0;
                    attron(COLOR_PAIR(6));
                    mvprintw(a,b+1,"o");
                    attron(COLOR_PAIR(5));
                    mvprintw(a,b," ");
                    push_box_map[a][b+1]=5;
                    push_box_map[a][b]=0;
                    b+=1;
                    StepCount();
                }
                else if(push_box_map[a][b+1]==3)//바닥에서 목적지로 가려고 할 때
                {
                    what=3;
                    attron(COLOR_PAIR(7));
                    mvprintw(a,b+1,"o");
                    attron(COLOR_PAIR(3));
                    mvprintw(a,b," ");
                    push_box_map[a][b+1]=5;
                    push_box_map[a][b]=0;
                    b+=1;
                    StepCount();
                }
                else if(push_box_map[a][b+1]==2)//상자 밀려고 할 때
                {
                if(push_box_map[a][b+2]==2)//상자 연속해서 있을 때
                {
                    continue;
                }
                else if(push_box_map[a][b+2]==1)//상자 뒤에 벽일 때
                {
                    continue;
                }
                else if(push_box_map[a][b+2]==0)//상자 뒤에 바닥일 때
                {
                    what=0;
                    attron(COLOR_PAIR(2));
                    mvprintw(a,b+2,"X");
                    attron(COLOR_PAIR(6));
                    mvprintw(a,b+1,"o");
                    attron(COLOR_PAIR(5));
                    mvprintw(a,b," ");
                    push_box_map[a][b+2]=2;
                    push_box_map[a][b+1]=5;
                    push_box_map[a][b]=0;
                    b+=1;
                    StepCount();
                    PushCount();
                }
                else if(push_box_map[a][b+2]==3) //상자 목적지에 넣을 때
                {
                    what=0;
                    attron(COLOR_PAIR(8));
                    mvprintw(a,b+2,"X");
                    attron(COLOR_PAIR(6));
                    mvprintw(a,b+1,"o");
                    attron(COLOR_PAIR(5));
                    mvprintw(a,b," ");
                    push_box_map[a][b+2]=2;
                    push_box_map[a][b+1]=5;
                    push_box_map[a][b]=0;
                    b+=1;
                    count+=1;
                    StepCount();
                    PushCount();
                }
                }
                else if(push_box_map[a][b+1]==1)//바닥에서 벽으로 가려고 할 때
                {
                continue;
                }
            }
            }

            else if(ch==KEY_UP)
            {
            if(what==3)
            {
                if(push_box_map[a-1][b]==3)//목적지에서 목적지로 가려고 할 때
                {
                    what=3;
                    attron(COLOR_PAIR(7));
                    mvprintw(a-1,b,"o");
                    attron(COLOR_PAIR(3));
                    mvprintw(a,b," ");
                    push_box_map[a-1][b]=5;
                    push_box_map[a][b]=3;
                    a-=1;
                    StepCount();
                }
                else if(push_box_map[a-1][b]==1)//목적지에서 벽으로 가려고 할 때
                {
                continue;
                }
                else if(push_box_map[a-1][b]==0)//목적지에서 바닥으로 가려고 할 때
                {
                    what=0;
                    attron(COLOR_PAIR(6));
                    mvprintw(a-1,b,"o");
                    attron(COLOR_PAIR(3));
                    mvprintw(a,b," ");
                    push_box_map[a][b+1]=5;
                    push_box_map[a][b]=3;
                    a-=1;
                    StepCount();
                }
                else if(push_box_map[a-1][b]==2)//상자 밀려고 할 때
                {
                if(push_box_map[a-2][b]==2)//상자 연속해서 있을 때
                {
                    continue;
                }
                else if(push_box_map[a-2][b]==1)//상자 뒤에 벽일 때
                {
                    continue;
                }
                else if(push_box_map[a-2][b]==0)//상자 뒤에 바닥일 때
                {
                    what=3;
                    attron(COLOR_PAIR(2));
                    mvprintw(a-2,b,"X");
                    attron(COLOR_PAIR(6));
                    mvprintw(a-2,b,"o");
                    attron(COLOR_PAIR(5));
                    mvprintw(a,b," ");
                    push_box_map[a-2][b]=2;
                    push_box_map[a-1][b]=5;
                    push_box_map[a][b]=3;
                    a-=1;
                    count-=1;
                    StepCount();
                    PushCount();
                }
                else if(push_box_map[a-2][b]==3) //상자 목적지에 넣을 때
                {
                    what=3;
                    attron(COLOR_PAIR(8));
                    mvprintw(a-2,b,"X");
                    attron(COLOR_PAIR(7));
                    mvprintw(a-1,b,"o");
                    attron(COLOR_PAIR(3));
                    mvprintw(a,b," ");
                    push_box_map[a-2][b]=2;
                    push_box_map[a-1][b]=5;
                    push_box_map[a][b]=3;
                    a-=1;
                    StepCount();
                    PushCount();
                }
                }
            }
            else if(what==0)
            {
                if(push_box_map[a-1][b]==0)//바닥에서 바닥으로 가려고 할 때
                {
                what=0;
                attron(COLOR_PAIR(6));
                mvprintw(a-1,b,"o");
                attron(COLOR_PAIR(5));
                mvprintw(a,b," ");
                push_box_map[a-1][b]=5;
                push_box_map[a][b]=0;
                a-=1;
                StepCount();
                }
                else if(push_box_map[a-1][b]==3)//바닥에서 목적지로 가려고 할 때
                {
                    what=3;
                    attron(COLOR_PAIR(7));
                    mvprintw(a-1,b,"o");
                    attron(COLOR_PAIR(5));
                    mvprintw(a,b," ");
                    push_box_map[a-1][b]=5;
                    push_box_map[a][b]=0;
                    b+=1;
                    StepCount();
                }
                else if(push_box_map[a-1][b]==2)//상자 옮기려고 할 때
                {
                if(push_box_map[a-2][b]==2)//상자 연속해서 있을 때
                {
                    continue;
                }
                else if(push_box_map[a-2][b]==1)//상자 뒤에 벽일 때
                {
                    continue;
                }
                else if(push_box_map[a-2][b]==0)//상자 뒤에 바닥일 때
                {
                    what=0;
                    attron(COLOR_PAIR(2));
                    mvprintw(a-2,b,"X");
                    attron(COLOR_PAIR(6));
                    mvprintw(a-1,b,"o");
                    attron(COLOR_PAIR(5));
                    mvprintw(a,b," ");
                    push_box_map[a-2][b]=2;
                    push_box_map[a-1][b]=5;
                    push_box_map[a][b]=0;
                    a-=1;
                    StepCount();
                    PushCount();
                }
                else if(push_box_map[a-2][b]==3) //상자 목적지에 넣을 때
                {
                    what=0;
                    attron(COLOR_PAIR(8));
                    mvprintw(a-2,b,"X");
                    attron(COLOR_PAIR(6));
                    mvprintw(a-1,b,"o");
                    attron(COLOR_PAIR(5));
                    mvprintw(a,b," ");
                    push_box_map[a-2][b]=2;
                    push_box_map[a-1][b]=5;
                    push_box_map[a][b]=0;
                    a-=1;
                    count+=1;
                    StepCount();
                    PushCount();
                }
                }
                else if(push_box_map[a-1][b]==1)//바닥에서 벽으로 가려고 할 때
                {
                continue;
                }
            }
            }

            else if(ch==KEY_DOWN)
            {
            if(what==3)
            {
                if(push_box_map[a+1][b]==3)//목적지에서 목적지로 가려고 할 때
                {
                    what=3;
                    attron(COLOR_PAIR(7));
                    mvprintw(a+1,b,"o");
                    attron(COLOR_PAIR(3));
                    mvprintw(a,b," ");
                    push_box_map[a+1][b]=5;
                    push_box_map[a][b]=3;
                    a+=1;
                    StepCount();
                }
                else if(push_box_map[a+1][b]==1)//목적지에서 벽으로 가려고 할 때
                {
                continue;
                }
                else if(push_box_map[a+1][b]==0)//목적지에서 바닥으로 가려고 할 때
                {
                    what=0;
                    attron(COLOR_PAIR(6));
                    mvprintw(a-1,b,"o");
                    attron(COLOR_PAIR(3));
                    mvprintw(a,b," ");
                    push_box_map[a][b+1]=5;
                    push_box_map[a][b]=3;
                    a+=1;
                    StepCount();
                }
                else if(push_box_map[a+1][b]==2)//상자 밀려고 할 때
                {
                if(push_box_map[a+2][b]==2)//상자 연속해서 있을 때
                {
                    continue;
                }
                else if(push_box_map[a+2][b]==1)//상자 뒤에 벽일 때
                {
                    continue;
                }
                else if(push_box_map[a+2][b]==0)//상자 뒤에 바닥일 때
                {
                    what=3;
                    attron(COLOR_PAIR(2));
                    mvprintw(a-2,b,"X");
                    attron(COLOR_PAIR(6));
                    mvprintw(a-2,b,"o");
                    attron(COLOR_PAIR(5));
                    mvprintw(a,b," ");
                    push_box_map[a+2][b]=2;
                    push_box_map[a+1][b]=5;
                    push_box_map[a][b]=3;
                    a+=1;
                    count-=1;
                    StepCount();
                    PushCount();
                }
                else if(push_box_map[a+2][b]==3) //상자 목적지에 넣을 때
                {
                    what=3;
                    attron(COLOR_PAIR(8));
                    mvprintw(a+2,b,"X");
                    attron(COLOR_PAIR(7));
                    mvprintw(a+1,b,"o");
                    attron(COLOR_PAIR(3));
                    mvprintw(a,b," ");
                    push_box_map[a+2][b]=2;
                    push_box_map[a+1][b]=5;
                    push_box_map[a][b]=3;
                    a+=1;
                    StepCount();
                    PushCount();
                }
                }
            }
            else if(what==0)
            {
                if(push_box_map[a+1][b]==2)//바닥에서 상자를 밀려고 할 때
                {
                if(push_box_map[a+2][b]==2)//상자 연속해서 있을 때
                {
                    continue;
                }
                else if(push_box_map[a+1][b]==1)//상자 뒤에 벽일 때
                {
                    continue;
                }
                else if(push_box_map[a+2][b]==0)//상자 뒤에 바닥일 때
                {
                    what=0;
                    attron(COLOR_PAIR(2));
                    mvprintw(a+2,b,"X");
                    attron(COLOR_PAIR(6));
                    mvprintw(a+1,b,"o");
                    attron(COLOR_PAIR(5));
                    mvprintw(a,b," ");
                    push_box_map[a][b]=0;
                    push_box_map[a+1][b]=5;
                    push_box_map[a+2][b]=2;
                    a+=1;
                    StepCount();
                    PushCount();
                }
                else if(push_box_map[a+2][b]==3) //상자 목적지에 넣을 때
                {
                    what=0;
                    attron(COLOR_PAIR(8));
                    mvprintw(a+2,b,"X");
                    attron(COLOR_PAIR(6));
                    mvprintw(a+1,b,"o");
                    attron(COLOR_PAIR(5));
                    mvprintw(a,b," ");
                    push_box_map[a+2][b]=2;
                    push_box_map[a+1][b]=5;
                    push_box_map[a][b]=0;
                    a+=1;
                    count+=1;
                    StepCount();
                    PushCount();
                }
                }
                else if(push_box_map[a+1][b]==0) //바닥에서 바닥으로 가려고 할 때
                {
                    what=0;
                    attron(COLOR_PAIR(6));
                    mvprintw(a+1,b,"o");
                    attron(COLOR_PAIR(5));
                    mvprintw(a,b," ");
                    push_box_map[a+1][b]=5;
                    push_box_map[a][b]=0;
                    a+=1;
                    StepCount();
                }
                else if(push_box_map[a+1][b]==3)//바닥에서 목적지로 가려고 할 때
                {
                    what=3;
                    attron(COLOR_PAIR(7));
                    mvprintw(a+1,b,"o");
                    attron(COLOR_PAIR(5));
                    mvprintw(a,b," ");
                    push_box_map[a+1][b]=5;
                    push_box_map[a][b]=0;
                    a+=1;
                    StepCount();
                }
                else if(push_box_map[a+1][b]==1)//바닥에서 벽으로 가려고 할 때
                {
                continue;
                }
            }
            }
        }
        clear();
        attron(COLOR_PAIR(9));
        printw("LEVEL%d CLEAR\nstep : %d\nmove box : %d",now+1, step,push);

        //KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT
        refresh();
        getch();
        clear();
        endwin();
    }

int main(void){
  ifstream instream;
  instream.open("draw.txt");
  int testnum;
  instream >> testnum;
  for(;now < testnum; now++){

    instream >> row >> col;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            instream >> push_box_map[i][j];
        }
    }
    push = 0;
    step = 0;
    gameManager* game = new gameManager();
    game->DrawMap();
    game->moveGame();
    delete game;
  }
    endwin();
    return 0;
}
