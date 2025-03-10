class Point
{
private:
    double x, y;

public:
    Point()
    {
        /*  
         * STUDENT ANSWER   
         * TODO: set zero x-y coordinate
         */
        x = 0.0;
        y = 0.0;
    }

    Point(double x, double y)
    {
        /*  
         * STUDENT ANSWER
         */
        this -> x = x;
        this -> y = y;
    }

    void setX(double x)
    {
        /*  
         * STUDENT ANSWER
         */
        this -> x = x;
    }

    void setY(double y)
    {
        /*  
         * STUDENT ANSWER
         */
        this -> y = y;
    }

    double getX() const
    {
        /*  
         * STUDENT ANSWER
         */
         return x;
    }

    double getY() const
    {
        /*  
         * STUDENT ANSWER
         */
         return y;
    }

    double distanceToPoint(const Point& pointA)
    {
        /*  
         * STUDENT ANSWER   
         * TODO: calculate the distance from this point to point A in the coordinate plane
         */
         return sqrt(pow(getX() - pointA.x , 2) + pow(getY() - pointA.y, 2));
    }
};
