//---------------------------------------------------------------------------//
// Copyright (c) 2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
// Copyright (c) 2020 Ilias Khairullin <ilias@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef ALGEBRA_CURVES_MNT6_HPP
#define ALGEBRA_CURVES_MNT6_HPP

#include <nil/algebra/curves/detail/mnt6/g1.hpp>
#include <nil/algebra/curves/detail/mnt6/g2.hpp>
#include <nil/algebra/curves/detail/mnt6/basic_policy.hpp>

#include <nil/algebra/fields/fp6_2over3.hpp>

namespace nil {
    namespace algebra {
        namespace curves {

            using namespace nil::algebra;

            template<std::size_t ModulusBits = 298, std::size_t GeneratorBits = CHAR_BIT>
            struct mnt6 { };

            template<>
            struct mnt6<298, CHAR_BIT> {

                using policy_type = detail::mnt6_basic_policy<298>;

                typedef typename policy_type::base_field_type base_field_type;
                typedef typename policy_type::scalar_field_type scalar_field_type;
                typedef typename policy_type::number_type number_type;

                constexpr static const std::size_t base_field_bits = policy_type::base_field_bits;
                constexpr static const number_type p = policy_type::p;

                constexpr static const std::size_t scalar_field_bits = policy_type::scalar_field_bits;
                constexpr static const number_type q = policy_type::q;

                typedef typename detail::mnt6_g1<base_field_bits, CHAR_BIT> g1_type;
                typedef typename detail::mnt6_g2<base_field_bits, CHAR_BIT> g2_type;

                typedef typename fields::fp6_2over3<base_field_type>::value_type gt_type;

                typedef std::vector<g1_type> g1_vector;
                typedef std::vector<g2_type> g2_vector;
            };

            template<std::size_t ModulusBits = 298, std::size_t GeneratorBits = CHAR_BIT>
            using mnt6_g1 = typename mnt6<ModulusBits, GeneratorBits>::g1_type;

            template<std::size_t ModulusBits = 298, std::size_t GeneratorBits = CHAR_BIT>
            using mnt6_g2 = typename mnt6<ModulusBits, GeneratorBits>::g2_type;

            template<std::size_t ModulusBits = 298, std::size_t GeneratorBits = CHAR_BIT>
            using mnt6_gt = typename mnt6<ModulusBits, GeneratorBits>::gt_type;

        }    // namespace curves
    }        // namespace algebra
}    // namespace nil

#endif    // ALGEBRA_CURVES_MNT6_HPP
