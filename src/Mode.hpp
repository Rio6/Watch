#ifndef _MODE_H_
#define _MODE_H_

class Mode {
    public:
        virtual ~Mode() = default;

        virtual void start() {};
        virtual bool display() = 0;
        virtual void stop() {};
        virtual bool isStd() {return true;};
};

#endif
