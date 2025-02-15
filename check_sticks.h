#include "putting_sticks&DFS.h"
#include "subcodes.h"


//////////////////////////////////////////// search to find visited houses
int SearchVisitHouse(int RowDestination,int ColumnDestination ){
    int i;
    for(i=0;i<house.coordinatesNo;i++){
        if(house.location[i].row==RowDestination && house.location[i].column==ColumnDestination){
            return 1;
        }
    }
        return 0;
}
///////////////////////////////////////////////
int DFS_Players(int  Row, int Column,int RowDestination,int ColumnDestination){
    int n,i,lastline;
    if(DFplayer==1){
        lastline=2;
    }else{
        lastline=TotalRows-3;
    }
    if(RowDestination==lastline || lastrow==1 ){
            lastrow=1;
			return 1;
	}else  {
       if(SearchVisitHouse(RowDestination,ColumnDestination )==0){   //search in visited list
          house.location[house.coordinatesNo].row=RowDestination;
           house.location[house.coordinatesNo].column=ColumnDestination;
          house.coordinatesNo++;

            if(board[RowDestination][ColumnDestination+3]==7||board[RowDestination][ColumnDestination+4]==100){
                 if(board[RowDestination-2][ColumnDestination]==100 && board[RowDestination+2][ColumnDestination]==100 ){
                    return 0;
                 }

            }
            else if( board[RowDestination][ColumnDestination+4]!=100){
                 DFS_Players(RowDestination,ColumnDestination,RowDestination,ColumnDestination+8); //move right
            }

            if(board[RowDestination][ColumnDestination-3]==7||board[RowDestination][ColumnDestination-4]==100){
                if(board[RowDestination-2][ColumnDestination]==100 && board[RowDestination+2][ColumnDestination]==100  ){
                     return 0;
                }

            }
            else if(board[RowDestination][ColumnDestination-4]!=100 ){

                 DFS_Players(RowDestination,ColumnDestination,RowDestination,ColumnDestination-8); //move left
             }

            if(board[RowDestination-2][ColumnDestination]==100 || board[RowDestination-2][ColumnDestination]==8  ){
                    if(board[RowDestination+2][ColumnDestination]==100){
                        if(lastrow!=1)return 0;
                    }

                }
            else if(board[RowDestination-2][ColumnDestination]!=100 ){

                   DFS_Players(RowDestination,ColumnDestination,RowDestination-4,ColumnDestination); //move up
            }
            if(board[RowDestination+2][ColumnDestination]==100 || board[RowDestination+2][ColumnDestination]==8){
                   if(lastrow!=1)return 0;
                }
            else{
                 DFS_Players(RowDestination,ColumnDestination,RowDestination+4,ColumnDestination); //move down
            }
		}else {
		     RowDestination= Row;
		    ColumnDestination=Column;
          return 0;
		}
    }
}

