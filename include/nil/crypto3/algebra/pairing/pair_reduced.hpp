//---------------------------------------------------------------------------//
// Copyright (c) 2020-2021 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020-2021 Nikita Kaskov <nbering@nil.foundation>
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

#ifndef CRYPTO3_ALGEBRA_PAIRING_PAIR_REDUCED_HPP
#define CRYPTO3_ALGEBRA_PAIRING_PAIR_REDUCED_HPP

namespace nil {
    namespace crypto3 {
        namespace algebra {
            namespace pairing {

                template<typename PairingCurveType>
                struct pair;

                template<typename PairingCurveType>
                struct final_exponentiation;

                template<typename PairingCurveType, 
                         typename Pair = pair<PairingCurveType>, 
                         typename FinalExponentiation = final_exponentiation<PairingCurveType>>
                class pair_reduced {
                    using curve_type = PairingCurveType;

                    using g1_type = typename curve_type::g1_type;
                    using g2_type = typename curve_type::g2_type;
                    using gt_type = typename curve_type::gt_type;
                public:

                    static typename gt_type::value_type process(
                        const typename g1_type::value_type &P, 
                        const typename g2_type::value_type &Q) {

                        const typename gt_type::value_type f = Pair::process(P, Q);
                        const typename gt_type::value_type result = 
                            FinalExponentiation::process(f);
                        return result;
                    }
                };
            }        // namespace pairing
        }            // namespace algebra
    }                // namespace crypto3
}    // namespace nil
#endif    // CRYPTO3_ALGEBRA_PAIRING_PAIR_REDUCED_HPP