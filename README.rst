===========================================================
CppSparse: A C++ sparse matrix library with Python bindings
===========================================================

About
-----

I have been fascinated with sparse direct solvers ever since I
encountered them whilst learning finite element analysis back during my
undergraduate days. One particularly clever trick that stood out was
the *multi-frontal* method developed by Bruce M. Irons back in the 1960s
that performed Gaussian elimination on the stiffness matrix *while it
was being assembled* in the usual element-by-element fashion.

As a graduate student, I was fortunate enough to re-learn finite
element methods from Prof. Bathe. One of the intriguing aspects of
sparse solvers he mentioned in his class was the use of methods based
on graph theory that had surpassed classical *skyline* solvers such as
COLSOL described in his book [Bathe1995]_. 



Building CppSparse
------------------

*CppSparse* currently reliably builds on Windows using Microsoft
 Visual Studio 2010 and MingW GCC 4.5 (64-bit) and is tested with
 64-bit Python 2.7 and NumPy. I also occassionally build it on my Mac
 OS Snow Leopard and back-port the changes back to Windows.

Some of the routines in CppSparse use C++11 features such as lambda
expressions that are not supported out-of-the-box on the older GCC
installed on Snow Leopard; I will eventually remove these features
once I have completed a few more chapters in Davis' book. I also had
move constructors on the matrix classes that I disabled because SWIG
seemed to choke on them.

Prequisites
~~~~~~~~~~~
* `SWIG` version 2.0.1 or better for generating the Python bindings
* `Microsoft Windows 7 SDK (64-bit)` that contains the 64-bit version of the Visual C++ compiler, or, 
* `MingW64` with GCC 4.5 or better for compiling the generated bindings
* `Python` 64-bit version 2.7 or better (I have not tested *CppSparse* with Python 3.x)
* `NumPy` compatible with your Python installation. You can get a 64-bit installer for Windows from `Ch. Golke` 's website.
.. _SWIG: http://www.swig.org 
.. _MingW64: http://tdm-gcc.tdragon.net/
.. _Microsoft Windows 7 SDK (64-bit): http://www.microsoft.com/download/en/details.aspx?id=8279
.. _Python: http://www.python.org
.. _NumPy: http://www.numpy.org
.. _Ch. Golke: http://www.lfd.uci.edu/~gohlke/pythonlibs

Building with the Microsoft C++ compiler
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Start up a 64-bit Visual C++ command prompt, navigate to the source 



Future plans
------------

License
-------


References
----------
.. [Bathe1995] Bathe, K-J. *Finite Element Procedures*, Prentice Hall, 1995. 
.. [Davis2006] Davis, T. *Direct Methods for Sparse Linear Systems*, SIAM, Philadelphia, PA, 2006.
.. [Irons1970] Irons, B.M. *A frontal solution scheme for finite element analysis*, IJNME, 2(5--32), 1970.

