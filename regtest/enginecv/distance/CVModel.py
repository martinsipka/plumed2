from ase import Atoms
import torch
from torch.autograd import grad

# The CV function actually called
def cv(atoms):
    x = torch.tensor(atoms.positions)
    x.requires_grad=True
    
    cv = (x[52]-x[77]).pow(2).sum().sqrt()
    grad = torch.autograd.grad(cv, x)[0]
    return cv.detach().numpy(), grad.detach().numpy()
