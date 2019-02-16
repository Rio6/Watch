// Copied and edited from https://drive.google.com/file/d/0BxwUdFnrQGeKUGUyajY3dkdZWHM/edit

// 用16進位儲存 1900-2100 年之農曆資料陣列
// 起算日為國曆1900年01月31日即農曆1900年元月初一
// 以 2進位檢視元素資料
// 16~5bit 儲存全年農曆月份之大小月，1 為大月30天，0 為小月29天
//  4~1bit 儲存農曆閏月月份，f 表示前一年閏年為大月30天，0 為小月29天

static int lunarInfo[] = {
    0x4bd8, //1900
    0x4ae0,0xa570,0x54d5,0xd260,0xd950,0x5554,0x56af,0x9ad0,0x55d2,0x4ae0, // 1910
    0xa5b6,0xa4d0,0xd250,0xd295,0xb54f,0xd6a0,0xada2,0x95b0,0x4977,0x497f, // 1920
    0xa4b0,0xb4b5,0x6a50,0x6d40,0xab54,0x2b6f,0x9570,0x52f2,0x4970,0x6566, // 1930
    0xd4a0,0xea50,0x6a95,0x5adf,0x2b60,0x86e3,0x92ef,0xc8d7,0xc95f,0xd4a0, // 1940
    0xd8a6,0xb55f,0x56a0,0xa5b4,0x25df,0x92d0,0xd2b2,0xa950,0xb557,0x6ca0, // 1950
    0xb550,0x5355,0x4daf,0xa5b0,0x4573,0x52bf,0xa9a8,0xe950,0x6aa0,0xaea6, // 1960
    0xab50,0x4b60,0xaae4,0xa570,0x5260,0xf263,0xd950,0x5b57,0x56a0,0x96d0, // 1970
    0x4dd5,0x4ad0,0xa4d0,0xd4d4,0xd250,0xd558,0xb540,0xb6a0,0x95a6,0x95bf, // 1980
    0x49b0,0xa974,0xa4b0,0xb27a,0x6a50,0x6d40,0xaf46,0xab60,0x9570,0x4af5, // 1990
    0x4970,0x64b0,0x74a3,0xea50,0x6b58,0x5ac0,0xab60,0x96d5,0x92e0,0xc960, // 2000
    0xd954,0xd4a0,0xda50,0x7552,0x56a0,0xabb7,0x25d0,0x92d0,0xcab5,0xa950, // 2010
    0xb4a0,0xbaa4,0xad50,0x55d9,0x4ba0,0xa5b0,0x5176,0x52bf,0xa930,0x7954, // 2020
    0x6aa0,0xad50,0x5b52,0x4b60,0xa6e6,0xa4e0,0xd260,0xea65,0xd530,0x5aa0, // 2030
    0x76a3,0x96d0,0x4afb,0x4ad0,0xa4d0,0xd0b6,0xd25f,0xd520,0xdd45,0xb5a0, // 2040
    0x56d0,0x55b2,0x49b0,0xa577,0xa4b0,0xaa50,0xb255,0x6d2f,0xada0,0x4b63, // 2050
    0x937f,0x49f8,0x4970,0x64b0,0x68a6,0xea5f,0x6b20,0xa6c4,0xaaef,0x92e0, // 2060
    0xd2e3,0xc960,0xd557,0xd4a0,0xda50,0x5d55,0x56a0,0xa6d0,0x55d4,0x52d0, // 2070
    0xa9b8,0xa950,0xb4a0,0xb6a6,0xad50,0x55a0,0xaba4,0xa5b0,0x52b0,0xb273, // 2080
    0x6930,0x7337,0x6aa0,0xad50,0x4b55,0x4b6f,0xa570,0x54e4,0xd260,0xe968, // 2090
    0xd520,0xdaa0,0x6aa6,0x56df,0x4ae0,0xa9d4,0xa4d0,0xd150,0xf252,0xd520, // 2100
};

