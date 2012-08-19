import numpy as N

def chol_up(A):
    m, n = A.shape
    if m != n:
        raise RuntimeError("Matrix is not square.")

    L = N.zeros_like(A)
    
    if A[0,0] <= 0.0:
        raise RuntimeError("Matrix is not PD.");

    L[0,0] = N.sqrt(A[0,0]);

    for k in range(1, n):
        L[0:k, k] = N.linalg.solve(L[0:k, 0:k], A[0:k, k])
        D         = A[k, k] - N.dot(L[0:k, k], L[0:k, k])
        if D <= 0.0:
            raise RuntimeError("Matrix is not PD: %f"%D)
        L[k, k]   = N.sqrt(D)

    return L.T
        

def chol_up_test(m):
    A1 = N.random.rand(m, m)
    A  = N.identity(m) * 100 + N.dot(A1.T, A1)
    L  = chol_up(A)
    print L
    print "Difference = ", N.linalg.norm(A - N.dot(L, L.T))/N.linalg.norm(A)
