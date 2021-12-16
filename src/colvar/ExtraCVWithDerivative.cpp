/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   Copyright (c) 2017-2020 The plumed team
   (see the PEOPLE file at the root of the distribution for a list of names)

   See http://www.plumed.org for more information.

   This file is part of plumed, version 2.

   plumed is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   plumed is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with plumed.  If not, see <http://www.gnu.org/licenses/>.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
#include "Colvar.h"
#include "ActionRegister.h"
#include "core/PlumedMain.h"
#include "core/Atoms.h"

#include <string>
#include <cmath>

namespace PLMD {
namespace colvar {

//+PLUMEDOC COLVAR EngineCV
/*
XX

\par Examples

XX

*/
//+ENDPLUMEDOC


class EngineCV : public Colvar {
  std::string name;
  int nAtoms = 0;
  bool pbc;
public:
  explicit EngineCV(const ActionOptions&);
// active methods:
  void prepare() override;
  void calculate() override;

  static void registerKeywords( Keywords& keys );
};


using namespace std;


PLUMED_REGISTER_ACTION(EngineCV,"ENGINECV")

EngineCV::EngineCV(const ActionOptions&ao):
  PLUMED_COLVAR_INIT(ao),
  pbc(true)
{
  parse("NAME",name);
  //CAREFUL NEED TO REWRITE

  //log<<"  name: "<<name<<"\n";

  addValueWithDerivatives();
  setNotPeriodic();

  vector<AtomNumber> atoms;
  parseAtomList("ATOMS",atoms);

  //We currently expect our CV to be function of every atom
  nAtoms = plumed.getAtoms().getNatoms();

  requestAtoms(atoms);
  //log << nAtoms << '\n';
}

void EngineCV::registerKeywords( Keywords& keys ) {
  Colvar::registerKeywords( keys );
  keys.remove("NUMERICAL_DERIVATIVES");
  keys.add("compulsory","NAME","name of the CV as computed by the MD engine");
  keys.add("atoms","ATOMS","the list of atoms involved TODO is it needed?");
}

void EngineCV::prepare() {
/// \todo: notify Atoms that this is requested
}

// calculator
void EngineCV::calculate() {
  double value=plumed.getAtoms().getExtraCV(name);
  double* grad=plumed.getAtoms().getExtraCVDerivative(name);
  // Is there more than 1 return value?

  //log << "We got something for " << name << " value "<< value << " grad " << grad[0] << "\n";


  setValue(value);

  // 2nd return value: gradient: numpy array of (natoms, 3)

  int stride = 3;
  //TODO HOW MANY ATOMS WE HAVE?
  for(int i=0; i<nAtoms; i++) {
    //log << "elements: " << grad[i*stride] << grad[i*stride+1] << grad[i*stride+2] << '\n';
    Vector gi(grad[i*stride],
                grad[i*stride+1],
                grad[i*stride+2]);
    //log << "Vector constructed" << '\n';
    setAtomsDerivatives(getPntrToValue(), i,gi);
    //log << "Derivative set" << '\n';
  }

  setBoxDerivativesNoPbc();	// ??
  //log << "We gut " << "\n";
}

}
}
