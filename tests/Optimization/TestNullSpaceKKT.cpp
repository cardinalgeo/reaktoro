// Reaktor is a C++ library for computational reaction modelling.
//
// Copyright (C) 2014 Allan Leal
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "TestNullSpaceKKT.hpp"

// Reaktor includes
#include <Reaktor/Reaktor.hpp>

namespace Reaktor {
namespace {

auto test_solveNullSpaceKKT() -> void
{
    const unsigned m = 3;
    const unsigned n = 7;

    const Matrix M = arma::randu(n, n);

    SaddleProblem problem;
    problem.H = M*M.t();
    problem.A = arma::randu(m, n);
    problem.f = arma::randu(n);
    problem.g = arma::randu(m);

    SaddleResult result;

    solveNullSpaceKKT(problem, result);

    const auto& H = problem.H;
    const auto& A = problem.A;
    const auto& f = problem.f;
    const auto& g = problem.g;
    const auto& x = result.solution.x;
    const auto& y = result.solution.y;
    const double residualx = arma::norm(H*x - A.t()*y - f)/arma::norm(f);
    const double residualy = arma::norm(A*x - g)/arma::norm(g);

    ASSERT(residualx < 1e-15);
    ASSERT(residualy < 1e-15);
}

} // namespace

auto testSuiteNullSpaceKKT() -> cute::suite
{
    cute::suite s;

    s += CUTE(test_solveNullSpaceKKT);

    return s;
}

} // namespace Reaktor
