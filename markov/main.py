import stoseg
import numpy as np


def varCond(dep: np.ndarray, dx: int, dy: int) -> float:
    param = stoseg.varCond(dep.astype(float).tolist(), int(dx), int(dy))
    return param
