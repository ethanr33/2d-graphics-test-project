
#pragma once

class ViewportTransformation {
    public:
        virtual double transform_x(double) const = 0;
        virtual double transform_y(double) const = 0;
};