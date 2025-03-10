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

class Circle
{
private:
    Point center;
    double radius;

public:
    Circle()
    {
        /*  
         * STUDENT ANSWER   
         * TODO: set zero center's x-y and radius
         */
        center = Point();
        radius = 0;
    }

    Circle(Point center, double radius)
    {
        /*  
         * STUDENT ANSWER
         */
         this -> center = center;
         this -> radius = radius;
    }

    Circle(const Circle &circle)
    {
        /*  
         * STUDENT ANSWER
         */
         this -> center = circle.center;
         this -> radius = circle.radius;
         
    }
    
    void setCenter(Point point)
    {
        /*  
         * STUDENT ANSWER
         */
         this -> center = point;
        
    }

    void setRadius(double radius)
    {
        /*  
         * STUDENT ANSWER
         */
        this -> radius = radius;
    }

    Point getCenter() const
    {
        /*  
         * STUDENT ANSWER
         */
         return center;
    }

    double getRadius() const
    {
        /*  
         * STUDENT ANSWER
         */
        return radius;
    }
    
    void printCircle()
    {
        printf("Center: {%.2f, %.2f} and Radius %.2f\n", this->center.getX(), this->center.getY(), this->radius);
    }
};
