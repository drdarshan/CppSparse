import cppsparse as c
import numpy as n

def nfull(x):
    import numpy as np
    m, n = (x.n_rows(), x.n_cols())
    y = np.array(x.full(), order = 'F')
    y.shape = m, n
    if m > 1 and n > 1:
        return y.transpose()
    else:
        return y
    

def nvec(x):
    return n.array(x)

def spcolvec(x):
    y = c.dtrp(len(x), 1)
    for i in range(len(x)):
        y.push_back(i, 0, float(x[i]))
    z = c.dcsc(y)
    z.keep()
    return z

def vect(n):
    v = c.ivec()
    for elem in n:
        v.push_back(int(elem))
    return v

lower_tri = c.dtrp(5, 5)
full_sym  = c.dtrp(5, 5)
upper_tri = c.dtrp(5, 5)
y         = c.dtrp(5, 1)

for col in range(5):
    for row in range(col, 5):
        lower_tri.push_back(row, col, float(row + col * 5.0))
        full_sym.push_back (row, col, float(row + col * 5.0))
        upper_tri.push_back (col, row, float(row + col * 5.0))
        if row != col:
            full_sym.push_back (col, row, float(row + col * 5.0))


lower_tri = c.dcsc(lower_tri)
upper_tri = c.dcsc(upper_tri)
full_sym  = c.dcsc(full_sym)

lower_tri.keep()

print(lower_tri)
l = lower_tri.subsref_range(0,4,0,4)
print(l)
print(nfull(l))

v = vect(n.array([0,0,1,1,2,2,3]))
ll = lower_tri.subsref_vector(v, v)
print(ll)
print(nfull(ll))
