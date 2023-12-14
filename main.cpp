#include <iostream>
#include "TTree.h"
#include <vector>
#include <random>
#include <algorithm>
#include <cassert>
#include <cmath>
#include "Angle.h"
#include "ConcatenableQueue.h"
#include <climits>
#include <LEDA/graphics/window.h>
#include <LEDA/geo/point.h>
// #include <LEDA/geo/polygon.h>
// #include <LEDA/core/list.h>
// #include <matplot/matplot.h>
#include <chrono>
#include <thread>

using namespace std;
// using namespace matplot;
using QNode = ConcatenableQueue::QNode;

void angleTest();

void angleTest2();

void CQueueTest();

void ttreTest();

void intersectionTest();

void sfmlTest();

void mergeTest();

void ascendTest();

void sciplotTest();

void ascendDescendTest();

void matplotplusplusTest();

void verticalTest();

void deleteTest();

void insertTest();

void randomInsertTest();

void duplicateTest();

void angleTest3() {
    Angle angle = Angle(Point(79, -INFINITY), Point(79, 35), Point(90, 10));
    Point test = Point(50, 85);
    angle.getUpperCase(test);
}

void matplotTest() {

}

bool looseEquality(Point &p1, Point &p2);

void drawHull(leda::window *w, TTree *t, vector<Point> &hull);

void deleteHull(leda::window *w, vector<Point> &hull);

int main() {
    TTree t;
    leda::window W(800, 800);
    W.display(leda::window::center, leda::window::center);
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
                deleteHull(&W, hull);
                drawHull(&W, &t, hull);
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
            deleteHull(&W, hull);
            drawHull(&W, &t, hull);
        }

    }

    return 0;
}

bool looseEquality(Point &p1, Point &p2) {
    return abs(p1.x - p2.x) < 0.5 and abs(p1.y - p2.y) < 0.5;
}

void deleteHull(leda::window *w, vector<Point> &hull) {
    if (hull.size() < 2) return;
    for (int i = 0; i < hull.size() - 1; ++i) {
        w->draw_segment(hull[i].x, hull[i].y, hull[i + 1].x, hull[i + 1].y, leda::white);
        // Redraw points since they will have empty lines through them
        w->draw_filled_circle(hull[i].x, hull[i].y, 0.5);
    }
    w->draw_segment(hull[0].x, hull[0].y, hull[hull.size() - 1].x, hull[hull.size() - 1].y, leda::white);
    w->draw_filled_circle(hull[hull.size() - 1].x, hull[hull.size() - 1].y, 0.5);
}

void drawHull(leda::window *w, TTree *t, vector<Point> &hull) {
    hull = t->getHull();
    if (hull.size() < 2) return;
    for (int i = 0; i < hull.size() - 1; ++i) {
        w->draw_segment(hull[i].x, hull[i].y, hull[i + 1].x, hull[i + 1].y);
    }
    w->draw_segment(hull[0].x, hull[0].y, hull[hull.size() - 1].x, hull[hull.size() - 1].y);
}

void duplicateTest() {
    TTree t;
    t.insert(Point(63, 63));
    t.insert(Point(10, 10));
    t.insert(Point(63, 63));
}

void insertTest() {
    TTree t;
    t.insert(50, 50);
    t.insert(40, 30);
    t.insert(10, 10);
    t.insert(20, 20);
    t.insert(40, 40);
    t.insert(80, 10);
    t.insert(80, 80);
    t.insert(40, 20);
    t.insert(50, 40);
    t.insert(30, 40);
    t.printLowerHull();
}

void deleteTest() {
    TTree t;
    t.insert(Point(50, 60));
    t.insert(Point(30, 40));
    t.insert(Point(10, 10));
    t.insert(Point(80, 20));
    t.insert(Point(20, 20));
    t.insert(Point(45, 45));
    t.remove(Point(80, 20));
    t.remove(Point(45, 45));
    t.printLowerHull();
}

void verticalTest() {
    TTree t;
    t.insert(Point(15, 8));
    t.insert(Point(15, 4));
    t.insert(Point(10, 2));
    t.printLowerHull();
}

/*
void randomInsertTest() {
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
    std::uniform_int_distribution dist(10, 90);
    for (int i = 0; i < 10000; ++i) {
        Point randPoint = Point(dist(gen), dist(gen));
        bool newPoint = t.insert(randPoint);
        if (newPoint){
            x.push_back(randPoint.x);
            y.push_back(randPoint.y);
        }
        scatter(x, y);
        hull = t.getLowerPoints();
        vector<double> xHull;
        vector<double> yHull;
        hold(on);
        for (auto p: hull) {
            xHull.emplace_back(p.x);
            yHull.emplace_back(p.y);
        }
        plot(xHull, yHull);

        hull = t.getUpperPoints();
        hold(on);
        xHull.clear();
        yHull.clear();
        for (auto p: hull) {
            xHull.emplace_back(p.x);
            yHull.emplace_back(p.y);
        }
        plot(xHull, yHull);
        this_thread::sleep_for(chrono::milliseconds(150));
        hold(off);
        if (i > 20 and newPoint) {
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
            this_thread::sleep_for(chrono::milliseconds(150));
        }
    }
    string stall;
    cin >> stall;
}
*/

