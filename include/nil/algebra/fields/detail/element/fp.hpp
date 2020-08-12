//---------------------------------------------------------------------------//
// Copyright (c) 2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef ALGEBRA_FIELDS_ELEMENT_FP_HPP
#define ALGEBRA_FIELDS_ELEMENT_FP_HPP

#include <nil/algebra/fields/element.hpp>
#include <nil/algebra/fields/fp.hpp>

namespace nil {
    namespace algebra {
        namespace fields {
            namespace detail {

                template<std::size_t ModulusBits, std::size_t GeneratorBits>
                struct element_fp : public element<fp<ModulusBits, GeneratorBits>> {

                    typedef params_type::modulus_type modulus_type;

                    using type = modulus_type;

                private:

                    type data;

                public:
                    element_fp(type data) : data(data);

                    inline static element_fp zero() const {
                        return element_fp(type(0));
                    }

                    inline static element_fp one() const {
                        return element_fp(type(1));
                    }

                    bool is_zero() const {
                        return data == type(0);
                    }

                    bool is_one() const {
                        return data == type(1);
                    }

                    bool operator==(const element_fp &B) const {
                        return data == B.data;
                    }

                    bool operator!=(const element_fp &B) const {
                        return data != B.data;
                    }

                    element_fp operator+(const element_fp &B) const {
                        return data + B.data;
                    }

                    element_fp operator-(const element_fp &B) const {
                        return data - B.data;
                    }

                    element_fp operator-() const {
                        return -data;
                    }

                    element_fp operator*(const element_fp &B) const {
                        return data * B.data;
                    }

                    element_fp dbl() const {
                        return data + data;
                    }

                    element_fp sqrt() const {
                        return sqrt(data);
                    }

                    element_fp _2z_add_3x() {
                        
                    }

                    element_fp square() const {
                        return data * data;    // maybe can be done more effective
                    }

                    template<typename PowerType>
                    element_fp pow(const PowerType &power) const {
                        return detail::power(data, power);
                    }

                    element_fp inverse() const {
                        return invert(data);
                    }
                };

            }   // namespace detail
        }   // namespace fields
    }    // namespace algebra
}    // namespace nil

#endif    // ALGEBRA_FIELDS_ELEMENT_FP_HPP
