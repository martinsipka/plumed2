#!/usr/bin/env python
# Simple initial test of the EngineCV plugin. Replicates one randomly chosen distance, based on this plumed.dat file. 
# 
#d1: DISTANCE ATOMS=53,78
#
#PRINT ARG=d1 FILE=colvar FMT=%8.4f
#


import ase.io
from ase.calculators.lj import LennardJones

import sys,os
import numpy as np

from ase.units import fs

from ase.calculators.lj import LennardJones

import custom_plumed_calc as ase_plumed

ffcalc = LennardJones(sigma=1, epsilon=1)

traj = ase.io.read('trajectory.xyz', index=':', format='xyz')
print(traj[0].pbc)

# Read plumed.dat file as list of commands
with open("plumed.dat") as file:
    plumed_dat = file.readlines()
    plumed_dat = [line.rstrip() for line in plumed_dat]

calc = ase_plumed.Plumed(ffcalc, plumed_dat, timestep=1000*fs, atoms=traj[0])

for atoms in traj:
    atoms.set_cell((5.0388,5.0388,5.0388))
    atoms.set_pbc((True, True, True))
    calc.calculate(atoms)
