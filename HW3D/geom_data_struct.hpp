#ifndef GEOM_DATA_STRUCT_HPP
#define GEOM_DATA_STRUCT_HPP

#include <iostream>
#include <vector>

//point in form of (x; y; z)
struct point_t {
private:
    std::vector<double> coordinates = {NAN, NAN, NAN};
public:
    point_t(double x, double y, double z) {coordinates[0] = x; 
                                           coordinates[1] = y;
                                           coordinates[2] = z;}

    void print() const {std::cout << "(" << coordinates[0] << "; " 
                                         << coordinates[1] << "; "
                                         << coordinates[2] << ")" << std::endl;}
                                          
    bool valid() const {return !(coordinates[0] != coordinates[0] || 
                                 coordinates[1] != coordinates[1] || 
                                 coordinates[2] != coordinates[2]);}

    bool equal(const point_t &сmp_point) const {return (coordinates == сmp_point.coordinates);}

    void copy(const point_t &dst_point) {coordinates[0] = dst_point.coordinates[0];
                                         coordinates[1] = dst_point.coordinates[1];
                                         coordinates[2] = dst_point.coordinates[2];}

    std::vector<double> value_coordinates() const {return coordinates;}

    point_t operator - (const point_t &point) const {return point_t(coordinates[0] - point.coordinates[0],
                                                                    coordinates[1] - point.coordinates[1],
                                                                    coordinates[2] - point.coordinates[2]);}
};

//                   guide vector
//                        |
//                 (x)   (a)    (x0)
// line in form of (y) = (b)t + (y0)
//                 (z)   (c)    (z0)
//                                |
//                          point of line
struct line_t {
private:
    point_t guide_vector  = {NAN, NAN, NAN};
    point_t point_of_line = {NAN, NAN, NAN};
public:
    line_t(const point_t &point1, const point_t &point2)
    {
        assert (point1.valid() && point2.valid());

        point_of_line.copy(point1);
        guide_vector.copy(point2 - point1);
    }

    void print() const 
    {
        std::vector<double> guide_vector_coord = guide_vector.value_coordinates();
        std::vector<double> point_of_line_coord = point_of_line.value_coordinates();

        std::cout << std::fixed;
        std::cout.precision(3);

        std::cout << "(x)   (" << guide_vector_coord[0] << ")    (" << point_of_line_coord[0] << ")" << std::endl
                  << "(y) = (" << guide_vector_coord[1] << ")t + (" << point_of_line_coord[1] << ")" << std::endl
                  << "(z)   (" << guide_vector_coord[2] << ")    (" << point_of_line_coord[2] << ")" << std::endl;
    }

    bool valid() const {return guide_vector.valid() && point_of_line.valid();}

    bool equal(const line_t &сmp_line) const {return (guide_vector.equal(сmp_line.guide_vector) && 
                                                      point_of_line.equal(сmp_line.point_of_line));}
};

//plane in form of ax+by+cz+d=0
struct plane_t {
private:
    double a = NAN, b = NAN, c = NAN, d = NAN;
public:
    plane_t(const point_t &point1, const point_t &point2, const point_t &point3)
    {
        std::vector<double> p1_coord = point1.value_coordinates();
        std::vector<double> p2_coord = point2.value_coordinates();
        std::vector<double> p3_coord = point3.value_coordinates();

        a = (p2_coord[1] - p1_coord[1])*(p3_coord[2] - p1_coord[2]) - 
            (p3_coord[1] - p1_coord[1])*(p2_coord[2] - p1_coord[2]);
        b = (p2_coord[2] - p1_coord[2])*(p3_coord[0] - p1_coord[0]) -
            (p3_coord[2] - p1_coord[2])*(p2_coord[0] - p1_coord[0]);
        c = (p2_coord[0] - p1_coord[0])*(p3_coord[1] - p1_coord[1]) - 
            (p3_coord[0] - p1_coord[0])*(p2_coord[1] - p1_coord[1]);

        d = (-1)*(a*p1_coord[0] + b*p1_coord[1] + c*p1_coord[2]);
    }

    bool valid() const {return !(a != a || b != b || c != c || d != d);}

    void print() const {std::cout << a << "x + " << b << "y + " << c << "z + " << d << " = 0" << std::endl;}

    bool equal(const plane_t &cmp_plane) const {return (a == cmp_plane.a && 
                                                        b == cmp_plane.b && 
                                                        c == cmp_plane.c && 
                                                        d == cmp_plane.d);}
};

struct polygon_t {
private:
    std::vector<point_t> verteces;
    size_t number_vertices = 0;
public:
    polygon_t(size_t number_vertices_, std::initializer_list<point_t> verteces_) : number_vertices(number_vertices_)
    {
        const point_t* ptr_vertexs = verteces_.begin();

        for (int i = 0; i < number_vertices; i++)
        {
            verteces.push_back(*(ptr_vertexs + i));
        }
    }

    bool valid() const 
    {
        for (int i = 0; i < number_vertices; i++)
        {
            if (!verteces[i].valid()) return false;
        }
        return true;
    }

    void print() const 
    {
        for (int i = 0; i < number_vertices; i++)
        {
            std::vector<double> point = (verteces[i]).value_coordinates();

            std::cout << "(" << point[0] << "; " 
                             << point[1] << "; "
                             << point[2] << ")\t";
        }
    }
};

#endif //GEOM_DATA_STRUCT_HPP