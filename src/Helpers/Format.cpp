//
// Created by mk on 19.01.16.
//

#include "Format.h"
#include <boost/format.hpp>

using namespace boost;

string toString(Vector2 vector) {
    return (format("[%1$.2f; %2$.2f]") % vector.x % vector.y).str();
}
