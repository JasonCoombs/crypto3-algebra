//---------------------------------------------------------------------------//
// Copyright (c) 2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
//
// MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//---------------------------------------------------------------------------//

#ifndef CRYPTO3_ALGEBRA_CURVES_MNT6_BASIC_POLICY_HPP
#define CRYPTO3_ALGEBRA_CURVES_MNT6_BASIC_POLICY_HPP

#include <nil/crypto3/algebra/fields/mnt6/base_field.hpp>
#include <nil/crypto3/algebra/fields/mnt6/scalar_field.hpp>

#include <nil/crypto3/algebra/fields/fp3.hpp>
#include <nil/crypto3/algebra/fields/fp6_2over3.hpp>

#include <nil/crypto3/detail/literals.hpp>

namespace nil {
    namespace crypto3 {
        namespace algebra {
            namespace curves {
                namespace detail {

                    using namespace algebra;
                    /** @brief A struct representing details about base and scalar fields.
                    *    @tparam ModulusBits size of the base field in bits 
                    *
                    */
                    template<std::size_t ModulusBits = 298>
                    struct mnt6_basic_policy { };

                    /** @brief A struct representing details about base and scalar fields of the size 298 bits.
                    *
                    */
                    template<>
                    struct mnt6_basic_policy<298> {
                        constexpr static const std::size_t base_field_bits = 298; ///< size of the base field in bits 
                        typedef fields::mnt6_fq<base_field_bits> g1_field_type;
                        using base_field_type = g1_field_type;
                        typedef typename fields::fp3<base_field_type> g2_field_type;
                        typedef typename fields::fp6_2over3<base_field_type> gt_field_type;

                        typedef typename base_field_type::modulus_type number_type;
                        typedef typename base_field_type::extended_modulus_type extended_number_type;

                        constexpr static const number_type base_field_modulus = base_field_type::modulus; ///< characteristic of the base field  

                        constexpr static const std::size_t scalar_field_bits = 298; ///< size of the scalar field (order of the group of points) in bits 
                        typedef fields::mnt6_scalar_field<scalar_field_bits> scalar_field_type;
                        constexpr static const number_type scalar_field_modulus = scalar_field_type::modulus; ///< characteristic of the scalar field (order of the group of points)

                        constexpr static const number_type p = base_field_modulus; ///< characteristic of the base field  
                        constexpr static const number_type q = scalar_field_modulus;///< characteristic of the scalar field (order of the group of points) 

                        constexpr static const number_type a = number_type(0x0B);///< coefficient of short Weierstrass curve $y^2=x^3+a*x+b$
                        constexpr static const number_type b = number_type(
                            0xD68C7B1DC5DD042E957B71C44D3D6C24E683FC09B420B1A2D263FDE47DDBA59463D0C65282_cppui296);///< coefficient of short Weierstrass curve $y^2=x^3+a*x+b$
                    };

                    constexpr typename mnt6_basic_policy<298>::number_type const mnt6_basic_policy<298>::a;

                    constexpr typename mnt6_basic_policy<298>::number_type const mnt6_basic_policy<298>::b;

                    constexpr typename std::size_t const mnt6_basic_policy<298>::base_field_bits;

                    constexpr typename std::size_t const mnt6_basic_policy<298>::scalar_field_bits;

                    constexpr typename mnt6_basic_policy<298>::number_type const mnt6_basic_policy<298>::p;

                    constexpr typename mnt6_basic_policy<298>::number_type const mnt6_basic_policy<298>::q;

                }    // namespace detail
            }        // namespace curves
        }            // namespace algebra
    }                // namespace crypto3
}    // namespace nil

#endif    // CRYPTO3_ALGEBRA_CURVES_MNT6_BASIC_POLICY_HPP