/*
void matplotplusplusTest() {
    string input;
    double x, y;

    TTree t;
    auto ax = gca();
    ax->x_axis().label("x");
    ax->y_axis().label("y");
    ax->x_axis().limits({0, 100});
    ax->y_axis().limits({0, 100});
    vector<Point> points;
    vector<Point> hull;
    while (cin >> input) {
        if (input == "add") {
            cin >> x >> y;
            points.emplace_back(x, y);
            t.insert(Point(x, y));
        } else if (input == "delete") {
            cin >> x >> y;
            t.remove(Point(x, y));
            // remove point from points
            points.erase(std::remove(points.begin(), points.end(), Point(x, y)), points.end());
        }
        vector<double> xVals;
        vector<double> yVals;
        for (auto &point: points) {
            xVals.emplace_back(point.x);
            yVals.emplace_back(point.y);
        }
        scatter(xVals, yVals);

        hull = t.getLowerHull();

        vector<double> xHull;
        vector<double> yHull;
        hold(on);
        for (auto p: hull) {
            cout << p << endl;
            xHull.emplace_back(p.x);
            yHull.emplace_back(p.y);
        }
        plot(xHull, yHull);
        hold(off);
    }
}
*/

void angleTest2() {
    Angle l(Point(63, 26), Point(63, 26), Point(72, 36));
    Angle r(Point(77, 15), Point(77, 15), Point(83, 86));
}

void angleTest() {
    // create a vector of angles representing the bottom of the unit circle
    // bottom of x^2 + y^2 = 1
    vector<Point> points;
    for (int i = -10; i < 10; ++i) {
        double x = (double) i / 10;
        double y = -sqrt(1 - (x * x));
        points.emplace_back(x, y);
    }
    // For every triple of points create an angle
    vector<Angle> angles;
    for (int i = 1; i < points.size() - 3; ++i) {
        angles.emplace_back(points[i], points[i + 1], points[i + 2]);
    }
    angles.back().right = angles.back().middle;
    angles.back().right.y += 1;
    angles.front().left = angles.front().middle;
    angles.front().left.y += 1;
    cout << angles.size() << "angles created" << endl;
    Point test = Point(1.5, 0.5);
    for (Angle a: angles) {
        cout << "angle: " << a << endl;
        cout << "case: " << a.getLowerCase(test) << endl;
    }
}

void ttreTest() {
    TTree t;
    cout << "created" << endl;
    vector<Point> points;
    for (int i = 0; i < 40; ++i) {
        Point randPoint = Point(random() % 100, random() % 100);
        points.push_back(randPoint);
        cout << "inserting " << i << " " << randPoint.x << endl;
        t.insert(randPoint);
        t.displayTree();
        cout << "checking properties" << endl;
        t.checkProperties();
    }
    std::shuffle(points.begin(), points.end(), std::mt19937(std::random_device()()));
    for (Point p: points) {
        cout << "removing " << p.x << endl;
        t.remove(p);
        t.displayTree();
        t.checkProperties();
    }
    points.clear();
    for (int i = 0; i < 40; ++i) {
        Point randPoint = Point(random() % 100, random() % 100);
        points.push_back(randPoint);
        cout << "inserting " << i << " " << randPoint.x << endl;
        t.insert(randPoint);
        t.displayTree();
        cout << "checking properties" << endl;
        t.checkProperties();
    }
    std::shuffle(points.begin(), points.end(), std::mt19937(std::random_device()()));
    for (Point p: points) {
        cout << "removing " << p.x << endl;
        t.remove(p);
        t.displayTree();
        t.checkProperties();
    }
}

/*
void CQueueTest() {
    ConcatenableQueue q(Point(0, 0));
    ConcatenableQueue q2(Point(1, 1));
    ConcatenableQueue a(Point(0.5, 0.5));
    QNode *n = ConcatenableQueue::join(q.root, a.root, q2.root);
    ConcatenableQueue::inOrder(n);
    ConcatenableQueue::checkProperties(n, nullptr, nullptr);

    ConcatenableQueue q3(Point(2, 2));
    ConcatenableQueue q4(Point(3, 3));
    ConcatenableQueue a2(Point(2.5, 2.5));
    QNode *n2 = ConcatenableQueue::join(q3.root, a2.root, q4.root);
    ConcatenableQueue::inOrder(n2);
    ConcatenableQueue::checkProperties(n2, nullptr, nullptr);

    cout << "n3" << endl;
    ConcatenableQueue a3(Point(1.5, 1.5));
    QNode *n3 = ConcatenableQueue::join(n, a3.root, n2);
    ConcatenableQueue::inOrder(n3);
    ConcatenableQueue::checkProperties(n3, nullptr, nullptr);


    ConcatenableQueue q5(Point(4, 4));
    ConcatenableQueue q6(Point(5, 5));
    ConcatenableQueue a4(Point(4.5, 4.5));
    QNode *n4 = ConcatenableQueue::join(q5.root, a4.root, q6.root);
    ConcatenableQueue::inOrder(n4);
    ConcatenableQueue::checkProperties(n4, nullptr, nullptr);


    cout << "n5" << endl;
    ConcatenableQueue a5(Point(3.5, 3.5));
    QNode *n5 = ConcatenableQueue::join(n3, a5.root, n4);
    ConcatenableQueue::inOrder(n5);
    ConcatenableQueue::checkProperties(n5, nullptr, nullptr);

    ConcatenableQueue q7(Point(-2, -2));
    ConcatenableQueue q8(Point(-1, -1));
    ConcatenableQueue a6(Point(-1.5, -1.5));
    QNode *n6 = ConcatenableQueue::join(q7.root, a6.root, q8.root);
    ConcatenableQueue::inOrder(n6);
    ConcatenableQueue::checkProperties(n6, nullptr, nullptr);

    cout << "n7" << endl;
    ConcatenableQueue a7(Point(-0.5, -0.5));
    QNode *n7 = ConcatenableQueue::join(n6, a7.root, n5);
    ConcatenableQueue::inOrder(n7);
    ConcatenableQueue::checkProperties(n7, nullptr, nullptr);
}
*/

