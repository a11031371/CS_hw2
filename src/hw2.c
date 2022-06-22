#include <stdio.h>
#include <string.h>
int map[11][11];//儲存棋盤、玩家、木板、牆壁位置
int onedone=0;
int twodone=0;
int end=0;
int w1=2,w2=2;//兩玩家木板數量
/////////////////////////////////////////////////////////
void information(void);
void start(void);
void playersinput(int a);
void change(int r,int c,int row,int column);
int move(int p,int r,int c);
int turnint(char x);
int place(int p,int b1,int b2,int w1,int w2,int wt);
void outputmap(void);
int gameover(void);
void puthorizontal(int p,int b1,int b2,int w1,int w2);
void putvertical(int p,int b1,int b2,int w1,int w2);
//////////////////////declaration////////////////////////
void information(void){
	printf("\n\033[35m\033[1m*****************遊戲資訊*****************\033[0m");
	printf("\n\033[33m\033[1m*******************規則*******************\033[0m");
	printf("\n\033[1m 2位玩家將在5*5棋盤上進行遊戲，利用指令使\033[0m");
	printf("\n\033[1m 自己的棋子移動，並放置木板於格子中央阻擋\033[0m");
	printf("\n\033[1m 對手，最先到達終點線的玩家即獲得勝利\033[0m");
	printf("\n\033[33m\033[1m*****************指令說明*****************\033[0m");
	printf("\n\033[1m         移動指令：\033[33m m [棋盤位置]\033[0m");
	printf("\n\033[1m         \033[33m\033[1m移動範例：  \033[36m\033[1mm C-3\033[0m");
	printf("\n\033[1m         棋子移至第 C 行第 3 欄\n\033[0m");
	printf("\n\033[1m         放置指令：\033[33mp [格線][位置]\033[0m");
	printf("\n\033[1m         \033[33m\033[1m放置範例1：\033[36m p 3-2 B-C\033[0m");
	printf("\n\033[1m         放置木板在欄位編號 3 和\033[0m");
	printf("\n\033[1m          2 之間的格線上，佔據的\033[0m");
	printf("\n\033[1m         位置為第 B 和 C 行\033[0m");
	printf("\n\033[1m         \033[33m\033[1m放置範例2：\033[36m\033[1m p E-D 1-2\033[0m");
	printf("\n\033[1m         放置木板在行數編號 E 和\033[0m");
	printf("\n\033[1m          D 之間的格線上，佔據的\033[0m");
	printf("\n\033[1m         位置為第 1 和 2 欄\n\033[0m");
	printf("\n\033[31m\033[1m*注意： \033[33m\033[1m放置木板不可使任一玩家無法到達終點\033[0m");
    printf("\n\033[35m\033[1m******************************************\033[0m");
}
//遊戲資訊
void start(void){
	int i,j;
    map[7][1]=1;
    map[3][9]=2;
	for(i=0;i<=10;i++){
		for(j=0;j<=10;j++){
			if((i==0)||(i==10)||(j==0)||(j==10)){map[i][j]=7;}
		}
	}
    printf("\033[33m\033[1m         歡迎進入簡易Quoridor遊戲\n\033[0m");
    information();
    outputmap();
}
//設定牆壁、玩家位置初始值及遊戲資訊
void playersinput(int a){//傳入玩家位置
    char input[9];
    char cref[5]={'A','B','C','D','E'};
    char nref[5]={'1','2','3','4','5'};
    int mrow=0;
    int mclm=0;
	onedone=0;
	twodone=0;
	int x,y;
	int row,column;
    if(a==1)printf("\033[1m玩家1請輸入指令：\033[0m");
    if(a==2)printf("\033[1m玩家2請輸入指令：\033[0m");
    gets(input);
    int len=strlen(input);
	for(x=0;x<=10;x++){
	for(y=0;y<=10;y++){
		if(a==1){
			if(map[x][y]==1){
				row=x;
				column=y;
				break;
			}
		}
		if(a==2){
			if(map[x][y]==2){
				row=x;
				column=y;
				break;
			}
		}
	}
	}
	//玩家現在位置
    if(len==5){
        if(input[0]=='m'&&input[1]==' '&&input[3]=='-'){
            int i;
            for(i=0;i<=4;i++){
                if(input[2]==cref[i])mrow++;
                if(input[4]==nref[i])mclm++;
            }
            if(mrow==1&&mclm==1){
				int rr=turnint(input[2]);
				int cc=turnint(input[4]);
                int mv=move(a,rr,cc);//判斷能否移動
				if(mv==1)printf("\033[31m\033[1m木板阻擋，請重新輸入指令\n\033[0m");
				else if(mv==2){
					if(a==1)printf("\033[31m\033[1m此處為玩家一所在位置，請重新輸入指令\n\033[0m");
					if(a==2)printf("\033[31m\033[1m此處為玩家二所在位置，請重新輸入指令\n\033[0m");
				}
				else if(mv==3)printf("\033[31m\033[1m此處無法到達，請重新輸入指令\n\033[0m");
				//由回傳值判斷能否移動並判斷情形
				else{
						change(rr,cc,row,column);//移動
                        outputmap();
                        int end2=gameover();
                        if(end2==1){
                            printf("\033[36m\033[1m玩家1到達終點，遊戲結束\n\033[0m");
                            exit(0);
                        }
                        if(end2==2){
                            printf("\033[36m\033[1m玩家2到達終點，遊戲結束\n\033[0m");
                            exit(0);
                        }
                        if(a==1)onedone=1;
                        if(a==2)twodone=1;
						//成功移動後跳出迴圈

                }
            }//判斷輸入指令是否正確
            else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}
        }
		else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}//判斷輸入指令是否正確
    }
    if(len==9){
        int plc1=0,plc2=0;
        int plce1=0,plce2=0;
        if(input[0]=='p'&&input[1]==' '&&input[5]==' '&&input[3]=='-'&&input[7]=='-'){
            switch(input[2]){
                case 'A':
                    if(input[4]=='B')plc1=1;
                    else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}
                    break;
                case 'B':
                    if(input[4]=='A'||input[4]=='C')plc1=1;
                    else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}
                    break;
                case 'C':
                    if(input[4]=='B'||input[4]=='D')plc1=1;
                    else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}
                    break;
                case 'D':
                    if(input[4]=='C'||input[4]=='E')plc1=1;
                    else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}
                    break;
                case 'E':
                    if(input[4]=='D')plc1=1;
                    else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}
                    break;
                case '1':
                    if(input[4]=='2')plc2=1;
                    else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}
                    break;
                case '2':
                    if(input[4]=='1'||input[4]=='3')plc2=1;
                    else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}
                    break;
                case '3':
                    if(input[4]=='2'||input[4]=='4')plc2=1;
                    else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}
                    break;
                case '4':
                    if(input[4]=='3'||input[4]=='5')plc2=1;
                    else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}
                    break;
                case '5':
                    if(input[4]=='4')plc2=1;
                    else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}
                    break;
                default:
                    printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");
                    break;
            }//判斷輸入指令是否正確
          switch(input[6]){
                case 'A':
                    if(input[8]=='B')plce1=1;
                    else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}
                    break;
                case 'B':
                    if(input[8]=='A'||input[8]=='C')plce1=1;
                    else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}
                    break;
                case 'C':
                    if(input[8]=='B'||input[8]=='D')plce1=1;
                    else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}
                    break;
                case 'D':
                    if(input[8]=='C'||input[8]=='E')plce1=1;
                    else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}
                    break;
                case 'E':
                    if(input[8]=='D')plce1=1;
                    else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}
                    break;
                case '1':
                    if(input[8]=='2')plce2=1;
                    else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}
                    break;
                case '2':
                    if(input[8]=='1'||input[8]=='3')plce2=1;
                    else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}
                    break;
                case '3':
                    if(input[8]=='2'||input[8]=='4')plce2=1;
                    else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}
                    break;
                case '4':
                    if(input[8]=='3'||input[8]=='5')plce2=1;
                    else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}
                    break;
                case '5':
                    if(input[8]=='4')plce2=1;
                    else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}
                    break;
                default:
                    printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");
                    break;
            }//判斷輸入指令是否正確
          if((plc1==1&&plce2==1)||(plc2==1&&plce1==1)){
              if((a==1&&w1>0)||(a==2&&w2>0)){
			    int xx=turnint(input[2]);
			    int yy=turnint(input[4]);
			    int zz=turnint(input[6]);
			    int uu=turnint(input[8]);
			    int walltype;//木板型態(橫或直)
			    if(plc1==1&&plce2==1)walltype=0;
			    if(plc2==1&&plce1==1)walltype=1;
				int canplace=place(a,xx,yy,zz,uu,walltype);//判斷放置位置有無違規
                if(canplace==1){
                    if(walltype==0)puthorizontal(a,xx,yy,zz,uu);
                    if(walltype==1)putvertical(a,xx,yy,zz,uu);
                }//放置木板
                outputmap();
                if(a==1&&onedone==1)w1--;
                if(a==2&&twodone==1)w2--;
				//紀錄剩餘木板數量
              }
              else{printf("已無木板，請重新輸入移動指令\n");}
          }//判斷輸入指令是否正確
        }
        else{printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");}
    }
    if(len!=5&&len!=9)printf("\033[31m\033[1m輸入錯誤，請重新輸入\n\033[0m");
}
//回合function，包含整個執行流程
void change(int r,int c,int row,int column){//傳入使用者欲移動位置及使用者實際位置
	int temp;
	temp=map[row][column];
	map[row][column]=map[r][c];
	map[r][c]=temp;
}
//移動(交換位置)
int move(int p,int r,int c){//傳入玩家1或2及使用者欲移動位置
	int i,j;
	int left=0,right=0,up=0,down=0;
	int row,column;
    if(p==1){//玩家1
		for(i=0;i<=10;i++){
			for(j=0;j<=10;j++){
				if(map[i][j]==1){
					row=i;
					column=j;
					break;
				}
			}
		}//判斷現在位置
		if(c-column<0)left=1;
		if(c-column>0)right=1;
		if(r-row<0)up=1;
		if(r-row>0)down=1;//判斷使用者欲移動位置與現在位置相對方位
		if(left+right+up+down==1){
			if(left==1){//正左方
				if(column-c==2){
					if(map[row][column-1]==4)return 1;//return 1：判斷有無木板阻擋
					else if(map[row][column-2]==2)return 2;//return 2：判斷使用者欲移動位置是否有另一玩家
					else{return 0;}//return 0：無違規
				}
                else if(column-c==4&&map[row][column-2]==2){
					if(map[row][column-1]==4||map[row][column-3]==4)return 1;
					else{return 0;}
				}
                else{return 3;}//return 3：超出該方位移動範圍
			}
			//下方return值所代表意義相同
			if(right==1){//正右方
				if(c-column==2){
					if(map[row][column+1]==4)return 1;
					else if(map[row][column+2]==2)return 2;
					else{return 0;}
				}
                else if(c-column==4&&map[row][column+2]==2){
					if(map[row][column+1]==4||map[row][column+3]==4)return 1;
					else{return 0;}
				}
                else{return 3;}
			}
			if(up==1){//正上方
				if(row-r==2){
					if(map[row-1][column]==3)return 1;
					else if(map[row-2][column]==2)return 2;
					else{return 0;}
				}
                else if(row-r==4&&map[row-2][column]==2){
					if(map[row-1][column]==3||map[row-3][column]==3)return 1;
					else{return 0;}
				}
                else{return 3;}
			}
			if(down==1){//正下方
				if(r-row==2){
					if(map[row+1][column]==3)return 1;
					else if(map[row+2][column]==2)return 2;
                    else{return 0;}
				}
                else if(r-row==4&&map[row+2][column]==2){
					if(map[row+1][column]==3||map[row+3][column]==3)return 1;
					else{return 0;}
				}
                else{return 3;}
			}
		}
		if(left+right+up+down==2){
			if(left+up==2){//左上方
				if(column-c==2&&row-r==2){
					if((map[row][column-3]==4||map[row][column-3]==7&&map[row][column-2]==2&&map[row-1][column-2]!=3)||(map[row-3][column]==3||map[row-3][column]==7&&map[row-2][column]==2&&map[row-2][column-1]!=4))
					{return 0;}
                    else{return 3;}
				}
				else{return 3;}
			}
			if(up+right==2){//右上方
				if(c-column==2&&row-r==2){
					if((map[row][column+3]==4||map[row][column+3]==7&&map[row][column+2]==2&&map[row-1][column+2]!=3)||(map[row-3][column]==3||map[row-3][column]==7&&map[row-2][column]==2&&map[row-2][column+1]!=4))
			        {return 0;}
                    else{return 3;}
				}
				else{return 3;}
			}
			if(right+down==2){//右下方
				if(r-row==2&&c-column==2){
					if((map[row][column+3]==4||map[row][column+3]==7&&map[row][column+2]==2&&map[row+1][column+2])!=3||(map[row+3][column]==3||map[row+3][column]==7&&map[row+2][column]==2&&map[row+2][column+1]!=4))
					{return 0;}
                    else{return 3;}
				}
				else{return 3;}
			}
			if(down+left==2){//左下方
				if(r-row==2&&column-c==2){
					if((map[row][column-3]==4||map[row][column-3]==7&&map[row][column-2]==2&&map[row+1][column-2]!=3)||(map[row+3][column]==3||map[row][column-3]==7&&map[row+2][column]==2&&map[row+2][column-1]!=4))
					{return 0;}
                    else{return 3;}
				}
				else{return 3;}
			}
		}
	}

	if(p==2){//玩家2(判斷方式同玩家1)
	for(i=0;i<=10;i++){
		for(j=0;j<=10;j++){
			if(map[i][j]==2){
				row=i;
				column=j;
				break;
			}
		}
	}
	if(c-column<0)left=1;
	if(c-column>0)right=1;
	if(r-row<0)up=1;
	if(r-row>0)down=1;
	if(left+right+up+down==1){
		if(left==1){
			if(column-c==2){
				if(map[row][column-1]==4)return 1;
				else if(map[row][column-2]==1)return 2;
				else{return 0;}
			}
			if(column-c==4&&map[row][column-2]==1){
				if(map[row][column-1]==4||map[row][column-3]==4)return 1;
				else{return 0;}
			}
		}
		if(right==1){
			if(c-column==2){
				if(map[row][column+1]==4)return 1;
				else if(map[row][column+2]==1)return 2;
				else{return 0;}
			}
			if(c-column==4&&map[row][column+2]==1){
				if(map[row][column+1]==4||map[row][column+3]==4)return 1;
				else{return 0;}
			}
		}
		if(up==1){
			if(row-r==2){
				if(map[row-1][column]==3)return 1;
				else if(map[row-2][column]==1)return 2;
                else{return 0;}
			}
			if(row-r==4&&map[row-2][column]==1){
				if(map[row-1][column]==3||map[row-3][column]==3)return 1;
				else{return 0;}
			}
		}
		if(down==1){
			if(r-row==2){
				if(map[row+1][column]==3)return 1;
				else if(map[row+2][column]==1)return 2;
				else{return 0;}
			}
			if(r-row==4&&map[row+2][column]==1){
				if(map[row+1][column]==3||map[row+3][column]==3)return 1;
				else{return 0;}
			}
		}
	}
	if(left+right+up+down==2){
		if(left+up==2){
			if(column-c==2&&row-r==2){
				if((map[row][column-3]==4&&map[row][column-2]==1&&map[row-1][column-2]!=3)||(map[row-3][column]==3&&map[row-2][column]==1&&map[row-2][column-1]!=4))
				{return 0;}
                else{return 3;}
			}
			else{return 3;}
		}
		if(up+right==2){
			if(column-c==2&&r-row==2){
				if((map[row][column+3]==4&&map[row][column+2]==1&&map[row-1][column+2]!=3)||(map[row-3][column]==3&&map[row-2][column]==1&&map[row-2][column+1]!=4))
				{return 0;}
                else{return 3;}
			}
			else{return 3;}
		}
		if(right+down==2){
			if(r-row==2&&c-column==2){
				if((map[row][column+3]==4&&map[row][column+2]==1&&map[row+1][column+2]!=3)||(map[row+3][column]==3&&map[row+2][column]==1&&map[row+2][column+1]!=4))
				{return 0;}
                else{return 3;}
			}
			else{return 3;}
		}
		if(down+left==2){
			if(r-row==2&&column-c==2){
				if((map[row][column-3]==4&&map[row][column-2]==1&&map[row+1][column-2]!=3)||(map[row+3][column]==3&&map[row+2][column]==1&&map[row+2][column-1]!=4))
				{return 0;}
                else{return 3;}
			}
			else{return 3;}
		}
	}
	}
}
//判斷移動條件
int turnint(char x){
	if(x=='A'||x=='1')return 1;
	if(x=='B'||x=='2')return 3;
	if(x=='C'||x=='3')return 5;
	if(x=='D'||x=='4')return 7;
	if(x=='E'||x=='5')return 9;
}
//將指令轉為Array位置實際值
void puthorizontal(int p,int b1,int b2,int w1,int w2){//傳入玩家1或2及使用者欲放置木板位置
	int b=(b1+b2)/2;
	int w=(w1+w2)/2;
		map[b][w1]=map[b][w2]=3;
		map[b][w]=5;
		if(p==1)onedone=1;
		if(p==2)twodone=1;
}
//放置橫木板
void putvertical(int p,int b1,int b2,int w1,int w2){//傳入玩家1或2及使用者欲放置木板位置
	int b=(b1+b2)/2;
	int w=(w1+w2)/2;
		map[w1][b]=map[w2][b]=4;
		map[w][b]=6;
		if(p==1)onedone=1;
		if(p==2)twodone=1;
}
//放置直木板
int place(int p,int b1,int b2,int w1,int w2,int wt){//傳入玩家1或2及使用者欲放置木板位置及型態
	int b=(b1+b2)/2;
	int w=(w1+w2)/2;
    if(wt==0){//橫木板
	    if(map[b][w]!=5&&map[b][w]!=6){
            if(map[b][w1]!=3&&map[b][w2]!=3)return 1;//return 1：可放置(下方同)
            else{return 0;}//return 0：不可放置(下方同)
        }
        else{return 0;}
    }
    if(wt==1){//直木板
        if(map[w][b]!=5&&map[w][b]!=6){
            if(map[w1][b]!=4&&map[w2][b]!=4)return 1;
            else{return 0;}
	    }
        else{return 0;}
    }
}
//判斷是否可以放置木板
void outputmap(void){
    int i,j;
    printf("\n");
    for(i=0;i<=10;i++){
        switch(i){
            case 1:
                printf("\033[33m\033[1mA \033[0m");
                break;
            case 3:
                printf("\033[33m\033[1mB \033[0m");
                break;
            case 5:
                printf("\033[33m\033[1mC \033[0m");
                break;
            case 7:
                printf("\033[33m\033[1mD \033[0m");
                break;
            case 9:
                printf("\033[33m\033[1mE \033[0m");
                break;
            default:
                printf("  ");
                break;
        }
        for(j=0;j<=10;j++){
            if(map[i][j]==1){
                printf("\033[33m\033[1m ● \033[0m");
            }
            else if(map[i][j]==2){
                printf("\033[33m\033[1m ○ \033[0m");
            }
            else if(map[i][j]==3){
                printf("\033[35m\033[1m═══\033[0m");
            }
            else if(map[i][j]==4||map[i][j]==6){
                printf("\033[34m\033[1m║\033[0m");
            }
            else if(map[i][j]==5){
                printf("\033[35m\033[1m═\033[0m");
            }
            else{
                if(i%2==0&&j%2==1){
                    printf("\033[1m═══\033[0m");
                }
                if(i%2==1&&j%2==0){
                    printf("\033[1m║\033[0m");
                }
                if(i%2==1&&j%2==1){
                    printf("\033[1m   \033[0m");
                }
                if(i%2==0&&j%2==0){
                    printf("\033[1m□\033[0m");
                }
            }
			//依Array值判斷輸出map
        }
        printf("\n");
    }
    printf("\033[33m\033[1m    1   2   3   4   5   \n\033[0m");
}
//輸出地圖
int gameover(void){
    int i;
    for(i=1;i<=9;i+=2){
        if(map[i][9]==1)return 1;//return 1：玩家1獲勝
        else if(map[i][1]==2)return 2;//return 2：玩家2獲勝
    }
}
//判斷遊戲是否結束
int main(void){
    start();//設定初始值及遊戲資訊
    while(end==0){
		while(onedone==0)playersinput(1);//玩家1回合
		while(twodone==0)playersinput(2);//玩家2回合
    }//infinite loop
    return 0;
}
//main
