/* imd_controler.h */
#ifndef __IMD_CONTROLER_H__
#define __IMD_CONTROLER_H__


template <uint16_t time>
class interval {
    unsigned long next_run = 0;

    template <class T>
    void _run(T func) {
        unsigned long now = micros();
        if (next_run < now) {
            func();
            next_run = now + time;
        }
    }

    interval() {}
public:

    template <class T>
    static void run(T func) {
        static interval<time> instance;
        instance._run(func);
    }
};

 #endif