void intersectionTest() {
    Point l1 = Point(0, 0);
    Point l2 = Point(1, -1);
    Point r1 = Point(3, 3);
    Point r2 = Point(2, 0);

    double s = ((r1.x - l1.x) * (l2.y - l1.y) - (r1.y - l1.y) * (l2.x - l1.x)) /
               ((r2.y - r1.y) * (l2.x - l1.x) - (r2.x - r1.x) * (l2.y - l1.y));
    double x = r1.x + s * (r2.x - r1.x);
    cout << x << endl;
}

/*void mergeTest() {
    ConcatenableQueue left(Point(0, 0));
    ConcatenableQueue right(Point(1, 1));
    ConcatenableQueue n;
    n.mergeHulls(&left, &right);
    ConcatenableQueue::inOrder(n.root);
}*/
/*void sfmlTest(){
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    vector<sf::CircleShape> dots;
    

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                // Draw a circle at the mouse position
                sf::CircleShape shape(5.f);
                shape.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                cout << "x: " << shape.getPosition().x << " y: " << shape.getPosition().y << endl;
                shape.setFillColor(sf::Color::Green);
                dots.push_back(shape);
            }
        }

        // clear the window with black color
        // window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);
        for (sf::CircleShape shape: dots) {
            window.draw(shape);
        }
        // end the current frame
        window.display();
    }
}*/

/*
void ascendTest(){
    TTree t;
    cout << "created" << endl;
    vector<Point> points;
    vector<double> x;
    vector<double> y;
    double lower_bound = 0;
    double upper_bound = 1;
    std::minstd_rand gen(std::random_device{}());
    std::weibull_distribution<double> unif(4, 2);
    for (int i = 0; i < 100000; ++i) {
        Point randPoint = Point(unif(gen), unif(gen));
        points.push_back(randPoint);
        x.push_back(randPoint.x);
        y.push_back(randPoint.y);
        t.insert(randPoint);
    }
    cout << "inserted" << endl;
    Plot2D plot;
    plot.drawPoints(x, y);
    
    
    std::cout << "ascend" << std::endl;
    std::vector<Point> hull = t.getPoints();
    std::vector<double> x2;
    std::vector<double> y2;
    for (Point p: hull) {
        x2.push_back(p.x);
        y2.push_back(p.y);
    }
    plot.drawCurve(x2, y2);
    Figure fig = {{plot}};
    Canvas canvas = {{fig}}; 
    canvas.size(800, 600);
    canvas.show();
}

void sciplotTest(){
    Vec x = { 1, 2, 3 };
    Vec y = { 4, 5, 6 };

    Plot2D plot;

    plot.drawPoints(x, y);
    Figure fig = {{plot}};
    Canvas canvas = {{fig}};
    canvas.size(800, 600);
    canvas.show();
}
void ascendDescendTest(){
    TTree t;
    cout << "created" << endl;
    vector<Point> points;
    vector<double> x;
    vector<double> y;
    double lower_bound = 0;
    double upper_bound = 1;
    std::minstd_rand gen(std::random_device{}());
    std::weibull_distribution<double> unif(4, 2);
    for (int i = 0; i < 10; ++i) {
        Point randPoint = Point(unif(gen), unif(gen));
        points.push_back(randPoint);
        x.push_back(randPoint.x);
        y.push_back(randPoint.y);
        t.insert(randPoint);
    }
    cout << "inserted" << endl;
    Plot2D plot;
    plot.drawPoints(x, y);

    std::vector<Point> hull = t.getLowerHull();
    std::vector<double> x2;
    std::vector<double> y2;
    for (Point p: hull) {
        x2.push_back(p.x);
        y2.push_back(p.y);
    }
    plot.drawCurve(x2, y2);
    Figure fig = {{plot}};
    Canvas canvas = {{fig}};
    canvas.size(800, 600);
    canvas.show();
    }
*/
