def householder(x):
    from cppsparse import dhouse, dvec
    import numpy
    xtemp = dvec(x);
    norm, beta = dhouse(xtemp)
    v = numpy.array(xtemp)
    v.shape = len(x),1
    print(v)
    return numpy.identity(len(x)) - beta * numpy.dot(v, v.transpose())
    

