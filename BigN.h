struct BigN {
    unsigned long long lower, upper;
    char num[128];
};

static inline void assignBigN(struct BigN *x, unsigned long long value)
{
    x->lower = value;
    x->upper = 0;
}

static inline void addBigN(struct BigN *output, struct BigN x, struct BigN y)
{
    output->upper = x.upper + y.upper;
    if (y.lower > ~x.lower) {  // check for overflow
        output->upper++;
    }
    output->lower = x.lower + y.lower;
}

// Helper function for big num print!
void printBigN(struct BigN *x)
{
    unsigned int p0 = (x->upper) >> 32;
    unsigned int p1 = (x->upper) & 0x00000000FFFFFFFF;
    unsigned int p2 = (x->lower) >> 32;
    unsigned int p3 = (x->lower) & 0x00000000FFFFFFFF;

    int cnt = 0;
    do {
        unsigned long long d, r;
        r = p0;

        d = r / 10;
        r = ((r - d * 10) << 32) + p1;
        p0 = d;

        d = r / 10;
        r = ((r - d * 10) << 32) + p2;
        p1 = d;

        d = r / 10;
        r = ((r - d * 10) << 32) + p3;
        p2 = d;

        d = r / 10;
        r = r - d * 10;
        p3 = d;

        x->num[cnt++] = (char) '0' + (r - 0);
    } while (p0 || p1 || p2 || p3);
    x->num[cnt] = '\0';

    int i = 0, j = cnt - 1;

    while (i < j) {
        char tmp;
        tmp = x->num[i];
        x->num[i++] = x->num[j];
        x->num[j--] = tmp;
    }
}
