#include "Mode.hpp"

class SWMode : public Mode {
    public:
        bool display();

    private:
        bool dbcStart = false;
        bool dbcReset = false;

        time_t startTime = 0;
        long startMillis = 0;
        bool running = false;
        bool zeroed = true;
        time_t time = 0;
        int centi = 0;

        void draw();
};

