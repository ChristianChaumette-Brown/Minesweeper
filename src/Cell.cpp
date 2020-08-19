#include <Cell.h>

Cell::Cell(){
    status=0;
    bomber=false;
    neighbor=0;
    filled=false;
    flag=false;
    peekabo=false;
    ground=true;


}

Cell::Cell(const Cell&other){
    status=other.status;
    bomber=other.bomber;
    neighbor=other.bomber;
    filled=other.filled;
    flag=other.flag;
    peekabo=other.peekabo;
    ground=other.ground;
}

void Cell::reset(){
    status=0;
    bomber=false;
    neighbor=0;
    filled=false;
    flag=false;
    peekabo=false;
    ground=true;


}
int Cell::state()const{
    return status;
}

void Cell::field(int x){
    neighbor=x;
}

bool Cell::isFilled(){
    if(filled==true){
        return true;
    }
    else{
        return false;
    }

}

bool Cell::bomb(){

    if(isFilled()==true){

    
    if(bomber==true){
        return true;
    }
    else {
        return false;
    }
    }
    else {
    return false;
    }
    
}

void Cell::setBomb(){
bomber=true;
filled=true;
status=9;
ground=false;


}

int Cell::path()const {
    return neighbor;
}

bool Cell::pole() const{
    return flag;
}


void Cell::setFlag(){
    if(flag==false)
    {
    flag=true;
    status=10;
    //peekabo=true;
    ground=false;
    if(bomb()==true){
        status=10;
    }
    //else{
    //    status=11;
    //}
    }
    else{
        flag=false;
        //peekabo=false;
        //status=0;
        if(bomb()==true){
            status=9;
        }
        if(bomber==true){
            ground=false;
        }
        else{
            ground=true;
        }
    }
}
void Cell::removeFlag(){
    flag=false;
    //peekabo=false;
    if(bomber==true){
        status=9;
    }
   // else{
   //     status=0;
   // }
}

void Cell::boom(){
    status=12;
}

void Cell::clearPath(){
    peekabo=true;
}

bool Cell::revealed(){
    return peekabo;
}

//void Cell::freeze(){
   // status=13;
//}

bool Cell::keeper(){
return ground;
}