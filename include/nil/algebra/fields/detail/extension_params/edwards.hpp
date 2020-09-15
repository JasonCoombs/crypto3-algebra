//---------------------------------------------------------------------------//
// Copyright (c) 2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef ALGEBRA_FIELDS_EDWARDS_EXTENSION_PARAMS_HPP
#define ALGEBRA_FIELDS_EDWARDS_EXTENSION_PARAMS_HPP

#include <nil/algebra/fields/detail/element/fp.hpp>
#include <nil/algebra/fields/detail/element/fp2.hpp>
#include <nil/algebra/fields/params.hpp>

#include <nil/algebra/fields/edwards/base_field.hpp>
#include <nil/algebra/fields/fp2.hpp>

#include <nil/algebra/detail/literals.hpp>

namespace nil {
    namespace algebra {
        namespace fields {
            namespace detail {

                using namespace nil::algebra;

                template<typename FieldType>
                struct fp3_extension_params;

                template<typename FieldType>
                struct fp6_2over3_extension_params;

                /************************* EDWARDS ***********************************/

                template<std::size_t ModulusBits, std::size_t GeneratorBits>
                class fp3_extension_params<fields::edwards_base_field<ModulusBits, GeneratorBits>>
                    : public params<fields::edwards_base_field<ModulusBits, GeneratorBits>> {

                    typedef params<fields::edwards_base_field<ModulusBits, GeneratorBits>> policy_type;

                public:
                    typedef typename policy_type::number_type number_type;
                    typedef typename policy_type::modulus_type modulus_type;

                    constexpr static const modulus_type modulus = policy_type::modulus;

                    typedef element_fp<policy_type> non_residue_type;
                    typedef element_fp<policy_type> underlying_type;

                    constexpr static const modulus_type non_residue = modulus_type(0x3D);
                };

                template<std::size_t ModulusBits, std::size_t GeneratorBits>
                class fp6_2over3_extension_params<fields::edwards_base_field<ModulusBits, GeneratorBits>>
                    : public params<fields::edwards_base_field<ModulusBits, GeneratorBits>> {

                    typedef params<fields::edwards_base_field<ModulusBits, GeneratorBits>> policy_type;

                public:
                    typedef typename policy_type::number_type number_type;
                    typedef typename policy_type::modulus_type modulus_type;

                    constexpr static const modulus_type modulus = policy_type::modulus;

                    typedef element_fp<policy_type> non_residue_type;
                    typedef element_fp3<fp3_extension_params<field_type>> underlying_type;

                    constexpr static const modulus_type non_residue = modulus_type(0x3D);
                };

                template<std::size_t ModulusBits, std::size_t GeneratorBits>
                constexpr typename fp3_extension_params<edwards_base_field<ModulusBits, GeneratorBits>>::modulus_type const
                    fp3_extension_params<edwards_base_field<ModulusBits, GeneratorBits>>::non_residue;
                template<std::size_t ModulusBits, std::size_t GeneratorBits>
                constexpr typename fp6_2over3_extension_params<edwards_base_field<ModulusBits, GeneratorBits>>::modulus_type const
                    fp6_2over3_extension_params<edwards_base_field<ModulusBits, GeneratorBits>>::non_residue;

                template<std::size_t ModulusBits, std::size_t GeneratorBits>
                constexpr typename fp3_extension_params<edwards_base_field<ModulusBits, GeneratorBits>>::modulus_type const
                    fp3_extension_params<edwards_base_field<ModulusBits, GeneratorBits>>modulus;
                template<std::size_t ModulusBits, std::size_t GeneratorBits>
                constexpr typename fp6_2over3_extension_params<edwards_base_field<ModulusBits, GeneratorBits>>::modulus_type const
                    fp6_2over3_extension_params<edwards_base_field<ModulusBits, GeneratorBits>>modulus;

            }    // namespace detail
        }        // namespace fields
    }            // namespace algebra
}    // namespace nil

#endif    // ALGEBRA_FIELDS_EDWARDS_EXTENSION_PARAMS_HPP