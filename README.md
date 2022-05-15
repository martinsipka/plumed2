This is a fork of [PLUMED repository](https://www.plumed.org/). It contains small modification that can be employed to use collective variables and their gradients calculated in another program compatible with PLUMED cmd interface. The typical workflow is as follows:

 - Initialize plumed calculator from plumed.dat file. **Set correct units (important!)**
 - Run MD simulation calculate the energy and forces from unbiased Hamiltonian and calculate also CVs with their gradients. 
 - Send CVs and their gradients to PLUMED using cmd interface and methods implemented for this reason. 
 - Get bias and biasing forces from plumed after bias calculation **Careful about the units the collective variables are in! PLUMED does not know the type of CV constructed.**

An example ASE calculator for this workflow is available in TODO. 

If you use this library please cite:

    @misc{https://doi.org/10.48550/arxiv.2203.08097,
	  doi = {10.48550/ARXIV.2203.08097},
	  url = {https://arxiv.org/abs/2203.08097},
	  author = {Šípka, Martin and Erlebach, Andreas and Grajciar, Lukáš}
	  keywords = {Chemical Physics (physics.chem-ph), FOS: Physical sciences, 	FOS: Physical sciences}, 
	  title = {Understanding chemical reactions via variational autoencoder and atomic representations},
	  publisher = {arXiv},


