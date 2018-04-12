//
// Created by USER on 2018/3/27.
//

#ifndef INVOLUTESPURGEAR_PAIR_H
#define INVOLUTESPURGEAR_PAIR_H

template <class T, class V>
class Pair {
private:
    T first;
    V second;
public:
    Pair(T t_first, V t_second)
    : first(t_first), second(t_second){}

    T x() {
        return first;
    }

    V y() {
        return second;
    }

};

#endif //INVOLUTESPURGEAR_PAIR_H
