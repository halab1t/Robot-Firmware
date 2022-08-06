#ifndef EDGE_DETECTION_H
#define EDGE_DETECTION_H
class EdgeDetection
{
private:
    EdgeDetection(int leftPin, int rightPin1, int rightPin2);
    int leftPin;
    int rightPin1;
    int rightPin2;
    static EdgeDetection instance;
public:
    static EdgeDetection GetEdgeDetection();
    int GetEDError();
    bool OverTheEdge();
    
};

#endif