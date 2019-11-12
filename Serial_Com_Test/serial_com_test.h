/* serial_communication_test.h */

#ifndef __SERIAL_COM_TEST_H__
#define __SERIAL_COM_TEST_H__

/* GLOBAL TYPE DEFINITION */

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

 #endif /*  __SERIAL_COM_TEST_H__ */
