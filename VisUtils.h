
#ifndef DYNAMICCONVEXHULL_VISUTILS_H
#define DYNAMICCONVEXHULL_VISUTILS_H

#include <climits>
#include <vector>
#include <LEDA/graphics/window.h>
#include "TTree.h"
#include "ConcatenableQueue.h"
#include "Angle.h"
#include "Point.h"
#include <thread>
#include <chrono>

class VisUtils {
    public:
    double gradientRatio = 0;
    leda::window *w = nullptr;

    void setLedaWindow(leda::window *_w);

    void drawHull(TTree *t, std::vector<Point> &hull);

    void drawHull(std::vector<Point> &hull);
    
    void drawHullGradient(std::vector<Point> &hull, bool increment);


    void drawHullGradient(std::vector<Point> &hull, int increments);
    
    void drawHull(std::vector<Point> &hull, double ratio);
    
    void incrementGradientRatio() { gradientRatio += 0.05; }

    void resetGradientRatio() { gradientRatio = 0; }
    void deleteHull(std::vector<Point> &hull);
    void wait(int milliseconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
    struct RGB {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };
    RGB rgb(double ratio)
    {
        //we want to normalize ratio so that it fits in to 6 regions
        //where each region is 256 units long
        int normalized = int(ratio * 256 * 6);

        //find the region for this position
        int region = normalized / 256;

        //find the distance to the start of the closest region
        int x = normalized % 256;

        uint8_t r = 0, g = 0, b = 0;
        switch (region)
        {
            case 0: r = 255; g = 0;   b = 0;   g += x; break;
            case 1: r = 255; g = 255; b = 0;   r -= x; break;
            case 2: r = 0;   g = 255; b = 0;   b += x; break;
            case 3: r = 0;   g = 255; b = 255; g -= x; break;
            case 4: r = 0;   g = 0;   b = 255; r += x; break;
            case 5: r = 255; g = 0;   b = 255; b -= x; break;
        }
        return RGB{r, g, b};
    } // Thanks to https://stackoverflow.com/a/40639903/20915145
    
    
};
#endif //DYNAMICCONVEXHULL_VISUTILS_H


