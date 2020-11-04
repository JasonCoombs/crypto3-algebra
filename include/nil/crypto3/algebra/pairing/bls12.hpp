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

#ifndef CRYPTO3_ALGEBRA_PAIRING_BLS12_POLICY_HPP
#define CRYPTO3_ALGEBRA_PAIRING_BLS12_POLICY_HPP

#include <nil/crypto3/algebra/pairing/detail/bls12/basic_policy.hpp>
#include <nil/crypto3/algebra/pairing/detail/bls12/functions.hpp>
#include <nil/crypto3/algebra/pairing/basic_policy.hpp>

#include <nil/crypto3/algebra/curves/bls12.hpp>

namespace nil {
    namespace crypto3 {
        namespace algebra {
            namespace curves {
                template<std::size_t ModulusBits>
                struct bls12;
            }    // namespace curves
            namespace pairing {

                template<typename PairingCurveType, typename PairingFunctions>
                struct pairing_policy;

                using namespace nil::crypto3::algebra;

                template<std::size_t ModulusBits, typename PairingFunctions>
                class pairing_policy<curves::bls12<ModulusBits>, PairingFunctions>{
                    using policy_type = PairingFunctions;
                    using basic_policy = detail::bls12_basic_policy<ModulusBits>;

                public:
                    using number_type = typename basic_policy::number_type;

                    constexpr static const typename basic_policy::number_type pairing_loop_count =
                        basic_policy::ate_loop_count;

                    using Fp_type = typename basic_policy::Fp_field;
                    using G1_type = typename basic_policy::g1;
                    using G2_type = typename basic_policy::g2;
                    using Fq_type = typename basic_policy::Fq_field;
                    using Fqe_type = typename basic_policy::Fqe_field;
                    using Fqk_type = typename basic_policy::Fqk_field;
                    using GT_type = typename basic_policy::gt;

                    using G1_precomp = typename policy_type::g1_precomp;
                    using G2_precomp = typename policy_type::g2_precomp;

                    static inline typename policy_type::g1_precomp precompute_g1(const typename policy_type::g1 &P) {
                        return policy_type::precompute_g1(P);
                    }

                    static inline typename policy_type::g2_precomp precompute_g2(const typename policy_type::g2 &Q) {
                        return policy_type::precompute_g2(Q);
                    }

                    static inline typename policy_type::gt pairing(const typename policy_type::g1 &P, 
                                                                   const typename policy_type::g2 &Q) {
                        return policy_type::pairing(P, Q);
                    }

                    static inline typename policy_type::gt reduced_pairing(const typename policy_type::g1 &P, 
                                                                           const typename policy_type::g2 &Q) {
                        return policy_type::reduced_pairing(P, Q);
                    }

                    static inline typename policy_type::gt double_miller_loop(const typename policy_type::g1_precomp &prec_P1, 
                                                                              const typename policy_type::g2_precomp &prec_Q1, 
                                                                              const typename policy_type::g1_precomp &prec_P2, 
                                                                              const typename policy_type::g2_precomp &prec_Q2) {
                        return policy_type::double_miller_loop(prec_P1, prec_Q1, prec_P2, prec_Q2);
                    }

                    static inline typename policy_type::gt final_exponentiation(const typename policy_type::gt &elt) {
                        return policy_type::final_exponentiation(elt);
                    }

                    static inline typename policy_type::gt miller_loop(const typename policy_type::g1_precomp &prec_P, 
                                                                       const typename policy_type::g2_precomp &prec_Q) {
                        return policy_type::miller_loop(prec_P, prec_Q);
                    }
                };

                template<std::size_t ModulusBits, typename PairingFunctions>
                constexpr typename pairing_policy<curves::bls12<ModulusBits>, PairingFunctions>::number_type const
                    pairing_policy<curves::bls12<ModulusBits>, PairingFunctions>::pairing_loop_count;
            }    // namespace pairing
        }        // namespace algebra
    }            // namespace crypto3
}    // namespace nil
#endif    // CRYPTO3_ALGEBRA_PAIRING_BLS12_POLICY_HPP