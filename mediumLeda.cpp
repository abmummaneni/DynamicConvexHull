#include <climits>
#include <vector>
#include <algorithm>
#include <LEDA/graphics/window.h>
#include "VisTTree.h"
#include "ConcatenableQueue.h"
#include "Angle.h"
#include "Point.h"
#include "VisUtils.h"

#define tolerance 0.5
using namespace std;
bool looseEquality(Point &p1, Point &p2) {
    return abs(p1.x - p2.x) < tolerance and abs(p1.y - p2.y) < tolerance;
}


int main(){
    VisTTree t;
    leda::window W(800, 800);
    W.display(leda::window::center, leda::window::center);
    VisUtils visualizer;
    visualizer.setLedaWindow(&W);
    t.setVisUtils(&visualizer);
    vector<Point> points;
    vector<Point> hull;
    while (W.get_state() != 0) {
        double x;
        double y;
        int mouse = W.read_mouse(x, y);
        Point newPoint = Point(x, y);
        if (mouse == -3) {
            auto it = std::find_if(points.begin(), points.end(),
                                   [&](Point p) { return looseEquality(p, newPoint); });
            if (it != points.end()) {
                auto realPoint = *it;
                points.erase(it);
                t.remove(realPoint);
                visualizer.resetGradientRatio();
                visualizer.deleteHull(hull);
                hull = t.getLowerHull();
                visualizer.drawHull(hull);
                W.draw_filled_circle(realPoint.x, realPoint.y, 0.5, leda::white);
            }

        } else {
            auto it = std::lower_bound(points.begin(), points.end(), newPoint);
            if (it != points.end() and *it == Point(x, y)) {
                continue;
            }
            points.insert(it, newPoint);
            W.draw_filled_circle(x, y, 0.5);
            t.insert(newPoint);
            visualizer.resetGradientRatio();
            visualizer.deleteHull(hull);
            hull = t.getLowerHull();
            visualizer.drawHull(hull);
        }

    }

    return 0;
}