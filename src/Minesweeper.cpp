#include <Minesweeper.h>
#include <Cell.h>

Minesweeper::Minesweeper(){}


Minesweeper::Minesweeper(int x, int y, int bombs){
    row=x;
    col=y;
    numBomb=bombs;
    numFlags=bombs;
    cleared=false;
    blownup=false;
    srand(time(NULL));
    std::vector<Cell> temp;

    for(int i=0; i<row;i++){
        for(int j=0; j<col;j++){
            temp.push_back(Cell());
        }
        Board.push_back(temp);
    }

    bombSeeding();
    neighborhood();
}

void Minesweeper::bombSeeding(){
for(int i=0; i<numBomb;i++){
        bombplace:
        int rc = rand() %col;
        int rr = rand() %row;
        if(Board[rr][rc].isFilled()==false){
            Board[rr][rc].setBomb();
           

        }
        else{
            goto bombplace;
        }
    }
    }

void Minesweeper::neighborhood(){
for(int i=0; i<row;i++){
    for(int j=0; j<col;j++){
        if(Board[i][j].bomb()==false){
        int counter=0;
        if(i==0){
            if(j>0){
                if(Board[i][j-1].bomb()==true){
                    counter++;
                }
            }
            if(j+1<col){
                if(Board[i][j+1].bomb()==true){
                    counter++;
                }
            }/*
            if(Board[i+1][j].bomb()==true){
                counter++;
            }*/
        }
        if(j==0){
           /* if(i==0){
                if(Board[i+1][j].bomb()==true){
                    counter++;
                }
            }*/
            if(i>0){
                if(Board[i-1][j].bomb()==true){
                    counter++;
                }
                
            }
        
            if(i+1<row){
                if(Board[i+1][j].bomb()==true){
                    counter++;
                }
            }
            }/*
            if(i+1<row){
                if(Board[i+1][j].bomb()==true){
                    counter++;
                }
                if(Board[i+1][j+1].bomb()==true){
                    counter++;
                }
            }
            if(i==0){
                if(Board[i][j+1].bomb()==true){
                    counter++;
                }
                if(Board[i+1][j].bomb()==true){
                    counter++;
                }
            }
        }*/
        if(j>0){
            if(i>0){
                if(Board[i-1][j-1].bomb()==true){
                    counter++;
                }
                if(Board[i][j-1].bomb()==true){
                    counter++;
                }
                if(Board[i-1][j].bomb()==true){
                    counter++;
                }
            }
            if(i+1<row){
                if(Board[i+1][j].bomb()==true){
                    counter++;
                }
                if(Board[i+1][j-1].bomb()==true){
                    counter++;
                }
            }

        }
        if(j+1<col){
            if(i>0){
                if(Board[i][j+1].bomb()==true){
                    counter++;
                }
                if(Board[i-1][j+1].bomb()==true){
                    counter++;
                }
            }
            if(i+1<row){
                if(Board[i+1][j+1].bomb()==true){
                    counter++;
                }
            }
        }


    Board[i][j].field(counter);
    }
    }
}



}



    void Minesweeper::reset(){
        for(int i=0; i<row;i++){
            for(int j=0; j<col;j++)
            Board[i][j].reset();
        }
        bombSeeding();
        neighborhood();
        cleared=false;
        blownup=false;
    }

    ucm::json Minesweeper::getBoard(){
        ucm::json result;
        int disposed=0;
        for(int i=0; i<row;i++){
		ucm::json temps;
		for(int j=0; j<col; j++){
            if((Board[i][j].bomb()==true&&Board[i][j].revealed()==true)||Board[i][j].pole()==true){
			temps.push_back(Board[i][j].state());
            if(Board[i][j].state()==10&&Board[i][j].bomb()==true){
                disposed++;
            }
           // if(blownup==true&&Board[i][j].pole()==true&&Board[i][j].bomb()==false){
            //    temps.push_back(11);
            //}
            }
            else if(Board[i][j].bomb()!=true&&Board[i][j].revealed()==true&&Board[i][j].pole()==false){
                if(Board[i][j].path()!=0){
                    temps.push_back(Board[i][j].path());
                    }
                else{
                    temps.push_back(-1);
                }

            }
            
            else{
                temps.push_back(" ");
            }
		}
		result.push_back(temps);
        }
        if(disposed==numBomb){
            cleared=true;
         //   wincon
         //result["message"]=winner;
         for(int i=0; i<row;i++){
                for(int j=0;j<col;j++){
                    Board[i][j].clearPath();
                    //Board[i][j].freeze();
                }
            }
        }


        return result;
    }

    void Minesweeper::sweep(int x, int y){
        if(Board[x][y].bomb()!=true){
            Board[x][y].clearPath();
            if(Board[x][y].path()==0){
            if(x>0){
                if(Board[x-1][y].revealed()==false){
                        sweep(x-1,y);
                }
                
            }
            if(x+1<row){
                if(Board[x+1][y].revealed()==false){
                sweep(x+1,y);
                }
            }
            if(y>0){
                if(Board[x][y-1].revealed()==false){
                sweep(x,y-1);
                }
            }
            if(y+1<col){
                if(Board[x][y+1].revealed()==false){
                sweep(x,y+1);
                }
            }
            }
        }
    }

    void Minesweeper::handle(int x, int y, MouseButton click){
        if(cleared==false&&blownup==false){
        if(click==left&&Board[x][y].bomb()==true&&Board[x][y].pole()==false){
            Board[x][y].boom();
            blownup=true;
            //Board[x][y].clearPath();
            for(int i=0; i<row;i++){
                for(int j=0;j<col;j++){
                    Board[i][j].clearPath();
                }
            }
        }
        if(click==left&&Board[x][y].bomb()==false&&Board[x][y].revealed()==false){
            Board[x][y].clearPath();
            if(Board[x][y].path()==0){
                sweep(x,y);
            }
        }
        if(click==right&&Board[x][y].revealed()==false){
            Board[x][y].setFlag();
        }
        
    std::cout<<x  <<" " << y << " handled"<<std::endl;
        }
    }

    //Minesweeper::~Minesweeper(){}