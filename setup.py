from setuptools import setup
from setuptools.extension import Extension
from Cython.Build import cythonize

import numpy as np


extensions = [
    Extension(
        name="stoseg",
        sources=["markov/main.cpp", "markov/wrapper.cpp"],
        language="c++",
        extra_compile_args=["-std=c++11"],
        include_dirs=[np.get_include()]
    )
]

setup(
    author=u"Faisal Jayousi",
    author_email="fjayousi90@gmail.com",
    ext_modules=cythonize(extensions),
    platforms=["linux", "windows"],
    license="MIT",
    python_requires=">=3.6",
    classifiers=[
        "Programming Language :: Python",
        "Programming Language :: C++",
        "Programming Language :: C",
        "Programming Language :: Cython",
    ]
)
