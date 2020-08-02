#define BUF_SIZE 128

struct BigN {
    unsigned long long lower, upper;
    char num[BUF_SIZE];
    int cnt;
};


static inline unsigned long long hi(unsigned long long x)
{
    return x >> 32;
}

static inline unsigned long long lo(unsigned long long x)
{
    return x & 0x00000000FFFFFFFF;
}


static inline void assignBigN(struct BigN *x, unsigned long long value)
{
    x->lower = value;
    x->upper = 0;
}

static inline struct BigN addBigN(struct BigN const x, struct BigN const y)
{
    struct BigN output;
    output.upper = x.upper + y.upper;
    if (y.lower > ~x.lower) {  // check for overflow
        output.upper++;
    }
    output.lower = x.lower + y.lower;

    return output;
}


static inline struct BigN mulBigN(struct BigN const x, struct BigN const y)
{
    struct BigN output;
    output.upper = x.upper * y.upper;

    unsigned long long s0, s1, s2;
    unsigned long long a = x.lower;
    unsigned long long b = y.lower;
    unsigned long long n = lo(a) * lo(b);
    s0 = lo(n);

    n = hi(a) * lo(b) + hi(n);
    s1 = lo(n);
    s2 = hi(n);

    n = s1 + lo(a) * hi(b);
    s1 = lo(n);

    n = s2 + hi(a) * hi(b) + hi(n);

    output.lower = s1 << 32 | s0;
    output.upper += n;
    return output;
}

// for substraction, x should always bigger than y
static inline struct BigN subBigN(struct BigN const x, struct BigN const y)
{
    struct BigN output;
    unsigned long long borrow = 0;
    if (y.lower > x.lower) {
        borrow = 1;
        output.lower = x.lower + ~y.lower + 1;
    } else
        output.lower = x.lower - y.lower;

    output.upper = x.upper - y.upper - borrow;

    return output;
}

static int printBigN(struct BigN *x, size_t size)
{
    unsigned int p0 = hi(x->upper);
    unsigned int p1 = lo(x->upper);
    unsigned int p2 = hi(x->lower);
    unsigned int p3 = lo(x->lower);

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

        if (cnt < BUF_SIZE)
            x->num[cnt++] = (char) '0' + (r - 0);
        else
            goto too_small_buffer;
    } while (p0 || p1 || p2 || p3);
    x->num[cnt] = '\0';
    x->cnt = cnt;

    int i = 0, j = cnt - 1;
    while (i < j) {
        char tmp;
        tmp = x->num[i];
        x->num[i++] = x->num[j];
        x->num[j--] = tmp;
    }

    return cnt;

too_small_buffer:
    return -1;
}
