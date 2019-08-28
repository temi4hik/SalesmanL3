from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext


sourcefiles = ["salesman.pyx"]
ext_modules = [Extension("salesman", sourcefiles)]

setup(
    name="Salesman",
    cmdclass={"build_ext": build_ext},
    ext_modules=ext_modules
)
