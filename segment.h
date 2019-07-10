#ifndef SEGMENTH
#define SEGMENTH

using namespace std;

class segment{
    public:
        segment() {}
        segment(vec3 point1, vec3 point2) : point1(point1), point2(point2){};
        bool static segment_intersection(const segment& s_1, const segment& s_2);
        vec3 point1;
        vec3 point2;
};

int orientation2D(const vec3& a, const vec3& b, const vec3& c){
    vec3 p1, p2;
    p1 = b - a;
    p2 = c - a;

    int cross_product = p1.x() * p2.y() - p1.y() * p2.x();

    if(cross_product > 0){
        return 1; // Left orientation, counter clockwise direction
    }
    else if(cross_product < 0){
        return 0; // Right orientation, clockwise direction
    }
    else{
        return -1; // Colinear points
    }
}

bool between2D(const vec3& test, const vec3& p1, const vec3& p2){
    return (min(p1.x(), p2.x()) <= test.x()) && test.x() <= max(p1.x(), p2.x()) && min(p1.y(), p2.y()) <= test.y() && test.y() <= max(p1.y(), p2.y());
}


bool segment::segment_intersection(const segment& s_1, const segment& s_2){
        // orientation of the (self.point2, self.point1, s_2.point2) triangle
        int s_1_orientation_point2 = orientation2D(s_1.point2, s_1.point1, s_2.point2);

        // orientation of the (self.point2, self.point1, s_2.point1) triangle
        int s_1_orientation_point1 = orientation2D(s_1.point2, s_1.point1, s_2.point1);

        // orientation of the (s_2.point2, s_2.point1, self.point2) triangle
        int s_2_orientation_point2 = orientation2D(s_2.point2, s_2.point1, s_1.point2);

        //orientation of the (s_2.point2, s_2.point1, self.point1) triangle
        int s_2_orientation_point1 = orientation2D(s_2.point2, s_2.point1, s_1.point1);

        // general case
        if (s_1_orientation_point2 != s_1_orientation_point1 && s_2_orientation_point2 != s_2_orientation_point1)
            return true;

        // collinear case
        if (s_1_orientation_point2 == 0 && s_1_orientation_point1 == 0 && s_2_orientation_point2 == 0 && s_2_orientation_point1 == 0)
        {
            if (between2D(s_1.point2, s_2.point1, s_2.point2) || between2D(s_1.point1, s_2.point1, s_2.point2) || between2D(s_2.point2, s_1.point1, s_1.point2) || between2D(s_2.point1, s_1.point1, s_1.point2))
                return true;
        }
        return false;
}

#endif // SEGMENTH
