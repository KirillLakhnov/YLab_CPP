#include "geom_data_struct.hpp"

int main ()
{
    point_t p1(1,2,3);
    point_t p2(3,4,5);
    point_t p3(5,7,8);

    //p1.print();
    //p2.print();
    //p3.print();

    //plane_t plane(p1, p2, p3);

    //plane.print();

    //line_t line1(p1, p2);
    //line_t line2(p1, p2);
    //line_t line3(p1, p3);

    polygon_t polygon(3, {p1, p2, p3});

    polygon.print();

    return 0;
}