#ifndef CHECKERS_REST_IA_C_RANDOMTEXTGENERATOR_H
#define CHECKERS_REST_IA_C_RANDOMTEXTGENERATOR_H

#include <string>
#include <cstdlib>
#include <ctime>

using std::string;
using std::time;
using std::srand;
using std::size_t;

namespace Domain {
    namespace Tool {
        class RandomTextGenerator {
        public:
            /**
             * @return an instance of RandomTextGenerator
             */
            static RandomTextGenerator &getInstance() {
                // Will not be deleted.
                static RandomTextGenerator instance;
                return instance;
            }

        public:
            RandomTextGenerator(
                    const string &str =
                        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789")
                    : m_str(str) {
                srand((unsigned int) time(NULL));
            }

            RandomTextGenerator(RandomTextGenerator const &) = delete;

            void operator=(RandomTextGenerator const &) = delete;

            /**
             * Generates a new random string of length len.
             * @param len the length of the generated string
             * @return a new random string
             */
            string operator()(size_t len = 1) {
                string seq;
                size_t siz = m_str.size();
                if (siz) {
                    while (len--) {
                        seq.push_back(m_str[rand() % siz]);
                    }
                }
                return seq;
            }

        private:
            string m_str;
        };
    }
}


#endif
