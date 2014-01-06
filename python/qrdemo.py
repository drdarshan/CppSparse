

def compute_q(V, B):
    "Given the Householder reflectors, V and the set of scaling coefficients Beta, compute the Q matrix"
    import numpy as np
    m, n = V.shape
    H = np.identity(m)

    for k in range(n):
        Hk = np.identity(m) - B[k] * np.outer(V[:,k], V[:,k])
        H = np.dot(H, Hk)

    return H

def apply_q(v, beta, x):
    "Compute H * x = x - beta * (v * v' * x)"
    import numpy as np
    return x - beta * np.dot(v, x) * v

def qr_right(a):
    "Computes a right-looking QR factorization of A with M >= N"

    import numpy as np
    from cppsparse import dhouse, dvec

    m,n = a.shape
    V = np.zeros((m, n))
    B = np.zeros(n);
    R = a.copy();

    for i in range(n):
        x = dvec(R[i::, i]);
        norm, beta = dhouse(x)
        x = np.array(x)
        V[i::,i] = x
        B[i] = beta
        x.shape = x.size,1
        R[i::,i::] = R[i::, i::] - beta * np.dot(x, np.dot(x.T, R[i::, i::]))

    return compute_q(V, B), np.triu(R)


def qr_left(A):
    "Computes a left-looking QR factorization of A with M >= N"

    import numpy as np
    from cppsparse import dhouse, dvec

    m,n = A.shape
    V = np.zeros((m, n))
    B = np.zeros(n);
    R = np.zeros((m, n))

    for i in range(n):
        x = A[:, i].copy();
        for k in range(i):
            v = V[k::, k]
            beta = B[k]
            x[k::] = apply_q(v, beta, x[k::])
        xt = dvec(x[i::])
        norm, beta = dhouse(xt)
        V[i::,i] = np.array(xt)
        B[i] = beta
        R[:i,i] = x[:i]
        R[i,i] = norm

    Q = compute_q(V, B)
    return Q, R
