#ifndef MODE_H
#define MODE_H

class Mode {
    public:
        virtual ~Mode() = default;

        virtual void start() {};
        virtual bool display() = 0;
        virtual void stop() {};
};

#endif