/*
 * 　。一丁七三丑丙乙九二五亥八六初刻十卅午卌卯四壬子寅己巳庚廿戊戌日月未正甲申癸辛辰酉
 * A B C D E F G H I J K L M N O P Q R S T U V W X Y Z [ \ ] ^ _ ` a b c d e f g h i j
 */

static char tiangan[] = {'e', 'I', 'H', 'D', '_', '[', ']', 'h', 'X', 'g'};
//                      {'甲','乙','丙','丁','戊','己','庚','辛','壬','癸'};
static char dizhi[] = {'Y', 'G', 'Z', 'V', 'i', '\\', 'T', 'c', 'f', 'j', '`', 'M'};
//                    {'子','丑','寅','卯','辰','巳','午','未','申','酉','戌','亥'};
static char nStr1[] = {'a', 'C', 'K', 'F', 'W', 'L', 'O', 'E', 'N', 'J', 'R'};
//                    {'日','一','二','三','四','五','六','七','八','九','十'};
static char nStr2[] = {'P', 'R', '^', 'S', 'U'};
//                    {'初','十','廿','卅','卌'};

// 傳回農曆 y年閏哪個月 1-12 , 沒閏傳回 0
static int leapMonth(int y) {
    int lm = lunarInfo[y-1900] & 0xf;
    return(lm == 0xf ? 0 : lm);
}

// 傳回農曆 y年閏月的天數
static int leapDays(int y) {
    if(leapMonth(y))
        return (lunarInfo[y-1899] & 0xf) == 0xf ? 30 : 29;
    return 0;
}

// 傳回農曆 y年的總天數
static int lYearDays(int y) {
    int sum = 348;
    for(int i = 0x8000; i > 0x8; i >>= 1)
        sum += (lunarInfo[y-1900] & i) ? 1: 0;
    return sum + leapDays(y);
}

// 傳回農曆 y年m月的總天數
static int monthDays(int y, int m) {
    return (lunarInfo[y-1900] & (0x10000 >> m))? 30 : 29 ;
}

static void getLunar(time_t now, int *year, int *month, int *day) {

    int offset = now / 864000 + 25537;

    int y;
    for(y = 1900; y < 2100; y++) {
        int tmp = lYearDays(y);
        if(offset - tmp < 0) {
            break;
        }
        offset -= tmp;
    }
    *year = y;

    int leap = leapMonth(y); //閏哪個月
    int isLeap = 0;
    int m = 0;

    for(m = 1; m <= 12 && offset > 0; m++) {
        int tmp;

        //閏月
        if(leap > 0 && m == leap+1 && !isLeap) {
            m--;
            isLeap = 1;
            tmp = leapDays(y);
        } else {
            tmp = monthDays(y, m);
        }

        //解除閏月
        if(isLeap && m == leap+1)
            isLeap = 0;

        if(offset - tmp == 0 && leap > 0 && m == leap+1) {
            if(isLeap) {
                isLeap = 0;
                m++;
            } else {
                isLeap = 1;
            }
            offset = 0;
            break;
        } else if(offset - tmp < 0) {
            break;
        } else {
            offset -= tmp;
        }
    }

    *month = m;
    *day = offset + 1;
}

static void getChYear(int year, char[3] cy) {
    int offset = year - 1864; // 1864 是甲子年
    sprintf(cy, "%c%c", tiangan[offset%10], dizhi[offset%12]);
}

static void getChMonth(int month, char[4] cm) {
    if(month >= 10) {
        sprintf(cm, "%c%c月", nStr2[month/10], nStr1[month%10]);
    } else {
        sprintf(cm, "%c月", nStr1[month]);
    }
}

static void getChDay(int day, char[3] cd) {
    sprintf(cd, "%c%c", nStr1[day/10], nStr1[day%10]);
}

static void getChWeekday(int wday, char[2] cw) {
    sprintf(cw, "%c", nStr1[wday-1]); // i'll trust wday to be [1,6]
}
