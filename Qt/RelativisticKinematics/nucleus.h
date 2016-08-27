#ifndef NUCLEUS_H
#define NUCLEUS_H


class Nucleus
{
public:
    Nucleus(int Z, int A);
    ~Nucleus();

    double mass, Z, A, N, BEA, Sp, Sn;
    double KE, momt,

    void SetKE(double KE);

};

#endif // NUCLEUS_H
