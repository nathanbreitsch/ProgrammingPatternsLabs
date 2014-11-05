#include <iostream>
using std::cout; using std::endl;

class LegacyRectangle{
public:
    LegacyRectangle(int x1, int y1, int x3, int y3): 
        x1_(x1), y1_(y1), x3_(x3), y3_(y3){}
    void oldDraw(){
        for(int i=0; i < y3_; ++i){
            for(int j=0; j < x3_; ++j){
                if(y1_ <= i && x1_ <= j){
                    cout << '*';
                }
                else{
                    cout << ' ';
                }
            }
            cout << endl;
        }
    }
    
    void move(int x1, int y1, int x3, int y3){
        x1_ = x1;
        y1_ = y1;
        x3_ = x3;
        y3_ = y3;
    }
    
    int getX1(){
        return x1_;
    }
    
    int getY1(){
        return y1_;
    }
    
    int getX3(){
        return x3_;
    }
        
    int getY3(){
        return y3_;
    }

private: // defining top/left and bottom/right coordinates 
    int x1_;
    int y1_;
    int x3_;
    int y3_;
};

class Square{
public:
    virtual int size() = 0;
    virtual void resize(int newSize) = 0;
    virtual void draw() = 0;
};

class SquareAdapter : public Square, private LegacyRectangle{
public:
    SquareAdapter(int size): LegacyRectangle(0,0,size,size){};
    
    int size(){
        return getX3() - getX1();
    }
    
    void resize(int newSize){
       move(getX1(), getY1(), getX1() + newSize, getY1() + newSize);
    }
    
    void draw(){
        oldDraw();
    }
};

int main(){
    Square* square = new SquareAdapter(10);
    square->draw();
    int currentSize = square->size();
    cout << "old size: " << currentSize << endl;
    square->resize(currentSize * 2);
    cout << "new size: " << square->size() << endl;
    square->draw();
}