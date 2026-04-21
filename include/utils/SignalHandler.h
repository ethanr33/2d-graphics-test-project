#pragma once

#include <functional>
#include <vector>

template<typename... Args>
class SignalHandler {
    private:
        std::vector<std::function<void(Args...)>> slots;
    public:
        /**
         * @brief Add a slot to handler
         */
        void connect(std::function<void(Args...)> fn) {
            slots.push_back(fn);
        }

        /**
         * @brief Invoke all slots
        */
        void invoke(Args... args) const {
            for (const auto& fn : slots) {
                fn(args...);
            }
        }
};