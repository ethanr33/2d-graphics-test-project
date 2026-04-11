
#pragma once

class ViewportTransformation {
    public:
        virtual double transform_x(double) = 0;
        virtual double transform_y(double) = 0;
};