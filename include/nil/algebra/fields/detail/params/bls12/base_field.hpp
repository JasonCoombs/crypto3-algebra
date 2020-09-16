//---------------------------------------------------------------------------//
// Copyright (c) 2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef ALGEBRA_FIELDS_BLS12_FQ_PARAMS_HPP
#define ALGEBRA_FIELDS_BLS12_FQ_PARAMS_HPP

#include <nil/algebra/fields/detail/element/fp.hpp>
#include <nil/algebra/fields/detail/element/fp2.hpp>
#include <nil/algebra/fields/detail/params/params.hpp>

#include <nil/algebra/fields/bls12/base_field.hpp>

#include <nil/algebra/detail/literals.hpp>

namespace nil {
    namespace algebra {
        namespace fields {
            namespace detail {

                template<>
                struct extension_params<bls12_base_field<381, CHAR_BIT>>
                    : public params<bls12_base_field<381, CHAR_BIT>> {
                private:
                    typedef params<bls12_base_field<381, CHAR_BIT>> policy_type;
                    typedef extension_params<bls12_base_field<381, CHAR_BIT>> element_policy_type;

                public:
                    typedef typename policy_type::number_type number_type;
                    typedef typename policy_type::modulus_type modulus_type;

                    constexpr static const modulus_type modulus = policy_type::modulus;
                    constexpr static const modulus_type group_order =
                        0xD0088F51CBFF34D258DD3DB21A5D66BB23BA5C279C2895FB39869507B587B120F55FFFF58A9FFFFDCFF7FFFFFFFD555_cppui380;

                    struct fp2{
                        /*constexpr static const std::size_t s = 3;
                        constexpr static const modulus_type t = 
                            0x5486F497186BF8E97A4F1D5445E4BD3C5B921CA1CE08D68CDCB3C92693D17A0A14C59FA2DBB94DDEA62926612F1DE023AD0C3390C30B8F6525D0B50E1234092CD7F23DA7CE36E862C586706C42279FAF9DAD63AEC705D564D54000038E31C7_cppui759;
                        constexpr static const modulus_type t_minus_1_over_2 = 
                            0x2A437A4B8C35FC74BD278EAA22F25E9E2DC90E50E7046B466E59E49349E8BD050A62CFD16DDCA6EF53149330978EF011D68619C86185C7B292E85A87091A04966BF91ED3E71B743162C338362113CFD7CED6B1D76382EAB26AA00001C718E3_cppui758;
                        constexpr static const std::array<modulus_type, 2> nqr_to_t = {
                            0x6AF0E0437FF400B6831E36D6BD17FFE48395DABC2D3435E77F76E17009241C5EE67992F72EC05F4C81084FBEDE3CC09_cppui379, 
                            0x135203E60180A68EE2E9C448D77A2CD91C3DEDD930B1CF60EF396489F61EB45E304466CF3E67FA0AF1EE7B04121BDEA2_cppui381};*/

                        typedef element_fp<element_policy_type> non_residue_type;

                        constexpr static const modulus_type non_residue = modulus_type(
                        0x1A0111EA397FE69A4B1BA7B6434BACD764774B84F38512BF6730D2A0F6B0F6241EABFFFEB153FFFFB9FEFFFFFFFFAAAA_cppui381);
                    };

                    struct fp6_3over2{
                        typedef element_fp2<element_policy_type> non_residue_type;

                        constexpr static const std::array<modulus_type, 2> non_residue = {1, 1};
                    };

                    struct fp12_2over3over2{
                        typedef element_fp2<element_policy_type> non_residue_type;

                        constexpr static const std::array<modulus_type, 2> non_residue = {1, 1};
                    };

                };

                template<>
                struct extension_params<bls12_base_field<377, CHAR_BIT>>
                    : public params<bls12_base_field<377, CHAR_BIT>> {
                private:
                    typedef params<bls12_base_field<377, CHAR_BIT>> policy_type;
                    typedef extension_params<bls12_base_field<377, CHAR_BIT>> element_policy_type;

                public:
                    typedef typename policy_type::number_type number_type;
                    typedef typename policy_type::modulus_type modulus_type;

                    constexpr static const modulus_type modulus = policy_type::modulus;
                    constexpr static const modulus_type group_order =
                        0xD71D230BE28875631D82E03650A49D8D116CF9807A89C78F79B117DD04A4000B85AEA2180000004284600000000000_cppui376;

                    struct fp2{
                        typedef element_fp<element_policy_type> non_residue_type;

                        constexpr static const modulus_type non_residue = modulus_type(
                        0x1AE3A4617C510EAC63B05C06CA1493B1A22D9F300F5138F1EF3622FBA094800170B5D44300000008508BFFFFFFFFFFC_cppui377);
                    };

                    struct fp6_3over2{
                        typedef element_fp2<element_policy_type> non_residue_type;

                        constexpr static const std::array<modulus_type, 2> non_residue = {0, 1};
                    };

                    struct fp12_2over3over2{
                        typedef element_fp2<element_policy_type> non_residue_type;

                        constexpr static const std::array<modulus_type, 2> non_residue = {0, 1};
                    };

                };

                constexpr typename extension_params<bls12_base_field<381, CHAR_BIT>>::modulus_type const
                    extension_params<bls12_base_field<381, CHAR_BIT>>::fp2::non_residue;
                constexpr typename extension_params<bls12_base_field<377, CHAR_BIT>>::modulus_type const
                    extension_params<bls12_base_field<377, CHAR_BIT>>::fp2::non_residue;
                

                constexpr std::array<typename extension_params<bls12_base_field<381, CHAR_BIT>>::modulus_type, 2> const
                    extension_params<bls12_base_field<381, CHAR_BIT>>::fp6_3over2::non_residue;
                constexpr std::array<typename extension_params<bls12_base_field<377, CHAR_BIT>>::modulus_type, 2> const
                    extension_params<bls12_base_field<377, CHAR_BIT>>::fp6_3over2::non_residue;

                constexpr std::array<typename extension_params<bls12_base_field<381, CHAR_BIT>>::modulus_type, 2> const
                    extension_params<bls12_base_field<381, CHAR_BIT>>::fp12_2over3over2::non_residue;
                constexpr std::array<typename extension_params<bls12_base_field<377, CHAR_BIT>>::modulus_type, 2> const
                    extension_params<bls12_base_field<377, CHAR_BIT>>::fp12_2over3over2::non_residue;

            }    // namespace detail
        }        // namespace fields
    }            // namespace algebra
}    // namespace nil

#endif    // ALGEBRA_FIELDS_BLS12_FQ_PARAMS_HPP
