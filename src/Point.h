/*
 * Point.h
 * Copyright (C) 2014 Florian Leprince <floleprince@gmail.com>
 *
 * Distributed under terms of the GNU GPL V2 license.
 */

#ifndef __POINT_H__
#define __POINT_H__

#include <vector>
#include <iostream>

using namespace std;

namespace Gaia {
    class Segment;

    class Point{
        public:
            Point();
            Point(Point* A, Point* B);
            ~Point();
            void Display(ostream& O) const;
            void setCartesian(double _x, double _y, double _z);
            void setSpherical(double _p, double _a, double _r);
            void Draw();
            bool isViewableFrom(Point* pcam);
            void AddSegment(Segment* s);
            void RemoveSegment(Segment* s);
            Segment* FindLink(Point* p);
            double getx();
            double gety();
            double getz();

        private:
            double x, y, z;
            double p, a, r;
            vector<Segment*> segments;
    };

    ostream& operator<<(ostream& O, Point const& P);
}

#endif /* __POINT_H__ */