int CheckSticksPlayers(char TypeStick){
	char rowlocation,columnlocation;
	int ansDFSplayer1,ansDFSplayer2,coordRow,coordcolumn,i,sw=1;
	int stick, horizontalsticks,verticalsticks;
	int RowDestination,ColumnDestination;
	if (turn==1){

        horizontalsticks=horizontalsticks1;
        verticalsticks=verticalsticks1;
	}else{

         horizontalsticks=horizontalsticks2;
         verticalsticks=verticalsticks2;
	}
	///////////////////////////////////////////////////////////////////Check number of sticks
	if(TypeStick=='H' || TypeStick=='h'  ){
		if(horizontalsticks==0){
			gotoxy(0,35);
			printf("Your number of horizontal sticks is 0");
			 return 0;
		}
	}else{
		if(verticalsticks==0){
			gotoxy(0,35);
			printf("Your number of vertical sticks is 0");
			 return 0;
		}
	}
	if(TypeStick=='H' || TypeStick=='h'  ){
        horizontalsticks--;
	}else{
        verticalsticks--;
	}
	////////////////////////////////////////////////////////////
	gotoxy(0,35);
	printf("Enter the name of the line where you want the stick to be placed!");
	rowlocation=getch();
	gotoxy(0,35);
	printf("Enter the name of the column where you want the stick to be placed!!");
	columnlocation=getch();
	////////////////////////////////////////////////(check harf bashe v dar baze)

            ////////////////////////////////////check full
    ///////////////////////////////convert the position of stick to org coord
    coordRow=((int)rowlocation-64)*4;
	coordcolumn=((int)columnlocation-64)*8-1;

    if(TypeStick=='H' || TypeStick=='h'){
        if(board[coordRow][coordcolumn]==100||board[coordRow][coordcolumn+3]==100||board[coordRow][coordcolumn-3]==100){
            printf("(%c,%c) is full!                                              ",rowlocation,columnlocation);
            sw=0;
            return 0;}
    }
    else if(board[coordRow][coordcolumn]==100||board[coordRow-2][coordcolumn]==100||board[coordRow+2][coordcolumn]==100){
            printf("(%c,%c) is full!                                              ",rowlocation,columnlocation);
            sw=0;
             return 0;
    /////////////////////////////////////////////////////////////// START DFS

	} if(sw==1){
	    house.coordinatesNo=0;
		i=coordcolumn-6;
		if(TypeStick=='H' || TypeStick=='h' ){ /////////ASSUMED WOOD
		i=coordcolumn-6;
		for(i;i<=coordcolumn+6;i++){
				board[coordRow][i]=100;
		}
        }else{
        i=coordRow-3;
		for(i;i<=coordRow+3;i++){
				board[i][coordcolumn]=100;
		}
    }
    ///////////////////////////////////////////// find a neighborhood p1
        if(board[row1-2][column1]!=100 && board[row1-2][column1]!=8 ){
            RowDestination=row1-4;
            ColumnDestination=column1;
        }else if(board[row1][column1+4]!=100 && board[row1][column1+4]!=7){
            RowDestination=row1;
            ColumnDestination=column1+8;
        }else if(board[row1][column1-4]!=100 && board[row1][column1+4]!=7 ){
            RowDestination=row1;
            ColumnDestination=column1-8;
        }else if(board[row1+2][column1]!=100 && board[row1+2][column1]!=8){
             RowDestination=row1+4;
            ColumnDestination=column1;
        }
        /////////////////////////////////////////check DFS player 1
        DFplayer=1;
         lastrow=0;
		ansDFSplayer1=DFS_Players(row1,column1,RowDestination,ColumnDestination);
		gotoxy(200,0);
        if(lastrow==1){
            ansDFSplayer1=1;
        }else{
            ansDFSplayer1=0;
        }

       ///////////////////////////////////////////// find a neighborhood p2
        if(board[row2-2][column2]!=100 && board[row2-2][column2]!=8){
            RowDestination=row2-4;
            ColumnDestination=column2;
        }else if(board[row2][column2+4]!=100 && board[row2][column2+4]!=7 ){
            RowDestination=row2;
            ColumnDestination=column2+8;
        }else if(board[row2][column2-4]!=100 && board[row2][column2-4]!=7){
            RowDestination=row2;
            ColumnDestination=column2-8;
        }else if(board[row2+2][column2]!=100 && board[row2+2][column2]!=8){
             RowDestination=row2+4;
            ColumnDestination=column2;
        }
          ////////////////////////////////////////check DFS player 2
        house.coordinatesNo=0;
        DFplayer=2;
        lastrow=0;
        ansDFSplayer2=DFS_Players(row2,column2,RowDestination,ColumnDestination);
        gotoxy(201,0);
        if(lastrow==1){
            ansDFSplayer2=1;
        }else{
            ansDFSplayer2=0;
        }
        lastrow==0;
        ///////////////////////////////////////////////////// close roads
		if(ansDFSplayer1==0 ||ansDFSplayer2==0){
			gotoxy(4,35);
			printf("By putting stick in (%c,%c) you will close all the roads!",rowlocation,columnlocation);
			/////////////////////////////////////////// remove assumed wood
			i=coordcolumn-6;
            if(TypeStick=='H' || TypeStick=='h' ){
                i=coordcolumn-6;
                for(i;i<=coordcolumn+6;i++){
                    board[coordRow][i]=0;
                }
            }else{
                i=coordRow-3;
                for(i;i<=coordRow+3;i++){
                    board[i][coordcolumn]=0;
            }
        }
        return 0;
        ///////////////////////////////////////////////////
		}if(ansDFSplayer1==1&&ansDFSplayer2==1){ //ok all of things
		    return 1;
		}
	}
}
