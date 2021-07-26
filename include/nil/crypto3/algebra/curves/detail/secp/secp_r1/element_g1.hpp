//---------------------------------------------------------------------------//
// Copyright (c) 2021 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2021 Ilias Khairullin <ilias@nil.foundation>
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

#ifndef CRYPTO3_ALGEBRA_CURVES_SECP_R1_G1_ELEMENT_HPP
#define CRYPTO3_ALGEBRA_CURVES_SECP_R1_G1_ELEMENT_HPP

#include <nil/crypto3/algebra/curves/detail/secp/secp_r1/basic_policy.hpp>

#include <nil/crypto3/algebra/curves/detail/scalar_mul.hpp>

#include <nil/crypto3/detail/literals.hpp>

namespace nil {
    namespace crypto3 {
        namespace algebra {
            namespace curves {
                namespace detail {

                    /** @brief A struct representing a group G1 of BLS12 curve.
                     *    @tparam Version version of the curve
                     *
                     */
                    template<std::size_t Version>
                    struct secp_r1_g1;

                    /** @brief A struct representing an element from the group G1 of secp_r1 curve.
                     *    @tparam Version version of the curve
                     *
                     */
                    template<std::size_t Version>
                    struct element_secp_r1_g1 { };
                    /** @brief A struct representing an element from the group G1 of secp_r1 curve.
                     *
                     * The size of the group G1 in bits equals 256.
                     */
                    template<>
                    struct element_secp_r1_g1<256> {

                        using group_type = secp_r1_g1<256>;

                        using policy_type = secp_r1_basic_policy<256>;

                        typedef typename policy_type::g1_field_type::value_type g1_field_type_value;
                        using underlying_field_value_type = g1_field_type_value;

                        underlying_field_value_type X;
                        underlying_field_value_type Y;
                        underlying_field_value_type Z;

                        /*************************  Constructors and zero/one  ***********************************/

                        /** @brief
                         *    @return the point at infinity by default
                         *
                         */
                        constexpr element_secp_r1_g1() :
                            element_secp_r1_g1(policy_type::g1_zero_fill[0], policy_type::g1_zero_fill[1],
                                               policy_type::g1_zero_fill[2]) {};

                        /** @brief
                         *    @return the selected affine point $(X:Y:1)$
                         *
                         */
                        constexpr element_secp_r1_g1(const underlying_field_value_type &X,
                                                     const underlying_field_value_type &Y) :
                            X(X),
                            Y(Y), Z(underlying_field_value_type::one()) {};

                        /** @brief
                         *    @return the selected point (X:Y:Z)
                         *
                         */
                        constexpr element_secp_r1_g1(underlying_field_value_type X,
                                                     underlying_field_value_type Y,
                                                     underlying_field_value_type Z) {
                            this->X = X;
                            this->Y = Y;
                            this->Z = Z;
                        };
                        /** @brief Get the point at infinity
                         *
                         */
                        constexpr static element_secp_r1_g1 zero() {
                            return element_secp_r1_g1();
                        }
                        /** @brief Get the generator of group G1
                         *
                         */
                        constexpr static element_secp_r1_g1 one() {
                            return element_secp_r1_g1(policy_type::g1_one_fill[0], policy_type::g1_one_fill[1],
                                                      policy_type::g1_one_fill[2]);
                        }

                        /*************************  Comparison operations  ***********************************/

