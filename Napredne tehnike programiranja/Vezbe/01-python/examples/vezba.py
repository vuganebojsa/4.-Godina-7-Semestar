class A:
    pass


class B(A):
    pass


class C(A):
    pass


class D(B, C, A):
    pass


class E(C):
    pass

class F(E, D):
    pass

print(F.__mro__)
