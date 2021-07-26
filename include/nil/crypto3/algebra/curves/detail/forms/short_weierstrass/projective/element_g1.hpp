//---------------------------------------------------------------------------//
// Copyright (c) 2020-2021 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020-2021 Nikita Kaskov <nbering@nil.foundation>
// Copyright (c) 2020-2021 Ilias Khairullin <ilias@nil.foundation>
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

#ifndef CRYPTO3_ALGEBRA_CURVES_SHORT_WEIERSTRASS_G1_ELEMENT_PROJECTIVE_HPP
#define CRYPTO3_ALGEBRA_CURVES_SHORT_WEIERSTRASS_G1_ELEMENT_PROJECTIVE_HPP

#include <nil/crypto3/algebra/curves/detail/scalar_mul.hpp>
#include <nil/crypto3/algebra/curves/detail/forms.hpp>

#include <nil/crypto3/algebra/curves/detail/forms/short_weierstrass/coordinates.hpp>
#include <nil/crypto3/algebra/curves/detail/forms/short_weierstrass/projective/add_1998_cmo_2.hpp>
#include <nil/crypto3/algebra/curves/detail/forms/short_weierstrass/projective/dbl_2007_bl.hpp>

namespace nil {
    namespace crypto3 {
        namespace algebra {
            namespace curves {
                namespace detail {
                    /** @brief A struct representing a group G1 of elliptic curve. 
                     *    @tparam CurveParams Parameters of the group 
                     *    @tparam Form Form of the curve 
                     *    @tparam Coordinates Representation coordinates of the group element 
                     */
                    // template<typename CurveParams, 
                    //          forms Form, 
                    //          short_weierstrass_coordinates Coordinates>
                    // struct short_weierstrass_element_g1;

                    /** @brief A struct representing an element from the group G1 of short Weierstrass curve of 
                     *  projective coordinates representation.
                     *  Description: https://hyperelliptic.org/EFD/g1p/auto-shortw-projective.html
                     *
                     */
                    template<typename CurveParams, 
                             typename Adder = short_weierstrass_element_g1_projective_add_1998_cmo_2, 
                             typename Doubler = short_weierstrass_element_g1_projective_dbl_2007_bl>
                    struct short_weierstrass_element_g1_projective {

                        using params_type = CurveParams;
                        using field_type = typename params_type::field_type;
                    private:
                        using field_value_type = typename field_type::value_type;
                    public:
                        using group_type = typename params_type::group_type;

                        constexpr static const forms form = 
                            forms::short_weierstrass;
                        constexpr static const 
                            short_weierstrass_coordinates coordinates = 
                            short_weierstrass_coordinates::projective;

                        field_value_type X;
                        field_value_type Y;
                        field_value_type Z;

                        /*************************  Constructors and zero/one  ***********************************/

                        /** @brief
                         *    @return the point at infinity by default
                         *
                         */
                        constexpr short_weierstrass_element_g1_projective() : short_weierstrass_element_g1_projective(
                            params_type::zero_fill[0], 
                            params_type::zero_fill[1], 
                            params_type::zero_fill[2]) {};

                        /** @brief
                         *    @return the selected point (X:Y:Z)
                         *
                         */
                        constexpr short_weierstrass_element_g1_projective(field_value_type X,
                                                  field_value_type Y,
                                                  field_value_type Z) {
                            this->X = X;
                            this->Y = Y;
                            this->Z = Z;
                        };

                        /** @brief Get the point at infinity
                         *
                         */
                        constexpr static short_weierstrass_element_g1_projective zero() {
                            return short_weierstrass_element_g1_projective();
                        }

                        /** @brief Get the generator of group G1
                         *
                         */
                        constexpr static short_weierstrass_element_g1_projective one() {
                            return short_weierstrass_element_g1_projective(params_type::one_fill[0], params_type::one_fill[1], 
                                params_type::one_fill[2]);
                        }

                        /*************************  Comparison operations  ***********************************/

                        constexpr bool operator==(const short_weierstrass_element_g1_projective &other) const {
                            if (this->is_zero()) {
                                return other.is_zero();
                            }

                            if (other.is_zero()) {
                                return false;
                            }

                            /* now neither is O */

                            // X1/Z1 = X2/Z2 <=> X1*Z2 = X2*Z1
                            if ((this->X * other.Z) != (other.X * this->Z)) {
                                return false;
                            }

                            // Y1/Z1 = Y2/Z2 <=> Y1*Z2 = Y2*Z1
                            if ((this->Y * other.Z) != (other.Y * this->Z)) {
                                return false;
                            }

                            return true;
                        }

                        constexpr bool operator!=(const short_weierstrass_element_g1_projective &other) const {
                            return !(operator==(other));
                        }
                        /** @brief
                         *
                         * @return true if element from group G1 is the point at infinity
                         */
                        constexpr bool is_zero() const {
                            return (this->X.is_zero() && this->Z.is_zero());
                        }
                        
