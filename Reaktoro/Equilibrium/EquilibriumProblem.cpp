// Reaktoro is a unified framework for modeling chemically reactive systems.
//
// Copyright © 2014-2021 Allan Leal
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library. If not, see <http://www.gnu.org/licenses/>.

#include "EquilibriumProblem.hpp"

// Reaktoro includes
#include <Reaktoro/Common/Exception.hpp>
#include <Reaktoro/Core/ChemicalState.hpp>

namespace Reaktoro {
namespace detail {

/// Return an EquilibriumSpecs object that represent the specifications of a Gibbs energy minimization problem.
inline auto createEquilibriumSpecs(const ChemicalSystem& system) -> EquilibriumSpecs
{
    EquilibriumSpecs specs(system);
    specs.temperature();
    specs.pressure();
    return specs;
}

} // namespace detail

EquilibriumProblem::EquilibriumProblem(const ChemicalSystem& system)
: EquilibriumProblem(detail::createEquilibriumSpecs(system))
{}

EquilibriumProblem::EquilibriumProblem(const EquilibriumSpecs& specs)
: EquilibriumConditions(specs), EquilibriumRestrictions(specs.system())
{}

} // namespace Reaktoro
