#ifndef FOO_H
#define FOO_H


class Foo
{
    public:
        Foo();
        virtual ~Foo();
        int Getbasic() { return basic; }
        void Setbasic(int val) { basic = val; }
        int GetnotBasic() { return notBasic; }
        void SetnotBasic(int val) { notBasic = val; }
    protected:
    private:
        int basic;
        int notBasic;
};

#endif // FOO_H
