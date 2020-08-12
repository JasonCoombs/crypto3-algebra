//---------------------------------------------------------------------------//
// Copyright (c) 2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef ALGEBRA_FF_FP3_HPP
#define ALGEBRA_FF_FP3_HPP

#include <nil/algebra/fields/fp2.hpp>
#include <nil/algebra/fields/element.hpp>

#include <nil/algebra/fields/detail/exponentiation.hpp>

namespace nil {
    namespace algebra {
        namespace fields {

            /**
             * Arithmetic in the field F[p^3].
             *
             * Let p := modulus. This interface provides arithmetic for the extension field
             * Fp3 = Fp[U]/(U^3-non_residue), where non_residue is in Fp.
             *
             * ASSUMPTION: p = 1 (mod 6)
             */
            template<std::size_t ModulusBits, std::size_t GeneratorBits>
            struct fp3 {
                typedef element<fp<ModulusBits, GeneratorBits>, number_type> non_residue_type;

                constexpr static const std::size_t modulus_bits = ModulusBits;
                typedef boost::multiprecision::number<
                    backends::cpp_int_backend<modulus_bits, modulus_bits, boost::multiprecision::unsigned_magnitude,
                                              boost::multiprecision::unchecked, void>>
                    modulus_type;

                constexpr static const std::size_t generator_bits = GeneratorBits;
                typedef boost::multiprecision::number<boost::multiprecision::backends::cpp_int_backend<
                    generator_bits, generator_bits, boost::multiprecision::unsigned_magnitude,
                    boost::multiprecision::unchecked, void>>
                    generator_type;
            };

        }   // namespace fields
    }    // namespace algebra
}    // namespace nil

#endif    // ALGEBRA_FF_FP2_HPP
