// Reaktoro is a unified framework for modeling chemically reactive systems.
//
// Copyright © 2014-2022 Allan Leal
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

#include "Utils.hpp"

// Reaktoro includes
#include <Reaktoro/Common/Algorithms.hpp>
#include <Reaktoro/Common/Exception.hpp>
#include <Reaktoro/Common/Units.hpp>
#include <Reaktoro/Core/ChemicalSystem.hpp>
#include <Reaktoro/Core/Phase.hpp>

namespace Reaktoro {
namespace detail {

auto molarMasses(const SpeciesList& species) -> ArrayXd
{
    ArrayXd molar_masses(species.size());
    transform(species, molar_masses, [](auto&& s) { return s.molarMass(); });
    return molar_masses;
}

auto computeSpeciesAmount(const ChemicalSystem& system, Index ispecies, real value, Chars unit) -> real
{
    if(unit == "mol")
        return value;

    if(units::convertible(unit, "kg"))
    {
        const auto molarmass = system.species(ispecies).molarMass(); // in kg/mol
        value = units::convert(value, unit, "kg"); // from some mass unit to kg
        return value / molarmass; // from kg to mol
    }
    else if(units::convertible(unit, "mol"))
        return units::convert(value, unit, "mol"); // from some amount unit to mol
    else errorif("Provided unit `", unit, "` should be convertible to mol or kg.");
}

auto resolveElementIndexAux(const ElementList& elementlist, Index index) -> Index
{
    return index;
}

auto resolveElementIndexAux(const ElementList& elementlist, int index) -> Index
{
    return index;
}

auto resolveElementIndexAux(const ElementList& elementlist, const String& symbol) -> Index
{
    return elementlist.index(symbol);
}

auto resolveElementIndex(const ElementList& elementlist, StringOrIndex element) -> Index
{
    return std::visit([&](auto&& arg) { return resolveElementIndexAux(elementlist, arg); }, element);
}

auto resolveElementIndex(const ChemicalSystem& system, StringOrIndex element) -> Index
{
    return resolveElementIndex(system.elements(), element);
}

auto resolveElementIndex(const Phase& phase, StringOrIndex element) -> Index
{
    return resolveElementIndex(phase.elements(), element);
}

auto resolveSpeciesIndexAux(const SpeciesList& specieslist, Index index) -> Index
{
    return index;
}

auto resolveSpeciesIndexAux(const SpeciesList& specieslist, int index) -> Index
{
    return index;
}

auto resolveSpeciesIndexAux(const SpeciesList& specieslist, const String& name) -> Index
{
    return specieslist.index(name);
}

auto resolveSpeciesIndex(const SpeciesList& specieslist, StringOrIndex species) -> Index
{
    return std::visit([&](auto&& arg) { return resolveSpeciesIndexAux(specieslist, arg); }, species);
}

auto resolveSpeciesIndex(const ChemicalSystem& system, StringOrIndex species) -> Index
{
    return resolveSpeciesIndex(system.species(), species);
}

auto resolveSpeciesIndex(const Phase& phase, StringOrIndex species) -> Index
{
    return resolveSpeciesIndex(phase.species(), species);
}

auto resolvePhaseIndexAux(const PhaseList& phaselist, Index index) -> Index
{
    return index;
}

auto resolvePhaseIndexAux(const PhaseList& phaselist, int index) -> Index
{
    return index;
}

auto resolvePhaseIndexAux(const PhaseList& phaselist, const String& name) -> Index
{
    return phaselist.index(name);
}

auto resolvePhaseIndex(const PhaseList& phaselist, StringOrIndex phase) -> Index
{
    return std::visit([&](auto&& arg) { return resolvePhaseIndexAux(phaselist, arg); }, phase);
}

auto resolvePhaseIndex(const ChemicalSystem& system, StringOrIndex phase) -> Index
{
    return resolvePhaseIndex(system.phases(), phase);
}

auto stringfyAux(Index index) -> String
{
    return std::to_string(index);
}

auto stringfyAux(int index) -> String
{
    return std::to_string(index);
}

auto stringfyAux(const String& name) -> String
{
    return name;
}

auto stringfy(StringOrIndex value) -> String
{
    return std::visit([&](auto&& arg) { return stringfyAux(arg); }, value);
}

auto assembleFormulaVector(const Species& species, const ElementList& elements) -> VectorXd
{
    const auto num_elements = elements.size();
    const auto num_components = num_elements + 1;
    VectorXd A(num_components);
    for(auto j = 0; j < num_elements; ++j)
        A[j] = species.elements().coefficient(elements[j].symbol());
    A[num_elements] = species.charge();
    return A;
}

auto assembleFormulaMatrix(const SpeciesList& species, const ElementList& elements) -> MatrixXd
{
    const auto num_elements = elements.size();
    const auto num_components = num_elements + 1;
    const auto num_species = species.size();
    MatrixXd A(num_components, num_species);
    for(auto i = 0; i < num_species; ++i)
        for(auto j = 0; j < num_elements; ++j)
            A(j, i) = species[i].elements().coefficient(elements[j].symbol());
    for(auto i = 0; i < num_species; ++i)
        A(num_elements, i) = species[i].charge();
    return A;
}

auto extractNames(const SpeciesList& list) -> Strings
{
    return vectorize(list, RKT_LAMBDA(x, x.name()));
}

auto extractNames(const ElementList& list) -> Strings
{
    return vectorize(list, RKT_LAMBDA(x, x.name()));
}

auto extractNames(const PhaseList& list) -> Strings
{
    return vectorize(list, RKT_LAMBDA(x, x.name()));
}

auto isChargeBalanced(const Reaction& reaction) -> bool
{
    return true; // replace by code
}

auto isElementBalanced(const Reaction& reaction) -> bool
{
    return true; // replace by code
}

} // namespace detail
} // namespace Reaktoro
