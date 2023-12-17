

#include <climits>
#include <vector>
#include "TTree.h"
#include "ConcatenableQueue.h"
#include "Angle.h"
#include "Point.h"
#include <matplot/matplot.h>
#include <chrono>
#include <thread>
#include <random>
using namespace std;
using namespace matplot;

int main(){
    TTree t;
    vector<double> x;
    vector<double> y;
    auto ax = gca();
    ax->x_axis().label("x");
    ax->y_axis().label("y");
    ax->x_axis().limits({0, 100});
    ax->y_axis().limits({0, 100});
    vector<Point> hull;
    std::mt19937 gen(std::random_device{}());
    std::normal_distribution<double> dist(50, 10);
    for (int i = 0; i < 500000; ++i) {
        Point randPoint = Point(dist(gen), dist(gen));
        bool newPoint = t.insert(randPoint);
        if (newPoint){
            x.push_back(randPoint.x);
            y.push_back(randPoint.y);
        }
        scatter(x, y);
        hull = t.getLowerHull();
        vector<double> xHull;
        vector<double> yHull;
        hold(on);
        for (auto p: hull) {
            xHull.emplace_back(p.x);
            yHull.emplace_back(p.y);
        }
        plot(xHull, yHull);

        hull = t.getUpperHull();
        hold(on);
        xHull.clear();
        yHull.clear();
        for (auto p: hull) {
            xHull.emplace_back(p.x);
            yHull.emplace_back(p.y);
        }
        plot(xHull, yHull);
        this_thread::sleep_for(chrono::milliseconds(5));
        hold(off);
        /*if (i > 200 and newPoint) {
            std::uniform_int_distribution randIndex(0, (int) (x.size() - 1));
            int index = randIndex(gen);
            t.remove(Point(x[index], y[index]));
            x.erase(x.begin() + index);
            y.erase(y.begin() + index);
            scatter(x, y);
            hull = t.getLowerHull();
            vector<double> xHull;
            vector<double> yHull;
            hold(on);
            for (auto p: hull) {
                xHull.emplace_back(p.x);
                yHull.emplace_back(p.y);
            }
            plot(xHull, yHull);

            hull = t.getUpperHull();
            hold(on);
            xHull.clear();
            yHull.clear();
            for (auto p: hull) {
                xHull.emplace_back(p.x);
                yHull.emplace_back(p.y);
            }
            plot(xHull, yHull);
            hold(off);
            this_thread::sleep_for(chrono::milliseconds(10));
        }*/
    }
    string stall;
    cin >> stall;
}
