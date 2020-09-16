//---------------------------------------------------------------------------//
// Copyright (c) 2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef ALGEBRA_FIELDS_MNT6_FQ_PARAMS_HPP
#define ALGEBRA_FIELDS_MNT6_FQ_PARAMS_HPP

#include <nil/algebra/fields/detail/element/fp.hpp>
#include <nil/algebra/fields/detail/element/fp2.hpp>
#include <nil/algebra/fields/detail/params/params.hpp>

#include <nil/algebra/fields/mnt6/base_field.hpp>

#include <nil/algebra/detail/literals.hpp>

namespace nil {
    namespace algebra {
        namespace fields {
            namespace detail {

                template<std::size_t ModulusBits, std::size_t GeneratorBits>
                struct extension_params<mnt6_base_field<ModulusBits, GeneratorBits>>
                    : public params<mnt6_base_field<ModulusBits, GeneratorBits>> {
                private:
                    typedef params<mnt6_base_field<ModulusBits, GeneratorBits>> policy_type;
                    typedef extension_params<mnt6_base_field<ModulusBits, GeneratorBits>> element_policy_type;

                public:
                    typedef typename policy_type::number_type number_type;
                    typedef typename policy_type::modulus_type modulus_type;

                    constexpr static const modulus_type modulus = policy_type::modulus;
                    constexpr static const modulus_type group_order =
                        0x1DE7BDE6A39D133124ED3D82A47657764B1AE7A20CA7DA4A603C92EB569DDA19A5200000000_cppui297;

                    struct fp3{
                        constexpr static const modulus_type group_order =
                            0x1A1E3D618BA643D0F7F10B59BD7DB6981AD661CC756DCF7EC82F4F320CF354C814FAB1F72198E11AAE5A65BFAC8866CDA5F25E91FE3405FB619822AE7756E3F1CBC0B60FBD44114FC23E7CC3932D198CBE6F3DF9DF28E58FF8DBDC80329943BF3F003B81A48CADD598E4CEF600000000_cppui893;

                        typedef element_fp<element_policy_type> non_residue_type;

                        constexpr static const modulus_type non_residue = modulus_type(0x05);
                    };

                    struct fp6_2over3{
                        typedef element_fp<element_policy_type> non_residue_type;

                        constexpr static const modulus_type non_residue = modulus_type(0x05);
                    };

                };

                template<std::size_t ModulusBits, std::size_t GeneratorBits>
                constexpr typename params<mnt6_base_field<ModulusBits, GeneratorBits>>::modulus_type const
                    extension_params<mnt6_base_field<ModulusBits, GeneratorBits>>::fp3::non_residue;

                template<std::size_t ModulusBits, std::size_t GeneratorBits>
                constexpr typename params<mnt6_base_field<ModulusBits, GeneratorBits>>::modulus_type const
                    extension_params<mnt6_base_field<ModulusBits, GeneratorBits>>::fp6_2over3::non_residue;

            }    // namespace detail
        }        // namespace fields
    }            // namespace algebra
}    // namespace nil

#endif    // ALGEBRA_FIELDS_MNT6_FQ_PARAMS_HPP