                        /** @brief
                         *
                         * @return true if element from group G1 lies on the elliptic curve
                         */
                        constexpr bool is_well_formed() const {
                            if (this->is_zero()) {
                                return true;
                            } else {
                                /*
                                  y^2 = x^3 + ax + b

                                  We are using projective, so equation we need to check is actually

                                  (y/z)^2 = (x/z)^3 + a (x/z) + b
                                  z y^2 = x^3  + a z^2 x + b z^3

                                  z (y^2 - b z^2) = x ( x^2 + a z^2)
                                */
                                const field_value_type X2 = this->X.squared();
                                const field_value_type Y2 = this->Y.squared();
                                const field_value_type Z2 = this->Z.squared();

                                return (this->Z * (Y2 - params_type::b * Z2) == this->X * (X2 + params_type::a * Z2));
                            }
                        }

                        /*************************  Arithmetic operations  ***********************************/

                        constexpr short_weierstrass_element_g1_projective operator=(const short_weierstrass_element_g1_projective &other) {
                            // handle special cases having to do with O
                            this->X = other.X;
                            this->Y = other.Y;
                            this->Z = other.Z;

                            return *this;
                        }

                        constexpr short_weierstrass_element_g1_projective operator+(const short_weierstrass_element_g1_projective &other) const {
                            // handle special cases having to do with O
                            if (this->is_zero()) {
                                return other;
                            }

                            if (other.is_zero()) {
                                return (*this);
                            }

                            if (*this == other) {
                                return this->doubled();
                            }

                            return Adder::process(*this, other);
                        }

                        constexpr short_weierstrass_element_g1_projective operator-() const {
                            return short_weierstrass_element_g1_projective(this->X, -this->Y, this->Z);
                        }

                        constexpr short_weierstrass_element_g1_projective operator-(const short_weierstrass_element_g1_projective &other) const {
                            return (*this) + (-other);
                        }
                        
                        /** @brief
                         *
                         * @return doubled element from group G1
                         */
                        constexpr short_weierstrass_element_g1_projective doubled() const {
                            return Doubler::process(*this);
                        }

                        /** @brief
                         *
                         * “Mixed addition” refers to the case Z2 known to be 1.
                         * @return addition of two elements from group G1
                         */
                        constexpr short_weierstrass_element_g1_projective mixed_add(const short_weierstrass_element_g1_projective &other) const {

                            // NOTE: does not handle O and pts of order 2,4
                            // http://www.hyperelliptic.org/EFD/g1p/auto-shortw-projective.html#addition-add-1998-cmo-2

                            if (this->is_zero()) {
                                return other;
                            }

                            if (other.is_zero()) {
                                return (*this);
                            }

                            // Because for some reasons it's not so
                            // assert(other.Z == field_value_type::one());

                            const field_value_type &X1Z2 =
                                (this->X);    // X1Z2 = X1*Z2 (but other is special and not zero)
                            const field_value_type X2Z1 = (this->Z) * (other.X);    // X2Z1 = X2*Z1

                            // (used both in add and double checks)

                            const field_value_type &Y1Z2 =
                                (this->Y);    // Y1Z2 = Y1*Z2 (but other is special and not zero)
                            const field_value_type Y2Z1 = (this->Z) * (other.Y);    // Y2Z1 = Y2*Z1

                            if (X1Z2 == X2Z1 && Y1Z2 == Y2Z1) {
                                return this->doubled();
                            }

                            const field_value_type u = Y2Z1 - this->Y;                // u = Y2*Z1-Y1
                            const field_value_type uu = u.squared();                  // uu = u2
                            const field_value_type v = X2Z1 - this->X;                // v = X2*Z1-X1
                            const field_value_type vv = v.squared();                  // vv = v2
                            const field_value_type vvv = v * vv;                      // vvv = v*vv
                            const field_value_type R = vv * this->X;                  // R = vv*X1
                            const field_value_type A = uu * this->Z - vvv - R - R;    // A = uu*Z1-vvv-2*R
                            const field_value_type X3 = v * A;                        // X3 = v*A
                            const field_value_type Y3 =
                                u * (R - A) - vvv * this->Y;                         // Y3 = u*(R-A)-vvv*Y1
                            const field_value_type Z3 = vvv * this->Z;    // Z3 = vvv*Z1

                            return short_weierstrass_element_g1_projective(X3, Y3, Z3);
                        }
                    };

                }    // namespace detail
            }        // namespace curves
        }            // namespace algebra
    }                // namespace crypto3
}    // namespace nil
#endif    // CRYPTO3_ALGEBRA_CURVES_SHORT_WEIERSTRASS_G1_ELEMENT_PROJECTIVE_HPP