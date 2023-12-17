#include "VisUtils.h"
#include <cassert>
using namespace std;

void VisUtils::drawHull(TTree *t, vector<Point> &hull) {
    hull = t->getHull();
    if (hull.size() < 2) return;
    for (int i = 0; i < hull.size() - 1; ++i) {
        w->draw_segment(hull[i].x, hull[i].y, hull[i + 1].x, hull[i + 1].y);
    }
    w->draw_segment(hull[0].x, hull[0].y, hull[hull.size() - 1].x, hull[hull.size() - 1].y);
}

void VisUtils::deleteHull(vector<Point> &hull) {
    if (hull.size() < 2) return;
    for (int i = 0; i < hull.size() - 1; ++i) {
        w->draw_segment(hull[i].x, hull[i].y, hull[i + 1].x, hull[i + 1].y, leda::white);
        // Redraw points since they will have empty lines through them
        w->draw_filled_circle(hull[i].x, hull[i].y, 0.5);
    }
    w->draw_segment(hull[0].x, hull[0].y, hull[hull.size() - 1].x, hull[hull.size() - 1].y, leda::white);
    w->draw_filled_circle(hull[hull.size() - 1].x, hull[hull.size() - 1].y, 0.5);
}

void VisUtils::setLedaWindow(leda::window *_w) {
    w = _w;
}

void VisUtils::drawHull(vector<Point> &hull) {
    if (hull.size() < 2) return;
    for (int i = 0; i < hull.size() - 1; ++i) {
        w->draw_segment(hull[i].x, hull[i].y, hull[i + 1].x, hull[i + 1].y);
    }
}

void VisUtils::drawHull(vector<Point> &hull, double ratio) {
    if (hull.size() < 2) return;
    if (ratio > 1) ratio = 0;
    RGB color = rgb(ratio);
    for (int i = 0; i < hull.size() - 1; ++i) {
        w->draw_segment(hull[i].x, hull[i].y, hull[i + 1].x, hull[i + 1].y, leda::color(color.r, color.g, color.b));
    }

}

void VisUtils::drawHullGradient(vector<Point> &hull, bool increment) {
    if (increment) gradientRatio += 0.01;
    if (hull.size() < 2) return;
    if (gradientRatio > 1) gradientRatio = 0;
    RGB color = rgb(gradientRatio);
    for (int i = 0; i < hull.size() - 1; ++i) {
        w->draw_segment(hull[i].x, hull[i].y, hull[i + 1].x, hull[i + 1].y, leda::color(color.r, color.g, color.b));
    }

}

void VisUtils::drawHullGradient(vector<Point> &hull, int increments) {
    gradientRatio = (0.1 * increments) - floor(0.1 * increments);
    drawHullGradient(hull, false);
}

