#ifndef MYCELL
#define MYCELL

class Cell{

public:

Cell();
Cell(const Cell&);
int neighbor;
int status;
bool filled;
bool bomber;
bool flag;
bool peekabo;
bool ground;
bool keeper();
void reset();
int state() const;
bool bomb();
bool pole() const;
void setBomb();
void setFlag();
void boom();
void clearPath();
int path() const;
void field(int);
bool isFilled();
bool revealed();
void removeFlag();
//void freeze();









};


#endif