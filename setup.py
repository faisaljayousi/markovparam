from setuptools import setup
from setuptools.extension import Extension
from Cython.Build import cythonize

import numpy as np


extensions = [
    Extension(
        "stoseg",
        ["markov/main.cpp", "markov/wrapper.cpp"],  # source files
        language="c++",
        extra_compile_args=["-std=c++11"],
        include_dirs=[np.get_include()]
    )
]

setup(
    ext_modules=cythonize(extensions),
)
