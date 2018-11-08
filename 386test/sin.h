double qsin(double x)
{
    double x2;
    double cur;
    int neg;
    double xpow;
    double n2m1;
    double nfac;
    int iters;
    double sum;

    // square of x
    x2 = x * x;

    // values for initial terms where n==0:
    xpow = x;
    n2m1 = 1.0;
    nfac = 1.0;
    neg = 1;

    sum = 0.0;

    // NOTES:
    // (1) with the setup above, we can just use the loop without any special
    //     casing
    // (2) this _will_ do an unnecessary calculation [that gets thrown away] on
    //     the last iteration, but it's a tradeoff for simplicity
    // (3) when translated to asm, it should be easy to restructure to avoid
    //     this (i.e. just harder to express in a loop here)
    for (iters = 5;  iters > 0;  --iters) {
        // calculate current value
        cur = xpow / nfac;

        // apply it to sum
        if (neg < 0)
            sum -= cur;
        else
            sum += cur;

        // now calculate intermediate values for _next_ sum term

        // get _next_ power term
        xpow *= x2;

        // go from factorial(2n+1) to factorial(2n+1+1)
        n2m1 += 1.0;
        nfac *= n2m1;

        // now get factorial(2n+1+1+1)
        n2m1 += 1.0;
        nfac *= n2m1;

        // flip sign
        neg = -neg;
    }

    return sum;
}
