#ifndef _MODE_H_
#define _MODE_H_

class Mode {
    public:
        virtual void start() {};
        virtual bool display() = 0;
        virtual void stop() {};
};

#endif