                        constexpr bool operator==(const element_secp_r1_g1 &other) const {
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

                        constexpr bool operator!=(const element_secp_r1_g1 &other) const {
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
                         * @return true if element from group G1 in affine coordinates
                         */
                        constexpr bool is_special() const {
                            return (this->is_zero() || this->Z.is_one());
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
                                const underlying_field_value_type X2 = this->X.squared();
                                const underlying_field_value_type Y2 = this->Y.squared();
                                const underlying_field_value_type Z2 = this->Z.squared();

                                return (this->Z * (Y2 - b * Z2) == this->X * (X2 + a * Z2));
                            }
                        }

                        /*************************  Arithmetic operations  ***********************************/

                        constexpr element_secp_r1_g1 operator=(const element_secp_r1_g1 &other) {
                            // handle special cases having to do with O
                            this->X = other.X;
                            this->Y = other.Y;
                            this->Z = other.Z;

                            return *this;
                        }

                        constexpr element_secp_r1_g1 operator+(const element_secp_r1_g1 &other) const {
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

                            return this->add(other);
                        }

                        constexpr element_secp_r1_g1 operator-() const {
                            return element_secp_r1_g1(this->X, -this->Y, this->Z);
                        }

                        constexpr element_secp_r1_g1 operator-(const element_secp_r1_g1 &other) const {
                            return (*this) + (-other);
                        }
                        /** @brief
                         *
                         * @return doubled element from group G1
                         */
                        constexpr element_secp_r1_g1 doubled() const {

                            if (this->is_zero()) {
                                return (*this);
                            } else {
                                // NOTE: does not handle O and pts of order 2,4
                                // http://www.hyperelliptic.org/EFD/g1p/auto-shortw-projective.html#doubling-dbl-2007-bl

                                const underlying_field_value_type XX = (this->X).squared();       // XX  = X1^2
                                const underlying_field_value_type ZZ = (this->Z).squared();       // ZZ  = Z1^2
                                const underlying_field_value_type w = a * ZZ + (XX + XX + XX);    // w   = a*ZZ + 3*XX
                                const underlying_field_value_type Y1Z1 = (this->Y) * (this->Z);
                                const underlying_field_value_type s = Y1Z1 + Y1Z1;      // s   = 2*Y1*Z1
                                const underlying_field_value_type ss = s.squared();     // ss  = s^2
                                const underlying_field_value_type sss = s * ss;         // sss = s*ss
                                const underlying_field_value_type R = (this->Y) * s;    // R   = Y1*s
                                const underlying_field_value_type RR = R.squared();     // RR  = R^2
                                const underlying_field_value_type B =
                                    ((this->X) + R).squared() - XX - RR;    // B   = (X1+R)^2 - XX - RR
                                const underlying_field_value_type h = w.squared() - B.doubled();    // h   = w^2 - 2*B
                                const underlying_field_value_type X3 = h * s;                       // X3  = h*s
                                const underlying_field_value_type Y3 =
                                    w * (B - h) - RR.doubled();                // Y3  = w*(B-h) - 2*RR
                                const underlying_field_value_type Z3 = sss;    // Z3  = sss

                                return element_secp_r1_g1(X3, Y3, Z3);
                            }
                        }
                        /** @brief
                         *
                         * “Mixed addition” refers to the case Z2 known to be 1.
                         * @return addition of two elements from group G1
                         */
                        constexpr element_secp_r1_g1 mixed_add(const element_secp_r1_g1 &other) const {

                            // NOTE: does not handle O and pts of order 2,4
                            // http://www.hyperelliptic.org/EFD/g1p/auto-shortw-projective.html#addition-add-1998-cmo-2

                            if (this->is_zero()) {
                                return other;
                            }

                            if (other.is_zero()) {
                                return (*this);
                            }

                            const underlying_field_value_type &X1Z2 =
                                (this->X);    // X1Z2 = X1*Z2 (but other is special and not zero)
                            const underlying_field_value_type X2Z1 = (this->Z) * (other.X);    // X2Z1 = X2*Z1

                            // (used both in add and double checks)

                            const underlying_field_value_type &Y1Z2 =
                                (this->Y);    // Y1Z2 = Y1*Z2 (but other is special and not zero)
                            const underlying_field_value_type Y2Z1 = (this->Z) * (other.Y);    // Y2Z1 = Y2*Z1

                            if (X1Z2 == X2Z1 && Y1Z2 == Y2Z1) {
                                return this->doubled();
                            }

                            const underlying_field_value_type u = Y2Z1 - this->Y;                // u = Y2*Z1-Y1
                            const underlying_field_value_type uu = u.squared();                  // uu = u2
                            const underlying_field_value_type v = X2Z1 - this->X;                // v = X2*Z1-X1
                            const underlying_field_value_type vv = v.squared();                  // vv = v2
                            const underlying_field_value_type vvv = v * vv;                      // vvv = v*vv
                            const underlying_field_value_type R = vv * this->X;                  // R = vv*X1
                            const underlying_field_value_type A = uu * this->Z - vvv - R - R;    // A = uu*Z1-vvv-2*R
                            const underlying_field_value_type X3 = v * A;                        // X3 = v*A
                            const underlying_field_value_type Y3 =
                                u * (R - A) - vvv * this->Y;                         // Y3 = u*(R-A)-vvv*Y1
                            const underlying_field_value_type Z3 = vvv * this->Z;    // Z3 = vvv*Z1

                            return element_secp_r1_g1(X3, Y3, Z3);
                        }

                    private:
                        constexpr element_secp_r1_g1 add(const element_secp_r1_g1 &other) const {

                            // NOTE: does not handle O and pts of order 2,4
                            // http://www.hyperelliptic.org/EFD/g1p/auto-shortw-projective.html#addition-add-1998-cmo-2

                            const underlying_field_value_type Y1Z2 = (this->Y) * (other.Z);        // Y1Z2 = Y1*Z2
                            const underlying_field_value_type X1Z2 = (this->X) * (other.Z);        // X1Z2 = X1*Z2
                            const underlying_field_value_type Z1Z2 = (this->Z) * (other.Z);        // Z1Z2 = Z1*Z2
                            const underlying_field_value_type u = (other.Y) * (this->Z) - Y1Z2;    // u    = Y2*Z1-Y1Z2
                            const underlying_field_value_type uu = u.squared();                    // uu   = u^2
                            const underlying_field_value_type v = (other.X) * (this->Z) - X1Z2;    // v    = X2*Z1-X1Z2
                            const underlying_field_value_type vv = v.squared();                    // vv   = v^2
                            const underlying_field_value_type vvv = v * vv;                        // vvv  = v*vv
                            const underlying_field_value_type R = vv * X1Z2;                       // R    = vv*X1Z2
                            const underlying_field_value_type A =
                                uu * Z1Z2 - (vvv + R + R);                   // A    = uu*Z1Z2 - vvv - 2*R
                            const underlying_field_value_type X3 = v * A;    // X3   = v*A
                            const underlying_field_value_type Y3 =
                                u * (R - A) - vvv * Y1Z2;                         // Y3   = u*(R-A) - vvv*Y1Z2
                            const underlying_field_value_type Z3 = vvv * Z1Z2;    // Z3   = vvv*Z1Z2

                            return element_secp_r1_g1(X3, Y3, Z3);
                        }

                    public:
                        /*************************  Reducing operations  ***********************************/
                        /** @brief
                         *
                         * @return return the corresponding element from group G1 in affine coordinates
                         */
                        constexpr element_secp_r1_g1 to_affine() const {
                            underlying_field_value_type p_out[3];

                            if (this->is_zero()) {
                                p_out[0] = underlying_field_value_type::zero();
                                p_out[1] = underlying_field_value_type::one();
                                p_out[2] = underlying_field_value_type::zero();
                            } else {
                                const underlying_field_value_type Z_inv = this->Z.inversed();
                                p_out[0] = this->X * Z_inv;
                                p_out[1] = this->Y * Z_inv;
                                p_out[2] = underlying_field_value_type::one();
                            }

                            return element_secp_r1_g1(p_out[0], p_out[1], p_out[2]);
                        }
                        /** @brief
                         *
                         * @return return the corresponding element from group G1 in affine coordinates
                         */
                        constexpr element_secp_r1_g1 to_projective() const {
                            return this->to_affine();
                        }

                    private:
                        constexpr static const g1_field_type_value a = policy_type::a;
                        constexpr static const g1_field_type_value b = policy_type::b;
                    };

                    constexpr typename element_secp_r1_g1<256>::g1_field_type_value const element_secp_r1_g1<256>::a;
                    constexpr typename element_secp_r1_g1<256>::g1_field_type_value const element_secp_r1_g1<256>::b;

                }    // namespace detail
            }        // namespace curves
        }            // namespace algebra
    }                // namespace crypto3
}    // namespace nil
#endif    // CRYPTO3_ALGEBRA_CURVES_SECP_G1_ELEMENT_HPP