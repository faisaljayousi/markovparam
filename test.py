"""
Test script to test the varCond function.
"""

import numpy as np
from markov.main import varCond


if __name__ == '__main__':

    dep = np.array([[5, 3, 8, 7],
                    [2, 4, 6, 2],
                    [1, 7, 9, 1],
                    [5, 4, 4, 8]
                    ])

    result = varCond(dep, dx=1, dy=0)
    print(f"Parameter value: {result}")
