class TimeMode {
    public:
        void display();
        void button(int);

    private:
        static const uint8_t BRIGHTNESS;
        static const int DURATION;

        volatile bool showDate;
        int counter = 0;

        void printDate();
        void printTime();
};
