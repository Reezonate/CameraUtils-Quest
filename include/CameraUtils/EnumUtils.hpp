#pragma once

namespace CameraUtils {
    template<class T>
    inline T operator~(T a) { return (T) ~(int) a; }

    template<class T>
    inline T operator|(T a, T b) { return (T) ((int) a | (int) b); }

    template<class T>
    inline T operator&(T a, T b) { return (T) ((int) a & (int) b); }

    template<class T>
    inline T operator^(T a, T b) { return (T) ((int) a ^ (int) b); }

    template<class T>
    inline T &operator|=(T &a, T b) { return (T &) ((int &) a |= (int) b); }

    template<class T>
    inline T &operator&=(T &a, T b) { return (T &) ((int &) a &= (int) b); }

    template<class T>
    inline T &operator^=(T &a, T b) { return (T &) ((int &) a ^= (int) b); }

    template<class T>
    inline bool HasFlag(T value, T flag) {
        return ((int) value & (int) flag) > 0;
    }
}