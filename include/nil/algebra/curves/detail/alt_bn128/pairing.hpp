//---------------------------------------------------------------------------//
// Copyright (c) 2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef ALGEBRA_CURVES_BN128_PAIRING_HPP
#define ALGEBRA_CURVES_BN128_PAIRING_HPP

#include <sstream>

#include <nil/algebra/curves/detail/bn128/bn128_g1.hpp>
#include <nil/algebra/curves/detail/bn128/bn128_g2.hpp>
#include <nil/algebra/curves/detail/bn128/bn128_gt.hpp>
#include <nil/algebra/curves/detail/bn128/bn128_init.hpp>

namespace nil {
    namespace algebra {
        namespace curves {
            namespace detail {

                template<std::size_t ModulusBits, std::size_t GeneratorBits>
                using fp_value_type = element_fp<ModulusBits, GeneratorBits>;

                template<std::size_t ModulusBits, std::size_t GeneratorBits>
                using fp2_value_type = element_fp2<ModulusBits, GeneratorBits>;

                struct bn128_ate_g1_precomp {
                    fp_value_type P[3];

                    bool operator==(const bn128_ate_g1_precomp &other) const {
                        return (P[0] == other.P[0] && P[1] == other.P[1] && P[2] == other.P[2]);
                    }
                };

                typedef element_fp6_3over2 bn128_ate_ell_coeffs;

                struct bn128_ate_g2_precomp {
                    fp2_value_type Q[3];
                    std::vector<bn128_ate_ell_coeffs> coeffs;

                    bool operator==(const bn128_ate_g2_precomp &other) const {
                        if (!(Q[0] == other.Q[0] && Q[1] == other.Q[1] && Q[2] == other.Q[2] &&
                              coeffs.size() == other.coeffs.size())) {
                            return false;
                        }

                        /* work around for upstream serialization bug */
                        for (size_t i = 0; i < coeffs.size(); ++i) {
                            std::stringstream this_ss, other_ss;
                            this_ss << coeffs[i];
                            other_ss << other.coeffs[i];
                            if (this_ss.str() != other_ss.str()) {
                                return false;
                            }
                        }

                        return true;
                    }
                };

                bn128_ate_g1_precomp bn128_ate_precompute_g1(const bn128_g1 &P) {

                    bn128_ate_g1_precomp result;
                    nil::algebra::pairing::detail::NormalizeJac(result.P, P.coord);

                    return result;
                }
                bn128_ate_g2_precomp bn128_ate_precompute_g2(const bn128_g2 &Q) {

                    bn128_ate_g2_precomp result;
                    nil::algebra::pairing::precomputeg2(result.coeffs, result.Q, Q.coord);

                    return result;
                }

                bn128_Fq12 bn128_double_ate_miller_loop(const bn128_ate_g1_precomp &prec_P1,
                                                        const bn128_ate_g2_precomp &prec_Q1,
                                                        const bn128_ate_g1_precomp &prec_P2,
                                                        const bn128_ate_g2_precomp &prec_Q2) {
                    bn128_Fq12 f;

                    nil::algebra::pairing::millerLoop2(f.elem, prec_Q1.coeffs, prec_P1.P, prec_Q2.coeffs, prec_P2.P);
                    return f;
                }

                bn128_Fq12 bn128_ate_miller_loop(const bn128_ate_g1_precomp &prec_P,
                                                 const bn128_ate_g2_precomp &prec_Q) {
                    bn128_Fq12 f;
                    nil::algebra::pairing::millerLoop(f.elem, prec_Q.coeffs, prec_P.P);
                    return f;
                }

                bn128_gt bn128_final_exponentiation(const bn128_Fq12 &elt) {
                    bn128_gt eltcopy = elt;
                    eltcopy.elem.final_exp();
                    return eltcopy;
                }

                template <std::size_t ModulusBits, std::size_t GeneratorBits>
                static bn128_gt final_exponentiation<bn128<ModulusBits, GeneratorBits>>(const bn128_Fq12 &elt) {
                    return bn128_final_exponentiation(elt);
                }

                template <std::size_t ModulusBits, std::size_t GeneratorBits>
                static bn128_Fq12 miller_loop<bn128<ModulusBits, GeneratorBits>>(const bn128_ate_g1_precomp &prec_P,
                                              const bn128_ate_g2_precomp &prec_Q) {

                    bn128_Fq12 result = bn128_ate_miller_loop(prec_P, prec_Q);

                    return result;
                }

                template <std::size_t ModulusBits, std::size_t GeneratorBits>
                static bn128_Fq12 double_miller_loop<bn128<ModulusBits, GeneratorBits>>(const bn128_ate_g1_precomp &prec_P1,
                                                     const bn128_ate_g2_precomp &prec_Q1,
                                                     const bn128_ate_g1_precomp &prec_P2,
                                                     const bn128_ate_g2_precomp &prec_Q2) {

                    bn128_Fq12 result = bn128_double_ate_miller_loop(prec_P1, prec_Q1, prec_P2, prec_Q2);

                    return result;
                }
                
            }    // namespace detail
        }        // namespace curves
    }            // namespace algebra
}    // namespace nil
#endif    // ALGEBRA_CURVES_BN128_PAIRING_HPP
