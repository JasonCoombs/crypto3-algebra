//---------------------------------------------------------------------------//
// Copyright (c) 2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef ALGEBRA_CURVES_EDWARDS_HPP
#define ALGEBRA_CURVES_EDWARDS_HPP

#include <nil/algebra/curves/detail/element/curve_weierstrass.hpp>
#include <nil/algebra/curves/detail/params/params.hpp>
#include <nil/algebra/curves/detail/edwards/g1.hpp>
#include <nil/algebra/curves/detail/edwards/g2.hpp>

#include <nil/algebra/fields/edwards/fq.hpp>
#include <nil/algebra/fields/edwards/fr.hpp>

#include <nil/algebra/detail/mp_def.hpp>

namespace nil {
    namespace algebra {
        namespace curves {

            using namespace algebra;

            /*
                The curve equation for a BN curve is:

                E/Fp: y^2 = x^3 + b.
            */

            /*
                Over Fp12_2over3over2
                y^2 = x^3 + b
                u^2 = -1
                xi = xi_a + xi_b u
                v^3 = xi
                w^2 = v
            */
            template<std::size_t ModulusBits = 183>
            struct edwards { };

            template<>
            struct edwards<183> {
                constexpr static const std::size_t base_field_bits = 183;
                typedef fields::edwards_fq<base_field_bits, CHAR_BIT> base_field_type;
                typedef typename base_field_type::modulus_type number_type;
                constexpr static const number_type base_field_modulus = base_field_type::modulus;

                constexpr static const std::size_t scalar_field_bits = 181;
                typedef fields::edwards_fr<scalar_field_bits, CHAR_BIT> scalar_field_type;
                constexpr static const number_type scalar_field_modulus = scalar_field_type::modulus;

                //typedef typename detail::element_curve_weierstrass<base_field_type::value_type> value_type;

                typedef typename detail::edwards_g1<183> g1_type;
                typedef typename detail::edwards_g2<183> g2_type;
                typedef typename nil::algebra::fields::detail::element_fp6_2over3<nil::algebra::fields::detail::arithmetic_params<edwards<183, CHAR_BIT>>> gt_type;

                typedef std::vector<typename g1_type> g1_vector;
                typedef std::vector<typename g2_type> g2_vector;

                constexpr static const number_type p = base_field_modulus;
                constexpr static const number_type q = scalar_field_modulus;

                constexpr static const number_type a = 0x01;
                constexpr static const number_type d = 0x64536D55979879327CF1306BB5A6277D254EF9776CE70;
                constexpr static const number_type x = 0x00;    //?
                constexpr static const number_type y = 0x00;    //?
            };

        }    // namespace curves
    }        // namespace algebra
}    // namespace nil

#endif    // ALGEBRA_CURVES_EDWARDS_HPP
